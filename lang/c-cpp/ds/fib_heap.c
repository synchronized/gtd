#include "stdlib.h"
#include "fib_heap.h"

//销毁结点
static void fib_heap_destory_node(struct fib_heap_node *node);
//将"单个节点node"加入"链表root"之前
static void fib_heap_add(fib_heap_node *root, fib_heap_node *node);
//链接两个双链表
static void fib_heap_cat(fib_heap_node *a, fib_heap_node *b);
//插入结点
static void fib_heap_insert_node(struct fib_heap *heap, struct fib_heap_node *node);
//删除结点
static struct fib_heap* fib_heap_delete_node(struct fib_heap *heap, struct fib_heap_node *node);
//创建结点
static struct fib_heap_node* fib_heap_create_node(fib_heap_key key);

static struct fib_heap_node* fib_heap_union(struct fib_heap_node *a, struct fib_heap_node *b);

//初始化
void fib_heap_init(struct fib_heap *heap)
{
  if (heap == NULL)
    return;

  heap->num = 0;
  heap->max_degree = 0;
  heap->min = NULL;
  heap->cons = NULL;
}


//销毁
void fib_heap_destroy(struct fib_heap *heap);

//插入
void fib_heap_insert(struct fib_heap *heap, fib_heap_key key);

//删除
void fib_heap_delete(struct fib_heap *heap, fib_heap_key key);


//销毁结点
static void fib_heap_destory_node(struct fib_heap_node *node);

/*
 * 将"单个节点node"加入"链表root"之前
 *   a …… root
 *   a …… node …… root
 *
 * 注意： 此处node是单个节点，而root是双向链表
 */
static void fib_heap_add(fib_heap_node *root, fib_heap_node *node)
{
  node->left = root->left;
  root->left->right = node;
  node->right = root;
  root->left = node;
}

/*
 * 将双向链表b链接到双向链表a的后面
 *
 * 注意： 此处a和b都是双向链表
 */
static void fib_heap_cat(fib_heap_node *a, fib_heap_node *b)
{
  struct fib_heap_cat tmp;
  tmp = a->right;
  a->right = b->right;
  b->right->left = a;
  b->right = tmp;
  tmp->left = b;
}

//插入结点
static void fib_heap_insert_node(struct fib_heap *heap, struct fib_heap_node *node)
{
  if (heap->num == 0) {
    heap->min = node;
  } else {
    fib_heap_add(heap->min, node);
    if (node->key < heap->min->key)
      heap->min = node;
  }
  heap->num++;
}
//删除结点
static struct fib_heap* fib_heap_delete_node(struct fib_heap *heap, struct fib_heap_node *node) {
  
}
//创建结点
static struct fib_heap_node* fib_heap_create_node(fib_heap_key key) {
  struct fib_heap_node *node = (struct fib_heap_node*)malloc(sizeof(struct fib_heap_node));
  if (node == NULL)
    return NULL;
  node->key = key;
  node->degree = 0;
  node->left = node->right = node;
  node->child = NULL;
  node->parent = NULL;
  return node;
}

/*
 * 将h1, h2合并成一个堆，并返回合并后的堆
 */
struct fib_heap_node* fib_heap_union(struct fib_heap *h1, struct fib_heap *h2)
{
  if (h1 == NULL)
    return h2;
  if (h2 == NULL)
    return h1;

  if (h1->max_degree < h2->max_degree) {
    tmp = h1;
    h1 = h2;
    h2 = tmp;
  }

  if (h1->min == NULL) {
    h1->min = h2->min;
    h1->num = h2->num;
    free(h2->cons);
  } else if(h2->min == NULL) {
    free(h2->cons);
  } else {
    fib_heap_cat(h1->min, h2->min);
    if (h1->min->key > h2->min->key) {
      h1->min = h2->min;
    }
    free(h2->cons);
  }
  return h1;
}
