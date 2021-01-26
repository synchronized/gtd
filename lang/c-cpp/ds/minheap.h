#ifndef __MIN_HEAP
#define __MIN_HEAP

#define MINHEAP_INCRE_STEP 10

struct minheap_struct {
  int *root;
  int len;
  int size;
};

/*
 * 创建最大堆
 */
int minheap_create(struct minheap_struct *min_heap, int len);

/*
 * 将data插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int minheap_insert(struct minheap_struct *min_heap, int data);

/*
 * 删除最大堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int minheap_remove(struct minheap_struct *min_heap, int data);

#endif
