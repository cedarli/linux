#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
int main(void){
    pid_t pid;
    if ( signal(SIGUSR1,sig_usr))
        printf("can't catch SIGUSR1\n");
    printf("parent pid=%d  \n",getpid());
    if ( (pid = fork()) == 0 ){
        printf("\nchild process run pid=%d \n",getpid());
        kill(getpid(),SIGUSR1);
        ////////////
        printf("send signal SIGUSR1 before execvp\n");
        execvp("./10.3.2.1",NULL);
        printf("send signal SIGUSR1 after execvp \n");
        kill(getpid(),SIGUSR1);
    }
    sleep(10);
}

static void sig_usr(int signo){
    printf("received SIGUSR1 \n");
}
