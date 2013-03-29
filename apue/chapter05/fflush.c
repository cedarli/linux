#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    fprintf(stdout, "hello ");
    fflush(stdout);
    sleep(3);
    fprintf(stdout, "world\n");
    pause();
    return 0;
}
