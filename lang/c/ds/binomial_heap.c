#include "binomial_heap.h"

/*
 * 将h1, h2中的根表合并成一个按度数递增的链表，返回合并后的根节点
 */
static struct binomial_heap_node* binomial_heap_merge(struct binomial_heap_node *h1, binomial_heap_node *h2)
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
static struct binomial_heap_node* binomial_reverse(struct binomial_heap_node *heap)
{
  struct binomial_heap_node *next;
  struct binomial_heap_node *tail = NULL;

  if (heap == NULL)
    return;

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
  if (node == NULL) {
    return heap;
  }
}

// 将二项堆heap的键值oldkey更新为newkey
void binomial_heap_update(struct binomial_heap_node *heap, binomial_key oldkey, binomial_key newkey);

// 合并二项堆：将h1, h2合并成一个堆，并返回合并后的堆
struct binomial_heap_node* binomial_heap_union(struct binomial_heap_node *h1, binomial_heap_node *h2)
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

// 获取二项堆中的最小节点
struct binomial_heap_node* binomial_heap_minimum(struct binomial_heap_node *heap);

// 移除最小节点，并返回移除节点后的二项堆
struct binomial_heap_node* binomial_heap_extract_minimum(struct binomial_heap_node *heap);
