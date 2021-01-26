#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rbtree.h"

static int rbtree_get_color(struct rbtree_node *node);
static void rbtree_set_color(struct rbtree_node *node, int color);
static bool rbtree_is_red(struct rbtree_node *node);
static bool rbtree_is_black(struct rbtree_node *node);
static void rbtree_set_red(struct rbtree_node *node);
static void rbtree_set_black(struct rbtree_node *node);

static int rbtree_insert_node(struct rbtree_root *root, struct rbtree_node *node);
static void rbtree_destroy_node(struct rbtree_node *node);
static void rbtree_delete_node(struct rbtree_root *root, struct rbtree_node *node);
static void rbtree_preorder_node(struct rbtree_node *node);
static void rbtree_inorder_node(struct rbtree_node *node);
static void rbtree_postorder_node(struct rbtree_node *node);
static void rbtree_destroy_node(struct rbtree_node *node);
static void rbtree_insert_fixup(struct rbtree_root *root, struct rbtree_node *node);
static void rbtree_delete_fixup(struct rbtree_root *root, struct rbtree_node *node, struct rbtree_node *p);
static struct rbtree_node *rbtree_minimum_node(struct rbtree_node *tree);
static struct rbtree_node *rbtree_maximum_node(struct rbtree_node *tree);
static struct rbtree_node *rbtree_search_node(struct rbtree_node *node, rbtree_type key);
static struct rbtree_node *rbtree_create_node(
                                       rbtree_type key,
                                       struct rbtree_node* left,
                                       struct rbtree_node* right,
                                       struct rbtree_node* parent);


// 创建红黑树，返回"红黑树的根"！
struct rbtree_root *rbtree_create() {
  struct rbtree_root *root = (struct rbtree_root*)malloc(sizeof(struct rbtree_root));
  rbtree_init(root);
  if (root == NULL) {
    perror("红黑树创建失败");
  }
  return root;
}

void rbtree_init(struct rbtree_root *root) {
  if (root == NULL) {
    return;
  }
  memset(root, 0, sizeof(struct rbtree_root *));
}

// 销毁红黑树
void rbtree_destroy(struct rbtree_root *root) {
  if (root == NULL){
    return;
  }
  rbtree_destroy_node(root->node);
}

// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
int rbtree_insert(struct rbtree_root *root, rbtree_type key) {
  struct rbtree_node *node = rbtree_create_node(key, NULL, NULL, NULL);
  if (node == NULL) {
    return -1;
  }
  return rbtree_insert_node(root, node);
}

// 删除结点(key为节点的值)
void rbtree_delete(struct rbtree_root *root, rbtree_type key) {
  struct rbtree_node *node = rbtree_search(root, key);
  if (node == NULL) {
    return;
  }
  rbtree_delete_node(root, node);
}

// 前序遍历"红黑树"
void rbtree_preorder(struct rbtree_root *root) {
  if (root) {
    rbtree_preorder_node(root->node);
  }
}

// 中序遍历"红黑树"
void rbtree_inorder(struct rbtree_root *root) {
  if (root) {
    rbtree_inorder_node(root->node);
  }
}

// 后序遍历"红黑树"
void rbtree_postorder(struct rbtree_root *root) {
  if (root) {
    rbtree_postorder_node(root->node);
  }
}

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
struct rbtree_node *rbtree_search(struct rbtree_root *root, rbtree_type key) {
  if (root == NULL) {
    return NULL;
  }
  return rbtree_search_node(root->node, key);
}

