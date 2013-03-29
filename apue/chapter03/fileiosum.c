#include"head.h"

#define BUFFSIZE 1024
const char *ptr = "hello suzhou";
const char *path = "/home/gupingchang/test.c";

char buff[BUFFSIZE] = {'0'};

//#define UPHALF

int main(int argc,char*argv[])
{
	int fd , n;
	char *fname = NULL;

#ifdef UPHALF
	if( argc >= 2)
	{
		if( argv[1] != NULL)
		{ /*
			if( fd = open(argv[1],O_RDWR) < 0)
			{	
				printf("open failed ,there's no such file:%s,flag:O_RDWR\n",argv[1]);
				return -1;
			}
			else
			{
				printf("open file success,flag:O_RDWR and close it\n");
				close(fd);
			}
			*/

/*			umask(0000);//mode&~umask*/ /*defaule 0022*/
			if(  fd = open( argv[1],O_RDWR|O_CREAT|O_APPEND,0777) < 0) /*O_CREAT must with mode arg!*/
				printf("open file fail,flag:O_RDWR|O_CREAT|O_APPEND\n");
			else
			{
				printf("open file :%s success fd:%d\n",argv[1],fd);
				if (n  =  write(fd,"hello infomax",strlen("hello infomax") == 0))
					printf("write fail\n");
				
				close(fd);
				return 0;
			
			}
		}	
	}
	else
	{
		printf("please touch a file first.\n");
		return -1;
	}
#else
	fd = open(path,O_RDWR);
	if( fd < 0)
	{
		printf("open %sfailed.\n",path);
		return 0;
	}

	n = read(fd,buff,BUFFSIZE);
	printf("read %d bytes:%s from file%s.\n",n,buff,path);
	/* read again without close file*/
	n = read(fd,buff,BUFFSIZE);
	if( n == 0)
		printf("file pointer at the END of file.\n");

	lseek(fd,0,SEEK_SET); /*off_t lseek(int fd,off_t offset,int wherece)*/ /*SEEK_SET SEEK_CUR SEEK_END*/
	n = read(fd,buff,BUFFSIZE);
	printf("read %d bytes:%s from file.%s\n",n,buff,path);
		
	lseek(fd,0,SEEK_SET); /*off_t lseek(int fd,off_t offset,int wherece)*/ /*SEEK_SET SEEK_CUR SEEK_END*/
	lseek(fd,6,SEEK_SET);
	n = read(fd,buff,BUFFSIZE);
	printf("read %d bytes:%s from file%s\n",n,buff,path);
	
	close(fd);

#endif	
	return 0;
}
