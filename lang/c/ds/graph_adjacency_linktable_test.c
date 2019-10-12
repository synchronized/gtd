#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32
#define LENGTH(a) sizeof(a)/sizeof(a[0])

//邻接表中对应的链表的顶点
struct graph_enode {
  int ivex; //边所只想的顶点的位置
  struct graph_enode *next; //指向下一条弧（边）
};

//邻接表中表的顶点
struct graph_vnode {
  char data; //顶点字符
  struct graph_enode *edges; //只想第一条依附该顶点的弧
};

//邻接表
struct graph_link_table {
  int vexnum; //图的顶点数
  int edgnum; //图的边的数目
  struct graph_vnode vexs[MAX]; //顶点
};

static int graph_vnode_search(struct graph_link_table *pg, char data) {
  for (int i=0; i<pg->vexnum; i++) {
    if (pg->vexs[i].data == data)
      return i;
  }
  return -1;
}

static int graph_vnode_insert_enode(struct graph_vnode *vnode, int ivex) {
  struct graph_enode *new_node = (struct graph_enode*)malloc(sizeof(struct graph_enode));
  if (new_node == NULL) {
    return -1;
  }
  new_node->ivex = ivex;
  new_node->next = NULL;

  //找到末节点
  struct graph_enode **node = &(vnode->edges);
  while((*node) != NULL) {
    node = &((*node)->next);
  }
  *node = new_node;
  return 0;
}

struct graph_link_table* graph_link_table_create() {
  char c1, c2;
  char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  char edges[][2] = {
    {'A', 'C'},
    {'A', 'D'},
    {'A', 'F'},
    {'B', 'C'},
    {'C', 'D'},
    {'E', 'G'},
    {'F', 'G'}};

  int vlen = LENGTH(vexs);
  int elen = LENGTH(edges);
  int i, p1, p2;
  struct graph_enode *node, node2;
  struct graph_link_table *pg;

  if ((pg = (struct graph_link_table*)malloc(sizeof(struct graph_link_table))) == NULL)
    return NULL;
  memset(pg, 0, sizeof(struct graph_link_table));

  //初始化"顶点数"和"边数"
  pg->vexnum = vlen;
  pg->edgnum = elen;

  //初始化邻接表
  for (i=0; i<pg->vexnum; i++) {
    pg->vexs[i].data = vexs[i];
    pg->vexs[i].edges = NULL;
  }

  //初始化邻接表的边
  for (i=0; i<pg->edgnum; i++) {
    p1 = graph_vnode_search(pg, edges[i][0]);
    p2 = graph_vnode_search(pg, edges[i][1]);
    graph_vnode_insert_enode(&pg->vexs[p1], p2);
  }
  return pg;
}

static void graph_link_table_print(struct graph_link_table *pg) {
  printf("List Graph:\n");
  for (int i=0; i<pg->vexnum; i++) {
    printf("%d(%c): ", i, pg->vexs[i].data);
    struct graph_enode *enode = pg->vexs[i].edges;
    while(enode != NULL) {
      printf("%d(%c) ", enode->ivex, pg->vexs[enode->ivex]);
      enode = enode->next;
    }
    printf("\n");
  }
}

void main() {
  struct graph_link_table *pg;
  pg = graph_link_table_create();
  graph_link_table_print(pg);
}
