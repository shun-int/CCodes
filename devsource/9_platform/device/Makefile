# modify the name of .o
obj-m += p_dev.o

# Specify kernel source dir arch=arm64
KDIR := /lib/modules/$(shell uname -r)/build
# ubuntu insmod err have to add
CONFIG_MODULE_SIG=n

PWD ?= $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	rm -f *.o *.mod *.mod.c *.order *.symvers .*.cmd
clean:
	rm -f *.o *.mod.c .*.*.cmd *.ko