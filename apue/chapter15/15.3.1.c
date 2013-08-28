#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PAGER "${PAGER:-more}" /*enviroment variable,or default*/
#define MAXLINE 512

int main ( int argc ,char *argv[]){
    char line[MAXLINE];
    FILE *fpin,*fpout;
    if (argc != 2 )
        printf("usage: a.out <pathname>\n");
    if ((fpin = fopen(argv[1],"r")) == NULL)
        printf("can't open %s \n",argv[1]);
    if ((fpout = popen(PAGER,"w")) == NULL)
        printf("popen error \n");
    /*copy argv[1] to pager*/
    while ( fgets(line,MAXLINE,fpin) != NULL ) {
        if ( fputs(line,fpout) == EOF )
            printf("fputs error to pipe \n");
    }
    if ( ferror(fpin) )
        printf("fgets eror\n");
    if ( pclose(fpout) == -1 )
        printf("pclose error\n");
    exit(0);
}
