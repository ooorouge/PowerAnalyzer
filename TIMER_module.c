#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"

#include "inc/hw_sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "global values.h"

//unsigned long  count;//10s内上升沿个数

static unsigned long count_time;///计算10s内周期个数
static unsigned long period_ADC;//ADC sampling frequency 所对应定时器load
static unsigned long period_50Hz;
static unsigned long count_start;
static unsigned long count_over;
static unsigned long count_last;
static unsigned long period_ADC_last= 50000000/50/51.2;
void WTimer2IntHandler()
{
        TimerIntClear(WTIMER2_BASE, TIMER_CAPA_EVENT);
            /*手动倍频51.2倍*/
        unsigned long timervalue = TimerValueGet(WTIMER2_BASE,TIMER_A);

        if(count_last <  timervalue)//未到达10s
                period_50Hz = timervalue-count_last;
            else
                period_50Hz = 10* SysCtlClockGet() + timervalue-count_last;

        // TimerDisable(WTIMER2_BASE, TIMER_A);//禁用定时器

        // HWREG(WTIMER2_BASE | TIMER_O_TAV) = 0x0;    //定时器计数值清零

        // TimerEnable(WTIMER2_BASE, TIMER_A);//启用定时器
       
        period_ADC = period_50Hz / 51.2f;


        //if((period_ADC_last > period _ADC && (period_ADC_last - period_ADC > 4)) || (period_ADC > period_ADC_last && (period_ADC - period_ADC_last > 4)))
           // {
              //  TimerLoadSet(TIMER0_BASE, TIMER_A, period_ADC - 1);//change the ADC timer's loadset
                //period_ADC_last = period_ADC;
            //}

/*计算频率*/
        count_time++;

        if(count_last >  timervalue)//到达10s
        {
            count_over = count_last;

            frequency_10s = (float)(count_time-1) * SysCtlClockGet() / (count_over - count_start);//=count/time(s)
            count_time = 0;

            count_start = timervalue;
        }
        count_last = timervalue;
}

void WTIMER2_init()//PD0
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER2);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

        GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_0);
        GPIOPinConfigure(GPIO_PD0_WT2CCP0);

        GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);//???

        TimerConfigure(WTIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP | TIMER_CFG_A_ACT_TOINTD);

        TimerControlEvent(WTIMER2_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);

        TimerLoadSet(WTIMER2_BASE, TIMER_A, 10*SysCtlClockGet()-1);

        TimerIntEnable(WTIMER2_BASE, TIMER_CAPA_EVENT);

        IntEnable(INT_WTIMER2A);

        TimerIntRegister(WTIMER2_BASE,TIMER_A,WTimer2IntHandler);

        IntMasterEnable();
        //TimerControlStall(WTIMER2_BASE,TIMER_A,true);

        TimerEnable(WTIMER2_BASE, TIMER_A);//counting start
}
