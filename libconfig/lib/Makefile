all:remote client
remote:remote.o
	gcc -o $@ $<
remote.o:remote.c
	gcc -c $<

client:client.o
	gcc -o $@ $<
client.o:client.c
	gcc -c $<
