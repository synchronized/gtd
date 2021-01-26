/**
 * 希尔排序
 * @author sunday
 */

#include "stdio.h"

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

void print_array(int a[], int n) {
  for (int i=0; i<n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}


void sort_shell(int a[], int n)
{
  int gap,i,j,k,max;
  //循环每一次分gap
  for (gap=n/2;gap >= 1; gap=gap/2) {
    //循环每一组
    for (i=0; i<gap; i++) {
      //循环一组内部每一个元素
      for (j=i+gap; j<n; j=j+gap) {
        k = j;
        max = a[k];
        //这里的max相当于a[j]
        while (k>=gap && max < a[k-gap] ) {
          a[k] = a[k-gap];
          k-=gap;
        }
        a[k] = max;
      }
    }
  }
}

void main(void) {
  int a[] = {3, 9, 5, 7, 2, 6, 4, 1, 8};
  int len = LENGTH(a);
  print_array(a, len);
  sort_shell(a, len);
  print_array(a, len);
}
