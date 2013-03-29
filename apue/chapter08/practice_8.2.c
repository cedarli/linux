#include<unistd.h>
#include<stdio.h>

static void f1(void),f2(void);

int main(void){
      f1();
      f2();
	  _exit(0);
}
//问题，共享代码段，共享那些？ f2函数不共享吗，那为什么父进程会死?

static void f1(void){
   pid_t pid;
   if((pid=vfork())<0)
		   printf("vfork error\n");

}

static void f2(void){
    char buf[1000];
	int i;
	for(i=0;i<sizeof(buf);i++)
			buf[i]=0;
}
