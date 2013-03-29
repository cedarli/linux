#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	long n;
	
	n = pathconf("foo",_PC_CHOWN_RESTRICTED);
	printf("_POSIX_CHOWN_RESTRICTED:%ld\n",n);
	
	if(chown("foo",0,-1)<0)
		printf("fail chown uid\n");
	else
		printf("success chown uid\n");
		
	if(chown("foo",1000,119)<0)						//119 代表admin组的id
		printf("fail chown gid \n");
	else
		printf("success chown gid\n");
	
	exit(0);
}