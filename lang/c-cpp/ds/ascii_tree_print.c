#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ascii_tree_print.h"

#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

//printing tree in ascii
typedef struct asciinode_struct asciinode;
typedef struct asciitree_context asciictx;

struct asciinode_struct
{
  asciinode * left, * right;

  //length of the edge from this node to its children
  int edge_length;

  int height;

  int lablen;

  //-1=I am left, 0=I am root, 1=right
  int parent_dir;

  //max supported unit32 in dec, 10 digits max
  char label[11];
};

struct asciitree_context
{
  int lprofile[MAX_HEIGHT];
  int rprofile[MAX_HEIGHT];
  int gap;
  int print_next;
  ascii_tree_build_handler build_handler;
};

//adjust gap between left and right nodes

//used for printing next node in the same level,
//this is the x coordinate of the next char printed

static int MIN (int X, int Y)
{
  return ((X) < (Y)) ? (X) : (Y);
}

static int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}

static asciictx * ascii_tree_create_context(ascii_tree_build_handler build_handler)
{
  asciictx *ctx = malloc(sizeof(asciictx));
  memset(ctx, 0, sizeof(asciictx));
  ctx->gap = 3;
  ctx->build_handler = build_handler;
  return ctx;
}


//Free all the nodes of the given tree
static void ascii_tree_free(asciinode *node)
{
  if (node == NULL) return;
  ascii_tree_free(node->left);
  ascii_tree_free(node->right);
  free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
static void compute_lprofile(asciictx *ctx, asciinode *node, int x, int y)
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  ctx->lprofile[y] = MIN(ctx->lprofile[y], x-((node->lablen-isleft)/2));
  if (node->left != NULL)
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
    {
	    ctx->lprofile[y+i] = MIN(ctx->lprofile[y+i], x-i);
    }
  }
  compute_lprofile(ctx, node->left, x-node->edge_length-1, y+node->edge_length+1);
  compute_lprofile(ctx, node->right, x+node->edge_length+1, y+node->edge_length+1);
}

static void compute_rprofile(asciictx *ctx, asciinode *node, int x, int y)
{
  int i, notleft;
  if (node == NULL) return;
  notleft = (node->parent_dir != -1);
  ctx->rprofile[y] = MAX(ctx->rprofile[y], x+((node->lablen-notleft)/2));
  if (node->right != NULL)
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
    {
	    ctx->rprofile[y+i] = MAX(ctx->rprofile[y+i], x+i);
    }
  }
  compute_rprofile(ctx, node->left, x-node->edge_length-1, y+node->edge_length+1);
  compute_rprofile(ctx, node->right, x+node->edge_length+1, y+node->edge_length+1);
}

