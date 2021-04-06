#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "sd_buffer.h"

int sd_buffer_init(struct sd_buffer *list) {
  if (list == NULL) return -1;
  bzero(list, sizeof(*list));
  return 0;
}

//增加写缓存
int sd_buffer_append(struct sd_buffer *list, void *buffer, int sz) {
  struct sd_buffer_node *wb = (struct sd_buffer_node*)malloc(sizeof(*wb));
  if (wb == NULL) return -1;
  memset(wb, 0, sizeof(*wb));
  wb->buffer = buffer;
  wb->size = sz;
  wb->next = NULL;
  if (!list->head) {
    list->head = list->tail = wb;
  } else {
    list->tail->next = wb;
    list->tail = wb;
  }
  list->size += sz;
  return 0;
}

//释放写缓存
int sd_buffer_destroy(struct sd_buffer *list) {
  if (list == NULL) return -1;
  struct sd_buffer_node *wb, *tmp;
  wb = list->head;
  while (wb) {
    tmp = wb;
    wb = wb->next;
    free(tmp);
  }
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return 0;
}

//移动
int sd_buffer_memmov(struct sd_buffer *list, size_t n) {
  if (!list) return -1;
  if (!list->head) return -2;
  struct sd_buffer_node *wb = list->head;
  if (wb->size < n) return -3;

  if (n == 0) {
    return 0;
  }

  list->size -= n;
  if (wb->size > n) {
    //移动到头部(方便外部释放wb->buffer)
    memmove(wb->buffer, wb->buffer+n, n);
    wb->size -= n;
  } else {
    list->head = wb->next;
    free(wb);
  }
  return 0;
}

//下一次写入数据块指针
void* sd_buffer_nextdata(struct sd_buffer *list) {
  if (!list) return NULL;
  if (!list->head) return NULL;
  return list->head->buffer;
}
//下一次写入数据块大小
int sd_buffer_nextsize(struct sd_buffer *list) {
  if (!list) return -1;
  if (!list->head) return 0;
  return list->head->size;
}
