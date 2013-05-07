#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    #pragma omp parallel
    {
        printf("Hello, world.\n");
    }
    printf("parallel out\n");

    return 1;
}
