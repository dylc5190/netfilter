MOD := nfhook
obj-m += $(MOD).o
KVERSION := $(shell uname -r)

all:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

install:
	/sbin/insmod $(MOD).ko

remove:
	/sbin/rmmod $(MOD).ko

