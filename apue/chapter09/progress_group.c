# include "apue.h"
//#include <stdio.h>
//进程可以为它自己或者子进程设置group id.
// a).---b).----
int main() {
	pid_t pid;
	if((pid = fork()) < 0) {
		printf("fork error!");
	} else if (pid == 0) {
		exit(0);
		//printf("child process group id: %d pid : %d\n",getpgid(pid),getpid());
		printf("child process group id: %d pid : %d\n",getpgrp(),getpid());

		//setpgid(getpid(),0);//a).(子)进程为自己设置进程组ID
		sleep(5); //等父进程为其设置新的group id.
		printf("after group id changed child process group id: %d pid : %d\n",getpgrp(),getpid());
		//sleep(15);
		exit(0);
	}

	//parent process space
	printf("child pid:%d\n",pid);//父进程中返回的pid是子进程的pid

	//printf("parent process group id: %d pid : %d\n",getpgrp(),getpid());
	printf("parent process group id: %d pid : %d\n",getpgid(0),getpid());
	
	setpgid(pid,pid);//b).父进程设置子进程id
	sleep(15);//ps -o pid,ppid,pgrp,sid,comm
	exit(0);
	
}

