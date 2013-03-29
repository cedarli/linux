# include "apue.h"
//#include <stdio.h>
/* 课后练习 9.2 */

int main() {
	pid_t pid;
	if((pid = fork()) < 0) {
		printf("fork error!");
	} else if (pid == 0) {//在子进程中调用setsid()
		printf("\n");
		printf("child process pid : %d, group id: %d sid:%d\n",getpid(),getpgid(pid),getsid(getpid()));
		//  /*
		sleep(5);// ps -o pid,ppid,pgrp,sid,comm,tty (1)
		//pid = setsid();
		printf("after session id changed child pid:%d group id: %d session id: %d \n",getpid(),getpgid(pid), getsid(getpid()));
		//  */
		sleep(10);//ps -o pid,ppid,pgrp,sid,comm,tty (2)
		printf("child process exit.\n");
		exit(0);
	}
	pid = setsid(); //runtime error 调用进程是组长进程，函数返回出错 -1
	printf("setsid return value: %d\n",pid);
	printf("parent process pid : %d, group id: %d sid:%d\n",getpid(),getpgid(pid),getsid(getpid()));
	sleep(15);
	exit(0);
}

