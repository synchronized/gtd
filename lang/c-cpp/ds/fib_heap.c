#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "fib_heap.h"

#if 0
#define LOG2(x) ({ \
      unsigned int _i = 0;                              \
      __asm__("bsr %1, %0" : "=r" (_i) : "r" ((x)));    \
      _i; })
#else   // 注意：通过gcc编译时，要添加 -lm 选项。
#define LOG2(x) ((log((double)(x))) / (log(2.0)))
#endif

static struct fib_heap_node* fib_heap_search(struct fib_heap *heap, fib_heap_key key);

/*
 * 将node从双链表移除
 */
static void fib_heap_remove(struct fib_heap_node *node) {
  node->left->right = node->right;
  node->right->left = node->left;
}

/*
 * 将"单个节点node"加入"链表root"之前
 *   a …… root
 *   a …… node …… root
 *
 * 注意： 此处node是单个节点，而root是双向链表
 */
static void fib_heap_add(struct fib_heap_node *root, struct fib_heap_node *node)
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
static void fib_heap_cat(struct fib_heap_node *a, struct fib_heap_node *b)
{
  struct fib_heap_node *tmp;
  tmp = a->right;
  a->right = b->right;
  b->right->left = a;
  b->right = tmp;
  tmp->left = b;
}

struct fib_heap* fib_heap_make() {
  struct fib_heap *heap;
  heap = (struct fib_heap*)malloc(sizeof(struct fib_heap));
  if (heap == NULL) {
    printf("Error: make fib heap failed\n");
    return NULL;
  }

  heap->key_num = 0;
  heap->max_degree = 0;
  heap->min = NULL;
  heap->cons = NULL;
  return heap;
}

/**
 * 创建节点
 */
static struct fib_heap_node* fib_heap_make_node(fib_heap_key key) {
  struct fib_heap_node *node;
  node = (struct fib_heap_node*)malloc(sizeof(struct fib_heap_node));
  if (node == NULL) {
    printf("Error: make Node failed\n");
    return NULL;
  }

  node->key = key;
  node->degree = 0;
  node->left = node;
  node->right = node;
  node->parent = NULL;
  node->child = NULL;

  return  node;
}

/*
 * 将节点node插入到斐波那契堆heap中
 */
static void fib_heap_insert_node(struct fib_heap *heap, struct fib_heap_node *node)
{
  if (heap->key_num == 0) {
    heap->min = node;
  } else {
    fib_heap_add(heap->min, node);
    if (node->key < heap->min->key)
      heap->min = node;
  }
  heap->key_num++;
}

/*
 * 新建键值为key的节点，并将其插入到斐波那契堆中
 */
void fib_heap_insert_key(struct fib_heap *heap, fib_heap_key key) {
  struct fib_heap_node *node;
  if (heap == NULL)
    return;

  node = fib_heap_make_node(key);
  if (node == NULL)
    return;

  fib_heap_insert_node(heap, node);
}

/*
 * 将h1, h2合并成一个堆，并返回合并后的堆
 */
struct fib_heap* fib_heap_union(struct fib_heap *h1, struct fib_heap *h2)
{
  if (h1 == NULL)
    return h2;
  if (h2 == NULL)
    return h1;

  if (h1->max_degree < h2->max_degree) {
    struct fib_heap *tmp = h1;
    h1 = h2;
    h2 = tmp;
  }

