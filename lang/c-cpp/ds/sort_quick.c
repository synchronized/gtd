/**
 * 快速排序：C 语言
 *
 * @author sunday
 * @date 2019/11/22
 */

#include <stdio.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

void print_array(int *a, int len) {
  int i;
  for (i=0; i<len; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void sort_quick(int a[], int l, int r) {
  int i, j, x;
  if (l < r) {
    i = l;
    j = r;
    x = a[i];
    while (i < j) {
      while (i < j && x < a[j])
        j--; //从右往左,找到第一个比x小的数
      if (i < j)
        a[i] = a[j]; //这个时候x代表a[j],相当于a[i],a[j]互换了
      while (i < j && x > a[i])
        i++; //从左往右,找到第一个比x大的数
      if (i < j)
        a[j] = a[i]; //这个时候x代表a[i],相当于a[i],a[j]互换了
    }
    a[i] = x;
    sort_quick(a, l, i-1);
    sort_quick(a, i+1, r);
  }
}

void main() {
  int a[] = {3, 10, 2, 7, 1, 6, 9, 5, 14};
  int len = LENGTH(a);
  print_array(a, len);
  sort_quick(a, 0, len-1);
  print_array(a, len);
}
