
#ifndef _LEFTIST_HEAP_H
#define _LEFTIST_HEAP_H

typedef int leftist_heap_key;

struct leftist_heap_node {
  leftist_heap_key key; /* 关键字(键值) */
  int npl; /* 零路经长度(Null Path Length) */
  struct leftist_heap_node *left; /* 左孩子 */
  struct leftist_heap_node *right; /* 右孩子 */
};

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int leftist_heap_minimum(struct leftist_heap_node *heap, int *pval);
// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
struct leftist_heap_node* leftist_heap_merge(struct leftist_heap_node *x, struct leftist_heap_node *y);
// 将结点插入到左倾堆中，并返回根节点
struct leftist_heap_node* leftist_heap_insert(struct leftist_heap_node *heap, leftist_heap_key key);
// 删除结点(key为节点的值)，并返回根节点
struct leftist_heap_node* leftist_heap_delete(struct leftist_heap_node *heap);

// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
struct leftist_heap_node* leftist_heap_create(
                                              leftist_heap_key key,
                                              int npl,
                                              struct leftist_heap_node *left,
                                              struct leftist_heap_node *right);

// 销毁左倾堆
void leftist_heap_destroy(struct leftist_heap_node *heap);

#endif // _LEFTIST_HEAP_H
