#include <stdio.h>
#include <wchar.h>
#include <assert.h>

int main() {
    wchar_t * wstr = L"hello";
    FILE * fp = fopen("test-fwide-w.dat", "w");
    assert(fp);
    printf("stream orientation: %d\n", fwide(fp, 0));
    fwprintf(fp, L"%ls\n", wstr);
    printf("strlen(wstr)=%ld\n", wcslen(wstr));
    printf("stream orientation: %d\n", fwide(fp, 0));
    fclose(fp);

    char * str="hello";
    fp = fopen("test-fwide-c.dat", "w");
    assert(fp);
    printf("stream orientation: %d\n", fwide(fp, 0));
    fprintf(fp, "%s\n", str);
    printf("stream orientation: %d\n", fwide(fp, 0));
    fclose(fp);
    return 0;
}
