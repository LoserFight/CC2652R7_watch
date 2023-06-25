#include "lcd_init.h"
//#include "delay.h"



SPI_Handle  spi_h;

void spi_write(const void *data, uint32_t size)
{
//    if (size > SPI_MAX_BLOCK) {
//        uint32_t rest  = size;
//        uint32_t start = 0;
//            hal_spi_send(&spi_st7789, (const void *)(data + start),
//                         SPI_MAX_BLOCK, 10);
//            start += SPI_MAX_BLOCK;
//            rest -= SPI_MAX_BLOCK;
//        }
//        hal_spi_send(&spi_st7789, (const void *)(data + start), rest, 10);
//    } else {
//        hal_spi_send(&spi_st7789, (const void *)data, (uint16_t)size, 10);
//    }

//    uint8_t   transmitBuffer[BUFSIZE];
//    uint8_t   receiveBuffer[BUFSIZE];
    SPI_Transaction spiTransaction;
    spiTransaction.count = size;
    spiTransaction.txBuf = (void *)data;
    spiTransaction.rxBuf= NULL;
    spiTransaction.arg    = NULL;

    //spiTransaction.rxBuf = (void *)receiveBuffer;
    bool transferOK = SPI_transfer(spi_h, &spiTransaction);
    //CPUdelay(12000*10);
}
///******************************************************************************
//      函数说明：LCD串行数据写入函数
//      入口数据：dat  要写入的串行数据
//      返回值：  无
//******************************************************************************/
//void LCD_Writ_Bus(uint8_t dat)
//{
//	uint8_t i;
//	for(i=0;i<8;i++)
//	{
//		LCD_SCLK_Clr();
//		if(dat&0x80)
//		{
//		   LCD_MOSI_Set();
//		}
//		else
//		{
//		   LCD_MOSI_Clr();
//		}
//		LCD_SCLK_Set();
//		dat<<=1;
//	}
//}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{


    spi_write(&dat, sizeof(dat));
	//LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
    uint8_t data[2];
    data[0]=dat>>8;
    data[1]=dat;
    spi_write(data, 2);
//	LCD_Writ_Bus(dat>>8);
//	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//写命令
	spi_write(&dat, sizeof(dat));
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+80);
		LCD_WR_DATA(y2+80);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+80);
		LCD_WR_DATA(x2+80);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
}

void LCD_Init(void)
{
    SPI_init();
        SPI_Handle  spi;
        SPI_Params  spiParams;
        SPI_Params_init(&spiParams);
        spiParams.dataSize = 8;       // 8-bit data size
        spiParams.bitRate=5000000;
        spiParams.frameFormat=SPI_POL1_PHA1;
        spi = SPI_open(CONFIG_SPI_0_CONST, &spiParams);
        spi_h=spi;
        if (spi == NULL) {
            while (1);  // SPI_open() failed
        }
	//LCD_GPIO_Init();//初始化GPIO
	
	LCD_RES_Clr();//复位
	CPUdelay(12000*100);
	LCD_RES_Set();
	CPUdelay(12000*100);
	
	LCD_BLK_Set();//打开背光
	CPUdelay(12000*100);
	
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	CPUdelay(12000*120);             //Delay 120ms
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);
	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29); 
} 








