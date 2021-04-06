
#ifndef __SD_EPOLL_H
#define __SD_EPOLL_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/epoll.h>

#define MAXEPOLLSIZE 10000
#define SD_EPOLL_IN (1)
#define SD_EPOLL_OUT (1<<1)

struct epoll_event;
struct sd_epoll_opt;
struct sd_epoll_mgr;

//typedef union sd_epoll_data {
//  void *prt;
//  int fd;
//  uint32_t u32;
//  uint64_t u64;
//} sd_epoll_data_t;

typedef void (*sd_epoll_handle)(void *ctx, void *ud);

struct sd_epoll_opt {
  int fd; //描述符
  //sd_epoll_data_t ud; //用户自己的数据
  void *ud; //用户数据(在触发事件的时候会通知到handle_xxxx)
  sd_epoll_handle handle_read; //处理函数-读取
  sd_epoll_handle handle_write; //处理函数-写入
  sd_epoll_handle handle_error; //处理函数-错误
  int flags; //监听的事件
  struct sd_epoll_opt *next; //下个元素
};

struct sd_epoll_mgr {
  int curfds; //当前有多少个文件描述符
  int terminate; //是否已经停止
  int efd; //epoll文件描述符
  void *ctx; //用户上下文数据(全局唯一)
  struct epoll_event events[MAXEPOLLSIZE];
  struct sd_epoll_opt head;
  struct sd_epoll_opt *tail;
};

int sd_epoll_init(struct sd_epoll_mgr *mgr, void *args); //初始化sd_epoll_mgr
int sd_epoll_opt_add(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *opt); //添加
int sd_epoll_opt_mod(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *opt); //修改
int sd_epoll_opt_del(struct sd_epoll_mgr *mgr, struct sd_epoll_opt *opt); //从mgr中删除opt
int sd_epoll_run(struct sd_epoll_mgr *mgr); //开始运行
int sd_epoll_stop(struct sd_epoll_mgr *mgr); //停止事件循环
int sd_epoll_destory(struct sd_epoll_mgr *mgr); //销毁mgr

#endif
