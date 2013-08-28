all: client_shm server_shm

client_shm:client_shm.o
	gcc -o $@ $<
client_shm.o:client_shm.c
	gcc -c client_shm.c

server_shm:server_shm.o
	gcc -o $@ $<
server_shm.o:server_shm.c
	gcc -c server_shm.c

clean:
	rm *.o
