#include <stdio.h>
#include <stdlib.h>
#include <list.h>

typedef struct listnode{
    int a;
    int b;
}Listnode;
void printElement(void * element){
    Listnode *pListnode = (Listnode *)element;
    printf("printElement a =%d,b=%d\n",pListnode->a,pListnode->b);
}
int main()
{
    LIST *pList = createList();
    pList->printElement = printElement;
    printf("test main %p\n",pList);

    Listnode node;
    node.a =1;
    node.b =2;
    printf("insert head\n");
    insertHead(pList,&node);
    printList(pList);
    return 0;

}
