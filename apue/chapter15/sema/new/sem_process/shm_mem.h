#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/ipc.h> 
#include<sys/sem.h> 
#include<sys/shm.h> 
#include<error.h> 
#include<errno.h>
#include<string.h>

# define SHM_SIZE     1024

/*semaphore coperation param*/
union semun{ 
    int val; 
    struct semid_ds * buf; 
    unsigned short * array; 
    struct seminfo * buf_info; 
    void * pad; 
} ; 

/* create sempahore set*/ 
int creatsem( const char * pathname, int proj_id, int members, int init_val) 
{ 
    key_t msgkey; 
    int index, sid; 
    union semun semopts; 
    
    if ( ( msgkey = ftok( pathname, proj_id) ) == -1) { 
        printf ( "ftok error:%d %s line:%d\n",errno,strerror(errno),__LINE__ ) ; 
        return - 1; 
    } 
    if ( ( sid = semget( msgkey, members, IPC_CREAT| 0666) ) == -1) { 
        printf ( "semget error:%d %s line:%d\n",errno,strerror(errno),__LINE__ ) ; 
        return - 1; 
    } 
    semopts.val = init_val;
    for ( index = 0; index< members; index++ ) {  //initialize semaphore in the set;
        semctl( sid, index, SETVAL, semopts) ; 
    } 
    
    return sid; 
} 

int opensem( const char * pathname, int proj_id) 
{ 
    key_t msgkey; 
    int sid; 
    
    if ( ( msgkey = ftok( pathname, proj_id) ) == -1) { 
        perror ("ftok error!/n"); 
        return - 1; 
    } 
    
    if( ( sid = semget(msgkey, 0, 0666) ) == -1) { 
        perror ( "open semget call failed./n" ) ; 
        return - 1; 
    } 
    return sid; 
} 

/* p operation*/ 
int sem_p( int semid, int index) 
{ 
    struct sembuf sbuf = { 0, -1, IPC_NOWAIT};  //do -1 operation to semaphore 0
    if ( index < 0) { 
        perror ( "index of array cannot equals a minus value!/n" ) ; 
        return - 1; 
    } 
 
   sbuf.sem_num = index; 

    if ( semop( semid, & sbuf, 1) == -1) { 
        perror ( "A wrong operation to semaphore occurred!/n" ) ; 
        return - 1; 
    } 
    return 0; 
} 

/* V operaion*/ 
int sem_v( int semid, int index) 
{ 
    struct sembuf sbuf = { 0, 1, IPC_NOWAIT} ; 
    if ( index < 0) { 
        perror ( "index of array cannot equals a minus value!/n" ) ; 
        return - 1; 
    } 
    sbuf.sem_num = index; //index of semapore in the set
    if ( semop( semid, & sbuf, 1) == -1) { 
        perror ( "A wrong operation to semaphore occurred!/n" ) ; 
        return - 1; 
    } 
    return 0; 
} 

/* delete sempahore set*/ 
int sem_delete( int semid) 
{ 
    return ( semctl( semid, 0, IPC_RMID) ) ; 
} 

/* wait semaphore to be 1*/ 
int wait_sem( int semid, int index) 
{ 
    while ( semctl(semid, index, GETVAL, 0) == 0) 
    { 
        usleep ( 500) ; 
    } 
    return 1; 

} 

/* create share memory*/ 
int creatshm( char * pathname, int proj_id, size_t size) 
{ 
    key_t shmkey; 
    int sid; 
    
    if ( ( shmkey = ftok( pathname, proj_id) ) == -1) { 
        perror ( "ftok error!/n" ); 
        return - 1; 
    } 
    if ( ( sid = shmget( shmkey, size, IPC_CREAT| 0666) ) == -1) { 
        perror ( "shm call failed!/n" ) ; 
        return - 1; 
    } 
    return sid; 
} 

/* delete share memory*/ 
int deleteshm( int sid) 
{ 
    void * p = NULL ; 
    return ( shmctl( sid, IPC_RMID, p)) ; 
}
 
