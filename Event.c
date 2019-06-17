#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

//#include "ADC_module.h"
//#include "global values.h"
//#include "calculate_module.h"


//float oneperiod_rms=3;

// int Second=0,Minutes=0,Hour=0,Day=1,Month=1,Year=0;
// float Time=0,mSecond=0;
// float TimeDown,TimeUp,TimeDown1,TimeUp1;;

// int UDownHour[3],UDownMinutes[3],UZeroHour[3],UZeroMinutes[3];

// float UDownSecond[3],UZeroSecond[3];
// float UDownEvent[3];//记录下降持续时间
// float UZeroEvent[3];//记录中断持续时间

//int flagEve=1;
int flagDown=0;
int flagZero=0;
// int EveCount[7]={0,0,0,0,0,0,0};
// int i=0;
const float standard_voltage = 220;

extern float points_50_square[3];
// float u1_rms_temp[10]={4,3,4,3,3,3.1,2.9,2.8,4,4};
// float u2_rms_temp[10];
// float u3_rms_temp[10];

time_t time_count;

static uint32_t count_zd;
static uint32_t count_zj;

char time_zj_1[9] ="00:00:00";
char time_zj_2[9] ="00:00:00";
char time_zj_3[9] ="00:00:00";
char time_zd_1[9] ="00:00:00";
char time_zd_2[9] ="00:00:00";
char time_zd_3[9] ="00:00:00";

time_t time_zj_start;//记录骤降
time_t time_zd_start;

uint32_t time_zj_lasting[4];//记录骤降[0]缓存
uint32_t time_zd_lasting[4];

uint8_t flag_zd_event_over;
uint8_t flag_zj_event_over;

uint8_t count_50_disposible[3];//仅使用一次

static float points_50_first[3];
// void UDownJudge(float points_50_rms)  //电压骤降单相判断 第m相
// {
//     float oneperiod_rms =sqrtf(points_50_rms/50);

//     if((oneperiod_rms < 0.8f*standard_voltage) && flagDown==0)//电压骤降判断
//     {
//      flagDown=1;
//     }

