#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int sig_int_flag = 0; /*set nonzero when fignal occurs*/
static void sig_int(int);/*my signal handling function*/
int main(){
    signal(SIGINT,sig_int);
    printf("signal in main\n");
    while (sig_int_flag == 0){
        kill(getpid(),SIGINT);//??????????????????
        sleep(5);
        pause();   /*signal happen between check sig_int_flag and pause*/
    }

}

static void sig_int(int sig_no){
    signal(SIGINT,sig_int);
    printf("\nsignal in sig_int\n");
    sig_int_flag = 1;
}
