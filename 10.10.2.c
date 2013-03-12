#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo){
    longjmp(env_alrm,1);
}

static void sig_int(int signo){
    int i;
    printf("\n sig_int starting \n");
    for (i=0;i<5;i++)
        sleep(1);
    printf("sig_int finished\n");
}
unsigned int sleep2(unsigned int nsecs){
    if (signal(SIGALRM,sig_alrm)==SIG_ERR)
        return (nsecs);
    if (setjmp(env_alrm) == 0){
        alarm(nsecs);       /*start the timer*/
        pause();            /*next caught signal wakes us up*/
    }
    return (alarm(0));      /*turn off timer,return unslept time*/
}

int main(void){
    unsigned int unslept;
    if (signal(SIGINT,sig_int)==SIG_ERR)
        printf("signal(SIGINT) error \n");
    unslept = sleep2(5);
    printf("sleep2 returned: %u\n",unslept);
    exit(0);
}

