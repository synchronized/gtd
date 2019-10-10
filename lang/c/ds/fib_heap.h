#ifndef __FIB_HEAP_H
#define __FIB_HEAP_H

typedef int fib_heap_key ;

struct fib_heap_node {
  fib_heap_key key; // 关键字(键值)
  int degree; //度
  struct fib_heap_node *parent; // 父结点
  struct fib_heap_node *left; // 左兄弟结点
  struct fib_heap_node *right; // 右兄弟结点
  struct fib_heap_node *child; // 孩子结点
  int marked; // 是否被删除第1个孩子(1表示删除，0表示未删除)
};

struct fib_heap {
  int num; // 堆中节点的总数
  int max_degree; // 最大度
  struct fib_heap_node *min; // 最小节点(某个最小堆的根节点)
  struct fib_heap_node **cons; // 最大度的内存区域
};

//初始化
void fib_heap_init(struct fib_heap *heap);

//销毁
void fib_heap_destroy(struct fib_heap *heap);

//插入
void fib_heap_insert(struct fib_heap *heap, fib_heap_key key);

//删除
void fib_heap_delete(struct fib_heap *heap, fib_heap_key key);

#endif // __FIB_HEAP_H
