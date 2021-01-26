#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/**

//轮询扫描多个描述符中的任一描述符是否发生响应，或经过一段时间后唤醒
//@param maxfd 指定要检测的描述符的范围 所检测描述符最大值+1
//@paarm readset 可读描述符集
//@param writeset 可写描述符集
//@param exceptset 异常描述符集
//@param timeout 超时时间
//@return 0：超时, -1：出错, >0：准备好的文件描述符数量
int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);

//该结构体表示等待超时的时间
struct timeval{
  long tv_sec;//秒
  long tv_usec;//微秒
};

//比如等待10.2秒
struct timeval timeout;
timeoout.tv_sec = 10;
timeoout.tv_usec = 200000;

//将select函数的timeout参数设置为NULL则永远等待

描述符集操作
void FD_ZERO(fd_set *fdset); //初始化描述符集
void FD_SET(int fd, fd_set *fdset); //将一个描述符添加到描述符集
void FD_CLR(int fd, fd_set *fdset); //将一个描述符从描述符集中删除
int FD_ISSET(int fd, fd_set *fdset); //检测指定的描述符是否有事件发生

//读取udp消息
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

//创建套接字
int socket(int domain, int type, int protocol);

//帮顶套接字到某个地址
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

//创建一个线程
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

//将一个字符串转换为网络地址,返回一个标记
int inet_pton(int af, const char *src, void *dst);

//将一个网络地址转换为字符串格式返回
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
*/

void *thread_recv(void *arg) {
  int udpfd = (int)(intptr_t)arg;
  struct sockaddr_in addr;
  socklen_t addrlen = sizeof(addr);

  bzero(&addr, sizeof(addr));
  while(1) {
    char buf[256] = "";
    char ipbuf[16] = "";
    recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addrlen);
    printf("\r\033[31m[%s]: \033[32m%s\n", inet_ntop(AF_INET, &addr.sin_addr, ipbuf, sizeof(ipbuf)), buf);
    write(1, "UdpQQ: ", 7);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  char buf[100] = "";
  int udpfd = 0;
  pthread_t tid;
  struct sockaddr_in addr;
  struct sockaddr_in cliaddr;

  //对套接字地址进行初始化
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  bzero(&cliaddr, sizeof(cliaddr));
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(8000);

  //创建套接口
  if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket error");
    exit(-1);
  }

  //设置端口
  if (bind(udpfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind error");
    close(udpfd);
    exit(-1);
  }

  printf("input: \"sayto 192.168.221.X\" to sendmsg to somebody\n");
  //创建接收线程
  pthread_create(&tid, NULL, thread_recv, (void*)(intptr_t)udpfd); //创建线程
  printf("\033[32m"); //设置自体颜色
  fflush(stdout);

  while(1) {
    //主线程负责f阿送消息
    fprintf(stdout, "UdpQQ: "); //表示标准输出
    fgets(buf, sizeof(buf), stdin); //等待输入
    buf[strlen(buf) -1] = '\0'; //确保输入的最后一位是0
    if (strncmp(buf, "sayto:", 6) == 0) {
      char ipbuf[INET_ADDRSTRLEN] = "";
      //给addr套接字地址再赋值
      int s;
      if ((s = inet_pton(AF_INET, buf+6, &cliaddr.sin_addr)) <= 0) {
        if (s == 0)
          fprintf(stderr, "Not in presentation format\n");
        else
          perror("inet_pton");
        continue;
      }
      printf("\rconnect %s successful!\n", inet_ntop(AF_INET, &cliaddr.sin_addr, ipbuf, sizeof(ipbuf)));
      continue;
    }
    else if (strncmp(buf, "exit", 4) == 0) {
      close(udpfd);
      exit(0);
    }

    sendto(udpfd, buf, strlen(buf), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
  }
  return 0;
}
