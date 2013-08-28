
all:server client

server.o: server.c
	gcc -c  server.c
server_api.o:server_api.c
	gcc -c server_api.c
server:server.o server_api.o
	gcc server.o server_api.o -o server  -lpthread


client.o:client.c
	gcc -c client.c
client_api.o:client_api.c
	gcc -c client_api.c 
client:client.o client_api.o
	gcc client.o client_api.o -o client -lpthread

clean:
	rm *.o
