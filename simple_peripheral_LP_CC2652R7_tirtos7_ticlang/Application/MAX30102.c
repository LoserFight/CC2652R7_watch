#include "MAX30102.h"

void max30102_write_reg(uint8_t uch_addr,uint8_t uch_data){
    i2c_write_one_byte(MAX30102ADDR,uch_addr,uch_data);
}

void max30102_read_reg(uint8_t uch_addr,uint8_t* uch_data){
    i2c_read_one_byte(MAX30102ADDR, uch_addr, uch_data);
}

/*
 * @brief 初始化max30102的寄存器
 *
 */
void max30102_init(){

    //max30102_write_reg(RES_MODE_CONFIGURATION,0x40); //reset

    //中断配置
    max30102_write_reg(RES_INTERRUPT_ENABLE_1,0x80);
    max30102_write_reg(RES_INTERRUPT_ENABLE_2,0x00);


    //When starting a new SpO2 or heart rate conversion,
    //it is recommended to first clear the FIFO_WR_PTR, OVF_COUNTER,
    //and FIFO_RD_PTR registers to all zeroes (0x00) to ensure the FIFO is empty and in a known state.
    max30102_write_reg(RES_FIFO_WRITE_POINTER,0x00);
    max30102_write_reg(RES_OVERFLOW_COUNTER,0x00);
    max30102_write_reg(RES_FIFO_READ_POINTER,0x00);

    //FIFO config
    max30102_write_reg(RES_FIFO_CONFIGURATION,0x4f); //4 平均 禁止新数据覆盖FIFO；在队列存有32-16个数据时中断
    max30102_write_reg(RES_MODE_CONFIGURATION,0x03); //0x02 Red only 0x03 Red and IR

    //max30102_write_reg(RES_SPO2_CONFIGURATION,0x27); //adc 4096nA 100Hz Sample ,411us integration time
    max30102_write_reg(RES_SPO2_CONFIGURATION,0x27); //adc 4096nA 100Hz Sample ,411us integration time
    //设置两个led的亮度(电流mA)
//    max30102_write_reg(RES_LED_PLUSE_AMPLITUDE_1,0x24);
//
//    max30102_write_reg(RES_LED_PLUSE_AMPLITUDE_2,0x24);
        max30102_write_reg(RES_LED_PLUSE_AMPLITUDE_1,0x3F);

        max30102_write_reg(RES_LED_PLUSE_AMPLITUDE_2,0x3F);
    max30102_write_reg(RES_PROXIMITY_MODE_LED_PLUSE_AMPLITUDE,0x7f);

    max30102_getState(); //clear INT FLAG


}

uint8_t max30102_getState(){
    uint8_t data1=0,data2=0;
    i2c_read_one_byte(MAX30102ADDR,RES_INTERRUPT_STATUS_1,&data1);
    i2c_read_one_byte(MAX30102ADDR,RES_INTERRUPT_STATUS_2,&data2);
    return data1|data2;
}
/*
 * @brief set SHDN put it into a power-save mode,all registers retain their
 * values, and write/read operations function as normal.
 * All interrupts are cleared to zero in this mode.
 */
void max30102_ON(){
    uint8_t config=0;
    i2c_read_one_byte(MAX30102ADDR,RES_MODE_CONFIGURATION,&config);
    config&=~(0x80);
    max30102_write_reg(RES_MODE_CONFIGURATION,config);
}

/*
 * @brief cancel SHDN
 */
void max30102_OFF(){
    uint8_t config=0;
    i2c_read_one_byte(MAX30102ADDR,RES_MODE_CONFIGURATION,&config);
    config|=(0x80);
    max30102_write_reg(RES_MODE_CONFIGURATION,config);
}

/*
 * @brief reset all reg to POP state
 */
void max30102_RESET(){
    max30102_write_reg(RES_MODE_CONFIGURATION,0x40);
    uint8_t temp;
    do{
        i2c_read_one_byte(MAX30102ADDR,RES_MODE_CONFIGURATION,&temp);
    }while(temp&0x40);
}

uint8_t max30102_getUnreadSampleCount()
{
    uint8_t wr = 0, rd = 0;
    i2c_read_one_byte(MAX30102ADDR,RES_FIFO_WRITE_POINTER,&wr);

    i2c_read_one_byte(MAX30102ADDR,RES_FIFO_READ_POINTER,&rd);
    if ((wr - rd) < 0)
        return wr - rd + 32;
    else
        return wr - rd;
}


/*
 * @brief read the FIFO data
 * need least 6 uint to read
 * @param red_led pointer that stores 18bit adc of Current for red led.
 * @param ir_led pointer that stores 18bit adc of Current for ir led.
 */
void max30102_read_FIFO(uint32_t *red_led,uint32_t *ir_led,uint8_t NUM_SAMPLES_TO_READ){
//    *red_led=0;
//    *ir_led=0;
    //clear the INT and get the INT FLAG
    //uint8_t status=max30102_getState();


    //uint8_t samCount=max30102_getUnreadSampleCount();
    //if (samCount<6) return ;


    unsigned char IIC_data[6*12];
//    for(uint8_t i=0;i<6*NUM_SAMPLES_TO_READ;i++){
//        i2c_read_one_byte(MAX30102ADDR,RES_FIFO_DATA_REGISTER,&(IIC_data[i]));
//    }
    i2c_read_multi_byte(MAX30102ADDR,RES_FIFO_DATA_REGISTER,IIC_data,6*NUM_SAMPLES_TO_READ);
    for(uint8_t i=0;i<NUM_SAMPLES_TO_READ;i++){

        uint32_t un_temp;
        ir_led[i]=0;
        red_led[i]=0;
        un_temp=(uint32_t)IIC_data[0+6*i];
        un_temp<<=16;
        red_led[i]+=un_temp;
        un_temp=(uint32_t)IIC_data[1+6*i];
        un_temp<<=8;
        red_led[i]+=un_temp;
        un_temp=(uint32_t)IIC_data[2+6*i];
        red_led[i]+=un_temp;

        un_temp=(uint32_t)IIC_data[3+6*i];
        un_temp<<=16;
        ir_led[i]+=un_temp;
        un_temp=(uint32_t)IIC_data[4+6*i];
        un_temp<<=8;
        ir_led[i]+=un_temp;
        un_temp=(uint32_t)IIC_data[5+6*i];
        ir_led[i]+=un_temp;

        red_led[i]&=0x03FFFF; //只要低18位
        ir_led[i]&=0x03FFFF;

    }

//    uint32_t un_temp;
//    un_temp=(uint32_t)IIC_data[0];
//    un_temp<<=16;
//    *red_led+=un_temp;
//    un_temp=(uint32_t)IIC_data[1];
//    un_temp<<=8;
//    *red_led+=un_temp;
//    un_temp=(uint32_t)IIC_data[2];
//    *red_led+=un_temp;
//
//    un_temp=(uint32_t)IIC_data[3];
//    un_temp<<=16;
//    *ir_led+=un_temp;
//    un_temp=(uint32_t)IIC_data[4];
//    un_temp<<=8;
//    *ir_led+=un_temp;
//    un_temp=(uint32_t)IIC_data[5];
//    *ir_led+=un_temp;
//
//    *red_led&=0x03FFFF; //只要低18位
//    *ir_led&=0x03FFFF;




}
