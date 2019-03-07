#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sd_lstack_size 5

typedef struct sd_lstack_node {
  int data;
  struct sd_lstack_node *next;
} sd_lstack_node_t;

typedef struct sd_lstack {
  sd_lstack_node_t *head;
  sd_lstack_node_t *top;
  int size;
} sd_lstack_t;

int sd_lstack_init(sd_lstack_t *ls, int size);
void sd_lstack_display(sd_lstack_t *ls);

int sd_lstack_init(sd_lstack_t *ls, int size) {
  if (!ls) {
    return -1;
  }
  memset(ls, 0, sizeof(sd_lstack_t));
  sd_lstack_node_t **t = &(ls->head);
  for (int i=0; i<size; i++) {
    sd_lstack_node_t *node = (sd_lstack_node_t*)malloc(sizeof(sd_lstack_node_t));
    if (!node) {
      return -2;
    }
    memset(node, 0, sizeof(sd_lstack_node_t));
    *t = node;
    ls->top = node;
    ls->size++;
    t = &(node->next);
  }
  return 0;
}

int sd_lstack_push(sd_lstack_t *ls, int elt) {
  if (!ls) {
    return -1;
  }
  sd_lstack_node_t *node = (sd_lstack_node_t*)malloc(sizeof(sd_lstack_node_t));
  if (!node) {
    return -2;
  }
  memset(node, 0, sizeof(sd_lstack_node_t));
  node->data = elt;
  sd_lstack_node_t **next = &(ls->head);
  if (ls->top) {
    next = &(ls->top->next);
  }
  *next = node;
  ls->top = node;
  return 0;
}

int sd_lstack_pop(sd_lstack_t *ls, int *elt) {
  if (!ls) {
    return -1;
  }
  if (!ls->top) {
    return -2; //empty
  }

  sd_lstack_node_t **node = &(ls->head);
  sd_lstack_node_t **last = &(ls->head);
  for (; *node != ls->top; node = &((*node)->next)) {
    last = node;
  }
  *elt = (*node)->data;
  *node = NULL;
  ls->top = *last;
  return 0;
}

void sd_lstack_display(sd_lstack_t *ls) {
  if (!ls) {
    return;
  }
  printf("{size:%d, [", ls->size);
  sd_lstack_node_t *node = ls->head;
  if (ls->top) {
    for (node = ls->head; node != ls->top; node = node->next) {
      printf("%d => ", node->data);
    }
    printf("%d => ", node->data);
  }
  printf("NULL]}\n");
}

int sd_lstack_test_init(sd_lstack_t *ls, int size) {
  int code = 0;
  code = sd_lstack_init(ls, size);
  printf("sd_lstack_init(&ls, %d) = %d\n", size, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_lstack_display(ls);
  }
  return code;
}

int sd_lstack_test_push(sd_lstack_t *ls, int elt) {
  int code = 0;
  code = sd_lstack_push(ls, elt);
  printf("sd_lstack_push(&ls, %d) = %d\n", elt, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_lstack_display(ls);
  }
  return code;
}

int sd_lstack_test_pop(sd_lstack_t *ls, int *elt) {
  int code = 0;
  code = sd_lstack_pop(ls, elt);
  printf("sd_lstack_pop(&ls, %d) = %d\n", *elt, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_lstack_display(ls);
  }
  return code;
}

int main() {
  int elt = 0;
  int code = 0;
  sd_lstack_t ls;
  code = sd_lstack_test_init(&ls, 0);
  if (code) {
    return -1;
  }
  sd_lstack_test_push(&ls, 11);
  sd_lstack_test_push(&ls, 12);
  sd_lstack_test_push(&ls, 13);
  sd_lstack_test_push(&ls, 14);
  sd_lstack_test_push(&ls, 15);

  sd_lstack_test_pop(&ls, &elt);
  sd_lstack_test_pop(&ls, &elt);
  sd_lstack_test_pop(&ls, &elt);
  sd_lstack_test_pop(&ls, &elt);
  sd_lstack_test_pop(&ls, &elt);
  sd_lstack_test_pop(&ls, &elt);
  return 0;
}
