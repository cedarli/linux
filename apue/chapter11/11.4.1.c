#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n",s,(unsigned int)pid,(unsigned int)tid,(unsigned int)(tid));
}

void * thr_fn(void *arg){
    printids("new thread: ");
    return ((void *) 0);
}
/**
 * note: pthread_create isn't library in linux by default.
 * When compiler this you must use -lpthread link static library
 * for pthread_create.
 * */
int main(void){
    int err;
    err = pthread_create(&ntid,NULL,thr_fn,NULL);
    if ( err != 0 )
        printf("can't create thread: %d \n",err);
    printids("main thread: ");
    sleep(1);
    exit(1);
}
