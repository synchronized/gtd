#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define maxs 512
#define RECV_SERVER_MSG "recv server data: "

void do_task(int sockfd) {
  int nread;
  char buf[maxs] = "";
  fd_set rset, allset;
  FD_ZERO(&allset);
  FD_SET(STDIN_FILENO, &allset);
  FD_SET(sockfd, &allset);
  int maxfd = STDIN_FILENO > sockfd ? STDIN_FILENO : sockfd;

  while(1) {
    rset = allset;
    //阻塞式调用
    if (select(maxfd+1, &rset, NULL, NULL, NULL) == -1) {
      perror("select error");
      continue;
    }

    if (FD_ISSET(sockfd, &rset)) {
      nread = read(sockfd, buf, sizeof(buf));
      if (nread < 0) {
        perror("read error");
        break;
      }
      else if (nread == 0) {
        printf("server close the connection\n");
        break;
      }
      buf[nread-1] = '\0';
      write(STDOUT_FILENO, RECV_SERVER_MSG, sizeof(RECV_SERVER_MSG));
      write(STDOUT_FILENO, buf, nread);
      write(STDOUT_FILENO, "\n", 1);
    }

    if (FD_ISSET(STDIN_FILENO, &rset)) {
      fgets(buf, sizeof(buf), stdin);
      buf[sizeof(buf)-1] = '\0';
      if (strlen(buf) == 0) {
        continue;
      }
      if (strncasecmp(buf, "quit", 4) == 0) {
        printf("client exit...\n");
        break;
      }
      write(sockfd, buf, strlen(buf)); //发送输入数据
      printf("send to server ok\n");
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "client <ip> <port>");
    return -1;
  }
  int sockfd;
  struct sockaddr_in server;
  bzero(&server, sizeof(server));
  //设置服务器信息
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  inet_aton(argv[1], &server.sin_addr);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("socket error");
    return -1;
  }

  if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("connect error");
    close(sockfd);
    return -1;
  }

  do_task(sockfd);
  close(sockfd);
  return 0;
}
