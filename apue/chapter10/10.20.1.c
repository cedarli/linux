#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define BUFFSIZE 1024

static void sig_tstp(int);

int main(void){
    int n;
    char buf[BUFFSIZE];
    /**
     * Olly catch SIGTSTP if wr're running with a job-control shell.
     * */
    if ( signal(SIGTSTP,SIG_IGN) == SIG_DFL )
        signal(SIGTSTP,sig_tstp);
    while ( (n = read(STDIN_FILENO,buf,BUFFSIZE)) >0 )
        if ( write(STDOUT_FILENO,buf,n) != n )
            printf("write error\n");
    if ( n<0 )
        printf("read error\n");
}

static void sig_tstp(int signo){/*signal handler for SIGTSTP*/
    sigset_t mask;
    /**
     * ...move cursor to lower left corner,reset tty  mode...
     * Unblocck SIGTSTP ,since it't blocked while we're handling it.
     * */
    sigemptyset(&mask);
    sigaddset(&mask,SIGTSTP);
    sigprocmask(SIG_UNBLOCK,&mask,NULL);
    signal(SIGTSTP,SIG_DFL);
    kill(getpid(),SIGTSTP);
    signal(SIGTSTP,sig_tstp);
}
