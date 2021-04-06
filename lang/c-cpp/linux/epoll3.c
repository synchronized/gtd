#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sd_buffer.h"

#define MAX_CLIENT 1000
#define BACKLOG 100
#define MIN_RSIZE 32
#define EVENT_NUM 64

//客户端连接信息
struct tclient {
  int fd; //客户端fd
  int rsize; //当前读取缓存的区大小
  int wsize; //还未写入的缓存区大小
  struct sd_buffer wblist; //写缓存列表
};

//服务器信息
struct tserver {
  int listenfd; //监听fd
  int epollfd; //epollfd
  struct tclient clients[MAX_CLIENT]; //客户端结构数组
};

//监听端口,并且返回监听套接字的文件描述符
int tcplisten(const char *host, int port, int backlog) {
  int listenfd;
  struct sockaddr_in saddr;

  bzero(&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  int ret = inet_pton(AF_INET, host, &saddr.sin_addr);
  if (ret < 0) {
    perror("inet_pton");
    return -1;
  }
  if (ret == 0) {
    fprintf(stderr, "invalid network address\n");
    return -1;
  }

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    perror("socket");
    close(listenfd);
    return -1;
  }
  if (bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
    perror("bind");
    close(listenfd);
    return -1;
  }
  if (listen(listenfd, backlog) < 0) {
    perror("listen");
    close(listenfd);
    return -1;
  }
  return listenfd;
}

//epoll增加读事件
void epoll_add(int efd, int fd, void *ud) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.ptr = ud;
  epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
}

//epoll修改写事件
void epoll_write(int efd, int fd, void *ud, int enabled) {
  struct epoll_event ev;
  ev.events = EPOLLIN | (enabled ? EPOLLOUT : 0);
  ev.data.ptr = ud;
  epoll_ctl(efd, EPOLL_CTL_MOD, fd, &ev);
}

//epoll删除事件
void epoll_del(int efd, int fd) {
  epoll_ctl(efd, EPOLL_CTL_DEL, fd, NULL);
}

void set_noblocking(int fd) {
  int flag = fcntl(fd, F_GETFL, 0);
  if (flag >= 0) {
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
  }
}


//创建客户信息
struct tclient* client_create(struct tserver *server, int fd) {
  int i;
  struct tclient *client = NULL;
  for (i=0; i<MAX_CLIENT; i++) {
    if (server->clients[i].fd < 0) {
      client = &server->clients[i];
      break;
    }
  }

  if (client) {
    sd_buffer_init(&client->wblist);
    client->fd = fd;
    client->rsize = MIN_RSIZE;
    set_noblocking(fd); //设置非阻塞
    epoll_add(server->epollfd, fd, client); //增加读事件
    return client;
  } else {
    fprintf(stderr, "too many client: %d\n", fd);
    close(fd);
    return NULL;
  }
}

//关闭客户端
void client_close(struct tserver *server, struct tclient *client) {
  assert(client->fd >= 0);
  epoll_del(server->epollfd, client->fd);
  if (close(client->fd) < 0) perror("close: ");
  client->fd = -1;
  client->wsize = 0;
  sd_buffer_destroy(&client->wblist);
}

//创建服务器
int server_create(struct tserver* server, int listenfd) {
  if (server == NULL) return -1;

  bzero(server, sizeof(*server));
  for (int i=0; i<MAX_CLIENT; i++) {
    server->clients[i].fd = -1;
  }
  server->epollfd = epoll_create(MAX_CLIENT);
  server->listenfd = listenfd;
  epoll_add(server->epollfd, server->listenfd, NULL);
  return 0;
}

//释放服务器
void server_destory(struct tserver *server) {
  for (int i=0; i<MAX_CLIENT; i++) {
    struct tclient *client = &server->clients[i];
    if (client->fd >= 0) {
      client_close(server, client);
    }
  }
  epoll_del(server->epollfd, server->listenfd);
  close(server->listenfd);
  close(server->epollfd);
  free(server);
}

