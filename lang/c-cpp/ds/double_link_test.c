#include <stdio.h>
#include "double_link.h"

/**
 * C 语言实现的双向链表的测试程序。
 *
 * (01) int_test()
 *      演示向双向链表操作“int数据”。
 * (02) string_test()
 *      演示向双向链表操作“字符串数据”。
 * (03) object_test()
 *      演示向双向链表操作“对象”。
 *
 * @author sunday
 * @date 2019/03/23
 */

void dlink_test_insert(int index, void *pval) {
  int code = dlink_insert(index, pval);
  printf("dlink_insert(%d, pval) == %d\n", index, code);
}

void dlink_test_destroy() {
  int code = destroy_dlink();
  printf("destroy_dlink() == %d\n", code);
}

// 双向链表操作int数据
void int_test() {
  printf("--------------------------------\n");
  int iarr[4] = {10, 20, 30, 40};

  create_dlink(); //创建dlink

  dlink_test_insert(0, &iarr[0]);
  dlink_test_insert(0, &iarr[1]);
  dlink_test_insert(1, &iarr[2]);
  dlink_append_last(&iarr[3]);

  printf("dlink_is_empty()=%d\n", dlink_is_empty());    // 双向链表是否为空
  printf("dlink_size()=%d\n", dlink_size());            // 双向链表的大小

  create_dlink();
  int i;
  int *p;
  int sz = dlink_size();
  for (i=0; i<sz; i++) {
    p = (int*)dlink_get(i);
    printf("dlink_get(%d) == %d\n", i, *p);
  }

  dlink_test_destroy();
}

void str_test() {
  printf("--------------------------------\n");
  char* sarr[4] = {"ten", "twenty", "thirty", "forty"};

  create_dlink(); //创建dlink

  dlink_insert(0, sarr[0]);
  dlink_insert(0, sarr[1]);
  dlink_insert(0, sarr[2]);
  dlink_insert(0, sarr[3]);

  printf("dlink_is_empty()=%d\n", dlink_is_empty());    // 双向链表是否为空
  printf("dlink_size()=%d\n", dlink_size());            // 双向链表的大小

  int i;
  char *p;
  int sz = dlink_size();
  for (i=0; i<sz; i++) {
    p = (char*)dlink_get(i);
    printf("    dlink_get(%d) = \"%s\"\n", i, p);
  }

  destroy_dlink();
}

typedef struct tag_stu {
    int id;
    char name[20];
}stu;

void obj_test() {
  printf("--------------------------------\n");
  stu arr_stu[] = {
      {10, "sky"},
      {20, "jody"},
      {30, "vic"},
      {40, "dan"},
  };

  create_dlink(); //创建dlink

  dlink_insert(0, &arr_stu[0]);
  dlink_insert(0, &arr_stu[1]);
  dlink_insert(1, &arr_stu[2]);
  dlink_append_last(&arr_stu[3]);

  printf("dlink_is_empty()=%d\n", dlink_is_empty());    // 双向链表是否为空
  printf("dlink_size()=%d\n", dlink_size());            // 双向链表的大小

  int i;
  stu *p;
  int sz = dlink_size();
  for (i=0; i<sz; i++) {
    p = (stu*)dlink_get(i);
    printf("    dlink_get(%d) = {%d, \"%s\"}\n", i, p->id, p->name);
  }

  destroy_dlink();
}

int main() {
  int_test();
  str_test();
  obj_test();
  return 0;
}
