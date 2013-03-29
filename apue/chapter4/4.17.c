#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	char buf[10];
	int num;
	
	memset(buf,0,sizeof(buf));
	
	if((num = readlink(argv[1],buf,sizeof(buf)))<0)
		perror("readlink error");
	else
	{
		printf("name is:%s\n",buf);
		printf("length:%d\n",num);
	}
	exit(0);
}