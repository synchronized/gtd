#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sd_thread_pool.h"


#define TASK_NUM 1000

struct sd_thread_test_manager {
  int count;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
};

int test_manager_init(struct sd_thread_test_manager *manager) {
  if (manager == NULL) return -1;

  memset(manager, 0, sizeof(*manager));
  manager->count = 0;
  pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
  memcpy(&manager->cond, &cond, sizeof(cond));
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  memcpy(&manager->mutex, &mutex, sizeof(mutex));
}

int test_manager_increment(struct sd_thread_test_manager *manager) {
  pthread_mutex_lock(&manager->mutex);
  manager->count++;
  pthread_mutex_unlock(&manager->mutex);
}

void* func_mutex_increment(void *args) {
  struct sd_thread_test_manager *manager = (struct sd_thread_test_manager*)args;
  test_manager_increment(manager);
  return NULL;
}

void* func_calc(void *args) {
  struct sd_thread_job *job = (struct sd_thread_job*)args;
  printf("+1\n");
  free(job);
  return NULL;
}

int main(int argc, char *argv[]) {
  int nworkers = 1;
  int i;
  struct sd_thread_pool pool;

  if (argc > 1) nworkers = atoi(argv[1]);

  if (sd_thread_pool_init(&pool, nworkers)) {
    fprintf(stderr, "sd_thread_pool_init failed\n");
    return -1;
  }

  for (i=0; i<TASK_NUM; i++) {
    struct sd_thread_job *job = (struct sd_thread_job*)malloc(sizeof(*job));
    if (job == NULL) break;
    memset(job, 0, sizeof(*job));
    job->func = func_calc;
    job->ud = job;
    sd_thread_pool_pushjob(&pool, job);
  }

  sd_thread_pool_waitempty(&pool);

  sd_thread_pool_destroy(&pool);
  return 0;
}
