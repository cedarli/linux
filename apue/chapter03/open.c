#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

int main()
{
    int fd;
    char buff[256] = {'0'};
    char*path = "./test.txt";
    pid_t child;

    fd=open(path,O_RDWR);
    read(fd,buff,6);
    printf("read %d bytess\"%s\" form file:%s \n",strlen(buff),buff,path);
    /*father and child share the fd.*/	
    child = fork();
    if( child == 0) {
        printf("i am child process %d file fd:%d\n",getpid(),fd);
        memset(buff,'\0',sizeof(buff));
        read(fd,buff,5);
        printf("read %d bytes: \"%s\" from file:%s\n",strlen(buff),buff,path);
        close(fd);  /*how*/
    } else if(child > 0) {
        //sleep(3);
        printf("generated a child process%d file fd:%d\n",child,fd);
        memset(buff,'\0',sizeof(buff));
        read(fd,buff,5);
        printf("read %d bytes:\"%s\" from file:%s\n",strlen(buff),buff,path);
        waitpid(-1,NULL,0);
        close(fd);
    } else
    printf("open file :%s failed\n",path);
    return 0;
}
