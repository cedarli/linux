#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define TELL_WAIT() printf("TELL_WAIT\n")
#define TELL_PARENT(a) printf("TELL_PARENT %d\n",a)
#define TELL_CHILD(a) printf("TELL_CHILD %d\n",a)
#define WAIT_PARENT() printf("WAIT_PARENT\n");
#define WAIT_CHILD() printf("WAIT_CHILD\n");

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

static void lockabyte(const char *name,int fd ,off_t offset){
    if ( writew_lock(fd,offset,SEEK_SET,1) < 0 )
        printf("%s:writew_lock error\n",name);
    printf("%s:got the lock,byte %ld\n",name,offset);
}

int main(void){
    int fd;
    pid_t pid;
    /**
     * Create a file and write two bytes to it.
     */
    if ( (fd = creat("templock",FILE_MODE)) < 0 )
        printf("create error\n");
    if ( write(fd,"ab",2) != 2 )
        printf("write error\n");
    TELL_WAIT();
    if ( (pid = fork()) < 0 ){
        printf("fork error\n");
    }else if ( pid == 0 ){
        lockabyte("child",fd,0);
        TELL_PARENT(getpid());
        WAIT_PARENT();
        lockabyte("child",fd,1);
    } else {
        lockabyte("parent",fd,1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent",fd,0);
    }
    exit(0);
}
