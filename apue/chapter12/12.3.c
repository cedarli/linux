#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static void * thread_fn(void * args){
    printf("this a thread function\n");
    return;
}

int makethread(void *(*fn)(void *),void *arg){
    int err;
    pthread_t tid;
    pthread_attr_t attr;
    err = pthread_attr_init(&attr);
    if (err !=0 )
        return err;
    err = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    if ( err ==0 )
        err = pthread_create(&tid,&attr,fn,arg);
    pthread_attr_destroy(&attr);
    return err;
}

int main(int argc,char *argv []){
    return makethread(thread_fn,NULL);
}
