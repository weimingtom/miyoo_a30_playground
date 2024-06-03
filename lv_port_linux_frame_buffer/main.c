#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_examples/lv_examples.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "generated/gui_guider.h"
#include "generated/events_init.h"
#include "custom/custom.h"
#define DISP_BUF_SIZE (80 * LV_HOR_RES_MAX)
lv_ui guider_ui;
int main(void)
{
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_buf_t disp_buf;
    lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);



    /*Initialize and register a display driver*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer   = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
#if 0
disp_drv.rotated=1;
#endif
    lv_disp_drv_register(&disp_drv);

    evdev_init();

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);     
    indev_drv.type =LV_INDEV_TYPE_POINTER;               
    indev_drv.read_cb =evdev_read;             
    lv_indev_t *indev_mouse = lv_indev_drv_register(&indev_drv);

//-------------------
    /*Set cursor. For simplicity set a HOME symbol now.*/
    lv_obj_t * mouse_cursor = lv_img_create(lv_disp_get_scr_act(NULL), NULL);
    lv_img_set_src(mouse_cursor, LV_SYMBOL_GPS);//LV_SYMBOL_HOME);
    lv_indev_set_cursor(indev_mouse, mouse_cursor);
//-------------------


    /*Create a GUI-Guider app */
	setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);
    /*Create a Demo*/
    lv_demo_widgets();
 //   lv_demo_benchmark();
    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_task_handler();
        usleep(5000);
    }

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
