#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

//
struct graph_adjacency_matrix {
  char vexs[MAX];       //顶点集合
  int vexnum;           //顶点数
  int edgnum;           //边数
  int matrix[MAX][MAX]; //邻接矩阵
};

static int get_position(struct graph_adjacency_matrix *pg, char vex) {
  for (int i=0; i<pg->vexnum; i++) {
    if (vex == pg->vexs[i]) {
      return i;
    }
  }
  return -1;
}

struct graph_adjacency_matrix* graph_adjacency_matrix_create() {
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
  struct graph_adjacency_matrix* pg;

  // 输入"顶点数"和"边数"
  if ((pg = (struct graph_adjacency_matrix*)malloc(sizeof(struct graph_adjacency_matrix))) == NULL)
    return NULL;
  memset(pg, 0, sizeof(struct graph_adjacency_matrix));

  //初始化"顶点数"和"边数"
  pg->vexnum = vlen;
  pg->edgnum = elen;

  //初始化顶点
  for (i=0; i<pg->vexnum; i++) {
    pg->vexs[i] = vexs[i];
  }

  for (i=0; i<pg->edgnum; i++) {
    p1 = get_position(pg, edges[i][0]);
    p2 = get_position(pg, edges[i][1]);
    pg->matrix[p1][p2] = 1;
    pg->matrix[p2][p1] = 1;
  }
  return pg;
}

static void graph_adjacency_matrix_print(struct graph_adjacency_matrix *pg) {
  int i,j=0;
  printf("Martix Graph:\n");
  for (i=0; i<pg->vexnum; i++) {
    for (j=0; j<pg->vexnum; j++)
      printf("%d ", pg->matrix[i][j]);
    printf("\n");
  }
}

int main() {
  struct graph_adjacency_matrix *pg;
  pg = graph_adjacency_matrix_create();
  graph_adjacency_matrix_print(pg);
}
