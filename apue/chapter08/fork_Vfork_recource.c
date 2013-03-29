#include "apue.h"
#include<fcntl.h>
 int glob =6;
char *mstr = "glob string";
void printResource(char* str){
   printf("实际用户Id=%d,实际组Id=%d \n",getuid(),getgid());
   printf("有效用户Id=%d,有效组Id=%d \n",geteuid(),getegid());
   printf("进程组Id=%d\n",getpgrp());
//   system("ps -o pid,ppid,pgid,sid,comm");
   printf("会话Id=%d\n",getsid(getpid()));
   
   char *cwdFileName = (char *)malloc(4096);
   printf("当前工作目录=%s\n",getcwd(cwdFileName,4096));
   free(cwdFileName);

   //文件模式创建屏蔽字
   cwdFileName = NULL;
   creat(str,O_RDWR);

   //信号屏蔽和安排
   //TELL_WAIT,屏蔽掉了所有的信号
}
int main(void){  
 char * mHeap =(char *)malloc(strlen(mstr)+1);
 strcpy(mHeap,mstr);
 int mStack = 10;
 pid_t pid;
 

 //文件描述符和针对任一打开文件描述符的在执行时关闭（close-on-exec）,默认的是0 打开
 int fd = open("testClose_on_Exec.txt",O_RDWR|O_APPEND);
 int valClose_On_Exce = fcntl(fd, F_GETFD);

 printf("fd = %d,valClose_On_Exce=%d\n",fd,valClose_On_Exce);  


 //文件模式创建屏蔽字
 umask(0);
 TELL_WAIT();
 if((pid=fork()) <0){
       printf("fork error\n");
 }else if(pid == 0){
        WAIT_PARENT();
		 printf("Child: Copy parent stack and heap: Adress{mHeap=%p,mStack=%p} value{mHeap =%s,mStack=%d},\n",&mHeap,&mStack,mHeap,mStack);
		 printf("Child:fd = %d,valClose_On_Exce=%d\n",fd,valClose_On_Exce);  
		printResource("child");
 } else {
		printf("Parent: parent stack and heap: Adress{mHeap=%p,mStack=%p} value{mHeap =%s,mStack=%d},\n",&mHeap,&mStack,mHeap,mStack);	
		printf("Parent:fd = %d,valClose_On_Exce=%d\n",fd,valClose_On_Exce);  
		printResource("parent");
		TELL_CHILD(pid);
 }

return 0;

}
