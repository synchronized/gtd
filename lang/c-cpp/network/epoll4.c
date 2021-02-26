#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 10
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 8006
#define INFTIM 1000
#define EPOLL_MAX 256
#define EPOLL_ENUM 32

struct task;

//线程池-任务
struct task {
  int fd; //需要读写的文件描述符
  struct task *next; //下一个任务
};

//用于读写的两个方面传递的参数
struct user_data {
  int fd;
  unsigned int n_size;
  char line[MAXLINE];
};

//线程的任务函数
void* readtask(void *args);

//生命event结构体变量,ev用于时间注册,数组用于回传要处理的事件

struct epoll_event ev, events[EPOLL_ENUM];
int epfd;
pthread_mutex_t mutex;
pthread_cond_t cond1;
struct task *readhead = NULL, *readtail = NULL, *writehead = NULL;

void setnonblocking(int fd) {
  int opts = fcntl(fd, F_GETFL);
  if (opts<0) {
    perror("fcntl(fd, F_GETFL)");
    return;
  }
  opts |= O_NONBLOCK;
  if (fcntl(fd, F_SETFL, opts)<0) {
    perror("fcntl(fd, F_SETTL, opts)");
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "epoll4 <port>\n");
    return 1;
  }
  int i, maxi, listenfd, connfd, sockfd, nfds, port;
  pthread_t tid1, tid2;

  struct task *new_task = NULL;
  struct user_data *rdata = NULL;
  struct sockaddr_in clientaddr;
  struct sockaddr_in serveraddr;
  socklen_t addrlen = sizeof(clientaddr);

  port = atoi(argv[1]);
  if (port < 0) {
    fprintf(stderr, "epoll4 <port>\n");
    return 1;
  }

  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port);
  serveraddr.sin_addr.s_addr = INADDR_ANY;

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond1, NULL);
  //初始化用于读线程池的线程

  if (pthread_create(&tid1, NULL, readtask, NULL) != 0) {
    perror("pthread_create");
    return 2;
  }
  if (pthread_create(&tid2, NULL, readtask, NULL) != 0) {
    perror("pthread_create");
    return 2;
  }

  //生成用于处理accept的epoll专用的文件描述符
  epfd = epoll_create(EPOLL_MAX);
  if (epfd == -1) {
    perror("epoll_create");
    return 3;
  }

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1) {
    perror("socket");
    return 3;
  }
  //把socket设置为非阻塞方式
  setnonblocking(listenfd);
  //设置与要处理的时间n香瓜的文件描述符
  ev.data.fd = listenfd;
  ev.events = EPOLLIN|EPOLLET;
  //注册epoll事件
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
    perror("epoll_ctl");
    return 4;
  }

  if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1) {
    perror("bind");
    return 5;
  }

  if (listen(listenfd, LISTENQ) == -1) {
    perror("listen");
    return 6;
  }

  maxi = 0;
  for (;;) {
    //等待epoll时间的发生
    nfds = epoll_wait(epfd, events, 20, EPOLL_ENUM);
    //处理所发生的所有事件
    if (nfds<0) {
      perror("epoll_wait");
      break;
    }
    if (nfds==0) {
      continue;
    }
    for (int i=0; i<nfds; i++){
      struct epoll_event ev2 = events[i];
      if (ev2.data.fd == listenfd) {
        connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &addrlen);
        if (connfd < 0) {
          perror("accept");
          continue;
        }
        ev.data.fd = connfd;
        ev.events = EPOLLIN | EPOLLET;
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev) < 0) {
          perror("epoll_ctl");
          close(connfd);
          continue;
        }
      } else if (ev2.events | EPOLLIN) {
        if ((sockfd = ev2.data.fd) < 0) continue;
        new_task = (struct task*)malloc(sizeof(*new_task));
        new_task->fd = sockfd;
        new_task->next = NULL;

        pthread_mutex_lock(&mutex);
        if (readhead == NULL) {
          readhead = readtail = new_task;
        } else {
          readtail->next = new_task;
          readtail = new_task;
        }

        //唤醒所有等待的线程
        pthread_cond_broadcast(&cond1);
        pthread_mutex_unlock(&mutex);
      } else if (ev2.events | EPOLLOUT) {
        rdata = (struct user_data*)ev2.data.ptr;
        sockfd = rdata->fd;
        write(sockfd, rdata->line, rdata->n_size);
        free(rdata);
        //设置用于读操作的文件描述符
        ev.data.fd = sockfd;
        ev.events = EPOLLIN|EPOLLET;

      }
    }
  }
  return 0;
}

void* readtask(void *args) {
  
}
