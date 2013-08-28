#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <string.h>

/************************************************************************/
/*             以下是关于线性表链接存储（单链表）操作的18种算法        */
/* 1.初始化线性表，即置单链表的表头指针为空 */
/* 2.创建线性表，此函数输入负数终止读取数据*/
/* 3.打印链表，链表的遍历*/
/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
/* 5.返回单链表的长度 */
/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
/* 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行 */
/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
/* 9.把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０ */
/* 10.向单链表的表头插入一个元素 */
/* 11.向单链表的末尾添加一个元素 */
/* 12.向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０ */
/* 13.向有序单链表中插入元素x结点，使得插入后仍然有序 */
/* 14.从单链表中删除表头结点，并把该结点的值返回，若删除失败则停止程序运行 */
/* 15.从单链表中删除表尾结点并返回它的值，若删除失败则停止程序运行 */
/* 16.从单链表中删除第pos个结点并返回它的值，若删除失败则停止程序运行 */
/* 17.从单链表中删除值为x的第一个结点，若删除成功则返回1,否则返回0 */
/* 18.交换2个元素的位置 */
/* 19.将线性表进行快速排序 */
/************************************************************************/

/* 1 init list to NULL */
void initList(Node **pNode) {
    *pNode = NULL;
     printf("initList scuess\n");
}
/* b.create list*/
Node *creatList(Node *pHead) {
    Node *p1;
    Node *p2;
    p1=p2=(Node *)malloc(sizeof(Node)); //申请新节点
    if(p1 == NULL || p2 ==NULL) {
        printf("malloc fail\n");
        return NULL;
    }
    memset(p1,0,sizeof(Node));
    scanf("%d",&p1->element); //输入新节点
    p1->next = NULL; //新节点的指针置为空
    while(p1->element > 0) {//输入的值大于0则继续，直到输入的值为负
        if(pHead == NULL) {
            pHead = p1;
        } else {
            p2->next = p1;//非空表，接入表尾
        }
        p2 = p1;
        p1=(Node *)malloc(sizeof(Node));//再重申请一个节点
        if(p1 == NULL || p2 ==NULL) {
            printf("malloc failed\n");
            return NULL;
        }
        memset(p1,0,sizeof(Node));
        scanf("%d",&p1->element);
        p1->next = NULL;
    }
    printf("creatList ok\n");
    return pHead;//return list head
}

/* 3.print list every node */
void printList(Node *pHead) {
    if(NULL == pHead) { //list is empty
        printf("PrintList函数执行，链表为空\n");
    } else {
        while(NULL != pHead) {
            printf("%d ",pHead->element);
            pHead = pHead->next;
        }
        printf("\n");
    }
}

/* 4.Empty list*/
void clearList(Node *pHead) {
    Node *pNext;//定义一个与pHead相邻节点
    if ( pHead == NULL ) {
        printf("clearList done\n");
        return;
    }
    while(pHead->next != NULL) {
        pNext = pHead->next;
        free(pHead);
        pHead = pNext;
    }
    printf("clearList函数执行，链表已经清除\n");
}

/* 5.Return list length*/
int sizeList(Node *pHead) {
    int size = 0;
    while(pHead != NULL) {
        size++;
        pHead = pHead->next;
    }
    printf("list length: %d\n",size);
    return size;
}

/* 6.empty list retorn 1 when empty ok;0 when empty fail */
int isEmptyList(Node *pHead) {
    if(pHead == NULL) {
        printf("test list is empty\n");
        return 1;
    }
    printf("empty ok\n");
    return 0;
}

/* 7.return pos node */
elemType getElement(Node *pHead, int pos) {
    int i=0;
    if(pos < 1) {
        printf("pos error\n");
        return -1;
    }
    if(pHead == NULL) {
        printf("list empty please check\n");
        return 0;
    }
    while(pHead !=NULL) {
        ++i;
        if ( i == pos ) {
             break;
        }
        pHead = pHead->next;
    }
    if ( i < pos ) {
        printf("list not find this pos\n");
        return 0;
    }
    return pHead->element;
}

/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
elemType *getElemAddr(Node *pHead, elemType x)
{
    if ( NULL == pHead ) {
        printf("\n");
        return NULL;
    }
    if ( x < 0 ) {
        printf("getElemAddr函数执行，给定值X不合法\n");
        return NULL;
    }
    while ( (pHead->element != x ) && (NULL != pHead->next)) {
        pHead = pHead->next;
    }
    if((pHead->element != x) && (pHead != NULL)) {
        printf("getElemAddr not find x\n");
        return NULL;
    }
    if(pHead->element == x) {
        printf("getElemAddr %d 0x%x\n",x,&(pHead->element));
    }
    return &(pHead->element);//返回元素的地址
}

/* 9.把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０ */
int modifyElem(Node *pNode,int pos,elemType x) {
    Node *pHead;
    pHead = pNode;
    int i = 0;

    if(NULL == pHead) {
        printf("empty list.\n");
    }
    if(pos < 1) {
        printf("error pos\n");
        return 0;
    }
    while(pHead !=NULL) {
        ++i;
        if(i == pos) {
            break;
        }
        pHead = pHead->next;
    }
    if ( i < pos ) {
        printf("modifyElem函数执行，pos值超出链表长度\n");
        return 0;
    }
    pNode = pHead;
    pNode->element = x;
    printf("modifyElem函数执行\n");
    return 1;
}

/* 10.insert element at the begin of list*/
int insertHeadList(Node **pNode,elemType insertElem) {
    Node *pInsert;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert,0,sizeof(Node));
    pInsert->element = insertElem;
    pInsert->next = *pNode;
    *pNode = pInsert;
    printf("insert element at the begin of list ok.\n");
    return 1;
}

/* 11.insert element at the end of list*/
int insertLastList(Node **pNode,elemType insertElem)
{
    Node *pInsert;
    Node *pHead;
    Node *pTmp;

    pHead = *pNode;
    pTmp = pHead;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert,0,sizeof(Node));
    pInsert->element = insertElem;

    while(pHead->next != NULL) {
        pHead = pHead->next;
    }
    pHead->next = pInsert;
    *pNode = pTmp;
    printf("insert element at the end of list ok.\n");

    return 1;
}
