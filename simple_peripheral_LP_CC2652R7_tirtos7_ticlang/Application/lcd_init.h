#ifndef __LCD_INIT_H
#define __LCD_INIT_H

//#include "sys.h"
#include <stdint.h>
#include "ti_drivers_config.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#define LCD_W 240
#define LCD_H 240



//-----------------LCD�˿ڶ���---------------- 

//#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET)//SCL=SCLK
//#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET)

//#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_RESET)//SDA=MOSI
//#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7, GPIO_PIN_SET)

#define LCD_RES_Clr()  GPIO_write(CONFIG_GPIO_RES_tft, 0);
#define LCD_RES_Set()  GPIO_write(CONFIG_GPIO_RES_tft, 1);

#define LCD_DC_Clr()   GPIO_write(CONFIG_GPIO_CSDC, 0);
#define LCD_DC_Set()   GPIO_write(CONFIG_GPIO_CSDC, 1);

#define LCD_BLK_Clr()  asm("nop")
#define LCD_BLK_Set()  asm("nop")





//void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void spi_write(const void *data, uint32_t size);
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




