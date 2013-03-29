#include"head.h"

int main()
{
	int fd = 0;
	int fd1 = 0;
	int ret = 0;
	
	if ( (fd = open("./test.txt",O_RDONLY)) < 0)
		printf("open failed.\n");

	fd1= dup(fd);
	
	if ( (ret = write(fd1,"hello\n",6)) < 6)
	{	
		printf("write eror: ");
		(ret<0)?(printf("write failed ret:%d\n",ret)):(printf("write successed ret:\n",ret));
	}
	close(fd1);
	close(fd);
	
	return 0;
}
