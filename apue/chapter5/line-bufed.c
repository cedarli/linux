#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *str = "hello";
    fwrite(str, strlen(str), 1, stdout);
    sleep(5);
    str = " and a new line\n";
    fwrite(str, strlen(str), 1, stdout);
    str = "a second new line\n";
    fwrite(str, strlen(str), 1, stdout);
    sleep(3);
    str = "a third new line\n";
    fwrite(str, strlen(str), 1, stdout);
    return 0;
}
