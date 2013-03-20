#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
/**
 * this program is avoid generate zombie process
 * */
/**
 *  http://blog.csdn.net/taolinke/article/details/8057335
 *  http://blog.csdn.net/21aspnet/article/details/6740110
 *  about errno and  ECHILD introduce
 * **/
int main(){
    pid_t pid;
    int status;
    printf("parent pid=%d \n",getpid());

    if ( (pid = fork())<0 ) {
        printf("fork error\n");
    }else if (pid == 0 ){   /*child*/
        if (signal(SIGCLD,SIG_IGN) == SIG_ERR ){
            printf("SIGCLD signal error \n");
        }
        sleep(2);
        printf("\n child 1 pid = %d\n",getpid());
        printf("child 1 process exit\n");
        _exit(0);
    }
    if ( (pid = fork())<0 ) {
        printf("fork error\n");
    }else if (pid == 0 ){   /*child*/
        printf("child 2 pid = %d\n",getpid());
        printf("child 2 process exit\n");
        _exit(0);
    }
//    sleep(10);
    pid = wait(&status);
    printf("errno =%d \n",errno);
    printf("errno string = %s\n",strerror(errno));
    printf("ECHILD =%m\n",ECHILD);
    printf("parent process exit wait pid =%d\n",pid);
}
