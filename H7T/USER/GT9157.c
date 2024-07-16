#include "GT9157.h"
#include "i2c.h"

const TOUCH_PARAM_TypeDef touch_param[TOUCH_TYPE_NUM] = 
{
  /* GT9157,5寸屏 */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8047,
  },
  /* GT911,7寸屏 */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8047,
  },
  /* GT5688,4.3寸屏 */
  {
    .max_width = 480,
    .max_height = 272,
    .config_reg_addr = 0x8050,
  },
	 /* GT917S,5寸屏 */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8050,
  },
  /* GT615,7寸屏 */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8047, //该起始地址与GT911的一样
  },

#if TOUCH_GT1151QM_LCD_4_3
  /* GT1151QM,4.3寸屏 */
  {
    .max_width = 480,
    .max_height = 272,
    .config_reg_addr = 0x8050,
  },
#elif TOUCH_GT1151QM_LCD_5
  /* GT1151QM,5寸屏 */
  {
    .max_width = 800,
    .max_height = 480,
    .config_reg_addr = 0x8050,
  },
#endif
};

LCD_TypeDef cur_lcd = INCH_5;

/**
  * @brief   使用IIC进行数据传输
  * @param
  *		@arg i2c_msg:数据传输结构体
  *		@arg num:数据传输结构体的个数
  * @retval  正常完成的传输结构个数，若不正常，返回0xff
  */
static int I2C_Transfer( struct i2c_msg *msgs,int num)
{
	int im = 0;
	int ret = 0;

//	GTP_DEBUG_FUNC();

	for (im = 0; ret == 0 && im != num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//根据flag判断是读数据还是写数据
		{
//			ret = HAL_I2C_Master_Receive(&hi2c2, msgs[im].addr, msgs[im].buf, msgs[im].len, HAL_MAX_DELAY);		//IIC读取数据
            GT911_ReadReg(msgs[im].addr, msgs[im].buf, msgs[im].len);
		} else
		{
//			ret = HAL_I2C_Master_Transmit(&hi2c2, msgs[im].addr,  msgs[im].buf, msgs[im].len, HAL_MAX_DELAY);	//IIC写入数据
            GT911_WriteReg(msgs[im].addr,  msgs[im].buf, msgs[im].len);
		}
	}

	if(ret)
		return ret;

	return im;   													//正常完成的传输结构个数
}


/**
  * @brief   向IIC设备写入数据
  * @param
  *		@arg client_addr:设备地址
  *		@arg  buf[0~1]: 要写入的数据寄存器的起始地址
  *		@arg buf[2~len-1]: 要写入的数据
  *		@arg len:    GTP_ADDR_LENGTH + write bytes count（寄存器地址长度+写入的数据字节数）
  * @retval  i2c_msgs传输结构体的个数，1为成功，其它为失败
  */
int32_t GTP_I2C_Write(uint8_t client_addr,uint8_t *buf,int32_t len)
{
    struct i2c_msg msg;
    int32_t ret = -1;
    int32_t retries = 0;

//    GTP_DEBUG_FUNC();
    /*一个写数据的过程只需要一个传输过程:
     * 1. IIC连续 写入 数据寄存器地址及数据
     * */
    msg.flags = !I2C_M_RD;			//写入
    msg.addr  = client_addr;			//从设备地址
    msg.len   = len;							//长度直接等于(寄存器地址长度+写入的数据字节数)
    msg.buf   = buf;						//直接连续写入缓冲区中的数据(包括了寄存器地址)

    while(retries < 5)
    {
        ret = I2C_Transfer(&msg, 1);	//调用IIC数据传输过程函数，1个传输过程
        if (ret == 1)break;
        retries++;
    }
    if((retries >= 5))
    {

//        GTP_ERROR("I2C Write: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);

    }
    return ret;
}
/**
  * @brief   从IIC设备中读取数据
  * @param
  *		@arg client_addr:设备地址
  *		@arg  buf[0~1]: 读取数据寄存器的起始地址
  *		@arg buf[2~len-1]: 存储读出来数据的缓冲buffer
  *		@arg len:    GTP_ADDR_LENGTH + read bytes count（寄存器地址长度+读取的数据字节数）
  * @retval  i2c_msgs传输结构体的个数，2为成功，其它为失败
  */
int32_t GTP_I2C_Read(uint8_t client_addr, uint8_t *buf, int32_t len)
{
    struct i2c_msg msgs[2];
    int32_t ret=-1;
    int32_t retries = 0;

//    GTP_DEBUG_FUNC();
    /*一个读数据的过程可以分为两个传输过程:
     * 1. IIC  写入 要读取的寄存器地址
     * 2. IIC  读取  数据
     * */

    msgs[0].flags = !I2C_M_RD;					//写入
    msgs[0].addr  = client_addr;					//IIC设备地址
    msgs[0].len   = GTP_ADDR_LENGTH;	//寄存器地址为2字节(即写入两字节的数据)
    msgs[0].buf   = &buf[0];						//buf[0~1]存储的是要读取的寄存器地址
    
    msgs[1].flags = I2C_M_RD;					//读取
    msgs[1].addr  = client_addr;					//IIC设备地址
    msgs[1].len   = len - GTP_ADDR_LENGTH;	//要读取的数据长度
    msgs[1].buf   = &buf[GTP_ADDR_LENGTH];	//buf[GTP_ADDR_LENGTH]之后的缓冲区存储读出的数据

    while(retries < 5)
    {
        ret = I2C_Transfer( msgs, 2);					//调用IIC数据传输过程函数，有2个传输过程
        if(ret == 2)break;
        retries++;
    }
    if((retries >= 5))
    {
//        GTP_ERROR("I2C Read: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
    }
    return ret;
}


