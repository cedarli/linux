#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(){
    int i;
    int j;
#pragma omp parallel for private(j) //collapse(2)
    for (i=0;i<2;i++){

//#pragma omp parallel for 
        for(j=2;j<10;j++){
            printf("i=%d;j=%d;num threads=%d;threadid=%d\n",i,j,omp_get_num_threads(),omp_get_thread_num());
            sleep(1);
        }
    }
    return 0;
}
