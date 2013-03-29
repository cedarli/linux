#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	struct stat buf;
	char *pName;
	
	printf("%s: ",argv[1]);
	if(lstat(argv[1],&buf)<0){
		perror("lstat error\n");
		exit(1);
	}
	printf("size:%d\n",sizeof(buf));
	if(S_ISREG(buf.st_mode))
		pName="regular";
	else if (S_ISDIR(buf.st_mode))
		pName = "directory";
	else if (S_ISCHR(buf.st_mode))
		pName = "character special";
	else if (S_ISBLK(buf.st_mode))
		pName = "block special";
	else if (S_ISFIFO(buf.st_mode))
		pName = "fifo";
	else if (S_ISLNK(buf.st_mode))
		pName = "symbolic link";
	else if (S_ISSOCK(buf.st_mode))
		pName = "socket";
	else
		pName = "** unknown mode **";
	printf("%s\n", pName);
	printf("inode number: %d\n",buf.st_ino);
	
	printf("ID of device containing file: %d\n", buf.st_dev);
	printf("dev = %d/%d\n", major(buf.st_dev), minor(buf.st_dev));

	printf("device ID (if special file): %d\n",buf.st_rdev);
	printf("rdev = %d/%d\n", major(buf.st_rdev), minor(buf.st_rdev));
	
	printf("number of hard links: %d\n",buf.st_nlink);
	printf("user ID of owner: %d\n",buf.st_uid);
	printf("group ID of owner: %d\n",buf.st_gid);
	printf("total size, in bytes: %d\n",buf.st_size);
	
	printf("blocksize for file system I/O: %d\n",buf.st_blksize);
	printf("number of 512B blocks allocated: %d\n",buf.st_blocks);
	
	
	exit(0);
		
}
