#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define 	MAXLINE 1024

int main(void)
{
    char    line[MAXLINE];
    FILE    *fpin;

    if ((fpin = popen("./filter", "r")) == NULL) //return the child's stdout
        printf("popen error");
	
    for (;;) {
        fputs("prompt> ", stdout);    			//stdout: FILE
		fflush(stdout);
	   if (fgets(line, MAXLINE, fpin) == NULL)  /* read from pipe */
            break;
        if (fputs(line, stdout) == '\n')
			break;
    	
	}
    if (pclose(fpin) == -1)
        printf("pclose error");
    putchar('\n');
    exit(0);
}

