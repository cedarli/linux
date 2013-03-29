#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *fname = "fopen-a+.dat";
    FILE *fp = fopen(fname, "w");
    assert(fp);
    for(char ch='A'; ch<'Z'; ++ch)
        fputc(ch, fp); 
    fclose(fp);

    fp = fopen(fname, "a+");
    assert(fp);
    int ch = fgetc(fp);
    printf("fgetc when open with a+: %c=0x%X\n", ch, ch);
    fputc('@', fp);
    fseek(fp, 2, SEEK_SET);
    ch = fgetc(fp);
    if(ch < 0 && feof(fp)) {
        printf("read a char after write, feof is true\n");
    }
    printf("fgetc when open with a+: %c=0x%X\n", ch, ch);
    fputc('#', fp);


    return 0;
}