//处理接受连接
void handle_accept(struct tserver *server) {
  struct sockaddr_in claddr;
  socklen_t addrlen = sizeof(struct sockaddr_in);
  for (;;) {
    int cfd = accept(server->listenfd, (struct sockaddr*)&claddr, &addrlen);
    if (cfd < 0) {
      int no = errno;
      if (no == EINTR) {
        continue;
      }
      perror("accept:");
      exit(1); //出错
    }
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    if (getnameinfo((struct sockaddr*)&claddr, addrlen, host, sizeof(host), service, sizeof(service), 0) == 0) {
      printf("client connect: fd=%d, (%s:%s)\n", cfd, host, service);
    } else {
      printf("client connect: fd=%d, (?UNKNOWN?)\n", cfd);
    }
    client_create(server, cfd);
    break;
  }
}

//处理读取
void handle_read(struct tserver *server, struct tclient *client) {
  int sz = client->rsize;
  char *buf = (char*)malloc(sz);
  size_t nread = read(client->fd, buf, sz);
  if (nread < 0) { //出错
    free(buf);
    int no = errno;
    if (no != EINTR && no != EAGAIN && no != EWOULDBLOCK) {
      perror("read");
      client_close(server, client);
    }
    return;
  }
  if (nread == 0) { //客户端关闭
    free(buf);
    printf("client close: %d\n", client->fd);
    client_close(server, client);
    return;
  }
  // 确定下一次读的大小
  if (nread == sz) {
    client->rsize <<= 1;
  } else if (sz > MIN_RSIZE && (nread * 2 < sz)) {
    client->rsize >>= 1;
  }
  //加入写缓存
  sd_buffer_append(&client->wblist, buf, nread);
  //加入写事件
  epoll_write(server->epollfd, client->fd, client, 1);
}

void handle_write(struct tserver *server, struct tclient *client) {
  struct sd_buffer *list = &client->wblist;
  int size = sd_buffer_nextsize(list);
  while (size > 0) {
    char *buf = sd_buffer_nextdata(list);
    for (;;) {
      size_t sz = write(client->fd, buf, size);
      if (sz < 0) {
        int no = errno;
        if (no == EINTR) { //信号中断
          continue;
        } else if (no == EAGAIN || no == EWOULDBLOCK) { //内核缓冲区满， 下次再来
          return;
        }
        perror("write:");
        client_close(server, client);
        return;
      }
      client->wsize -= sz;
      int ret = sd_buffer_memmov(list, sz);
      if (ret != 0) {
        fprintf(stderr, "sd_buffer_memmov failed sz:%d size:%d ret:%d\n", sz, size, ret);
        return;
      }
      if (sz != size) { //未完全发送下次再来
        return;
      }
      free(buf); //释放buffer
      break;
    }
    size = sd_buffer_nextsize(list);
  }
  //这里写全部完成，关闭写事件
  epoll_write(server->epollfd, client->fd, client, 0);
}

//处理错误
void handle_error(struct tserver *server, struct tclient *client) {
  perror("client error:");
  client_close(server, client);
}


int main(int argc, char * argv[]) {
  if (argc < 3) {
    fprintf(stderr, "epoll3 <host> <port>\n");
    return 1;
  }

  int ret;
  int port = atoi(argv[2]);
  int listenfd = tcplisten(argv[1], port, BACKLOG);
  if (listenfd < 0) {
    fprintf(stderr, "tcplisten failed host:%s, poart:%d\n", argv[1], port);
    return 1;
  }
  printf("server start host:%s, poart:%d\n", argv[1], port);
  struct tserver lserver;
  struct tserver *server = &lserver;
  ret = server_create(server, listenfd);
  if (ret) {
    fprintf(stderr, "server_create(server, %d) failed ret:%d\n", listenfd, ret);
    return 1;
  }
  struct epoll_event events[EVENT_NUM];
  for (;;) {
    int nevent = epoll_wait(server->epollfd, events, EVENT_NUM, -1);
    if (nevent < 0) {
      if (errno != EINTR) {
        perror("epoll_wait");
        return 1;
      }
      continue;
    }
    if (nevent == 0){
      continue;
    }
    int i = 0;
    for (i = 0; i < nevent; i++) {
      struct epoll_event ev = events[i];
      if (ev.data.ptr == NULL) {
        handle_accept(server);
        continue;
      } else {
        struct tclient *client = ev.data.ptr;
        if (ev.events & (EPOLLIN | EPOLLHUP)) { //read
          handle_read(server, client);
        }
        if (ev.events & EPOLLOUT) {
          handle_write(server, client);
        }
        if (ev.events & EPOLLERR) {
          handle_error(server, client);
        }
      }
    }
  }
  printf("server stop\n");
  server_destory(server);
  return 0;
}
