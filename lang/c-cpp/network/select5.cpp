#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <list>

#define BUFSIZE 1024

struct sockfd_opt;
struct sockfd_mgr;

typedef int (sockfd_opt_task_t)(struct sockfd_mgr *mgr, struct sockfd_opt *p_so);

//处理买个socket描述符的结构体
struct sockfd_opt {
  int fd; //描述符
  sockfd_opt_task_t *do_task;
};

struct sockfd_mgr {
  int maxfd; //文件描述符最大值
  int listenfd; //监听文件描述符
  fd_set rfds, orfds; //文件描述符集合
  std::list<struct sockfd_opt*> list; //链表
  struct sockfd_opt listen_opt; //监听用的
};

void sockfd_mgr_addfd(struct sockfd_mgr *mgr, struct sockfd_opt *p_so) {
  mgr->list.push_back(p_so); //将此套接字加入队列
  FD_SET(p_so->fd, &mgr->orfds);
  if (p_so->fd > mgr->maxfd) {
    mgr->maxfd = p_so->fd;
  }
}

void sockfd_mgr_delfd(struct sockfd_mgr *mgr, struct sockfd_opt *p_so) {
  close(p_so->fd); //关闭当前套接字描述符
  mgr->list.remove(p_so); //从链表中删除当前选项
  //注意:这里必须从orfds集合中删除此关闭的文件描述符，方便下次select
  FD_CLR(p_so->fd, &mgr->orfds);
  if (&mgr->listen_opt != p_so) {
    free(p_so);
  }
}

static void bail(const char *on_what) {
  fputs(strerror(errno), stderr);
  fputs(": ", stderr);
  fputs(on_what, stderr);
  fputs("\n", stderr);
  exit(1);
}

//向客户端发送日期
int send_reply(struct sockfd_mgr *mgr, struct sockfd_opt *p_so) {
  char rbuf[BUFSIZE]; //接收缓存
  char dtbuf[BUFSIZE]; //日期-时间结果字符串
  time_t td; //当前时间和日期
  struct tm tm;
  int z = read(p_so->fd, rbuf, sizeof(rbuf));
  if (z < 0) {
    sockfd_mgr_delfd(mgr, p_so);
    //若读操作返回-1且不是RST分段
    if (errno != ECONNRESET) {
      bail("read()");
    }
    return -1;
  } else if (z == 0) {
    printf("client close\n");
    sockfd_mgr_delfd(mgr, p_so);
    return 1;
  }

  rbuf[z] = '\0';
  printf("recv from client '%s'\n", rbuf);
  time(&td);
  localtime_r(&td, &tm);
  strftime(dtbuf, sizeof(dtbuf), rbuf, &tm);
  dtbuf[sizeof(dtbuf)-1] = '\0';
  //想客户端发回结果
  z = write(p_so->fd, dtbuf, strlen(dtbuf));
  if (z < 0) {
    bail("write()");
  }
  return 0;
}

//接受TCP链接
int create_conn(struct sockfd_mgr *mgr, struct sockfd_opt *p_so) {
  int conn_fd;
  char ipbuf[16];
  struct sockaddr_in client; //客户端ip地址
  socklen_t addrlen;
  addrlen = sizeof(client);
  if ((conn_fd = accept(p_so->fd, (struct sockaddr*)&client, &addrlen)) == -1) {
    bail("accept()");
    return 0;
  }
  fprintf(stdout, "server got connection from %s:%d\n",
          inet_ntop(AF_INET, &client.sin_addr, ipbuf, sizeof(ipbuf)), ntohs(client.sin_port));
  //若连接c熬过了最大值
  if (mgr->list.size()+1 == FD_SETSIZE) {
    fprintf(stderr, "too many clients!\n");
    exit(-1);
  }
  if ((p_so=(struct sockfd_opt*)malloc(sizeof(struct sockfd_opt))) == NULL) {
    bail("malloc()");
    return 0;
  }
  p_so->fd = conn_fd;
  p_so->do_task = send_reply; //设置当前套接字选项的
  //将此已连接套接字加入到orfds集合中
  sockfd_mgr_addfd(mgr, p_so);
  return 0;
}

//初始化坚挺套接字选线
int init(struct sockfd_mgr *mgr) {
  struct sockfd_opt *p_so = &mgr->listen_opt;
  //设置监听套接字选项的回调函数
  p_so->do_task = create_conn;
  p_so->fd = mgr->listenfd;
  //将监听套接字选项加入到链表尾
  //晴空orfds
  FD_ZERO(&mgr->orfds);
  //将监听套接字加入d奥orfds集合
  sockfd_mgr_addfd(mgr, p_so);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "select5 <port>\n");
    return -1;
  }

  struct sockfd_mgr mgr;

  int port, opt;
  struct sockaddr_in server;
  socklen_t optlen;

  port = atoi(argv[1]);
  if (port <= 0 || port > 65000) {
    fprintf(stderr, "invalid port\n");
    return -1;
  }

  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  //创建套接字
  if ((mgr.listenfd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    bail("socket()");
    return -1;
  }

  //设置套接字选项
  optlen = sizeof(opt);
  if (setsockopt(mgr.listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, optlen) == -1) {
    bail("socket()");
    return -1;
  }

  //帮顶地址
  if (bind(mgr.listenfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
    bail("bind()");
    return -1;
  }

  //开始监听
  if (listen(mgr.listenfd, 5) == -1) {
    bail("listen()");
    return -1;
  }

  if (init(&mgr) == -1) {
    bail("init()");
    return -1;
  }

  printf("server is waiting for acceptance of new client \n");
  struct sockfd_opt *p_so;

  for (;;) {
    //回复rfds为最初设置的orfds,准备下次select调用
    mgr.rfds = mgr.orfds;
    //执行select
    int n = select(mgr.maxfd+1, &mgr.rfds, NULL, NULL, NULL);
    //在返回的n个可读的文件描述符中进行迭代
    for (int i=0; i<n; i++) {
      std::list<struct sockfd_opt*>::iterator it = mgr.list.begin();
      while(it != mgr.list.end()) {
        p_so = *it;
        //检查此套接字文件描述符是否可读
        if (FD_ISSET(p_so->fd, &mgr.rfds)) {
          p_so->do_task(&mgr, p_so);
          break;
        }
        it++;
      }
    }
  }

  std::list<struct sockfd_opt*>::iterator it = mgr.list.begin();
  while (it != mgr.list.end()) {
    sockfd_mgr_delfd(&mgr, *it);
  }
  return 0;
}
