#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <string.h>

/* 1 init list to NULL */
void *createList() {
    LIST *pList = (LIST *)malloc(sizeof(LIST));
    if ( pList != NULL ){
        memset(pList,0,sizeof(LIST));
        pList->list = NULL;
        return pList;
    }
    return NULL;
}

/* 3.print list every node */
void printList(LIST *pList) {
    Node *pNode = pList->list;
    if(NULL == pList->list) {
        printf("PrintList empty List\n");
    } else {
        while(NULL != pNode) {
            pList->printElement(pNode->element);
            pNode = pNode->next;
        }
    }
}

/* 4.Empty list*/
void clearList(LIST *pList) {
    Node *pNext;
    Node *pNode;
    if ( pList->list == NULL ) {
        printf("clearList done\n");
        return;
    }
    pNode = pList->list;
    while ( pNode != NULL ) {
        pNext = pNode->next;
        pList->freeElement(pNode->element);
        free(pNode);
        pNode = pNext;
    }
}

/* 5.Return list length*/
int sizeList(LIST *pList) {
    int size = 0;
    Node *pHead;
    pHead = pList->list;
    while(pHead != NULL) {
        size++;
        pHead = pHead->next;
    }
    return size;
}

/* 6.empty list retorn 1 when empty ok;0 when empty fail */
int isEmptyList(LIST *pList) {
    if(pList->list == NULL) {
        printf("test list is empty\n");
        return 1;
    }
    return 0;
}

/* 7.return pos node */
void * getElement(LIST *pList, int pos) {
    int i=0;
    if(pos < 1) {
        printf("pos error\n");
        return NULL;
    }
    Node *pHead = pList->list;
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
        return 0;
    }
    return pHead->element;
}

/* 8.find out equal with x in pList */
void *getElemAddr(LIST *pList, void *x)
{
    Node *pNode = pList->list;
    if ( NULL == pNode ) {
        return NULL;
    }

    while ( (pList->compare(pNode->element,x)) && (NULL != pNode->next)) {
        pNode = pNode->next;
    }
    if ( pList->compare(pNode->element,x) ) {
        return pNode->element;
    }
    return NULL;
}

/* 9.modify element at pos value to x,rturn 1 success,otherwise return 0 */
int modifyElem(LIST *pList,int pos,void *x) {
    Node *pNode;
    int i = 0;
    pNode = pList->list;
    if(NULL == pNode) {
        printf("empty list.\n");
    }
    if(pos < 1) {
        printf("error pos\n");
        return 0;
    }
    while(pNode !=NULL) {
        ++i;
        if(i == pos) {
            break;
        }
        pNode = pNode->next;
    }
    if ( i < pos ) {
        return 0;
    }
    pList->assignment(pNode->element,x);
    return 1;
}

/* 10.insert element at the begin of list*/
int insertHead(LIST *pList,void *element) {
    Node *pInsert,*pHead;
    pHead = pList->list;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert,0,sizeof(Node));
    pInsert->element = element;
    pInsert->next = pHead;
    pList->list = pInsert;
    return 1;
}

/* 11.insert element at the end of list*/
int insertLast(LIST *pList,void *element)
{
    Node *pInsert;
    Node *pNode;
    pNode = pList->list;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert,0,sizeof(Node));
    pInsert->element = element;
    pInsert->next = NULL;
    while( pNode != NULL ) {
        pNode = pNode->next;
    }
    pNode->next = pInsert;
    return 1;
}
