#
# Makefile
#

#(not good) use xubuntu20: sudo apt install gcc-arm-linux-gnueabihf
CC := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
PRJ_DIR  :=  ${shell pwd}
CFLAGS ?= -O3 -g0 -I$(LVGL_DIR) -Wall -Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wundef -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wno-switch-enum -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wstack-usage=1024 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wswitch-enum -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare
#LDFLAGS ?= -lSDL2 -lm
BIN = lvgl_demo

DIR_OBJS = $(LVGL_DIR)/obj
DIR_EXEC = $(LVGL_DIR)/exec

#获取源文件路径下的所有.o文件名
# GCC_SOURCE_PATH = $(foreach dir,$(LVGL_DIR),$(wildcard $(dir)/*.c))
# GCC_OBJ_PATH = $(patsubst %.c,$(DIR_OBJS)/%.o, $(notdir $(GCC_SOURCE_PATH)))


#Collect the files to compile
MAINSRC = ./main.c

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/lv_examples/lv_examples.mk
include $(LVGL_DIR)/generated/generated.mk
include $(LVGL_DIR)/custom/custom.mk

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))
GENOBJ  = $(GEN_CSRCS:.c=$(OBJEXT))


SRCS = $(ASRCS) $(CSRCS) $(MAINSRC) $(GEN_CSRCS)
OBJS = $(AOBJS) $(COBJS)


## MAINOBJ -> OBJFILES

all: default

%.o: %.c
#将生成的.o文件放到O_PATH目录下
# 	$(DIR_OBJS)/%.o: $(LVGL_DIR)/%.c
#	@$(cc) -c $(CFLAGS) $< -o $@
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "CC $<"

default: $(AOBJS) $(COBJS) $(MAINOBJ) $(GENOBJ)
	$(CC) -o $(BIN) $(MAINOBJ) $(GENOBJ) $(AOBJS) $(COBJS) $(LDFLAGS) 

clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ) $(GENOBJ)

