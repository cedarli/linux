#ifndef SERVER_API_H
#define SERVER_API_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<errno.h>
#include<semaphore.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

ssize_t readn(int sockfd,char*vptr,const int num);
ssize_t writen(int sockfd,char*vptr,const int num);
int initial_socket_semaphore(sem_t *semaphore);
void destroy_socket_semaphore(sem_t *semaphore);
int sock_listen(int server_sockfd[], int fdnum);
int sock_accept(int server_sockfd);
void *read_sock_func(void *arg);
void *write_sock_func(void *arg);

#endif
