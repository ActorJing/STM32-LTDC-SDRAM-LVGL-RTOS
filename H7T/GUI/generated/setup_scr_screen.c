/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int screen_digital_clock_1_min_value = 25;
int screen_digital_clock_1_hour_value = 11;
int screen_digital_clock_1_sec_value = 50;
char screen_digital_clock_1_meridiem[] = "AM";
void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	ui->g_kb_screen = lv_keyboard_create(ui->screen);
	lv_obj_add_event_cb(ui->g_kb_screen, kb_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(ui->g_kb_screen, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(ui->g_kb_screen, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_size(ui->screen, 800, 480);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_digital_clock_1
	static bool screen_digital_clock_1_timer_enabled = false;
	ui->screen_digital_clock_1 = lv_dclock_create(ui->screen, "11:25:50 AM");
	if (!screen_digital_clock_1_timer_enabled) {
		lv_timer_create(screen_digital_clock_1_timer, 1000, NULL);
		screen_digital_clock_1_timer_enabled = true;
	}
	lv_obj_set_pos(ui->screen_digital_clock_1, 4, 4);
	lv_obj_set_size(ui->screen_digital_clock_1, 100, 25);

	//Write style for screen_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_digital_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_digital_clock_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_digital_clock_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_digital_clock_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_digital_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_digital_clock_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_digital_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_slider_1
	ui->screen_slider_1 = lv_slider_create(ui->screen);
	lv_slider_set_range(ui->screen_slider_1, 0, 100);
	lv_slider_set_mode(ui->screen_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_slider_1, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_slider_1, 72, 81);
	lv_obj_set_size(ui->screen_slider_1, 241, 28);

	//Write style for screen_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_slider_2
	ui->screen_slider_2 = lv_slider_create(ui->screen);
	lv_slider_set_range(ui->screen_slider_2, 0, 100);
	lv_slider_set_mode(ui->screen_slider_2, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_slider_2, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_slider_2, 349, 80);
	lv_obj_set_size(ui->screen_slider_2, 252, 29);

	//Write style for screen_slider_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider_2, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider_2, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_slider_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_slider_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider_2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider_2, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_slider_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_slider_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_slider_2, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_slider_2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_slider_2, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_animimg_1
	ui->screen_animimg_1 = lv_animimg_create(ui->screen);
	lv_animimg_set_src(ui->screen_animimg_1, (const void **) screen_animimg_1_imgs, 35);
	lv_animimg_set_duration(ui->screen_animimg_1, 40*35);
	lv_animimg_set_repeat_count(ui->screen_animimg_1, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->screen_animimg_1);
	lv_obj_set_pos(ui->screen_animimg_1, 56, 341);
	lv_obj_set_size(ui->screen_animimg_1, 134, 99);

	//Write codes screen_sw_1
	ui->screen_sw_1 = lv_switch_create(ui->screen);
	lv_obj_set_pos(ui->screen_sw_1, 680, 78);
	lv_obj_set_size(ui->screen_sw_1, 73, 31);

	//Write style for screen_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
	lv_obj_set_style_bg_opa(ui->screen_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style for screen_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_arc_1
	ui->screen_arc_1 = lv_arc_create(ui->screen);
	lv_arc_set_mode(ui->screen_arc_1, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->screen_arc_1, 0, 100);
	lv_arc_set_bg_angles(ui->screen_arc_1, 135, 45);
	lv_arc_set_value(ui->screen_arc_1, 70);
	lv_arc_set_rotation(ui->screen_arc_1, 0);
	lv_obj_set_style_arc_rounded(ui->screen_arc_1, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->screen_arc_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_arc_1, 556, 262);
	lv_obj_set_size(ui->screen_arc_1, 220, 165);

	//Write style for screen_arc_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_arc_1, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_arc_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_arc_1, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_arc_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_arc_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_arc_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_arc_1, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_arc_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_arc_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_arc_1, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_arc_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_arc_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_arc_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_arc_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_arc_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_arc_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->screen_arc_1, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_label_1, "0");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_1, 220, 181);
	lv_obj_set_size(ui->screen_label_1, 100, 32);

	//Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_montserratMedium_37, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btn_1
	ui->screen_btn_1 = lv_btn_create(ui->screen);
	ui->screen_btn_1_label = lv_label_create(ui->screen_btn_1);
	lv_label_set_text(ui->screen_btn_1_label, "+");
	lv_label_set_long_mode(ui->screen_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_1, 109, 232);
	lv_obj_set_size(ui->screen_btn_1, 100, 50);

	//Write style for screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btn_2
	ui->screen_btn_2 = lv_btn_create(ui->screen);
	ui->screen_btn_2_label = lv_label_create(ui->screen_btn_2);
	lv_label_set_text(ui->screen_btn_2_label, "-");
	lv_label_set_long_mode(ui->screen_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_btn_2_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_btn_2, 342, 232);
	lv_obj_set_size(ui->screen_btn_2, 100, 50);

	//Write style for screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_ddlist_1
	ui->screen_ddlist_1 = lv_dropdown_create(ui->screen);
	lv_dropdown_set_options(ui->screen_ddlist_1, "list1\nlist2\nlist3");
	lv_obj_set_pos(ui->screen_ddlist_1, 561, 135);
	lv_obj_set_size(ui->screen_ddlist_1, 216, 99);

	//Write style for screen_ddlist_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_ddlist_1, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_ddlist_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_ddlist_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_ddlist_1, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_ddlist_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_ddlist_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ddlist_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_ddlist_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_ddlist_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_ddlist_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_screen_ddlist_1_extra_list_selected_checked
	static lv_style_t style_screen_ddlist_1_extra_list_selected_checked;
	ui_init_style(&style_screen_ddlist_1_extra_list_selected_checked);
	
	lv_style_set_border_width(&style_screen_ddlist_1_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_ddlist_1_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_ddlist_1), &style_screen_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_ddlist_1_extra_list_main_default
	static lv_style_t style_screen_ddlist_1_extra_list_main_default;
	ui_init_style(&style_screen_ddlist_1_extra_list_main_default);
	
	lv_style_set_max_height(&style_screen_ddlist_1_extra_list_main_default, 90);
	lv_style_set_text_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_ddlist_1_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_text_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_width(&style_screen_ddlist_1_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0xffffff));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_ddlist_1), &style_screen_ddlist_1_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_ddlist_1_extra_list_scrollbar_default
	static lv_style_t style_screen_ddlist_1_extra_list_scrollbar_default;
	ui_init_style(&style_screen_ddlist_1_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_ddlist_1), &style_screen_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_ta_1
	ui->screen_ta_1 = lv_textarea_create(ui->screen);
	lv_textarea_set_text(ui->screen_ta_1, "Hello World");
	lv_textarea_set_placeholder_text(ui->screen_ta_1, "");
	lv_textarea_set_password_bullet(ui->screen_ta_1, "*");
	lv_textarea_set_password_mode(ui->screen_ta_1, false);
	lv_textarea_set_one_line(ui->screen_ta_1, false);
	lv_textarea_set_accepted_chars(ui->screen_ta_1, "");
	lv_textarea_set_max_length(ui->screen_ta_1, 32);
	#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
		lv_obj_add_event_cb(ui->screen_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_screen);
	#endif
	lv_obj_set_pos(ui->screen_ta_1, 292, 348);
	lv_obj_set_size(ui->screen_ta_1, 200, 60);

	//Write style for screen_ta_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_ta_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_ta_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_ta_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_ta_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_ta_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_ta_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_ta_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_ta_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_ta_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_ta_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_ta_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ta_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_ta_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_ta_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_ta_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_ta_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//The custom code of screen.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	//Init events for screen.
	events_init_screen(ui);
}
