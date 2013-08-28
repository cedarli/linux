#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int shmid;
    char *shm, *s;

    key_t key = 5678;

    if ((shmid = shmget(key, 0, 0666)) < 0) {
        printf("shmget: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
        exit(1);
    }
	/*link shm to self-process-address*/
    if ((shm = shmat(shmid, NULL, 0/*SHM_RDONLY*/)) == (char *) -1) {
        printf("shmmat: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
        exit(1);
    }

    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    
	putchar('\n');

	{
		printf("its %d to change share-memory first byte to '*' \n",getpid());
		sleep(2);
		*shm = '*';
		
	}
	if( shmdt(shm) != 0){
        printf("shmdt: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
	}

	return 0;
}

