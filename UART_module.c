#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_uart.h"

#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/fpu.h"
#include "driverlib/uart.h"

#include "utils/uartstdio.h"

#include "global values.h"

int32_t flag_UART;
char char_input;
//unsigned char flagdeng = 0;
//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif
extern void UART_select_menu();
extern void UART_menu_1();
extern void UART_menu_2();
extern void UART_menu_3();
extern void UART_menu_4();
extern void UART_menu_5();
extern void UART_menu_6();
extern void UART_menu_7();
extern void UART_menu_8();
extern void UART_send_error();
extern void UART_polling();
void UART1IntHandler()
{
    uint32_t flag=UARTIntStatus(UART1_BASE,true);
    UARTIntClear(UART1_BASE,flag);
    if(flag == UART_INT_RX)
    {
        flag_UART=1;
        char_input = UARTCharGet(UART1_BASE);
    }
    //flagdeng = 1-flagdeng;
}

void ConfigureUART(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

//    FPUEnable();
//    FPULazyStackingEnable();

    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    //UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTStdioConfig(1, 115200, SysCtlClockGet());
    UARTFIFODisable(UART1_BASE);
    UARTIntRegister(UART1_BASE,UART1IntHandler);
    UARTIntEnable(UART1_BASE,UART_INT_RX);
    //UARTFIFOLevelSet(UART1_BASE,UART_FIFO_TX7_8,UART_FIFO_RX1_8);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0<<4);
}

void UART_polling()
{
                    switch(char_input)
                    {
                        case ('1'):{UART_menu_1();UART_select_menu();
                        //GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,flagdeng<<4);
                        break;}
                        case ('2'):{UART_menu_2();UART_select_menu();break;}
                        case ('3'):{UART_menu_3();UART_select_menu();break;}
                        case ('4'):{UART_menu_4();UART_select_menu();break;}
                        case ('5'):{UART_menu_5();UART_select_menu();break;}
                        case ('6'):{UART_menu_6();UART_select_menu();break;}
                        case ('7'):{UART_menu_7();UART_select_menu();break;}
                        case ('8'):{UART_menu_8();UART_select_menu();break;}

                        default:{UART_send_error();UART_select_menu();break;}
                    }
                    flag_UART=0;
}

static char* sprintf_wtf(float data,char *pcBuf,int prec)//返回字符串起始位�?,prec表示小数点后位数,pcBuf[8]
{
    char  *p = &pcBuf[6];       //pcBuf[7]存放'/0'
    unsigned long n = (unsigned long)(fabs(data) * pow(10,prec) + 0.5);//获得整数数字
    int count1 = 0,count2 = 0;
        do
       {
           if(count1 == prec)
               {*p-- = '.';}
           *p-- = (n % 10) + '0';
            n /= 10;
            count1++;
        }
        while (count1 <= prec);         //先输出小数部分和小数�?,还有个位数字

       while(n != 0)//再输出整数部�?
       {
           *p-- = (n % 10) + '0';
            n /= 10;
            count2++;       //count2表示整数部分长度-1
        }
        return &(pcBuf[7 - (prec + count2 + 2)]);
}

void UART_select_menu()
{
    UARTprintf("Select menu:\n");
    UARTprintf("1-----three-phase voltage\n");
    UARTprintf("2-----three-phase current\n");
    UARTprintf("3-----power parameter\n");
    UARTprintf("4-----three-phase voltage THD\n");
    UARTprintf("5-----three-phase current THD\n");
    UARTprintf("6-----voltage deviation\n");
    UARTprintf("7-----frequency\n");
    UARTprintf("8-----voltage/current unblance\n\n");
}

void UART_menu_1()
{
    char temp[8] = {0};

    UARTprintf("phase A voltage:");
    UARTprintf(sprintf_wtf(u1_rms_2s, temp, 1));
    UARTprintf("V\n");
    UARTprintf("phase B voltage:");
    UARTprintf(sprintf_wtf(u2_rms_2s, temp, 1));
    UARTprintf("V\n");
    UARTprintf("phase C voltage:");
    UARTprintf(sprintf_wtf(u3_rms_2s, temp, 1));
    UARTprintf("V\n\n");
}
void UART_menu_2()
{
    char temp[8] = {0};

    UARTprintf("phase A current:");
    UARTprintf(sprintf_wtf(i1_rms_2s, temp, 3));
    UARTprintf("A\n");
    UARTprintf("phase B current:");
    UARTprintf(sprintf_wtf(i2_rms_2s, temp, 3));
    UARTprintf("A\n");
    UARTprintf("phase C current:");
    UARTprintf(sprintf_wtf(i3_rms_2s, temp, 3));
    UARTprintf("A\n\n");
}
void UART_menu_3()
{
    char temp[8] = {0};

    UARTprintf("active power:");
    UARTprintf(sprintf_wtf(active_power_2s, temp, 1));
    UARTprintf("W\n");
    UARTprintf("reactive power:");
    UARTprintf(sprintf_wtf(reactive_power_2s, temp, 1));
    UARTprintf("Var\n");
    UARTprintf("apparent power:");
    UARTprintf(sprintf_wtf(apparent_power_2s, temp, 1));
    UARTprintf("VA\n");
    UARTprintf("power factor:");
    UARTprintf(sprintf_wtf(power_factor_2s, temp, 2));
    UARTprintf("\n\n");
}
void UART_menu_4()
{
    char temp[8] = {0};

    UARTprintf("phase A voltage THD:");
    UARTprintf(sprintf_wtf(voltage_A_harmonic_2s, temp, 1));
    UARTprintf("%%\n");
    UARTprintf("phase B voltage THD:");
    UARTprintf(sprintf_wtf(voltage_B_harmonic_2s, temp, 1));
    UARTprintf("%%\n");
    UARTprintf("phase C voltage THD:");
    UARTprintf(sprintf_wtf(voltage_C_harmonic_2s, temp, 1));
    UARTprintf("%%\n\n");
}
void UART_menu_5()
{
    char temp[8] = {0};

    UARTprintf("phase A current THD:");
    UARTprintf(sprintf_wtf(current_A_harmonic_2s, temp, 1));
    UARTprintf("%%\n");
    UARTprintf("phase B current THD:");
    UARTprintf(sprintf_wtf(current_B_harmonic_2s, temp, 1));
    UARTprintf("%%\n");
    UARTprintf("phase C current THD:");
    UARTprintf(sprintf_wtf(current_C_harmonic_2s, temp, 1));
    UARTprintf("%%\n\n");
}
void UART_menu_6()
{
    char temp[8] = {0};

    UARTprintf("voltage overdeviation:");
    UARTprintf(sprintf_wtf(voltage_overdeviation_10s, temp, 1));
    UARTprintf("%%\n");
    UARTprintf("voltage underdeviation:");
    UARTprintf(sprintf_wtf(voltage_underdeviation_10s, temp, 1));
    UARTprintf("%%\n\n");
}
void UART_menu_7()
{
    char temp[8] = {0};

    UARTprintf("frequency:");
    UARTprintf(sprintf_wtf(frequency_10s, temp, 2));
    UARTprintf("Hz\n\n");
}
void UART_menu_8()
{
    char temp[8] = {0};

    UARTprintf("voltage unblance:");
    UARTprintf(sprintf_wtf(voltage_unblance_10s, temp, 1));
    UARTprintf("%%\n");
    UARTprintf("current unblance:");
    UARTprintf(sprintf_wtf(current_unblance_10s, temp, 1));
    UARTprintf("%%\n\n");
}

void UART_send_error()
{
    UARTprintf("error, please send message again!\n\n");
}
