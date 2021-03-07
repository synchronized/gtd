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
  struct sd_epoll_opt opt_stdin;
  struct sd_epoll_opt opt_listen;
  struct sd_epoll_mgr mgr;
};

int sd_epoll_opt_create(struct sd_epoll_opt **pp_opt) {
  if (pp_opt == NULL) return -1;
  *pp_opt = (struct sd_epoll_opt*)malloc(sizeof(struct sd_epoll_opt));
  if (*pp_opt == NULL) {
    perror("malloc failed");
    return -2;
  }
  bzero(*pp_opt, sizeof(struct sd_epoll_opt));
  return 0;
}

//从mgr中删除opt,并且销毁opt使用的内存
int sd_epoll_opt_destory(struct context *ctx, struct sd_epoll_opt *opt) {
  struct sd_epoll_mgr *mgr = &ctx->mgr;
  int ret = sd_epoll_opt_del(mgr, opt);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_del failed ret:%d\n", ret);
    return -1;
  }
  if (opt != &ctx->opt_listen && opt != &ctx->opt_stdin) {
    free(opt);
  }
  return 0;
}


static int setnonblocking(int sockfd) {
  if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK)) {
    return -1;
  }
  return 0;
}

static void read_stdin(void *_ctx, void *ud) {
  struct context *ctx = (struct context*)_ctx;
  struct sd_epoll_mgr *mgr = &ctx->mgr;
  struct sd_epoll_opt *opt = (struct sd_epoll_opt*)ud;

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
    return;
  }

  int connfd = opt->fd;
  write(connfd, buf, strlen(buf));
}

static void read_client(void *_ctx, void *ud) {
  struct context *ctx = (struct context*)_ctx;
  struct sd_epoll_opt *opt = (struct sd_epoll_opt*)ud;
  int nread;
  char buf[BUFSIZE];
  int connfd = opt->fd;

  nread = read(connfd, buf, sizeof(buf)-1);
  buf[nread] = '\0';
  if (nread == 0) {
    printf("client close the connection\n");
    sd_epoll_opt_destory(ctx, opt);
    return;
  }
  if (nread < 0) {
    perror("read error");
    sd_epoll_opt_destory(ctx, opt);
    return;
  }

  printf("recv from client: %s\n", buf);
  write(connfd, buf, nread); //响应客户端
  return;
}

static void onconnect(void *_ctx, void *ud) {
  struct context *ctx = (struct context*)_ctx;
  struct sd_epoll_mgr *mgr = &ctx->mgr;
  struct sd_epoll_opt *opt = (struct sd_epoll_opt*)ud;

  int ret;
  char buf[BUFSIZE], ipbuf[16];
  struct sockaddr_in cliaddr;
  struct sd_epoll_opt *opt_conn;
  socklen_t socklen;
  int listenfd = opt->fd;


  int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &socklen);
  if (connfd == -1) {
    perror("accpet");
    return;
  }
  sprintf(buf, "accept from %s:%d\n",
          inet_ntop(AF_INET, &cliaddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(cliaddr.sin_port));
  printf("%d:%s", ++ctx->naccept, buf);
  if (ctx->naccept >= MAXEPOLLSIZE) {
    fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
    close(connfd);
    return;
  }
  if (setnonblocking(connfd) < 0) {
    perror("setnonblocking error");
  }

  ret = sd_epoll_opt_create(&opt_conn);
  if (ret) {
    free(opt_conn);
    close(connfd);
    fprintf(stderr, "sd_epoll_opt_create failed %d\n", ret);
    return;
  }
  opt_conn->fd = connfd;
  opt_conn->ud = opt_conn;
  opt_conn->handle_read = read_client;
  opt_conn->flags |= SD_EPOLL_IN;

  ret = sd_epoll_opt_add(mgr, opt_conn);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_add(mgr, opt_conn) failed ret:%d\n", ret);
    return;
  }
  return;
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "epoll2 <port>\n");
    return -1;
  }
  int sport; //服务器端口
  int listenfd;
  int ret;
  struct sockaddr_in servaddr;
  struct rlimit rt;
  char ipbuf[16];
  struct context ctx;
  struct sd_epoll_mgr *mgr = &ctx.mgr;
  struct sd_epoll_opt *opt_listen = &ctx.opt_listen;
  struct sd_epoll_opt *opt_stdin = &ctx.opt_stdin;


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

  ret = sd_epoll_init(mgr, &ctx);
  if (ret) {
    fprintf(stderr, "sd_epoll_init(mgr, &ctx) failed ret:%d\n", ret);
    return -1;
  }

  opt_listen->fd = listenfd;
  opt_listen->ud = opt_listen;
  opt_listen->handle_read = onconnect;
  opt_listen->flags |= SD_EPOLL_IN;

  opt_stdin->fd = STDIN_FILENO;
  opt_stdin->ud = opt_stdin;
  opt_stdin->handle_read = read_stdin;
  opt_stdin->flags |= SD_EPOLL_IN;

  ret = sd_epoll_opt_add(mgr, opt_listen);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_add(mgr, opt_listen) failed ret:%d\n", ret);
    return -1;
  }

  ret = sd_epoll_opt_add(mgr, opt_stdin);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_add(mgr, opt_stdin) failed ret:%d\n", ret);
    return -1;
  }

  printf("listen to %s:%d\n",
         inet_ntop(AF_INET, &servaddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(servaddr.sin_port));

  ret = sd_epoll_run(mgr);
  if (ret) {
    fprintf(stderr, "sd_epoll_run(mgr) failed ret:%d\n", ret);
    return -1;
  }
  sd_epoll_destory(mgr);

  close(listenfd);
  return 0;
}

