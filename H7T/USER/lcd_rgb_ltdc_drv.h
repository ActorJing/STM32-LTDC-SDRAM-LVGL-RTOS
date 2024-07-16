#ifndef _LCD_RGB_LTDC_DRV_H_
#define _LCD_RGB_LTDC_DRV_H_

#include "ltdc.h"
//#include "fonts.h"
/**
 * @brief   Windows size on lcd.
*/
#define LCD_WIDTH       800
#define LCD_HEIGHT      480

/**
 * @brief   start address of lcd framebuffer.
*/
#define LCD_FRAME_BUFFER    0xD0000000

/** 
  * @brief  字体对齐模式  
  */ 
typedef enum
{
  CENTER_MODE             = 0x01,    /* 居中对齐 */
  RIGHT_MODE              = 0x02,    /* 右对齐   */
  LEFT_MODE               = 0x03     /* 左对齐   */
}Text_AlignModeTypdef;

/**
 * @brief   color
 * @note    rgb565   
*/
#define BLACK   0x0000
#define BLUE    0x001F
#define GREEN   0x07E0
#define GBLUE   0X07FF
#define GRAY    0X8430
#define BROWN   0XBC40
#define RED     0xF800
#define PINK    0XF81F
#define BRRED   0XFC07
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

/**
 * @brief       Control the lcd backlight.
 * @param[in]   brightness  the value of lcd backlight.
 * @return      None
*/
void lcd_backlight_control(uint8_t bightness);

/**
 * @brief       LCD initialization.
 * @param       None
 * @return      None
*/
void lcd_init(void);

/**
 * @brief       Clear lcd.
 * @param[in]   color   rgb565.
 * @return      None
*/
void lcd_clear(uint16_t color);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode);
#endif /* _LCD_RGB_LTDC_DRV_H_ */

