/**
 * @file fbdev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "fbdev.h"
#if USE_FBDEV || USE_BSD_FBDEV

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#if USE_BSD_FBDEV
#include <sys/fcntl.h>
#include <sys/time.h>
#include <sys/consio.h>
#include <sys/fbio.h>
#else  /* USE_BSD_FBDEV */
#include <linux/fb.h>
#endif /* USE_BSD_FBDEV */

/*********************
 *      DEFINES
 *********************/
#ifndef FBDEV_PATH
#define FBDEV_PATH  "/dev/fb0"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      STRUCTURES
 **********************/

struct bsd_fb_var_info{
    uint32_t xoffset;
    uint32_t yoffset;
    uint32_t xres;
    uint32_t yres;
    int bits_per_pixel;
 };

struct bsd_fb_fix_info{
    long int line_length;
    long int smem_len;
};

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
#if USE_BSD_FBDEV
static struct bsd_fb_var_info vinfo;
static struct bsd_fb_fix_info finfo;
#else
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
#endif /* USE_BSD_FBDEV */
static char *fbp = 0;
static long int screensize = 0;
static int fbfd = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void fbdev_init(void)
{
    // Open the file for reading and writing
    fbfd = open(FBDEV_PATH, O_RDWR);
    if(fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        return;
    }
    printf("The framebuffer device was opened successfully.\n");

#if USE_BSD_FBDEV
    struct fbtype fb;
    unsigned line_length;

    //Get fb type
    if (ioctl(fbfd, FBIOGTYPE, &fb) != 0) {
        perror("ioctl(FBIOGTYPE)");
        return;
    }

    //Get screen width
    if (ioctl(fbfd, FBIO_GETLINEWIDTH, &line_length) != 0) {
        perror("ioctl(FBIO_GETLINEWIDTH)");
        return;
    }

    vinfo.xres = (unsigned) fb.fb_width;
    vinfo.yres = (unsigned) fb.fb_height;
    vinfo.bits_per_pixel = fb.fb_depth + 8;
    vinfo.xoffset = 0;
    vinfo.yoffset = 0;
    finfo.line_length = line_length;
    finfo.smem_len = finfo.line_length * vinfo.yres;
#else /* USE_BSD_FBDEV */

    // Get fixed screen information
    if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        return;
    }

    // Get variable screen information
    if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        return;
    }
#endif /* USE_BSD_FBDEV */

    printf("%dx%d, %dbpp, yoffset=%d\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel, vinfo.yoffset);

    // Figure out the size of the screen in bytes
    screensize =  finfo.smem_len; //finfo.line_length * vinfo.yres;    

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if((intptr_t)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        return;
    }
    memset(fbp, 0, screensize);

    printf("The framebuffer device was mapped to memory successfully.\n");

}

void fbdev_exit(void)
{
    close(fbfd);
}

/**
 * Flush a buffer to the marked area
 * @param drv pointer to driver where this function belongs
 * @param area an area where to copy `color_p`
 * @param color_p an array of pixel to copy to the `area` part of the screen
 */
void fbdev_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
    if(fbp == NULL ||
            area->x2 < 0 ||
            area->y2 < 0 ||
            area->x1 > (int32_t)vinfo.xres - 1 ||
            area->y1 > (int32_t)vinfo.yres - 1) {
        lv_disp_flush_ready(drv);
        return;
    }

    /*Truncate the area to the screen*/
    int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
    int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
    int32_t act_x2 = area->x2 > (int32_t)vinfo.xres - 1 ? (int32_t)vinfo.xres - 1 : area->x2;
    int32_t act_y2 = area->y2 > (int32_t)vinfo.yres - 1 ? (int32_t)vinfo.yres - 1 : area->y2;


    lv_coord_t w = (act_x2 - act_x1 + 1);
    long int location = 0;
    long int byte_location = 0;
    unsigned char bit_location = 0;

    /*32 or 24 bit per pixel*/
    if(vinfo.bits_per_pixel == 32 || vinfo.bits_per_pixel == 24) {
        uint32_t * fbp32 = (uint32_t *)fbp;
        int32_t y;
#if 0
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 4;
            memcpy(&fbp32[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 4);
            color_p += w;
        }
#elif 0
	int32_t x;
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 4;
            memcpy(&fbp32[location], 
		(uint32_t *)(color_p + (act_x2 - act_x1 + 1) * (y - act_y1)), 
		(act_x2 - act_x1 + 1) * 4);
        }
