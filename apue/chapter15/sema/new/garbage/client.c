#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<semaphore.h>

int main(int argc,char*argv[])
{
    char c;
    int ret ,shmid;
    void *shm, *s;
    key_t key = 1234;
 	sem_t sem;

    if ((shmid = shmget(key, 0,  0666)) < 0) {
        printf("shmget: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
        exit(-1);
    }else
        printf("shmget: line:%d success\n",__LINE__);
	
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        printf("shmget: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	 }else
        printf("shmat: line:%d success\n",__LINE__);
    
	s = shm;
	
	if( sem_wait(s)  != 0 ){
        printf("shmwait: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	}
	printf("%d ########remote have increase the sem value\n",getpid());

	return 0;
}

