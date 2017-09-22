PROJECT_ROOT=..

include rules.mk

TAG_ALL     = Mklink Version Gui
TAG_INSTALL = ExportRelease2Tmp SetModelDep CopyUserlib2Tmp

all: $(TAG_ALL)

Mklink:
	@$(CD) $(LIBDIR); $(SH) script/mklink.sh

Version: dummy
	@$(SH) script/version.sh "0.0.9"

Gui: dummy
	@$(ECHO)  "QT MainWidget"
	@$(CD)    gui/mainwidget; $(SH) build.sh
	@$(CPARF) gui/mainwidget/mainwidget $(LIBDIR)
	@$(MKDIR) $(NFS)/usr/lib/translator
	@$(CPARF) gui/mainwidget/mainwidget                                   $(NFS)/usr/lib
	@$(CPARF) gui/mainwidget/qss/*.qss                                    $(NFS)/usr/lib
	@$(CPARF) gui/mainwidget/src/dvrsetup/system/language/translator/*.qm $(NFS)/usr/lib/translator
ifeq (exist,$(shell [ -e $(TMP) ] && echo exist))
	@$(CPARF) gui/mainwidget/qss/*.qss                                    $(TMP)/host/rootfs/usr/lib
	@$(CPARF) gui/mainwidget/src/dvrsetup/system/language/translator/*.qm $(TMP)/host/rootfs/usr/lib/translator
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
	@$(ECHO) "QT BASE COPY!!!!!"
	@$(CPARF) gui/mainwidget/src/dvrsetup/system/language/translator/*.qm   $(TMP)/host/rootfs/usr/lib/translator
	@$(CPARF) gui/mainwidget/qss/*.qss                                      $(TMP)/host/rootfs/usr/lib
	@$(CD) $(LIBDIR); $(SH) script/export2usrlib.sh         $(PROJECT_ROOT)/$(TMP)/host/rootfs/usr/lib
	@$(CD) $(LIBDIR); $(SH) script/export2host.sh           $(PROJECT_ROOT)/$(TMP)/host/rootfs/usr/lib
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
