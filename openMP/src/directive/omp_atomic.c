#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(){
    int sum = 0;
    int i;
    printf("Before sum=%d\n",sum);
#pragma omp parallel for
    for(i=0;i<100000;++i){
#pragma omp atomic
        sum++;
    }
    printf("After sum=%d\n",sum);
    return 0;
}
