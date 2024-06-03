# miyoo_a30_playground
My Miyoo A30 playground

## Cross compile toolchain gcc    
* gcc-linaro-7.5.0-arm-linux-gnueabihf, arm-linux-gnueabihf-gcc  
* **Don't use ubuntu/xubuntu apt install version !!!**, download XK9274/a30-sdk-miyoo releases     
* https://github.com/XK9274/a30-sdk-miyoo  
* https://github.com/XK9274/a30-sdk-miyoo/releases/tag/16042024  

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

## TODO  
* (done)  
