#include <stdio.h>
#include <errno.h>

void pr_stdio(const char *name, FILE *fp);

int main(int argc, const char *argv[])
{
    FILE *fp;
    fputs("enter any character\n", stdout);
    if(getchar() == EOF) {
        printf("getchar error\n");
        return 1;
    }
    fputs("one line to standard error\n", stderr);

    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if((fp = fopen("/etc/inputrc", "r")) == NULL) {
        perror("fopen");
        return 2;
    }

    if(getc(fp) == EOF) {
        printf("getc error\n");
    }

    pr_stdio("/etc/inputrc", fp);
    return 0;
}


void
pr_stdio(const char * name, FILE *fp) {
    printf("stream = %s, ", name);
    if(fp->_IO_file_flags & _IO_UNBUFFERED)
        printf("unbuffered");
    else if(fp->_IO_file_flags & _IO_LINE_BUF)
        printf("line buffered");
    else
        printf("fully buffered");
    printf(", buffer size  = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}
