#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_int(int);

int main(void){
    sigset_t newmask,oldmask,waitmask;
    printf("program start:\n");
    if ( signal(SIGINT,sig_int) == SIG_ERR )
        printf("signal (SIGINT) error\n");
    sigemptyset(&waitmask);
    sigaddset(&waitmask,SIGINT);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGINT);
    /**
     * Block SIGINT and save current signal mask;
     * **/
    if ( sigprocmask(SIG_BLOCK,&newmask,&oldmask) <0 )
        printf("SIG_BLOCK error\n");
    /**
     * Critical region of code.
     * **/
    printf("in critical region:\n");
    /**
     * Pause , allowing all signals except SIGUSR1
     * **/
    if ( sigsuspend (&waitmask) != -1 )
        printf("sigsuspend error \n");
    printf("after return from sigsuspend:\n");
    /**
     * Reset signal mask which unblocks SIGINT
     * **/
    if ( sigprocmask( SIG_SETMASK,&oldmask,NULL ) < 0 )
        printf("SIG_SETMASK error\n");
    /**
     * And continue processing...
     * **/
    printf( "program exit:\n" );
    exit(0);
}

static void sig_int(int signo) {
    printf( "\n in sig_int \n");
}