//     if((oneperiod_rms >= 0.8f*standard_voltage) && flagDown == 1)//电压回复判断
//     {
//       TimeUp=Minutes*60+Second+mSecond/1000;
//       UDownEvent[EveCount[m]]=TimeUp-TimeDown;
//          EveCount[m]++;
//          flagDown=0;
//      if(EveCount[m]==3)EveCount[m]=0;
//     }
//     if((oneperiod_rms <= 0.01f*standard_voltage) && flagZero == 0)//电压中断判断
//     {
//      // UZeroHour[EveCount[m+3]]=Hour;
//      // UZeroMinutes[EveCount[m+3]]=Minutes;
//      // UZeroSecond[EveCount[m+3]]=Second*1000+mSecond/1000;
//      // TimeDown1=Minutes*60+Second+mSecond/1000;
//      flagZero=1;
//     }
//     if((oneperiod_rms > 0.01f*standard_voltage) && flagZero == 1)//电压回复判断
//     {
//       // TimeUp1=Minutes*60+Second+mSecond/1000;
//       // UZeroEvent[EveCount[m+3]]=TimeUp1-TimeDown1;
//          // EveCount[m+3]++;
//      flagZero=0;
//      // if(EveCount[m+3]==3)EveCount[m+3]=0;
//     }
// }
float rms_50_pick(uint32_t count_512,const float data[],const float data_temp[])//0,1,2 phase
{
    float temp = 0;
    if(count_50_disposible[0] <50)
        {
            temp += data_temp[count_512]* data_temp[count_512];
            count_50_disposible[0]++;
        }
    if(count_50_disposible[0] == 50)
         {
            count_50_disposible[0] = 100;
            points_50_first[0] = data_temp[0];
        }
    if(count_512 < 50 && count_50_disposible[0] == 100)
        {
            temp +=  - points_50_first[0] * points_50_first[0] +   data_temp[count_512]* data_temp[count_512];
            if(count_512 != 49)
                points_50_first[0] = data_temp[count_512+513-50];
            else
                points_50_first[0] = data_temp[0];
        }
    else if(count_512 >= 50 && count_50_disposible[0] == 100)
        {
            temp +=  - points_50_first[0] * points_50_first[0] +   data[count_512]* data[count_512];
            points_50_first[0] = data_temp[count_512 - 49];
        }
        return temp;
}
void UDownJudge(float points_50_rms)  //电压骤降单相判断
{
    //float oneperiod_rms =sqrtf(points_50_rms/50);
    float oneperiod_rms =points_50_rms;
    if((oneperiod_rms < 0.8f*standard_voltage) && flagDown==0)//电压骤降判断
    {
      flagDown=1;
      time_zj_start = time_count;//记录开始时间
    }
    if((oneperiod_rms >= 0.8f*standard_voltage) && flagDown == 1)//电压回复判断
    {
      flagDown = 0;
      time_zj_lasting[0] = count_zj;//记录持续时间
      count_zj  =0;
      flag_zj_event_over = 1; 
    }
    if((oneperiod_rms <= 0.01f*standard_voltage) && flagZero == 0)//电压中断判断
    {
      flagZero=1;
      time_zd_start = time_count;
    }
    if((oneperiod_rms > 0.01f*standard_voltage) && flagZero == 1)//电压回复判断
    {
      flagZero=0;
      time_zd_lasting[0] = count_zd;
      count_zd = 0;
      flag_zd_event_over = 1; 
    }
}
// void Timer1AIntHandler()
// {
//  TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
//  //Calendar();
//     time_count
//   if(flagEve&&(int)mSecond%100==0)
//  {
//      if((oneperiod_rms-standard_voltage)<0.01f*oneperiod_rms)
//      flagEve=0;
//      standard_voltage=oneperiod_rms;

//  }
//  if(flagEve==0)
//          {
//          UDownJudge(1);
//          }
// }
void zd_zj_dectect()
{
  //TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  //Calendar();
  //count_2560++;
  //if(count_2560 == 2560) count_2560 = 0;
  UDownJudge(points_50_square[0]);// check every half period == 10ms

  if(flagDown == 1) count_zj++;     //lasting time 
  if(flagZero == 1) count_zd++;
  if(flag_zj_event_over == 1) 
  {
        int i;
        for(i=0;i<8;i++)
          {
            time_zj_3[i]=time_zj_2[i];
            time_zj_2[i]=time_zj_1[i];
          }
          time_zj_lasting[3] = time_zj_lasting[2];
          time_zj_lasting[2] = time_zj_lasting[1];
          time_zj_lasting[1] = time_zj_lasting[0];
        struct tm *tblock = __localtime32(&time_zd_start);
        strftime(time_zj_1,8,"%X",tblock);

        flag_zj_event_over  = 0;//处理完毕
  }
    if(flag_zd_event_over == 1) 
  {
        int i;
        for(i=0;i<8;i++)
          {
            time_zd_3[i]=time_zd_2[i];
            time_zd_2[i]=time_zd_1[i];
          }
          time_zd_lasting[3] = time_zd_lasting[2];
          time_zd_lasting[2] = time_zd_lasting[1];
          time_zd_lasting[1] = time_zd_lasting[0];
        struct tm *tblock = __localtime32(&time_zd_start);
        strftime(time_zd_1,8,"%X",tblock);

        flag_zd_event_over  =0;
  }


}
void zd_zj_dectect_init()
{
    // SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    // TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC );

    // TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet()/1000-1);// 时钟周期1ms

    // TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1AIntHandler);

    // IntMasterEnable();
    // TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT );
    // IntEnable(INT_TIMER1A);

    // TimerEnable(TIMER1_BASE, TIMER_A);

        //char time[] =__DATE__;
    time_count = time(NULL)+14*3600;//1900开始的秒数

}
