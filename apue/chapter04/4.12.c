#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

char    buf1[] = "abcdefghij";
char    buf2[] = "ABCDEFGHIJ";
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int
main(int argc, char *argv[])
{
	int     fd;

    if ((fd = creat("hole", FILE_MODE)) < 0)
        printf("creat error");

    if (write(fd, buf1, 10) != 10)
        printf("buf1 write error");
    /* offset now = 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        printf("lseek error");
    /* offset now = 16384 */

    if (write(fd, buf2, 10) != 10)
        printf("buf2 write error");
    /* offset now = 16394 */

    exit(0);

}
