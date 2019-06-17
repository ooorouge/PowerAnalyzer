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
#include "inc/hw_i2c.h"
#include "inc/hw_sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/i2c.h"
#include "driverlib/udma.h"
#include "driverlib/fpu.h"
#include "driverlib/rom.h"
//#include <math.h>
#include <stdlib.h>
#include "menu.h"
#include "driverlib/pin_map.h"
#include "uc1701.h"
#include "screen.h"
//*****************************************************************************
#ifdef DEBUG
void__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif
//*****************************************************************************
//
// Global variables
//
//*****************************************************************************
uint16_t screen_line=1,screen_row=1;
uint16_t screen_flag;
uint16_t flag_up;
uint16_t flag_down;
uint16_t flag_enter;
uint16_t flag_back;
//*****************************************************************************
//
// The interrupt application.
// key妫�娴嬭Е鍙�
//
//*****************************************************************************
void Key1IntHandler()//up
    {
        GPIOIntClear(GPIO_PORTD_BASE,GPIO_INT_PIN_7);
        flag_up = 1;
        //SysCtlDelay(SysCtlClockGet() /50);

    }
void Key2IntHandler()//enter
    {
         GPIOIntClear(GPIO_PORTF_BASE,GPIO_INT_PIN_4);

         GPIOIntDisable(GPIO_PORTD_BASE,GPIO_PIN_7);//绂佺敤涓婄炕鍜屼笅缈�
         GPIOIntDisable(GPIO_PORTA_BASE,GPIO_PIN_3);

         GPIOIntDisable(GPIO_PORTF_BASE,GPIO_PIN_4);//绂佺敤杩涘叆

         GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_2);//浣胯兘閫�鍑洪敭

         flag_enter = 1;
         //screen(screen_line,screen_row);

         screen_flag=1;
         //SysCtlDelay(SysCtlClockGet() /50);

    }
void Key34IntHandler()
  {
          if(GPIOIntStatus(GPIO_PORTA_BASE, 0) & GPIO_INT_PIN_3)//down
          {
              GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_3);

              flag_down = 1;
          }
          if(GPIOIntStatus(GPIO_PORTA_BASE, 0) & GPIO_INT_PIN_2)//back
          {
              GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_2);

              GPIOIntEnable(GPIO_PORTD_BASE,GPIO_PIN_7);
              GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_3);

              GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_4);//浣胯兘杩涘叆閿�

              GPIOIntDisable(GPIO_PORTA_BASE,GPIO_PIN_2);

              flag_back = 1;

              screen_flag=0;
          }
          //SysCtlDelay(SysCtlClockGet() /50);
  }
void key_up()
{
        if(screen_line>1)
        {
            if(screen_row>1)
                {
                     screen_row--;
                     highlight(screen_line,screen_row, screen_row+1);
                }
            else
                {
                    screen_line--;
                    screen_menu(screen_line);//鍒囨崲鑷充笂涓�灞�
                    screen_row=4;
                    highlight(screen_line,screen_row, 100);//楂樹寒鏈�鍚庝竴琛�
                }
        }
        else
            {
                if(screen_row>1)
                    {
                        screen_row--;
                        highlight(screen_line,screen_row, screen_row+1);
                    }
              }
             flag_up = 0;
}
void key_down()
{
    if(screen_line<4)
         {
            if(screen_row<4)
              {
                screen_row++;
                highlight(screen_line,screen_row,screen_row-1);
              }
            else
            {
              screen_line++;
              screen_menu(screen_line);//鍒囨崲鑷充笅涓�灞�
              screen_row= 1;
              highlight(screen_line,screen_row, 100);//楂樹寒绗竴琛�
            }
         }
         else
         {
             if(screen_row<2)
               {
                 screen_row++;
                 highlight(screen_line,screen_row,screen_row - 1);
               }
        
        
        }
         flag_down = 0;
}
void key_polling()
{
    if(flag_up == 1)key_up();
    if(flag_enter == 1)
        {
           screen(screen_line,screen_row);
           flag_enter = 0;
        }
    if(flag_down == 1)key_down();
    if(flag_back == 1)
    {
               screen_menu(screen_line);
               highlight(screen_line, screen_row, 100);//楂樹寒鍘熷厛琛�
               flag_back = 0;
    }
}
void key_init()
{

    //SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//澶栬浣胯兘
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //
//    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;//PD7瑙ｉ攣
//    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;//纭
//    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;//閲嶆柊閿佸畾

    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_7);  //K1锛�
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);  //K2锛�
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_3|GPIO_PIN_2); //K3K4

    GPIOIntTypeSet(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_FALLING_EDGE);//璁剧疆PD7涓柇绫诲瀷
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);//璁剧疆PF4涓柇绫诲瀷
    GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_3|GPIO_PIN_2,GPIO_FALLING_EDGE);//璁剧疆PA2,3涓柇绫诲瀷

    GPIOIntEnable(GPIO_PORTD_BASE,GPIO_PIN_7);                  //浣胯兘PD7涓柇
    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_4);                  //浣胯兘PF4涓柇
    GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_3|GPIO_PIN_2);       //浣胯兘PA2,3涓柇

    GPIOIntRegister(GPIO_PORTD_BASE, Key1IntHandler);     //涓篜D7娉ㄥ唽涓�涓腑鏂鐞嗗彞鏌�
    GPIOIntRegister(GPIO_PORTF_BASE, Key2IntHandler);     //涓篜F4娉ㄥ唽涓�涓腑鏂鐞嗗彞鏌�
    GPIOIntRegister(GPIO_PORTA_BASE, Key34IntHandler);    //涓篜A2,3娉ㄥ唽涓�涓腑鏂鐞嗗彞鏌�
    GPIOIntDisable(GPIO_PORTA_BASE,GPIO_PIN_2);       //浣胯兘PA2,3涓柇
    UC1701Init(1000000);

    //UC1701Clear();
    screen_menu(1);
    highlight(1,1,100);
}
