#include<stdio.h>
#include<stdlib.h>

#define MAXLINE 1024
int main(void)
{
    int     int1, int2;
    char    line[MAXLINE];

	if(setvbuf(stdin,NULL,_IOLBF,0) != 0)
		perror("setvbuf error\n");
	if(setvbuf(stdout,NULL,_IOLBF,0) != 0)
		perror("stdout failed\n");

    while (fgets(line, MAXLINE, stdin) != NULL) {
        if (sscanf(line, "%d%d", &int1, &int2) == 2) {
            if (printf("%d\n", int1 + int2) == EOF)
                perror("printf error");
        } else {
            if (printf("invalid args\n") == EOF)
                perror("printf error");
        }
    }
    exit(0);
}

