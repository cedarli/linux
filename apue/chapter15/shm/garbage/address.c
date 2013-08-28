#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define ARRAY_SIZE  40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    0600    /* user read/write */

#define SUBKEY  0x13

char    array[ARRAY_SIZE];  /* uninitialized data = bss */

int main(void)
{
    int     shmid;
    char    *ptr, *shmptr;
	key_t shmkey = ftok("/tmp/shm",SUBKEY);
	if( shmkey < 0 )
		exit(-1);
	else 
		printf(" shmkey is:%d\n",shmkey);
    printf("array[] from %lx to %lx\n", (unsigned long)&array[0],
      (unsigned long)&array[ARRAY_SIZE]);
    printf("stack around %lx\n", (unsigned long)&shmid);

    if ((ptr = malloc(MALLOC_SIZE)) == NULL)
        perror("malloc error");
    printf("malloced from %lx to %lx\n", (unsigned long)ptr,
      (unsigned long)ptr+MALLOC_SIZE);

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) //IPC_PRIVATE
        perror("shmget error");
    if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
        perror("shmat error");
    printf("shared memory attached from %lx to %lx\n",
      (unsigned long)shmptr, (unsigned long)shmptr+SHM_SIZE);

    if (shmctl(shmid, IPC_RMID, 0) < 0)
        perror("shmctl error");

    exit(0);
}

