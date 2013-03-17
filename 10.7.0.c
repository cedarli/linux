#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
/**
 * this program is generate a zombie process
 * */

int main(){
    pid_t pid;
    printf("parent pid=%d \n",getpid());
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
