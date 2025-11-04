#include <stdio.h>
#include <stdlib.h>
typedef int ShuJuLeiXing;
typedef struct  LianBiaoJieDian//链表结点定义
{
        ShuJuLeiXing  shuZi;
        struct LianBiaoJieDian  *next;
}lianBiaoJieDian;
typedef struct  LianBiaoJieDian *PlianBiaoJieDian;
typedef struct LianBiao//链表定义
{
        PlianBiaoJieDian  head;
}lianBiao;
typedef struct  LianBiao *PlianBiao;


PlianBiao ChuangJianTouJieDianLianBiao();
void chaRu(PlianBiao biao,ShuJuLeiXing shuzi,PlianBiaoJieDian jieDian);
void PrintLinkedList(PlianBiao biao);
void MergeListsAscending(PlianBiao biao1, PlianBiao biao2, PlianBiao biao3);

int main()
{
    PlianBiao biao1,biao2,biao3;
    biao1=ChuangJianTouJieDianLianBiao();
    biao2=ChuangJianTouJieDianLianBiao();
    biao3=ChuangJianTouJieDianLianBiao();
    int Length1,Length2,i;
    PlianBiaoJieDian p1 = biao1->head;
    PlianBiaoJieDian p2 = biao2->head;
    scanf("%d",&Length1);

    for (i = 0; i < Length1; i++) {
        ShuJuLeiXing shuzi;
        scanf("%d", &shuzi);
        // 调用插入函数将数字插入链表1
        chaRu(biao1, shuzi, p1);
        p1 = p1->next;
    }
    scanf("%d",&Length2);
    for (i = 0; i < Length2; i++) {
        ShuJuLeiXing shuzi;
        scanf("%d", &shuzi);
        chaRu(biao2, shuzi, p2);
        p2 = p2->next;
    }
    MergeListsAscending(biao1,biao2,biao3);
    PrintLinkedList(biao3);

//    PrintLinkedList(biao1);
//    PrintLinkedList(biao2);
    return 0;
}

void chaRu(PlianBiao biao,ShuJuLeiXing shuzi,PlianBiaoJieDian jieDian)
{
    /* 在单链表中 jieDian 所指结点的后面插入元素 shuzi */
        PlianBiaoJieDian  newJieDian;
        newJieDian = (PlianBiaoJieDian)malloc( sizeof( struct LianBiaoJieDian ) );
        if ( newJieDian == NULL )
                printf( "错误！\n" );
        else {
                newJieDian->shuZi = shuzi;
                newJieDian->next = jieDian->next;
                jieDian->next = newJieDian;
        }
}

PlianBiao ChuangJianTouJieDianLianBiao()
/* 创建一个带头结点的空链表 */
{
    PlianBiao  biao;
    PlianBiaoJieDian  jieDian;

    biao = (PlianBiao)malloc(sizeof(struct LianBiao));

    if (biao != NULL) {
        jieDian = (PlianBiaoJieDian)malloc(sizeof(struct LianBiaoJieDian));

        if (jieDian != NULL) {
            biao->head = jieDian;
            jieDian->next = NULL;
        } else {
            printf("内存不足！\n");
            biao->head = NULL;
        }
    } else {
        printf("内存不足！\n");
    }

    return biao;
}

void PrintLinkedList(PlianBiao biao)
{
    PlianBiaoJieDian current = biao->head->next; // 获取链表的第一个节点
    while (current != NULL) {
        printf("%d\n", current->shuZi); // 输出当前节点的数字
        current = current->next; // 移动到下一个节点
    }
    printf("\n"); // 输出换行符
}


void MergeListsAscending(PlianBiao biao1, PlianBiao biao2, PlianBiao biao3)
{
    PlianBiaoJieDian pa, pb, pc;
    pa = biao1->head->next;  // 获取链表1的第一个节点
    pb = biao2->head->next;  // 获取链表2的第一个节点
    biao3->head = pc = biao1->head;  // 将链表3的头指针指向链表1的头节点

    while (pa && pb) {
        if (pa->shuZi <= pb->shuZi) {
            pc->next = pa;
            pc = pc->next;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pc->next;
            pb = pb->next;
        }
    }

    pc->next = pa ? pa : pb;  // 将剩余的节点链接到链表3中
}



