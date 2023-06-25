#ifndef __CC26XXI2C_H
#define __CC26XXI2C_H
#include "ti/sysbios/knl/Task.h"
#include <ti/display/Display.h>
/* I2C */
//#define CC2640R2_LAUNCHXL_I2C0_SCL0             IOID_4    //i2c SCL时钟线
//#define CC2640R2_LAUNCHXL_I2C0_SDA0             IOID_5    //i2c SDA数据线

/*!
 *  @def    CC2640R2_LAUNCHXL_I2CName
 *  @brief  Enum of I2C names
 */
//typedef enum user_CC2640R2_LAUNCHXL_I2CName {
//    user_CC2640R2_LAUNCHXL_I2C0 = 0,
//
//    user_CC2640R2_LAUNCHXL_I2CCOUNT
//} user_CC2640R2_LAUNCHXL_I2CName;

void i2c_init(void);
void i2c_write_one_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t Data);
void i2c_write_multi_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t *pData, uint8_t Len);
uint8_t i2c_read_one_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t *pData);
uint8_t i2c_read_multi_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t *pData, uint8_t Len);
void i2c_write_two_byte_addr(uint8_t SlaveAddr,uint16_t Cmd,uint8_t *pData, uint8_t Len );
#endif
