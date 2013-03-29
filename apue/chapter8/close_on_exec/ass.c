#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main(int argc, char *argv[])  
{  
		   int fd;  
		      printf("argc = %d\n ",argc);  
			     fd = *argv[1];  
				    printf("fd = %d,close_on_exec=%d \n",fd,fcntl(fd,F_GETFD));  
					   char *s = "zzzzzzzzzzzzzzzzzzz";  
					       write(fd, (void *)s, strlen(s));  
						      close(fd);  
							      return 0;  
}  
