#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define INF (~(0x1<<31)) // 最大值(即0X7FFFFFFF)
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

//邻接矩阵
struct dg_matrix {
  char vexs[MAX];       //顶点集合
  int vexnum;           //顶点数
  int edgnum;           //边数
  int matrix[MAX][MAX]; //邻接矩阵
};

//边的结构体
struct dg_edge {
  char strart; //边的起点
  char end;    //边的终点
  int weight;  //边的权重
};

int get_position(struct dg_matrix *pg, char ch) {
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

/*
 * prim 最小生成树
 * 参数说明:
 * @param pg 邻接矩阵
 * @param start 从途中的第几个元素开始，生成最小树
 */
void prim(struct dg_matrix *pg, int start) {
  int min,i,j,k,m,n,sum = 0;
  int index = 0; //prim最小树的索引,即prims数组的索引
  int prims[MAX]; //结果顶点
  int weights[MAX]; //当前顶点和剩余顶点的权值

  // prim最小生成树中第一个数是"图中第start个顶点"，因为是从start开始的。
  prims[index++] = pg->vexs[start];

  // 初始化"顶点的权值数组"，
  // 将每个顶点的权值初始化为"第start个顶点"到"该顶点"的权值。
  for (i=0; i<pg->vexnum; i++)
    weights[i] = pg->matrix[start][i];

  // 将第start个顶点的权值初始化为0。
  // 可以理解为"第start个顶点到它自身的距离为0"。
  weights[start] = 0;

  for (i=0; i<pg->vexnum; i++) {
    // 由于从start开始的，因此不需要再对第start个顶点进行处理。
    if (start == i)
      continue;

    j=0;
    k=0;
    min = INF;
    // 在未被加入到最小生成树的顶点中，找出权值最小的顶点
    while(j < pg->vexnum) {
      // 若weights[j]=0，意味着"第j个节点已经被排序过"(或者说已经加入了最小生成树中)。
      if (weights[j] != 0 && weights[j] < min) {
        min = weights[j];
        k = j;
      }
      j++;
    }

    // 经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点是第k个顶点。
    // 将第k个顶点加入到最小生成树的结果数组中
    prims[index++] = pg->vexs[k];
    // 将"第k个顶点的权值"标记为0，意味着第k个顶点已经排序过了(或者说已经加入了最小树结果中)。
    weights[k] = 0;

    // 当第k个顶点被加入到最小生成树的结果数组中之后，更新其它顶点的权值。
    for (j=0; j<pg->vexnum; j++) {
      // 当第j个节点没有被处理，并且需要更新时才被更新。
      if (weights[j] != 0 && pg->matrix[k][j] < weights[j])
        weights[j] = pg->matrix[k][j];
    }
  }

  //求权值
  sum = 0;
  for (i=1; i<index; i++) {
    min = INF;
    //获取prims[i]在G中的位置
    n = get_position(pg, prims[i]);
    // 在vexs[0...i]中，找出到j的权值最小的顶点。
    for (j=0; j<i; j++) {
      m = get_position(pg, prims[j]);
      if (pg->matrix[m][n] < min)
        min = pg->matrix[m][n];
    }
    sum += min;
  }

  //打印
  printf("Prims(%c)=%d: ", pg->vexs[start], sum);
  for (i=0; i<index; i++) 
    printf("%c ", prims[i]);
  printf("\n");
}

void main() {
  struct dg_matrix *pg = create_example_graph();
  prim(pg, 0);             // prim算法生成最小生成树
}
