#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i;
    for(i=0; i<5; ++i) {
        fputc('1'+i, stdout);
        sleep(1);
    }
    fputc('\n', stdout);

    for(i=0; i<10; ++i) {
        fputc('a'+i, stderr);
        sleep(1);
    }
    return 0;
}
