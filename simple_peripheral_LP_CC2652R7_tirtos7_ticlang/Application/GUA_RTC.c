//******************************************************************************
//name:         GUA_RTC.c
//introduce:    香瓜自定义的RTC驱动
//author:       甜甜的大香瓜
//email:        897503845@qq.com
//QQ group      香瓜BLE之CC2640(557278427)
//changetime:   2016.09.04
//******************************************************************************
#include "GUA_RTC.h"

//******************************************************************************
//name:             GUA_RTC_Init
//introduce:        香瓜的RTC初始化
//parameter:        none
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜BLE之CC2640(557278427)
//changetime:       2016.09.04
//******************************************************************************
void GUA_RTC_Init(void)
{
  //初始化UTC.
  UTC_init();
}
//******************************************************************************
//name:             GUA_RTC_Set
//introduce:        香瓜的RTC设置时间函数
//parameter:        pGUA_Timer：传入的时间
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜BLE之CC2640(557278427)
//changetime:       2016.09.04
//******************************************************************************
void GUA_RTC_Set(UTCTimeStruct *pGUA_Timer)
{
  UTCTimeStruct SetTime;
  UTCTime SetTime_seconds;

  //转换数据
  SetTime.year = pGUA_Timer->year;
  SetTime.month = pGUA_Timer->month - 1;
  SetTime.day = pGUA_Timer->day - 1;
  SetTime.hour = pGUA_Timer->hour - 1;
  SetTime.minutes = pGUA_Timer->minutes;
  SetTime.seconds = pGUA_Timer->seconds;

  //将时间转换为秒
  SetTime_seconds = UTC_convertUTCSecs(&SetTime);

  //设置时间
  UTC_setClock(SetTime_seconds);
}

//******************************************************************************
//name:             GUA_RTC_Get
//introduce:        香瓜的RTC获取时间函数
//parameter:        pGUA_Timer：传入的时间
//return:           none
//author:           甜甜的大香瓜
//email:            897503845@qq.com
//QQ group          香瓜BLE之CC2640(557278427)
//changetime:       2016.09.04
//******************************************************************************
void GUA_RTC_Get(UTCTimeStruct *pGUA_Timer)
{
  UTCTimeStruct GetTime;

  //获取当前数据
  UTC_convertUTCTime(&GetTime, UTC_getClock());

  //抓换数据
  pGUA_Timer->year = GetTime.year;
  pGUA_Timer->month = GetTime.month + 1;
  pGUA_Timer->day = GetTime.day + 1;
  pGUA_Timer->hour = GetTime.hour + 1;
  pGUA_Timer->minutes = GetTime.minutes;
  pGUA_Timer->seconds = GetTime.seconds;
}