  if (h1->min == NULL) {
    h1->min = h2->min;
    h1->key_num = h2->key_num;
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
 * 将"堆的最小结点"从根链表中移除，
 * 这意味着"将最小节点所属的树"从堆中移除!
 */
static struct fib_heap_node* fib_heap_remove_min(struct fib_heap *heap) {
  struct fib_heap_node *min = heap->min;

  if (heap->min == min->right) {
    heap->min = NULL;
  } else {
    fib_heap_remove(min);
    heap->min = min->right;
  }
  min->left = min->right = min;

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
  heap->max_degree = LOG2(heap->key_num) + 1;

  //如果原本空间不够,则再次分配内存
  if (old >= heap->max_degree)
    return;

  //因为度为heap->max_degree可能被合并,所以要max_degree+1
  heap->cons = (struct fib_heap_node **)realloc(heap->cons,
                                                sizeof(struct fib_heap_node *)
                                                * (heap->max_degree + 1));
}

//合并斐波那契堆的根链表中左右相同的度数的数
static void fib_heap_consolidate(struct fib_heap *heap) {
  int i, d, D;
  struct fib_heap_node *x, *y, *tmp;

  fib_heap_cons_make(heap); //开辟哈希所用空间
  D = heap->max_degree + 1;

  for (i = 0; i< D; i++)
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
    heap->cons[d] = x;
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

/*
 * 移除最小节点，并返回移除节点后的斐波那契堆
 */
static struct fib_heap_node* _fib_heap_extract_min(struct fib_heap *heap) {
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
  heap->key_num--;
  return min;
}

void fib_heap_extract_min(struct fib_heap *heap) {
  struct fib_heap_node *node;
  if (heap == NULL || heap->min == NULL)
    return;

  node = _fib_heap_extract_min(heap);
  if (node != NULL)
    free(node);
}

/*
 * 在斐波那契堆heap中是否存在键值为key的节点；存在返回1，否则返回0。
 */
int fib_heap_get_min(struct fib_heap *heap, fib_heap_key *pkey) {
  if (heap==NULL || heap->min==NULL || pkey==NULL)
    return 0;
  *pkey = heap->min->key;
  return 1;
}

/**
 * 修改度数
 */
static void renew_degree(struct fib_heap_node *parent, int degree) {
  parent->degree -= degree;
  if (parent->parent != NULL)
    renew_degree(parent->parent, degree);
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
static void fib_heap_decrease(struct fib_heap *heap, struct fib_heap_node *node, fib_heap_key key) {
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
    fib_heap_remove(child); //将child从node的子链表中删除
    if (child->right == child)
      node->child = NULL;
    else
      node->child = node->right;

    fib_heap_add(heap->min, child); //将child添加到根链表中
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
        heap->min = right;
      right = right->right;
    }
  }
}

/*
 * 更新二项堆heap的节点node的键值为key
 */
void _fib_heap_update(struct fib_heap *heap, struct fib_heap_node *node, fib_heap_key key) {
  if (key < node->key)
    fib_heap_decrease(heap, node, key);
  else if(key > node->key)
    fib_heap_increase(heap, node, key);
  else
    printf("No need to update!!! \n");
}

void fib_heap_update(struct fib_heap *heap, fib_heap_key oldkey, fib_heap_key newkey) {
  struct fib_heap_node *node;
  if (heap == NULL)
    return;

  node = fib_heap_search(heap, oldkey);
  if (node != NULL)
    _fib_heap_update(heap, node, newkey);
}

/*
 * 在最小堆root中查找键值为key的节点
 */
static struct fib_heap_node* fib_heap_search_node(struct fib_heap_node *root, fib_heap_key key) {
  struct fib_heap_node *t = root; //临时节点
  struct fib_heap_node *p = NULL; //要查找的节点

  if (root == NULL)
    return root;

  do {
    if (t->key == key) {
      p = t;
      break;
    } else {
      if ((p = fib_heap_search_node(t->child, key)) != NULL)
        break;
    }
    t = t->right;
  } while (t != root);
  return p;
}

/*
 * 在斐波那契堆heap中查找键值为key的节点
 */
static struct fib_heap_node* fib_heap_search(struct fib_heap *heap, fib_heap_key key) {
  if (heap == NULL || heap->min == NULL)
    return NULL;

  return fib_heap_search_node(heap->min, key);
}

/*
 * 在斐波那契堆heap中是否存在键值为key的节点。
 * 存在返回1，否则返回0。
 */
int fib_heap_contains(struct fib_heap *heap, fib_heap_key key) {
  return fib_heap_search(heap, key) != NULL ? 1 : 0;
}

/*
 * 删除节点
 */
static void fib_heap_delete_node(struct fib_heap *heap, struct fib_heap_node *node) {
  fib_heap_key min = heap->min->key;
  fib_heap_decrease(heap, node, min-1);
  fib_heap_extract_min(heap);
  free(node);
}

void fib_heap_delete(struct fib_heap *heap, fib_heap_key key) {
  struct fib_heap_node *node;

  if (heap == NULL || heap->min == NULL) 
    return ;
  node = fib_heap_search(heap, key);
  if (node == NULL)
    return ;

  fib_heap_delete_node(heap, node);
}

/*
 * 销毁斐波那契堆
 */
void fib_heap_destroy_node(struct fib_heap_node *node) {
  struct fib_heap_node *start = node;
  if (node == NULL)
    return;

  do {
    fib_heap_destroy_node(node->child);
    //销毁node，并且指向下一个
    node = node->right;
    free(node->left);
  } while(node != start);
}

void fib_heap_destroy(struct fib_heap *heap) {
  fib_heap_destroy_node(heap->min);
  free(heap->cons);
  free(heap);
}

/*
 * 打印"斐波那契堆"
 *
 * 参数说明：
 *     node       -- 当前节点
 *     prev       -- 当前节点的前一个节点(父节点or兄弟节点)
 *     direction  --  1，表示当前节点是一个左孩子;
 *                    2，表示当前节点是一个兄弟节点。
 */
static void _fib_print(struct fib_heap_node *node, struct fib_heap_node *prev, int direction)
{
    struct fib_heap_node *start = node;

    if (node==NULL)
        return ;
    do
    {
        if (direction == 1)
            printf("%8d(%d) is %2d's child\n", node->key, node->degree, prev->key);
        else
            printf("%8d(%d) is %2d's next\n", node->key, node->degree, prev->key);

        if (node->child != NULL)
            _fib_print(node->child, node, 1);

        // 兄弟节点
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

void fib_print(struct fib_heap *heap) {
    int i=0;
    struct fib_heap_node *p;

    if (heap==NULL || heap->min==NULL)
        return ;

    printf("== 斐波那契堆的详细信息: ==\n");
    p = heap->min;
    do {
        i++;
        printf("%2d. %4d(%d) is root\n", i, p->key, p->degree);

        _fib_print(p->child, p, 1);
        p = p->right;
    } while (p != heap->min);
    printf("\n");
}

