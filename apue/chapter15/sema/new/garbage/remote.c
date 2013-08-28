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

#define SHMSZ    sizeof(int) 

int main(int argc,char*argv[])
{
    char c;
    int ret ,shmid;
    void *shm, *s;
    key_t key = 1234;
 	sem_t sem;

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
    
	s = shm;
	
	if( (ret = sem_init(&sem,1,1) ) != 0 ){ //shared among processes
        printf("shmget: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	}
	
	*s = sem;  //save sem to share memory ?
	
	if( sem_wait(&sem)  != 0 ){
        printf("shmwait: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	}

	sleep(10);  //let the chilent work now
	
	if( sem_post(&sem)  != 0 ){
        printf("shmpost: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	}else
		printf("sem_post success pid:%d\n",getpid());
	
	if( sem_destroy(&sem)  != 0 ){
        printf("semdestroy: line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	}

	sleep(3); //
	
	if( ( ret = shmctl(shmid,IPC_RMID,NULL))!= 0 ){
        printf("shmctl ,line:%d, errno:%d : %s\n",__LINE__,errno,strerror(errno));
   		exit(-1);
	}

	return 0;
}

