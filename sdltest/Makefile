#

#
# patches for https://github.com/steward-fu/sdl
# src/joystick/a30/SDL_a30_joystick.c:549
#        static int xx = 320 / 2;
#        static int yy = 240 / 2;
# src/video/a30/SDL_a30_video.c:71, '.rgb' -> '.bgr'
#    "    if (s_alpha >= 2.0) {                                 \n"
#    "        gl_FragColor = texture2D(s_texture, v_texCoord).bgra;  \n" //ori none
#    "    }                                                     \n"
#    "    else if (s_alpha > 0.0) {                             \n"
#    "        vec3 tex = texture2D(s_texture, v_texCoord).bgr;  \n" //ori .rgb
#    "        gl_FragColor = vec4(tex, s_alpha);                \n"
#    "    }                                                     \n"
#    "    else {                                                \n"
#    "        vec3 tex = texture2D(s_texture, v_texCoord).bgr;  \n" //ori .rgb
#    "        gl_FragColor = vec4(tex, 1.0);                    \n"
#    "    }                                                     \n"
#

# how to build https://github.com/steward-fu/sdl
# wmt@wmt-VirtualBox:~/work_a30/sdl-main$ 
# CFLAGS=-I/home/wmt/work_a30/staging_dir/target/usr/include LDFLAGS=-L/home/wmt/work_a30/staging_dir/target/usr/lib PATH=/home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/:$PATH ./configure --prefix=/home/wmt/work_a30/sdl --host=arm-linux-gnueabihf --disable-pulseaudio --enable-video-a30 
# PATH=/home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/:$PATH make clean all install
# (do not use -j4)

#
# not used global env:
# (not need) SDL_NOMOUSE=0
# (not need, embed in libSDL.a static lib) SDL_VIDEODRIVER=a30
# (not need, static lib) LD_LIBRARY_PATH=/tmp
#

CC := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc

CFLAGS := -L./sdl/lib
CFLAGS += -I./sdl/include
CFLAGS += -I./sdl/include/SDL
CFLAGS += -L./staging_dir/target/usr/lib

#CFLAGS += -L/home/wmt/work_a30/staging_dir/target/usr/lib 
#CFLAGS += -I/home/wmt/work_a30/staging_dir/target/usr/include
#CFLAGS += -I/home/wmt/work_a30/staging_dir/target/usr/include/SDL

#-ggdb 
LDFLAGS := -O0 -g3
#LDFLAGS += -lSDL -lpthread -lm -ldl -lEGL -lGLESv2
LDFLAGS += -lSDL -lpthread -ldl -lGLESv2

all:
	$(CC) main.c -o sdltest $(LDFLAGS) $(CFLAGS) 
	$(CC) graywin.c -o graywin $(LDFLAGS) $(CFLAGS)

# -lasound 

#-I/home/wmt/work_q90/arm-buildroot-linux-musleabi_sdk-buildroot/arm-buildroot-linux-musleabi/sysroot/usr/include/SDL 
#-L/opt/miyoo/arm-miyoo-linux-uclibcgnueabi/sysroot/usr/lib

clean:
	rm -rf sdltest graywin *.o *.exe


