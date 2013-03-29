#include<unistd.h>
#include<stdio.h>

int main(void){
     pid_t pid;
	 alarm(20);

	 if((pid=fork())<0)
	 {
          printf("fork() error\n");
	 }else if(pid == 0){
        int result = alarm(10);
		printf("Child:result %d\n",result);
	 }else {
      sleep(3);
      printf("parent: result %d\n",alarm(10)); 
	 }

return 0;

}
