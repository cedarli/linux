CC ：= gcc

all:feed_sem consume_sem
	
feed_sem:feed_sem.o
	$(CC) -o $@ $<
feed_sem.o:feed_sem.c
	$(CC) -c feed_sem.c

consume_sem:consume_sem.o
	$(CC) -o  $@ $<
consume_sem.o:consume_sem.c
	$(CC) -c consume_sem.c

clean:
	rm *.o 
