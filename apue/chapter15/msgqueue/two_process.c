#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<stdio.h>


int main(int argc,char*argv[])
{
	int msgid;
	pid_t pid;
	key_t msg_key;
	char *str1 = "linux is my favoriate!";
	char *str2 = "i do like linux system!";
	int ret;
	struct msgbuf{
		long msgtype;
		char data[256];
	}sendmsg,recvmsg;
		
	msg_key = ftok("/tmp/msg",16);
	if(msg_key == -1)
		puts("ftok failed\n");

	msgid = msgget(msg_key,0666);
	if(msgid == -1)
		puts("msgget failed\n");
	sendmsg.msgtype=100;
	sprintf(sendmsg.data,"%s",str1);
	if(msgsnd(msgid,&sendmsg,256,0) == -1)
		puts("msgsnd failed\n");
	
	if(( pid=fork()) < 0)
		puts("fork error\n");
	else if( pid == 0){
		ret = msgrcv(msgid,&recvmsg,256,100,0);
		printf("child reveive data:%s\n",recvmsg.data);
		exit(-1);
	}else{
		waitpid(pid,NULL);
		msgctl(msgid,RMV);	
	}
	return 0;
}
