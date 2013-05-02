#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void test() {
    int a,i = 0;
    clock_t t1 = clock();
    for ( i = 0; i < 100000000; i++) {
        a = i+1;
    }
    clock_t t2 = clock();
    printf("Time = %d\n", t2-t1);
}

int main(int argc, char* argv[]) {
    int j;
    clock_t t1 = clock();
#pragma omp parallel for
    for (j = 0; j < 2; j++ ){
        test();
    }
    clock_t t2 = clock();
    printf("Total time = %d\n", t2-t1);
    test();
    return 0;
}
