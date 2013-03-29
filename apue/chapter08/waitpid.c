#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
int main(void){
   pid_t pid,pid2;

   if((pid =fork())<0){
       printf("fork error \n");
   }else if(pid == 0){
            sleep(5);
            exit(0);
   }

    printf("Parent run here.....\n");
    do{
//	  pid2 = waitpid(pid,NULL,0);//父进程阻塞
	  pid2 = waitpid(pid,NULL,WNOHANG);//父进程不阻塞
      printf("pid2=%d\n",pid2);       
	  if(pid2 == 0){
		 printf("No child exited\n");
		 sleep(1);
	  }
	}while(pid2==0);

	if(pid==pid2)
			printf("successfully release child %d\n", pid);
	else
			printf("some error occured\n");

   return 0;
}

