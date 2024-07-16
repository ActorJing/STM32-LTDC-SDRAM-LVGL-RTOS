/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *g_kb_screen;
	lv_obj_t *screen_digital_clock_1;
	lv_obj_t *screen_slider_1;
	lv_obj_t *screen_slider_2;
	lv_obj_t *screen_animimg_1;
	lv_obj_t *screen_sw_1;
	lv_obj_t *screen_arc_1;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_btn_1;
	lv_obj_t *screen_btn_1_label;
	lv_obj_t *screen_btn_2;
	lv_obj_t *screen_btn_2_label;
	lv_obj_t *screen_ddlist_1;
	lv_obj_t *screen_ta_1;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_move_animation(void * var, int32_t duration, int32_t delay, int32_t x_end, int32_t y_end, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_scale_animation(void * var, int32_t duration, int32_t delay, int32_t width, int32_t height, lv_anim_path_cb_t path_cb,
                        uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                        lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_zoom_animation(void * var, int32_t duration, int32_t delay, int32_t zoom, lv_anim_path_cb_t path_cb,
                           uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                           lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_rotate_animation(void * var, int32_t duration, int32_t delay, lv_coord_t x, lv_coord_t y, int32_t rotate,
                   lv_anim_path_cb_t path_cb, uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time,
                   uint32_t playback_delay, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
#include "extra/widgets/animimg/lv_animimg.h"
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_0);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_1);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_2);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_3);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_4);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_5);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_6);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_7);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_8);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_9);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_10);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_11);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_12);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_13);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_14);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_15);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_16);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_17);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_18);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_19);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_20);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_21);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_22);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_23);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_24);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_25);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_26);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_27);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_28);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_29);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_30);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_31);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_32);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_33);
LV_IMG_DECLARE(screen_animimg_120200329040230_BGeJU_34);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_37)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)


#ifdef __cplusplus
}
#endif
#endif
