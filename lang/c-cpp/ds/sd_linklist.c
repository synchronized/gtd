#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sd_llist_size 5
typedef struct sd_llist_node {
  char elt;
  struct sd_llist_node *next;
} sd_llist_node_t;

typedef struct sd_llist {
  sd_llist_node_t *head;
} sd_llist_t;

int sd_llist_init(sd_llist_t *ll, int size);
int sd_llist_display(sd_llist_t *ll);
int sd_llist_insert(sd_llist_t *ll, int elt, int pos);
int sd_llist_update(sd_llist_t *ll, int elt, int pos);
int sd_llist_delete(sd_llist_t *ll, int pos);


int sd_llist_init(sd_llist_t *ll, int size) {
  if (!ll) {
    return -1;
  }
  memset(ll, 0, sizeof(sd_llist_t));
  sd_llist_node_t **next = &ll->head;
  sd_llist_node_t *temp = NULL;

  for (int i=0; i<size; i++) {
    temp = (sd_llist_node_t*)malloc(sizeof(sd_llist_node_t));
    if (!temp) {
      return -2;
    }
    memset(temp, 0, sizeof(sd_llist_node_t));
    temp->elt = i;
    *next = temp;
    next = &(*next)->next;
  }
  return 0;
}

int sd_llist_display(sd_llist_t *ll) {
  if (!ll) {
    return -1;
  }
  sd_llist_node_t *next = ll->head;
  while(next) {
    printf("{elt: %d} -> ", next->elt) ;
    next = next->next;
  }
  printf("NULL\n");
  return 0;
}

int sd_llist_insert(sd_llist_t *ll, int elt, int pos) {
  if (!ll) {
    return -1;
  }
  int i = 0;
  sd_llist_node_t **next = &ll->head;
  for (; i<pos && *next; i++, next = &(*next)->next) {
    ;
  }
  if (i != pos) {
    return -2; //t invalid
  }

  sd_llist_node_t *node = (sd_llist_node_t*)malloc(sizeof(sd_llist_node_t));
  if (!node) {
    return -3; //new node invalid
  }
  memset(node, 0, sizeof(sd_llist_t));
  node->elt = elt;
  node->next = *next;
  *next = node;
  return 0;
}

int sd_llist_update(sd_llist_t *ll, int elt, int pos) {
  if (!ll) {
    return -1;
  }
  int i = 0;
  sd_llist_node_t *curr = ll->head;
  while (i<pos && curr) {
    curr = curr->next;
    i++;
  }
  if (i != pos) {
    return -2; //pos invalid
  }

  if (!curr) {
    return -3; //pos invalid
  }

  curr->elt = elt;
  return 0;
}

int sd_llist_delete(sd_llist_t *ll, int pos) {
  if (!ll) {
    return -1;
  }
  int i = 0;
  sd_llist_node_t **next = &ll->head;
  for (; i<pos && *next; i++, next=&(*next)->next) {
    ;
  }
  if (i != pos) {
    return -1; //pos invalid
  }

  if (*next) {
    *next = (*next)->next;
  }
  return 0;
}

int sd_llist_test_init(sd_llist_t *ll, int size) {
  int code = 0;
  code = sd_llist_init(ll, size);
  printf("sd_llist_init(t, %d) = %d\n", size, code);
  if (code != 0) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_llist_display(ll);
  }
  return code;
}

void sd_llist_test_insert(sd_llist_t *ll, int elt, int pos) {
  int code = sd_llist_insert(ll, elt, pos);
  printf("sd_llist_insert(ll, %d, %d) = %d\n", elt, pos, code);
  if (code != 0) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_llist_display(ll);
  }
}

void sd_llist_test_update(sd_llist_t *ll, int elt, int pos) {
  int code = sd_llist_update(ll, elt, pos);
  printf("sd_llist_update(ll, %d, %d) = %d\n", elt, pos, code);
  if (code != 0) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_llist_display(ll);
  }
}

void sd_llist_test_delete(sd_llist_t *ll, int pos) {
  int code = sd_llist_delete(ll, pos);
  printf("sd_llist_delete(ll, %d) = %d\n", pos, code);
  if (code != 0) {
    printf("    Error\n");
  } else {
    printf("    ");
    sd_llist_display(ll);
  }
}

int main() {
  printf("linklist:\n");
  int code = 0;
  sd_llist_t ll;
  code = sd_llist_test_init(&ll, sd_llist_size);
  if (code) {
    return -1;
  }
  sd_llist_test_insert(&ll, 10, 0);
  sd_llist_test_insert(&ll, 11, 2);
  sd_llist_test_insert(&ll, 12, 7);
  sd_llist_test_insert(&ll, 13, 9);

  printf("\n");
  sd_llist_test_update(&ll, -1, 0);
  sd_llist_test_update(&ll, -1, 2);
  sd_llist_test_update(&ll, -1, 7);
  sd_llist_test_update(&ll, -1, 8);

  printf("\n");
  sd_llist_test_delete(&ll, 7);
  sd_llist_test_delete(&ll, 2);
  sd_llist_test_delete(&ll, 0);
  sd_llist_test_delete(&ll, 8);
  return 0;
}
