#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 512

int main (void){
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    if ( pipe(fd) < 0 )
        printf("pipe error\n");
    if ( (pid = fork()) < 0 ) {
        printf("fork error\n");
    } else if ( pid > 0 ) {
        char info[512];
        char buf[20] = {'4','9','\0'};
        int index =0;
        close(fd[0]);
        write(fd[1],"hello world\n",12);
        printf("strlen=%d\n",(int)strlen("\n"));
        printf("strlen=%d\n",(int)strlen("BAT CA     :%s%%\n"));
        snprintf(&info[index], sizeof(buf),"BAT CA     :%s%%\n",buf );
        printf("strlen info=%d\n",(int)strlen(info));
        for (index=0;index<strlen(info);index++)
            printf("%c",info[index]);
        printf("info=%s\n",info);
        sleep(1);
    } else {
        close(fd[1]);
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
    }
    exit(0);
}
