#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

/*
// End of file character.
//   Some things throughout the library rely on this being -1.  
#ifndef EOF
# define EOF (-1)
#endif
*/

int main(int argc, const char *argv[])
{
    printf("========= testing default char ==========\n");
    int c;
    while((c = getchar()) != EOF)
        putchar(c);
    printf("========= testing unsigned char ==========\n");
    //unsigned char d; //0xff ->0x00000ff
    /*while((d = getchar()) != EOF) // EOF -> 0xffffffff
        printf("0x%X\n", d);
        */
    return 0;
}
