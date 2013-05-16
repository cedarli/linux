#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main(){
    int i;
    int j;
#pragma omp parallel
    {
        for(i = 0; i < 4; ++i){
            printf("i=%d threadid=%d;num threads=%d\n",i,omp_get_thread_num(),omp_get_num_threads());
        }
#pragma omp barrier
        for(j = 0; j < 4; ++j){
            printf("j=%d threadid=%d;num threads=%d\n",j,omp_get_thread_num(),omp_get_num_threads());
        }
    }
}
