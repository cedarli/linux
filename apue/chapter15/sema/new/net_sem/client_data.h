#ifndef _CLIENT_DATA_H
#define _CLIENT_DATA_H
#include<semaphore.h>
#define BUFSIZE 1024
#define SOCKNUM 2
#define PORTS 2013
struct {
	char buf[BUFSIZE];
	sem_t read_write_semaphore;
	int client_sockfd[SOCKNUM];
}mydata;

#endif
