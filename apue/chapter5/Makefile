CC=gcc
CFLAGS=-Wall -g -O2 -std=c99 -pipe

.PHONEY:clean 

%.out:%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.out *.dat
