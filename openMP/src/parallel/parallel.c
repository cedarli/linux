#include <stdlib.h>
#include <stdio.h>
int main() {
    int i;
#pragma omp parallel for
    for (i=0;i<9;i++){
        if (i>=4){
            printf("\n");
        }
        printf("%d ",i);
    }
    printf("\n");
    return 0;
}
