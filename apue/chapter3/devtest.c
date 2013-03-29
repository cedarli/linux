#include"head.h"

#include"command.h"

#define PATH "/dev/test"

int main(int argc ,char*argv)
{
	int fd = open(PATH,O_RDWR);
	int getvalue=0;
	int setvalue=10;
	
	if(fd < 0)
	{
		printf("open failed\n");
		return -1;
	}


	printf("before ioctl:GET_TEST ,getvalue:%d\n",getvalue);
	ioctl(fd,GET_TEST,&getvalue);  
	printf("after ioctl:GET_TEST ,getvalue:%d\n",getvalue);

	
	ioctl(fd,SET_TEST,&setvalue);  
	printf("ckeck data value in kernel\n");

	close(fd);

	return 0;

}

