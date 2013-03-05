#include <signal.h>
int sig_int_flag = 0; /*set nonzero when fignal occurs*/
static void sig_int(int);/*my signal handling function*/
int main(){
    signal(SIGINT,sig_int);
    printf("signal in main\n");
    while (sig_int_flag == 0)
        pause();
}

static void sig_int(int sig_no){
    signal(SIGINT,sig_int);
    printf("\nsignal in sig_inti\n");
    sig_int_flag = 1;
}
