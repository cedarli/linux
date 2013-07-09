#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#define PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#define ARG_MAX 1000
static char envbuf[ARG_MAX];
extern char **environ;

char *getenv(const char *name){
    int i,len;
    len = strlen(name);
    for ( i=0;environ[i] != NULL; i++ ){
        if ((strncmp(name,environ[i],len) == 0) && (environ[i] == '=') ){
            strcpy(envbuf,&environ[i][len+1]);
            return envbuf;
        }
    }
    return NULL;
}

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void){
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex,&attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf,int buflen){
    int i,len,olen;
    pthread_once(&init_done,thread_init);
    len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for ( i=0;environ[i] != NULL;i++) {
        if ( (strncmp(name,environ[i],len) == 0) && (environ[i][len] == '=') ) {
            olen = strlen(&environ[i][len+1]);
            if ( olen >= buflen ) {
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strcpy(buf,&environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}

int main(int argc,char *argv[]){
    char buf[256],*temp;
    printf("getenv call \n");
    temp = getenv("PATH");
    printf("getenv =%s\n",temp);
    printf("getenv_r call \n");
    getenv_r("PATH",buf,256);
    printf("buf=%s\n",buf);
    exit(0);
}
