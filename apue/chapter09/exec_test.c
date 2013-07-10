#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[]) {
    printf("hello,main()\n");
    printf("test group id: %d pid : %d ppid: %d \n",getpgrp(),getpid(),getppid());
    //sleep(5);
    return 0;
}
