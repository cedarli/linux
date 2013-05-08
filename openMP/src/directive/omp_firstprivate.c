#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    int val=8;
    int i;
#pragma omp parallel for firstprivate(val) lastprivate(val)
    for(i=0;i<2;i++){
        printf("i=%d val=%d\n",i,val);
        if(i==1)
            val=10000;
        printf("i=%d val=%d\n",i,val);
    }
    printf("val=%d\n",val);
}

