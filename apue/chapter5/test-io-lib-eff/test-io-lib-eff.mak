all:
	@echo "\n=======================\nbuild uclibc version"
	gcc -Wall -g -O3 -std=c99 -pipe -nostdinc -nostdlib -I/usr/x86_64-linux-uclibc/usr/include -L/usr/x86_64-linux-uclibc/usr/lib -o test-io-lib-eff-ulibc.out test-io-lib-eff.c -iwithprefix include /usr/x86_64-linux-uclibc/usr/lib/crti.o /usr/x86_64-linux-uclibc/usr/lib/crt1.o /usr/x86_64-linux-uclibc/usr/lib/crtn.o -lc -static

	@echo "\n=======================\nbuild glibc version"
	gcc -Wall -g -O3 -std=c99 -pipe -static test-io-lib-eff.c -o test-io-lib-eff-glibc.out
