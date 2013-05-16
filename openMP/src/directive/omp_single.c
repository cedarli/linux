#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main() {
    int i;
#pragma omp single
    for ( i = 0; i < 4; i++ ){
        printf("i = %d omp_thread=%d num threads=%d\n", i,omp_get_thread_num(),omp_get_num_threads());
    }
    return 0;
}
