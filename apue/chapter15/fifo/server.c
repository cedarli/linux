#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<fcntl.h>  
#include<sys/types.h>  
#include<sys/stat.h>  
#include<signal.h>

#define PATH "/tmp/fifo"

static void sigCatch(int sig)
{
	if( sig == SIGPIPE)
		printf("catch signal:%d\n",sig);
}


int main(int argc,char *argv[])  
{  
    int fd,fd2; 
	int ret;
    char buf[20] = "hello world!!!/n";  
	char buff[128];

	//char name[16]={'0'};
	//sprintf(name,"%s-%d",PATH,getpid());
	//	puts(name);
	
	if( signal(SIGPIPE,sigCatch) == SIG_ERR){
		perror("signal failed\n");
	}

	if((mkfifo(PATH, 0666)) < 0){  
       	perror("mkfifo");  
       	exit(1);  
   	}
	printf("0000000000000\n");
   	if((fd = open(PATH , O_WRONLY)) < 0){   //nonblock
   	    perror("open");  
   	    exit(1);  
   	 } 
 	printf("111111111\n");
   	if((write(fd,buf,strlen(buf)-1)) < 0){  
   	    perror("write");  
   	    exit(1);  
   	} 
	
 	printf("22222222222\n");

    return 0;  
} 
