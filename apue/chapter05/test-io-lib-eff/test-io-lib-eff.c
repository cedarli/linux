#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    char buf[BUFSIZ];    
    /* printf("BUFSIZ=%d\n", BUFSIZ); */
    while(fread(buf, BUFSIZ, 1, stdin) != 0) {
        if(fwrite(buf, BUFSIZ, 1, stdout) < 1) {
            perror("fputs");
            return 1;
        }
    }
    if(ferror(stdin)) {
        printf("ferror of stdin\n");
    }
    fsync(fileno(stdout));
    return 0;
}
