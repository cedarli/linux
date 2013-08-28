#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHMSZ    1024 
#define DEBUG 

int main(int argc,char*argv[])
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;//ftok
 
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        printf("shmget: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
        exit(-1);
    }else
        printf("shmget: line:%d success\n",__LINE__);

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        printf("shmget: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	 }else
        printf("shmat: line:%d success\n",__LINE__);

#ifdef DEBUG
	printf("#######");
#endif
    s = shm;

#ifdef DEBUG
	printf("######");
#endif
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = '\0';
	/*wait for the change*/
    while (*shm != '*'){
		//printf("wait child process to change the content of the share-memory to *");
		write(STDOUT_FILENO,"wait child process to change share-memory \n",64);
        sleep(1);
	}
	
	return 0;
}

