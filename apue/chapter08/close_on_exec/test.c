#include <unistd.h>
#include<stdio.h>
#include<fcntl.h>
       int main()  
		{  
				    pid_t pid;  
				 int   fd = open("test.txt",O_RDWR|O_APPEND);  
				    if (fd == -1)  
						   printf("open err\n");   
				    printf("Parent:fd = %d\n",fd);  
				    
				   // fcntl(fd, F_SETFD, 1);                      
				    char *s="ooooooooooooooooooo";  
				    pid = fork();  
				    if(pid == 0)  
						    execl("ass", "./ass", &fd, NULL);  
				    wait(NULL);  
				    write(fd,s,strlen(s));  
				    close(fd);  
				    return 0;  
	}  

