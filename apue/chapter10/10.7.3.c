#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static void sig_cld(int);
int main(){
    pid_t pid;
    if ( signal(SIGCLD,sig_cld) == SIG_ERR )
        printf("signal error");
    if ( (pid = fork())<0 ) {
        printf("fork error");
    }else if (pid == 0 ){   /*child*/
        printf("child pid = %d\n",getpid());
        printf("before sleep\n");
        sleep(2);
        printf("end sleep\n");
        _exit(0);
    }
    if ( (pid = fork())<0 ) {
        printf("fork error");
    }else if (pid == 0 ){   /*child*/
        if ( (pid = fork())<0 ) {
            printf("fork error");
        }else if (pid == 0 ){   /*child*/
            printf("child 12 pid = %d\n",getpid());
            _exit(0);
        }
        printf("child 11 pid = %d\n",getpid());
        printf("before 11 sleep\n");
        sleep(10);
        printf("end 11 sleep\n");
        _exit(0);
    }
    pause();    /*parent*/
   // sleep(20);
    exit(0);
}

static void sig_cld(int signo){ /*interrupts pause()*/
    pid_t pid;
    int status;
    printf("SIGCLD received \n");
    if (signal(SIGCLD,sig_cld) == SIG_ERR )/*reestablish handler*/
        printf("signal error \n");
    if ((pid = wait(&status))<0)
        printf("wait error \n");
    printf("wait process pid = %d \n",pid);
}
