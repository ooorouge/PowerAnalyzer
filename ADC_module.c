#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_adc.h"

#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

#include "global values.h"
#include "calculate_module.h"
#include "Event.h"
#include "WDT.h"

float u1_temp[50];//用来存储
float u2_temp[50];
float u3_temp[50];
float i1_temp[50];
float i2_temp[50];
float i3_temp[50];

//static float unit = 3.3f / 4095;
//static float unit_u = 1/ 1.6f *1.414213562f;
//static float unit_i = 250/1.6f*1.414213562f;
static const float unit_u1 = 3.28922f/ 4095 * 250/1.6f*1.414213562f;
static const float unit_i1 = 3.28922f/ 4095 * 1/ 1.6f *1.414213562f;
//static const float unit_u1 =  4095 * 250*1.414213562f;
//static const float unit_i1 =  4095 * 1 *1.414213562f;

float unit_bias_u1 = -1.65f *250/1.6f*1.414213562f;
float unit_bias_u2 = -1.65f *250/1.6f*1.414213562f;
float unit_bias_u3 = -1.65f *250/1.6f*1.414213562f;

float unit_bias_i1 = -1.65f * 1/ 1.6f *1.414213562f;
float unit_bias_i2 = -1.65f * 1/ 1.6f *1.414213562f;
float unit_bias_i3 = -1.65f * 1/ 1.6f *1.414213562f;

// float rms_50(const float data[50])
// {
//     float total = 0;
//     int count;
//     for(count = 0;count < 50;count++)
//     {
//         total += data[count] * data[count];
//     }
//     return sqrtf(total/50);
// }


float points_50_square[3];




static int32_t pui32ADC0Value[8];//or 6??
uint32_t flag_200ms;

uint32_t count_2560;

uint32_t count_512;

uint32_t count_50;

unsigned short flag_event_detect;
    // if(count_512<51)
    //     data_first=u1[coun_nt_51<83)
    //     data_first=u1_temp[count_512-51];
    // if(count_512>=83)
    //     data_first=u1[count_512-51];
    // oneperiod_rms=sqrtf((oneperiod_rms*oneperiod_rms*51-data_first*data_first
    //                       +pui32ADC0Value[0]*pui32ADC0Value[0])/51);

void ADC0Sequence0Handler(void)
{
    ADCIntDisable(ADC0_BASE, 0);

    ADCIntClear(ADC0_BASE, 0);

    ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC0Value);
    if(count_512 < 50)
    {
        //u1_temp[count_512] = (pui32ADC0Value[0] * 1 -1.65) * unit_u;//（=/1.6*250*sqrt(2)）
        u1_temp[count_512] = pui32ADC0Value[0] * unit_u1 +unit_bias_u1;
        u2_temp[count_512] = pui32ADC0Value[1] * unit_u1+unit_bias_u2;
        u3_temp[count_512] = pui32ADC0Value[2] * unit_u1 +unit_bias_u3;
        //i1_temp[count_512] = (pui32ADC0Value[3] * unit -1.65) * unit_i;//（=/ 1.6 * 1*sqrt(2)）
        i1_temp[count_512] = pui32ADC0Value[3] * unit_i1 +unit_bias_i1;
        i2_temp[count_512] = pui32ADC0Value[4] * unit_i1 +unit_bias_i2;
        i3_temp[count_512] = pui32ADC0Value[5] * unit_i1 +unit_bias_i3;
    }
    else 
    {
        u1[count_512] = pui32ADC0Value[0] * unit_u1 +unit_bias_u1;
        u2[count_512] = pui32ADC0Value[1] * unit_u1+unit_bias_u2;//（=/1.6*250）
        u3[count_512] = pui32ADC0Value[2] * unit_u1 +unit_bias_u3;
        i1[count_512] = pui32ADC0Value[3] * unit_i1 +unit_bias_i1;//（=/ 1.6 * 1）
        i2[count_512] = pui32ADC0Value[4] * unit_i1 +unit_bias_i2;
        i3[count_512] = pui32ADC0Value[5] * unit_i1 +unit_bias_i3;
    }

    if(count_512 == 50)
    {
        int i;
        for(i = 0;i < 50;i++)
        {
            u1[i] = u1_temp[i];
            u2[i] = u2_temp[i];
            u3[i] = u3_temp[i];
            i1[i] = i1_temp[i];
            i2[i] = i2_temp[i];
            i3[i] = i3_temp[i];
        }
    }
//判断电压中断////////////////////////////
//extern void rms_50_pick(int,const float*,const float*);//0,1,2 phase

points_50_square[0] = sqrtf(rms_50_pick(count_512,u1,u1_temp)/50);
// rms_50_pick(1,u2,u2_temp);
// rms_50_pick(2,u3,u3_temp);
//判断电压中断///////////////////
    count_512++;
    count_2560++;//电压中断检测用，不归零

    if(count_512 == 512)
        {
                count_512 = 0;
                flag_200ms=1;
        }
    if(count_2560 %25 == 0)
        flag_event_detect  = 1;

    if(count_2560 % 2559 == 0)
        {
            time_count++;
            //WTIMER0_feed();
        }
    ADCIntEnable(ADC0_BASE, 0);
}


void TIMER0_init()
{


    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC_UP);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/2560 -1);

    TimerControlTrigger(TIMER0_BASE,TIMER_A, true);
    TimerControlStall(TIMER0_BASE,TIMER_A, true);

    TimerADCEventSet(TIMER0_BASE, TIMER_ADC_TIMEOUT_A);

    TimerEnable(TIMER0_BASE, TIMER_A);
}
void ADC0_init()
{
    TIMER0_init();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_TIMER, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 );//PE3
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1 );//PE2
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH2 );//PE1
    ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH4 );//PD3
    ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH5 );//PD2
    ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH6 | ADC_CTL_IE | ADC_CTL_END);//PD1

    ADCIntRegister(ADC0_BASE, 0, ADC0Sequence0Handler);
    ADCIntEnable(ADC0_BASE, 0);
    IntEnable(INT_ADC0SS0);
    //ADCHardwareOversampleConfigure(ADC0_BASE, 16);//????
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCIntClear(ADC0_BASE, 0);
    

}


