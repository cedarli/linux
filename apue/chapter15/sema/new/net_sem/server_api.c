#include"server_data.h"
#include"server_api.h"

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
/*sock*/
 int sock_listen(int server_sockfd[], int fdnum) 
{
	int err;
	const int on = 1;
	static struct sockaddr_in server_addr;
	int i;
	
	if((fdnum < 0)|| (fdnum > SOCKNUM))
	{
		printf("error! don't alloc so much socket ports\n");
		return -1;
	}
	for(i = 0; i< fdnum; i++)
	{
		if((server_sockfd[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("sock:");
			return -1;
		}
		
		setsockopt(server_sockfd[i], SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); //make address reused.

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		server_addr.sin_port = htons(PORTS+i);
		bzero(&(server_addr.sin_zero),8);

		if( (err= bind(server_sockfd[i], (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) < 0)
		{
			perror("bind:");
			close(server_sockfd[i]);
			return -1;
		}
		if((err = listen(server_sockfd[i], LISTEN_NUM)) < 0)
		{
			perror("listen:");
			close(server_sockfd[i]);
			return -1;
		}
		printf("server_sockfd[%d]=%d\n",i,server_sockfd[i]);
	}
	return 0;
}

 int sock_accept(int server_sockfd)
{
	static int client_sockfd;
	static struct sockaddr_in client_addr;
	int client_sockfd_size;

	client_sockfd_size = sizeof(struct sockaddr_in);
	if((client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_addr, (socklen_t *)&client_sockfd_size)) < 0)
	{
		perror("accept:");
		close(server_sockfd);
		return -1;
	}
	return client_sockfd;
}

/*thread funcs*/
void *read_sock_func(void *arg){
	int *server_sockfd = (int *)arg;
	int newfd;
	int nread,nwrite;
	
	for(;;){
		printf("now:%s %d\n",__FUNCTION__,__LINE__);
		newfd = sock_accept(*server_sockfd);
		printf("accetpt done.\n");
		if( newfd < 0)
			continue;
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
	int newfd;
	int nread,nwrite;
	
	for(;;){
		newfd = sock_accept(*server_sockfd);
		if( newfd < 0)
			continue;
		sem_wait(&mydata.read_write_semaphore);
		do
		{
			printf("To write:\n");
			memset(mydata.buf,'\0',sizeof(mydata.buf));
			nread = readn(STDIN_FILENO,mydata.buf,sizeof(mydata.buf));
			if( nread<0)
				perror("readn:");
			//write to newsock
			nwrite = writen(newfd,mydata.buf,nread);
			if( nwrite != nread)
				perror("nwrite:");
		}while(1);
		sem_post(&mydata.read_write_semaphore);
	}

}

