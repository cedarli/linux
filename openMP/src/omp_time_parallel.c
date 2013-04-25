#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test() {
    int a = 0;
    int i = 0;
    for(i=0;i<100000000;i++)
        a++;
 }
 int main() {
    clock_t t1 = clock();
    int j=0;
#pragma omp parallel for
    for (j=0;j<8;j++)
        test();
    clock_t t2 = clock();
    printf("\ntime: =%d\n",t2-t1);
}
