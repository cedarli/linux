#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

static void * thread_fn(void * args){
    printf("this a thread function\n");
    return;
}

int makethread(void *(*fn)(void *),void *arg){
    printf("makethread runed\n");
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


struct to_info{
    void (*to_fn)(void *); /*function*/
    void * to_arg;         /*argument*/
    struct timespec to_wait;/*time to wait*/
};

#define SECTONSEC 1000000000
#define USECTONSEC 1000
/*PTHREAD_MUTEX_RECURSIVE is a POSIX parameter so redefine PTHREAD_MUTEX_RECURSIVE to PTHREAD_MUTEX_RECURSIVE_NP*/
#define PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP

void * timeout_helper(void *arg){
    struct to_info *tip;
    tip = (struct to_info *)arg;
    nanosleep(&tip->to_wait,NULL);
    (*tip->to_fn)(tip->to_arg);
    return (0);
}

void timeout(const struct timespec *when,void (*func)(void *), void *arg){
    printf("timeout runing......\n");
    struct timespec now;
    struct timeval tv;
    struct to_info *tip;
    int err;
    gettimeofday(&tv,NULL);
    now.tv_sec = tv.tv_sec;
    now.tv_nsec = tv.tv_usec * USECTONSEC;
    printf("when->tv_sec=%d;now.tv_sec=%d\n",when->tv_sec,now.tv_sec);
    printf("when->tv_nsec=%lld;now.tv_nsec=%lld\n",when->tv_nsec,now.tv_nsec);
    if ( (when->tv_sec > now.tv_sec ) ||
         (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec) ) {
        tip = malloc(sizeof(struct to_info));
        if ( tip != NULL ){
            tip->to_fn = func;
            tip->to_arg =arg;
            tip->to_wait.tv_sec = when->tv_sec-now.tv_sec;
            if ( when->tv_nsec >= now.tv_nsec ){
                tip->to_wait.tv_nsec = when->tv_sec -now.tv_sec;
            } else {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SECTONSEC-now.tv_nsec+when->tv_nsec;
            }
            err = makethread(timeout_helper,(void *) tip);
            if ( err == 0 ) return;
        }
    }
    /**
     * We get here if 
     * (a) when <= now, or 
     * (b) malloc fails, or 
     * (c) we can't make a thread,so we just call the function now.
     */
    (*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void retry (void *arg){
    pthread_mutex_lock(&mutex);
    /*perform retry steps....*/
    pthread_mutex_unlock(&mutex);
}
int main(void){
    int err,condition,arg;
    struct timespec when;
    condition = 1;
    if ( (err = pthread_mutexattr_init(&attr)) != 0 )
        printf("pthread_mutexattr_init failed %d\n",err);
    if ( (err = pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE)) != 0 )
        printf("can't set recursive tipe %d\n",err);
    if ( (err = pthread_mutex_init(&mutex,&attr)) != 0 )
        printf("can't create recursive mutex %d \n",err);
    pthread_mutex_lock(&mutex);
    printf("condition =%d\n",condition);
    if ( condition ){
        /*calculate targe time when*/
        printf("before timeout\n");
        timeout(&when,retry,(void *)arg);
        printf("end timeout\n");
    }
    pthread_mutex_unlock(&mutex);
    exit(0);
}
