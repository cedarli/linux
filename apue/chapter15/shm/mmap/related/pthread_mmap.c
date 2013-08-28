#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h> 
#include <pthread.h>
#include <string.h>
#include <errno.h>

static struct _data{
	sem_t sem;
	char arry[128];
}data;
void* feed_func(void *arg){	
	struct _data *data = arg;
	int ret, value;

	while(1){
		ret = sem_getvalue(&data->sem,&value);
		if(ret != 0){
			printf("sem_getvalue , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
			pthread_exit(NULL);
		}else
			printf("%s : sem value:%d\n",__func__,value);

		if( sem_wait(&(data->sem )) != 0 ){
			printf("sem_wait , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
			pthread_exit(NULL);
		}
		sprintf(data->arry,"this is feed_fun #################");
		printf("%s\n",data->arry);
		if(sem_post( &(data->sem))  != 0 ){
			printf("sem_post , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
			pthread_exit(NULL);
		}
		sleep(1);
	}
	return (void *)0;
}
void* consume_func(void *arg){
	struct _data *data = arg;
	while(1){
		sleep(1);
		if( sem_wait(&(data->sem )) != 0 ){
			printf("sem_wait , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
			pthread_exit(NULL);
		}
		sprintf(data->arry,"this is consume_fun @@@@@@@@@@@@@@@@@@@@");
		printf("%s\n",data->arry);
		
		if(sem_post( &(data->sem))  != 0 ){
			printf("sem_post , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
			pthread_exit(NULL);
		}
	
		sleep(1);
	}
	return (void *)0;
}


int main(void)
{
	int ret;
	pthread_t pth_feed,pth_consume;

	ret = sem_init(&data.sem,0,1);  //shared pthreads;the initializeation value is 1 
	if( ret != 0){
		printf("sem_intit , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
	}

	ret = pthread_create(&pth_feed,NULL,feed_func,&data);
	if( ret <  0){
		printf("pthread_create, err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
	}
#if 0
	ret = pthread_create(&pth_consume,NULL,consume_func,&data);
	if( ret <  0){
		printf("pthread_create , err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
	}

	pthread_join(pth_consume,NULL);
#endif	
	pthread_join(pth_feed,NULL);

	ret = sem_destroy(&data.sem);
	if( ret !=  0){
		printf("sem_destroy, err:%d %s, line:%d\n",errno,strerror(errno),__LINE__);
	}

	return 0;
}
