#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAXLINE 1024

int main(void)
{
    int     n,  int1,  int2;
    char    line[MAXLINE];

    while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {	//use space to interrupt the two operants!!!
        line[n] = 0;        								/* null terminate */
        if (sscanf(line, "%d%d", &int1, &int2) == 2) {
            sprintf(line, "%d\n", int1 + int2);
            n = strlen(line);
            if (write(STDOUT_FILENO, line, n) != n)
                printf("write error");
        } else {
            if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
                printf("write error");
        }
    }
    exit(0);
}

