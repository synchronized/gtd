#include <stdio.h>

#define LENGTH(array) (sizeof(array)/sizeof(array[0]))

void print_array(int *a, int len) {
  int i;
  for (i=0; i<len; i++)
    printf("%d ", a[i]);
  printf("\n");
}

void sort_insert(int a[], int len) {
  int i, j, x;
  //从第二个元素开始遍历
  for (i=1; i<len; i++) {
    j = i;
    x = a[j];

    //便利每一个从1到i,把第i个元素插入到对应的位置
    //把比a[i](x)大的元素往右移动
    while (j>0 && x < a[j-1]) {
      //比较x和a[j-1]的大小，把大于x的元素都向右移动
      a[j] = a[j-1];
      j--;
    }
    if (j < i) {
      a[j] = x;
    }
  }

}

void main() {
  int a[] = {3, 10, 2, 7, 1, 6, 9, 5, 14};
  int len = LENGTH(a);

  print_array(a, len);
  sort_insert(a, len);
  print_array(a, len);
}
