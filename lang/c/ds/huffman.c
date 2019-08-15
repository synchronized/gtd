#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

static int minheap_incre_step = 10;

struct huffman_minheap{
  struct huffman_node **root; //指针的数组
  int len;
  int size;
};

//创建最小堆
static int minheap_create(struct huffman_minheap *heap, huffman_key *data, int size);

//销毁最小堆
static void minheap_destroy(struct huffman_minheap *heap);

//插入结点到最小堆
static int minheap_insert(struct huffman_minheap *heap, struct huffman_node *node);

//从最小堆中获取最小值
static struct huffman_node *minheap_pop(struct huffman_minheap *heap);

//霍夫曼树-创建结点
static struct huffman_node *huffman_create_node(huffman_key key,
                                                struct huffman_node *left,
                                                struct huffman_node *right,
                                                struct huffman_node *parent)
{
  struct huffman_node *node = (struct huffman_node*)malloc(sizeof(struct huffman_node));
  if (node == NULL) {
    return NULL;
  }
  node->key = key;
  node->left = left;
  node->right = right;
  node->parent = parent;
  return node;
}


/*
 * 创建Huffman树
 *
 * 参数说明：
 *     a 权值数组
 *     size 数组大小
 *
 * 返回值：
 *     Huffman树的根
 */
struct huffman_node* huffman_create(huffman_key data[], int size) {
  int i;
  struct huffman_node *left, *right, *parent = NULL;

  struct huffman_minheap heap;
  // 建立数组a对应的最小堆
  minheap_create(&heap, data, size);
  int ret;

  for (i=0; i<size-1; i++) {
    left = minheap_pop(&heap); // 最小节点是左孩子
    if (left == NULL) {
      break;
    }
    right = minheap_pop(&heap); //其次才是右孩子
    if (right == NULL) {
      parent = left;
      break;
    }
    // 新建parent节点，左右孩子分别是left/right；
    parent = huffman_create_node(left->key + right->key, left, right, NULL);
    left->parent = parent;
    right->parent = parent;

    // 将parent节点数据拷贝到"最小堆"中
    ret = minheap_insert(&heap, parent);
    if (ret != 0) {
      printf("huffman insert failed: minheap_insert(parent) == %d", ret);
      huffman_destroy(parent);
      parent = NULL;
      break;
    }
  }

  //销毁最小堆
  minheap_destroy(&heap);
  return parent;
}

//霍夫曼树-销毁树
void huffman_destroy(struct huffman_node *node) {
  if (node == NULL) {
    return;
  }
  huffman_destroy(node->left);
  huffman_destroy(node->right);
  free(node);
}

//创建最小堆
static int minheap_create(struct huffman_minheap *heap, huffman_key *data, int size)
{
  if (heap == NULL) {
    return -1;
  }
  heap->root = (struct huffman_node**)malloc(sizeof(struct huffman_node*)*size);
  if (heap->root == NULL) {
    return -2;
  }
  int i;
  for (i = 0; i < size; i++) {
    heap->root[i] = huffman_create_node(data[i], NULL, NULL, NULL);
  }
  heap->len = size;
  heap->size = size;
  return 0;
}

//销毁最小堆
static void minheap_destroy(struct huffman_minheap *heap) {
  if (heap == NULL) {
    return;
  }
  free(heap->root);
  heap->len = 0;
  heap->size = 0;
}

static int minheap_insert_fixup(struct huffman_minheap *heap, int start)
{
  if (heap == NULL) {
    return -1;
  }
  if (heap->size <= 0 || heap->size <= start) {
    return -2;
  }
  int c = start;
  struct huffman_node *node = heap->root[c];
  while(c > 0) {
    int p = (c-1)/2; /* 父结点索引 */
    if (heap->root[p]->key <= node->key)
      break;

    heap->root[c] = heap->root[p];
    c = p;
  }
  heap->root[c] = node;
  return 0;
}

//插入结点到最小堆
static int minheap_insert(struct huffman_minheap *heap, struct huffman_node *node)
{
  if (heap == NULL) {
    return -1;
  }
  if (node == NULL) {
    return -2;
  }
  if (heap->size >= heap->len) {
    struct huffman_node** newroot;
    newroot = (struct huffman_node**)realloc(heap->root, sizeof(struct huffman_node*)*minheap_incre_step);
    if (newroot == NULL) {
      return -3;
    }
    heap->root = newroot;
    heap->len += minheap_incre_step;
  }
  heap->root[heap->size++] = node;
  return minheap_insert_fixup(heap, heap->size-1);
}

static int minheap_delete_fixup(struct huffman_minheap *heap, int start, int end) {
  if (heap == NULL) {
    return -1;
  }
  if (heap->size <= 0 || heap->size <= start || heap->size <= end) {
    return -2;
  }
  int c = start;
  struct huffman_node *node = heap->root[c];
  while(c < end) {
    int l = c*2 + 1; /* 左子结点 */
    if (l < end && heap->root[l]->key > heap->root[l+1]->key) {
      l++;
    }
    if (node->key <= heap->root[l]->key)
      break;

    heap->root[c] = heap->root[l];
    c = l;
  }
  heap->root[c] = node;
  return 0;
}

//从最小堆中获取最小值
static struct huffman_node *minheap_pop(struct huffman_minheap *heap) {
  if (heap == NULL) {
    return NULL;
  }
  if (heap->size <= 0) {
    return NULL;
  }
  struct huffman_node *node = heap->root[0];
  heap->size--;
  heap->root[0] = heap->root[heap->size];
  minheap_delete_fixup(heap, 0, heap->size-1);
  return node;
}
