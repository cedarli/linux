#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int gval=8;
void funcb(int * x, int *y, int z){
    printf("*x=%d,*y=%d\n",*x,*y);
    static int sv;
    int u;
    u=(*y)*gval;
    *x=u+z;
}

void funca(int * a, int n){
    int i;
    int cc=9;
#pragma omp parallel for
    for(i=0;i<n;i++){
        int temp=cc;
        funcb(&a[i],&temp,i);
    }
}

int a[10] = {1,2,3,4,5,6,7,8,9,0};
int main(){
    funca(a,10);
    return 0;
}
