#include"head.h"

int main(int argc,char *argv[])
{
    int fd;
    fd = open("./test.txt",O_RDWR|O_CREAT|O_EXCL);
    if(fd < 0)
        printf("file has exited\n");

    return 0;
}
