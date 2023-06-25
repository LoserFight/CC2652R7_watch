//******************************************************************************
//name:         GUA_RTC.h
//introduce:    香瓜自定义的RTC驱动头文件
//author:       甜甜的大香瓜
//email:        897503845@qq.com
//QQ group      香瓜BLE之CC2640(557278427)
//changetime:   2016.09.04
//******************************************************************************
#ifndef _GUA_RTC_H_
#define _GUA_RTC_H_

/*********************头文件************************/
#include "utc_clock.h"

/*********************函数声明************************/
extern void GUA_RTC_Init(void);
extern void GUA_RTC_Set(UTCTimeStruct *pGUA_Timer);
extern void GUA_RTC_Get(UTCTimeStruct *pGUA_Timer);

#endif

