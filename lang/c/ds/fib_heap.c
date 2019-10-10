#include "stdlib.h"
#include "math.h"
#include "fib_heap.h"

//销毁结点
static void fib_heap_destory_node(struct fib_heap_node *node);
//将"单个节点node"加入"链表root"之前
static void fib_heap_add(fib_heap_node *root, fib_heap_node *node);
//链接两个双链表
static void fib_heap_cat(fib_heap_node *a, fib_heap_node *b);
//插入结点
static void fib_heap_insert_node(struct fib_heap *heap, struct fib_heap_node *node);
//删除结点
static struct fib_heap* fib_heap_delete_node(struct fib_heap *heap, struct fib_heap_node *node);
//创建结点
static struct fib_heap_node* fib_heap_create_node(fib_heap_key key);

static struct fib_heap_node* fib_heap_union(struct fib_heap_node *a, struct fib_heap_node *b);

//初始化
void fib_heap_init(struct fib_heap *heap)
{
  if (heap == NULL)
    return;

  heap->num = 0;
  heap->max_degree = 0;
  heap->min = NULL;
  heap->cons = NULL;
}


//销毁
void fib_heap_destroy(struct fib_heap *heap);

//插入
void fib_heap_insert(struct fib_heap *heap, fib_heap_key key);

//删除
void fib_heap_delete(struct fib_heap *heap, fib_heap_key key);


//销毁结点
static void fib_heap_destory_node(struct fib_heap_node *node);

/*
 * 将"单个节点node"加入"链表root"之前
 *   a …… root
 *   a …… node …… root
 *
 * 注意： 此处node是单个节点，而root是双向链表
 */
static void fib_heap_add(fib_heap_node *root, fib_heap_node *node)
{
  node->left = root->left;
  root->left->right = node;
  node->right = root;
  root->left = node;
}

/*
 * 将双向链表b链接到双向链表a的后面
 *
 * 注意： 此处a和b都是双向链表
 */
static void fib_heap_cat(fib_heap_node *a, fib_heap_node *b)
{
  struct fib_heap_cat *tmp;
  tmp = a->right;
  a->right = b->right;
  b->right->left = a;
  b->right = tmp;
  tmp->left = b;
}

//插入结点
static void fib_heap_insert_node(struct fib_heap *heap, struct fib_heap_node *node)
{
  if (heap->num == 0) {
    heap->min = node;
  } else {
    fib_heap_add(heap->min, node);
    if (node->key < heap->min->key)
      heap->min = node;
  }
  heap->num++;
}
//删除结点
static struct fib_heap* fib_heap_delete_node(struct fib_heap *heap, struct fib_heap_node *node) {
  
}
//创建结点
static struct fib_heap_node* fib_heap_create_node(fib_heap_key key) {
  struct fib_heap_node *node = (struct fib_heap_node*)malloc(sizeof(struct fib_heap_node));
  if (node == NULL)
    return NULL;
  node->key = key;
  node->degree = 0;
  node->left = node->right = node;
  node->child = NULL;
  node->parent = NULL;
  return node;
}

/*
 * 将h1, h2合并成一个堆，并返回合并后的堆
 */
struct fib_heap_node* fib_heap_union(struct fib_heap *h1, struct fib_heap *h2)
{
  if (h1 == NULL)
    return h2;
  if (h2 == NULL)
    return h1;

  if (h1->max_degree < h2->max_degree) {
    tmp = h1;
    h1 = h2;
    h2 = tmp;
  }

  if (h1->min == NULL) {
    h1->min = h2->min;
    h1->num = h2->num;
    free(h2->cons);
    free(h2);
  } else if(h2->min == NULL) {
    free(h2->cons);
    free(h2);
  } else {
    fib_heap_cat(h1->min, h2->min);
    if (h1->min->key > h2->min->key) {
      h1->min = h2->min;
    }
    free(h2->cons);
    free(h2);
  }
  return h1;
}
/*
 * 将node从双链表移除
 */
