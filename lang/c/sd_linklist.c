#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sd_llist_size 5
typedef struct sd_llist {
  char elt;
  struct sd_llist *next;
} sd_llist_t;

sd_llist_t * sd_llist_init(int size);
int sd_llist_display(sd_llist_t *t);
int sd_llist_insert(sd_llist_t **t, int elt, int pos);
int sd_llist_update(sd_llist_t **t, int elt, int pos);
int sd_llist_delete(sd_llist_t **t, int pos);


sd_llist_t * sd_llist_init(int size) {
  printf("sd_llist_init(%d)\n", size);
  sd_llist_t *head = NULL;
  sd_llist_t **next = &head;
  sd_llist_t *temp = NULL;

  for (int i=0; i<size; i++) {
    temp = (sd_llist_t*)malloc(sizeof(sd_llist_t));
    memset(temp, 0, sizeof(sd_llist_t));
    temp->elt = i;
    *next = temp;
    next = &(*next)->next;
  }
  return head;
}

int sd_llist_display(sd_llist_t *t) {
  sd_llist_t *next = t;
  while(next) {
    printf("{elt: %d} -> ", next->elt) ;
    next = next->next;
  }
  printf("NULL\n");
  return 0;
}

int sd_llist_insert(sd_llist_t **t, int elt, int pos) {
  int i = 0;
  sd_llist_t **node = t;
  sd_llist_t *new_node = NULL;
  for (i=0; i<pos && *node; i++, node=&(*node)->next) {
    ;
  }
  if (i != pos) {
    return -1; //t invalid
  }

  new_node = (sd_llist_t*)malloc(sizeof(sd_llist_t));
  if (!new_node) {
    return -3; //new node invalid
  }
  memset(new_node, 0, sizeof(sd_llist_t));
  new_node->next = (*node);
  new_node->elt = elt;
  *node = new_node;
  return 0;
}

int sd_llist_update(sd_llist_t **t, int elt, int pos) {
  int i = 0;
  sd_llist_t **node = t;
  for (i=0; i<pos && *node; i++, node=&(*node)->next) {
    ;
  }
  if (i != pos) {
    return -1; //pos invalid
  }
  if (!*node) {
    return -2; //pos invalid
  }

  (*node)->elt = elt;
  return 0;
}

int sd_llist_delete(sd_llist_t **t, int pos) {
  int i = 0;
  sd_llist_t **node = t;
  for (i=0; i<pos && *node; i++, node=&(*node)->next) {
    ;
  }
  if (i != pos) {
    return -1; //pos invalid
  }
  if (!*node) {
    return -2; //pos invalid
  }

  *node = (*node)->next;
  return 0;
}

void sd_llist_test_insert(sd_llist_t **t, int elt, int pos) {
  int code = sd_llist_insert(t, elt, pos);
  printf("sd_llist_insert(t, %d, %d) = %d\n", elt, pos, code);
  if (code != 0) {
    printf("    Error\n");
  }
  printf("    after insert: ");
  sd_llist_display(*t);
}

void sd_llist_test_update(sd_llist_t **t, int elt, int pos) {
  int code = sd_llist_update(t, elt, pos);
  printf("sd_llist_update(t, %d, %d) = %d\n", elt, pos, code);
  if (code != 0) {
    printf("    Error\n");
  }
  printf("    after update: ");
  sd_llist_display(*t);
}

void sd_llist_test_delete(sd_llist_t **t, int pos) {
  int code = sd_llist_delete(t, pos);
  printf("sd_llist_delete(t, %d) = %d\n", pos, code);
  if (code != 0) {
    printf("    Error\n");
  }
  printf("    after delete: ");
  sd_llist_display(*t);
}

int main() {
  printf("linklist:\n");
  int code = 0;
  sd_llist_t *t = sd_llist_init(sd_llist_size);
  printf("    init: ");
  sd_llist_display(t);
  sd_llist_test_insert(&t, 10, 0);
  sd_llist_test_insert(&t, 11, 2);
  sd_llist_test_insert(&t, 12, 7);

  printf("\n");
  sd_llist_test_update(&t, -1, 0);
  sd_llist_test_update(&t, -1, 2);
  sd_llist_test_update(&t, -1, 7);
  sd_llist_test_update(&t, -1, 8);

  printf("\n");
  sd_llist_test_delete(&t, 7);
  sd_llist_test_delete(&t, 2);
  sd_llist_test_delete(&t, 0);
  sd_llist_test_delete(&t, 8);
}
