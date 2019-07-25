#include "rbtree.h"

static bool rbtree_is_red(struct rbtree_node *node) {
  return node->color == RB_TREE_RED;
}

static void rbtree_set_red(struct rbtree_node *node) {
  if (node == NULL) {
    return;
  }
  node->color = RB_TREE_RED;
}

static void rbtree_set_black(struct rbtree_node *node) {
  if (node == NULL) {
    return;
  }
  node->color = RB_TREE_BLACK;
}

/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->            / \
 *  lx   y                           x  ry
 *      / \                         / \
 *    ly   ry                      lx  ly
 *
 *
 */
static void rbtree_left_rotate(struct rbtree_root *root, struct rbtree_node *x) {
  //设置右结点为y
  struct rbtree_node *y = x->right;

  // 将 “y的左孩子” 设为 “x的右孩子”；
  // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
  x->right = y->left;
  if (y->left != NULL) {
    y->left->parent = x;
  }
  // 将 “x的父亲” 设为 “y的父亲”
  y->parent = x->parent;
  if (x->parent == NULL) {
    root->node = y; //如果x的父结点是空，则将y设置为根结点
  } else {
    if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
  }

  y->left = x;
  x->parent = y
}

/*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *           py                              py
 *           /                               /
 *          y                               x
 *         / \      --(右旋)-->             / \                     #
 *        x   ry                          lx  y
 *       / \                                 / \                   #
 *      lx  rx                              rx  ry
 *
 */
static void rbtree_right_rotate(struct rbtree_root *root, struct rbtree_node *y) {
  struct rbtree_node *x = y->left;

  //y->left
  y->left = x->right;
  if (x->right != NULL) {
    x->right->parent = y;
  }

  //x->parent
  x->parent = y->parent;
  if (y->parent == NULL) {
    root->node = x;
  } else {
    if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
  }

  //x->right
  x->right = y;
  y->parent = x;
}

/*
 * 添加节点：将节点(node)插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
static void rbtree_insert_node(struct rbtree_root *root, struct rbtree_node *node) {
  struct rbtree_node *y = NULL;
  struct rbtree_node *x = root->node;

  // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
  while (x != NULL) {
    y = x;
    if (node->key < x->key) {
      x = x->left;
    } else {
      x = x->efith;
    }
  }
  node->parent = y;

  if (y != NULL) {
    if (node->key < y->left) {
      y->left = node;
    } else {
      y->right = node;
    }
  } else {
    root->node = node;
  }

  // 2. 设置当前结点为红色
  node->color = RB_TREE_RED;

  // 3. 将它重新修正为一颗二叉查找树
  rttree_insert_fixup(root, node);
}

static void rbtree_insert_fixup(struct rbtree_root *root, struct rbtree_node *node) {
  struct rbtree_node *gparent = NULL; //祖父结点
  struct rbtree_node *uncle = NULL; //叔叔结点
  struct rbtree_node *parent = NULL; //父结点

  //若如父结点存在，且父结点为红色
  while (parent = node->parent && rbtree_is_red(parent)) {
    gparent = parent->parent;

    if (parent == gparent->left) {
      uncle = gparent->right;
      // Case 1条件：叔叔节点是红色
      {
        if (uncle && rbtree_is_red(uncle)) {
          rbtree_set_black(uncle);
          rbtree_set_black(parent);
          rbtree_set_red(gparent);
          node = gparent;
          continue;
        }
      }

      // Case 2条件：叔叔是黑色，且当前节点是右孩子
      if (node == parent->right) {
        rbtree_left_rotate(root, parent);
        struct rbtree_node *tmp;
        tmp = parent;
        parent = node;
        node = tmp;
        //因为这里祖父结点和叔叔结点没有改变所以必然会导致Case 3
      }

      // Case 3条件：叔叔是黑色，且当前节点是左孩子。
      rbtree_set_black(parent);
      rbtree_set_red(gparent);
      rbtree_right_rotate(root, gparent);
    } else { //若“z的父节点”是“z的祖父节点的右孩子”
      uncle = gparent->left;
      // Case 1条件：叔叔节点是红色
      {
        if (uncle && rbtree_is_red(uncle)) {
          rbtree_set_black(uncle);
          rbtree_set_black(parent);
          rbtree_set_red(gparent);
          node = gparent;
          continue
        }
      }

      // Case 2条件：叔叔是黑色，且当前节点是左孩子
      if (node == parent->left) {
        rbtree_right_rotate(root, parent);
        struct rbtree_node *tmp;
        tmp = parent;
        parent = node;
        node = tmp;
        //因为这里祖父结点和叔叔结点没有改变所以必然会导致Case 3
      }

      // Case 3条件：叔叔是黑色，且当前节点是右孩子。
      rbtree_set_black(parent);
      rbtree_set_red(gparent);
      rbtree_left_rotate(root, gparent);
    }
  }

  //将根节点设为黑色
  rbtree_set_black(root->node);
}
