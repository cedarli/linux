#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

typedef void Sigfunc(int);
static void sig_usr1(int);
static void sig_usr_info(int signo,siginfo_t *info,void *context);

Sigfunc * signal_intr(int signo,Sigfunc *func){
    struct sigaction act ,oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_flags |= SA_INTERRUPT;
    act.sa_flags |= SA_SIGINFO;
    act.sa_sigaction = sig_usr_info;
    if (sigaction(signo,&act,&oact)<0)
        return (SIG_ERR);
    return (oact.sa_handler);
}

int main(void){
   if(signal_intr(SIGUSR1,sig_usr1) == SIG_ERR)
       printf("SIGUSR1 error \n");
//   kill(getpid(),SIGUSR1);
   sleep(1);
//   kill(getpid(),SIGPOLL);
   sleep(1);
   kill(getpid(),SIGSEGV);
   sleep(1);
   kill(getpid(),SIGILL);
   sleep(5);
}

static void sig_usr1(int signo){
    printf("SIGUSR1 happen\n");
}

static void sig_usr_info(int signo,siginfo_t *info,void *context){
    printf("sig_usr_info called\n");
    printf("siginfo_t info info->si_signo =%d\n",info->si_signo);
    printf("siginfo_t info info->si_errno=%d\n",info->si_errno);
    printf("siginfo_t info info->si_code=%d\n",info->si_code);
    printf("siginfo_t info info->si_pid=%d\n",info->si_pid);
    printf("siginfo_t info info->si_uid=%d\n",info->si_uid);
    printf("siginfo_t info info->si_addr=%x\n",info->si_addr);
    printf("siginfo_t info info->si_status=%d\n",info->si_status);
    printf("siginfo_t info info->si_band=%lld\n",info->si_band);
}


