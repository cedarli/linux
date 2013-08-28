#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

#include <string.h>
#include <errno.h>

union semun 
{ 
    int val; 
    struct semid_ds *buf; 
    unsigned short int *array; 
    struct seminfo *__buf; 
}; 
 
int main(void) 
{ 
    char* buf_father[]={"process ", "say ", "i ", "consume ", "semaphore! "}; 
    int i = 0,ret ; 
    struct sembuf sb;  //operation array
    union semun sem;  //semctl parameter

	key_t key = ftok("/tmp/semkey",32);
	if( key < 0){
		printf("ftok,line:%d err:%d %s\n",__LINE__,errno,strerror(errno));
	}
    int semid = semget(key, 1, 0666 | IPC_CREAT/* | IPC_EXCL*/); //one set contains one semaphores
	if( semid < 0){
		printf("semget,line:%d err:%d %s\n",__LINE__,errno,strerror(errno));
	}

	/*initialize*/
    sem.val = 0; 
    semctl(semid, 0, SETVAL, sem); //初始化第0号信号量为0
 	
	while (i < 5) { 
		sb.sem_num = 0; //将0号信号量
		sb.sem_op = -1; //减1
	    sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT; 
		
		semop(semid, &sb, 1); //操作信号量 ;挂起

		write(STDOUT_FILENO,buf_father[i], strlen(buf_father[i])); 
		i++; 
	}
 	putchar('\n');
	if ( ret = semctl(semid,0,IPC_RMID) != 0 ){
		printf("semctl,line:%d err:%d %s\n",__LINE__,errno,strerror(errno));
	}
	sleep(1);

    return 0; 
} 
