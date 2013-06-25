#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int lock_reg(int fd,  int cmd, int type ,off_t offset, int whence, off_t len){
    struct flock lock;
    lock.l_type = type;     /*F_RDLCK,F_WRLCK,F_UNLCK*/
    lock.l_start = offset;  /*byte offset ,relative to l_whence*/
    lock.l_whence = whence; /*SEEK_SET ,SEEK_CUR,SEEK_END*/
    lock.l_len = len;       /*#bytes (0 means to EOF)*/
    return fcntl(fd,cmd,&lock);
}

pid_t lock_test(int fd, int type, off_t offset, int whence,off_t len){
    struct flock lock;
    lock.l_type = type;      /*F_RDLCK or F_WRLCK*/
    lock.l_start = offset;   /*byte offset ,relative to l_whence*/
    lock.l_whence = whence;  /*SEEK_SET ,SEEK_CUR,SEEK_END*/
    lock.l_len = len;        /*#bytes (0 means to EOF)*/
    if ( fcntl(fd,F_GETLK,&lock)<0 )
        printf("fcntl error");
    if ( lock.l_type == F_UNLCK )
        return 0;            /*false ,region isn't locked by another proc*/
    return lock.l_pid;       /*true ,return pid of lock owner*/

}

#define read_lock(fd,offset,whence,len) \
    lock_reg(fd,F_SETLK,F_RDLCK,offset,whence,len)
#define readw_lock(fd,offset,whence,len) \
    lock_reg(fd,F_SETLKW,F_RDLCK,offset,whence,len)
#define write_lock(fd,offset,whence,len) \
    lock_reg(fd,F_SETLK,F_WRLCK,offset,whence,len)
#define writew_lock(fd,offset,whence,len) \
    lock_reg(fd,F_SETLKW,F_WRLCK,offset,whence,len)
#define un_lock(fd,offset,whence,len) \
    lock_reg(fd,F_SETLK,F_UNLCK,offset,whence,len)


#define is_read_lockable(fd,offset,whence,len) \
    (lock_test(fd,F_RDLCK,offset,whence,len) == 0 )
#define is_write_lockable(fd,offset,whence,len) \
    (lock_test(fd,F_WRLCK,offset,whence,len) == 0 )
