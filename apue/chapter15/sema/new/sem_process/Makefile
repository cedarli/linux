all:write read

write:write.o
	gcc -o $@ $<
write.o:write.c
	gcc -c $<

read:read.o
	gcc -o $@ $<
read.o:read.c
	gcc -c $<
