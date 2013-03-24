#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sig_abt(int signo){
    printf("SIGABRT sig_abt\n");
    printf("abort exit process\n");
    exit(1);
}
int main(void){
    if (signal (SIGABRT,sig_abt) == SIG_ERR )
        printf("SIGABRT error\n");

    abort();
}

