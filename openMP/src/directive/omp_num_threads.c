#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
void main(int argc, char *argv[]) {
#pragma omp parallel num_threads(8)
    {
        printf("Hello, World!, ThreadId=%d\n", omp_get_thread_num() );
    }
}
