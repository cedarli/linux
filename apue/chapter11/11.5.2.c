#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct foo{
    int a,b,c,d;
};
struct foo foo = {1,2,3,4};
void printfoo(const char *s,const struct foo *fp){
    printf("%s",s);
    if (fp == NULL){
        printf("fp equal NULL\n");
        return;
    }
    printf(" structure at 0x%x\n",(unsigned)fp);
    printf(" foo.a =%d \n",fp->a);
    printf(" foo.b =%d \n",fp->b);
    printf(" foo.c =%d \n",fp->c);
    printf(" foo.d =%d \n",fp->d);

}
void * thr_fn1(void *arg){
    printfoo("thread 1 \n",&foo);
    pthread_exit((void *)&foo);
}

void * thr_fn2(void *arg){
    printf("thread 2 : ID is %d\n",pthread_self());
    pthread_exit((void *)0);
}

int main(void){
    int err;
    pthread_t tid1,tid2;
    struct foo *fp;
    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if ( err != 0 )
        printf("can't create thread 1:%d\n",err);
    err = pthread_join(tid1,(void *)&fp);
    if ( err != 0 )
        printf("can't join with thread 1\n");
    sleep(1);
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if ( err != 0 )
        printf("can't create thread 1:%d\n",err);
    pthread_join(tid2,(void *)&fp);
    sleep(1);
    printfoo("parent:\n",fp);
    exit(0);
}
