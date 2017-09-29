PROJECT_ROOT=../..

include $(PROJECT_ROOT)/rules.mk

INC_DIR     = -I./inc
CFLAGS      = -D_FILE_OFFSET_BITS=64 -O2 -g -Wall -Wextra -Wwrite-strings
CFLAGS     += -Wno-sign-compare -ffunction-sections -fdata-sections

LDFLAGS     = -L$(PROJECT_ROOT)/$(LIBDIR) -lm

TARGET      = libnmea.so

SRCS        = src/context.c       \
              src/generate.c      \
              src/generator.c     \
              src/gmath.c         \
              src/info.c          \
              src/parse.c         \
              src/parser.c        \
              src/sentence.c      \
              src/time.c          \
              src/tok.c           \

all : host

host : $(SRCS)
	$(CC) -shared -o $(TARGET) $(INC_DIR) $(CFLAGS) $(LDFLAGS) $(SRCS)
	$(STRIP) $(TARGET)
	$(CHMOD644) $(TARGET)
	$(CPARF) $(TARGET) $(PROJECT_ROOT)/$(LIBDIR)

clean:
	$(RMF) $(TARGET) *.o
