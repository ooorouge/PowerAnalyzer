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
#include "driverlib/fpu.h"

#include "ADC_module.h"
#include "UART_module.h"
#include "calculate_module.h"
#include "LED.h"
#include "Key.h"
#include "screen.h"
#include "TIMER_module.h"
#include "PWM_module.h"
//#include "WDT.h"
#include "Event.h"

void system_init()
{
    FPUEnable();
    FPULazyStackingEnable();
    ConfigureUART();
    UART_select_menu();
    key_init();
    ADC0_init();
    calculate_init();
    WTIMER2_init();
    Init_M0PWM4();
    LED_init();
    //WTIMER0_init();

    zd_zj_dectect_init();

}

void main()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    system_init();

    while(1)
    {
        if(flag_200ms == 1)
        {
            flag_200ms = 0;
            calculate_200ms(count_50 % 10);
            if(count_50 == 50) 
                count_50 = 0;

            if(count_50 % 5  == 0) //1s
                calculate_1s(count_50 / 5, (count_50 / 5 + 1) % 2);

            if(count_50 % 10  == 0) //2s
            {
                calculate_2s(count_50 / 10);
                LED_2s_blink();
                if(count_50 != 0 && screen_flag==1)
                    {screen(screen_line,screen_row);
                    }
            }

            if(count_50  == 0) //10s??
            {
                calculate_10s();
                LED_10s_blink();
                if(screen_flag==1)
                    {screen(screen_line,screen_row);
                    }
            }

            count_50++;
        }
         if(flag_UART)
                {
                    UART_polling();
                }

          if(flag_up + flag_down + flag_enter + flag_back != 0)
             {
                 key_polling();
             }
            // WTIMER0_feed();
             if(flag_event_detect == 1)
             {
                zd_zj_dectect();
                flag_event_detect = 0;
             }
    }
}



