#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void main(){
    printf("Child process pid=%d \n",getpid());
    printf("wait send SIGUSR1 after execvp \n");
    sleep(20);
}
