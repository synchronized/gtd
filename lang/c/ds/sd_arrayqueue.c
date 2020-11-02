#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int *data;
  int size;
  int head;
  int tail;
} sd_aqueue_t;

int sd_aqueue_init(sd_aqueue_t *aq, int size) {
  if (!aq) {
    return -1; //aq invalid
  }
  memset(aq, 0, sizeof(sd_aqueue_t));
  aq->data = (int*)malloc(size*sizeof(int));
  if (!aq->data) {
    return -2; //malloc failed
  }
  memset(aq->data, 0, (size*sizeof(int)));
  aq->size = size;
  aq->head = 0;
  aq->tail = 0;
  return 0;
}

int sd_aqueue_next(int curr, int size) {
  int ret = curr + 1;
  if (ret >= size) {
    ret %= size;
  }
  return ret;
}

void sd_aqueue_display(sd_aqueue_t *aq) {
  if (!aq) {
    return;
  }
  printf("{size:%d, head:%d, tail:%d, data:[", aq->size, aq->head, aq->tail);
  int first = 1;
  for (int i=aq->head; i!=aq->tail; ) {
    if (!first) {
      printf(", ");
    }
    first = 0;
    printf("%d", aq->data[i]);
    i = sd_aqueue_next(i, aq->size);
  }
  printf("]}\n");
}

int sd_aqueue_append(sd_aqueue_t *aq, int elt) {
  if (!aq) {
    return -1;
  }
  int next = sd_aqueue_next(aq->tail, aq->size);
  if (next == aq->head) {
    return -2; //full
  }
  aq->data[aq->tail] = elt;
  aq->tail = next;
  return 0;
}

int sd_aqueue_shift(sd_aqueue_t *aq, int *elt) {
  if (!aq) {
    return -1;
  }
  if (aq->head == aq->tail) {
    return -2; //empty
  }
  int next = sd_aqueue_next(aq->head, aq->size);
  *elt = aq->data[aq->head];
  aq->head = next;
  return 0;
}

int sd_aqueue_test_init(sd_aqueue_t *aq, int size) {
  int code = 0;
  code = sd_aqueue_init(aq, size);
  printf("sd_aqueue_init(aq, %d) == %d\n", size, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_aqueue_display(aq);
  }
  return code;
}

int sd_aqueue_test_append(sd_aqueue_t *aq, int elt) {
  int code = 0;
  code = sd_aqueue_append(aq, elt);
  printf("sd_aqueue_append(aq, %d) == %d\n", elt, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_aqueue_display(aq);
  }
  return code;
}

int sd_aqueue_test_shift(sd_aqueue_t *aq, int *elt) {
  int code = 0;
  code = sd_aqueue_shift(aq, elt);
  printf("sd_aqueue_shift(aq, %d) == %d\n", *elt, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_aqueue_display(aq);
  }
  return code;
}

int main() {
  int code = 0;
  int elt = 0;
  sd_aqueue_t aq;
  code = sd_aqueue_test_init(&aq, 5);
  if (code) {
    return -1;
  }

  sd_aqueue_test_append(&aq, 11);
  sd_aqueue_test_append(&aq, 12);
  sd_aqueue_test_append(&aq, 13);
  sd_aqueue_test_append(&aq, 14);
  sd_aqueue_test_append(&aq, 15);
  sd_aqueue_test_append(&aq, 16);

  sd_aqueue_test_shift(&aq, &elt);
  sd_aqueue_test_shift(&aq, &elt);
  sd_aqueue_test_shift(&aq, &elt);
  sd_aqueue_test_shift(&aq, &elt);
  sd_aqueue_test_shift(&aq, &elt);
  return 0;
}
