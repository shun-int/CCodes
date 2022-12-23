# modify the name of .o
obj-m += chrdev.o

# Specify kernel source dir arch=arm64
KDIR := /lib/modules/$(shell uname -r)/build

# ubuntu insmod err have to add    arch=arm64
CONFIG_MODULE_SIG=n

PWD ?= $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	rm -f *.o *.mod *.mod.c *.order *.symvers .*.cmd
clean:
	rm -f *.o *.mod.c .*.*.cmd *.ko