#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <poll.h>

#define MAXLINE 10240
#ifndef OPEN_MAX
#define OPEN_MAX 40960
#endif //OPEN_MAX

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "poll2 <port>");
    return 1;
  }
  int i, maxi, listenfd, connfd, sockfd;
  int nready, nread;
  short port;
  ssize_t n;
  char buf[MAXLINE], ipbuf[16];
  socklen_t clilen;
  struct pollfd client[OPEN_MAX];
  struct sockaddr_in cliaddr, servaddr;

  port = atoi(argv[1]);

  listenfd = socket(AF_INET, SOCK_STREAM, 0); //监听ff
  if (listenfd < 0) {
    perror("socket");
    return -1;
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    perror("bind");
    return -2;
  }

  if (listen(listenfd, 1024) < 0) {
    perror("listen");
    return -3;
  }

  client[0].fd = listenfd;
  client[0].events = POLLIN;

  //初始化client列表
  for (i=1; i<OPEN_MAX; i++) {
    client[i].fd = -1;
  }

  maxi = 0;

  for (;;) {
    nready = poll(client, maxi+1, -1);
    if (nready < 0) {
      perror("poll");
      return 1;
    }
    if (nready == 0) {
      continue;
    }

    if (client[0].revents & POLLIN) {
      clilen = sizeof(cliaddr);
      //bzero(&cliaddr, sizeof(cliaddr));
      connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
      if (connfd < 0) {
        int eno = errno;
        if (eno != EAGAIN && eno != EWOULDBLOCK) {
          perror("accept");
        }
      } else {
        printf("new client %s:%d\n", inet_ntop(AF_INET, &cliaddr, ipbuf, sizeof(ipbuf)), ntohs(cliaddr.sin_port));
        for (i=1; i<OPEN_MAX; i++) {
          if (client[i].fd == -1) {
            break;
          }
        }
        if (i == OPEN_MAX) {
          fprintf(stderr, "too many connections\n");
        } else {
          client[i].fd = connfd;
          client[i].events = POLLIN;

          if (maxi < i) {
            maxi = i;
          }

          printf("i:%d, connfd:%d, maxi:%d\n", i, connfd, maxi);
        }
      }
    }

    for (i=1; i<=maxi; i++) {
      if (client[i].fd == -1) {
        continue;
      }
      if (client[i].revents & POLLIN) {
        connfd = client[i].fd;
        nread = read(connfd, buf, sizeof(buf)-1);
        if (nread < 0) {
          int eno = errno;
          if (eno != EAGAIN && eno != EWOULDBLOCK) {
            perror("read");
            client[i].fd = -1;
            close(connfd);
          }
          continue;
        }
        if (nread == 0) {
          printf("client close fd:%d\n", connfd);
          client[i].fd = -1;
          close(connfd);
          continue;
        }
        buf[nread] = '\0';
        int j = nread-1;
        for (; j>0; j--) {
          if (buf[j] == '\n' || buf[j] == '\r') {
            buf[j] = '\0';
            nread--;
            continue;
          }
          break;
        }
        printf("recv fd: %d msg: %s\n", connfd, buf);
      }
    }

  }

  return 0;
}
