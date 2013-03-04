#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_usr(int);
static void sig_int(int);
int main(void){

    if ( signal(SIGUSR1,sig_usr) == SIG_ERR )
        printf("can't catch SIGUSR1\n");
    if (signal(SIGUSR2,sig_usr) == SIG_ERR )
        printf("can't catch SIGUSR2\n");
    if (signal(SIGINT,sig_int) == SIG_ERR )
        printf("can't catch SIGINT");
    sleep(15);
}

static void sig_usr(int signo){

    if ( signo == SIGUSR1 )
        printf("received SIGUSR1 \n");
    else if ( signo == SIGUSR2 )
        printf("received SIGUSR2 \n");
    else
        printf("received signal %d \n",signo);
}

static void sig_int(int signo){
    printf("received SIGINT\n");
}
