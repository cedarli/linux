#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_usr(int);
int main(void){
    if( signal(SIGUSR1,sig_usr) ==SIG_ERR);
        printf("Return signal (SIGUSR1)");
    pause();
}

static void sig_usr(int signo){

    if ( signo == SIGUSR1 )
        printf("received SIGUSR1 \n");
}

