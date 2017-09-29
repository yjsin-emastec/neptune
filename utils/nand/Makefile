PROJECT_ROOT=../..

include $(PROJECT_ROOT)/rules.mk

INC_DIR         = -I./inc
CFLAGS          = -D_FILE_OFFSET_BITS=64 -O2 -g -Wall -Wextra -Wwrite-strings
CFLAGS         += -Wno-sign-compare -ffunction-sections -fdata-sections
#CFLAGS         += -Wl,--gc-sections

LDFLAGS         = -L$(PROJECT_ROOT)/$(LIBDIR) -lglib-2.0 -lgthread-2.0 -lpthread -lm

TARGET          = libnand.so

SRCS            = src/libmtd.c           \
                  src/libmtd_legacy.c    \
                  src/libcrc32.c         \
                  src/libfec.c           \
                  src/nand_erase.c       \
                  src/nand_write.c       \
                  src/nand_read.c        \

EXPORT_HEADERS  = inc/nand.h

all : host

host : $(SRCS)
	$(CC) -shared -o $(TARGET) $(INC_DIR) $(CFLAGS) $(LDFLAGS) $(SRCS)
	$(STRIP) $(TARGET)
	$(CHMOD644) $(TARGET)
	$(CP) $(EXPORT_HEADERS) $(PROJECT_ROOT)/include/utils
	$(CPARF) $(TARGET) $(PROJECT_ROOT)/$(LIBDIR)

clean:
	$(RMF) $(TARGET) *.o
