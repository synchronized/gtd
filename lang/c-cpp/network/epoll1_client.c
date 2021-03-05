#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "sd_epoll.h"

#define BUFSIZE 4096

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

int read_stdin(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
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

int read_server(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so) {
  int nread;
  char buf[BUFSIZE];
  nread = read(p_so->fd, buf, sizeof(buf));
  if (nread == 0) {
    printf("close from server\n");
    sd_epoll_stop(mgr); //停止事件循环
    return 0;
  }
  else if(nread < 0) {
    perror("read");
    return -1;
  }
  buf[sizeof(buf)-1] = '\0';
  fprintf(stdout, "recv from server: %s\n", buf);
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "epoll1_client <ip> <port>\n");
    return -1;
  }
  int ret;
  int connfd, sport;
  char ipbuf[16];
  struct sockaddr_in saddr;
  struct sd_epoll_opt *opt_stdin;
  struct sd_epoll_opt *opt_client;
  struct sd_epoll_mgr mgr;

  sport = atoi(argv[2]);
  if (sport <= 0) {
    fprintf(stderr, "invalid port: %s\n", argv[2]);
    return -1;
  }

  bzero(&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(sport);
  if (inet_pton(AF_INET, argv[1], &saddr.sin_addr) == -1) {
    fprintf(stderr, "inet_pton(%s) failed: %s\n", argv[1], strerror(errno));
    return -1;
  }

  connfd = socket(AF_INET, SOCK_STREAM, 0);
  if (connfd == -1) {
    perror("socket failed");
    return -1;
  }

  if (connect(connfd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
    fprintf(stderr, "connect %s:%d failed: %s\n",
            inet_ntop(AF_INET, &saddr.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(saddr.sin_port), strerror(errno));
    return -1;
  }

  ret = sd_epoll_init(&mgr, NULL);
  if (ret) {
    fprintf(stderr, "sd_epoll_init(&mgr, NULL) failed ret:%d\n", ret);
    return -1;
  }

  ret = sd_epoll_opt_create(&opt_client);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_create(&opt_client) failed ret:%d\n", ret);
    return -1;
  }
  opt_client->fd = connfd;
  opt_client->handle = read_server;
  opt_client->flags |= SD_EPOLL_IN;

  ret = sd_epoll_opt_create(&opt_stdin);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_create(&opt_stdin) failed ret:%d\n", ret);
    return -1;
  }
  opt_stdin->fd = STDIN_FILENO;
  opt_stdin->handle = read_stdin;
  opt_stdin->data.fd = connfd;
  opt_stdin->flags |= SD_EPOLL_IN;

  ret = sd_epoll_opt_add(&mgr, opt_client);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_add(&mgr, opt_client) failed ret:%d\n", ret);
    return -1;
  }

  ret = sd_epoll_opt_add(&mgr, opt_stdin);
  if (ret) {
    fprintf(stderr, "sd_epoll_opt_add(&mgr, opt_stdin) failed ret:%d\n", ret);
    return -1;
  }

  ret = sd_epoll_run(&mgr);
  if (ret) {
    fprintf(stderr, "sd_epoll_run(&mgr) failed ret:%d\n", ret);
    return -1;
  }
  sd_epoll_destory(&mgr);

  close(connfd);
  return 0;
}
