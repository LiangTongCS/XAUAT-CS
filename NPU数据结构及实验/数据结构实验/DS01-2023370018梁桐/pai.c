#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

// 定义节点结构体
typedef struct Node {
    int num; // 数字
    int power; // 幂次
    struct Node* previous; // 前一个节点指针
    struct Node* next; // 后一个节点指针
} Node;

// 初始化链表
void init(Node* head, int m) {
    int temp_power = m; // 记录初始幂次
    Node* temp_node = head;
    // 从最高幂次到0逐个初始化节点
    for (; m >= 0; m--) {
        Node* newNode = (Node*)malloc(sizeof(Node)); // 分配新节点内存
        if (newNode) {
            if (m == temp_power) {
                newNode->num = 1; // 最高幂次的数字为1
            } else {
                newNode->num = 0;
            }
            newNode->power = m - temp_power; // 设置幂次
            temp_node->next = newNode; // 上一个节点指向新节点
            newNode->previous = temp_node; // 新节点指向上一个节点
            temp_node = newNode; // 更新临时节点为新节点
        }
    }
    temp_node->next = head; // 最后一个节点指向头节点
    head->previous = temp_node; // 头节点指向最后一个节点
}

// 数字乘法
void multiplyNumber(Node* head, int n) {
    int carry = 0; // 进位
    Node* currentNode = head->previous; // 从链表最后一个节点开始
    // 逐个节点进行乘法运算
    while (currentNode != head) {
        currentNode->num = (currentNode->num) * n + carry; // 当前节点数字乘以n并加上进位
        carry = (currentNode->num) / 10; // 计算新的进位
        currentNode->num = (currentNode->num) % 10; // 取余作为当前节点的数字
        currentNode = currentNode->previous; // 移动到上一个节点
    }
}

// 数字除法
void divideNumber(Node* head, int n) {
    int remainder = 0; // 余数
    Node* currentNode = head->next; // 从链表第一个节点开始
    // 逐个节点进行除法运算
    while (currentNode != head) {
        remainder = (currentNode->num) % n; // 计算余数
        currentNode->num = (currentNode->num) / n; // 更新当前节点的数字为商
        (currentNode->next)->num = (currentNode->next)->num + 10 * remainder; // 更新下一个节点的数字为原来的数字加上余数
        currentNode = currentNode->next; // 移动到下一个节点
    }
}

// 数字加法
void addNumber(Node* head1, Node* head2) {
    Node* currentNode1 = head1->previous; // head1从最后一个节点开始
    Node* currentNode2 = head2->previous; // head2从最后一个节点开始
    int carry = 0; // 进位
    // 逐个节点进行加法运算
    while (currentNode1 != head1) {
        currentNode2->num = (currentNode2->num) + (currentNode1->num) + carry; // 当前节点相加并加上进位
        carry = (currentNode2->num) / 10; // 计算新的进位
        currentNode2->num = (currentNode2->num) % 10; // 取余作为当前节点的数字
        currentNode1 = currentNode1->previous; // 移动到上一个节点
        currentNode2 = currentNode2->previous; // 移动到上一个节点
    }
}

// 主函数
int main() {
    int x;
    scanf("%d", &x); // 读取输入的数字

    // 创建两个头节点
    Node* head1 = (Node*)malloc(sizeof(Node));
    Node* head2 = (Node*)malloc(sizeof(Node));
    head1->next = head1->previous = NULL; // 头节点初始化为空
    head2->next = head2->previous = NULL; // 头节点初始化为空

    if (head1 && head2) {
        init(head1, 550); // 初始化链表1，幂次为550
        init(head2, 550); // 初始化链表2，幂次为550
        int n;
        // 循环计算5000次
        for (n = 1; n <= 5000; n++) {
            int temp = 2 * n + 1; // 计算除数
            divideNumber(head1, temp); // 链表1除以temp
            multiplyNumber(head1, n); // 链表1乘以n
            addNumber(head1, head2); // 链表1和链表2相加
        }
        multiplyNumber(head2, 2); // 链表2乘以2
    }

    printf("3."); // 输出小数点前的数字
    Node* currentNode = head2->next;
    for (; x > 0; x--) {
        currentNode = currentNode->next;
        printf("%d", currentNode->num); // 输出小数点后的数字
    }

    return 0;
}
