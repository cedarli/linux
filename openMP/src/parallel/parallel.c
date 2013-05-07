#include <stdlib.h>
#include <stdio.h>
int main() {
    int i;
    int sum=0;
#pragma omp parallel for
    for (i=0;i<9;i++){
        printf("%d ",i);
        usleep(1000);
        sum+=i;
    }
    printf("sum=%d \n",sum);
    return 0;
}
