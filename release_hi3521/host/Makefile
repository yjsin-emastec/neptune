PROJECT_ROOT=../..

include $(PROJECT_ROOT)/rules.mk

all: Extract

Extract: dummy
	$(TARZXVF) rootfs.tar.gz

clean:
	$(RMRF) rootfs

dummy:
