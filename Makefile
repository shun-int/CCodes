obj-m += drv.o
# Specify kernel source dir
#KDIR := /home/usr-name/linux/
# test ubuntu linux dev dir
KDIR :=/lib/modules/$(shell uname -r)/build
PWD ?= $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	rm -f *.o *.mod *.mod.c *.order *.symvers .*.cmd
clean:
	rm -f *.o *.mod.c .*.*.cmd *.ko