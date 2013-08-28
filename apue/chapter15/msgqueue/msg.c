#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 

int main(int argc, char *argv[])  
{  
    int msgid;  
      
    int status;  
    char str1[]={"test message:hello msgtest"};  
    char str2[]={"test message:goodbye msgtest"};  
      
    struct msgbuf  
    {  
    	long msgtype;  
    	char msgtext[1024];  
    }sndmsg,rcvmsg;  
  
    if((msgid = msgget(IPC_PRIVATE,0666))==-1)  
    {  
    	printf("msgget error!\n");  
    	exit(1);  
    }  
  
    sndmsg.msgtype =111;  
    sprintf(sndmsg.msgtext,str1);  
  
    if(msgsnd(msgid,(struct msgbuf *)&sndmsg,sizeof(str1)+1,0)==-1)  
    {  
    	printf("msgsnd error!\n");  
    	exit(1);  
    }  
  
    sndmsg.msgtype =222;  
    sprintf(sndmsg.msgtext,str2);  
    if(msgsnd(msgid,(struct msgbuf *)&sndmsg,sizeof(str2)+1,0)==-1)  
    {  
    	printf("msgsnd error\n");  
    	exit(1);  
    }  
  
    if((status = msgrcv(msgid,(struct msgbuf *)&rcvmsg,80,222,IPC_NOWAIT))==-1)  
    {  
    	printf("msgrcv error\n");  
    	exit(1);  
    }  
  
    printf("The receved message:%s\n",rcvmsg.msgtext);  
    msgctl(msgid,IPC_RMID,0);  
    exit(0);  
}  
