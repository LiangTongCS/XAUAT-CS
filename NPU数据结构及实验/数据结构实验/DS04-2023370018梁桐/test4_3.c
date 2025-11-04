#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 102  // 定义节点数的最大值

int graph[MAX_NODES][MAX_NODES] = {};  // 用于存储图的邻接矩阵
int numNodes = 0;  // 用于存储节点的数量

// 实现弗洛伊德-沃尔沙尔算法以找到所有节点之间的最短路径
void floydWarshall()
{
    int i, j, k;
    // 遍历每个节点作为中间节点
    for (i = 0; i < numNodes; i++) {
        // 遍历每对节点
        for (j = 0; j < numNodes; j++) {
            for (k = 0; k < numNodes; k++) {
                // 如果通过中间节点i的路径更短，则更新路径长度
                if (graph[j][i] + graph[i][k] < graph[j][k]) {
                    graph[j][k] = graph[j][i] + graph[i][k];
                }
            }
        }
    }
}

// 打印从起始节点到目标节点的最短路径长度
void printShortestPaths()
{
    int numQueries, i, nodeA, nodeB;
    scanf("%d", &numQueries);  // 读取查询的数量
    for (i = 0; i < numQueries; i++) {
        scanf("%d %d", &nodeA, &nodeB);  // 读取查询的起始节点和目标节点
        printf("%d\n", graph[nodeA][nodeB]);  // 输出最短路径长度
    }
}

int main()
{
    int i, j;
    scanf("%d", &numNodes);  // 读取节点的数量
    // 读取图的邻接矩阵
    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    floydWarshall();  // 计算所有节点之间的最短路径
    printShortestPaths();  // 打印查询的最短路径

    return 0;
}
