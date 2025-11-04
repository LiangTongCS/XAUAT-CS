#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

typedef int ElementType;

// 三元组结构体
typedef struct {
    int row, col;       // 行号和列号
    ElementType e;      // 元素值
} Triple;

// 稀疏矩阵结构体
typedef struct {
    Triple data[MAXSIZE + 1];   // 存储非零元素的数组，下标从1开始
    int m, n;                   // 矩阵的行数和列数
    int len;                    // 非零元素个数
} TSMatrix;

// 初始化稀疏矩阵
TSMatrix init(TSMatrix* P) {
    TSMatrix A;
    int i = 0;
    A.len = 0;
    *P = A;
    scanf("%d%d", &A.m, &A.n);  // 输入矩阵的行数和列数
    A.len = 0;
    while (1) {
        i++;
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);   // 输入三元组的行号、列号和元素值
        if (x == 0 && y == 0 && z == 0) {
            break;
        }

        A.data[i].row = x;
        A.data[i].col = y;
        A.data[i].e = z;
        A.len++;  // 更新非零元素个数
    }
    return A;
}

// 矩阵乘法
TSMatrix mult(TSMatrix A, TSMatrix B) {
    TSMatrix C;
    C.m = A.m;
    C.n = B.n;
    C.len = 0;

    // 遍历A的行
    for (int i = 1; i <= A.m; i++) {
        // 遍历B的列
        for (int j = 1; j <= B.n; j++) {
            int temp = 0; // 用于累加当前行列相乘所得到的结果
            // 在A的非零元素中查找能与B的当前列相乘的元素
            for (int p = 1; p <= A.len; p++) {
                for (int q = 1; q <= B.len; q++) {
                    if (A.data[p].row == i && B.data[q].col == j && A.data[p].col == B.data[q].row) {
                        temp += A.data[p].e * B.data[q].e;
                    }
                }
            }
            // 若结果不为0，则添加到C中
            if (temp != 0) {
                C.len++;
                C.data[C.len].row = i;
                C.data[C.len].col = j;
                C.data[C.len].e = temp;
            }
        }
    }
    return C;
}

int main() {
    int i;
    TSMatrix A, B, C;
    // 初始化矩阵A和B
    A = init(&A);
    B = init(&B);

    // 计算A和B的乘积
    C = mult(A, B);

    // 输出结果矩阵C
    for (i = 1; i <= C.len; i++) {
        printf("%d %d %d\n", C.data[i].row, C.data[i].col, C.data[i].e);
    }

    return 0;
}
