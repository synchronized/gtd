#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#define sd_lstring_node_size 4

typedef struct sd_lstring_node {
  size_t len;
  char data[sd_lstring_node_size];
  struct sd_lstring_node *next;
} sd_lstring_node_t;

sd_lstring_node_t* sd_lstring_create(char *str, size_t n) {
  if (!str) {
    return NULL;
  }

  sd_lstring_node_t *head = NULL;
  sd_lstring_node_t **next = &head;
  for (int i=0; i<n; ) {
    sd_lstring_node_t *node = (sd_lstring_node_t*)malloc(sizeof(sd_lstring_node_t));
    if (!node) {
      perror("sd_lstring node malloc failed");
      break;
    }
    memset(node, 0, sizeof(sd_lstring_node_t));
    size_t len = MIN(sd_lstring_node_size-1, n-i);
    memcpy(node->data, &str[i], len);

    node->len = len;
    *next = node;
    next = &node->next;
    i += (int)sd_lstring_node_size-1;
  }
  return head;
}

int  sd_lstring_destory(sd_lstring_node_t* t) {
  if (!t) {
    return -1;
  }
  printf("destory: ");
  for (sd_lstring_node_t *node = t; node; ) {
    printf("\"%s\", ", node->data);
    sd_lstring_node_t *tmp = node;
    node = node->next;
    free(tmp);
  }
  printf("\n");

  return 0;
}

void sd_lstring_display(sd_lstring_node_t *t) {
  if (!t) {
    return;
  }
  for (sd_lstring_node_t *node = t; node; node = node->next) {
    printf("%s", node->data);
  }
}

void sd_lstring_display_verbose(sd_lstring_node_t *t) {
  if (!t) {
    return;
  }
  sd_lstring_node_t *node = t;
  while (node) {
    printf("{len:%zu, data:\"%s\"} -> ", node->len, node->data);
    node = node->next;
  }
  printf("NULL\n");
}

sd_lstring_node_t* sd_lstring_test_create(char *str, size_t n) {
  sd_lstring_node_t* t = NULL;
  t = sd_lstring_create(str, n);
  printf("sd_lstring_create(\"%s\", %zu)\n", str, n);
  if (!t){
    printf("    Error\n");
  } else {
    printf("    ");
    sd_lstring_display(t);
    printf("\n");
  }
  return t;
}

int main() {
  sd_lstring_node_t* t = sd_lstring_test_create("hello world!", 12);
  if (!t) {
    return -1;
  }
  sd_lstring_destory(t);
  return 0;
}
