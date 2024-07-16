
#ifndef _GT9157_H
#define _GT9157_H

#include "main.h"

#define GTP_ADDRESS                      0xBA

#define GT_CMD_WR 		0XBA    //д����
#define GT_CMD_RD 		0XBB		//������
/** 
  * @brief  ����������
  */ 
typedef enum 
{
	GT9157=0,
	GT911=1,
  GT5688=2,
	GT917S=3,
  GT615=4,
  GT1151QM=5,
  
  TOUCH_TYPE_NUM /* TOUCHоƬ�������� */
}TOUCH_IC;

/** 
  * @brief ����������
  */
typedef struct
{
  /*���ݴ�������������*/
  uint16_t max_width;  //�������ֵ,��
  uint16_t max_height;  //�������ֵ����

  uint16_t config_reg_addr;  	//��ͬ���͵Ĵ���ic���üĴ�����ַ��ͬ

}TOUCH_PARAM_TypeDef;

/** 
  * @brief  LCDҺ������
  */   
typedef enum
{ 
  INCH_5  = 0x00, /* Ұ��5���� */
  INCH_7,     /* Ұ��7���� */
  INCH_4_3,  /* Ұ��4.3���� */
  
  LCD_TYPE_NUM /* LCD��������*/
}LCD_TypeDef;
/* ��ʾ������ */ 
#define I2C_M_RD		0x0001	 /*
 * �洢I2CͨѶ����Ϣ
 * @addr��  ���豸��I2C�豸��ַ	
 * @flags: ���Ʊ�־
 * @len��  ��д���ݵĳ���
 * @buf��  �洢��д���ݵ�ָ��
 **/
struct i2c_msg {
	uint8_t addr;		/*���豸��I2C�豸��ַ */
	uint16_t flags;	/*���Ʊ�־*/
	uint16_t len;		/*��д���ݵĳ���			*/
	uint8_t *buf;		/*�洢��д���ݵ�ָ��	*/
};

#define GTP_ADDR_LENGTH       2

#define GTP_REG_CONFIG_DATA   touch_param[touchIC].config_reg_addr
#define GTP_REG_VERSION       0x8140
#define GTP_READ_COOR_ADDR    0x814E


#define GT_GSTID_REG 	0X814E   	//GT911��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  

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
