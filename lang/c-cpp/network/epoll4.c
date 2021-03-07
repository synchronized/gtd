#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sd_buffer.h"
#include "sd_epoll.h"

#define MAX_CLIENT 1024
#define MIN_RSIZE 512
#define BACKLOG 1024

static void handle_accept(void *ctx, void *ud);
static void handle_read(void *ctx, void *ud);
static void handle_write(void *ctx, void *ud);
static void handle_error(void *ctx, void *ud);

//客户端连接信息
struct tclient {
  int fd; //客户端fd
  int rsize; //当前读取缓存的区大小
  int wsize; //还未写入的缓存区大小
  struct sd_buffer wblist; //写缓存列表
  struct sd_epoll_opt opt;
};

//服务器信息
struct tserver {
  struct tclient clients[MAX_CLIENT]; //客户端结构数组
  struct sd_epoll_opt opt_listen;
  struct sd_epoll_mgr mgr;
};

//监听端口,并且返回监听套接字的文件描述符
static int tcplisten(const char *host, int port, int backlog) {
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

//epoll修改写事件
static void epoll_write(struct tserver *server, struct tclient *client, int enabled) {
  assert(server);
  assert(client);

  client->opt.flags = SD_EPOLL_IN | (enabled ? SD_EPOLL_OUT : 0);
  sd_epoll_opt_mod(&server->mgr, &client->opt);
}

static void set_noblocking(int fd) {
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

  if (!client) {
    fprintf(stderr, "too many client: %d\n", fd);
    return NULL;
  }

  set_noblocking(fd); //设置非阻塞
  struct sd_epoll_opt *opt_conn = &client->opt;
  opt_conn->ud = client;
  opt_conn->fd = fd;
  opt_conn->handle_read = handle_read;
  opt_conn->handle_write = handle_write;
  opt_conn->handle_error = handle_error;
  opt_conn->flags |= SD_EPOLL_IN;
  int ret = sd_epoll_opt_add(&server->mgr, opt_conn);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_add(&server->mgr, opt_conn) failed ret:%d\n", ret);
    return NULL;
  }

  sd_buffer_init(&client->wblist);
  client->fd = fd;
  client->rsize = MIN_RSIZE;
  return client;
}

//关闭客户端
static int client_close(struct tserver *server, struct tclient *client) {
  assert(server);
  assert(client);
  assert(client->fd >= 0);

  struct sd_epoll_opt *opt_conn = &client->opt;
  int ret = sd_epoll_opt_del(&server->mgr, opt_conn);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_del(&server->mgr, opt_conn) failed ret:%d\n", ret);
    return -4;
  }
  if (close(client->fd) < 0) perror("close: ");
  client->fd = -1;
  client->wsize = 0;
  sd_buffer_destroy(&client->wblist);
  return 0;
}

//创建服务器
static int server_create(struct tserver* server, int listenfd) {
  if (server == NULL) return -1;

  bzero(server, sizeof(*server));
  for (int i=0; i<MAX_CLIENT; i++) {
    server->clients[i].fd = -1;
  }
  int ret;
  ret = sd_epoll_init(&server->mgr, server);
  if (ret) {
    fprintf(stderr, "sd_epoll_init(server->mgr, server) failed ret:%d\n", ret);
    return -2;
  }

  struct sd_epoll_opt *opt = &server->opt_listen;
  opt->fd = listenfd;
  opt->ud = opt;
  opt->handle_read = handle_accept; //TODO
  opt->flags = SD_EPOLL_IN;
  ret = sd_epoll_opt_add(&server->mgr, opt);
  if (ret) {
    sd_epoll_destory(&server->mgr);
    fprintf(stderr, "sd_epoll_opt_add(&server->mgr, opt) failed ret:%d\n", ret);
    return -3;
  }
  return 0;
}

//释放服务器
static int server_destory(struct tserver *server) {
  if (!server) return -1;

  int ret;

  for (int i=0; i<MAX_CLIENT; i++) {
    struct tclient *client = &(server->clients[i]);
    if (client->fd >= 0) {
      ret = client_close(server, client);
    }
  }

  ret = sd_epoll_opt_del(&server->mgr, &server->opt_listen);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_del(&server->mgr, opt) failed ret:%d\n", ret);
    return -2;
  }
  ret = sd_epoll_destory(&server->mgr);
  if (ret) {
    fprintf(stderr, "sd_epoll_destory(&server->mgr) failed ret:%d\n", ret);
    return -3;
  }
  return 0;
}

//处理接受连接
static void handle_accept(void *ctx, void *ud) {
  struct tserver *server = (struct tserver*)ctx;
  struct sd_epoll_opt *opt = (struct sd_epoll_opt*)ud;

  struct sockaddr_in claddr;
  socklen_t addrlen = sizeof(struct sockaddr_in);
  for (;;) {
    int connfd = accept(opt->fd, (struct sockaddr*)&claddr, &addrlen);
    if (connfd < 0) {
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
      printf("client connect: fd=%d, (%s:%s)\n", connfd, host, service);
    } else {
      printf("client connect: fd=%d, (?UNKNOWN?)\n", connfd);
    }
    struct tclient *client = client_create(server, connfd);
    if (!client) {
      close(connfd);
      fprintf(stderr, "client_create(server, %d) failed\n", connfd);
    }
    break;
  }
}

//处理读取
static void handle_read(void *ctx, void *ud) {
  struct tserver *server = (struct tserver*)ctx;
  struct tclient *client = (struct tclient*)ud;

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
  client->wsize = nread;
  //加入写缓存
  sd_buffer_append(&client->wblist, buf, nread);
  //加入写事件
  epoll_write(server, client, 1);
}

static void handle_write(void *ctx, void *ud) {
  struct tserver *server = (struct tserver*)ctx;
  struct tclient *client = (struct tclient*)ud;

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
  epoll_write(server, client, 0);
}

//处理错误
static void handle_error(void *ctx, void *ud) {
  struct tserver *server = (struct tserver*)ctx;
  struct tclient *client = (struct tclient*)ud;
  perror("client error:");
  int ret = client_close(server, client);
  if (ret) {
    fprintf(stderr, "client_close(server, client) failed ret:%d\n", ret);
  }
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

  ret = sd_epoll_run(&server->mgr);
  if (ret) {
    fprintf(stderr, "sd_epoll_run(&mgr) failed ret:%d\n", ret);
    return 2;
  }

  printf("server stop\n");
  server_destory(server);
  return 0;
}
