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

#include "sd_epoll.h"

#define BUFSIZE 10240

struct context {
  int naccept;
};

static int setnonblocking(int sockfd) {
  if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
    return -1;
  }
  return 0;
}

static int read_stdin(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  char buf[BUFSIZE];
  fgets(buf, sizeof(buf), stdin);
  buf[sizeof(buf)-1] = '\0';
  int slen = strlen(buf);
  if (slen > 0) {
    if (buf[slen-1] == '\n') {
      buf[slen-1] = '\0';
      slen--;
    }
  }

  if (strncasecmp(buf, "quit", 4) == 0) {
    sd_epoll_stop(mgr); //停止事件循环
    return 0;
  }

  int connfd = p_so->data.fd;
  write(connfd, buf, strlen(buf));
  return 0;
}

static int read_client(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  int nread;
  char buf[BUFSIZE];
  int connfd = p_so->fd;

  nread = read(connfd, buf, sizeof(buf)-1);
  buf[nread] = '\0';
  if (nread == 0) {
    printf("client close the connection\n");
    sd_epoll_opt_destory(mgr, p_so);
    return -1;
  }
  if (nread < 0) {
    perror("read error");
    sd_epoll_opt_destory(mgr, p_so);
    return -1;
  }

  printf("recv from client: %s\n", buf);
  write(connfd, buf, nread); //响应客户端
  return 0;
}

static int onconnect(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  char buf[BUFSIZE], ipbuf[16];
  struct sockaddr_in cliaddr;
  struct sd_epoll_opt *opt_conn;
  socklen_t socklen;
  int listenfd = p_so->fd;

  struct context *ctx = (struct context*)mgr->ctx;

  int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &socklen);
  if (connfd == -1) {
    perror("accpet");
    return -1;
  }
  sprintf(buf, "accept from %s:%d\n",
          inet_ntop(AF_INET, &cliaddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(cliaddr.sin_port));
  printf("%d:%s", ++ctx->naccept, buf);
  if (mgr->curfds >= MAXEPOLLSIZE) {
    fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
    close(connfd);
    return -1;
  }
  if (setnonblocking(connfd) < 0) {
    perror("setnonblocking error");
  }

  if (sd_epoll_opt_create(&opt_conn) == -1) {
    return -1;
  }
  opt_conn->fd = connfd;
  opt_conn->handle = read_client;

  if (sd_epoll_opt_add(mgr, opt_conn) == -1) {
    return -1;
  }
  return 0;
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "epoll2 <port>\n");
    return -1;
  }
  int sport; //服务器端口
  int listenfd;
  struct sockaddr_in servaddr;
  struct rlimit rt;
  char ipbuf[16];
  struct context ctx;

  struct sd_epoll_opt *opt_stdin;
  struct sd_epoll_opt *opt_listen;
  struct sd_epoll_mgr mgr;

  bzero(&ctx, sizeof(ctx));

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

  if (sd_epoll_init(&mgr, &ctx) == -1) {
    return -1;
  }

  if (sd_epoll_opt_create(&opt_listen) == -1) {
    return -1;
  }
  opt_listen->fd = listenfd;
  opt_listen->handle = onconnect;

  if (sd_epoll_opt_create(&opt_stdin) == -1) {
    return -1;
  }
  opt_stdin->fd = STDIN_FILENO;
  opt_stdin->handle = read_stdin;

  if (sd_epoll_opt_add(&mgr, opt_listen) == -1) {
    return -1;
  }

  if (sd_epoll_opt_add(&mgr, opt_stdin) == -1) {
    return -1;
  }

  printf("listen to %s:%d\n",
         inet_ntop(AF_INET, &servaddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(servaddr.sin_port));

  if (sd_epoll_run(&mgr) == -1) {
    return -1;
  }
  sd_epoll_destory(&mgr);

  close(listenfd);
  return 0;
}

