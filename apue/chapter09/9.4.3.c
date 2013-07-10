#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//父进程在子进程调用exec函数后不能再改变子进程的进程组id
extern char **environ;
int main() {
    pid_t pid;
    if((pid = fork()) < 0) {
            printf("fork error!");
    } else if (pid == 0) {
        printf("child process group id: %d pid : %d\n",getpgrp(),getpid());
        if (execle("./exec_test", "exec_test", "myarg1",
                "MY ARG2", (char *)0, environ) < 0)
                printf("execle error");
        sleep(5);
        printf("after group id changed child process group id: %d pid : %d\n",getpgrp(),getpid());
        sleep(15);
        exit(0);
    }

    //parent process space
    printf("child pid:%d\n",pid);//b.父进程中返回的pid是子进程的pid
    printf("parent process group id: %d pid : %d\n",getpgid(0),getpid());

    sleep(4);//等待子进程调用exec函数，
    if(setpgid(pid,pid) < 0)
            printf("set child group id failed.\n");
    exit(0);
}

