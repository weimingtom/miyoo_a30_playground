/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	lv_obj_t *screen_img_num0;
	lv_obj_t *screen_img_num1;
	lv_obj_t *screen_img_num2;
	lv_obj_t *screen_img_num3;
	lv_obj_t *screen_img_num4;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_pic5_alpha_800x480);
LV_IMG_DECLARE(_pic3_alpha_800x480);
LV_IMG_DECLARE(_pic2_alpha_800x480);
LV_IMG_DECLARE(_pic1_alpha_800x480);
LV_IMG_DECLARE(_pic4_alpha_800x480);

#ifdef __cplusplus
}
#endif
#endif