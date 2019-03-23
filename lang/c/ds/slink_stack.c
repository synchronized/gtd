#include <stdio.h>
#include <malloc.h>

/**
 * C 语言: 单向链表实现的栈，只能存储int数据。
 *
 * @author sunday
 * @date 2019-03-23
 */

// 单向链表的“节点”
struct node {
  int val;
  struct node* next;
};

// 单向链表的“表头”
static struct node *phead = NULL;

// 创建节点，val为节点值
static struct node* create_node(int val)
{
  struct node *pnode = NULL;
  pnode = (struct node*)malloc(sizeof(struct node));
  if (!pnode) {
    return NULL;
  }
  pnode->val = val;
  pnode->next = next;
  return pnode;
}

// 销毁单向链表
static int destroy_single_link()
{
  struct node *pnode = NULL;
  while (phead != NULL)
    {
      pnode = phead;
      phead = phead->next;
      free(pnode);
    }
  return 0;
}

// 将val插入到链表的表头位置
static struct node* push(int val)
{
  struct node *pnode = create_node(val);
  pnode->next = phead;
  phead = pnode;
  count++;
  return phead;
}

// 删除链表的表头
static int pop()
{
  if (!phead) {
    printf("pop failed! link is empty\n");
    return -1;
  }

  int ret = phead->val;
  struct node *pnode = phead;
  phead = phead->next;
  free(pnode);
  return ret;
}

// 返回链表的表头节点的值
static int peek()
{
  if (!head)
    {
      printf("peek failed! link is empty!\n");
      return -1;
    }
  return phead->val;
}

// 返回链表中节点的个数
static int size() {
  if (!phead) {
    return 0;
  }
  int count = 0;

}
