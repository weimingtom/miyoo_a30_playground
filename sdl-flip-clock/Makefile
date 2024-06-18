TARGET=flipClock
VERSION=1.1
#CROSS_COMPILE=/home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
MIYOOMINI=1

CC=$(CROSS_COMPILE)gcc
# CFLAGS+=-I$(INC_DIR) -Werror
CFLAGS+=-I$(INC_DIR)

ifeq ($(MIYOOMINI),1)
#CFLAGS+=-DSDL=1
#LDLIBS=-DSDL=1 -lSDL -lpthread -lSDL_ttf
LDLIBS=-lSDL2 -lpthread -lSDL2_ttf -lfreetype -lbz2 -lz
else
LDLIBS=-lSDL2 -lpthread -lSDL2_ttf
endif

ifeq ($(MIYOOMINI),1)
#CROSS_COMPILE?=~/buildroot/output/host/bin/arm-linux-gnueabihf-
CROSS_COMPILE?=/home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
#SYSROOT	?= $(shell ${CC} --print-sysroot)
SYSROOT?=/home/wmt/work_a30/staging_dir/target
ARCH=-marm -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard 
#-march=armv7ve+simd
CFLAGS+=-Os $(ARCH) -I${SYSROOT}/usr/include -ffunction-sections -fdata-sections -Wall
LDFLAGS+=-I${SYSROOT}/usr/lib -L${SYSROOT}/usr/lib $(ARCH) -Bstatic,-lutil,-Bdynamic
endif

RM=rm
RMFLAGS=-rf

MKDIR=mkdir
MKDIRFLAGS=-p

OUTPUT_DIR=build
INC_DIR=include
SRC_DIR=src
OBJ_DIR=objs

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(TARGET)

re: clean all

clean:
	$(RM) $(RMFLAGS) $(OBJS) $(TARGET) FlipClock-v$(VERSION).zip

$(TARGET): ${OBJS}
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MKDIR) $(MKDIRFLAGS) $(OBJ_DIR)

pack: FlipClock-v$(VERSION).zip

FlipClock-v$(VERSION).zip: $(TARGET)
	zip -r FlipClock-v$(VERSION).zip fonts flipClock icon config.json launch.sh


.PHONY: all clean re
