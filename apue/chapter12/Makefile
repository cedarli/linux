#Filename Makefile
#this file is used for show how to compile program.
CC :=gcc
CFLAGS := -g -Wall -pthread
SOURCE := $(wildcard *.c)
TARGETS := $(patsubst %.c,%,$(SOURCE))
$(info $(TARGETS))
ALL:$(TARGETS)
clean:
	rm -f $(TARGETS)
