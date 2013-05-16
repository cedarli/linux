#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>

#define SIZEARRAY 10
int main(){
    int a[SIZEARRAY];
    int i,j;
    for (i=0;i<=SIZEARRAY;i++)
        a[i] = i;

#pragma omp parallel for ordered
    for (i=0;i<=SIZEARRAY;i++){
#pragma omp ordered
        {
            a[i] = a[i]+a[i+1];
        }
        usleep(100);
        printf("a[%d]=%d;threadid=%d\n",i,a[i],omp_get_thread_num());
    }

    for (i=0;i<=SIZEARRAY;i++)
        printf("%d ",a[i]);
}
