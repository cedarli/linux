#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>

#include <unistd.h>
volatile int i=0;
static void my_alarm(int signo){
//    alarm(1);
//    free(ptr);
    for (;;) {
        ++i;
        printf("in sig handler pid=%d\n",getpid());
    }
}

int main(void){
    struct passwd *ptr;
    signal(SIGALRM,my_alarm);
    printf("main pid=%d\n",getpid());
    alarm(1);
    printf("before for \n");
    for (;;){
        printf("i=%d\n", i);
    }
}
    //    void *ptr1 =  malloc(100000000);
 //       if ((ptr = getpwnam ("lanbo")) == NULL )
//            free(ptr1);
  //      if (ptr )
   //     if ( strcmp(ptr->pw_name,"lanbo") != 0 )
    //        printf("return value corrupted!,pw_name = %s\n",ptr->pw_name);
 //   struct passwd *rootprt;
//    void *ptr;
  //  printf("xxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxsignal handler \n");
//    if ( (rootprt = getpwnam("root")) == NULL )
//    ptr = malloc(1000000);
    
