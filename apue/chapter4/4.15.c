#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if(link("foo",argv[1])<0)
		perror("link fail");
	
	exit(0);
}