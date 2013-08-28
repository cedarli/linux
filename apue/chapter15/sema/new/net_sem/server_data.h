#ifndef _MYSEMAP_H
#define _MYSEMAP_H

#define SOCKNUM 2
#define BUFSIZE 1024
#include<semaphore.h>
struct {
	char buf[BUFSIZE];
	sem_t read_write_semaphore;
	int server_sockfd[SOCKNUM];
}mydata;

#define PORTS 2013
#define LISTEN_NUM 5

#endif
