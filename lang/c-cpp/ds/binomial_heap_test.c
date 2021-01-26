/**
 * C语言实现的二项堆
 *
 * @author sunday
 * @date 2019/08/21
 */

#include <stdio.h>
#include "binomial_heap.h"
#include "ascii_tree_print.h"

#define DEBUG 1

#if DEBUG
#define log(x, ...)   printf(x, __VA_ARGS__)
#else
#define log(x, ...)
#endif

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

// 共7个 = 1+2+4
int a[] = {12,  7, 25, 15, 28,
           33, 41};
// 共13个 = 1+4+8
int b[] = {18, 35, 20, 42,  9,
           31, 23,  6, 48, 11,
           24, 52, 13 };

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  struct binomial_heap_node *node = (struct binomial_heap_node*)t;
  sprintf(buf, "%d(%d)", node->key, node->degree);
  *left = node->child;
  *right = node->next;
}

// 验证"二项堆的插入操作"
void test_insert()
{
    int i;
    int alen=LENGTH(a);
    struct binomial_heap_node * ha=NULL;

    // 二项堆ha
    printf("== 二项堆(ha)中依次添加: ");
    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        ha = binomial_heap_insert(ha, a[i]);
    }
    printf("\n");
    // 打印二项堆ha
    printf("== 二项堆(ha)的详细信息: \n");
    ascii_tree_print(ha, print_build_handler);
}

// 验证"二项堆的合并操作"
void test_union()
{
    int i;
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    struct binomial_heap_node *ha, *hb;

    ha=hb=NULL;

    // 二项堆ha
    printf("== 二项堆(ha)中依次添加: ");
    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        ha = binomial_heap_insert(ha, a[i]);
    }
    printf("\n");
    printf("== 二项堆(ha)的详细信息: \n");
    ascii_tree_print(ha, print_build_handler);

    // 二项堆hb
    printf("== 二项堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = binomial_heap_insert(hb, b[i]);
    }
    printf("\n");
    printf("== 二项堆(hb)的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);

    // 将"二项堆hb"合并到"二项堆ha"中。
    ha = binomial_heap_union(ha, hb);
    printf("== 合并ha和hb后的详细信息:\n");
    ascii_tree_print(ha, print_build_handler);
}

// 验证"二项堆的删除操作"
void test_delete()
{
    int i;
    int blen=LENGTH(b);
    struct binomial_heap_node * hb=NULL;

    // 二项堆hb
    printf("== 二项堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = binomial_heap_insert(hb, b[i]);
    }
    printf("\n");
    printf("== 二项堆(hb)的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);

    // 删除二项堆hb中的节点
    i = 20;
    hb = binomial_heap_delete(hb, i);
    printf("== 删除节点%d后的详细信息: \n", i);
    ascii_tree_print(hb, print_build_handler);
}

// 验证"二项堆的更新(减少)操作"
void test_decrease()
{
    int i;
    int blen=LENGTH(b);
    struct binomial_heap_node * hb=NULL;

    // 二项堆hb
    printf("== 二项堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = binomial_heap_insert(hb, b[i]);
    }
    printf("\n");
    printf("== 二项堆(hb)的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);

    // 将节点20更新为2
    binomial_heap_update(hb, 20, 2);
    printf("== 更新节点20->2后的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);
}

// 验证"二项堆的更新(增加)操作"
void test_increase()
{
    int i;
    int blen=LENGTH(b);
    struct binomial_heap_node * hb=NULL;

    // 二项堆hb
    printf("== 二项堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = binomial_heap_insert(hb, b[i]);
    }
    printf("\n");
    printf("== 二项堆(hb)的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);

    // 将节点6更新为20
    binomial_heap_update(hb, 6, 60);
    printf("== 更新节点6->60后的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);
}


void main()
{
    // 1. 验证"二项堆的插入操作"
    //test_insert();
    // 2. 验证"二项堆的合并操作"
    test_union();
    // 3. 验证"二项堆的删除操作"
    //test_delete();
    // 4. 验证"二项堆的更新(减少)操作"
    //test_decrease();
    // 5. 验证"二项堆的更新(增加)操作"
    //test_increase();
}
