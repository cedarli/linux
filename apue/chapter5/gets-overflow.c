#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#pragma pack(1)
struct bufs {
    char buf0[4];
    char buf1[4];
    char buf2[4];
};

int main(int argc, char *argv[]) {
    struct bufs buf;
    memset(&buf, 0, sizeof(buf));
    printf("input exactly 7 chars to see the overflow.\ninput a long line to see seg fault.\n");
    gets(buf.buf1-5);
    printf("buf.buf0:%*s\n", (int)sizeof(buf.buf0), buf.buf0);
    printf("buf.buf1:%*s\n", (int)sizeof(buf.buf1), buf.buf1);
    pause();
//    printf("buf.buf2:%*s\n", (int)sizeof(buf.buf2), buf.buf2);
    return 0;
}
