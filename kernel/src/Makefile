obj-m := hello.o
KDIR := /lib/modules/2.6.32/build/
PWD := $(shell pwd)
all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c modules.* Module.*
.PHONY:clean
