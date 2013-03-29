#include<unistd.h>
#include<stdio.h>
#include<signal.h>

static void sig_quit(int);
int main(void){
    pid_t pid;
	sigset_t newmask,oldmask;
	if(signal(SIGQUIT,sig_quit)<0)
			printf("can't catch SIGQUIT\n");

	sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) <0)
			printf("SIG_BLOCK erro \n");

	if((pid=fork())<0){
       printf("fork error\n");
	}else if(pid == 0){
      printf("Enter child procces,,,,,,pid=%d\n",getpid());
	  sleep(20);
	// if(sigpending(&pendset)<0)
	//		printf("sigpenging error\n");
      _exit(0);
	}

	wait();
	//if(sigpending(&pendset)<0)
	//		printf("sigpenging error\n");
	  printf("wait done\n");
      return 0;
}

static void sig_quit(int signal){
  printf("caught SIGQUIT\n");

}
