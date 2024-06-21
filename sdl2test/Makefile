CC := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc

CFLAGS := 
CFLAGS += -L/home/wmt/work_a30/staging_dir/target/usr/lib 
CFLAGS += -I/home/wmt/work_a30/staging_dir/target/usr/include

#-ggdb 
LDFLAGS := -O0 -g3
#LDFLAGS += -lSDL -lpthread -lm -ldl -lEGL -lGLESv2
LDFLAGS += -lSDL2 -lpthread -ldl

all:
	$(CC) testdraw2.c -o testdraw2 $(LDFLAGS) $(CFLAGS) 
#gcc -o testdraw2 testdraw2.c -lSDL2
# -lasound 

#-I/home/wmt/work_q90/arm-buildroot-linux-musleabi_sdk-buildroot/arm-buildroot-linux-musleabi/sysroot/usr/include/SDL 
#-L/opt/miyoo/arm-miyoo-linux-uclibcgnueabi/sysroot/usr/lib

clean:
	rm -rf testdraw2 *.o *.exe


