TARGET = gutest
OBJS = main.o

BUILD_PRX = 1
PSP_FW_VERSION = 500

INCDIR = 
CFLAGS = -g3 -Wall -D__PSP__
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS =
LIBS = -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = $(TARGET)

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
