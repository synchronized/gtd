
#ifndef __SD_THREAD_POOL_H
#define __SD_THREAD_POOL_H

#include <pthread.h>

struct sd_thread_pool; //线程池
struct sd_thread_worker; //线程
struct sd_thread_job; //任务

struct sd_thread_worker {
  pthread_t pid;
  int terminate; //结束标记
  struct sd_thread_pool *pool;
  struct sd_thread_worker *prev, *next;
};

struct sd_thread_job {
  void* ud; //用户数据
  void* (*func)(void *args); //任务逻辑函数
  struct sd_thread_job *prev, *next;
};

struct sd_thread_pool {
  struct sd_thread_worker *workers; //线程列表
  struct sd_thread_job *jobs; //任务列表
  pthread_cond_t emptycond;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
};

//将item插入到list中
//需要item和list都是类似下面类型的指针
//struct XXX{
//    struct XXX *prev, *next;
//}
#define SD_LIST_ADD(item, list) do{             \
    item->prev = NULL;                          \
    item->next = list;                          \
    if (list != NULL) list->prev = item;        \
    list = item;                                \
  } while(0)

#define SD_LIST_DEL(item, list) do{                 \
    if (item->prev) item->prev->next = item->next;  \
    if (item->next) item->next->prev = item->prev;  \
    if (item == list) list = list->next;            \
  } while(0)

//初始化线程池,0:成功，其他失败
int sd_thread_pool_init(struct sd_thread_pool *pool, int nworkers);
//销毁线程池
int sd_thread_pool_destroy(struct sd_thread_pool *pool);
//添加任务
int sd_thread_pool_pushjob(struct sd_thread_pool *pool, struct sd_thread_job *job);
//等待所有任务执行完
int sd_thread_pool_waitempty(struct sd_thread_pool *pool);

#endif //__SD_THREAD_POOL_H
