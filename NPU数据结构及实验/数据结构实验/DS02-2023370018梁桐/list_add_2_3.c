#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct OLNode
{
    int row, col;            // 节点的行坐标、列坐标和元素值
    ElementType e;          // 元素值
    struct OLNode* right, * down;  // 指向右方节点和下方节点的指针
} OLNode, *OLink;

typedef struct CrossList
{
    OLink* row_head, * col_head;  // 行指针和列指针
    int m, n, len;            // 矩阵的行数、列数和非零元素个数
} CrossList;

// 初始化矩阵
void initMatrix(CrossList* A, CrossList* B)
{
    scanf("%d%d%d%d", &A->m, &A->n, &A->len, &B->len); // 输入矩阵的行数、列数和非零元素个数
    B->m = A->m;    // 保证两个矩阵行数相同
    B->n = A->n;    // 保证两个矩阵列数相同
}

// 向矩阵中插入节点
void insertNode(CrossList* L, OLNode* P)
{
    OLNode* temp, * N;
    N = (OLNode*)malloc(sizeof(OLNode)); // 创建新节点
    N->col = P->col;
    N->row = P->row;
    N->e = P->e;

    // 插入行指针
    if (L->row_head[N->row] == NULL || L->row_head[N->row]->col > N->col) // 如果当前行为空或新节点的列坐标小于当前行的第一个节点的列坐标
    {
        N->right = L->row_head[N->row]; // 新节点的右指针指向当前行的第一个节点
        L->row_head[N->row] = N;        // 当前行的第一个节点更新为新节点
    }
    else
    {
        for (temp = L->row_head[N->row]; temp->right && temp->right->col < N->col; temp = temp->right) // 遍历当前行找到新节点应该插入的位置
            ;
        N->right = temp->right; // 新节点的右指针指向当前位置的下一个节点
        temp->right = N;        // 当前位置的节点的右指针指向新节点
    }

    // 插入列指针
    if (L->col_head[N->col] == NULL || L->col_head[N->col]->row > N->row) // 如果当前列为空或新节点的行坐标小于当前列的第一个节点的行坐标
    {
        N->down = L->col_head[N->col]; // 新节点的下指针指向当前列的第一个节点
        L->col_head[N->col] = N;        // 当前列的第一个节点更新为新节点
    }
    else
    {
        for (temp = L->col_head[N->col]; temp->down && temp->down->row < N->row; temp = temp->down) // 遍历当前列找到新节点应该插入的位置
            ;
        N->down = temp->down; // 新节点的下指针指向当前位置的下一个节点
        temp->down = N;       // 当前位置的节点的下指针指向新节点
    }
}

// 创建矩阵
void createMatrix(CrossList* M)
{
    OLNode* p;
    M->row_head = (OLNode**)malloc((M->m + 1) * sizeof(OLNode*)); // 分配行指针数组的内存空间
    M->col_head = (OLNode**)malloc((M->n + 1) * sizeof(OLNode*)); // 分配列指针数组的内存空间
    for (int i = 1; i <= M->m; i++)
        M->row_head[i] = NULL; // 初始化行指针数组
    for (int i = 1; i <= M->n; i++)
        M->col_head[i] = NULL; // 初始化列指针数组
    for (int i = 1; i <= M->len; i++) // 输入非零元素的信息并插入矩阵
    {
        p = (OLNode*)malloc(sizeof(OLNode));
        scanf("%d%d%d", &p->row, &p->col, &p->e); // 输入非零元素的行坐标、列坐标和值
        insertNode(M, p); // 将新节点插入矩阵
    }
}

// 将矩阵B的元素加到矩阵A中
void addMatrix(CrossList* A, CrossList* B)
{
    OLNode* p, * temp1, * temp2;
    for (int i = 1; i <= B->m; i++) // 遍历矩阵B的每一行
    {
        if (B->row_head[i] == NULL) // 如果当前行为空，直接跳过
            continue;
        else
        {
            if (A->row_head[i] == NULL) // 如果当前行为空，则直接将矩阵B的当前行节点复制到矩阵A中
            {
                temp2 = B->row_head[i];
                while (temp2)
                {
                    insertNode(A, temp2);
                    temp2 = temp2->right;
                }
            }
            else
            {
                for (temp2 = B->row_head[i];; temp2 = temp2->right) // 遍历矩阵B的当前行的每个节点
                {
                    for (temp1 = A->row_head[i];; temp1 = temp1->right) // 遍历矩阵A的当前行的每个节点
                    {
                        if (temp2->col == temp1->col) // 如果当前节点的列坐标相同，则将对应位置的元素相加
                        {
                            temp1->e += temp2->e;
                            break;
                        }
                        else if ((temp2->col < temp1->col) || temp1->right == NULL) // 如果当前节点的列坐标小于当前矩阵A的节点的列坐标，或者当前节点是最后一个节点，则将当前节点插入矩阵A中
                        {
                            insertNode(A, temp2);
                            break;
                        }
                        else if (temp2->col > temp1->col && temp2->col < temp1->right->col) // 如果当前节点的列坐标大于当前矩阵A的节点的列坐标，并且小于下一个节点的列坐标，则将当前节点插入矩阵A中
                        {
                            insertNode(A, temp2);
                            break;
                        }
                    }
                    if (temp2->right == NULL) // 如果已经遍历到矩阵B的当前行的最后一个节点，则退出循环
                        break;
                }
            }
        }
    }
}

// 打印矩阵
void printMatrix(CrossList* L)
{
    OLNode* p;
    for (int i = 1; i <= L->m; i++) // 遍历矩阵的每一行
    {
        p = L->row_head[i];
        while (p != NULL) // 遍历当前行的每个节点
        {
            if (p->e != 0) // 如果当前节点的元素值不为0，则打印该节点的行坐标、列坐标和元素值
                printf("%d %d %d\n", p->row, p->col, p->e);
            p = p->right;
        }
    }
}

int main()
{
    CrossList A, B;
    initMatrix(&A, &B); // 初始化矩阵A和矩阵B
    createMatrix(&A);   // 创建矩阵A
    createMatrix(&B);   // 创建矩阵B
    addMatrix(&A, &B);  // 将矩阵B的元素加到矩阵A中
    printMatrix(&A);    // 打印结果矩阵A
    return 0;
}
