#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <errno.h>
#include <string.h>

union semun 
{ 
    int val; 
    struct semid_ds *buf; 
    unsigned short int *array; 
    struct seminfo *__buf; 
}; 
 
int main(void) 
{ 
    int i = 0; 
    struct sembuf sb; 
    union semun sem; 
 
	key_t key = ftok("/tmp/semkey",32);
	if( key < 0){
		printf("ftok,err:%d %s\n",errno,strerror(errno));
	}

    int semid = semget(key, 0,0666); //use the exist semaphore set
	if( semid < 0){
		printf("semget,err:%d %s\n",errno,strerror(errno));
	}
 
	while (i < 5) { 
		sb.sem_num = 0; 		//将0号信号量
		sb.sem_op = 1;  		//加1
	    sb.sem_flg = sb.sem_flg & ~IPC_NOWAIT; 
		semop(semid, &sb, 1); 	//操作信号量
		
		i++; 
		sleep(2);
	} 

    return 0; 
} 
