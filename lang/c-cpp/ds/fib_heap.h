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
  int key_num; // 堆中节点的总数
  int max_degree; // 最大度
  struct fib_heap_node *min; // 最小节点(某个最小堆的根节点)
  struct fib_heap_node **cons; // 最大度的内存区域
};

//创建堆
struct fib_heap* fib_heap_make();

//插入
void fib_heap_insert_key(struct fib_heap *heap, fib_heap_key key);

//删除
void fib_heap_delete(struct fib_heap *heap, fib_heap_key key);

//移除最小节点
void fib_heap_extract_min(struct fib_heap *heap);

//更新heap中的oldkey为newkey
void fib_heap_update(struct fib_heap *heap, fib_heap_key oldkey, fib_heap_key newkey);

//将h1, h2合并成一个堆，并且返回合并后的堆
struct fib_heap* fib_heap_union(struct fib_heap *h1, struct fib_heap *h2);

// 在斐波那契堆heap中是否存在键值为key的节点；存在返回1，否则返回0。
int fib_heap_contains(struct fib_heap *heap, fib_heap_key key);
// 获取最小节点对应的值(保存在pkey中)；成功返回1，失败返回0。
int fib_heap_get_min(struct fib_heap *heap, fib_heap_key *pkey);
// 销毁斐波那契堆
void fib_heap_destroy(struct fib_heap *heap);
// 打印"斐波那契堆"
void fib_print(struct fib_heap *heap);

#endif // __FIB_HEAP_H
