#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int fd;
	char *buf="abcd";
	
	if((fd=open("bar",O_RDWR))<0)
	{
		perror("open error");
		exit(1);
	}
	if(unlink("bar")<0)
	{
		perror("unlink error");
		exit(1);
	}
	printf("file unlinked\n");
	
	if(write(fd,buf,sizeof(buf))<0)
	{
		perror("write error");
		exit(1);
	}else
	{
		printf("write success\n");
	}
	
	sleep(15);
	printf("done\n");
    exit(0);

}