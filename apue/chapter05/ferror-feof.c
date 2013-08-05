#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char * fname = "mnt/ferror-feof.dat";
    int i;
    FILE * fp = fopen(fname, "w");
    if(!fp)    {
        perror("fopen");
        exit(1);
    }
    for(i=0; i<2; ++i)
        fprintf(fp, "ABCDEFG");
    fclose(fp);

    printf("sleep for rm\n");
    fp = fopen(fname, "r");
    sleep(5);
    if(!fp) {
        perror("fopen");
        return 1;
    }

    int ch;
    fseek(fp, 100, SEEK_SET);
    while((ch = fgetc(fp)) >= 0) {
        fprintf(stderr, "%c", ch);
        //sleep(1);
    }
    printf("\nis feof: %d\n", feof(fp));
    printf("is ferror: %d\n", ferror(fp));


    return 0;
}
