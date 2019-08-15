
#ifndef _LEFTIST_TREE_H
#define _LEFTIST_TREE_H

typedef int leftist_tree_key;

struct leftist_tree_node {
  leftist_tree_key key; /* 关键字(键值) */
  int npl; /* 零路经长度(Null Path Length) */
  struct leftist_tree_node *left; /* 左孩子 */
  struct leftist_tree_node *right; /* 右孩子 */
};

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int leftist_tree_minimum(struct leftist_tree_node *heap, int *pval);
// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
struct leftist_tree_node* leftist_tree_merge(struct leftist_tree_node *x, struct leftist_tree_node *y);
// 将结点插入到左倾堆中，并返回根节点
struct leftist_tree_node* leftist_tree_insert(struct leftist_tree_node *heap, leftist_tree_key key);
// 删除结点(key为节点的值)，并返回根节点
struct leftist_tree_node* leftist_tree_delete(struct leftist_tree_node *heap);

// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
struct leftist_tree_node* leftist_tree_create(
                                              leftist_tree_key key,
                                              int npl,
                                              struct leftist_tree_node *left,
                                              struct leftist_tree_node *right);

// 销毁左倾堆
void leftist_tree_destroy(struct leftist_tree_node *heap);

#endif // _LEFTIST_TREE_H
