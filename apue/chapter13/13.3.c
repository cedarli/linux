#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize( const char *cmd ) {
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit r1;
    struct sigaction sa;
    /**
     * clear file creation mask.
     */
    umask(0);
    /**
     * Get maximum number of fele descriptors.
     */
    if ( getrlimit(RLIMIT_NOFILE,&r1) < 0 )
        printf("%s:can't get file limit\n",cmd);
    /**
     * Become a session leader to lose controlling TTY.
     */
    if ((pid = fork()) < 0 )
        printf("%s:can't fork\n",cmd);
    else if ( pid != 0 )/*parent*/
        exit(0);
    setsid();
    /**
     * Ensure future opens won't allocate controlling TTYs
     */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if ( sigaction(SIGHUP,&sa,NULL) < 0 )
        printf("%s:can't ignore SIGHUP\n",cmd);
    if ( (pid = fork()) < 0 )
        printf("%s:can't fork\n",cmd);
    else if ( pid != 0 ) /*parent*/
        exit(0);
    /**
     * Change the current working directory to the root so 
     * we won't prevent file systems form being unmounted.
     */
    if ( chdir("/")<0 )
        printf("%s:can't change directory to / \n");
    /**
     * Close all open file descriptors.
     */
    if (r1.rlim_max == RLIM_INFINITY )
        r1.rlim_max = 1024;
    for ( i=0;i<r1.rlim_max;i++ )
        close(i);
    /**
     * Attach file descriptors 0,1 and 2 to /dev/null.
     */
    fd0 = open("/dev/null",O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    /**
     * Initialize the log file.
     */
    openlog(cmd,LOG_CONS,LOG_DAEMON);
    syslog(LOG_ERR,"test syslog \n");
    if (fd0 != 0 || fd1 != 1 || fd2 != 2 ){
        syslog(LOG_ERR,"unexpected file descriptors %d %d %d",fd0,fd2,fd2);
        exit(1);
    }
}
void main (void){

    daemonize("abc");
    sleep(100);
}
