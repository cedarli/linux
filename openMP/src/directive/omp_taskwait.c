//fib(n) = fib(n-1) -fib(n-2)
#include <stdio.h>
#include <omp.h>
int fib(int n){
    printf("n=%d;threadid=%d\n",n,omp_get_thread_num());
    int i, j;
    if (n<2)
        return n;
    else {
#pragma omp task shared(i) firstprivate(n)
        i=fib(n-1);
#pragma omp task shared(j) firstprivate(n)
        j=fib(n-2);
#pragma omp taskwait
        return i+j;
    }
}

int main() {
    int n = 10;
    omp_set_dynamic(0);
    omp_set_num_threads(4);
    #pragma omp parallel shared(n)
    {
        #pragma omp single
        printf ("fib(%d) = %d\n", n, fib(n));
    }
}
