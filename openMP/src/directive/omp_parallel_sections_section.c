#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>

void main() {
#pragma omp parallel sections
    {
        printf("num threads=%d\n",omp_get_num_threads());
#pragma omp section
        {
            printf("section 1 ThreadId = %d\n", omp_get_thread_num());
            sleep(1);
        }

#pragma omp section
        {
            printf("section 2 ThreadId = %d\n", omp_get_thread_num());
            sleep(1);
        }

#pragma omp section
        {
            printf("section 3 ThreadId = %d\n", omp_get_thread_num());
            sleep(1);
        }

#pragma omp section
        {
            printf("section 4 ThreadId = %d\n", omp_get_thread_num());
            sleep(1);
        }
    }
}
