//******************************************************************************
//name:         GUA_RTC.h
//introduce:    ����Զ����RTC����ͷ�ļ�
//author:       ����Ĵ����
//email:        897503845@qq.com
//QQ group      ���BLE֮CC2640(557278427)
//changetime:   2016.09.04
//******************************************************************************
#ifndef _GUA_RTC_H_
#define _GUA_RTC_H_

/*********************ͷ�ļ�************************/
#include "utc_clock.h"

/*********************��������************************/
extern void GUA_RTC_Init(void);
extern void GUA_RTC_Set(UTCTimeStruct *pGUA_Timer);
extern void GUA_RTC_Get(UTCTimeStruct *pGUA_Timer);

#endif

