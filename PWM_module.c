#include <stdbool.h>
#include <stdint.h>

#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

static uint32_t PWM_frequency = 64000;

//void Init_M0PWM4()//PE4//CLOCK
//{
//        SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
//
//        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
//
//        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
//
//        GPIOPinConfigure(GPIO_PE4_M0PWM4);
//
//        GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
//
//        //PWMGenConfigure(PWM0_BASE, PWM_GEN_0,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_SYNC | PWM_GEN_MODE_GEN_SYNC_LOCAL);
//        PWMGenConfigure(PWM0_BASE, PWM_GEN_2,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC );
//
//        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/PWM_frequency);
//
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, SysCtlClockGet()/PWM_frequency/2);
//
//        PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
//
//        //PWMSyncTimeBase(PWM0_BASE, PWM_GEN_0_BIT | PWM_GEN_1_BIT);
//        PWMGenEnable(PWM0_BASE, PWM_GEN_2);
//
//        // PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_ZERO);
//        // PWMGenIntRegister(PWM0_BASE, PWM_GEN_0,PWMGenIntHandler);
//        // PWMIntEnable(PWM0_BASE, PWM_INT_GEN_0);
//        // IntMasterEnable();
//}
void Init_M0PWM4()//PE4//CLOCK
{
        SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

        GPIOPinConfigure(GPIO_PB6_M0PWM0);

        GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

        //PWMGenConfigure(PWM0_BASE, PWM_GEN_0,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_SYNC | PWM_GEN_MODE_GEN_SYNC_LOCAL);
        PWMGenConfigure(PWM0_BASE, PWM_GEN_0,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC );

        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SysCtlClockGet()/PWM_frequency);

        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, SysCtlClockGet()/PWM_frequency/2);

        PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);

        //PWMSyncTimeBase(PWM0_BASE, PWM_GEN_0_BIT | PWM_GEN_1_BIT);
        PWMGenEnable(PWM0_BASE, PWM_GEN_0);

        // PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_ZERO);
        // PWMGenIntRegister(PWM0_BASE, PWM_GEN_0,PWMGenIntHandler);
        // PWMIntEnable(PWM0_BASE, PWM_INT_GEN_0);
        // IntMasterEnable();
}
