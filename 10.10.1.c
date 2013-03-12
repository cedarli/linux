#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void sig_alrm(int signo){
    /*nothing to do ,just return to wake up the pause*/
}

unsigned int sleep1(unsigned int nsecs){
    int ret = 0;
    if (signal(SIGALRM,sig_alrm)==SIG_ERR)
        return (nsecs);
    ret = alarm(nsecs);
    printf("alarm ret =%d\n",ret);
    pause();
    return (alarm(0));
}

int main(void){
    alarm(5);
    printf("main sleep1 before\n");
    sleep1(3);
    printf("main sleep1 after\n");
}
