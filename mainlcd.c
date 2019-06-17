#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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

#include "driverlib/pin_map.h"
#include "uc1701.h"

#define startedgex 0
#define startedgey 0
#define endedgex 15
#define endedgey 7

//˳ʱ��Ϊ0
unsigned char flagofdir = 0;
unsigned char flagn = 0;
unsigned char flage = 0;
unsigned char flagw = 0;
unsigned char flags = 0;
unsigned char FoodEaten = 0;

//G����
char Gleftup[]={0xFC,0xFE,0x0F,0x07,0x03,0x03,0x03,0x03};
char Gleftdown[]={0x3F,0x7F,0xF0,0xE0,0xC0,0xC0,0xC0,0xC0};
char Grightup[]={0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03};
char Grightdown[]={0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFF,0xFF};
char snakebody[]={0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00};
char Food[]={0x18,0x3C,0x7E,0xFF,0xFF,0x7E,0x3C,0x18};
char baobao[]={
0x60,0xC0,0x00,0x00,0x00,0x00,0x70,0xC8,0x14,0xC4,0x94,0x84,0x04,0xD8,0x60,0x00,
0x1C,0x07,0x03,0x05,0x09,0x10,0x11,0x21,0x20,0x20,0x20,0x20,0x10,0x0F,0x00,0x00
};
//����
int lenofbody = 1;
int snakebodyx[50] = {0};
int snakebodyy[50] = {0};
int Foodx;
int Foody;
int RTlocX = 7;
int RTlocY = 3;

//**************************��������***************************
//����ͼ��
void Printblock(unsigned char ucLine, unsigned char ucRow, char *pcChar)
{ 
     int i=0;             
        for(i=0;i<8;i++)
         {
             UC1701AddressSet((ucLine),(129-(ucRow*4)-i));
             UC1701DataWrite(pcChar[i]);
         }
}
//��ʱ��
void Key1IntHandler()
{
    GPIOIntClear(GPIO_PORTD_BASE,GPIO_INT_PIN_7);
    flagofdir = 1;
    SetDir(); //�ж���һ���˶�����
}
//˳ʱ��
void Key2IntHandler()
{
  GPIOIntClear(GPIO_PORTF_BASE,GPIO_INT_PIN_4);
  flagofdir = 0;
    SetDir(); //�ж���һ���˶�����
}

void UC1701CharDispaly2(unsigned char ucLine, unsigned char ucRow,
                       char *pcChar)
{
//    xASSERT((ucLine <= 3) && (ucRow <= 15));
     do
     {
        UC1701Dispaly(ucLine,ucRow,*pcChar++);
        ucRow++;
        if(ucRow>15)
        {
            ucRow=0;
        }
     }
     while(*pcChar!='\0');
 }
//ʹ��ģ��
 void initKey()
 {  
    //********************************************
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //********************************************
    
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;//PD7����
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;//ȷ��
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;//��������

    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_7);  //K1��
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);  //K2��

    GPIOIntTypeSet(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_FALLING_EDGE);//����PD7�ж�����
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);//����PF4�ж�����

    GPIOIntEnable(GPIO_PORTD_BASE,GPIO_PIN_7);                  //ʹ��PD7�ж�
    GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_4);                  //ʹ��PF4�ж�

    GPIOIntRegister(GPIO_PORTD_BASE, Key1IntHandler);     //ΪPD7ע��һ���жϴ�����
    GPIOIntRegister(GPIO_PORTF_BASE, Key2IntHandler);     //ΪPF4ע��һ���жϴ�����
    UC1701Init(100000);
    UC1701Clear();
 }
 //ˢ��ƻ��
 void FoodRnd()
 {
    Printblock( Foody, 2*Foodx, Food);
    if(FoodEaten)
    {
    //srand(time(NULL));
    Foodx = rand()%(endedgex - startedgex)+startedgex+1;
    Foody = rand()%(endedgey - startedgey)+startedgey+1;
    }
    FoodEaten = 0;
 }
 //���ƾ�̬����
 void DrawLCD()
 {

 }
 //�߽���ײ�ж� ײ��Ϊ��
 bool MarginCrash()
 {
    if(snakebodyx[0] > endedgex || snakebodyy[0] > endedgey || snakebodyx[0] < startedgex || snakebodyy[0] < startedgey)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
 }
 //ʳ��ʰȡ�ж� �Ե�Ϊ��
 void EatFood()
 {
    if(snakebodyx[0] == Foodx && snakebodyy[0] == Foody)
    {
        lenofbody++;
        FoodEaten = 1;
    }
 }
