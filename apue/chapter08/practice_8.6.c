#include<stdio.h>
#include<unistd.h>
#define PSCMD "ps -o pid,ppid,state,tty,command"

int main(void){
     pid_t pid;

	 if((pid=fork()) <0){
        printf("fork() error \n");
	  } else if(pid == 0)
		exit(0);

	 
	sleep(10);

	system(PSCMD);
    exit(0);


}