// (非递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
struct rbtree_node *rbtree_search_iterative(struct rbtree_root *root, rbtree_type key) {
  if (root == NULL || root->node == NULL) {
    return NULL;
  }
  struct rbtree_node *node = root->node;
  while (node && key != node->key) {
    if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

/**
 * 最大结点
 * @param tree 要查找的树
 * @param key 输出参数-结果
 */
int rbtree_minimum(struct rbtree_root *root, int *key) {
  if (root == NULL) {
    return -1;
  }
  struct rbtree_node *node = rbtree_minimum_node(root->node);
  if (node == NULL) {
    return -1;
  }
  *key = node->key;
  return 0;
}

/**
 * 最大结点
 * @param tree 要查找的树
 * @param key 输出参数-结果
 */
int rbtree_maximum(struct rbtree_root *root, int *key) {
  if (root == NULL) {
    return -1;
  }
  struct rbtree_node *node = rbtree_maximum_node(root->node);
  if (node == NULL) {
    return -1;
  }
  *key = node->key;
  return 0;
}

// 创建红黑树-结点
static struct rbtree_node *rbtree_create_node(
                                       rbtree_type key,
                                       struct rbtree_node* left,
                                       struct rbtree_node* right,
                                       struct rbtree_node* parent)
{
  struct rbtree_node *node = (struct rbtree_node*)malloc(sizeof(struct rbtree_node));
  if (node != NULL) {
    node->key = key;
    node->left = left;
    node->right = right;
    node->parent = parent;
  }
  return node;
}

// 销毁红黑树-单个结点
static void rbtree_destroy_node(struct rbtree_node *node) {
  if (node == NULL) {
    return;
  }
  rbtree_destroy_node(node->left);
  rbtree_destroy_node(node->right);
}

static void rbtree_preorder_node(struct rbtree_node *node) {
  if (node == NULL) {
    return;
  }
  printf(" %d,", node->key);
  rbtree_preorder_node(node->left);
  rbtree_preorder_node(node->right);
}

static void rbtree_inorder_node(struct rbtree_node *node) {
  if (node == NULL) {
    return;
  }
  rbtree_preorder_node(node->left);
  printf(" %d,", node->key);
  rbtree_preorder_node(node->right);
}

static void rbtree_postorder_node(struct rbtree_node *node) {
  if (node == NULL) {
    return;
  }
  rbtree_preorder_node(node->left);
  rbtree_preorder_node(node->right);
  printf(" %d,", node->key);
}

static struct rbtree_node *rbtree_search_node(struct rbtree_node *node, rbtree_type key) {
  if (node == NULL) {
    return NULL;
  }
  if (key == node->key) {
    return node;
  }
  if (key < node->key) {
    return rbtree_search_node(node->left, key);
  } else {
    return rbtree_search_node(node->right, key);
  }
}

/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *       px                              px
 *       /                               /
 *     (x)                             (y)
 *     / \       --(左旋)-->            / \
 *   lx  (y)                         (x)  ry
 *       / \                         / \
 *     ly   ry                     lx   ly
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
  x->parent = y;
}

/*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *         py                              py
 *         /                               /
 *       (y)                             (x)
 *       / \      --(右旋)-->             / \
 *     (x)  ry                         lx  (y)
 *     / \                                 / \
 *   lx   rx                             rx   ry
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

/**
 * 添加节点：将节点(node)插入到红黑树中
 *
 * @param root 红黑树的根
 * @param node 插入的结点        // 对应《算法导论》中的z
 */
static int rbtree_insert_node(struct rbtree_root *root, struct rbtree_node *node) {
  struct rbtree_node *y = NULL;
  struct rbtree_node *x = root->node;

  // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
  while (x != NULL) {
    y = x;
    int a = node->key;
    int b = x->key;
    if (a < b) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  node->parent = y;

  if (y != NULL) {
    if (node->key == y->key) {
      return -1; //不能插入相等的值
    } else if (node->key < y->key) {
      y->left = node;
    } else {
      y->right = node;
    }
  } else {
    root->node = node;
  }

  // 2. 设置当前结点为红色
  node->color = RBTREE_RED;

  // 3. 将它重新修正为一颗二叉查找树
  rbtree_insert_fixup(root, node);
  return 0;
}

static void rbtree_insert_fixup(struct rbtree_root *root, struct rbtree_node *node) {
  struct rbtree_node *gparent = NULL; //祖父结点
  struct rbtree_node *uncle = NULL; //叔叔结点
  struct rbtree_node *parent = node->parent; //父结点

  //若如父结点存在，且父结点为红色
  while (rbtree_is_red(parent)) {
    parent = node->parent;
    gparent = parent->parent;

    if (parent == gparent->left) {
      uncle = gparent->right;
      /**
       * Case 1条件：叔叔节点是红色
       *  o -- 红色
       *  * -- 黑色
       *
       *              *(gparent)             (CURR)-> o(gparent)
       *             / \                             / \
       *    (parent)o   o(uncle)    -->     (parent)*   *(uncle)
       *             \                               \
       *     (CURR)-> o(node)                         o(node)
       */
      {
        if (uncle && rbtree_is_red(uncle)) {
          rbtree_set_black(uncle);
          rbtree_set_black(parent);
          rbtree_set_red(gparent);
          node = gparent;
          continue;
        }
      }

      /**
       * Case 2条件：叔叔是黑色，且当前节点是右孩子
       *  o -- 红色
       *  * -- 黑色
       *
       *              *(gparent)                      o(gparent)
       *             / \                             / \
       *    (parent)o   *(uncle)    -->       (node)o   *(uncle)
       *             \                             /
       *     (CURR)-> o(node)            (CURR)-> o(parent)
       */
      if (node == parent->right) {
        rbtree_left_rotate(root, parent);
        struct rbtree_node *tmp;
        tmp = parent;
        parent = node;
        node = tmp;
        //因为这里祖父结点和叔叔结点没有改变所以必然会导致Case 3
      }

      /**
       * Case 3条件：叔叔是黑色，且当前节点是左孩子。
       *  o -- 红色
       *  * -- 黑色
       *
       *              *(gparent)                 (parent)*
       *             / \                                / \
       *    (parent)o   *(uncle)    -->  (CURR)->(node)o   o(gparent)
       *           /                                        \
       * (CURR)-> o(node)                                    *(uncle)
       */
      rbtree_set_black(parent);
      rbtree_set_red(gparent);
      rbtree_right_rotate(root, gparent);
    } else { //若“z的父节点”是“z的祖父节点的右孩子”
      uncle = gparent->left;
      /**
       * Case 1条件：叔叔节点是红色
       *  o -- 红色
       *  * -- 黑色
       *
       *              *(gparent)             (CURR)-> o(gparent)
       *             / \                             / \
       *     (uncle)o   o(parent)    -->     (uncle)*   *(parent)
       *               /                               /
       *     (CURR)-> o(node)                         o(node)
       */
      {
        if (uncle && rbtree_is_red(uncle)) {
          rbtree_set_black(uncle);
          rbtree_set_black(parent);
          rbtree_set_red(gparent);
          node = gparent;
          continue;
        }
      }

      /**
       * Case 2条件：叔叔是黑色，且当前节点是左孩子
       *  o -- 红色
       *  * -- 黑色
       *
       *              *(gparent)                      *(gparent)
       *             / \                             / \
       *     (uncle)*   o(parent)   -->      (uncle)*   o(node)
       *               /                                 \
       *     (CURR)-> o(node)                    (CURR)-> o(parent)
       */
      if (node == parent->left) {
        rbtree_right_rotate(root, parent);
        struct rbtree_node *tmp;
        tmp = parent;
        parent = node;
        node = tmp;
        //因为这里祖父结点和叔叔结点没有改变所以必然会导致Case 3
      }

      /**
       * Case 3条件：叔叔是黑色，且当前节点是右孩子。
       *  o -- 红色
       *  * -- 黑色
       *
       *              *(gparent)                      *(parent)
       *             / \                             / \
       *     (uncle)*   o(parent)   -->    (gparent)o   o(node) <-(CURR)
       *                 \                         /
       *         (CURR)-> o(node)          (uncle)*
       */
      rbtree_set_black(parent);
      rbtree_set_red(gparent);
      rbtree_left_rotate(root, gparent);
    }
  }

  //将根节点设为黑色
  rbtree_set_black(root->node);
}

/**
 * 最小结点
 */
static struct rbtree_node *rbtree_minimum_node(struct rbtree_node *tree) {
  if (tree == NULL) {
    return NULL;
  }

  struct rbtree_node *node = tree;
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

/**
 * 最大结点
 */
static struct rbtree_node *rbtree_maximum_node(struct rbtree_node *tree) {
  if (tree == NULL) {
    return NULL;
  }

  struct rbtree_node *node = tree;
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}

/**
 * 前驱结点
 */
static struct rbtree_node *rbtree_predecessor(struct rbtree_node *node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->left) {
    return rbtree_maximum_node(node->left);
  }

  struct rbtree_node *x = node;
  struct rbtree_node *y = node->parent;
  while (y != NULL && x != y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

/**
 * 后继结点
 */
static struct rbtree_node *rbtree_successor(struct rbtree_node *node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->right) {
    return rbtree_minimum_node(node->right);
  }

  struct rbtree_node *x = node;
  struct rbtree_node *y = node->parent;
  while (y != NULL && x != y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

/**
 * 删除结点
 */
static void rbtree_delete_node1(struct rbtree_root *root, struct rbtree_node *node) {
  struct rbtree_node *child = NULL;
  struct rbtree_node *parent = NULL;
  int color;

  // 被删除结点的"左右子结点都不为空"的情况
  if (node->left != NULL && node->right != NULL) {
    // 被删除结点的后继结点(称为"取代结点")
    // 用它来取代"被删除结点"的位置,然后再将"被删除结点"去掉
    struct rbtree_node *replace = node;
    // 获取后继结点
    replace = replace->right;
    while (replace->left != NULL) {
      replace = replace->left;
    }

    // "node结点"不是根结点(只有跟结点不存在父结点)
    if (node->parent != NULL) {
      if (node->parent->left == node) {
        node->parent->left = replace;
      } else {
        node->parent->right = replace;
      }
    } else {
      // "node结点"是根结点
      root->node = replace;
    }

    // child是"取代结点"的又孩子,  也就是需要“调整的结点”
    // “取代结点”肯定不存在左子结点! 因为他是一个后继结点
    child = replace->right;
    parent = replace->parent;
    // 保存"取代结点"的颜色
    color = replace->color;
    // "被删除结点"是“是它的后继结点的父结点”
    // 也就是说child结点没有左子结点
    if (parent == node) {
      parent = replace;
    } else {
      // child不为空
      if (child) {
        child->parent = parent;
      }
      parent->left = child;

      replace->right = node->right;
      node->right->parent = replace;
    }

    replace->parent = node->parent;
    replace->color = node->color;
    replace->left = node->left;
    node->left->parent = replace;

    if (color == RBTREE_BLACK) {
      rbtree_delete_fixup(root, child, parent);
    }
    free(node);
    return;
  }

  if (node->left != NULL) {
    child = node->left;
  } else {
    child = node->right;
  }
  parent = node->parent;
  // 保存"取代节点"的颜色
  color = node->color;
  if (child) {
    child->parent = parent;
  }
  // "node节点"不是根节点
  if (parent == NULL) {
    root->node = child;
  } else {
    if (parent->left == node) {
      parent->left = child;
    } else {
      parent->right = child;
    }
  }

  if (color == RBTREE_BLACK) {
    rbtree_delete_fixup(root, child, parent);
  }
  free(node);
}

/**
 * 删除结点
 */
static void rbtree_delete_node(struct rbtree_root *root, struct rbtree_node *node) {
  struct rbtree_node *replace = node;
  struct rbtree_node *child = NULL;
  struct rbtree_node *parent = NULL;
  // 如果被删除结点有连个子结点会很麻烦，但是后继结点不可能有两个子结点，
  // 所以可以考虑将后继结点替换被删除的芥蒂娜，然后将删除操作转化为删除“后继结点”操作
  if (node->left != NULL && node->right != NULL) {
    replace = rbtree_successor(node); //后继结点
  }
  parent = replace->parent;

  if (replace->left != NULL) {
    child = replace->left;
  } else {
    child = replace->right;
  }
  if (child) {
    child->parent = parent;
  }

  //如果被删除结点是根结点
  if (parent == NULL) {
    root->node = child;
  } else {
    if (parent->left == replace) {
      parent->left = child;
    } else {
      parent->right = child;
    }
  }

  //使用后继结点替换被删除的结点的内容,相当于将后继结点覆盖被删除的结点
  if (replace != node) {
    node->key = replace->key;
  }

  if (replace->color == RBTREE_BLACK) {
    rbtree_delete_fixup(root, child, parent);
  }
  free(replace);
}

static void rbtree_delete_fixup(struct rbtree_root *root, struct rbtree_node *node, struct rbtree_node *p) {
  struct rbtree_node *parent = p;
  struct rbtree_node *other;
  while((!node || rbtree_is_black(node)) && node != root->node) {
    if (parent->left == node) {
      other = parent->right;
      if (rbtree_is_red(other)) {
        /**
         * Case 1: x的兄弟w是红色的
         *     这样调整之后other结点一定是黑色
         *  o -- 红色
         *  * -- 黑色
         *
         *                 *(parent)                       *(other)
         *                / \                             / \
         * (CURR)->(node)*   o(other)   -->      (parent)o   *(or)
         *                  / \                         / \
         *             (ol)*   *(or)     (CURR)->(node)*   *(ol)<-(NEW other)
         */
        rbtree_set_black(other);
        rbtree_set_red(parent);
        rbtree_left_rotate(root, parent);
        other = parent->right;
      }
      if (rbtree_is_black(other->left) && rbtree_is_black(other->right)) {
        /**
         * Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
         *  o -- 红色
         *  * -- 黑色
         *
         *               *(gparent)                      *(gparent)
         *                \                               \
         *                 o(parent)              (CURR)-> o(parent)
         *                / \                             / \
         * (CURR)->(node)*   *(other)   -->        (node)*   o(other)
         *                  / \                             / \
         *             (ol)*   *(or)                   (ol)*   *(or)
         */
        rbtree_set_red(other);
        node = parent;
        parent = node->parent;
        continue;
      }
      if (rbtree_is_black(other->right)) {
        /**
         * Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
         *  o -- 红色
         *  * -- 黑色
         *
         *               *(gparent)                        *(gparent)
         *                \                                 \
         *                 *(parent)                         *(parent)
         *                / \                               / \
         * (CURR)->(node)*   *(other)   -->  (CURR)->(node)*   *(ol)
         *                  / \                               / \
         *             (ol)o   *(or)                    (oll)*   o(other)
         *                /                                       \
         *          (oll)*                                         *(or)
         */
        rbtree_set_black(other->left);
        rbtree_set_red(other);
        rbtree_right_rotate(root, other);
        other = parent->right;
        //这里变化之后必然出现第四种情况
      }
      /**
       * Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
       *    (CURR)结点会附带一个额外的黑色，所以需要在该结点所在的线路增加一个黑色的结点
       *    将other结点左旋过来后后other结点原来的路径会少一个黑色的结，需要将(or)改为黑色补充
       *  o -- 红色
       *  * -- 黑色
       *
       *               *(gparent)                        *(gparent)
       *                \                                 \
       *                 *(parent)                         *(other)
       *                / \                               / \
       * (CURR)->(node)*   *(other)   -->        (parent)*   *(or)
       *                  / \                           / \
       *             (ol)*   o(or)               (node)*   *(ol)
       */
      rbtree_set_color(other, rbtree_get_color(parent));
      rbtree_set_black(parent);
      rbtree_set_black(other->right);
      rbtree_left_rotate(root, parent);
      node = root->node;
      break;
    } else {
      other = parent->left;
      if (rbtree_is_red(other)) {
        /**
         * Case 1: x的兄弟w是红色的
         *  o -- 红色
         *  * -- 黑色
         *
         *           *(gparent)                         *(gparent)
         *            \                                  \
         *     (parent)*                           (other)*
         *            / \                                / \
         *    (other)o   *(node) <-(CURR)  -->      (ol)*   o(parent)
         *          / \                                    / \
         *     (ol)*   *(or)                          (or)*   *(node) <-(CURR)
         */
        rbtree_set_black(other);
        rbtree_set_red(parent);
        rbtree_right_rotate(root, parent);
        other = parent->left;
      }
      if (rbtree_is_black(other->left) && rbtree_is_black(other->right)) {
        /**
         * Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
         *     因为(CURR)结点会额外的携带一个黑色所以需要将other设置为黑色
         *
         *           *(gparent)                           *(gparent)
         *            \                                    \
         *     (parent)*                            (parent)* <-(CURR)
         *            / \                                  / \
         *    (other)*   *(node) <-(CURR)  -->     (other)o   *(node)
         *          / \                                  / \
         *     (ol)*   *(or)                        (ol)*   *(or)
         */
        rbtree_set_red(other);
        node = parent;
        parent = node->parent;
        continue;
      }
      if (rbtree_is_black(other->left)) {
        /**
         * Case 3: x的兄弟w是黑色的，并且w的右孩子是红色，左孩子为黑色。
         *
         *           *(gparent)                           *(gparent)
         *            \                                    \
         *     (parent)*                            (parent)*
         *            / \                                  / \
         *    (other)*   *(node) <-(CURR)  -->        (or)*   *(node) <-(CURR)
         *          / \                                  / \
         *     (ol)*   o(or)                     (other)o   *(orr)
         *              \                              /
         *               *(orr)                   (ol)*
         */
        rbtree_set_black(other->right);
        rbtree_set_red(other);
        rbtree_left_rotate(root, other);
        other = parent->left;
        //这里变化之后必然出现第四种情况
      }
      /**
       * Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
       *    (CURR)结点会附带一个额外的黑色，所以需要在该结点所在的线路增加一个黑色的结点
       *    将other结点左旋过来后后other结点原来的路径会少一个黑色的结，需要将(or)改为黑色补充
       *  o -- 红色
       *  * -- 黑色
       *
       *          *(gparent)                         *(gparent)
       *           \                                  \
       *    (parent)*                                  *(other)
       *           / \                                / \
       *   (other)*   *(node) <-(CURR)   -->     (ol)*   *(parent)
       *         / \                                    / \
       *    (ol)o   *(or)                          (or)*   *(node)
       */
      rbtree_set_color(other, rbtree_get_color(parent));
      rbtree_set_black(parent);
      rbtree_set_black(other->left);
      rbtree_right_rotate(root, parent);
      node = root->node;
      break;
    }
  }
  rbtree_set_black(node);
}

/**
 * 返回结点的颜色
 * @param node 要判断的结点
 * @return 结点的颜色
 */
static int rbtree_get_color(struct rbtree_node *node) {
  if (node == NULL) {
    return RBTREE_BLACK;
  }
  return node->color;
}

/**
 * 设置结点的颜色
 * @param node 要判断的结点
 * @param color 颜色
 */
static void rbtree_set_color(struct rbtree_node *node, int color) {
  if (node != NULL) {
    node->color = color;
  }
}

/**
 * 判断结点是否是-红色
 * @param node 要判断的结点
 * @return 是否是红色
 */
static bool rbtree_is_red(struct rbtree_node *node) {
  return rbtree_get_color(node) == RBTREE_RED;
}

/**
 * 判断结点是否是-黑色
 * @param node 要判断的结点
 * @return 是否是黑色
 */
static bool rbtree_is_black(struct rbtree_node *node) {
  return rbtree_get_color(node) == RBTREE_BLACK;
}

/**
 * 设置结点的颜色为-红色
 * @param node 要设置的结点
 */
static void rbtree_set_red(struct rbtree_node *node) {
  rbtree_set_color(node, RBTREE_RED);
}

/**
 * 设置结点的颜色为-黑色
 * @param node 要设置的结点
 */
static void rbtree_set_black(struct rbtree_node *node) {
  rbtree_set_color(node, RBTREE_BLACK);
}
