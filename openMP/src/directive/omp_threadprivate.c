#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int threaded_var;
#pragma omp threadprivate(threaded_var)
int main(){

#pragma omp parallel
    {
        if (omp_get_thread_num() != 0)
            threaded_var++;
        printf("threaded_var=%d ;threadid=%d\n",threaded_var,omp_get_thread_num());
    }
}
