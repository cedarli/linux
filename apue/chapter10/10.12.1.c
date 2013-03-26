#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void pr_mask(const char *str){
    printf("begin pr_mask save errno\n");
    sigset_t sigset,sigmask;
    int errno_save;
    errno_save = errno; /*wo can be called by signal handlers */
    sigemptyset(&sigmask);
    sigaddset(&sigmask,SIGUSR1);
    sigaddset(&sigmask,SIGALRM);
    if ( sigprocmask(SIG_BLOCK,&sigmask,NULL))
        printf("sigprocmask set BLOCK error\n");
    if ( sigprocmask(0,NULL,&sigset)<0 )
        printf("sigprocmask error\n");
    printf("%s\n",str);
    if (sigismember(&sigset,SIGINT)) printf("SIGINT\n");
    if (sigismember(&sigset,SIGQUIT)) printf("SIGQUIT\n");
    if (sigismember(&sigset,SIGUSR1)) printf("SIGUSR1\n");
    if (sigismember(&sigset,SIGALRM)) printf("SIGALRM\n");
    printf("end pr_mask restore errno\n");
}

int main (void){
    pr_mask("test sigprocmask");
}
