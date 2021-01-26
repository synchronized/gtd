#include <stdio.h>
#include <stdlib.h>
#include "binomial_heap.h"

#define __binomial_heap_swap(a,b) (a^=b,b^=a,a^=b)

static void binomial_heap_update_key(struct binomial_heap_node *heap,
                                     struct binomial_heap_node *node, binomial_key key);

static void binomial_heap_increase_key(struct binomial_heap_node *heap,
                                       struct binomial_heap_node *node, binomial_key key);

static void binomial_heap_decrease_key(struct binomial_heap_node *heap,
                                       struct binomial_heap_node *node, binomial_key key);

/*
 * 将h1, h2中的根表合并成一个按度数递增的链表，返回合并后的根节点
 */
static struct binomial_heap_node* binomial_heap_merge(struct binomial_heap_node *h1, struct binomial_heap_node *h2)
{
  struct binomial_heap_node *head = NULL; //heap为指向新堆根结点
  struct binomial_heap_node **pos = &head;

  while(h1 && h2) {
    if (h1->degree < h2->degree) {
      *pos = h1;
      h1 = h1->next;
    } else {
      *pos = h2;
      h2 = h2->next;
    }
    pos = &(*pos)->next;
  }
  if (h1)
    *pos = h1;
  else
    *pos = h2;

  return head;
}
/*
 * 合并两个二项堆：将child合并到heap中
 */
static void binomial_heap_link(struct binomial_heap_node *child, struct binomial_heap_node *heap)
{
  child->parent = heap;
  child->next = heap->child;
  heap->child = child;
  heap->degree++;
}

/*
 * 反转二项堆heap
 */
static struct binomial_heap_node* binomial_heap_reverse(struct binomial_heap_node *heap)
{
  struct binomial_heap_node *next;
  struct binomial_heap_node *tail = NULL;

  if (heap == NULL)
    return NULL;

  heap->parent = NULL;
  while(heap->next) {
    next = heap->next;
    heap->next = tail;
    tail = heap;
    heap = next;
    heap->parent = NULL;
  }
  heap->next = NULL;

  return heap;
}

// 查找：在二项堆中查找键值为key的节点
struct binomial_heap_node* binomial_heap_search(struct binomial_heap_node *heap, binomial_key key)
{
  struct binomial_heap_node *child;
  struct binomial_heap_node *parent = heap;

  while(parent != NULL) {
    if (parent->key == key)
      return parent;

    if ((child = binomial_heap_search(heap->child, key)) != NULL)
      return child;

    parent = parent->next;
  }
  return NULL;
}

struct binomial_heap_node* binomial_heap_create(binomial_key key) {
  struct binomial_heap_node* node = (struct binomial_heap_node*)malloc(sizeof(struct binomial_heap_node));
  if (node == NULL) {
    return NULL;
  }
  node->key = key;
  node->parent = node->child = node->next = NULL;
  return node;
}

// 新建key对应的节点，并将其插入到二项堆中。
struct binomial_heap_node* binomial_heap_insert(struct binomial_heap_node *heap, binomial_key key)
{
  struct binomial_heap_node *node;
  if (binomial_heap_search(heap, key) != NULL) {
    printf("insert failed: already exists key:(%d)\n", key);
    return heap;
  }

  node = binomial_heap_create(key);
  if (node == NULL) {
    return heap;
  }
  return binomial_heap_union(heap, node);
}

// 删除节点：删除键值为key的节点，并返回删除节点后的二项树
struct binomial_heap_node* binomial_heap_delete(struct binomial_heap_node *heap, binomial_key key) {
  struct binomial_heap_node *node = binomial_heap_search(heap, key);
  if (node == NULL)
    return heap;

  // 将被删除的节点的数据数据上移到它所在的二项树的根节点
  struct binomial_heap_node *parent = node->parent;
  while(parent != NULL) {
    // TODO 交换结点数据
    __binomial_heap_swap(node->key, parent->key);
    node = parent;
    parent = node->parent;
  }

  // 找到node的前一个根节点(prev)
  struct binomial_heap_node **prev_next = &heap, *pos = heap;
  while(pos != node) {
    prev_next = &(pos->next);
    pos = pos->next;
  }
  // 移除node节点
  *prev_next = node->next;

  heap = binomial_heap_union(heap, binomial_heap_reverse(node->child));
  free(node);
  return heap;
}

// 将二项堆heap的键值oldkey更新为newkey
void binomial_heap_update(struct binomial_heap_node *heap, binomial_key oldkey, binomial_key newkey) {
  struct binomial_heap_node *node;
  node = binomial_heap_search(heap, oldkey);
  if (node == NULL)
    return;

  binomial_heap_update_key(heap, node, newkey);
}

// 合并二项堆：将h1, h2合并成一个堆，并返回合并后的堆
struct binomial_heap_node* binomial_heap_union(struct binomial_heap_node *h1, struct binomial_heap_node *h2)
{
  struct binomial_heap_node *heap = NULL;
  struct binomial_heap_node *prev_x, *x, *next_x;

  heap = binomial_heap_merge(h1, h2);
  if (heap == NULL)
    return NULL;

  prev_x = NULL;
  x = heap;
  next_x = x->next;

