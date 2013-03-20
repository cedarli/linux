#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAXLINE 1000
static  void sig_alrm(int);

int main(void){
    int n;
    char line[MAXLINE];
    if (signal(SIGALRM,sig_alrm) == SIG_ERR)
        printf("signal(SIGALRM) error\n");
    alarm(10);
    if ((n = read(STDIN_FILENO,line,MAXLINE)) <0 )
        printf("read error \n");
    alarm(0);
    write (STDOUT_FILENO,line,n);
    exit(0);
}

static void sig_alrm(int signo){
    /*nothing to do,just return to interrupt the read*/
}
