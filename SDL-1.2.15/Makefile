PLAT := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
#PLAT := /home/wmt/work_licheerv/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.2.4/bin/riscv64-unknown-linux-gnu-

# adb shell 
# getevent
# cat /dev/input/event3
# getevent /dev/input/event3 -t -l -v

# src/video/fbcon/SDL_fbvideo.c
# #define FBCON_DEBUG
# SDL_VIDEO_FBCON_ROTATION=NONE,CW,CCW,UD

# killall -KILL main MainUI
# fbset -g 640 640 640 640 32
# /mnt/SDCARD/graywin1215 -width 640 -height 480

# why use = (0xFF000000 | xxxx) ? 

CC := $(PLAT)gcc 
CPP := $(PLAT)g++
LD := $(PLAT)ld
AR := $(PLAT)ar rcu 
RANLIB := $(PLAT)ranlib
STRIP := $(PLAT)strip
RM := rm -f

CFLAGS += -O2 -g 
CFLAGS += -Wall
#-static
#-Wstrict-prototypes 
CFLAGS += -I./include
CFLAGS += -D_GNU_SOURCE=1 -D_REENTRANT -DHAVE_LINUX_VERSION_H

LDFLAGS += -lpthread

####################

OBJECTS := 

OBJECTS += src/SDL.o
OBJECTS += src/SDL_error.o src/SDL_fatal.o

OBJECTS += src/audio/SDL_audio.o src/audio/SDL_audiocvt.o
OBJECTS += src/audio/SDL_audiodev.o 
OBJECTS += src/audio/SDL_mixer.o 
OBJECTS += src/audio/SDL_mixer_MMX.o src/audio/SDL_mixer_MMX_VC.o
OBJECTS += src/audio/SDL_mixer_m68k.o
OBJECTS += src/audio/SDL_wave.o

OBJECTS += src/cdrom/SDL_cdrom.o

OBJECTS += src/cpuinfo/SDL_cpuinfo.o

OBJECTS += src/events/SDL_active.o
OBJECTS += src/events/SDL_events.o 
OBJECTS += src/events/SDL_expose.o
OBJECTS += src/events/SDL_keyboard.o
OBJECTS += src/events/SDL_mouse.o src/events/SDL_quit.o
OBJECTS += src/events/SDL_resize.o

OBJECTS += src/file/SDL_rwops.o

OBJECTS += src/stdlib/SDL_getenv.o
OBJECTS += src/stdlib/SDL_iconv.o src/stdlib/SDL_malloc.o
OBJECTS += src/stdlib/SDL_qsort.o src/stdlib/SDL_stdlib.o
OBJECTS += src/stdlib/SDL_string.o

OBJECTS += src/thread/SDL_thread.o

OBJECTS += src/timer/SDL_timer.o

OBJECTS += src/video/SDL_RLEaccel.o src/video/SDL_blit.o
OBJECTS += src/video/SDL_blit_0.o src/video/SDL_blit_1.o
OBJECTS += src/video/SDL_blit_A.o src/video/SDL_blit_N.o

OBJECTS += src/video/SDL_bmp.o src/video/SDL_cursor.o 
OBJECTS += src/video/SDL_gamma.o src/video/SDL_pixels.o
OBJECTS += src/video/SDL_stretch.o
OBJECTS += src/video/SDL_surface.o src/video/SDL_video.o
OBJECTS += src/video/SDL_yuv.o 
OBJECTS += src/video/SDL_yuv_mmx.o src/video/SDL_yuv_sw.o

OBJECTS += src/joystick/SDL_joystick.o



####################


OBJECTS += src/video/dummy/SDL_nullevents.o 
OBJECTS += src/video/dummy/SDL_nullmouse.o
OBJECTS += src/video/dummy/SDL_nullmouse.o
OBJECTS += src/video/dummy/SDL_nullvideo.o

OBJECTS += src/audio/disk/SDL_diskaudio.o
OBJECTS += src/audio/dummy/SDL_dummyaudio.o

OBJECTS += src/loadso/dlopen/SDL_sysloadso.o 

OBJECTS += src/audio/dsp/SDL_dspaudio.o 
OBJECTS += src/audio/dma/SDL_dmaaudio.o 

OBJECTS += src/video/fbcon/SDL_fb3dfx.o 
OBJECTS += src/video/fbcon/SDL_fbelo.o 
OBJECTS += src/video/fbcon/SDL_fbevents.o 
OBJECTS += src/video/fbcon/SDL_fbmatrox.o 
OBJECTS += src/video/fbcon/SDL_fbmouse.o 
OBJECTS += src/video/fbcon/SDL_fbriva.o 
OBJECTS += src/video/fbcon/SDL_fbvideo.o 

OBJECTS += src/thread/pthread/SDL_systhread.o
OBJECTS += src/thread/pthread/SDL_syssem.o
OBJECTS += src/thread/pthread/SDL_sysmutex.o
OBJECTS += src/thread/pthread/SDL_syscond.o

OBJECTS += src/joystick/linux/SDL_sysjoystick.o
OBJECTS += src/cdrom/linux/SDL_syscdrom.o
OBJECTS += src/timer/unix/SDL_systimer.o

####################
LIBS := libSDL.a
BIN := graywin1215

all : $(BIN)

$(BIN) : $(LIBS)
	$(CC) $(CFLAGS) -o $@ src/main/dummy/SDL_dummy_main.c test/graywin.c $(LIBS) $(LDFLAGS)
	
libSDL.a : $(OBJECTS)
	$(AR) $@ $(OBJECTS) 
	$(RANLIB) $@
	
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean :
	$(RM) $(OBJECTS) $(BIN) $(LIBS) $(OBJECTS) *.a

