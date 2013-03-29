#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if(truncate(argv[1],atoi(argv[2]))<0)
		printf("truncate error\n");
	exit(0);
}