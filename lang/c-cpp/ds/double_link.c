#include "double_link.h"
#include <stdio.h>
#include <malloc.h>

/**
 * C 语言实现的双向链表，能存储任意数据。
 *
 * @author sunday
 * @date 2019/03/23
 */

typedef struct tag_node {
  struct tag_node *prev;
  struct tag_node *next;
  void *p;
} node;

// 表头，注意，表头不存放数据
static node *phead = NULL;
// 元素个数
static int count = 0;

// 新建结点,成功返回结点指针，否则，返回NULL
static node* create_node(void *pval) {
  node *pnode = NULL;
  pnode = (node*)malloc(sizeof(node));
  if (!pnode) {
    printf("create node error\n");
    return NULL;
  }
  pnode->prev = pnode->next = pnode;
  pnode->p = pval;
  return pnode;
}

//创double link,成功返回0，否则返回-1
int create_dlink() {
  //创建表头
  phead = create_node(NULL);
  if (!phead) {
    return -1;
  }
  count = 0;
  return 0;
}

//double link 是否为空,为空返回1,否则返回0
int dlink_is_empty() {
  return count == 0;
}

//返回double link的size
int dlink_size() {
  return count;
}

//返回double link中index所在的d结点,成功返回结点指针，否则返回NULL
static node* get_node(int index) {
  if (index < 0 || index >= count) {
    printf("%s failed! index out of bound\n", __func__);
    return NULL;
  }

  //正向查找
  if (index <= (count/2)) {
    int i = 0;
    node *pnode = phead->next;
    while ((i++) < index) {
      pnode = pnode->next;
    }
    return pnode;
  }

  //反向查找
  int j = 0;
  int rindex = count - index - 1;
  node *rnode = phead->prev;
  while ((j++) < rindex) {
    rnode = rnode->prev;
  }
  return rnode;
}

//获取double link第一个结点
static node* get_first_node() {
  return get_node(0);
}

//获取double link最后一个结点
static node* get_last_node() {
  return get_node(count-1);
}

// 获取“双向链表中第index位置的元素”。成功，返回节点值；否则，返回-1。
void* dlink_get(int index) {
  node *pindex = get_node(index);
  if (!pindex) {
    printf("%s failed!\n", __func__);
    return NULL;
  }
  return pindex->p;
}

// 获取“双向链表中第1个元素的值”
void* dlink_get_first() {
  return dlink_get(0);
}

// 获取“双向链表中最后1个元素的值”
void* dlink_get_last() {
  return dlink_get(count-1);
}

// 将“pval”插入到index位置。成功，返回0；否则，返回-1。
int dlink_insert(int index, void* pval) {
  if (index == 0) {
    return dlink_insert_first(pval);
  }

  //查找原结点
  node *pindex = get_node(index);
  if (!pindex) {
    return -1;
  }

  //创建结点
  node *pnode = create_node(pval);
  if (!pnode) {
    return -1;
  }

  pnode->prev = pindex->prev;
  pnode->next = pindex;
  pindex->prev->next = pnode;
  pindex->prev = pnode;

  //结点个数+1
  count++;

  return 0;
}

// 将“pval”插入到表头位置
int dlink_insert_first(void *pval) {
  node *pnode = create_node(pval);
  if (!pnode) {
    return -1;
  }

  pnode->prev = phead;
  pnode->next = phead->next;
  phead->next->prev = pnode;
  phead->next = pnode;
  count++;
  return 0;
}

// 将“pval”插入到末尾位置
int dlink_append_last(void *pval) {
  node *pnode = create_node(pval);
  if (!pnode) {
    return -1;
  }

  pnode->prev = phead->prev;
  pnode->next = phead;
  phead->prev->next = pnode;
  phead->prev = pnode;
  count++;
  return 0;
}

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1。
int dlink_delete(int index) {
  node *pindex = get_node(index);
  if (!pindex) {
    return -1;
  }
  pindex->prev->next = pindex->next;
  pindex->next->prev = pindex->prev;
  free(pindex);
  count--;
  return 0;
}

// 删除第一个节点
int dlink_delete_first() {
  return dlink_delete(0);
}

// 删除组后一个节点
int dlink_delete_last() {
  return dlink_delete(count-1);
}

// 销毁“双向链表”，成功，返回0；否则，返回-1
int destroy_dlink() {
  if (!phead) {
    printf("%s failed! dlink is null!\n", __func__);
    return -1;
  }
  node *curr = NULL;
  node *next = phead->next;
  while (phead != next) {
    curr = next;
    next = curr->next;
    free(curr);
  }

  free(phead);
  phead = NULL;
  count = 0;
  return 0;
}
