#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>

void sighandler(int signo)
{
	printf("catch the nonsynchronous i/o operation signal\n");
	return;	
}

int main(int argc, char *argv[])
{
		int nbytes,val,newfd,owner;
		char buff[256] = {'0'};
		pid_t pid;
		char *ptr = "1234567890";
		
		int fd = open("./testno2.txt",O_RDWR|O_CREAT|O_APPEND,0755);
/*
		if (fd < 0)
		{
			printf("open file error");
			return -1;		
		}
		nbytes = write(fd,ptr,16);//read up to arg2,write at least arg2
		if( nbytes < 16)
		{
			printf("123wertyuio write nbytes:%d\n",nbytes);
			return -2;
		}
		printf("write %d bytes to fd:%d\n",nbytes,fd);
*/
		if ((val = fcntl(fd,F_GETFL, 0)) < 0)  /*O_ACCMODE*/
			printf("fcntl error %d", fd);
		
		switch (val & O_ACCMODE)     /*O_ACCMODE:mark*/
		{
			case O_RDONLY:
				printf("read only");
				break;
			case O_WRONLY:
				printf("write only");
				break;
			case O_RDWR:
				printf("read write");
				break;
			default:
				printf("unknown access mode\n");
		}
		if (val & O_APPEND)
			printf(", append\n");
		if (val & O_NONBLOCK)  /*auto,if block ,return error.*/
			printf(", nonblocking\n");
		if (val & O_SYNC)
			printf(", synchronous writes\n");
	
		//putchar('\n');
/*
		newfd =  fcntl(fd,F_DUPFD,5); /*>=arg2		
			printf("newfd:%d\n",newfd);
		lseek(fd,0,SEEK_SET); /*set to the start of the file 
		memset(buff,'\0',sizeof(buff));
		if ( (nbytes = read(newfd,buff,8)) <= 0)
			printf("read from newfd:%d failed,nbytes:%d\n",newfd,nbytes);
		else
			printf("read %d bytes:%s from newfd:%d\n",nbytes,buff,newfd);
		close(newfd);
*/		
		signal(SIGIO,sighandler); 
		pid = fork();
		if( pid < 0)
		{
			printf("fork failed\n");
			return -1;	
		}	
		else if(0 == pid)
		{
				if( fcntl(fd,F_SETOWN,getpid()) < 0)
						printf("F_SETOWM failed\n"); 
				else
						printf("F_SETOWM success,current pid:%d,F_SETOWN pid:%d\n",getpid(),fcntl(fd,F_GETOWN));
		}

		close(fd);
		
		return 0;
}
