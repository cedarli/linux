#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if(opendir(argv[1])<0)
	{
		perror("open error");
		exit(1);
	}
	if(rmdir(argv[1])<0)
	{
		perror("rmdir error");
		exit(1);
	}
	
	printf("rmdir done\n");
	sleep(15);
	printf("done\n");
	
	exit(0);
}