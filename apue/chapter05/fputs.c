#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *str = "hello\nworld";
    fputs(str, stdout);
    puts(str);
    puts("=========================");
    return 0;
}
