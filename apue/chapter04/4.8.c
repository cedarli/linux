#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int
main(int argc, char *argv[])
{
	int pre;
	pre = umask(0);
	printf("pre umask: %o\n",pre);
    if (creat("foo", RWRWRW) < 0)		
        printf("creat error for foo");
    pre = umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	printf("pre umask: %o\n",pre);
    if (creat("bar", RWRWRW) < 0)
        printf("creat error for bar");
    exit(0);

}