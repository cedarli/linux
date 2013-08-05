#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stropts.h>

int main(int argc,char * argv[]) {
    int fd,i,nmods;
    struct str_list list;
    if ( argc != 2 )
        printf("usage: %s <pathname>\n",argv[0]);
    if ( (fd = open (argv[1],O_RDONLY)) < 0 )
        printf("can't open %s\n",argv[1]);
    if ( isastream(fd) == 0 ){
        printf("%s is not a stream\n",argv[1]);
        exit(0);
    }
    /**
     * Fetch number of modules.
     */
    if ( (nmods = ioctl(fd,I_LIST,(void*)0)) < 0 )
        printf("I_LIST error for nmods\n");
    printf("#modules = %d \n",nmods);
    /**
     * Allocate storage for all the module names.
     */
    list.sl_modlist = calloc(nmods,sizeof(struct str_mlist));
    if ( list.sl_modlist == NULL )
        printf("calloc error\n");
    list.sl_nmods = nmods;
    /**
     * Fetch the module names
     */
    if ( ioctl(fd,I_LIST,&list) < 0 )
        printf("I_LIST error for list\n");
    /**
     * Print the names.
     */
    for (i=1;i<=nmods;i++)
        printf("%s :%s \n",(i== nmods)?"driver":"module",list.sl_modlist++->l_name);
    exit(0);

}
