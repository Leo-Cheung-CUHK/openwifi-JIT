# KVERS = $(shell uname -r)
# obj-m += misc.o

# build:miscdev_modules

# miscdev_modules:
# 	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules
# clean:
# 	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
obj-m += misc.o

all:
	make -C $(KDIR) M=$(PWD) modules
	# ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.order
