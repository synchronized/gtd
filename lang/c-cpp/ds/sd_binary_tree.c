#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sd_bintree_node {
  int data;
  struct sd_bintree_node *left;
  struct sd_bintree_node *right;
} sd_bintree_node_t;

typedef struct {
  sd_bintree_node_t *root;
} sd_bintree_t;

int sd_bintree_init(sd_bintree_t *bt, int size) {
  if (!bt) {
    return -1;
  }
  memset(bt, 0, sizeof(sd_bintree_t));
  return 0;
}

void sd_bintree_display(sd_bintree_t *bt) {
  if (!bt) {
    return;
  }

  
}

int main() {
}
