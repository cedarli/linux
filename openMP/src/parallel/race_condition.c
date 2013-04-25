#include <stdlib.h>
#include <stdio.h>

int main() {
    int sum = 0;
    int i;
//#pragma omp parallel for
    for (i=0;i<100;i++)
        sum = sum + i;
    printf("sum:=%d\n",sum);
    return 0;
}
