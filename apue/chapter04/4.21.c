#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
	DIR *pDir;
	struct dirent *pDirent;
	
	if((pDir = opendir(argv[1])) == NULL)
		perror("opendir error");
	
	printf("current location:%ld\n",telldir(pDir));
	
	while((pDirent = readdir(pDir)) != NULL)
	{
		printf("inode number:%d\n",pDirent->d_ino);
		printf("filename:%s\n",pDirent->d_name);
		//printf("offset to the next dirent:%d\n",pDirent->d_off);
		//printf("length of this record:%d\n",pDirent->d_reclen);
		//printf("type of file:%d\n",pDirent->d_type);
		
		
		printf("current location:%ld\n",telldir(pDir));
		
		printf("\n");
	}
	printf("current location:%ld\n",telldir(pDir));
	rewinddir(pDir);
	printf("current location:%ld\n",telldir(pDir));
	
	closedir(pDir);
	
	
	exit(0);
}