#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //printf("fwide of stdout: %d\n", fwide(stdout, 0));
    assert(fwide(stdout, 1) > 0);
    printf("fwide of stdout: %d\n", fwide(stdout, 1));
    freopen("freopen.dat", "w", stdout);
    assert(fwide(stdout, 1) > 0);
    printf("fwide of stdout: %d\n", fwide(stdout, 0));
    printf("hello world");
    return 0;
}
