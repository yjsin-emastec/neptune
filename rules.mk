EA_ID             = 101901
EA_VENDOR         = EASTERN
EA_MODEL          = 1
EA_SUB_MODEL      = 0
EA_OEM            = 0
EA_SUB_OEM        = 0
EA_REGION         = 0
EA_MODEL_NAME     = EMD-S10
GUI_TYPE          = QT_BASE
EA_REF_YEAR       = 2016
CODEC_CHIP        = HI3521

EA_1ST_IFNAME     = eth0
EA_2ND_IFNAME     = eth1

#-----------------------------------------------------------
# SYSTEM TYPE (DVR:0)
#-----------------------------------------------------------
SYS_TYPE          = 0

ifeq ($(EA_MODEL), 0)
ARCH              = arm
CODEC_CHIP        = HI3521
endif

ifeq ($(EA_MODEL), 1)
ARCH              = arm
CODEC_CHIP        = HI3521
endif

#-----------------------------------------------------------
# Definition of Cross Compiler
#-----------------------------------------------------------
#ifeq ($(ARCH),arm)
CROSS             = arm-hisiv100nptl-linux-
#endif
CC                = $(CROSS)gcc
AR                = $(CROSS)ar
ARFLAGS           = rcv
RANLIB            = $(CROSS)ranlib
STRIP             = $(CROSS)strip
LIBDIR            = lib
OEM               = oem
EA_LOGO           = btlogo-$(EA_OEM).$(EA_SUB_OEM).$(EA_REGION).img

CD                = cd
MV                = mv
SH                = sh
RM                = rm
RMF               = rm -f
RMRF              = rm -rf
CP                = cp
CPARF             = cp -arf
LS                = ls -alh
TARXC             = tar -x -C
TARZXVF           = tar zxvf
TMP               = tmp
NFS               = /nfs
GIT               = git archive HEAD
ECHO              = echo
RMDIR             = rmdir
MKDIR             = mkdir -p
CHMOD644          = chmod 644
CHMOD755          = chmod 755
CHMOD755R         = chmod 755 -R

#-----------------------------------------------------------
# Definition of SDK 
#-----------------------------------------------------------
ifeq ($(CODEC_CHIP), HI3521)
CHIP_ARCH        ?=hi352x
HISDK             = SDK_3521_V1_0_6_2
HICHIP            = 0x35210100
HIDBG             = HI_DEBUG
endif

ifeq ($(HISDK),SDK_3521_V1_0_6_2)
SDK_PATH          = sdk_3521_v1.0.6.2
endif

#-----------------------------------------------------------
# Cross Compiler Options
#-----------------------------------------------------------
CFLAGS           := -g -O2 -Wl,-Map=a.map -Wall -fpic -D_GNU_SOURCE -DFS64 -DLINUX -D$(CHIP_ARCH) -D$(HISDK)
CFLAGS           += -DNAUNIFIED_APPLY
CFLAGS           += -DREMOTE_PB_DSOCK_UDP
CFLAGS           += -DSCREEN_USE_BMP
CFLAGS           += -DEA_REGION=$(EA_REGION)
CFLAGS           += -DOEM=$(EA_OEM)
CFLAGS           += -DSUB_MODEL=$(EA_SUB_MODEL)
CFLAGS           += -DSUB_OEM=$(EA_SUB_OEM)
CFLAGS           += -DMODEL=$(EA_MODEL)
CFLAGS           += -DSYS_TYPE=$(SYS_TYPE)

ifeq ($(GUI_TYPE),QT_BASE)
CFLAGS           += -DQT_BASE
endif

CORELIBDIR        = arm-hisiv100
