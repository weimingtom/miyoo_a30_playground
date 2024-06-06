# miyoo_a30_playground
My Miyoo A30 playground

## Cross compile toolchain gcc    
* gcc-linaro-7.5.0-arm-linux-gnueabihf, arm-linux-gnueabihf-gcc  
* **Don't use ubuntu/xubuntu apt install version !!!**, download XK9274/a30-sdk-miyoo releases
* **GET gcc-linaro-7.5.0-arm-linux-gnueabihf.tgz FROM sdk_miyoo282_allwinnerA33.tgz**, running under xubuntu 20.04 64bit     
* https://github.com/XK9274/a30-sdk-miyoo  
* https://github.com/XK9274/a30-sdk-miyoo/releases/tag/16042024

## Not tested gcc  
* NOT tested, maybe works: https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/  
* for test, please use this x86_64 version, same as gcc-linaro-7.5.0-arm-linux-gnueabihf.tgz /lib64/ld-linux-x86-64.so.2 version (?)  
https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz  
* different for 32bit ubuntu (?)  
https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-i686_arm-linux-gnueabihf.tar.xz   

## lv_port_linux_frame_buffer  
* Mod from https://gitee.com/RCSN/lv_port_linux_frame_buffer_mq_d1s  
* search baidupan, lv_port_linux_frame_buffer_a30_v5_fbset640640_and_rotate_yoffset.tar.gz  
* Usage:  
```
> adb push lvgl_demo /tmp
> adb shell
...
# fbset -g 640 640 640 640 32
# killall -KILL main MainUI
# chmod +x /tmp/lvgl_demo
# /tmp/lvgl_demo  
640x640, 32bpp, yoffset=640  
The framebuffer device was mapped to memory successfully.  
```
* see lv_port_linux_frame_buffer/lv_drivers/display/fbdev.c:159, fbdev_flush()   
* I modify fbdev_flush() source to rotate screen for LVGL 7 (high version LVGL may be unnecessary)  
* **TODO**: try to embed c language code to execute fbset -g before running  
* patches:  
https://github.com/weimingtom/miyoo_a30_playground/blob/master/lv_port_linux_frame_buffer/lv_conf.h  
```
#define LV_HOR_RES_MAX          (640)//(480)//(800)
#define LV_VER_RES_MAX          (480)//(640)//(480)//1280)
```
https://github.com/weimingtom/miyoo_a30_playground/blob/master/lv_port_linux_frame_buffer/lv_drivers/display/fbdev.c  
```
//rotate and flip
//exchange x and y, and flip x
	int32_t x;
	uint32_t *color32 = (uint32_t *)color_p;
	for(y = act_y1; y <= act_y2; ++y) {
	    for (x = act_x1; x <= act_x2; ++x) {
if (y < 0 || y >= vinfo.xres) continue;
if ((vinfo.yres - x - 1) < 0 || (vinfo.yres - x - 1) >= vinfo.yres) continue;

if (x - act_x1 < 0 || x - act_x1 >= (act_x2 - act_x1 + 1)) continue;
if ((y - act_y1) < 0 || (y - act_y1) >= (act_y2 - act_y1 + 1)) continue;

            fbp32[(vinfo.yres - x - 1 + vinfo.yoffset) * vinfo.xres + y] =  
				color32[(act_x2 - act_x1 + 1) * (y - act_y1) + (x - act_x1)]; 
	    }
    }
```

## sdltest for steward-fu/sdl static libsdl.a lib, need libEGL.so and libGLESv2.so (actually libMali.so), my sdl build no sound (?)      
* main.c from src_sdltest.7z of https://github.com/steward-fu/archives/releases?q=miyoo&expanded=true  
* graywin.c from libsdl-1 test code    
* sdl-main.zip from https://github.com/steward-fu/sdl
* configure command like this: (need uncompress staging_dir.tgz from XK9274/a30-sdk-miyoo releases)    
CFLAGS=-I/home/wmt/work_a30/staging_dir/target/usr/include LDFLAGS=-L/home/wmt/work_a30/staging_dir/target/usr/lib PATH=/home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/:$PATH ./configure --prefix=/home/wmt/work_a30/sdl --host=arm-linux-gnueabihf --disable-pulseaudio --enable-video-a30   
* sdl-main patch see sdltest/sdl-main.tar.gz  
```
//src/joystick/a30/SDL_a30_joystick.c:549
        static int xx = 320 / 2;
        static int yy = 240 / 2;
//src/video/a30/SDL_a30_video.c:71, '.rgb' -> '.bgr'
    "    if (s_alpha >= 2.0) {                                 \n"
    "        gl_FragColor = texture2D(s_texture, v_texCoord).bgra;  \n" //ori none
    "    }                                                     \n"
    "    else if (s_alpha > 0.0) {                             \n"
    "        vec3 tex = texture2D(s_texture, v_texCoord).bgr;  \n" //ori .rgb
    "        gl_FragColor = vec4(tex, s_alpha);                \n"
    "    }                                                     \n"
    "    else {                                                \n"
    "        vec3 tex = texture2D(s_texture, v_texCoord).bgr;  \n" //ori .rgb
    "        gl_FragColor = vec4(tex, 1.0);                    \n"
    "    }                                                     \n"
```
* Usage:  
```
> adb push graywin /mnt/SDCARD/
> adb push sdltest /mnt/SDCARD/
> adb shell
...
# /mnt/SDCARD/graywin
# /mnt/SDCARD/sdltest
```

## TODO  
* (done)  
