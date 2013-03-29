#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#pragma pack(1)
typedef struct PACK1 {
    char a;
    char b;
    int c;
} PACK1;

#pragma pack(4)
typedef struct PACK4 {
    char a;
    char b;
    int c;
} PACK4;

#pragma pack()

int main(int argc, char *argv[]) {
    PACK1 pack1 = {'a', 'b', 0x0F};    
    PACK4 pack4;
    memset(&pack4, 0, sizeof(pack4));
    printf("sizeof(int)=%ld\n", sizeof(int));
    printf("pack1: a=%c, b=%c, c=0x%X\n", pack1.a, pack1.b, pack1.c); 

    FILE *fp = fopen("direct-io.dat", "w+");
    fwrite(&pack1, sizeof(pack1), 1, fp);
    fwrite(&pack1, sizeof(pack4), 1, fp);

    fseek(fp, 0, SEEK_SET);
    fread(&pack4, sizeof(pack4), 1, fp);
    printf("pack4: a=%c, b=%c, c=0x%X\n", pack4.a, pack4.b, pack4.c); 

    return 0;
}
