#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define maxs 1024

void do_task(int *clientfd, int maxsfd, fd_set *rset, fd_set *allset) {
  int nread;
  char buf[maxs];
  for (int i=0; i<maxsfd; i++) {
    if (clientfd[i] == -1) {
      continue;
    }
    //某个客户端发送请求
    if (FD_ISSET(clientfd[i], rset)) {
      nread = read(clientfd[i], buf, sizeof(buf));
      if (nread < 0) {
        perror("read error");
        close(clientfd[i]);
        FD_CLR(clientfd[i], allset); //清除该套接字
        clientfd[i] = -1;
        continue;
      }
      else if (nread == 0) {
        printf("client close the connection\n");
        close(clientfd[i]);
        FD_CLR(clientfd[i], allset);
        clientfd[i] = -1;
        continue;
      }
      buf[sizeof(buf)-1] = '\0'; //保证不会越界
      printf("recv and send to '%s' client ok\n", buf);
      write(clientfd[i], buf, nread);
    }
  }
}

int main(int argc, char *argv[]) {
  char quit[512], ipbuf[16];
  int port, listenfd, maxfd, clientfd[FD_SETSIZE], nread, connfd;
  struct sockaddr_in server, client;
  fd_set allset, rset;

  if (argc < 3) {
    fprintf(stderr, "server <ip> <port>");
    return -1;
  }

  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  inet_aton(argv[1], &server.sin_addr);

  bzero(&client, sizeof(client));
  client.sin_family = AF_INET;
  client.sin_port = htons(0); //TODO

  listenfd = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
  if (listenfd < 0) {
    perror("socket error");
    return -1;
  }
  int opt = 1;
  //设置套接字地址可重用
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt error");
  }

  if (bind(listenfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("bind error");
    close(listenfd);
    return -1;
  }

  if (listen(listenfd, 100) < 0) {
    perror("listen error");
    close(listenfd);
    return -1;
  }
  for (int i=0; i<FD_SETSIZE; i++) {
    clientfd[i] = -1;
  }

  FD_ZERO(&allset); //初始化文件描述符
  FD_SET(listenfd, &allset); //添加坚挺文件描述符到集合中
  FD_SET(STDIN_FILENO, &allset); //添加标准输入到描述符集合
  maxfd=listenfd;
  if (maxfd<listenfd) {
    maxfd=listenfd;
  }

  printf("echo server use select startup, listen on port %d\n", atoi(argv[2]));
  printf("max connection: %d\n", FD_SETSIZE);
  socklen_t socklen = sizeof(server);

  while(1) {
    rset = allset;
    nread = select(maxfd+1, &rset, NULL, NULL, NULL); //阻塞式等待
    if (nread < 0) {
      perror("select error");
      continue;
    }

    //监听套接字可度，表示有新的链接
    if (FD_ISSET(listenfd, &rset)) {
      connfd = accept(listenfd, (struct sockaddr*)&client, &socklen);
      if (connfd < 0) {
        perror("accept error");
        continue;
      }
      printf("accept from %s:%d\n",
             inet_ntop(AF_INET, &client.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(client.sin_port));
      for (int i=0; i<FD_SETSIZE; i++) {
        if (clientfd[i] == -1) {
          clientfd[i] = connfd; //添加套接字到数组中
          break;
        }
      }
      if (connfd > maxfd) {
        maxfd = connfd;
      }

      FD_SET(connfd, &allset); //添加链接套接字到文件描述符集合中
      if (nread <= 1) { //如果只返回一个可读，不用继续往下执行
        continue;
      }
    }

    if (FD_ISSET(STDIN_FILENO, &rset)) {
      scanf("%s", quit);
      quit[sizeof(quit)-1] = '\0';
      if (strncasecmp(quit, "quit", 4) == 0) {
        break;
      }
    }

    do_task(clientfd, maxfd, &rset, &allset);
  }

  //关闭链接
  close(listenfd);
  for (int i=0; i<FD_SETSIZE; i++) {
    if (clientfd[i] > 0) {
      close(clientfd[i]);
    }
  }

  return 0;
}
