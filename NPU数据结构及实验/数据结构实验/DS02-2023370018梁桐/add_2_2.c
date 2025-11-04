#include <stdio.h>

#define MAX_SIZE 20000

// 定义三元组结构体
typedef struct {
    int x, y;
    int value;
} triple;

// 定义稀疏矩阵结构体
typedef struct {
    int row, col; // 矩阵的行数和列数
    int count;    // 非零元素的个数
    triple data[MAX_SIZE]; // 保存矩阵中的非零元素
} matrix;

// 函数声明
void input_matrix(matrix *matrix1, matrix *matrix2);
void add_matrices(matrix *matrix1, matrix *matrix2);
void sort_matrix(matrix *matrix1);
void print_matrix(matrix matrix1);

// 输入稀疏矩阵数据
void input_matrix(matrix *matrix1, matrix *matrix2) {
    // 循环输入第一个矩阵的非零元素
    for (int i = 0; i < matrix1->count; i++) {
        scanf("%d%d%d", &matrix1->data[i].x, &matrix1->data[i].y, &matrix1->data[i].value);
    }
    // 循环输入第二个矩阵的非零元素
    for (int i = 0; i < matrix2->count; i++) {
        scanf("%d%d%d", &matrix2->data[i].x, &matrix2->data[i].y, &matrix2->data[i].value);
    }
}

// 矩阵加法
void add_matrices(matrix *matrix1, matrix *matrix2) {
    // 遍历第二个矩阵的非零元素
    for (int i = 0; i < matrix2->count; i++) {
        // 遍历第一个矩阵的非零元素
        for (int j = 0; j < matrix1->count; j++) {
            // 如果找到相同位置的非零元素，则将两个元素相加
            if (matrix1->data[j].x == matrix2->data[i].x && matrix1->data[j].y == matrix2->data[i].y) {
                matrix1->data[j].value += matrix2->data[i].value;
                matrix2->data[i].x = -1; // 标记第二个矩阵中已经相加过的元素
            }
            // 如果第一个矩阵的元素值为0，则标记为无效
            if (matrix1->data[j].value == 0) {
                matrix1->data[j].x = -1;
            }
        }
    }
    // 将第二个矩阵中未被标记的非零元素添加到第一个矩阵中
    for (int i = 0; i < matrix2->count; i++) {
        if (matrix2->data[i].x == -1)
            continue;
        matrix1->data[matrix1->count].x = matrix2->data[i].x;
        matrix1->data[matrix1->count].y = matrix2->data[i].y;
        matrix1->data[matrix1->count].value = matrix2->data[i].value;
        matrix1->count++;
    }
}

// 对矩阵中的非零元素按照行列坐标进行排序
void sort_matrix(matrix *matrix1) {
    for (int i = 0; i < matrix1->count; i++) {
        for (int j = 0; j < matrix1->count - i - 1; j++) {
            if (matrix1->data[j].x > matrix1->data[j + 1].x ||
                (matrix1->data[j].x == matrix1->data[j + 1].x && matrix1->data[j].y > matrix1->data[j + 1].y)) {
                triple temp = matrix1->data[j];
                matrix1->data[j] = matrix1->data[j + 1];
                matrix1->data[j + 1] = temp;
            }
        }
    }
}

// 打印矩阵
void print_matrix(matrix matrix1) {
    for (int i = 0; i < matrix1.count; i++) {
        if (matrix1.data[i].x == -1)
            continue;
        printf("%d %d %d\n", matrix1.data[i].x, matrix1.data[i].y, matrix1.data[i].value);
    }
}

// 主函数
int main() {
    matrix matrix1, matrix2;
    scanf("%d%d%d%d", &matrix1.row, &matrix1.col, &matrix1.count, &matrix2.count);
    matrix2.row = matrix1.row;
    matrix2.col = matrix1.col;
    input_matrix(&matrix1, &matrix2);
    add_matrices(&matrix1, &matrix2);
    sort_matrix(&matrix1);
    print_matrix(matrix1);
    return 0;
}
