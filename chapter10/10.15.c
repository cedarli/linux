#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <signal.h>

static void sig_usr1(int) ,sig_alarm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;
int main(void){
    if ( signal (SIGUSR1,sig_usr1) == SIG_ERR )
        printf("signal (SIGUSR1) error\n");
    if ( signal (SIGALRM,sig_alarm) == SIG_ERR )
        printf("signal (SIGALRM) error\n");
    printf("\nstarting main:\n");
    if (sigsetjmp(jmpbuf,1)){
        printf("ending main: \n");
        exit(0);
    }
    canjump = 1;
    for(;;)
        pause();
}

static void sig_usr1(int signo){
    time_t starttime;
    if ( canjump == 0 )
        return;       /* unexpected signal,ignore */
    printf("starting sig_usr1:\n ");
    alarm(3);
    starttime = time(NULL);
    for(;;)
        if ( time(NULL) >starttime+5)
            break;
    printf("finishing sig_usr1:\n");
    canjump = 0;
    siglongjmp(jmpbuf,1);/*jump back to main,don't return */
}

static void sig_alarm(int signo){
    printf("\n in sig_alarm\n");
}