#elif 0
	int32_t x;
        for(y = act_y1; y <= act_y2; y++) {
	    for (x = 0; x < (act_x2 - act_x1 + 1)/* * 4*/; ++x)
	    {
            	fbp32[(act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 4 + x] =  
			((uint32_t *)color_p)[(act_x2 - act_x1 + 1) * (y - act_y1) + x]; 
	    }
        }
#elif 0
	int32_t x;
	uint32_t *color32 = (uint32_t *)color_p;
        for(y = act_y1; y <= act_y2; ++y) {
	    for (x = act_x1; x <= act_x2; ++x) {
            	fbp32[(y + vinfo.yoffset) * finfo.line_length / 4 + (vinfo.xoffset + x)] =  
			color32[(act_x2 - act_x1 + 1) * (y - act_y1) + (x - act_x1)]; 
	    }
        }
#elif 0
	int32_t x;
	uint32_t *color32 = (uint32_t *)color_p;
	for(y = act_y1; y <= act_y2; ++y) {
	    for (x = act_x1; x <= act_x2; ++x) {
            	fbp32[y * vinfo.xres + x] =  
			color32[(act_x2 - act_x1 + 1) * (y - act_y1) + (x - act_x1)]; 
	    }
        }
#elif 0
//not good
//rotate and flip
//exchange x and y, and flip x
	int32_t x;
	uint32_t *color32 = (uint32_t *)color_p;
	for(y = act_y1; y <= act_y2; ++y) {
	    for (x = act_x1; x <= act_x2; ++x) {
if (y < 0 || y >= vinfo.xres) continue;
if ((vinfo.yres - x - 1) < 0 || (vinfo.yres - x - 1) >= vinfo.yres) continue;

if (y - act_x1 < 0 || y - act_x1 >= (act_x2 - act_x1 + 1)) continue;
if (((vinfo.yres - x - 1) - act_y1) < 0 || ((vinfo.yres - x - 1) - act_y1) >= (act_y2 - act_y1 + 1)) continue;

            	fbp32[(vinfo.yres - x - 1) * vinfo.xres + y] =  
			color32[(act_x2 - act_x1 + 1) * ((vinfo.yres - x - 1) - act_y1) + (y - act_x1)]; 
	    }
        }
#elif 1
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
#endif
    }
    /*16 bit per pixel*/
    else if(vinfo.bits_per_pixel == 16) {
        uint16_t * fbp16 = (uint16_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length / 2;
            memcpy(&fbp16[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1) * 2);
            color_p += w;
        }
    }
    /*8 bit per pixel*/
    else if(vinfo.bits_per_pixel == 8) {
        uint8_t * fbp8 = (uint8_t *)fbp;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            location = (act_x1 + vinfo.xoffset) + (y + vinfo.yoffset) * finfo.line_length;
            memcpy(&fbp8[location], (uint32_t *)color_p, (act_x2 - act_x1 + 1));
            color_p += w;
        }
    }
    /*1 bit per pixel*/
    else if(vinfo.bits_per_pixel == 1) {
        uint8_t * fbp8 = (uint8_t *)fbp;
        int32_t x;
        int32_t y;
        for(y = act_y1; y <= act_y2; y++) {
            for(x = act_x1; x <= act_x2; x++) {
                location = (x + vinfo.xoffset) + (y + vinfo.yoffset) * vinfo.xres;
                byte_location = location / 8; /* find the byte we need to change */
                bit_location = location % 8; /* inside the byte found, find the bit we need to change */
                fbp8[byte_location] &= ~(((uint8_t)(1)) << bit_location);
                fbp8[byte_location] |= ((uint8_t)(color_p->full)) << bit_location;
                color_p++;
            }

            color_p += area->x2 - act_x2;
        }
    } else {
        /*Not supported bit per pixel*/
    }

    //May be some direct update command is required
    //ret = ioctl(state->fd, FBIO_UPDATE, (unsigned long)((uintptr_t)rect));

    lv_disp_flush_ready(drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif
