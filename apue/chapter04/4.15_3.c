#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if(rename(argv[1],argv[2])<0)
		perror("rename fail");
	
	exit(0);
}