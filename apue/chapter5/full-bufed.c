#include <stdio.h>
#include <wchar.h>
#include <assert.h>


int main() {
    char buf[BUFSIZ];
    FILE *fp = fopen("full-buffered.dat", "w");
    char ch;
    fwrite(buf, BUFSIZ-1, 1, fp);
    ch = getchar();

    fwrite(buf, 1, 1, fp);
    _exit(0);
    getchar();
    // fflush(fp);

    fwrite(buf, 1, 1, fp);
    getchar();
    return 0;
}
