#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_quit(int);

int main(void){
    sigset_t newmask,oldmask,pendmask;
    if (signal(SIGQUIT,sig_quit) == SIG_ERR)
        printf("can't catch SIGQUIT\n");
    /**
     * Block SIGQUIT and save current signal mask
     * */
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);
    if (sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
        printf("SIG_BLOCK error\n");
    sleep(5);
    if (sigpending(&pendmask) < 0)
        printf("sigpending error \n");
    if (sigismember(&pendmask,SIGQUIT))
        printf("\n SIGQUIT pending\n");
    /**
     * Reset signal mask which unblocks SIGQUIT
     * */
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        printf("SIG_SETMASK error\n");
    printf("SIGQUIT unblocked \n");
    sleep(5);/*SIGQUIT here will terminate with core file*/
    exit(0);
}

static void sig_quit(int signo){
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT,SIG_DFL) == SIG_ERR)
        printf("can't reset SIGQUIT'");
}
