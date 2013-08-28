all:main libcstruct.so

main:main.c libcstruct.so
	gcc  -o main -I./  main.c ./libcstruct.so
libcstruct.so:list.o
	gcc -shared -lc -o libcstruct.so list.o
list.o:
	gcc -c -fPIC -I ./ list.c

clean:
	rm *.o main libcstruct.so
