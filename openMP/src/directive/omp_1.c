#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
    int i;

#pragma omp parallel for
    for ( i = 0; i < 10; i++ ){
        printf("i = %d\n", i);
    }
    return 0;
}
