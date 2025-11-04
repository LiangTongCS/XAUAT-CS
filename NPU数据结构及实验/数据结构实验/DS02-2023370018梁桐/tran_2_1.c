#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

typedef int ElementType;

typedef struct {
    int row, col;           // 行号和列号
    ElementType e;          // 元素值
} Triple;

typedef struct {
    Triple data[MAXSIZE + 1];   // 三元组表存储非零元素
    int m, n, len;              // 矩阵的行数、列数以及非零元素个数
} TSMatrix;

// 矩阵转置函数
void Tran(TSMatrix A, TSMatrix *B) {
    int col, t, p, q;
    int num[MAXSIZE];           // 记录每列非零元素个数
    int position[MAXSIZE];      // 记录每列非零元素在B中的起始位置

    // 初始化转置后矩阵B的属性
    B->len = A.len;
    B->n = A.m;
    B->m = A.n;

    if (B->len) {
        // 初始化每列非零元素个数为0
        for (col = 0; col <= A.n; col++) {
            num[col] = 0;
        }

        // 统计每列非零元素个数
        for (t = 1; t <= A.len; t++) {
            num[A.data[t].col]++;
        }

        // 计算每列非零元素在B中的起始位置
        position[0] = 1;
        for (col = 1; col <= A.n; col++) {
            position[col] = position[col - 1] + num[col - 1];
        }

        // 开始转置
        for (p = 1; p <= A.len; p++) {
            col = A.data[p].col;
            q = position[col];
            B->data[q].row = A.data[p].col;    // 行列互换
            B->data[q].col = A.data[p].row;
            B->data[q].e = A.data[p].e;        // 元素赋值
            position[col]++;                    // 指向下一个列号为col的非零元素在B中的存放位置
        }
    }
}

int main() {
    int i;
    TSMatrix A, B;

    // 读入矩阵A的行数和列数
    scanf("%d%d", &A.m, &A.n);

    // 逐个读入非零元素并存入矩阵A中
    i = 0;
    A.len = 0;
    while (1) {
        i++;
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (x == 0 && y == 0 && z == 0) {
            break;
        }

        A.data[i].row = x;
        A.data[i].col = y;
        A.data[i].e = z;
        A.len++;  // 更新非零元素个数
    }

    // 调用转置函数将矩阵A转置得到矩阵B
    Tran(A, &B);

    // 输出转置后的矩阵B
    for (i = 1; i <= B.len; i++) {
        printf("%d %d %d\n", B.data[i].row, B.data[i].col, B.data[i].e);
    }

    return 0;
}
