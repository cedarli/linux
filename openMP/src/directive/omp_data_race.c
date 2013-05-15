#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define SIZEARRAY 10
int main(){
    int a[SIZEARRAY];
    int i,j;
    for (i=0;i<=SIZEARRAY;i++)
        a[i] = i;

#pragma omp parallel for
    for (i=0;i<=SIZEARRAY;i++){
        a[i] = a[i]+a[i+1];
        usleep(100);
        printf("a[%d]=%d\n",i,a[i]);
    }

    for (i=0;i<=SIZEARRAY;i++)
        printf("%d ",a[i]);
}
