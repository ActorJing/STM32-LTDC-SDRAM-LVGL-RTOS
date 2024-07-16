#include "main.h"
#include "lcd_rgb_ltdc_drv.h"
#include "dma2d.h"

#include "fonts.h"

static void dma2d_transfer_data_r2m(uint32_t *addr, uint32_t xSize, uint32_t ySize, uint32_t offsetLine, uint16_t color)
{
    DMA2D->CR = DMA2D_R2M;   // dma2d mode: register to memory.
    DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;

    DMA2D->OCOLR = color;
    DMA2D->OMAR = (uint32_t)addr;
    DMA2D->OOR = offsetLine;
    DMA2D->NLR = (uint32_t)(xSize << 16) | (uint16_t)ySize;
//    DMA2D->NLR = (uint32_t)(xSize * ySize);
    
    DMA2D->CR |= DMA2D_CR_START;
    while (DMA2D->CR & DMA2D_CR_START);
}

void lcd_clear(uint16_t color)
{
    dma2d_transfer_data_r2m((uint32_t *)LCD_FRAME_BUFFER, LCD_WIDTH, LCD_HEIGHT, 0, color);
//    uint16_t *ptr = (uint16_t*)LCD_FRAME_BUFFER;
//    uint32_t i = 0;

//    while (i++ < LCD_WIDTH*LCD_HEIGHT) {
//        *(ptr+i) = color;
//    }
}

void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    uint32_t pos;
    uint16_t *ptr;

    // check position.
    if (x > LCD_WIDTH || y > LCD_HEIGHT) {
        return;
    }

    // calculate the position offset in framebuffer.
    pos = x + y*LCD_WIDTH;
    ptr = (uint16_t*)LCD_FRAME_BUFFER;

    // modify the framebuffer.

    dma2d_transfer_data_r2m((uint32_t *)(ptr+pos), 1, 1, 0, color);

}


/**
  * @brief  显示一个字符
  * @param  Xpos: 显示字符的行位置
  * @param  Ypos: 列起始位置
  * @param  c: 指向字体数据的指针
  * @retval 无
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c)
{
  uint32_t i = 0, j = 0;
  uint16_t height, width;
  uint8_t  offset;
  uint8_t  *pchar;
  uint32_t line;
  
  height = Font24.Height;//获取正在使用字体高度
  width  = Font24.Width; //获取正在使用字体宽度
  
  offset =  8 *((width + 7)/8) -  width ;//计算字符的每一行像素的偏移值，实际存储大小-字体宽度
  
  for(i = 0; i < height; i++)//遍历字体高度绘点
  {
    pchar = ((uint8_t *)c + (width + 7)/8 * i);//计算字符的每一行像素的偏移地址
    
    switch(((width + 7)/8))//根据字体宽度来提取不同字体的实际像素值
    {
      
    case 1:
      line =  pchar[0];      //提取字体宽度小于8的字符的像素值
      break;
      
    case 2:
      line =  (pchar[0]<< 8) | pchar[1]; //提取字体宽度大于8小于16的字符的像素值     
      break;
      
    case 3:
    default:
      line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2]; //提取字体宽度大于16小于24的字符的像素值     
      break;
    } 
    
    for (j = 0; j < width; j++)//遍历字体宽度绘点
    {
      if(line & (1 << (width- j + offset- 1))) //根据每一行的像素值及偏移位置按照当前字体颜色进行绘点
      {
        lcd_draw_point((Xpos + j), Ypos, RED);
      }
      else//如果这一行没有字体像素则按照背景颜色绘点
      {
        lcd_draw_point((Xpos + j), Ypos, WHITE);
      } 
    }
    Ypos++;
  }
}

void LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
    DrawChar(Xpos, Ypos, &Font24.table[(Ascii-' ') *\
    Font24.Height * ((Font24.Width + 7) / 8)]);
}

void LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode)
{
  uint16_t ref_column = 1, i = 0;
  uint32_t size = 0, xsize = 0; 
  uint8_t  *ptr = Text;
  
  /* 获取字符串大小 */
  while (*ptr++) size ++ ;
  
  /* 每一行可以显示字符的数量 */
  xsize = (LCD_WIDTH/17);
  
  switch (Mode)
  {
  case CENTER_MODE:
    {
      ref_column = Xpos + ((xsize - size)* 17) / 2;
      break;
    }
  case LEFT_MODE:
    {
      ref_column = Xpos;
      break;
    }
  case RIGHT_MODE:
    {
      ref_column = - Xpos + ((xsize - size)*17);
      break;
    }    
  default:
    {
      ref_column = Xpos;
      break;
    }
  }
  
  /*检查起始行是否在显示范围内 */
  if ((ref_column < 1) || (ref_column >= 0x8000))
  {
    ref_column = 1;
  }

  /* 使用字符显示函数显示每一个字符*/
  while ((*Text != 0) & (((800 - (i*17)) & 0xFFFF)\
			>= 17))
  {
    /* 显示一个字符 */
    LCD_DisplayChar(ref_column, Ypos, *Text);
    /* 根据字体大小计算下一个偏移位置 */
    ref_column += 17;
    /* 指针指向下一个字符 */
    Text++;
    i++;
  }  
}
