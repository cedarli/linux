#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#define MAXLINE 1024
#define DEF_PAGER   "/bin/more"     /* default pager program */

int main(int argc, char *argv[])
{
    int    n;
    int    fd[2];
    pid_t  pid;
    char   *pager, *argv0;
    char   line[MAXLINE];
    FILE   *fp;	

    if (argc != 2){
        perror("usage: ./a.out filename");
		exit(-1);
	}
    if ((fp = fopen(argv[1], "r")) == NULL)
        printf("can't open %s", argv[1]);
	/*pipe*/
    if (pipe(fd) < 0)
        printf("pipe error");
	/*fork*/
    if ((pid = fork()) < 0) {					/*much things to explain*/
        printf("fork error");
    } else if (pid > 0) { 
        close(fd[0]); 					//output

        while (fgets(line, MAXLINE, fp) != NULL) {	//get the whole file content.
            n = strlen(line);						// does a string must be termitted by '\0'
            if (write(fd[1], line, n) != n)
                printf("write error to pipe");
        }
        if (ferror(fp))								// if theres error, error indexer would be return.
            printf("fgets error");

        close(fd[1]);   /* close write end of pipe for reader */

        if (waitpid(pid, NULL, 0) < 0)
            printf("waitpid error");
        exit(0);
    } else {
        close(fd[1]);   //input;write
        if (fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)   		//if equals , dup2 would do nothing , just return newfd
                printf("dup2 error to stdin");
            close(fd[0]);   /* don't need this after dup2 */
        }

        /* get arguments for execl() */
        if ((pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;									//bin/more
        if ((argv0 = strrchr(pager, '/')) != NULL)				//strchr * strrchr
            argv0++;        /* step past rightmost slash */
        else
            argv0 = pager;  /* no slash in pager */

        if (execl(pager, argv0, (char *)0) < 0)					//by convetion, argv0 is the name .
            printf("execl error for %s", pager);

    }
    exit(0);
}