static void fib_heap_remove(struct fib_heap_node *node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

/*
 * 移除最小节点，并返回移除节点后的斐波那契堆
 */
static struct fib_heap_node* fib_heap_extract_min(struct fib_heap *heap) {
    if (heap == NULL || heap->min == NULL)
        return NULL;

    struct fib_heap_node *child = NULL;
    struct fib_heap_node *min = heap->min;

    //将min每一个儿子(儿子和儿子的兄弟)都添加到“斐波那契堆的根链表”中
    while (min->child != NULL) {
      child = min->child;
      fib_heap_remove(child);
      if (child->right == child)
        min->child = NULL;
      else
        min->child = child->right;

      fib_heap_add(heap->min, child);
      child->parent = NULL;
    }

    //将min 从根链表中移除
    fib_heap_remove(min);
    // 若min是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(min->right)，然后再进行调节。
    if (min->right == min) {
      heap->min = NULL;
    } else {
      heap->min = min->right;
      fib_heap_consolidate(heap);
    }
    heap->keyNum--;
    return min;
}

//将node链接到root根节点
static void fib_heap_link(struct fib_heap *heap, struct fib_heap_node *node, struct fib_heap_node *root) {
  //将node从双链表移除
  fib_heap_remove(node);
  //将node设置为root的孩子
  if (root->child == NULL)
    root->child = node;
  else
    fib_heap_add(root->child, node);

  node->parent = root;
  root->degree++;
  node->marked = 0;
}

//创建fib_heap_consolidate所需空间
static void fib_heap_cons_make(struct fib_heap *heap) {
  int old = heap->max_degree;

  //计算log2(x), "+1"意味着向上取整
  //ex. log2(13) = 3, 向上取整为3+1=4
  heap->max_degree = (int)log2l(heap->num) + 1;

  //如果原本空间不够,则再次分配内存
  if (old >= heap->max_degree)
    return;

  //因为度为heap->max_degree可能被合并,所以要max_degree+1
  heap->cons = (struct fib_heap_node **)realloc(heap->cons,
                                                sizeof(struct fib_heap_node *)
                                                * (heap->maxDegree + 1));
}

//取出最小的树(最小节点所在的树)
static struct fib_heap_node* fib_heap_remove_min(struct fib_heap *heap) {
  /*TODO*/
  return NULL;
}

//合并斐波那契堆的根链表中左右相同的度数的数
static void fib_heap_consolidate(struct fib_heap *heap) {
  int i, d, D;
  struct fib_heap_node *x, *y, *tmp;

  fib_heap_cons_make(heap); //开辟哈希所用空间
  D = heap->max_degree + 1;

  for (i = ; i< D; i++)
    heap->cons[i] = NULL;

  //合并相同度的跟节点, 使每个度数的树唯一
  while (heap->min != NULL) {
    x = fib_heap_remove_min(heap); //取出堆中最小树(min所在的树)
    d = x->degree;
    //heap->cons[d] != NULL 意味着两个树(x和y)的“度数”相同
    while (heap->cons[d] != NULL) {
      y = heap->cons[d]; //y是与x度数相同的树
      //保证x的key比较小
      if (x->key > y->key) {
        tmp = x;
        x = y;
        y = tmp;
      }
      fib_heap_link(heap, y, x); //将y链接到x中
      heap->cons[d] = NULL;
      d++;
    }
    heap->cons[d] = x
  }
  heap->min = NULL;

  //将heap->cons中的节点重新加到根表中
  for (i = 0; i<D; i++) {
    if (heap->cons[i] != NULL) {
      if (heap->min == NULL) {
        heap->min = heap->cons[i];
      } else {
        fib_heap_add(heap->min, heap->cons[i]);
        if (heap->cons[i]->key < heap->min->key)
          heap->min = heap->cons[i];
      }
    }
  }
}

//将node从副节点parent的子链接中剥离出来
//并使node成为"堆的跟链表"中的一员
static void fib_heap_cut(struct fib_heap *heap, struct fib_heap_node *node, struct fib_heap_node *parent) {
  fib_heap_remove(node);
  renew_degree(parent, node->degree);
  //node 没有兄弟
  if (node == node->right)
    parent->child = NULL;
  else
    parent->child = node->right;

  node->parent = NULL;
  node->left = node->right = node;
  node->marked = 0;
  //将“node”所在树添加到“根链表”中
  fib_heap_add(heap->min, node);
}

/*
 * 对节点node进行"级联剪切"
 *
 * 级联剪切：如果减小后的结点破坏了最小堆性质，
 *     则把它切下来(即从所在双向链表中删除，并将
 *     其插入到由最小树根节点形成的双向链表中)，
 *     然后再从"被切节点的父节点"到所在树根节点递归执行级联剪枝
 */
static void fib_heap_cascading_cut(struct fib_heap *heap, struct fib_heap_node *node) {
  struct fib_heap_node *parent = node->parent;
  if (parent != NULL)
    return;

  if (node->marked == 0) {
    node->marked = 1;
  } else {
    fib_heap_cut(heap, node, parent);
    fib_heap_cascading_cut(heap, parent);
  }
}

/*
 * 将斐波那契堆heap中节点node的值减少为key
 */
static void fib_heap_decrease(struct fib_heap *heap, struct fib_heap_node *node, fib_heap_key) {
  struct fib_heap_node *parent;
  if (heap == NULL || heap->min == NULL || node == NULL)
    return;

  if (key >= node->key) {
    printf("decrease failed: the new key(%d) is no smaller than current key(%d)\n", key, node->key);
    return;
  }

  node->key = key;
  parent = node->parent;
  if (parent != NULL && node->key < parent->key) {
    //将node从副节点parent中剥离出来,并将node添加到根链表中
    fib_heap_cut(heap, node, parent);
    fib_heap_cascading_cut(heap, parent);
  }

  //更新最小节点
  if (node->key < heap->min->key)
    heap->min = node;
}

/* 
 * 将斐波那契堆heap中节点node的值增加为key
 */
static void fib_heap_increase(struct fib_heap *heap, struct fib_heap_node *node, fib_heap_key key) {
  struct fib_heap_node *child, *parent, *right;
  if (heap == NULL || heap->min == NULL || node == NULL)
    return;
  
  if (key <= node->key) {
    printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node->key);
    return;
  }

  //将node每一个儿子(不包括孙子，重孙,..)都添加到根链表中
  while (node->child != NULL) {
    child = node->child;
    fib_node_remove(child); //将child从node的子链表中删除
    if (child->right == child)
      node->child = NULL;
    else
      node->child = node->right;

    fib_node_add(heap->min, child); //将child添加到根链表中
    child->parent = NULL;
  }
  node->degree = 0;
  node->key = key;

  // 如果node不在根链表中，
  //     则将node从父节点parent的子链接中剥离出来，
  //     并使node成为"堆的根链表"中的一员，
  //     然后进行"级联剪切"
  // 否则，则判断是否需要更新堆的最小节点
  parent = node->parent;
  if (parent != NULL) {
    fib_heap_cut(heap, node, parent);
    fib_heap_cascading_cut(heap, parent);
  } else if (heap->min == node) {
    right = node->right;
    while(right != node) {
      if (node->key > right->key)
        heap->min = right
          right = right->right;
    }
  }
}

//删除节点
static void fib_heap_delete_node(struct fib_heap *heap, struct fib_heap_node *node) {
  fib_heap_key min = heap->min->key;
  fib_heap_decrease(heap, node, min-1);
  fib_heap_extract_min(heap);
  free(node);
}
