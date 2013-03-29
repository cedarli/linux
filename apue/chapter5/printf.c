#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define my_printf(fmt, args...) printf("\n=============\n%" fmt fmt, ##args) 

int main(int argc, const char *argv[])
{
    char buf[BUFSIZ];    
    my_printf("%10d\n", 0x01);
    my_printf("%.10d\n", 0x01);
    my_printf("%.10f\n", 1.001);
    my_printf("%5.10f\n", 1.001);
    my_printf("%25.10f\n", 1.001);
    my_printf("%025.10f\n", 1.001);
    my_printf("%zd\n", (size_t)(0x1<<31));
    my_printf("%%\n");
    my_printf("%0*.*f\n", 25, 10, 1.001);
    return 0;
}
