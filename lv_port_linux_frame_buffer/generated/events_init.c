/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"
static uint8_t pic_num = 1;

void events_init(lv_ui *ui)
{
}

static void screen_img_num4event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
				pic_num ++;
				if(pic_num == 6) pic_num = 1;
				switch (pic_num)
				{
						case 1:
							lv_img_set_src(guider_ui.screen_img_num4,&_pic1_alpha_800x480);
							break;
						case 2:
							lv_img_set_src(guider_ui.screen_img_num4,&_pic2_alpha_800x480);
							break;
						case 3:
							lv_img_set_src(guider_ui.screen_img_num4,&_pic3_alpha_800x480);
							break;
						case 4:
							lv_img_set_src(guider_ui.screen_img_num4,&_pic4_alpha_800x480);
							break;
						case 5:
							lv_img_set_src(guider_ui.screen_img_num4,&_pic5_alpha_800x480);
							break;		
						default:
							break;
				}
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->screen_img_num4, screen_img_num4event_handler);
}
