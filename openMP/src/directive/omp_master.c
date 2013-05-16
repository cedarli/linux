#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(){
    int j;
#pragma omp parallel
    {
        #pragma omp master
        {
            for(j = 0; j < 10; ++j)  {
                printf("j=%d;threadid=%d;num threads=%d\n",j,omp_get_thread_num(),omp_get_num_threads());
            }
        }
        printf("this print twice ;threadid=%d;num threads=%d\n",omp_get_thread_num(),omp_get_num_threads());
    }
    return 0;
}
