#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

static void sig_cld(int);
int main(){
    pid_t pid;
    if ( signal(SIGCLD,sig_cld) == SIG_ERR )
        printf("signal error");
    if ( (pid = fork())<0 ) {
        printf("fork error");
    }else if (pid == 0 ){
        printf("before sleep");
        sleep(2);
        printf("end sleep");
        _exit(0);
    }
    pause();    /*parent */
    exit(0);
}

static void sig_cld(int signo){ /*interrupts pause()*/
    pid_t pid;
    int status;
    printf("SIGCLD received \n");
    if (signal(SIGCLD,sig_cld) == SIG_ERR )/*reestablish handler*/
        printf("signal error");
    if ((pid = wait(&status))<0 )
        printf("wait error");
    printf("pid = %d\n",pid);
}