//This function fills in the edge_length and
//height fields of the specified tree
static void compute_edge_lengths(asciictx *ctx, asciinode *node)
{
  int h, hmin, i, delta;
  if (node == NULL) return;
  compute_edge_lengths(ctx, node->left);
  compute_edge_lengths(ctx, node->right);

  /* first fill in the edge_length of node */
  if (node->right == NULL && node->left == NULL)
  {
	  node->edge_length = 0;
  }
  else
  {
    if (node->left != NULL)
    {
	    for (i=0; i<node->left->height && i < MAX_HEIGHT; i++)
      {
		    ctx->rprofile[i] = -INFINITY;
	    }
	    compute_rprofile(ctx, node->left, 0, 0);
	    hmin = node->left->height;
    }
    else
    {
	    hmin = 0;
    }
	  if (node->right != NULL)
    {
	    for (i=0; i<node->right->height && i < MAX_HEIGHT; i++)
      {
		    ctx->lprofile[i] = INFINITY;
	    }
	    compute_lprofile(ctx, node->right, 0, 0);
	    hmin = MIN(node->right->height, hmin);
    }
    else
    {
	    hmin = 0;
    }
	  delta = 4;
	  for (i=0; i<hmin; i++)
    {
	    delta = MAX(delta, ctx->gap + 1 + ctx->rprofile[i] - ctx->lprofile[i]);
    }

    //If the node has two children of height 1, then we allow the
    //two leaves to be within 1, instead of 2
	  if (((node->left != NULL && node->left->height == 1) ||
	      (node->right != NULL && node->right->height == 1))&&delta>4)
    {
      delta--;
    }

    node->edge_length = ((delta+1)/2) - 1;
  }

  //now fill in the height of node
  h = 1;
  if (node->left != NULL)
  {
	  h = MAX(node->left->height + node->edge_length + 1, h);
  }
  if (node->right != NULL)
  {
	  h = MAX(node->right->height + node->edge_length + 1, h);
  }
  node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
static void print_level(asciictx *ctx, asciinode *node, int x, int level)
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  if (level == 0)
  {
	  for (i=0; i<(x-ctx->print_next-((node->lablen-isleft)/2)); i++)
    {
	    printf(" ");
    }
	  ctx->print_next += i;
	  printf("%s", node->label);
	  ctx->print_next += node->lablen;
  }
  else if (node->edge_length >= level)
  {
	  if (node->left != NULL)
    {
	    for (i=0; i<(x-ctx->print_next-(level)); i++)
      {
		    printf(" ");
	    }
	    ctx->print_next += i;
	    printf("/");
	    ctx->print_next++;
    }
	  if (node->right != NULL)
    {
	    for (i=0; i<(x-ctx->print_next+(level)); i++)
      {
		    printf(" ");
	    }
	    ctx->print_next += i;
	    printf("\\");
	    ctx->print_next++;
    }
  }
  else
  {
	  print_level(ctx, node->left,
                x-node->edge_length-1,
                level-node->edge_length-1);
	  print_level(ctx, node->right,
                x+node->edge_length+1,
                level-node->edge_length-1);
  }
}

asciinode * ascii_tree_build_recursive(asciictx *ctx, void *t)
{
  asciinode * node;

  if (t == NULL) return NULL;
  void *left = malloc(sizeof(void*));
  void *right = malloc(sizeof(void*));
  memset(left, 0, sizeof(void*));
  memset(right, 0, sizeof(void*));

  node = malloc(sizeof(asciinode));
  ctx->build_handler(t, node->label, &left, &right);
  node->left = ascii_tree_build_recursive(ctx, left);
  node->right = ascii_tree_build_recursive(ctx, right);

  if (node->left != NULL)
    {
      node->left->parent_dir = -1;
    }

  if (node->right != NULL)
    {
      node->right->parent_dir = 1;
    }

  //sprintf(node->label, "%d", t->key);
  node->lablen = strlen(node->label);

  return node;
}

//Copy the tree into the ascii node structre
asciinode * ascii_tree_build(asciictx *ctx, void *t)
{
  asciinode *node;
  if (t == NULL) return NULL;
  node = ascii_tree_build_recursive(ctx, t);
  node->parent_dir = 0;
  return node;
}

//prints ascii tree for given Tree structure
void ascii_tree_print(void *t, ascii_tree_build_handler build_handler)
{
  asciictx *ctx;
  asciinode *proot;
  int xmin, i;
  if (t == NULL) return;
  ctx = ascii_tree_create_context(build_handler);
  proot = ascii_tree_build(ctx, t);
  compute_edge_lengths(ctx, proot);
  for (i=0; i<proot->height && i < MAX_HEIGHT; i++)
    {
      ctx->lprofile[i] = INFINITY;
    }
  compute_lprofile(ctx, proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
      xmin = MIN(xmin, ctx->lprofile[i]);
    }
  for (i = 0; i < proot->height; i++)
    {
      ctx->print_next = 0;
      print_level(ctx, proot, -xmin, i);
      printf("\n");
    }
  if (proot->height >= MAX_HEIGHT)
    {
      printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
  ascii_tree_free(proot);
}
