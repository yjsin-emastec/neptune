PROJECT_ROOT=..

include $(PROJECT_ROOT)/rules.mk

all: Mkrootfs

Mkrootfs: dummy
	$(CD) mkrootfs; $(SH) build_rootfs

clean:
	$(CD) mkrootfs; $(SH) clean_rootfs

dummy:
