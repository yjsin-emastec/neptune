PROJECT_ROOT=..

include rules.mk

TAG_ALL     = Mklink Version Gui
TAG_INSTALL	= ExportRelease2Tmp SetModelDep CopyUserlib2Tmp

all: $(TAG_ALL)

Mklink:
	$(CD) $(LIBDIR); $(SH) script/mklink.sh

Version: dummy
	@$(SH) script/version.sh "0.0.6"

Gui: dummy
	$(ECHO)  "QT MainWidget"
	$(CD)    gui/mainwidget; $(SH) build.sh
	$(CPARF) gui/mainwidget/mainwidget lib

Install: $(TAG_INSTALL)

Reinstall: DelTmp Install Mkimg

DelTmp:
	$(RMRF) tmp

ExportRelease2Tmp: dummy
	@$(MKDIR) tmp
	@$(GIT)   release_hi3521 | $(TARXC) tmp
	@$(MV)    tmp/release_hi3521/* tmp
	@$(RMDIR) tmp/release_hi3521

SetModelDep: dummy
	$(ECHO) $(MODEL_NAME)    > tmp/host/MODEL
	$(ECHO) $(EA_MODEL)      > tmp/host/rootfs/etc/MODEL_NUM
	$(ECHO) $(EA_SUB_MODEL)  > tmp/host/rootfs/etc/SUB_MODEL
	$(ECHO) $(EA_OEM)        > tmp/host/rootfs/etc/OEM_NUM
	$(ECHO) $(EA_REGION)     > tmp/host/rootfs/etc/REGION
	$(ECHO) $(EA_SUB_OEM)    > tmp/host/rootfs/etc/SUB_OEM
	$(ECHO) $(EA_1ST_IFNAME) > tmp/host/rootfs/etc/ifname1.conf
	$(ECHO) $(EA_2ND_IFNAME) > tmp/host/rootfs/etc/ifname2.conf

CopyUserlib2Tmp: dummy
	$(CD) $(LIBDIR); $(SH) script/export2usrlib.sh    $(PROJECT_ROOT)/tmp/host/rootfs/usr/lib
	$(ECHO) "QT BASE COPY!!!!!"
	$(CD) $(LIBDIR); $(SH) script/export2host.sh      $(PROJECT_ROOT)/tmp/host/rootfs/usr/lib
	$(CHMOD755R) tmp/host/rootfs/usr/sbin
	$(CHMOD755R) tmp/host/rootfs/usr/drv
	$(CHMOD755R) tmp/host/rootfs/usr/lib

Mkimg: dummy
	$(CD) tmp; $(MAKE)

clean:
	$(MAKE) -C gui/mainwidget   clean
	$(RMF)  gui/mainwidget/Makefile gui/mainwidget/mainwidget gui/mainwidget/mainwidget.pro;
	$(RMF)  *.txt
	$(RMF)  *.bin
	$(CD)   $(LIBDIR); $(SH) script/delink.sh
	$(CD)   $(LIBDIR); $(SH) script/delusrlib.sh
	$(RMRF) tmp
	$(RMRF) rules.mk

dummy:
