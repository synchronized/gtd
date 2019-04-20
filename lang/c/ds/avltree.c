
/**
 * C 语言: AVL树
 *
 * @author sunday
 * @date 2019-04-03
 */

#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

static int MIN (int X, int Y)
{
  return ((X) < (Y)) ? (X) : (Y);
}

static int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}

/*
 * 获取AVL树的高度
 */
int avltree_height(avltree *tree) {
  return HEIGHT(tree);
}

/*
 * 前序遍历"AVL树"
 */
void avltree_preorder(avltree *tree) {
  if (tree == NULL) {
    return;
  }
  printf("%d ", tree->key);
  avltree_preorder(tree->left);
  avltree_preorder(tree->right);
}

/*
 * 中序遍历"AVL树"
 */
void avltree_inorder(avltree *tree) {
  if (tree == NULL) {
    return;
  }
  avltree_inorder(tree->left);
  printf("%d ", tree->key);
  avltree_inorder(tree->right);
}

/*
 * 后序遍历"AVL树"
 */
void avltree_postorder(avltree *tree) {
  if (tree == NULL) {
    return;
  }
  avltree_postorder(tree->left);
  avltree_postorder(tree->right);
  printf("%d ", tree->key);
}
/*
 * (递归实现)查找"AVL树x"中键值为key的节点
 */
avlnode* avltree_search(avltree *tree, avltype key) {
  if (tree == NULL || key == tree->key) {
    return tree;
  }
  if (key < tree->key) {
    return avltree_search(tree->left, key);
  } else {
    return avltree_search(tree->right, key);
  }
}

/*
 * (非递归实现)查找"AVL树x"中键值为key的节点
 */
avlnode* avltree_search_iterative(avltree *tree, avltype key) {
  while (tree == NULL || key != tree->key) {
    if (key < tree->key) {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }
}

/*
 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
 */
avlnode* avltree_minimum(avltree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  avltree *node = tree;
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

/*
 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
 */
avlnode* avltree_maximum(avltree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  avltree *node = tree;
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
static avlnode* avltree_left_left_rotation(avltree *k2) {
  avltree *k1 = NULL;

  k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;

  k2->height = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
  k1->height = MAX(HEIGHT(k1->left), k2->height) + 1;

  return k1;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
static avlnode* avltree_right_right_rotation(avltree *k1) {
  avltree *k2 = NULL;

  k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;

  k1->height = MAX(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
  k2->height = MAX(k1->height, HEIGHT(k2->right)) + 1;
}

/*
 * LR：左右对应的情况(右单旋转左子结点,再左单旋)。
 *
 * 返回值：旋转后的根节点
 */
static avlnode* avltree_left_right_rotation(avltree *tree) {
  tree->left = avltree_right_right_rotation(tree->left);
  return avltree_left_left_rotation(tree);
}

/*
 * RL: 右左对应的情况(先左单旋右子结点,再右单旋)
 *
 */
static avlnode* avltree_right_left_rotation(avltree *tree) {
  tree->right = avltree_left_left_rotation(tree->right);
  return avltree_right_right_rotation(tree);
}

/*
 * 创建AVL树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     left 是左孩子。
 *     right 是右孩子。
 */
static avlnode* avltree_create_node(avltype key, avlnode *left, avlnode *right) {
  avlnode* pnode = (avlnode*)malloc(sizeof(avlnode));
  if (pnode == NULL) {
    return NULL;
  }
  pnode->key = key;
  pnode->height = 0;
  pnode->left = left;
  pnode->right = right;
  return pnode;
}

/*
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
avlnode* avltree_insert(avltree *tree, avltype key) {
  if (tree == NULL) {
    tree = avltree_create_node(key, NULL, NULL);
    if (tree == NULL) {
      printf("ERROR: create avltree node failed!\n");
      return NULL;
    }
  } else if (key < tree->key) {
    tree->left = avltree_insert(tree->left, key);
    if (HEIGHT(tree->left) - HEIGHT(tree->right) >= 2) {
      if (key < tree->left->key) {
        tree = avltree_left_left_rotation(tree);
      } else {
        tree = avltree_left_right_rotation(tree);
      }
    }
  } else if (key > tree->key) {
    tree->right = avltree_insert(tree->right, key);
    if (HEIGHT(tree->right) - HEIGHT(tree->left) >= 2) {
      if (key > tree->right->key) {
        tree = avltree_right_right_rotation(tree);
      } else {
        tree = avltree_right_left_rotation(tree);
      }
    }
  } else {
    printf("ERROR: can not insert exists key\n");
    return tree;
  }
  tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
}

/*
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     ptree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
static avlnode* avltree_delete_node(avltree *tree, avlnode *node) {
  // 根为空 或者 没有要删除的节点，直接返回NULL。
  if (tree == NULL || node == NULL) {
    return tree;
  }

  if (node->key < tree->key) { // 待删除的节点在"tree的左子树"中
    tree->left = avltree_delete_node(tree->left, node);
    // 删除节点后，若AVL树失去平衡，则进行相应的调节。
    if (HEIGHT(tree->right) - HEIGHT(tree->left) >= 2) {
      avlnode *r = tree->right;
      if (HEIGHT(r->left) > HEIGHT(r->right)) {
        tree = avltree_right_left_rotation(tree);
      } else {
        tree = avltree_right_right_rotation(tree);
      }
    }
  } else if (node->key > tree->key) { // 待删除的节点在"tree的右子树"中
    tree->right = avltree_delete_node(tree->right, node);
    // 删除节点后，若AVL树失去平衡，则进行相应的调节。
    if (HEIGHT(tree->left) - HEIGHT(tree->right) >= 2) {
      avlnode *l = tree->right;
      if (HEIGHT(l->left) > HEIGHT(l->right)) {
        tree = avltree_left_left_rotation(tree);
      } else {
        tree = avltree_left_right_rotation(tree);
      }
    }
  } else { // tree是对应要删除的节点。
    // tree的左右孩子都非空
    if (tree->left != NULL && tree->right != NULL) {
      if (HEIGHT(tree->left) > HEIGHT(tree->right)) {
        // 如果tree的左子树比右子树高；
        // 则(01)找出tree的左子树中的最大节点
        //   (02)将该最大节点的值赋值给tree。
        //   (03)删除该最大节点。
        // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
        // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
        avlnode *max = avltree_maximum(tree->left);
        tree->key = max->key;
        tree->left = avltree_delete_node(tree->left, max);
      } else {
        // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
        // 则(01)找出tree的右子树中的最小节点
        //   (02)将该最小节点的值赋值给tree。
        //   (03)删除该最小节点。
        // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
        // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
        avlnode *min = avltree_minimum(tree->right);
        tree->key = min->key;
        tree->right = avltree_delete_node(tree->right, min);
      }
    } else {
      avlnode *tmp = tree;
      tree = tree->left ? tree->left : tree->right;
      free(tmp);
    }
  }
  return tree;
}

/*
 * 删除结点(key是节点值)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 待删除的结点的键值
 * 返回值：
 *     根节点
 */
avlnode* avltree_delete(avltree *tree, avltype key) {
  avlnode *node = avltree_search(tree, key);
  if (node != NULL) {
    tree = avltree_delete_node(tree, node);
  }
  return tree;
}

/*
 * 销毁AVL树
 */
void avltree_destroy(avltree *tree) {
  if (tree == NULL) return;
  avltree_destroy(tree->left);
  avltree_destroy(tree->right);
  free(tree);
}

/*
 * 打印"AVL树"
 *
 * tree       -- AVL树的节点
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void avltree_print(avltree *tree, avltype key, int direction) {
  if (tree == NULL) {
    return;
  }

  if (direction == 0) { //root
    printf("%2d is root\n", tree->key);
  } else { //children
    printf("%2d is %2d %6s child\n", tree->key, key, direction==1 ? "right" : "left");
  }
  avltree_print(tree->left, tree->key, -1);
  avltree_print(tree->right, tree->key, 1);
}
