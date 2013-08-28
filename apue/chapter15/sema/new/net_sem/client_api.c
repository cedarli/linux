#include"client_data.h"
#include"client_api.h"
#define DEBUG

/*read-write*/
ssize_t readn(int sockfd,char*vptr,const int num){
	printf("FUNCTION:%s LINE:%d\n",__FUNCTION__,__LINE__);
	size_t nleft;
	ssize_t nread;
	char *ptr;
	
	ptr = vptr;
	nleft = num;
	
	while(nleft > 0)
	{
		if((nread = read(sockfd, ptr, nleft)) < 0)
		{
			if( EINTR == errno)		//the connection is broken
				nread = 0;
			else
				return(nread);		//if error, may be less than Zero
		}
		else if(0 == nread)			//EOF
			break;
		
		nleft -= nread;
		ptr += nread;
	}

	return (num-nleft);

}
ssize_t writen(int sockfd,char*vptr,const int num){
	printf("FUNCTION:%s,LINE:%d:\n",__FUNCTION__,__LINE__);
	ssize_t	nwritten;
	size_t nleft;
	const char *ptr;

	ptr = vptr;
	nleft = num;
	
	while(nleft > 0)
	{
		if((nwritten = write(sockfd, ptr, nleft)) <= 0)
		{
			if( EINTR == errno) 		//the connection is broken
			{
				printf("interrupt by signal before any data has been read!");
				nwritten = 0;
			}
			else
			{
				//EOF
				return(nwritten);
			}
		}
		nleft -=  nwritten;				//left
		ptr += nwritten;				//move the pointer
	}
	
	return num;

}
/*semaphore reference*/
 int initial_socket_semaphore(sem_t *semaphore)
{
    if(sem_init(semaphore, 0, 1) != 0)    //no shared with others process,just inner pthread
    {
        perror("sem_init");
        return -1;
    }

	return 0;
}

 void destroy_socket_semaphore(sem_t *semaphore)
{
    sem_destroy(semaphore);
    return;
}

/*socket */
int sock_connect(int client_sockfd[],int fdnum){
	int i;
	int ret;
	struct sockaddr_in servaddr;
	
	if( fdnum< 0 || fdnum > 2)
		perror("wrong number of client sockfd");
	
	for(i=0;i<fdnum;i++){
		if((client_sockfd[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("sock:");
			return -1;
		}

		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		servaddr.sin_port = htons(PORTS+i);
		bzero(&(servaddr.sin_zero),8);

		ret = connect(client_sockfd[i],(struct sockaddr*)&servaddr,(socklen_t)sizeof(struct sockaddr));
		if( ret != 0)
			perror("bind:");
	}
	return 0;
}

/*thread funcs*/
void *read_sock_func(void *arg){
	int *client_sockfd = (int *)arg;
	int newfd = *client_sockfd;
	int nread,nwrite;
	
	for(;;){

		sem_wait(&mydata.read_write_semaphore);
		do
		{
			printf("To read:\n");
			memset(mydata.buf,'\0',sizeof(mydata.buf));
			/*read from sockfd*/
			nread = readn(newfd,mydata.buf,sizeof(mydata.buf));
			if( nread<0)
				perror("readn:");
			nwrite = writen(STDOUT_FILENO,mydata.buf,nread);
			if( nwrite != nread)
				perror("nwrite:");
		}while(1);
		
		sem_post(&mydata.read_write_semaphore);
	}
	
}
void *write_sock_func(void *arg){
	int *server_sockfd = (int *)arg;
	int newfd=*server_sockfd;
	int nread,nwrite;
	
	for(;;){
		sem_wait(&mydata.read_write_semaphore);
		do
		{
			printf("To write:\n");
			memset(mydata.buf,'\0',sizeof(mydata.buf));
			nread = readn(STDIN_FILENO,mydata.buf,sizeof(mydata.buf));
			if( nread<0){
				perror("readn:");
				break;
			}
			//write to newsock
			nwrite = writen(newfd,mydata.buf,nread);
			if( nwrite != nread){
				perror("nwrite:");
				break;
			}
		}while(1);
		sem_post(&mydata.read_write_semaphore);
	}

}

