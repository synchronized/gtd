/**
 * Dijkstra 算法获取最短路径(邻接矩阵)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         100
#define INF         (~(0x1<<31)) // 最大值(即0X7FFFFFFF)

//#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

struct dg_matrix {
  char vexs[MAX];        //顶点集合
  int vexnum;            //顶点数
  int edgnum;            //边数
  int matrix[MAX][MAX];  //邻接矩阵
};

//边的结构
struct dg_edge {
  int start;  //边的起点
  int end;    //边的终点
  int weight; //边的权重
};

//返回ch在dg_matrix.vexs中的索引
static int get_position(struct dg_matrix *pg, char ch) {
  for (int i=0; i<pg->vexnum; i++)
    if (pg->vexs[i] == ch)
      return i;

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
  struct dg_matrix *pg = (struct dg_matrix*)malloc(sizeof(struct dg_matrix));
  if (pg == NULL)
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
      if (pg->matrix[i][j] != INF)
        pg->edgnum++;

  pg->edgnum /= 2;

  return pg;
}

/*
 * Dijkstra最短路径。
 * 即，统计图(G)中"顶点vs"到其它各个顶点的最短路径。
 *
 * 参数说明：
 *       pg -- 图
 *       vs -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
 *     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，
 *             位于"顶点i"之前的那个顶点。
 *     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
 */
void dijkstra(struct dg_matrix *pg, int vs, int prev[], int dist[]) {
  int i, j, k;
  int min;
  int tmp;
  int flag[MAX]; // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

  //初始化
  for (i=0; i<pg->vexnum; i++) {
    flag[i] = 0;                 // 顶点i的最短路径还没获取到。
    prev[i] = 0;                 // 顶点i的前驱顶点为0。
    dist[i] = pg->matrix[vs][i]; // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
  }
  // 对"顶点vs"自身进行初始化
  flag[vs] = 1;
  dist[vs] = 0;

  // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
  for (i=1; i<pg->vexnum; i++) {
    // 寻找当前最小的路径；
    // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
    min = INF;
    k = 0;
    for (j=0; j<pg->vexnum; j++) {
      if ((flag[j] == 0) && (dist[j] < min)) {
        min = dist[j];
        k = j;
      }
    }
    // 标记"顶点k"为已经获取到最短路径
    flag[k] = 1;

    // 修正当前最短路径和前驱顶点
    // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
    for (j=0; j<pg->vexnum; j++) {
      tmp = (pg->matrix[k][j] == INF ? INF : (pg->matrix[k][j] + min)); //防止溢出
      if ((flag[j] == 0) && (tmp < dist[j])) {
        dist[j] = tmp;
        prev[j] = k;
      }
    }
  }
  // 打印dijkstra最短路径的结果
  printf("dijkstra(%c): \n", pg->vexs[vs]);
  for (i = 0; i < pg->vexnum; i++)
    printf("    shortest(%c, %c)=(%d,%d)\n", pg->vexs[vs], pg->vexs[i], prev[i], dist[i]);
}

void main() {
  int prev[MAX];
  int dist[MAX];
  int vs = 0;
  struct dg_matrix *pg = create_example_graph();

  dijkstra(pg, vs, prev, dist);
}
