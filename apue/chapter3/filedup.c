#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main( int argc,char *argv[])
{
	int fd_2 = 5,fd_3;
	
	int fd_1 = dup(1);  /*standard output*/
	write(fd_1,"write to fd_1\n",strlen("write to fd_1\n"));
	printf("fd_1:%d\n",fd_1);
/*	close (fd_1); // all the resources are freed!!!!!! test the /dev/fd/n*/
	
	if ( (fd_3 = dup2(1,fd_2)) < 0)  /*close 1 / fd_1 first.&  was occupied.*/ 
		printf("dup2 failed,fd_3:%d\n",fd_3);

	write(fd_3,"write to fd_3\n",strlen("write to fd_3\n")); //0 1
	printf("fd_3:%d\n",fd_3);

	close(fd_3);
	write(fd_3,"write to fd_3\n",strlen("write to fd_3\n")); 
	
	//write(0,"write to fd_3\n",strlen("write to fd_3\n")); 
	write(fd_1,"write to fd_1\n",strlen("write to fd_1\n")); 
	write(1,"write to fd_0\n",strlen("write to fd_3\n")); 
	
	/*close....*/  //reference count. the last one special
	open(path,O_RDONLY);  //LOOP
	
	return 0;
	
}

/*
target file is stdout.

write to fd_1
fd_1:3
write to fd_3
fd_3:0
*/