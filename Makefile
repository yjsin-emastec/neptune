PROJECT_ROOT=..

include rules.mk

TAG_ALL     = Mklink Version Gui
TAG_INSTALL	= ExportRelease2Tmp SetModelDep CopyUserlib2Tmp

all: $(TAG_ALL)

Mklink:
	@$(CD) $(LIBDIR); $(SH) script/mklink.sh

Version: dummy
	@$(SH) script/version.sh "0.0.6"

Gui: dummy
	@$(ECHO)  "QT MainWidget"
	@$(CD)    gui/mainwidget; $(SH) build.sh
	@$(CPARF) gui/mainwidget/mainwidget $(LIBDIR)
ifeq (exist,$(shell [ -e $(TMP) ] && echo exist))
	@$(CPARF) gui/mainwidget/src/dvrsetup/system/language/translator $(TMP)/host/rootfs/usr/local/Trolltech
endif

Install: $(TAG_INSTALL)

Reinstall: DelTmp Install Mkimg

DelTmp:
	@$(RMRF) $(TMP)

ExportRelease2Tmp: dummy
	@$(MKDIR) $(TMP)
	@$(GIT)   release_hi3521 | $(TARXC) $(TMP)
	@$(MV)    $(TMP)/release_hi3521/* $(TMP)
	@$(RMDIR) $(TMP)/release_hi3521

SetModelDep: dummy
	@$(ECHO) $(MODEL_NAME)    > $(TMP)/host/MODEL
	@$(ECHO) $(EA_MODEL)      > $(TMP)/host/rootfs/etc/MODEL_NUM
	@$(ECHO) $(EA_SUB_MODEL)  > $(TMP)/host/rootfs/etc/SUB_MODEL
	@$(ECHO) $(EA_OEM)        > $(TMP)/host/rootfs/etc/OEM_NUM
	@$(ECHO) $(EA_REGION)     > $(TMP)/host/rootfs/etc/REGION
	@$(ECHO) $(EA_SUB_OEM)    > $(TMP)/host/rootfs/etc/SUB_OEM
	@$(ECHO) $(EA_1ST_IFNAME) > $(TMP)/host/rootfs/etc/ifname1.conf
	@$(ECHO) $(EA_2ND_IFNAME) > $(TMP)/host/rootfs/etc/ifname2.conf

CopyUserlib2Tmp: dummy
	@$(CPARF) gui/mainwidget/src/dvrsetup/system/language/translator   $(TMP)/host/rootfs/usr/local/Trolltech
	@$(CD) $(LIBDIR); $(SH) script/export2usrlib.sh    $(PROJECT_ROOT)/$(TMP)/host/rootfs/usr/lib
	@$(ECHO) "QT BASE COPY!!!!!"
	@$(CD) $(LIBDIR); $(SH) script/export2host.sh      $(PROJECT_ROOT)/$(TMP)/host/rootfs/usr/lib
	@$(CHMOD755R) $(TMP)/host/rootfs/usr/sbin
	@$(CHMOD755R) $(TMP)/host/rootfs/usr/drv
	@$(CHMOD755R) $(TMP)/host/rootfs/usr/lib

Mkimg: dummy
	@$(CD) $(TMP); $(MAKE)

clean:
	@$(MAKE) -C gui/mainwidget   clean
	@$(RMF)  include/eaVersion.h
	@$(RMF)  gui/mainwidget/Makefile gui/mainwidget/mainwidget gui/mainwidget/mainwidget.pro;
	@$(RMF)  *.txt
	@$(RMF)  *.bin
	@$(CD)   $(LIBDIR); $(SH) script/delink.sh
	@$(CD)   $(LIBDIR); $(SH) script/delusrlib.sh
	@$(RMRF) $(TMP)
	@$(RMRF) rules.mk

dummy:
