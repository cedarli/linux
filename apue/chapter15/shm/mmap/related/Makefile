all:pthread_mmap mmap_zero

pthread_mmap:pthread_mmap.o
	gcc -o pthread_mmap pthread_mmap.o -lpthread
pthread_mmap.o:pthread_mmap.c
	gcc -c pthread_mmap.c

mmap_zero:mmap_zero.o apis.o
	gcc -o $@  mmap_zero.o apis.o
mmap_zero.o:mmap_zero.c
	gcc -c mmap_zero.c
apis.o:apis.c
	gcc -c apis.c

clean:
	rm *.o
