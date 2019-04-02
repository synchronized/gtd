#include <stdio.h>
#include <malloc.h>

/**
 * C 语言: 数组实现的队列，只能存储int数据。
 *
 * @author sunday
 * @date 2019-03-25
 */

// 保存数据的数组
static int *arr = NULL;
// 队列的实际大小
static int count = 0;

// crate queue
int create_array_queue(int sz)
{
  arr = (int*)malloc(sz*sizeof(int));
  if (!arr)
    {
      printf("%s failed! malloc failed!", __func__);
      return -1;
    }

  count = 0;
  return 0;
}

// destroy queue
int destroy_array_queue()
{
  if (arr)
    {
      free(arr);
      arr = NULL;
    }

  return 0;
}

// append to queue tail
int add(int val)
{
  arr[count++] = val;
  return 0;
}

// return front for queue
int front()
{
  return arr[0];
}

// shift arr head
int pop()
{
  int i = 0;
  int ret = arr[0];
  count--;
  while ((i++)<count)
    {
      arr[i-1] = arr[i];
    }


  return ret;
}

//return size
int size()
{
  return count;
}

//return is empty
int is_empty()
{
  return count == 0;
}

void main() 
{
  int tmp=0;

  // 创建“队列”
  create_array_queue(12);

  // 将10, 20, 30 依次推入队列中
  add(10);
  add(20);
  add(30);

  // 将“队列开头的元素”赋值给tmp，并删除“该元素”
  tmp = pop();
  printf("tmp=%d\n", tmp);

  // 只将“队列开头的元素”赋值给tmp，不删除该元素.
  tmp = front();
  printf("tmp=%d\n", tmp);

  add(40);

  // 打印队列
  printf("is_empty()=%d\n", is_empty());
  printf("size()=%d\n", size());
  while (!is_empty())
    {
      printf("%d\n", pop());
    }

  // 销毁队列
  destroy_array_queue();
}

