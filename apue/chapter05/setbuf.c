#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buf[BUFSIZ];
    memset(buf, 0, sizeof(buf));
    FILE * fp = fopen("setbuf.dat", "w");
    setbuf(fp, buf);
    fprintf(fp, "hello world");
    printf("in buf: %s\n", buf);
    return 0;
}
