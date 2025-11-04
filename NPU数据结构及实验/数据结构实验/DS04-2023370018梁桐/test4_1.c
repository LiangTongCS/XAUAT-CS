#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 105
#define INF 10000

// 全局变量
int vertex_count = 0;
int distance[MAXSIZE][MAXSIZE] = {};

bool visited[MAXSIZE] = {};
int shortest_path[MAXSIZE] = {};



// Dijkstra算法函数，计算最短路径
void dijkstra(void) {
    int i,j;
    // 初始化最短路径数组为无穷大
    for ( i = 0; i < vertex_count; ++i) {
        shortest_path[i] = INF;
    }
    visited[0] = true;
    shortest_path[0] = 0;
    // 更新起始节点到其他节点的最短路径
    for ( i = 0; i < vertex_count; ++i) {
        if (distance[0][i] != INF) {
            shortest_path[i] = distance[0][i];
        }
    }

    // 进行n-1次迭代，n为节点数量
    for ( i = 0; i < vertex_count - 1; ++i) {
        int min_path_length = INF, next_vertex;
        // 找出当前未访问节点中距离起始节点最近的节点
        for ( j = 0; j < vertex_count; ++j) {
            if (!visited[j] && shortest_path[j] < min_path_length) {
                min_path_length = shortest_path[j];
                next_vertex = j;
            }
        }
        visited[next_vertex] = true;

        // 更新当前节点的邻接节点的最短路径
        for ( j = 0; j < vertex_count; ++j) {
            if (!visited[j] && distance[next_vertex][j] != INF) {
                int tmp = shortest_path[next_vertex] + distance[next_vertex][j];
                shortest_path[j] = shortest_path[j] < tmp ? shortest_path[j] : tmp;
            }
        }
    }
}

// 打印最短路径函数
void print_shortest_path(void) {
    int i;
    for ( i = 0; i < vertex_count; ++i) {
        printf("%d\n", shortest_path[i]);
    }
}

int main () {
    int i,j;
    scanf("%d", &vertex_count);
    for ( i = 0; i < vertex_count; ++i) {
        for ( j = 0; j < vertex_count; ++j) {
            scanf("%d", &distance[i][j]);
        }
    }
    dijkstra(); // 运行Dijkstra算法
    print_shortest_path(); // 打印最短路径
    return 0;
}
