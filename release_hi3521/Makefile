PROJECT_ROOT=..

include $(PROJECT_ROOT)/rules.mk

all: Host

Host: dummy
	$(CD) host; $(SH) build_host

clean:
	$(CD) host; $(SH) clean_host

dummy:
