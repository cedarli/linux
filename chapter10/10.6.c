#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>
static void my_alarm(int signo){
    struct passwd *rootprt;
    printf("in signal handler \n");
    if ( (rootprt = getpwnam("root")) == NULL )
        printf("getpwnam(root) error");
    alarm(1);
}

int main(void){
    struct passwd *ptr;
    signal(SIGALRM,my_alarm);
    alarm(1);
    printf("before for \n");
    for (;;){
        if ((ptr = getpwnam ("sar")) == NULL )
            printf("getpwnam error");
        if ( strcmp(ptr->pw_name,"sar") != 0 )
            printf("return value corrupted!,pw_name = %s\n",ptr->pw_name);
    }
}
