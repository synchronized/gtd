
#ifndef __SD_EPOLL_H
#define __SD_EPOLL_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/epoll.h>

#define MAXEPOLLSIZE 10000

struct epoll_event;
struct sd_epoll_opt;
struct sd_epoll_mgr;

typedef int (*sd_epoll_handle)(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so);

typedef union sd_epoll_data {
  void *prt;
  int fd;
  uint32_t u32;
  uint64_t u64;
} sd_epoll_data_t;

struct sd_epoll_opt {
  int fd; //描述符
  sd_epoll_data_t data; //用户自己的数据
  sd_epoll_handle handle; //处理函数
  struct sd_epoll_opt *next; //下个元素
};

struct sd_epoll_mgr {
  int curfds; //当前有多少个文件描述符
  int runing; //是否正在运行
  int efd; //epoll文件描述符
  void *ctx; //用户上下文数据(全局唯一)
  struct epoll_event ev;
  struct epoll_event events[MAXEPOLLSIZE];
  struct sd_epoll_opt head;
  struct sd_epoll_opt *tail;
};

int sd_epoll_init(struct sd_epoll_mgr *mgr, void *args); //初始化sd_epoll_mgr
int sd_epoll_opt_create(struct sd_epoll_opt **pp_opt); //申请内存
int sd_epoll_opt_add(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so); //添加
int sd_epoll_opt_destory(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so); //从mgr中删除p_so,并且销毁p_so使用的内存
int sd_epoll_del_from_mgr(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *p_so); //从mgr中删除p_so
int sd_epoll_run(struct sd_epoll_mgr *mgr); //开始运行
int sd_epoll_stop(struct sd_epoll_mgr *mgr); //停止事件循环
int sd_epoll_destory(struct sd_epoll_mgr *mgr); //销毁mgr

#endif
