#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));
    fprintf(stderr, "before");
    sleep(3);
    fprintf(stderr, " setvbuf\n");

    setvbuf(stderr, buf, _IOLBF, sizeof(buf));
    fprintf(stderr, "after");
    sleep(3);
    fprintf(stderr, " setvbuf\n");
    pause();
    return 0;
}
