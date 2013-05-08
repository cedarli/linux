#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int i;
    int j;
#pragma omp parallel for private(j)
    for (i=0;i<2;i++)
//#pragma omp parallel for 
        for(j=6;j<10;j++)
            printf("i=%d;j=%d\n",i,j);
    return 0;
}
