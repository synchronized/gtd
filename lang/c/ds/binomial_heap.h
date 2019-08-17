/**
 * 二项堆-练习
 */

#ifndef __BINOMIAL_HEAP_H
#define __BINOMIAL_HEAP_H

typedef int binomial_key;

struct binomial_heap_node {
  binomial_key key; //键值
  int degree; //度数
  struct binomial_heap_node *parent; //父结点
  struct binomial_heap_node *child; //左孩子结点
  struct binomial_heap_node *next; //兄弟结点(这是一个链表)
};

// 新建key对应的节点，并将其插入到二项堆中。
struct binomial_heap_node* binomial_heap_insert(struct binomial_heap_node *heap, binomial_key key);
// 删除节点：删除键值为key的节点，并返回删除节点后的二项树
struct binomial_heap_node* binomial_heap_delete(struct binomial_heap_node *heap, binomial_key key);

// 将二项堆heap的键值oldkey更新为newkey
void binomial_heap_update(struct binomial_heap_node *heap, binomial_key oldkey, binomial_key newkey);

// 合并二项堆：将h1, h2合并成一个堆，并返回合并后的堆
struct binomial_heap_node* binomial_heap_union(struct binomial_heap_node *h1, binomial_heap_node *h2);

// 查找：在二项堆中查找键值为key的节点
struct binomial_heap_node* binomial_heap_search(struct binomial_heap_node *heap, binomial_key key);

// 获取二项堆中的最小节点
struct binomial_heap_node* binomial_heap_minimum(struct binomial_heap_node *heap);

// 移除最小节点，并返回移除节点后的二项堆
struct binomial_heap_node* binomial_heap_extract_minimum(struct binomial_heap_node *heap);

#endif //__BINOMIAL_HEAP_H
