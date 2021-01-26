/**
 * 堆排序
 */
#include <stdio.h>

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

/*
 * 最大堆向下整理
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *     其中，N为数组下标索引值，如数组中第1个数对应的N为0。
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
void maxheap_down(int a[], int start, int end) {
  int c = start; // 当前(current)节点的位置
  int l = c*2+1; // 左(left)孩子的位置
  int max = a[c]; // 当前(current)节点的大小

  for (; l<= end; c=l,l=l*2+1) {
    // "l"是左孩子，"l+1"是右孩子
    if (l < end && a[l] < a[l+1])
      l++; // 左右两孩子中选择较大者，即m_heap[l+1]

    if (max > a[l]) {
      break;
    }

    a[c] = a[l];
    a[l] = max;
  }
}

/*
 * 堆排序(从小到大)
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     n -- 数组的长度
 */
void sort_heap(int a[], int n)
{
  int i;
  int tmp;
  // 从(n/2-1) --> 0逐次遍历。遍历之后，得到的数组实际上是一个(最大)二叉堆。
  for (i=n/2-1; i>=0; i--)
    maxheap_down(a, i, n);

  // 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
  for (i=n-1; i>0; i--) {
    // 交换a[0]和a[i]。交换后，a[i]是a[0...i]中最大的。
    tmp = a[i];
    a[i] = a[0];
    a[0] = tmp;

    maxheap_down(a, 0, i-1);
  }
}

void print_array(int a[], int n) {
  int i;
  for (i=0; i<n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void main() {
  int a[] = {3, 10, 2, 7, 1, 6, 9, 5, 14};
  int len = LENGTH(a);
  print_array(a, len);
  sort_heap(a, len);
  print_array(a, len);
}
