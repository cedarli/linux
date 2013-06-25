#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <syslog.h>

sigset_t mask;
extern int already_runing(void);

void reload(void){
    /*reload config file*/
    printf("reload configuration file\n");
}

void thr_fn(void *arg){
    int err,signo;
    for(;;){
        err = sigwait(&mask,signo);
        if( err != 0 ){
            syslog(LOG_ERR,"sigwait failed");
            exit(1);
        }
        switch ( signo ){
            case SIGHUP:
                syslog(LOG_INFO,"Re-reading configuration file");
                reload();
                break;
            case SIGTERM:
                syslog(LOG_INFO,"got SIGTERM; exiting");
                exit(0);
            default:
                syslog(LOG_INFO,"unexpected signal %d\n",signo);
        }
    }
    return 0;
}


int main ( int argc,char *argv[] ){
    int err;
    pthread_t tid;
    char *cmd;
    struct sigaction sa;
    if ( ( cmd = strrchr(argv[0],'/') ) == NULL )
        cmd = argv[0];
    else
        cmd++;
    /**
     * Become a  daemon.
     */
    daemonize(cmd);
    /**
     * Make sure only one copy of the daemon is runing.
     */
    if ( already_runing() ){
        syslog(LOG_ERR,"daemon alread running");
        exit(1);
    }
    /**
     * Restore SIGHUP default and block all signals.
     */
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if ( sigaction(SIGHUP,&sa,NULL) < 0 )
        printf("can't restore SIGHUP default' \n");
    sigfillset(&mask);
    if ( ( err = pthread_sigmask(SIG_BLOCK,&mask,NULL)) != 0 )
        printf("SIG_BLOCK error \n");
    /**
     * Create a thread to handle SIGHUP and SIGTERM.
     */
    err = pthread_create(&tid,NULL,thr_fn,0);
    if ( err != 0 )
        printf("can't create thread\n");
    /**
     * Proceed with the rest of the daemon.
     */
    exit(0);
}
