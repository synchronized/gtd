#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
#define backlog 128 //等待队列大小

static void bail(const char *on_what) {
  fputs(strerror(errno), stderr);
  fputs(": ", stderr);
  fputs(on_what, stderr);
  fputs("\n", stderr);
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "client <hostname> <port>");
    return -1;
  }

  int sockfd;
  int port;
  int ret, maxfd = -1;
  long z;
  char rbuf[BUFSIZE];
  char wbuf[BUFSIZE];
  char hostqbuf[8192];
  char ipbuf[16];
  struct sockaddr_in server;
  struct hostent host, *phost;
  fd_set rfds, orfds;

  FD_ZERO(&orfds);

  bzero(&server, sizeof(server));
  if (gethostbyname_r(argv[1], &host, hostqbuf, sizeof(hostqbuf), &phost, &ret)) {
    bail("gethostbyname()");
    return -1;
  }

  if ((port = atoi(argv[2])) < 0) {
    fprintf(stderr, "get port error");
    return -1;
  }

  //创建客户端套接字文件描述符
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    bail("socket()");
    return -1;
  }

  //服务器地址
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr = *((struct in_addr*)phost->h_addr);

  //连接到服务器
  if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
    bail("socket()");
    return -1;
  }

  FD_SET(STDIN_FILENO, &orfds);
  FD_SET(sockfd, &orfds);
  maxfd = STDIN_FILENO;
  if (maxfd < sockfd) {
    maxfd = sockfd;
  }

  printf("connected to server: %s:%d\n", inet_ntop(AF_INET, &server.sin_addr, ipbuf, sizeof(ipbuf)), port);

  for (;;) {
    rfds = orfds; //重新恢复用于检测的可读描述符集合
    printf("\nEnter format string(^D or 'quit' to exit):");
    fflush(stdout);

    //调用select开始等待可读文件描述符集合
    ret = select(maxfd+1, &rfds, NULL, NULL, NULL);
    if (ret == -1) {
      perror("select");
      break;
    }

    //检测套接字描述符
    if (FD_ISSET(sockfd, &rfds)) {
      //读取服务器应答
      z = read(sockfd, rbuf, sizeof(rbuf));
      if (z == -1) {
        bail("read()");
        return -1;
      }
      else if (z == 0) {
        printf("close socket from server\n");
        break;
      }
      rbuf[sizeof(rbuf)-1] = '\0';
      printf("\n");
      printf("result from %s:%u\n\t '%s'\n", inet_ntop(AF_INET, &server.sin_addr, ipbuf, sizeof(ipbuf)), port, rbuf);
    }
    if (FD_ISSET(STDIN_FILENO, &rfds)) {
      if (!fgets(wbuf, sizeof(wbuf), stdin)) {
        //用户按ctrl+D组合键结束输入,eof
        printf("\n");
        break;
      }
      wbuf[sizeof(wbuf)-1] = '\n';
      z = strlen(wbuf);
      if (z > 0 && wbuf[z-1] == '\n') {
        wbuf[z-1] = '\n';
        z--;
      }
      if (z==0) {
        continue;
      }
      //用户输入quit退出
      if (strncasecmp(wbuf, "quit", 4) == 0) {
        printf("exit\n");
        break;
      }
      //将格式发送到服务器
      z = write(sockfd, wbuf, z);
      if (z < 0) {
        bail("write()");
      }
    }
  }
  return 0;
}
