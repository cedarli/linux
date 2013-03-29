#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>



int
main(int argc, char *argv[])
{
	char    *ptr;
	int     size;
	
	#ifdef  PATH_MAX
	size = PATH_MAX;
	#else
	size = 1024;
	#endif
	
	printf("max path:%d\n",size);
	if ((ptr = malloc(size)) == NULL)
        perror("malloc error for pathname");
		
	if (getcwd(ptr, size) == NULL)
		perror("getcwd failed");
	else
		printf("cwd before = %s\n", ptr);
	
	if (chdir("/home") < 0)
		perror("chdir failed");

		
	if (getcwd(ptr, size) == NULL)
		perror("getcwd failed");
	else
		printf("cwd after= %s\n", ptr);
		
	exit(0);

}