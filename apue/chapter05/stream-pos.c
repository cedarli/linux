#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char * fname = "stream-pos.dat";
    FILE *fp = fopen(fname, "w");
    int i;
    assert(fp);

    for(i='a'; i<='z'; ++i)
        fputc(i, fp);
    for(i='A'; i<='Z'; ++i)
        fputc(i, fp);
    fclose(fp);

    fp = fopen(fname, "r+");
    assert(fp);
    setbuf(fp, NULL);
    printf("ftell: %ld\n", ftell(fp));
    printf("fgetc: %c\n", fgetc(fp));
    printf("ftell: %ld\n", ftell(fp));
    printf("fputc: %c\n", fputc('0', fp));
    printf("ftell: %ld\n", ftell(fp));

    fseek(fp, 3, SEEK_CUR);
    printf("fgetc after seek forward 3: %c\n", fgetc(fp));
    rewind(fp);
    printf("fgetc after rewind: %c\n", fgetc(fp));

    printf("sizeof(off_t)=%ld\n", sizeof(off_t));
    printf("ftello: %d\n", ftello(fp));

    fpos_t fpos;
    fgetpos(fp, &fpos);
    printf("fgetc: %c\n", fgetc(fp));
    fsetpos(fp, &fpos);
    printf("fgetc: %c\n", fgetc(fp));

    return 0;
}
