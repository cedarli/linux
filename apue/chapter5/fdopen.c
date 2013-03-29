#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const int fd2 = 5;
    dup2(STDOUT_FILENO, fd2);
    FILE *fp = fdopen(fd2, "w");
    fprintf(fp, "fdopen: hello world\n");
    return 0;
}
