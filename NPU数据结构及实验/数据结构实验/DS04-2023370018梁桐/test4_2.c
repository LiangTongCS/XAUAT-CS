#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 105
#define INF 10000

// 定义全局变量
int vertex_count = 0;
int distance[MAXSIZE][MAXSIZE] = {};
bool visited[MAXSIZE] = {};
int shortest_path[MAXSIZE] = {};
int path_stack1[MAXSIZE] = {};
int stack_top1 = -1;
int path_stack2[MAXSIZE] = {};
int stack_top2 = -1;

// Dijkstra算法函数
void dijkstra_algorithm(void) {
    int i, j;
    // 初始化最短路径数组
    for (i = 0; i < vertex_count; ++i) {
        shortest_path[i] = INF;
    }
    visited[0] = true;
    shortest_path[0] = 0;
    // 初始化起始节点到其他节点的最短路径
    for (i = 0; i < vertex_count; ++i) {
        if (distance[0][i] != INF) {
            shortest_path[i] = distance[0][i];
        }
    }

    // 进行n-1次迭代，n为节点数量
    for (i = 0; i < vertex_count - 1; ++i) {
        int min_path_length = INF, next_vertex;
        // 找出当前未访问节点中距离起始节点最近的节点
        for (j = 0; j < vertex_count; ++j) {
            if (!visited[j] && shortest_path[j] < min_path_length) {
                min_path_length = shortest_path[j];
                next_vertex = j;
            }
        }
        visited[next_vertex] = true;

        // 更新当前节点的邻接节点的最短路径
        for (j = 0; j < vertex_count; ++j) {
            if (!visited[j] && distance[next_vertex][j] != INF) {
                int tmp = shortest_path[next_vertex] + distance[next_vertex][j];
                shortest_path[j] = shortest_path[j] < tmp ? shortest_path[j] : tmp;
            }
        }
    }
}

// 打印最短路径函数
void print_shortest_path(void) {
    int i, j;
    bool flag = false;
    int start_vertex, start_vertex1, start_vertex2, end_vertex, end_vertex1, end_vertex2;
    scanf("%d %d", &start_vertex, &end_vertex);
    start_vertex1 = end_vertex2 = start_vertex;
    end_vertex1 = start_vertex2 = end_vertex;
    path_stack1[++stack_top1] = end_vertex1;
    path_stack2[++stack_top2] = start_vertex2;

    // 寻找第一条最短路径
    for (j = 0; end_vertex1 != start_vertex1; j++) {
        for (i = 0; i < vertex_count; ++i) {
            if (distance[i][end_vertex1] != INF && shortest_path[i] < shortest_path[end_vertex1] && shortest_path[i] + distance[i][end_vertex1] == shortest_path[end_vertex1]) {
                path_stack1[++stack_top1] = end_vertex1 = i;
            }
        }

        // 防止死循环，若超过节点数则跳出
        if (j > 105) break;
    }
    // 若超过节点数，则寻找另一条最短路径
    if (j > 105) {
        for (; end_vertex2 != start_vertex2;) {
            for (i = 0; i < vertex_count; ++i) {
                if (distance[i][end_vertex2] != INF && shortest_path[i] < shortest_path[end_vertex2] && shortest_path[i] + distance[i][end_vertex2] == shortest_path[end_vertex2]) {
                    path_stack2[++stack_top2] = end_vertex2 = i;
                }
            }
        }
        flag = true;
    }

    // 输出最短路径
    while (stack_top1 > -1 && !flag) {
        printf("%d\n", path_stack1[stack_top1--]);
    }
    while (stack_top2 > -1 && flag) {
        printf("%d\n", path_stack2[stack_top2--]);
    }
}

int main() {
    int i, j;
    scanf("%d", &vertex_count);
    // 读取节点间的距离信息
    for (i = 0; i < vertex_count; ++i) {
        for (j = 0; j < vertex_count; ++j) {
            scanf("%d", &distance[i][j]);
        }
    }
    // 调用Dijkstra算法计算最短路径
    dijkstra_algorithm();
    // 打印最短路径
    print_shortest_path();
    return 0;
}
