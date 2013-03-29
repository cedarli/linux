#include<unistd.h>

int main(int argc,char **argv){
   pid_t pid;

   if((pid=fork()) <0){
           printf("fork error \n");
   }else if(pid==0){
 
         printf("child process \n");
		 exit(0);
   }

   sleep(20);

   printf("main done\n");
   return 0;

}
