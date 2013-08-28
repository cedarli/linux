#ifndef __APIS__H_
#define __APIS__H_

void TELL_WAIT(void);

void TELL_PARENT(pid_t pid);

void WAIT_PARENT(void);

void TELL_CHILD(pid_t pid);
void WAIT_CHILD(void);

#endif
