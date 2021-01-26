/**
 * Kruskal 算法生成最小生成树(邻接矩阵)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         100                 // 矩阵最大容量
#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

//邻接矩阵
struct dg_matrix {
  char vexs[MAX];       //顶点集合
  int vexnum;           //顶带数
  int edgnum;           //变数
  int matrix[MAX][MAX]; //邻接矩阵
};

//边的结构体
struct dg_edge {
  char start; //边的起点
  char end;   //边的终点
  int weight; //边的权重
};

//返回ch在dg_matrix.vexs中的索引
static int get_position(struct dg_matrix *pg, char ch) {
  for (int i=0; i<pg->vexnum; i++) {
    if (ch == pg->vexs[i]) {
      return i;
    }
  }
  return -1;
}

struct dg_matrix* create_example_graph() {
  char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  int matrix[][7] = {
    /* */  /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
    /*A*/ {   0,  12, INF, INF, INF,  16,  14},
    /*B*/ {  12,   0,  10, INF, INF,   7, INF},
    /*C*/ { INF,  10,   0,   3,   5,   6, INF},
    /*D*/ { INF, INF,   3,   0,   4, INF, INF},
    /*E*/ { INF, INF,   5,   4,   0,   2,   8},
    /*F*/ {  16,   7,   6, INF,   2,   0,   9},
    /*G*/ {  14, INF, INF, INF,   8,   9,   0}};

  int vlen = LENGTH(vexs);
  int i, j;
  struct dg_matrix *pg;
  //输入"起点数"和"边数"
  if ((pg = (struct dg_matrix*)malloc(sizeof(struct dg_matrix))) == NULL)
    return NULL;
  memset(pg, 0, sizeof(struct dg_matrix));

  //初始化顶点
  pg->vexnum = vlen;
  for (i=0; i<pg->vexnum; i++)
    pg->vexs[i] = vexs[i];

  //初始化边
  for (i=0; i<pg->vexnum; i++)
    for (j=0; j<pg->vexnum; j++)
      pg->matrix[i][j] = matrix[i][j];

  //统计边的数目
  for (i=0; i<pg->vexnum; i++)
    for (j=0; j<pg->vexnum; j++)
      if (i!=j &&pg->matrix[i][j]!=INF)
        pg->edgnum++;
  pg->edgnum /= 2;

  return pg;
}

//获取图的所有边
static struct dg_edge* get_edges(struct dg_matrix *pg) {
  int index = 0;
  struct dg_edge *edges = (struct dg_edge*)malloc(sizeof(struct dg_edge)*pg->edgnum);
  if (edges == NULL)
    return NULL;

  for (int i=0; i<pg->vexnum; i++) {
    for (int j=i+1; j<pg->vexnum; j++) {
      if (pg->matrix[i][j] != INF) {
        edges[index].start = pg->vexs[i];
        edges[index].end   = pg->vexs[j];
        edges[index].weight = pg->matrix[i][j];
        index++;
      }
    }
  }
  return edges;
}

//把边按权重排序
static void sort_edges(struct dg_edge *edges, int len) {
  for (int i=0; i<len; i++) {
    for (int j=i+1; j<len; j++) {
      if (edges[i].weight > edges[j].weight) {
        struct dg_edge tmp = edges[i];
        edges[i] = edges[j];
        edges[j] = tmp;
      }
    }
  }
}

/*
 * 获取i的终点
 */
static int get_end(int vends[], int i) {
  while(vends[i] != 0) {
    i = vends[i];
  }
  return i;
}

/*
 * 克鲁斯卡尔(Kruskal)最小生成树
 */
void kruskal(struct dg_matrix *pg) {
  int i,m,n,p1,p2;
  int length;
  int index=0; //rets数组索引
  int vends[MAX]={0}; //用于保存已有最小生成数中每个顶点在该最小树中的终点
  struct dg_edge rets[MAX]; //结果z数u，保存kruskal最小生成树的边
  struct dg_edge *edges; //图对应的所有边

  //获取图中所有的边
  edges = get_edges(pg);
  //将边按"权"的大小排序
  sort_edges(edges, pg->edgnum);

  for (i=0; i<pg->edgnum; i++) {
    p1 = get_position(pg, edges[i].start); //获取第i条边的起点
    p2 = get_position(pg, edges[i].end); //获取第i条边的终点
    m = get_end(vends, p1); //获得p1在"已有的最小生成树"中的终点
    n = get_end(vends, p2); //获得p2在"已有的最小生成树"中的终点
    //如果m!=n,意味着"边i"与"已经添加到最小生成树中的顶点"没有形成环路
    if (m != n) {
      vends[m] = n; //设置m在"已有的最小生成树"中的终点为n
      rets[index++] = edges[i]; //保存结果
    }
  }

  free(edges);

  //统计并打印"kruskal最小生成树"的信息
  length = 0;
  for (i=0; i<index; i++)
    length += rets[i].weight;
  printf("Kruskal=%d: ", length);
  for (i=0; i<index; i++)
    printf("(%c,%c) ", rets[i].start, rets[i].end);
  printf("\n");
}

void main() {
  struct dg_matrix *pg;
  // 采用已有的"图"
  pg = create_example_graph();

  kruskal(pg);             // kruskal算法生成最小生成树
}
