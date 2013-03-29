#include"apue.h"
#include <sys/wait.h>

int main(void){
           pid_t pid;
           
		   printf("main %d\n",getpid());
		   if((pid= fork()) <0)
				   err_sys("fork error \n");
		   else if(pid == 0){
				   printf("First child %d ,parent id=%d \n",getpid(),getppid());
                    if((pid=fork()) < 0)
						   err_sys("fork error \n");
				   else if(pid > 0){
					    printf(" parent id =%d exit\n",getpid());
						   exit(0);
				   }
                
				   sleep(20);

				   printf("second child parent %d,child %d, pid=%d\n",getppid(),getpid(),pid);
				//   exit(0);
		   }

		    
//		if( waitpid(pid,NULL,0) != pid)
//				   err_sys("waitpid error");
         printf("main pid=%d \n",pid);
		   exit(0);

}
