#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main(int argc, char* argv[]) {
    int i;
    int j=1;

#pragma omp parallel for num_threads(4)
    for ( i = 0; i < 10; i++ ){
        printf("i = %d omp_thread=%d\n", i,omp_get_thread_num());
    }
    return 0;
}
