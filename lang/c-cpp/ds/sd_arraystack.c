#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sd_astack_size 5

typedef struct {
  int *data;
  int top;
  int size;
} sd_astack_t;

int sd_astack_init(sd_astack_t *as, int size);
int sd_astack_push(sd_astack_t *as, int elt);
int sd_astack_pop(sd_astack_t *as, int *elt);
void sd_astack_display(sd_astack_t *as);

int sd_astack_init(sd_astack_t *as, int size) {
  if (!as) {
    return -1; //as invalid
  }
  memset(as, 0, sizeof(sd_astack_t));
  as->data = (int*)malloc(size*sizeof(int));
  if (!as->data) {
    return -2; //malloc failed
  }
  as->top = 0;
  as->size = size;
  return 0;
}

void sd_astack_display(sd_astack_t *as) {
  if (!as) {
    return; //as invalid
  }
  printf("{top:%d, data:[", as->top);
  for (int i=0; i<as->top; i++) {
    if (i) {
      printf(", ");
    }
    printf("%d", as->data[i]);
  }
  printf("]}\n");
}

int sd_astack_push(sd_astack_t *as, int elt) {
  if (!as) {
    return -1; //as invalid
  }
  if (as->top >= as->size) {
    return -2; //full, maby realloc
  }
  as->data[as->top++] = elt;
  return 0;
}

int sd_astack_pop(sd_astack_t *as, int *elt) {
  if (!as) {
    return -1; //as invalid
  }
  if (!as->top) {
    return -2; //empty
  }
  *elt = as->data[--as->top];
  return 0;
}

int sd_astack_test_init(sd_astack_t *as, int size) {
  int code = 0;
  code = sd_astack_init(as, size);
  printf("sd_astack_init(as, %d) = %d\n", size, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_astack_display(as);
  }
  return code;
}

int sd_astack_test_push(sd_astack_t *as, int elt) {
  int code = 0;
  code = sd_astack_push(as, elt);
  printf("sd_astack_push(as, %d) = %d\n", elt, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_astack_display(as);
  }
  return code;
}

int sd_astack_test_pop(sd_astack_t *as, int *elt) {
  int code = 0;
  code = sd_astack_pop(as, elt);
  printf("sd_astack_pop(as, out:%d) = %d\n", *elt, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_astack_display(as);
  }
  return code;
}

int main() {
  int elt;
  sd_astack_t as;
  int code = sd_astack_test_init(&as, sd_astack_size);
  if (code) {
    return -1;
  }
  sd_astack_test_push(&as, 11);
  sd_astack_test_push(&as, 12);
  sd_astack_test_push(&as, 13);
  sd_astack_test_push(&as, 14);
  sd_astack_test_push(&as, 15);
  sd_astack_test_push(&as, 16);

  sd_astack_test_pop(&as, &elt);
  sd_astack_test_pop(&as, &elt);
  sd_astack_test_pop(&as, &elt);
  sd_astack_test_pop(&as, &elt);
  sd_astack_test_pop(&as, &elt);
  sd_astack_test_pop(&as, &elt);
  return 0;
}
