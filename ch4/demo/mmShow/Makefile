#
obj-m :=  mm_show.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/kernels/$(LINUX_KERNEL)

all:
	echo "CURRENT_PATH:$(CURRENT_PATH)"
	echo "LINUX_KERNEL:$(LINUX_KERNEL)"
	echo "LINUX_KERNEL_PATH:$(LINUX_KERNEL_PATH)"
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean


