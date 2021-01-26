#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sd_dlink_node {
  struct sd_dlink_node *prev;
  int data;
  struct sd_dlink_node *next;
} sd_dlink_node_t;

typedef struct sd_dlink {
  sd_dlink_node_t *head;
} sd_dlink_t;

int sd_dlink_init(sd_dlink_t *dl, int size);
int sd_dlink_insert(sd_dlink_t *dl, int elt, int pos);
int sd_dlink_update(sd_dlink_t *dl, int elt, int pos);
int sd_dlink_delete(sd_dlink_t *dl, int pos);
void sd_dlink_display(sd_dlink_t *dl);
void sd_dlink_free(sd_dlink_t *dl);

int sd_dlink_init(sd_dlink_t *dl, int size) {
  if (!dl) {
    return -1; //dl invalid
  }
  memset(dl, 0, sizeof(sd_dlink_t)); //init memory
  int i=0;
  sd_dlink_node_t **t = &(dl->head);
  sd_dlink_node_t *node = NULL;
  sd_dlink_node_t **prev = NULL;
  for (; i<size; i++, t = &(node->next)) {
    node = (sd_dlink_node_t *)malloc(sizeof(sd_dlink_node_t));
    memset(node, 0, sizeof(sd_dlink_node_t));
    if (!node) {
      break; //malloc failed
    }
    node->data = i;
    node->prev = prev ? *prev : NULL;
    node->next = *t;
    *t = node; //prev->next;
    prev = &node;
  }
  if (i!=size) {
    return -2; //malloc failed
  }

  return 0;
}

int sd_dlink_insert(sd_dlink_t *dl, int elt, int pos) {
  if (!dl) {
    return -1; //dl invalid
  }
  int i=0;
  sd_dlink_node_t dummyNode;
  dummyNode.next = dl->head;
  sd_dlink_node_t *prev = &dummyNode;
  sd_dlink_node_t *curr = prev->next;

  while (i<pos && curr) {
    i++;
    prev = curr;
    curr = curr->next;
  }
  if (i!=pos) {
    return -2; //pos invalid
  }

  sd_dlink_node_t *node = (sd_dlink_node_t *)malloc(sizeof(sd_dlink_node_t));
  if (!node) {
    return -3; //malloc invalid
  }
  memset(node, 0, sizeof(sd_dlink_node_t));
  node->data = elt;
  node->prev = prev;
  node->next = curr;
  prev->next = node;
  if (!curr) {
    curr->prev = node;
  }
  dl->head = dummyNode.next;
  return 0;
}

void sd_dlink_display(sd_dlink_t *dl) {
  if (!dl) {
    return;
  }
  sd_dlink_node_t *curr = dl->head;
  printf("{[");
  for (; curr; curr=curr->next) {
    printf("{data: %d} <-> ", curr->data);
  }
  printf("NULL]}\n");
}

void sd_dlink_free(sd_dlink_t *dl) {
  sd_dlink_node_t dummyNode;
  memset(&dummyNode, 0, sizeof(sd_dlink_t));
  dummyNode.next = dl->head;
  sd_dlink_node_t *curr = dl->head;
  while (curr) {
    sd_dlink_node_t *tmp = curr;
    curr = curr->next;

    tmp->prev = NULL;
    tmp->next = NULL;
    free(tmp);
  }

  dl->head = NULL;
}

int sd_dlink_test_init(sd_dlink_t *dl, int size) {
  int code = 0;
  code = sd_dlink_init(dl, size);
  printf("sd_dlink_init(dl, %d) = %d\n", size, code);
  if (code) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_dlink_display(dl);
  }
  return code;
}

void sd_dlink_test_free(sd_dlink_t *dl) {
  sd_dlink_free(dl);
  printf("sd_dlink_free(dl)\n");
  printf("    ");
  sd_dlink_display(dl);
  return;
}

int main() {
  int size = 5;
  sd_dlink_t dl;
  int code = sd_dlink_test_init(&dl, size);
  if (code) {
    return -1;
  }
  sd_dlink_test_init(&dl, 11);
  sd_dlink_test_init(&dl, 12);
  sd_dlink_test_init(&dl, 13);
  sd_dlink_test_init(&dl, 14);
  sd_dlink_test_free(&dl);
  return 0;
}