  while(next_x != NULL) {
    if (  (x->degree != next_x->degree)
          || (next_x->next != NULL && next_x->degree == next_x->next->degree))
    {
      // Case 1: x->degree != next_x->degree
      // Case 2: x->degree == next_x->degree == next_x->next->degree
      x = next_x;
      next_x = next_x->next;
    }
    else if(x->key < next_x->key)
    {
      // Case 3: x->degree == next_x->degree != next_x->next->degree
      //     && x->key < next_x->key
      x->next = next_x->next;
      binomial_heap_link(next_x, x);
    }
    else
    {
      // Case 4: x->degree == next_x->degree != next_x->next->degree
      //     && x->key > next_x->key
      if (prev_x == NULL)
        heap = next_x;
      else {
        prev_x->next = next_x;
      }
      binomial_heap_link(x, next_x);
      x = next_x;
    }
    next_x = x->next;
  }
  return heap;
}

/*
 * 获取二项堆中的最小根节点(*y)
 *
 * 参数说明：
 *     heap    -- 二项堆
 *     prev_y  -- [输出参数]最小根节点y的前一个根节点
 *     y       -- [输出参数]最小根节点
 */
void __binomial_heap_minimum(struct binomial_heap_node *heap,
                             struct binomial_heap_node **prev,
                             struct binomial_heap_node **node)
{
  struct binomial_heap_node *prev_x = NULL, *x = heap;
  *prev = NULL;
  *node = heap;

  while(x != NULL) {
    if ((*node)->key > x->key) {
      *node = x;
      *prev = prev_x;
    }
    prev_x = x;
    x = x->next;
  }
}

// 获取二项堆中的最小节点
struct binomial_heap_node* binomial_heap_minimum(struct binomial_heap_node *heap)
{
  struct binomial_heap_node *prev, *min;
  __binomial_heap_minimum(heap, &prev, &min);
  return min;
}

// 移除最小节点，并返回移除节点后的二项堆
struct binomial_heap_node* binomial_heap_extract_minimum(struct binomial_heap_node *heap)
{
  if (heap == NULL)
    return NULL;

  struct binomial_heap_node *prev, *min;
  // 找到"最小节点根y"和"它的前一个根节点prev_y"
  __binomial_heap_minimum(heap, &prev, &min);

  if (prev == NULL) // heap的根节点就是最小根节点
    heap = min->next;
  else // heap的根节点不是最小根节点
    prev->next = min->next;

  // 反转最小节点的左孩子，得到最小堆child；
  // 这样，就使得最小节点所在二项树的孩子们都脱离出来成为一棵独立的二项树(不包括最小节点)
  struct binomial_heap_node *child = binomial_heap_reverse(min->child);
  // 将"删除最小节点的二项堆child"和"heap"进行合并。
  heap = binomial_heap_union(heap, child);
  // 删除最小节点
  free(min);
  return heap;
}

/*
 * 更新二项堆heap的节点node的键值为key
 */
static void binomial_heap_update_key(struct binomial_heap_node *heap,
                                     struct binomial_heap_node *node, binomial_key key)
{
  if (node == NULL)
    return;

  if (key < node->key)
    binomial_heap_decrease_key(heap, node, key);
  else if(key > node->key)
    binomial_heap_increase_key(heap, node, key);
  else
    printf("No need to update!!!\n");
}

static void binomial_heap_decrease_key(struct binomial_heap_node *heap,
                                       struct binomial_heap_node *node, binomial_key key)
{
  if ((key >= node->key) || (binomial_heap_search(heap, key) != NULL)) {
    printf("decrease failed: the new key(%d) is existed already, \
                  or is no smaller than current key(%d)\n", key, node->key);
    return ;
  }
  node->key = key;

  struct binomial_heap_node *child = node;
  struct binomial_heap_node *parent = child->parent;
  while(parent != NULL && child->key > parent->key) {
    __binomial_heap_swap(child->key, parent->key);
    child = parent;
    parent = child->parent;
  }
}

static void binomial_heap_increase_key(struct binomial_heap_node *heap,
                                       struct binomial_heap_node *node, binomial_key key)
{
  if ((key >= node->key) || (binomial_heap_search(heap, key) != NULL)) {
    printf("decrease failed: the new key(%d) is existed already, \
                  or is no smaller than current key(%d)\n", key, node->key);
    return ;
  }

  node->key = key;

  struct binomial_heap_node *cur, *child, *least;
  cur = node;
  child = cur->child;
  while(child != NULL) {
    if (cur->key < child->key) {
      child = child->next;
      continue;
    }
    // 如果"当前节点" < "它的左孩子"，
    // 则在"它的孩子中(左孩子 和 左孩子的兄弟)"中，找出最小的节点；
    // 然后将"最小节点的值" 和 "当前节点的值"进行互换
    least = child;
    while(child->next != NULL) {
      child = child->next;
      if (least->key > child->key)
        least = child;
    }
    // 交换最小节点和当前节点的值
    __binomial_heap_swap(least->key, cur->key);

    // 交换数据之后，再对"原最小节点"进行调整，使它满足最小堆的性质：父节点 <= 子节点
    cur = least;
    child = cur->child;
  }
}
