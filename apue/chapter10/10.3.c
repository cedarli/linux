#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
/**
  * #include <signal.h>
  * void (*signal (int signo,void (func)(int)))(int);
  *
  * typedef void Sigfunc(int)
  * Sigfunc *signal(int,Sigfunc *)
  *
 **/
static void sig_usr(int);
static void sig_usr2(int);
typedef void Sigfunc(int);
int main(void){
    Sigfunc *handle;
    handle = signal(SIGUSR1,sig_usr2);
    printf("\nreturn SIGUSR1 handle=%p;sig_usr2=%p\n",handle,sig_usr2);
    handle = signal(SIGUSR1,sig_usr);
    printf("\nreturn SIGUSR1 handle=%p;sig_usr=%p\n",handle,sig_usr);
    if ( handle == SIG_ERR )
        printf("can't catch SIGUSR1\n");
    handle = signal(SIGUSR2,sig_usr);
    printf("return SIGUSR2 handle=%p;sig_usr=%p\n",handle,sig_usr);
    if ( handle == SIG_ERR )
        printf("can't catch SIGUSR2\n");
    for (;;)
        pause();
}

static void sig_usr(int signo){

    if ( signo == SIGUSR1 )
        printf("received SIGUSR1 \n");
    else if ( signo == SIGUSR2 )
        printf("received SIGUSR2 \n");
    else
        printf("received signal %d \n",signo);
}

static void sig_usr2(int signo){
    printf("sig_usr2\n");
}
