#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

static void sig_int(int signo){
    printf("sig_int handler\n");
}

static void sig_chld(int signo){
    printf("sig_chld handler \n");
}
int system1(const char *cmdstring){ /* with appropriate signal handling*/
    pid_t pid;
    int status;
    struct sigaction ignore,saveintr,savequit;
    sigset_t chldmask,savemask;

    if ( cmdstring == NULL )
        return (1); /*always a command processor with UNIX*/
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;

    if( sigaction(SIGINT,&ignore,&saveintr) < 0 )
        return (-1);
    if( sigaction(SIGQUIT,&ignore,&savequit) <0 )
        return (-1);
    sigemptyset(&chldmask); /*now block SIGCHLD*/
    sigaddset(&chldmask,SIGCHLD);
    if( sigprocmask(SIG_BLOCK,&chldmask,&savemask) < 0 )
        return (-1);
    if( (pid = fork()) < 0 )
        status = -1;  /*probably out of processes*/
    else if( pid == 0 ){
        /*restore previous signal action & reset signal mask*/
        sigaction(SIGINT,&saveintr,NULL);
        sigaction(SIGQUIT,&savequit,NULL);
        sigprocmask(SIG_SETMASK,&savemask,NULL);
        execl("/bin/sh","sh","-c",cmdstring,(char *)0);
        _exit(127);
    } else {
        while ( waitpid(pid,&status,0) <0 )
            if( errno != EINTR ){
                status =-1;/*error other than EINTR from waitpid()*/
                break;
            }
    }
    /*resetore previous signal actions & reset signal mask*/
    if( sigaction(SIGINT,&saveintr,NULL) < 0 )
        return (-1);
    if( sigaction(SIGQUIT,&savequit,NULL) <0 )
        return (-1);
    if( sigprocmask(SIG_SETMASK,&savemask,NULL) <0 )
        return (-1);
    return (status);
}

int main (void){
    if ( signal(SIGINT,sig_int) == SIG_ERR )
        printf("signal (SIGINT)\n");
    if ( signal(SIGCHLD,sig_chld) == SIG_ERR )
        printf("signal (SIGCHLD) error\n");
    if ( system1("/bin/ed") < 0 )
        printf("system() error\n");
    exit(0);
}
