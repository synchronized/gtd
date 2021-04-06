#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "sd_thread_pool.h"

static void* sd_thread_func(void *args) {
  struct sd_thread_worker *worker = (struct sd_thread_worker*)args;
  struct sd_thread_pool *pool = worker->pool;
  while(1) {
    pthread_mutex_lock(&pool->mutex);
    while(!pool->jobs) {
      if (worker->terminate) break;
      pthread_cond_signal(&pool->emptycond);
      pthread_cond_wait(&pool->cond, &pool->mutex);
    }
    if (worker->terminate) {
      pthread_mutex_unlock(&pool->mutex);
      break;
    }
    struct sd_thread_job *job = pool->jobs;
    SD_LIST_DEL(job, pool->jobs);
    pthread_mutex_unlock(&pool->mutex);

    job->func(job->ud);
  }
  pthread_exit(NULL);
  return NULL;
}

//初始化线程池,0:成功，其他失败
int sd_thread_pool_init(struct sd_thread_pool *pool, int nworkers) {
  if (pool == NULL) return -1;
  if (nworkers < 1) nworkers = 1;

  int i;
  memset(pool, 0, sizeof(*pool));
  pool->jobs = NULL;
  pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
  memcpy(&pool->cond, &cond, sizeof(cond));
  memcpy(&pool->emptycond, &cond, sizeof(cond));
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  memcpy(&pool->mutex, &mutex, sizeof(mutex));

  for (i=0; i<nworkers; i++) {
    struct sd_thread_worker *worker = (struct sd_thread_worker*)malloc(sizeof(*worker));
    if (worker == NULL) {
      perror("malloc(struct sd_thread_worker)");
      return -2;
    }
    worker->pool = pool;
    SD_LIST_ADD(worker, pool->workers);
    if (pthread_create(&worker->pid, NULL, sd_thread_func, worker) != 0) {
      perror("pthread_create");
      free(worker);
      return -3;
    }
  }
  return 0;
}

//销毁线程池
int sd_thread_pool_destroy(struct sd_thread_pool *pool) {
  if (pool == NULL) return -1;

  struct sd_thread_worker *worker;
  struct sd_thread_worker *tmp;

  pthread_mutex_lock(&pool->mutex);
  worker = pool->workers;
  while(worker) {
    worker->terminate = 1;
  }
  pthread_cond_broadcast(&pool->cond);
  pthread_mutex_unlock(&pool->mutex);

  worker = pool->workers;
  while(worker) {
    pthread_join(worker->pid, NULL);
    worker = worker->next;
  }

  worker = pool->workers;
  while(worker) {
    tmp = worker;
    worker = worker->next;
    free(tmp);
  }
  pool->workers = NULL;
  pthread_cond_destroy(&pool->cond);
  pthread_cond_destroy(&pool->emptycond);
  pthread_mutex_destroy(&pool->mutex);

  return 0;
}

//添加任务
int sd_thread_pool_pushjob(struct sd_thread_pool *pool, struct sd_thread_job *job) {
  if (pool == NULL) return -1;
  if (job == NULL) return -2;

  pthread_mutex_lock(&pool->mutex);
  SD_LIST_ADD(job, pool->jobs);
  pthread_cond_signal(&pool->cond);
  pthread_mutex_unlock(&pool->mutex);
  return 0;
}

int sd_thread_pool_waitempty(struct sd_thread_pool *pool) {
  if (pool == NULL) return -1;
  pthread_mutex_lock(&pool->mutex);
  while(pool->jobs) {
    pthread_cond_wait(&pool->emptycond, &pool->mutex);
  }
  pthread_mutex_unlock(&pool->mutex);
  return 0;
}
