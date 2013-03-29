#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char * fname = "ungetc.dat";
    FILE * fp = fopen(fname, "w");
    if(!fp)    {
        perror("fopen");
        exit(1);
    }
    fprintf(fp, "ABC");
    fclose(fp);
    fp = fopen(fname, "r");
    char ch = fgetc(fp);
    fprintf(stderr, "read before ungetc: %c\n", ch);

    ungetc(ch, fp);
    ungetc('Z', fp);
    ch = fgetc(fp);
    fprintf(stderr, "%c", ch);
    ch = fgetc(fp);
    fprintf(stderr, "%c", ch);
    ch = fgetc(fp);
    fprintf(stderr, "%c", ch);

    return 0;
}
