#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int     c;

    while ((c = getchar()) != EOF) {
        if (isupper(c))
            c = tolower(c);
        if (putchar(c) == EOF)
       		break;
		 if (c == '\n'){
			break;
            fflush(stdout);
		}
    }
    exit(0);
}


