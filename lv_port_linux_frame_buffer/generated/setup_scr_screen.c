/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL, NULL);

	//Write codes screen_img_num0
	ui->screen_img_num0 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_num0
	static lv_style_t style_screen_img_num0_main;
	lv_style_init(&style_screen_img_num0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_num0_main
	lv_style_set_image_recolor(&style_screen_img_num0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_num0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_num0_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_num0, LV_IMG_PART_MAIN, &style_screen_img_num0_main);
	lv_obj_set_pos(ui->screen_img_num0, 0, 0);
	lv_obj_set_size(ui->screen_img_num0, 800, 480);
	lv_obj_set_click(ui->screen_img_num0, true);
	lv_img_set_src(ui->screen_img_num0,&_pic1_alpha_800x480);
	lv_img_set_pivot(ui->screen_img_num0, 0,0);
	lv_img_set_angle(ui->screen_img_num0, 0);

	//Write codes screen_img_num1
	ui->screen_img_num1 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_num1
	static lv_style_t style_screen_img_num1_main;
	lv_style_init(&style_screen_img_num1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_num1_main
	lv_style_set_image_recolor(&style_screen_img_num1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_num1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_num1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_num1, LV_IMG_PART_MAIN, &style_screen_img_num1_main);
	lv_obj_set_pos(ui->screen_img_num1, 0, 0);
	lv_obj_set_size(ui->screen_img_num1, 800, 480);
	lv_obj_set_click(ui->screen_img_num1, true);
	lv_img_set_src(ui->screen_img_num1,&_pic2_alpha_800x480);
	lv_img_set_pivot(ui->screen_img_num1, 0,0);
	lv_img_set_angle(ui->screen_img_num1, 0);

	//Write codes screen_img_num2
	ui->screen_img_num2 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_num2
	static lv_style_t style_screen_img_num2_main;
	lv_style_init(&style_screen_img_num2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_num2_main
	lv_style_set_image_recolor(&style_screen_img_num2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_num2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_num2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_num2, LV_IMG_PART_MAIN, &style_screen_img_num2_main);
	lv_obj_set_pos(ui->screen_img_num2, 0, 0);
	lv_obj_set_size(ui->screen_img_num2, 800, 480);
	lv_obj_set_click(ui->screen_img_num2, true);
	lv_img_set_src(ui->screen_img_num2,&_pic3_alpha_800x480);
	lv_img_set_pivot(ui->screen_img_num2, 0,0);
	lv_img_set_angle(ui->screen_img_num2, 0);

	//Write codes screen_img_num3
	ui->screen_img_num3 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_num3
	static lv_style_t style_screen_img_num3_main;
	lv_style_init(&style_screen_img_num3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_num3_main
	lv_style_set_image_recolor(&style_screen_img_num3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_num3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_num3_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_num3, LV_IMG_PART_MAIN, &style_screen_img_num3_main);
	lv_obj_set_pos(ui->screen_img_num3, 0, 0);
	lv_obj_set_size(ui->screen_img_num3, 800, 480);
	lv_obj_set_click(ui->screen_img_num3, true);
	lv_img_set_src(ui->screen_img_num3,&_pic4_alpha_800x480);
	lv_img_set_pivot(ui->screen_img_num3, 0,0);
	lv_img_set_angle(ui->screen_img_num3, 0);

	//Write codes screen_img_num4
	ui->screen_img_num4 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_num4
	static lv_style_t style_screen_img_num4_main;
	lv_style_init(&style_screen_img_num4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_num4_main
	lv_style_set_image_recolor(&style_screen_img_num4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_num4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_num4_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_num4, LV_IMG_PART_MAIN, &style_screen_img_num4_main);
	lv_obj_set_pos(ui->screen_img_num4, 0, 0);
	lv_obj_set_size(ui->screen_img_num4, 800, 480);
	lv_obj_set_click(ui->screen_img_num4, true);
	lv_img_set_src(ui->screen_img_num4,&_pic5_alpha_800x480);
	lv_img_set_pivot(ui->screen_img_num4, 0,0);
	lv_img_set_angle(ui->screen_img_num4, 0);

	//Init events for screen
	events_init_screen(ui);
}