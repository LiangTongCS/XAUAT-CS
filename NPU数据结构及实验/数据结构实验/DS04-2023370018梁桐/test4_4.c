#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 102  // 定义节点数的最大值
int graph[MAX_NODES][MAX_NODES] = {};  // 用于存储图的邻接矩阵，表示每对节点之间的距离
int numNodes = 0;  // 用于存储节点的数量
int path[MAX_NODES][MAX_NODES] = {};  // 用于存储路径信息，用于重建最短路径
int stack[MAX_NODES] = {};  // 用于存储路径的栈
int top = -1;  // 栈顶指针
// 弗洛伊德-沃尔沙尔算法计算最短路径
void floydWarshall(void) {
    int i,j,k;
    for ( k = 0; k < numNodes; ++k) {
        for ( i = 0; i < numNodes; ++i) {
            for ( j = 0; j < numNodes; ++j) {
                // 如果通过节点k的路径比直接路径更短，则更新最短路径和路径数组
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    path[i][j] = k;  // 记录中间节点
                }
            }
        }
    }
}
// 递归查找从节点a到节点b的路径
void findPath(int startNode, int endNode) {
    stack[++top] = endNode;  // 将目标节点压入栈
    if (path[startNode][endNode] == -1) {  // 如果路径数组中没有中间节点，直接压入起始节点
        stack[++top] = startNode;
        return;
    }
    findPath(startNode, path[startNode][endNode]);  // 递归查找路径
}
// 打印路径函数
void printPaths(void) {
    int numQueries,i;
    scanf("%d", &numQueries);  // 读取查询次数
    for ( i = 0; i < numQueries; ++i) {
        int startNode, endNode;
        scanf("%d %d", &startNode, &endNode);  // 读取查询的起始节点和目标节点
        top = -1;  // 重置栈顶指针
        findPath(startNode, endNode);  // 查找路径
        while (top > -1) printf("%d\n", stack[top--]);  // 输出路径中的节点
    }
}
int main() {
    int i,j;
    scanf("%d", &numNodes);  // 读取节点数量
    for ( i = 0; i < numNodes; ++i)
        for ( j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);  // 读取邻接矩阵中的距离
            path[i][j] = -1;  // 初始化路径数组为-1，表示无中间节点
        }
    floydWarshall();  // 计算所有节点之间的最短路径
    printPaths();  // 打印查询的路径
    return 0;
}
