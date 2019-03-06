#include <stdio.h>
#include <stdlib.h>

#define sd_slink_size 5

typedef struct {
  int idx; //index
  int data; //data
  int cur; //cursor
} sd_slink_comp_t;

typedef struct {
  sd_slink_comp_t *head;
  int startidx;
  int size;
} sd_slink_t;

int sd_slink_init(sd_slink_t *sl, int size);
int *sd_slink_getidx_pos(sd_slink_t *sl, int pos);
int sd_slink_insert(sd_slink_t *sl, int elt, int pos);
int sd_slink_update(sd_slink_t *sl, int elt, int pos);
int sd_slink_delete(sd_slink_t *sl, int pos);
int sd_slink_indexof(sd_slink_t *sl, int pos);
int sd_slink_eltat(sd_slink_t *sl, int elt);
void sd_slink_display(sd_slink_t *sl);
void sd_slink_display_link(sd_slink_t *sl);

int sd_slink_comp_malloc(sd_slink_comp_t *t);
void sd_slink_comp_display_arr(sd_slink_comp_t *t, int size);

int sd_slink_init(sd_slink_t *sl, int size) {
  if (!sl) {
    return -1; //sl invalid
  }
  sd_slink_comp_t *t = (sd_slink_comp_t*)malloc(size*sizeof(sd_slink_comp_t));
  if (!t) {
    return -2; //malloc failed
  }
  sl->head = t;
  int i=0;
  for (; i<size; i++) {
    (t+i)->idx = i;
    (t+i)->data = 0;
    (t+i)->cur = i+1;
  }
  (t+i-1)->cur = 0;
  sl->startidx = 0; //sd_slink_comp_malloc(t);
  sl->size = size;
  return 0;
}

int sd_slink_comp_malloc(sd_slink_comp_t *t) {
  int i = t->cur;
  if (i) {
    t->cur = (t+i)->cur;
    (t+i)->cur = 0;
  }
  return i;
}

void sd_slink_comp_display_arr(sd_slink_comp_t *t, int size) {
  printf("[");
  for (int i=0; i<size; i++) {
    if (i) {
      printf(", ");
    }
    printf("{idx: %d, data:%d, cur:%d}", (t+i)->idx, (t+i)->data, (t+i)->cur);
  }
  printf("]\n");
}

void sd_slink_display_link(sd_slink_t *sl) {
  sd_slink_comp_t *t = (sl->head);
  printf("startidx: %d [", sl->startidx);
  for (int i=sl->startidx; i; i = (t+i)->cur) {
    //printf("{idx: %d, data:%d, cur:%d} -> ", (t+i)->idx, (t+i)->data, (t+i)->cur);
    printf("{data:%d, cur:%d} -> ", (t+i)->data, (t+i)->cur);
  }
  printf("NULL]\n");
}

void sd_slink_display(sd_slink_t *sl) {
  if (!sl) {
    return;
  }
  //printf("    ");
  //sd_slink_comp_display_arr(sl->head, sl->size);
  printf("    ");
  sd_slink_display_link(sl);
}

int *sd_slink_getidx_pos(sd_slink_t *sl, int pos) {
  sd_slink_comp_t *t = sl->head;
  int *cur = &(sl->startidx);
  int i=0;
  for (; i<pos && (*cur) > 0; i++) {
    cur=&((t+(*cur))->cur);
  }
  if (i != pos) {
    return NULL;
  }
  return cur;
}

int sd_slink_insert(sd_slink_t *sl, int elt, int pos) {
  if (!sl) {
    return -1; //t invalid
  }
  int *cur = NULL;
  cur = sd_slink_getidx_pos(sl, pos);
  if (!cur) {
    return -2; //not found
  }
  int eltidx = sd_slink_comp_malloc(sl->head);
  if (!eltidx) {
    return -3; //not enough
  }
  sd_slink_comp_t *t = sl->head;
  (t+eltidx)->cur = *cur;
  *cur = eltidx;
  (t+(*cur))->data = elt;
  return 0;
}

int sd_slink_update(sd_slink_t *sl, int elt, int pos) {
  if (!sl) {
    return -1; //t invalid
  }
  int *cur = NULL;
  cur = sd_slink_getidx_pos(sl, pos);
  if (!cur) {
    return -2; //not found
  }
  if (!*cur) {
    return -3; //not found
  }
  sd_slink_comp_t *t = sl->head;
  (t+(*cur))->data = elt;
  return 0;
}

int sd_slink_delete(sd_slink_t *sl, int pos) {
  if (!sl) {
    return -1; //t invalid
  }
  int *cur = NULL;
  cur = sd_slink_getidx_pos(sl, pos);
  if (!cur) {
    return -2; //not found
  }
  sd_slink_comp_t *t = sl->head;
  *cur = (t+(*cur))->cur;
  return 0;
}

int sd_slink_indexof(sd_slink_t *sl, int pos) {
  int *cur = sd_slink_getidx_pos(sl, pos);
  if (!cur) {
    return -1;
  }
  if (!*cur) {
    return -1;
  }
}

int sd_slink_eltat(sd_slink_t *sl, int elt) {
  sd_slink_comp_t *t = sl->head;
  int *cur = &(sl->startidx);
  for (; i<pos && (*cur) > 0; i++) {
    cur=&((t+(*cur))->cur);
  }
}

int sd_slink_test_init(sd_slink_t *sl, int size) {
  printf("sd_slink_init(sl, %d)\n", size);
  int code = 0;
  code = sd_slink_init(sl, size);
  if (code) {
    printf("    Error:\n");
  } else {
    sd_slink_display(sl);
  }
  return code;
}

void sd_slink_test_insert(sd_slink_t *sl, int elt, int pos) {
  int code = 0;
  code = sd_slink_insert(sl, elt, pos);
  printf("sd_slink_insert(sl, %d, %d) = %d\n", elt, pos, code);
  if (code) {
    printf("    Error:\n");
  } else {
    sd_slink_display(sl);
  }
}

void sd_slink_test_update(sd_slink_t *sl, int elt, int pos) {
  int code = 0;
  code = sd_slink_update(sl, elt, pos);
  printf("sd_slink_update(sl, %d, %d) = %d\n", elt, pos, code);
  if (code) {
    printf("    Error:\n");
  } else {
    sd_slink_display(sl);
  }
}

void sd_slink_test_delete(sd_slink_t *sl, int pos) {
  int code = 0;
  code = sd_slink_delete(sl, pos);
  printf("sd_slink_delete(sl, %d) = %d\n", pos, code);
  if (code) {
    printf("    Error:\n");
  } else {
    sd_slink_display(sl);
  }
}

int main() {
  int code = 0;
  int size = sd_slink_size;
  sd_slink_t sl;
  code = sd_slink_test_init(&sl, size);
  if (code) {
    return -1;
  }
  sd_slink_test_insert(&sl, 2, 0);
  sd_slink_test_insert(&sl, 1, 0);
  sd_slink_test_insert(&sl, 3, 2);
  sd_slink_test_insert(&sl, 13, 2);

  sd_slink_test_update(&sl, 20, 0);
  sd_slink_test_update(&sl, 21, 1);
  sd_slink_test_update(&sl, 22, 2);
  sd_slink_test_update(&sl, 23, 3);

  sd_slink_test_delete(&sl, 2);
  sd_slink_test_delete(&sl, 2);
  sd_slink_test_delete(&sl, 0);
  sd_slink_test_delete(&sl, 0);
  return 0;
}
