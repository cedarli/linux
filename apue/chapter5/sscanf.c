#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define exec_n_print(args...)  { args; puts("\n=============\n" #args); }

int main(int argc, const char *argv[])
{
    int i;
    unsigned int uint;
    float f;
    char c;
    char buf[BUFSIZ];


    exec_n_print(sscanf("1001010", "%5d", &i));
    printf("i=%d\n", i);

    exec_n_print(sscanf("100 1010", "%5d", &i));
    printf("i=%d\n", i);

    exec_n_print(sscanf("10.101010", "%4f", &f));
    printf("b=%f\n", f);

    exec_n_print(sscanf("CDEFG", "%c", &c));
    printf("c=%c\n", c);

    exec_n_print(sscanf("hello world!", "%10s", buf));
    printf("buf=%s\n", buf);

    exec_n_print(sscanf("hello-world!", "%10s", buf));
    printf("buf=%s\n", buf);

    exec_n_print(sscanf("100 789", "%*d %d", &i));
    printf("i=%d\n", i);

    exec_n_print(sscanf("-1", "%d", &uint));
    printf("uint=%u\n", uint);

    exec_n_print(sscanf("0768", "%o", &uint));
    printf("uint=0%o\n", uint);

    assert(exec_n_print(sscanf("abchijopq0768", "%3[a-g]%*[a-z]%o", buf, &uint) == 2));
    printf("buf=%s, i=0%o\n", buf, uint);

    //assert(exec_n_print(sscanf("abchijopq099", "%[a-g]%3s%[a-z]%i", buf, &i) == 2));
    //printf("buf=%s, i=%i\n", buf, i);
    
    return 0;
}
