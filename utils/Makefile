PROJECT_ROOT=..

include $(PROJECT_ROOT)/rules.mk

INC_DIR         = -I$(PROJECT_ROOT)/include -I./inc -I./nand/inc
CFLAGS         += -DLINUX -D_FILE_OFFSET_BITS=64 -O2 -g -Wall -Wextra -Wwrite-strings -fno-strict-aliasing
CFLAGS         += -Wno-sign-compare -ffunction-sections -fdata-sections
LDFLAGS         = -L$(PROJECT_ROOT)/$(LIBDIR) -L$(PROJECT_ROOT)/$(LIBDIR)/$(CORELIBDIR) -lpthread -lglib-2.0 -lgthread-2.0 -lpthread -lm -lhimem

TARGET          = libutils.so

SRCS            = src/net.c                   \
                  src/sysid.c                 \
                  src/cfg.c                   \
                  src/util.c                  \
                  src/upgrade.c               \
                  src/app_upgrade.c           \
                  src/crc.c                   \
                  src/model.c                 \
                  src/live.c                  \
                  nand/src/libmtd.c           \
                  nand/src/libmtd_legacy.c    \
                  nand/src/libcrc32.c         \
                  nand/src/libfec.c           \
                  nand/src/nand_erase.c       \
                  nand/src/nand_write.c       \
                  nand/src/nand_read.c        \

EXPORT_HEADERS  = inc/utils.h

all : host Nmea

host : $(SRCS)
	$(CC) -shared -o $(TARGET) $(INC_DIR) $(LDFLAGS) $(CFLAG) $(CFLAGS) $(SRCS)
	$(STRIP) $(TARGET)
	$(CHMOD644) $(TARGET)
	$(CP) $(EXPORT_HEADERS) $(PROJECT_ROOT)/include/utils
	$(CPARF) $(TARGET) $(PROJECT_ROOT)/$(LIBDIR)

Nmea:
	$(MAKE) -C nmea

clean:
	$(RMF) $(TARGET) *.o a.map inc/model_util.h
	$(MAKE) -C nmea clean
