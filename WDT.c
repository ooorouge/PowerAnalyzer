//*****************************************************************************
//婵繐绲介悥璺侯啅閵夈倗绋婇柡鍐ㄥ鐠炪垽鎮橀鐐达紡闁绘垳绶ょ槐婵娿亹閹惧灈鏌ら幖鏉戠箲椤掓挳寮甸悮瀵哥婵炲备鍓濆﹢渚�宕ｆ繝鍐╊槯闁哥姴鍊荤�氬秹鏁嶅畝锟界�涒晠鎮橀鐐达紡闁绘垳绶ょ槐婵嬫儎绾惧娈惧璺虹С缂嶅懘濡撮敓锟�
//缂佸顑呯花顓熺▔椤撶喓效闁告瑥锕﹀▓鎴﹀籍閸洘锛熼柛褍娲﹂惀鍛村嫉婢跺寒鍟庨悗鐧告嫹
//闁告鍠庨崹顖涚▔婵℃矘tchdog timer闁汇劌瀚�涒晠宕欓悜妯活槯闂傚倹娼欓妵鍥ㄧ鎼淬垹顣查柡鍫濐槸閸ㄥ酣寮ㄩ婊勭暠闁哄牞鎷峰鍫嗗棴鎷峰Δ浣诡槯闁挎稑鑻弶娲偑濡や焦顦ч梻鍌涙尦濡潡姊鹃弬璺ㄦ瘓濞存粌瀛╂晶宥夊嫉婢跺﹤鐎婚柡锟介婊勭暠闁哄牞鎷峰鍫嗗棴鎷峰Δ浣诡槯闁靛棴鎷�
//
//*****************************************************************************
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
#include "driverlib/watchdog.h"


//*****************************************************************************
//static uint32_t flag_LED;
void WatchdogIntHandler(void)
{
    //缂佷勘鍨绘导鍛存⒒椤忓棗鍓�
// 	while(1)
//     {
// //		if(flag>=2)
// //		{GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6,~GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6)<<4);}
// //		flag++;
// //		if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6))
// //        {
// //            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0<<4);
// //        }
// //        else
// //        {
// //            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 1<<4);
// //        }
// 		SysCtlDelay(SysCtlClockGet()/10);
//     }
}

void WTIMER0_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
			  //PF0鐟欙綁鏀�
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_0,1<<0);//鐠佸墽鐤嗛拑婵婂LED閻忣垰鍨垫慨瀣Ц閹椒璐熼悘锟�

	//
	// Enable watchdog
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);

    //
	// Enable processor interrupts.
	//
	IntMasterEnable();

	//
	// Enable the watchdog interrupt.
	//
	WatchdogIntRegister(WATCHDOG0_BASE,WatchdogIntHandler);

	//
	// Set the period of the watchdog timer.
	//
	WatchdogReloadSet(WATCHDOG0_BASE, SysCtlClockGet()*2);

	//
	// Enable reset generation from the watchdog timer.
	//
	WatchdogResetEnable(WATCHDOG0_BASE);
	WatchdogStallEnable(WATCHDOG0_BASE);

	//
	// Enable the watchdog timer.
	//
	WatchdogEnable(WATCHDOG0_BASE);

}

void WTIMER0_feed()
{
     	//缂備浇娉曟导鍛存⒒椤忓棗鍓�
//flag_LED = 1 -flag_LED;
     	     //   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, flag_LED<<0);
//	// SysCtlDelay(SysCtlClockGet());//闁哥姴鍊荤�氬秹寮崼鏇燂紵闂傚倹鎸冲▓锟�
    	WatchdogIntClear(WATCHDOG0_BASE);//闁哥姴鍊荤�氾拷


}
