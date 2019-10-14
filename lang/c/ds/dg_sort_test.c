/**
 * 无回路有向图(Directed Acyclic Graph)的拓扑排序
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 100
#define LENGTH(a) sizeof(a)/sizeof(a[0])

//邻接表边节点
struct dg_list_enode {
  int ivex; //该边只想的顶点的位置
  struct dg_list_enode *next; //只想下一条弧的指针
};

//邻接表的顶点
struct dg_list_vnode {
  char data; //顶点信息
  struct dg_list_enode *edges; //只想第一条依附该顶点的弧
};

//邻接表
struct dg_list {
  int vexnum; //顶点数
  int edgnum; //边数
  struct dg_list_vnode *vexs; //顶点信息
};

int get_position(struct dg_list *pg, char data) {
  for (int i=0; i<pg->vexnum; i++) {
    if (pg->vexs[i].data == data) {
      return i;
    }
  }
  return -1;
}

/*
 * 拓扑排序
 *
 * 参数说明：
 *     G -- 邻接表表示的有向图
 * 返回值：
 *     -1 -- 失败(由于内存不足等原因导致)
 *      0 -- 成功排序，并输入结果
 *      1 -- 失败(该有向图是有环的)
 */
int topological_sort(struct dg_list *pg) {
  int i,j;
  int index = 0;
  int head = 0; //辅助队列头
  int rear = 0; //辅助队列尾
  int *queue; //辅助队列
  int *ins; //入度数组
  char *tops; //拓扑排序结果数组,记录每个节点的排序后的序号
  int num = pg->vexnum;
  struct dg_list_enode *node;

  ins = (int*)malloc(num*sizeof(int)); //入度数组
  tops = (char*)malloc(num*sizeof(char)); //拓扑排序结果数组
  queue = (int*)malloc(num*sizeof(int)); //辅助队列
  assert(ins!= NULL && tops != NULL && queue != NULL);
  memset(ins, 0, num*sizeof(int));
  memset(tops, 0, num*sizeof(char));
  memset(queue, 0, num*sizeof(int));

  //统计每个顶点的入度数
  for (i=0; i<num; i++) {
    node = pg->vexs[i].edges;
    while (node != NULL) {
      ins[node->ivex]++;
      node = node->next;
    }
  }

  //将所有度为0的顶点入队列
  for (i=0; i<num; i++) {
    if (ins[i] == 0)
      queue[rear++] = i; //入队列
  }

  while (head != rear) { //队列非空
    j = queue[head++]; //出队列,j是顶点的序号
    tops[index++] = pg->vexs[j].data; //将该顶点添加到tops中,tops是排序结果
    node = pg->vexs[j].edges; //获取该顶点为起点的边

    //将与"node"关联的节点的入度减1
    //若减1后,该节点的入度为0,则将该节点添加到队列中
    while (node != NULL) {
      //将需要为node->ivex的入度减1
      ins[node->ivex]--;
      //若节点的入度为0,则将其“入队列”
      if (ins[node->ivex] == 0) 
        queue[rear++] = node->ivex; //入队列

      node = node->next;
    }
  }

  if (index != pg->vexnum) {
    printf("graph has a syscle\n");
    free(queue);
    free(ins);
    free(tops);
    return 1;
  }

  //打印拓扑排序结果
  printf("-- topsort:");
  for (i=0; i<num; i++)
    printf("%c ", tops[i]);
  printf("\n");

  free(queue);
  free(ins);
  free(tops);
  return 0;
}

void link_last(struct dg_list_vnode *vnode, struct dg_list_enode *enode) {
  struct dg_list_enode **node = &vnode->edges;
  while(*node != NULL) {
    node = &(*node)->next;
  }
  *node = enode;
}

/*
 * 创建邻接表对应的图(用已提供的数据)
 */
struct dg_list* create_example_lgraph()
{
    char c1, c2;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'G'}, 
        {'B', 'A'}, 
        {'B', 'D'}, 
        {'C', 'F'}, 
        {'C', 'G'}, 
        {'D', 'E'}, 
        {'D', 'F'}}; 
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    struct dg_list_enode *node1, *node2;
    struct dg_list* pG;

    if ((pG=(struct dg_list*)malloc(sizeof(struct dg_list))) == NULL )
    assert(pG != NULL);
    memset(pG, 0, sizeof(struct dg_list));

    // 初始化"顶点数"和"边数"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    pG->vexs = (struct dg_list_vnode *)malloc(pG->vexnum * sizeof(struct dg_list_vnode));
    assert(pG->vexs != NULL);
    // 初始化"邻接表"的顶点
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = vexs[i];
        pG->vexs[i].edges = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<pG->edgnum; i++) {
        // 读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = get_position(pG, c1);
        p2 = get_position(pG, c2);
        // 初始化node1
        node1 = (struct dg_list_enode*)malloc(sizeof(struct dg_list_enode));
        node1->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(pG->vexs[p1].edges == NULL)
          pG->vexs[p1].edges = node1;
        else
            link_last(&pG->vexs[p1], node1);
    }

    return pG;
}


/*
 * 打印邻接表图
 */
void print_lgraph(struct dg_list G)
{
  int i;
  struct dg_list_enode *node;

  printf("== List Graph:\n");
  for (i = 0; i < G.vexnum; i++) {
    printf("%d(%c): ", i, G.vexs[i].data);
    node = G.vexs[i].edges;
    while (node != NULL) {
      printf("%d(%c) ", node->ivex, G.vexs[node->ivex].data);
      node = node->next;
    }
    printf("\n");
  }
}

void main() {
  struct dg_list *pG;

  // 自定义"图"(自己输入数据)
  //pG = create_lgraph();
  // 采用已有的"图"
  pG = create_example_lgraph();

  // 打印图
  print_lgraph(*pG);      // 打印图
  //DFS_traverse(*pG);    // 深度优先搜索
  //BFS(*pG);             // 广度优先搜索
  topological_sort(pG);  // 拓扑排序
}
