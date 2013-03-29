#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    char *buf = malloc(BUFSIZ);
    printf("TMP_MAX=%d\n", TMP_MAX);
    printf("tmpnam(NULL)=%s\n", tmpnam(NULL));
    printf("tmpnam(buf)=%s\n", tmpnam(buf));
    printf("buf=%s\n", buf);

    memset(buf, 0, BUFSIZ);

    FILE *fp = tmpfile();
    fprintf(fp, "hello world!");
    fflush(fp);
    fsync();

    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%[a-z! ]", buf);
    printf("content read from tmpfile: %s\n", buf);
    fclose(fp);

    return 0;
}
