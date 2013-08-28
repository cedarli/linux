#include <stdio.h>
#include <stdlib.h>
#include <list.h>

int main()
{
    Node *pList=NULL;

    elemType posElem;

    initList(&pList);
    printList(pList);

    pList=creatList(pList);
    printList(pList);

    sizeList(pList);
    printList(pList);

    isEmptyList(pList);

    posElem = getElement(pList,3);
    printf("getElement函数执行，位置 3 中的元素为 %d\n",posElem);
    printList(pList);

    getElemAddr(pList,5);

    modifyElem(pList,4,1);
    printList(pList);

    insertHeadList(&pList,5);
    printList(pList);

    insertLastList(&pList,10);
    printList(pList);

    clearList(pList);
    system("pause");
    return 0;
}
