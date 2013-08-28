#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 512

int main ( int argc ,char *argv[]){
    char line[MAXLINE];
    FILE *fpin;
    if (argc != 2 )
        printf("usage: a.out <pathname>\n");
    if ((fpin = popen("./myuclc","r")) == NULL)
        printf("can't popen error \n");
    for (;;){
        fputs("promot>",stdout);
        fflush(stdout);
        if ( fgets(line,MAXLINE,fpin) == NULL ) /*read from pipe*/
            break;
        if ( fputs(line,stdout) == EOF )
            printf("fputs error to pipe\n");
    }
    exit(0);
}
