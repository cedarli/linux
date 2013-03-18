#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(){
    pid_t pid;
    printf("parent pid=%d \n",getpid());
    if ( signal(SIGCLD,SIG_IGN) == SIG_ERR )
        printf("signal error\n");
    if ( (pid = fork())<0 ) {
        printf("fork error\n");
    }else if (pid == 0 ){   /*child*/
        printf("child pid = %d\n",getpid());
        printf("child process exit\n");
        _exit(0);
    }
    sleep(10);
    printf("parent process exit\n");
}
