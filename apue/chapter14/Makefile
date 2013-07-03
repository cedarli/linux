#Filename Makefile
#this file is used for show how to compile program.
CC :=gcc
CFLAGS :=-g -Wall
SOURCE := $(wildcard *.c)
TARGETS := $(patsubst %.c,%,$(SOURCE))
ALL : $(TARGETS)
	@for temp in $(TARGETS); \
$(info $(temp))
	do \
$(temp):$(temp).c \
	$(CC) $(CFLAGS) -o $(temp) \
	done
