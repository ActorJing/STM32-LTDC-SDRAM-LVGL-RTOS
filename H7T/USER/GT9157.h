
#ifndef _GT9157_H
#define _GT9157_H

#include "main.h"

#define GTP_ADDRESS                      0xBA

#define GT_CMD_WR 		0XBA    //写命令
#define GT_CMD_RD 		0XBB		//读命令
/** 
  * @brief  触摸屏类型
  */ 
typedef enum 
{
	GT9157=0,
	GT911=1,
  GT5688=2,
	GT917S=3,
  GT615=4,
  GT1151QM=5,
  
  TOUCH_TYPE_NUM /* TOUCH芯片类型总数 */
}TOUCH_IC;

/** 
  * @brief 触摸屏参数
  */
typedef struct
{
  /*根据触摸屏类型配置*/
  uint16_t max_width;  //触点最大值,高
  uint16_t max_height;  //触点最大值，宽

  uint16_t config_reg_addr;  	//不同类型的触摸ic配置寄存器地址不同

}TOUCH_PARAM_TypeDef;

/** 
  * @brief  LCD液晶类型
  */   
typedef enum
{ 
  INCH_5  = 0x00, /* 野火5寸屏 */
  INCH_7,     /* 野火7寸屏 */
  INCH_4_3,  /* 野火4.3寸屏 */
  
  LCD_TYPE_NUM /* LCD类型总数*/
}LCD_TypeDef;
/* 表示读数据 */ 
#define I2C_M_RD		0x0001	 /*
 * 存储I2C通讯的信息
 * @addr：  从设备的I2C设备地址	
 * @flags: 控制标志
 * @len：  读写数据的长度
 * @buf：  存储读写数据的指针
 **/
struct i2c_msg {
	uint8_t addr;		/*从设备的I2C设备地址 */
	uint16_t flags;	/*控制标志*/
	uint16_t len;		/*读写数据的长度			*/
	uint8_t *buf;		/*存储读写数据的指针	*/
};

#define GTP_ADDR_LENGTH       2

#define GTP_REG_CONFIG_DATA   touch_param[touchIC].config_reg_addr
#define GTP_REG_VERSION       0x8140
#define GTP_READ_COOR_ADDR    0x814E


#define GT_GSTID_REG 	0X814E   	//GT911当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址  

#define GTP_MAX_HEIGHT   touch_param[touchIC].max_height
#define GTP_MAX_WIDTH    touch_param[touchIC].max_width
#define GTP_INT_TRIGGER  0
#define GTP_MAX_TOUCH         5

int32_t GTP_Init_Panel(void);
int32_t GTP_I2C_Read(uint8_t client_addr, uint8_t *buf, int32_t len);
int32_t GTP_I2C_Write(uint8_t client_addr,uint8_t *buf,int32_t len);


void GT911_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void GT911_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);

#endif
