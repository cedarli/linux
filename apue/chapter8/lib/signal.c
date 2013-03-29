#include<apue.h>
static volatile sig_atomic_t  sigflag;

static sigset_t newmask,oldmask,zeromask;

static void sig_usr(int siagno){
     sigflag = 1;
}

void TELL_WAIT(void){
   if(signal(SIGUSR1,sig_usr)<0)
		   err_sys("signal(SIGUSR1) error");
   if(signal(SIGUSR2,sig_usr)<0)
		   err_sys("signal(SIGUSR2) error");

   sigemptyset(&newmask);
   sigemptyset(&zeromask);

   if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
		   err_sys("sigprocmask error");
}

void WAIT_PARENT(void){
   while(sigflag ==0)
		   sigsuspend(&zeromask);

   sigflag = 0;

   if(sigprocmask(SIG_SETMASK,&oldmask,NULL))
		   err_sys("SIG_SETMASK error");
}

void TELL_CHILD(pid_t pid){

		kill(pid,SIGUSR1);
}

void WAIT_CHILD(void){
   while(sigflag ==0)
		   sigsuspend(&zeromask);

   sigflag = 0;

   if(sigprocmask(SIG_SETMASK,&oldmask,NULL))
		   err_sys("SIG_SETMASK error");
}

void TELL_PARENT(pid_t pid){

   kill(pid,SIGUSR1);
}



