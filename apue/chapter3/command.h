#ifndef __COMMAND_H
#define __COMMAND_H	

#define TESTMAGIC 	't'

#define IO_TEST  _IO(TESTMAGIC,0x01)
#define SET_TEST _IOW(TESTMAGIC,0x02,int)
#define GET_TEST _IOR(TESTMAGIC,0x03,int)

#define MAX_CMD_NUM 4

#endif 