/* 触摸IC类型默认为5寸屏的ic */
TOUCH_IC touchIC = GT9157;		
/*******************************************************
Function:
    I2c test Function.
Input:
    client:i2c client.
Output:
    Executive outcomes.
        2: succeed, otherwise failed.
*******************************************************/
static int8_t GTP_I2C_Test( void)
{
    uint8_t test[3] = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};
    uint8_t retry = 0;
    int8_t ret = -1;

//    GTP_DEBUG_FUNC();
  
    while(retry++ < 5)
    {
        ret = GTP_I2C_Read(GTP_ADDRESS, test, 3);
        if (ret > 0)
        {
            return ret;
        }
//        GTP_ERROR("GTP i2c test failed time %d.",retry);
    }
    return ret;
}

/*******************************************************
Function:
    Read chip version.
Input:
    client:  i2c device
    version: buffer to keep ic firmware version
Output:
    read operation return.
        2: succeed, otherwise: failed
*******************************************************/
int32_t GTP_Read_Version(void)
{
    int32_t ret = -1;
    uint8_t buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //寄存器地址

//    GTP_DEBUG_FUNC();

    ret = GTP_I2C_Read(GTP_ADDRESS, buf, sizeof(buf));
    if (ret < 0)
    {
//        GTP_ERROR("GTP read version failed");
        return ret;
    }

#ifdef LCD_TOUCH_IC_GT1151QM
    //GT1151QM芯片
    if (buf[2]=='1' && buf[3]=='1' && buf[4]=='5')
    {
        GTP_INFO("IC Version: %c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[7], buf[6]);
        touchIC = GT1151QM;
        
        #if TOUCH_GT1151QM_LCD_4_3
        cur_lcd = INCH_4_3;     //设置当前的液晶屏类型
        #elif TOUCH_GT1151QM_LCD_5
        cur_lcd = INCH_5;       //设置当前的液晶屏类型
        #endif
    }
    else
    {
        GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
    }
#else

    if (buf[4] == '1')
    {				
				//GT911芯片
				if(buf[2] == '9' && buf[3] == '1' && buf[4] == '1')
        {
//          GTP_INFO("IC1 Version: %c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[7], buf[6]);

					touchIC = GT911;
          /* 设置当前的液晶屏类型 */
//          cur_lcd = INCH_7;
        }
        //GT9157芯片
        else{}
//           GTP_INFO("Unknown IC Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
    }
    else if (buf[4] == '5')
    {
        if( buf[2] == '9' && buf[3] == '1' && buf[4] == '5' && buf[5] == '7')
    {
//          GTP_INFO("IC2 Version: %c%c%c%c_%02x%02x", buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);

					touchIC = GT9157;
          /* 设置当前的液晶屏类型 */
          cur_lcd = INCH_5;
    }

    }    
   
#endif

    return ret;
}

static int32_t GTP_Get_Info(void)
{
    uint8_t opr_buf[10] = {0};
    int32_t ret = 0;

    uint16_t abs_x_max = GTP_MAX_WIDTH;
    uint16_t abs_y_max = GTP_MAX_HEIGHT;
    uint8_t int_trigger_type = GTP_INT_TRIGGER;
        
    opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+1) >> 8);
    opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+1) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 10);
    if (ret < 0)
    {
        return 0;
    }
    
    abs_x_max = (opr_buf[3] << 8) + opr_buf[2];
    abs_y_max = (opr_buf[5] << 8) + opr_buf[4];
//		GTP_DEBUG("RES");   
//		GTP_DEBUG_ARRAY(&opr_buf[0],10);

    opr_buf[0] = (uint8_t)((GTP_REG_CONFIG_DATA+6) >> 8);
    opr_buf[1] = (uint8_t)((GTP_REG_CONFIG_DATA+6) & 0xFF);
    
    ret = GTP_I2C_Read(GTP_ADDRESS, opr_buf, 3);
    if (ret < 0)
    {
        return 0;
    }
    int_trigger_type = opr_buf[2] & 0x03;
    
//    GTP_INFO("X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x",
//            abs_x_max,abs_y_max,int_trigger_type);
    
    return 1;    
}

/*******************************************************
Function:
    Initialize gtp.
Input:
    ts: goodix private data
Output:
    Executive outcomes.
        0: succeed, otherwise: failed
*******************************************************/
int32_t GTP_Init_Panel(void)
{
    int32_t ret = -1;

    int32_t i = 0;
    uint16_t check_sum = 0;
    int32_t retry = 0;

    const uint8_t* cfg_info;
    uint8_t cfg_info_len  ;
		uint8_t* config;

    uint8_t cfg_num =0 ;		//需要配置的寄存器个数


    ret = GTP_I2C_Test();
    if (ret < 0)
    {
//        GTP_ERROR("I2C communication ERROR!");
				return ret;
    } 
		HAL_Delay(100);
		//获取触摸IC的型号
    GTP_Read_Version(); 
  
	 /* emXGUI示例中不使能中断 */
//		I2C_GTP_IRQEnable();
	
    GTP_Get_Info();

    return 0;
}
void GT911_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	HAL_I2C_Mem_Write(&hi2c2, GT_CMD_WR, _usRegAddr, I2C_MEMADD_SIZE_16BIT, _pRegBuf, _ucLen, 0xff);
}
void GT911_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	HAL_I2C_Mem_Read(&hi2c2, GT_CMD_RD, _usRegAddr, I2C_MEMADD_SIZE_16BIT, _pRegBuf, _ucLen, 0xff);
}
