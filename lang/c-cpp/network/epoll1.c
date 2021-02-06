#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> /* close() definitions */
#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <arpa/inet.h> /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h> /* nonblocking */
#include <sys/resource.h> /* setrlimit */

#define MAXEPOLLSIZE 10000
#define MAXLINE 10240

int handle(int connfd);
int setnonblocking(int sockfd) {
  if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "epoll1 <port>\n");
    return -1;
  }
  int sport; //服务器端口
  int listenq = 1024;
  int listenfd, connfd, kdpfd, nfds, nread, n, curfds, naccept = 0;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t socklen = sizeof(struct sockaddr_in);
  struct epoll_event ev;
  struct epoll_event events[MAXEPOLLSIZE];
  struct rlimit rt;
  char buf[MAXLINE];
  char ipbuf[16];

  /* 设置每个进程允许打开的最大文件数 */
  rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
  if (setrlimit(RLIMIT_NOFILE, &rt) == -1) {
    perror("setrlimit error");
    return -1;
  }

  sport = atoi(argv[1]);
  if (sport <= 0) {
    fprintf(stderr, "epoll1 <port>\n");
    return -1;
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(sport);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1) {
    perror("socket error");
    return -1;
  }

  int opt = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  if (setnonblocking(listenfd) < 0){
    perror("setnonblock error");
  }

  if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
    perror("bind error");
    return -1;
  }

  if (listen(listenfd, 512) == -1) {
    perror("listen error");
    return -1;
  }

  /* 创建epoll句柄 */
  kdpfd = epoll_create(MAXEPOLLSIZE);
  curfds = 0;

  /* 将标准输入加入到epoll */
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = STDIN_FILENO;
  if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
    return -1;
  }
  curfds++;

  /* 把监听socket加入到epoll结合中 */
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = listenfd;
  if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) {
    fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
    return -1;
  }
  curfds++;

  printf("listen to %s:%d\n",
         inet_ntop(AF_INET, &servaddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(servaddr.sin_port));
  for (;;) {
    /* 等待有事件 */
    nfds = epoll_wait(kdpfd, events, curfds, -1);
    if (nfds == -1) {
      perror("epoll_wait");
      continue;
    }
    /* 处理所有事件 */
    for (n = 0; n<nfds; ++n) {
      if (events[n].data.fd == listenfd) {
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &socklen);
        if (connfd == -1) {
          perror("accpet");
          continue;
        }
        sprintf(buf, "accept from %s:%d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(cliaddr.sin_port));
        printf("%d:%s", ++naccept, buf);
        if (curfds >= MAXEPOLLSIZE) {
          fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
          close(connfd);
          continue;
        }
        if (setnonblocking(connfd) < 0) {
          perror("setnonblocking error");
        }
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = connfd;
        if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, connfd, &ev) < 0) {
          fprintf(stderr, "add socket '%d' to epoll failed:%s\n", connfd, strerror(errno));
          return -1;
        }

        curfds++;
        continue;
      }
      if (events[n].data.fd == STDIN_FILENO) {
        nread = read(STDIN_FILENO, buf, sizeof(buf));
        buf[sizeof(buf)-1] = '\n';
        if (nread <= 0) {
          fprintf(stderr, "read stdin failed: %s\n", strerror(errno));
        } else if (strncasecmp(buf, "quit", 4) == 0) {
          printf("exit\n");
          exit(0);
        }
        continue;
      }
      //处理客户端请求
      if (handle(events[n].data.fd) < 0) {
        epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
        curfds--;
      }
    }
  }
  close(listenfd);
  return 0;
}

int handle(int connfd) {
  int nread;
  char buf[MAXLINE];

  nread = read(connfd, buf, sizeof(buf));
  if (nread == 0) {
    printf("client close the connection\n");
    close(connfd);
    return -1;
  }
  if (nread < 0) {
    perror("read error");
    close(connfd);
    return -1;
  }
  write(connfd, buf, nread); //响应客户端
  return 0;
}
