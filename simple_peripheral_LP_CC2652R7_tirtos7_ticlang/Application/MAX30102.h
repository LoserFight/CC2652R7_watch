#ifndef _MAX30102_H_
#define _MAX30102_H_
// MAX30102 IIC addr
#include "cc26xxi2c.h"
#define MAX30102ADDR 0x57


// register

#define RES_INTERRUPT_STATUS_1 0x00
#define RES_INTERRUPT_STATUS_2 0x01
#define RES_INTERRUPT_ENABLE_1 0x02
#define RES_INTERRUPT_ENABLE_2 0x03
#define RES_FIFO_WRITE_POINTER 0x04
#define RES_OVERFLOW_COUNTER 0x05
#define RES_FIFO_READ_POINTER 0x06
#define RES_FIFO_DATA_REGISTER 0x07
#define RES_FIFO_CONFIGURATION 0x08
#define RES_MODE_CONFIGURATION 0x09
#define RES_SPO2_CONFIGURATION 0x0a
#define RES_LED_PLUSE_AMPLITUDE_1 0x0c
#define RES_LED_PLUSE_AMPLITUDE_2 0x0d
#define RES_PROXIMITY_MODE_LED_PLUSE_AMPLITUDE 0x10
#define RES_MULTI_LED_MODE_CONTROL_1 0x11
#define RES_MULTI_LED_MODE_CONTROL_2 0x12
#define RES_DIE_TEMP_INTEGER 0x1f
#define RES_DIE_TEMP_FRACTION 0x20
#define RES_DIE_TEMPERATURE_CONFIG 0x21
#define RES_PROXIMITY_INTERRUPT_THRESHOLD 0x30
#define RES_REVISION_ID 0xfe
#define RES_PART_ID 0xff

// IIC operations to max30102


void max30102_init();
uint8_t max30102_getState();
void max30102_ON();
void max30102_OFF();
void max30102_RESET();
void max30102_read_FIFO(uint32_t *red_led,uint32_t *ir_led,uint8_t NUM_SAMPLES_TO_READ);
void max30102_write_reg(uint8_t uch_addr,uint8_t uch_data);
void max30102_read_reg(uint8_t uch_addr,uint8_t* uch_data);
uint8_t max30102_getUnreadSampleCount();
#endif
