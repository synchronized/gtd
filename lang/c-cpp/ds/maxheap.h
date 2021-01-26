#ifndef __MAX_HEAP
#define __MAX_HEAP

#define MAXHEAP_INCRE_STEP 10

struct maxheap_struct {
  int *root;
  int len;
  int size;
};

/*
 * 创建最大堆
 */
int maxheap_create(struct maxheap_struct *max_heap, int len);

/*
 * 将data插入到二叉堆中
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
int maxheap_insert(struct maxheap_struct *max_heap, int data);

/*
 * 删除最大堆中的data
 *
 * 返回值：
 *      0，成功
 *     -1，失败
 */
int maxheap_remove(struct maxheap_struct *max_heap, int data);

#endif
