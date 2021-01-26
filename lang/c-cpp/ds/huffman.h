
#ifndef __HUFFMAN
#define __HUFFMAN

typedef int huffman_key;

struct huffman_node{
  huffman_key key;
  struct huffman_node *left, *right, *parent;
};

/*
 * 创建Huffman树
 *
 * 参数说明：
 *     a 权值数组
 *     size 数组大小
 *
 * 返回值：
 *     Huffman树的根
 */
struct huffman_node* huffman_create(huffman_key data[], int size);

//霍夫曼树-销毁树
void huffman_destroy(struct huffman_node *node);

//前序遍历
void huffman_preorder(struct huffman_node *node);

#endif
