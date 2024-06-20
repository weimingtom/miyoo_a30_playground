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

## flipClock from https://github.com/JaeSeoKim/sdl-flip-clock  
* rotate -90 degree (270 degree) with SDL_RenderCopyEx
* also see https://github.com/steward-fu/website/releases/download/miyoo-a30/src_app_flipclock-v1.1.zip  
* src/render.c:  
```
int RenderPresent(SDL_Renderer *renderer, SDL_Window *window) {
#if defined SDL && SDL == 1
  return SDL_BlitSurface(renderer, NULL, window, NULL);
#else

#if 1
//see https://wiki.libsdl.org/SDL2/CategoryAPI
//see https://github.com/EXL/P2kElfs/blob/master/Yeti3D-Old/main_sdl2.c
SDL_UpdateTexture(_G.texture, NULL, _G.video->pixels, _G.video->pitch);
SDL_Rect rect = {0};
rect.x = (480 - 640) / 2; //-80;
rect.y = (640 - 480) / 2; //80;
rect.w = 640 * 1;
rect.h = 480 * 1;
SDL_Point p = {0};
p.x = 640 / 2;//320;
p.y = 480 / 2;//240;
SDL_RenderCopyEx(renderer, _G.texture, NULL, &rect, 270, &p, SDL_FLIP_NONE);
SDL_RenderPresent(renderer);
return 0;
#else

  SDL_RenderPresent(renderer);
  return 0;
#endif
#endif
}
```
```
int RenderFillRect(SDL_Renderer *dst, SDL_Rect *rect, Uint32 color) {
#if defined SDL && SDL == 1
  return SDL_FillRect(dst, rect, color);
#else

#if 1
SDL_FillRect(_G.video, rect, color);
#endif

  SDL_SetRenderDrawColor(dst, color >> 16 & 255, color >> 8 & 255, color & 255,
                         color >> 24 & 255);
  return SDL_RenderFillRect(dst, rect);
#endif
}
```
```
int RenderClear(SDL_Renderer *dst, Uint32 color) {
#if defined SDL && SDL == 1
  return RenderFillRect(dst, NULL, color);
#else

#if 1
return SDL_FillRect(_G.video, NULL, color);
#else

  SDL_SetRenderDrawColor(dst, color >> 16 & 255, color >> 8 & 255, color & 255,
                         color >> 24 & 255);
  return SDL_RenderClear(dst);
#endif

#endif
}
```
```

int BlitSurface(SDL_Surface *src, SDL_Rect *srcrect, SDL_Renderer *dst,
                SDL_Rect *dstrect) {
#if defined SDL && SDL == 1
  return SDL_BlitSurface(src, srcrect, dst, dstrect);
#else

#if 1
int ret = SDL_BlitSurface(src, srcrect, _G.video, dstrect);
return ret;
#else
  SDL_Texture *mTexture = SDL_CreateTextureFromSurface(dst, src);
  if (mTexture == NULL) {
    return -1;
  }
  int ret = SDL_RenderCopy(dst, mTexture, NULL, dstrect);
  SDL_DestroyTexture(mTexture);
  return ret;
#endif

#endif
};
```
* src/init.c:  
```
_G.video = SDL_CreateRGBSurface(0, 640, 480, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
_G.texture = SDL_CreateTexture(_G.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
```
* https://wiki.libsdl.org/SDL2/CategoryAPI  
* https://github.com/EXL/P2kElfs/blob/master/Yeti3D-Old/main_sdl2.c  
* flipclock, /mnt/SDCARD/App/flipclock    
* https://github.com/JaeSeoKim/sdl-flip-clock  
* Study in weibo  
```
不知道SDL_RenderCopyEx的原理是什么，反正好像是可以任意旋转角度，难道是软件实现仿射的吗？
如果这样就有点SDL1代码中影子缓冲的感觉，其实就是软件实现旋转，牺牲一下性能，
不过SDL1的shadow buffer比较麻烦，它是每次产生局部刷新的时候都要仿射一下，
不是说整个屏幕旋转一次
```
```
我初步猜测是这样，可能miyoo a30的SDL2程序是通过SDL_RenderCopyEx来旋转，
证据是我比较过我用JaeSeoKim/sdl-flip-clock编译出来的文件和原版掌机上的elf文件，
发现好像改变了这个API名称入口。如图右侧是原版横屏正常版本，
使用SDL_RenderCopyEx旋转回去，当然这只是猜测，以后找时间试验
```
```
我想换一种思路去解决SDL_RenderCopyEx旋转90度问题，根据上次的截图，
其实原版的flipClock还多用了这几个API：
SDL_UpdateTexture，SDL_CreateTexture，SDL_UpperBlit（即SDL_BlitSurface）。
SDL_CreateTexture和SDL_BlitSurface应该可以实现类似SDL1影子缓冲的效果
（只需要旋转一次），但目前还没有试验和头绪（最好能找到类似的代码）
```

## TODO  
* Copy sdl-flip-clock sdl2 include and lib stage files  
* (done)  
