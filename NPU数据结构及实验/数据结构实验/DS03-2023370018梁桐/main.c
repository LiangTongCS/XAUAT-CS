#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100 // 定义字符数组大小
#define M 199 // 定义树结构数组大小
// 定义树的结构体
typedef struct {
    int wei;    // 权重
    int par;    // 父节点
    int lift;   // 左子节点
    int right;  // 右子节点
} Tree[M + 1];  // 树结构数组

Tree tree = {};   // 初始化树结构数组
char zifu[N] = {};  // 初始化字符数组
int n;  // 字符数量

char *treec[N + 1];  // 定义存储编码后数据的数组

// 读取输入数据
void read() {
    int i;
    scanf("%d", &n);  // 输入字符数量
    for(i = 1; i <= n * 2; i++) {
        char c;
        scanf("%c", &c);
        if(c != ' ') {  // 避免读入空格键
            zifu[(i + 1) / 2] = c;  // 保存字符到字符数组
        }
    }
    for(i = 1; i <= n; i++)
        scanf("%d", &tree[i].wei);  // 输入权重
    return;
}

// 用于测试的读取数据函数
void read2() {
    n = 5;
    zifu[1] = 'a';
    zifu[2] = 'b';
    zifu[3] = 'c';
    zifu[4] = 'd';
    zifu[5] = 'e';
    tree[1].wei = 12;
    tree[2].wei = 40;
    tree[3].wei = 15;
    tree[4].wei = 8;
    tree[5].wei = 25;
    return;
}

// 选择权重最小的两个节点
void select1(int i, int *s1, int *s2) {
    int j;
    *s1 = *s2 = i;
    for(j = i; j >= 1; j--) {
        if(tree[j].wei < tree[*s1].wei && !tree[j].par) {
            *s2 = *s1;
            *s1 = j;
        }
        else if(tree[j].wei < tree[*s2].wei && !tree[j].par)
            *s2 = j;
    }
    return;
}

// 构建哈夫曼树
void make() {
    int m, i, s1, s2,c;
    m = 2 * n + 1;  // 总节点数
    for(i = n + 1; i <= m; i++) {
        select1(i - 1, &s1, &s2);  // 选择权重最小的两个节点
        if(s1 == s2) break;
        tree[i].wei = tree[s1].wei + tree[s2].wei;  // 合并节点的权重为子节点权重之和
        tree[s1].par = tree[s2].par = i;  // 更新父节点
        tree[i].lift = s1;
        tree[i].right = s2;
    }
    c=2;
    c=c*2;
}

// 编码
void code() {
    char *cd;
    int i, start, p, c;
    cd = (char *)malloc((n) * sizeof(char));  // 分配编码数组的内存空间
    cd[n - 1] = '\0';  // 设置字符串结束符
    for(i = 1; i <= n; i++) {
        start = n - 1;
        c = i;
        p = tree[i].par;
        while(p != 0) {
            --start;
            if(tree[p].lift == c)
                cd[start] = '0';  // 左子节点标记为'0'
            else if(tree[p].right == c)
                cd[start] = '1';  // 右子节点标记为'1'
            c = p;
            p = tree[p].par;
        }
        treec[i] = (char *)malloc((n - start ) * sizeof(char));  // 分配编码后数组的内存空间
        strcpy(treec[i], &cd[start]);  // 复制编码字符串到编码数组
    }
    free(cd);  // 释放编码数组的内存空间
}

// 解码并输出
void pri() {
    char s[100] = {};  // 输入的待解码字符串
    int j, k;
    scanf("%s", s);  // 输入待解码字符串
    int len = 0;
    while(s[len] != '\0')  // 计算输入字符串的长度
        len++;
    for(j = 0; j < len; j++) {
        for(k = 1; k <= n; k++) {
            if(s[j] == zifu[k]) {
                printf("%s", treec[k]);  // 输出对应字符的哈夫曼编码
            }
        }
    }
    printf("\n");
    printf("%s", s);  // 输出输入的待解码字符串
    return;
}

int main() {
    read();  // 读取测试数据
    make();  // 构建哈夫曼树
    code();  // 编码
    pri();   // 解码并输出
    return 0;
}
