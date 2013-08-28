#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 1024
#define PAGER   "${PAGER:-more}" /* environment variable, or default */

int main(int argc, char *argv[])
{
    char    line[MAXLINE];
    FILE    *fpin, *fpout;

    if(argc != 2){
        perror("usage: a.out <pathname>");
		exit(-1);
	}
    if ((fpin = fopen(argv[1], "r")) == NULL)
        printf("can't open %s", argv[1]);

    if ((fpout = popen(PAGER, "w")) == NULL)   //the child process sd input
        perror("popen error");

    /* copy argv[1] to pager */
    while (fgets(line, MAXLINE, fpin) != NULL) {
        if (fputs(line, fpout) == EOF)			//write
            perror("fputs error to pipe");
    }
    if (ferror(fpin))
        perror("fgets error");
    if (pclose(fpout) == -1)
        perror("pclose error");
		//is fclose  closed?
    exit(0);
}