//������λ�ø���
 void snakeFollow()
 {
  int i;
  for(i=lenofbody-1;i>0;i--)
  {
    snakebodyx[i] = snakebodyx[i-1];
    snakebodyy[i] = snakebodyy[i-1];
  }
    snakebodyx[0] = RTlocX;
    snakebodyy[0] = RTlocY;
  if(FoodEaten)
  {
snakebodyx[0] = Foodx;
snakebodyy[0] = Foody;
  } 
 }
 //�ߵ�ǰ�����ж� ˳ʱ��0 ��ʱ��1
 int ChangeDir()
 {  
    switch(flagofdir)
    {
        case 0:{
            if(flagn){return 2;}//N˳ʱ��ΪE
            if(flage){return 1;}//E˳ʱ��ΪS
            if(flagw){return 3;}//W˳ʱ��ΪN
            if(flags){return 4;}//S˳ʱ��ΪW
               break;}
        case 1:{
            if(flagn){return 4;}//N��ʱ��ΪW  
            if(flage){return 3;}//E��ʱ��ΪN
            if(flagw){return 1;}//W��ʱ��ΪS
            if(flags){return 2;}//S��ʱ��ΪE               
               break;}
        default:return 0;break;
    }
 }
 //������һ���˶�����
 void SetDir()
 {
    switch (ChangeDir())
      {
        case 1:{flagn= 0;flage= 0;flagw= 0;flags= 1;break;}//����S
        case 2:{flagn= 0;flage= 1;flagw= 0;flags= 0;break;}//����E
        case 3:{flagn= 1;flage= 0;flagw= 0;flags= 0;break;}//����N
        case 4:{flagn= 0;flage= 0;flagw= 1;flags= 0;break;}//����W
        default:break;
      }

 }
 void GameOver()
 {
    if(MarginCrash())
    {
         int i,j;
         UC1701Clear();   
         //par1               
          for(j=0; j<12; j++)
          {
            Printblock( 3, j, Gleftup);
            Printblock( 4, j, Gleftdown);
            UC1701Clear();
          }
           for(i=0; i<4; i++)
          {
            Printblock( 3, 11, Gleftup);
            Printblock( 4, 11, Gleftdown);            
            Printblock( i, 13, Grightup);
            UC1701Clear();
          }
          for(i=7; i>3; i--)
          {
            Printblock( 3, 11, Gleftup);
            Printblock( 4, 11, Gleftdown);
            Printblock( 3, 13, Grightup);
            Printblock( 4, j, Grightdown);
          }
          //par2
          for(j=30; j>18; j--)
          {
            Printblock( 3, 11, Gleftup);
            Printblock( 4, 11, Gleftdown);
            Printblock( 3, 13, Grightup);
            Printblock( 4, 13, Grightdown);
            Printblock( 3, j, Grightup);
            Printblock( 4, j, Grightdown);
            UC1701Clear();
          }
           for(i=0; i<4; i++)
          {
            Printblock( 3, 11, Gleftup);
            Printblock( 4, 11, Gleftdown);
            Printblock( 3, 13, Grightup);
            Printblock( 4, 13, Grightdown);
            Printblock( 3, 19, Grightup);
            Printblock( 4, 19, Grightdown);           
            Printblock( i, 17, Gleftup);
            UC1701Clear();
          }
          for(i=7; i>3; i--)
          {
            Printblock( 3, 11, Gleftup);
            Printblock( 4, 11, Gleftdown);
            Printblock( 3, 13, Grightup);
            Printblock( 4, 13, Grightdown);
            Printblock( 3, 17, Gleftup);
            Printblock( 3, 19, Grightup);
            Printblock( 4, 19, Grightdown);
            Printblock( 4, j, Gleftdown);
          }              
         Printblock( 3, 11, Gleftup);
         Printblock( 4, 11, Gleftdown);
         Printblock( 3, 13, Grightup);
         Printblock( 4, 13, Grightdown);
         Printblock( 3, 17, Gleftup);
         Printblock( 4, 17, Gleftdown);
         Printblock( 3, 19, Grightup);
         Printblock( 4, 19, Grightdown);

         SysCtlDelay(SysCtlClockGet()*10);
        //screen_menu1();
    }
 }
 //��ʼ����Ϸ
 void GameInit()
 {
    snakebodyx[0] = RTlocX;
    snakebodyy[0] = RTlocY;
    flage = 1;
    Foodx = rand()%(endedgex - startedgex-2)+startedgex;
    Foody = rand()%(endedgey - startedgey-2)+startedgey;
//int num=rand()%(n-m+1)+m;
    initKey();
    UC1701CharDispaly(3,4,"HUNGRY SNAKE");
    SysCtlDelay(SysCtlClockGet()/2);
    FoodRnd();
    Printblock(snakebodyy[0], 2*snakebodyx[0], snakebody);

 }
 //������
 void Printsnake()
 {
    int countofsnake;
    for(countofsnake=0;countofsnake<lenofbody;countofsnake++)
       {
          Printblock(snakebodyy[countofsnake], 2*snakebodyx[countofsnake], snakebody);
       }
 }
 void snakeGame()
 {
      EatFood();
      FoodRnd();
      snakeGO(); //�ж���һ���˶�����
      snakeFollow();
      Printsnake();           
      GameOver();
      SysCtlDelay(SysCtlClockGet()/10);
       UC1701Clear();

 }
 void snakeGO()
 {
            if(flagn){RTlocY--;}
            if(flage){RTlocX++;}
            if(flagw){RTlocX--;}
            if(flags){RTlocY++;}
 }
//**************************��������***************************

int
main(void)
{
    int countofsnake;
    GameInit(); //��ʼ
    while(1)
    {
      snakeGame();
    }

}
//**********
