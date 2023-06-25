//******************************************************************************
//name:         GUA_RTC.c
//introduce:    ����Զ����RTC����
//author:       ����Ĵ����
//email:        897503845@qq.com
//QQ group      ���BLE֮CC2640(557278427)
//changetime:   2016.09.04
//******************************************************************************
#include "GUA_RTC.h"

//******************************************************************************
//name:             GUA_RTC_Init
//introduce:        ��ϵ�RTC��ʼ��
//parameter:        none
//return:           none
//author:           ����Ĵ����
//email:            897503845@qq.com
//QQ group          ���BLE֮CC2640(557278427)
//changetime:       2016.09.04
//******************************************************************************
void GUA_RTC_Init(void)
{
  //��ʼ��UTC.
  UTC_init();
}
//******************************************************************************
//name:             GUA_RTC_Set
//introduce:        ��ϵ�RTC����ʱ�亯��
//parameter:        pGUA_Timer�������ʱ��
//return:           none
//author:           ����Ĵ����
//email:            897503845@qq.com
//QQ group          ���BLE֮CC2640(557278427)
//changetime:       2016.09.04
//******************************************************************************
void GUA_RTC_Set(UTCTimeStruct *pGUA_Timer)
{
  UTCTimeStruct SetTime;
  UTCTime SetTime_seconds;

  //ת������
  SetTime.year = pGUA_Timer->year;
  SetTime.month = pGUA_Timer->month - 1;
  SetTime.day = pGUA_Timer->day - 1;
  SetTime.hour = pGUA_Timer->hour - 1;
  SetTime.minutes = pGUA_Timer->minutes;
  SetTime.seconds = pGUA_Timer->seconds;

  //��ʱ��ת��Ϊ��
  SetTime_seconds = UTC_convertUTCSecs(&SetTime);

  //����ʱ��
  UTC_setClock(SetTime_seconds);
}

//******************************************************************************
//name:             GUA_RTC_Get
//introduce:        ��ϵ�RTC��ȡʱ�亯��
//parameter:        pGUA_Timer�������ʱ��
//return:           none
//author:           ����Ĵ����
//email:            897503845@qq.com
//QQ group          ���BLE֮CC2640(557278427)
//changetime:       2016.09.04
//******************************************************************************
void GUA_RTC_Get(UTCTimeStruct *pGUA_Timer)
{
  UTCTimeStruct GetTime;

  //��ȡ��ǰ����
  UTC_convertUTCTime(&GetTime, UTC_getClock());

  //ץ������
  pGUA_Timer->year = GetTime.year;
  pGUA_Timer->month = GetTime.month + 1;
  pGUA_Timer->day = GetTime.day + 1;
  pGUA_Timer->hour = GetTime.hour + 1;
  pGUA_Timer->minutes = GetTime.minutes;
  pGUA_Timer->seconds = GetTime.seconds;
}

