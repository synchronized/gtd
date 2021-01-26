#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sd_alist_size 5

typedef struct sd_alist {
  int *head;
  int length;
  int size;
} sd_alist_t;

//初始化
int sd_alit_init(sd_alist_t *t) {
  t->head = (int*)malloc(sd_alist_size*sizeof(int));
  if (!t->head) {
    return -1;
  }
  t->length = 0;
  t->size = sd_alist_size;
  return 0;
}

//打印
void sd_alist_display(sd_alist_t *t) {
  if (!t) {
    return;
  }

  printf("{head: [");
  for (int i=0; i<t->length; i++) {
    if (i != 0) {
      printf(" ");
    }
    printf("%d", t->head[i]);
  }
  printf("], length:%d, size:%d}\n", t->length, t->size);
}

//添加
int sd_alist_insert(sd_alist_t *t, int elt, int pos) {
  if (!t) {
    return -1; //t invalid
  }
  if (pos == -1) {
    pos = t->length;
  }
  if (pos < 0 || pos > t->length) {
    return -2; //pos invalid
  }
  if (t->length >= t->size) {
    t->head = (int*)realloc(t->head, (t->length+1)*sizeof(int));
    if (!t->head) {
      return -3; //realloc failed
    }
    t->length;
    t->size = t->length + 1;
  }
  for (int i=t->length; i>pos; i--) {
    t->head[i] = t->head[i-1];
  }
  t->head[pos] = elt;
  t->length++;
  return 0;
}

//删除
int sd_alist_delete(sd_alist_t *t, int pos) {
  if (!t) {
    return -1; //t invalid
  }
  if (pos == -1) {
    pos = t->length-1;
  }
  if (pos < 0 || pos >= t->length) {
    return -2; //pos invalid
  }
  for (int i=pos; i<t->length-1; i++) {
    t->head[i] = t->head[i+1];
  }
  t->length--;
  return 0;
}

//修改
int sd_alist_update(sd_alist_t *t, int elt, int pos) {
  if (!t) {
    return -1; //t invalid
  }
  if (pos == -1) {
    pos = t->length-1;
  }
  if (pos < 0 || pos >= t->length) {
    return -2; //pos invalid
  }
  t->head[pos] = elt;
  return 0;
}

//搜索
int sd_alist_select(sd_alist_t *t, int elt) {
  if (!t) {
    return -2; //t invalid
  }
  for (int i=0; i<t->length; i++) {
    if (t->head[i] == elt) {
      return i;
    }
  }
  return -1; //not found
}

int main() {
  sd_alist_t t;
  int err;
  printf("sd_alist test:\n");
  memset(&t, 0, sizeof(sd_alist_t));
  printf("    t.size: %d\n", t.size);
  err = sd_alit_init(&t);
  if (err != 0) {
    printf("    Error: sd_alist init failed");
  }
  printf("    t: ");
  sd_alist_display(&t);

  //insert
  err = sd_alist_insert(&t, 1, 0);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  err = sd_alist_insert(&t, 2, 0);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  err = sd_alist_insert(&t, 3, 1);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  err = sd_alist_insert(&t, 4, -1);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  err = sd_alist_insert(&t, 5, t.length);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  err = sd_alist_insert(&t, 6, t.length);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  err = sd_alist_insert(&t, 7, t.length);
  if (err != 0) {
    printf("    Error: sd_alist insert failed");
  }
  printf("    t: ");
  sd_alist_display(&t);

  //delete
  err = sd_alist_delete(&t, 0);
  if (err != 0) {
    printf("    Error: sd_alist delete failed: 0");
  }
  err = sd_alist_delete(&t, 2);
  if (err != 0) {
    printf("    Error: sd_alist delete failed: 2");
  }
  err = sd_alist_delete(&t, -1);
  if (err != 0) {
    printf("    Error: sd_alist delete failed: -1");
  }
  printf("    t: ");
  sd_alist_display(&t);

  //update
  err = sd_alist_update(&t, 10, -1);
  if (err != 0) {
    printf("    Error: sd_alist delete failed: -1");
  }
  err = sd_alist_update(&t, 11, 0);
  if (err != 0) {
    printf("    Error: sd_alist delete failed: -1");
  }
  err = sd_alist_update(&t, 12, 1);
  if (err != 0) {
    printf("    Error: sd_alist delete failed: -1");
  }
  printf("    t: ");
  sd_alist_display(&t);

  printf("    sd_alist_select(&t, 12) = %d\n", sd_alist_select(&t, 12));
  printf("    sd_alist_select(&t, 10) = %d\n", sd_alist_select(&t, 10));
}
