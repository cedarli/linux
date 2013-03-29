#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
	struct stat buf;
	
	if(stat(argv[1],&buf)<0){
		printf("stat error\n");
		exit(1);
	}
	
	if (chmod(argv[1], buf.st_mode | S_ISVTX) < 0)
		printf("chmod error\n");
		
	exit(0);
}