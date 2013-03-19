#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
/**
 * test kill parameter pid =,>,< 0 pid=-1.
 * **/

static void sig_parent(int);
static void sig_child(int);
//进程可以为它自己或者子进程设置group id.
int main(void) {
    pid_t pid;
    if (signal(SIGUSR1,sig_parent) == SIG_ERR)
        printf("signal SIGUSR1 error\n");
    printf("parent process group id: %d,pid : %d\n",getpgid(0),getpid());
    if((pid = fork()) < 0) {
        printf("fork error!\n");
    } else if (pid == 0) {
        printf("child process group id: %d ,pid : %d\n",getpgrp(),getpid());
        setpgid(getpid(),getppid());//a).(子)进程为自己设置进程组ID
        printf("after group id changed child process group id: %d pid : %d\n",getpgrp(),getpid());
        if (signal(SIGUSR1,sig_child) == SIG_ERR ){
            printf("child SIGUSR1 error \n");
        }
        printf("send SIGUSR1 signal to self pid >0 \n");
        kill(getpid(),SIGUSR1);
        sleep(1);
        printf("send SIGUSR1 signal to group pid == 0\n");
        kill(0,SIGUSR1);
        sleep(1);
        printf("send SIGUSR1 signal to group is pid<0\n");
        kill(-getppid(),SIGUSR1);
        sleep(1);
        printf("send SIGUSR1 signal to group kill -1");
        kill(-1,SIGUSR1);
        sleep(5); //等父进程为其设置新的group id.
        exit(0);
    }
    //parent process space
    printf("child pid:%d\n",pid);//父进程中返回的pid是子进程的pid 

    setpgid(pid,pid);//b).父进程设置子进程id
    sleep(15);//ps -o pid,ppid,pgrp,sid,comm
    exit(0);
}

static void sig_parent(int signo){
    printf("this is parent signal handler\n");
}

static void sig_child(int signo){
    printf("this is child signal handler\n");
}
