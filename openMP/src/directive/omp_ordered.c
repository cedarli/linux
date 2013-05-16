// omp_ordered.cpp
// compile with: /openmp 
#include <stdio.h>
#include <omp.h>

static float a[1000], b[1000], c[1000];

void test(int first, int last) {
    int i;
    #pragma omp for schedule(static) ordered
    for (i = first; i <= last; ++i) {
        // Do something here.
        if (i % 2) {
            #pragma omp ordered
            printf("test() iteration %d;threadid=%d\n", i,omp_get_thread_num());
        }
    }
}

void test2(int iter) {
    #pragma omp ordered
    printf("test2() iteration %d;threadid=%d\n", iter,omp_get_thread_num());
    sleep(1);
}

int main() {
    int i;
    #pragma omp parallel
    {
        printf("num threads=%d\n",omp_get_num_threads());
        test(1, 8);
        #pragma omp for ordered
        for (i = 0 ; i < 5 ; i++)
            test2(i);
    }
}
