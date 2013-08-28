#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<fcntl.h>  
#include<sys/types.h>  
#include<sys/stat.h>  

#define PATH "/tmp/fifo"

int main(int argc,char *argv[])  
{  
    int fd,fd2; 
	int ret;
    char buf[20] = "hello world!!!/n";  
	char buff[20];
	memset(buff,0,sizeof(buff));

   	if((fd = open(PATH , O_RDONLY)) < 0){  
   	    perror("open");  
   	    exit(1);  
   	 } 
 	printf("0000000000\n");
   	if((read(fd,buff,strlen(buf)-1)) < 0){  
   	    perror("read");  
   	    exit(1);  
   	} 
	printf("read:%s\n",buff);
	
    return 0;  
} 
