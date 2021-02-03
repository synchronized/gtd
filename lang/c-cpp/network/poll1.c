#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFSIZE 1024
#define PFDSIZE 2

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "poll1 <port>\n");
    return -1;
  }
  int port, ret;
  int udpfd;
  char buf[BUFSIZE];
  char ipbuf[16];
  struct pollfd fds[2];
  struct sockaddr_in saddr, caddr;

  port = atoi(argv[1]);
  if (port <= 0 || port > 65535) {
    fprintf(stderr, "invalid port\n");
    return -1;
  }

  bzero(&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  //if (inet_pton(AF_INET, argv[2], &saddr.sin_addr) <= 0) {
  //  fprintf(stderr, "invalid ipaddr");
  //  return -1;
  //}

  bzero(&caddr, sizeof(caddr));
  caddr.sin_family = AF_INET;
  caddr.sin_port = htons(port);

  udpfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (udpfd == -1) {
    perror("listen error");
    return -1;
  }

  if (bind(udpfd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
    perror("bind error");
    return -1;
  }

  printf("input: \"sayto 192.168.220.X\" to sendmsg to somebody\033[32m\n");
  fds[0].fd = STDIN_FILENO;
  fds[0].events = POLLIN;
  fds[1].fd = udpfd;
  fds[1].events = POLLIN;

  for (;;) {
    write(STDOUT_FILENO, "UdpQQ: ", 7);
    int ret = poll(fds, 2, -1);

    if (ret < 0) {
      perror("poll error");
      continue;
    }
    else if (ret == 0) {
      printf("time out\n");
      continue;
    }

    if ((fds[0].events & POLLIN) == POLLIN) {
      if (!fgets(buf, sizeof(buf), stdin)) {
        perror("fgets error");
        continue;
      }
      buf[sizeof(buf)-1] = '\0';
      int slen = strlen(buf);
      if (slen > 0) {
        if (buf[slen-1] == '\n') {
          buf[slen-1] = '\0';
          slen--;
        }
      }
      if (strncmp(buf, "sayto:", 6) == 0) {
        int ipr = inet_pton(AF_INET, buf+6, &caddr.sin_addr);
        if (ipr < 0) {
          perror("inet_pton error");
        } else if (ipr == 0) {
          printf("inet_pton error: %s\n", buf+6);
        } else {
          printf("\rsay to %s\n", inet_ntop(AF_INET, &caddr.sin_addr, ipbuf, sizeof(ipbuf)));
        }
        continue;
      }
      else if (strncasecmp(buf, "quit", 4) == 0) {
        printf("exit\n");
        exit(0);
      }
      sendto(udpfd, buf, slen, 0, (struct sockaddr*)&caddr, sizeof(caddr));
    }
    if ((fds[1].events & POLLIN == POLLIN)) {
      struct sockaddr_in addr;
      bzero(&addr, sizeof(addr));
      socklen_t addrlen = sizeof(addr);

      if (recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addrlen) == -1) {
        perror("recvfrom error");
        continue;
      }
      buf[sizeof(buf)-1] = '\0';
      printf("\r\033[32m%s: \033[32m%s\n", inet_ntop(AF_INET, &addr.sin_addr, ipbuf, sizeof(ipbuf)), buf);
    }
  }

  return 0;
}
