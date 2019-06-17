#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
static uint8_t flag_2s;
static uint8_t flag_10s;
void LED_init()
{
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
       GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,1<<4);

            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
       GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);
            GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,1<<6);
}
void LED_2s_blink()
{
        flag_2s = 1 - flag_2s;
        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,flag_2s<<4);
        //GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,1<<4);
}
void LED_10s_blink()
{
        flag_10s = 1 - flag_10s;
        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,flag_10s<<6);
        //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_6,1<<6);
}
            





















