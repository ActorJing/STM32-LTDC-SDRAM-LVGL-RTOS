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
  * @brief  ��ʾһ���ַ�
  * @param  Xpos: ��ʾ�ַ�����λ��
  * @param  Ypos: ����ʼλ��
  * @param  c: ָ���������ݵ�ָ��
  * @retval ��
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c)
{
  uint32_t i = 0, j = 0;
  uint16_t height, width;
  uint8_t  offset;
  uint8_t  *pchar;
  uint32_t line;
  
  height = Font24.Height;//��ȡ����ʹ������߶�
  width  = Font24.Width; //��ȡ����ʹ��������
  
  offset =  8 *((width + 7)/8) -  width ;//�����ַ���ÿһ�����ص�ƫ��ֵ��ʵ�ʴ洢��С-������
  
  for(i = 0; i < height; i++)//��������߶Ȼ��
  {
    pchar = ((uint8_t *)c + (width + 7)/8 * i);//�����ַ���ÿһ�����ص�ƫ�Ƶ�ַ
    
    switch(((width + 7)/8))//��������������ȡ��ͬ�����ʵ������ֵ
    {
      
    case 1:
      line =  pchar[0];      //��ȡ������С��8���ַ�������ֵ
      break;
      
    case 2:
      line =  (pchar[0]<< 8) | pchar[1]; //��ȡ�����ȴ���8С��16���ַ�������ֵ     
      break;
      
    case 3:
    default:
      line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2]; //��ȡ�����ȴ���16С��24���ַ�������ֵ     
      break;
    } 
    
    for (j = 0; j < width; j++)//���������Ȼ��
    {
      if(line & (1 << (width- j + offset- 1))) //����ÿһ�е�����ֵ��ƫ��λ�ð��յ�ǰ������ɫ���л��
      {
        lcd_draw_point((Xpos + j), Ypos, RED);
      }
      else//�����һ��û�������������ձ�����ɫ���
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
  
  /* ��ȡ�ַ�����С */
  while (*ptr++) size ++ ;
  
  /* ÿһ�п�����ʾ�ַ������� */
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
  
  /*�����ʼ���Ƿ�����ʾ��Χ�� */
  if ((ref_column < 1) || (ref_column >= 0x8000))
  {
    ref_column = 1;
  }

  /* ʹ���ַ���ʾ������ʾÿһ���ַ�*/
  while ((*Text != 0) & (((800 - (i*17)) & 0xFFFF)\
			>= 17))
  {
    /* ��ʾһ���ַ� */
    LCD_DisplayChar(ref_column, Ypos, *Text);
    /* ���������С������һ��ƫ��λ�� */
    ref_column += 17;
    /* ָ��ָ����һ���ַ� */
    Text++;
    i++;
  }  
}
