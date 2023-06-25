#include "cc26xxi2c.h"
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CCC26XX.h>
#include <ti/drivers/power/PowerCC26XX.h>
//#include "sdi_task.h"
#include "icall.h"
#include <stdlib.h>
#include <string.h>

//I2CCC26XX_Object _i2cCC26xxObjects[user_CC2640R2_LAUNCHXL_I2CCOUNT];
//
//const I2CCC26XX_HWAttrsV1 _i2cCC26xxHWAttrs[user_CC2640R2_LAUNCHXL_I2CCOUNT] =
//{
//    {
//        .baseAddr    = I2C0_BASE,
//        .powerMngrId = PowerCC26XX_PERIPH_I2C0,
//        .intNum      = INT_I2C_IRQ,
//        .intPriority = ~0,
//        .swiPriority = 0,
//        .sdaPin      = CC2640R2_LAUNCHXL_I2C0_SDA0,
//        .sclPin      = CC2640R2_LAUNCHXL_I2C0_SCL0,
//    }
//};
//
//const I2C_Config cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2CCOUNT] =
//{
//    {
//        .fxnTablePtr = &I2CCC26XX_fxnTable,
//        .object      = &_i2cCC26xxObjects[user_CC2640R2_LAUNCHXL_I2C0],
//        .hwAttrs     = &_i2cCC26xxHWAttrs[user_CC2640R2_LAUNCHXL_I2C0]
//    },
//};

//I2C 句柄及参数
extern I2C_Handle cc2652_I2C_Handle;
extern I2C_Params cc2652_I2C_Params;
extern Display_Handle dispHandle;
extern void Display_doPrintf(Display_Handle handle, uint8_t line, uint8_t column, const char *fmt, ...);
//static I2C_Transaction transaction;

//初始化I2C
void i2c_init(void)
{
//  I2C_Params_init(&cc2640_I2C_Params);
//  cc2640_I2C_Params.transferMode = I2C_MODE_BLOCKING; //i2c阻塞模式
//  cc2640_I2C_Params.bitRate = I2C_100kHz; //i2c模式
//  cc2640_I2C_Params.transferCallbackFxn = NULL;
//  cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2C0].fxnTablePtr->initFxn((I2C_Handle)&cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2C0]);
//  cc2640_I2C_Handle = cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2C0].fxnTablePtr->openFxn((I2C_Handle)&cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2C0],&cc2640_I2C_Params);
//  if (cc2640_I2C_Handle == NULL)
//  {
//
//    //SDITask_sendToUART("i2c init fail\r\n",15);
//    for(;;);
//  }
}

//i2c写入数据
static void i2c_write(size_t slaveAddress,uint8_t *write_data,size_t len)
{
  I2C_Transaction transaction = {0};
  transaction.targetAddress = slaveAddress;
  transaction.writeBuf = write_data;
  transaction.writeCount = len;
  transaction.readBuf = NULL;
  transaction.readCount = 0;
  transaction.arg = NULL;
  //cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2C0].fxnTablePtr->transferFxn(cc2640_I2C_Handle,&transaction);
  I2C_transfer(cc2652_I2C_Handle, &transaction);
}

//i2c读取数据
static void i2c_read(uint8_t slaveAddress,uint8_t *read_data,uint8_t len)
{
  I2C_Transaction transaction = {0};
  transaction.targetAddress = slaveAddress;
  transaction.writeBuf = NULL;
  transaction.writeCount = 0;
  transaction.readBuf = read_data;
  transaction.readCount = len;
  transaction.arg = NULL;
  //if (cc26xxI2C_config[user_CC2640R2_LAUNCHXL_I2C0].fxnTablePtr->transferFxn(cc2640_I2C_Handle,&transaction))
  if (I2C_transfer(cc2652_I2C_Handle, &transaction))
  {
      //
    //SDITask_sendToUART("i2c read success\r\n",18);
  }
}

//i2c写一个字节数据
void i2c_write_one_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t Data)
{
  uint8_t buf[2] = {0};
  buf[0] = Cmd;
  buf[1] = Data;
  i2c_write(SlaveAddr,buf,sizeof(buf));
}

//i2c写多个字节
void i2c_write_multi_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t *pData, uint8_t Len)
{
  uint8_t *buf = ICall_malloc(Len + 1);
  buf[0] = Cmd;
  memcpy(buf+1,pData,Len);
  i2c_write(SlaveAddr,buf,sizeof(buf));
  ICall_free(buf);
  buf = NULL;
}

//i2c读一个字节数据
uint8_t i2c_read_one_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t *pData)
{
//  i2c_write(SlaveAddr,&Cmd,1);
//  i2c_read(SlaveAddr,pData,1);
    I2C_Transaction transaction = {0};
    transaction.targetAddress = SlaveAddr;
    transaction.writeBuf = &Cmd;
    transaction.writeCount = 1;
    transaction.readBuf = pData;
    transaction.readCount = 1;
    //transaction.arg = NULL;
    if(I2C_transfer(cc2652_I2C_Handle, &transaction)){
        //Display_doPrintf(dispHandle, 0, 0, "i2c read reg:%x value:%x,succeed!\n",Cmd,*pData);
        return 0;
    }
    else{
        //Display_doPrintf(dispHandle, 0, 0, "i2c read reg:%x,fail!\n",Cmd);
        //i2cErrorHandler(&transaction, dispHandle);
        return 1;
    }
}

//i2c读多个字节数据
uint8_t i2c_read_multi_byte(uint8_t SlaveAddr, uint8_t Cmd, uint8_t *pData, uint8_t Len)
{
//  i2c_write(SlaveAddr,&Cmd,1);
//  i2c_read(SlaveAddr,pData,Len);
    I2C_Transaction transaction = {0};
    transaction.targetAddress = SlaveAddr;
    transaction.writeBuf = &Cmd;
    transaction.writeCount = 1;
    transaction.readBuf = pData;
    transaction.readCount = Len;
    //transaction.arg = NULL;
    if(I2C_transfer(cc2652_I2C_Handle, &transaction)){
        //Display_doPrintf(dispHandle, 0, 0, "i2c multi read reg:%x value:%x,succeed!\n",Cmd,*pData);
        return 0;
    }
    else{
        //i2cErrorHandler(&transaction, dispHandle);
        return 1;
    }
}

//写入16bit地址数据
void i2c_write_two_byte_addr(uint8_t SlaveAddr,uint16_t Cmd,uint8_t *pData, uint8_t Len )
{
  uint8_t addr[2] = {0};
  addr[0] = Cmd >> 8;
  addr[1] = Cmd;
  i2c_write(SlaveAddr,addr,2);
  i2c_write(SlaveAddr,pData,Len);
}
