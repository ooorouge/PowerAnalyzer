#include "uc1701.h"

#define BASE 1.785714286 //单个像素点所代表的长度

//从满格到one pixel格
static char block_8_base[] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static char block_7_base[] = {0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00};
static char block_6_base[] = {0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00};
static char block_5_base[] = {0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x00};
static char block_4_base[] = {0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x00};
static char block_3_base[] = {0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00};
static char block_2_base[] = {0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00};
static char block_1_base[] = {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00};
static char block_0_base[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static char label_1[] = {0x80, 0x80, 0x80, 0x84, 0x86, 0xFF, 0x06, 0x04};
static char label_2[] = {0x00, 0x00, 0x00, 0x88, 0x88, 0xFF, 0x00, 0x00}; //标度
static char label_4[] = {0x80, 0x80, 0x80, 0x88, 0x88, 0xFF, 0x00, 0x00}; //长标度
static char label_5[] = {0x00, 0x00, 0x00, 0x08, 0x08, 0xFF, 0x00, 0x00}; //短标度

static char num_1[] = {0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //数字的点阵排列
static char num_2[] = {0x00, 0xF2, 0x92, 0x92, 0x92, 0x9E, 0x00, 0x00};
static char num_3[] = {0x00, 0x92, 0x92, 0x92, 0x92, 0xFE, 0x00, 0x00};
static char num_4[] = {0x00, 0x1E, 0x10, 0x10, 0x10, 0xFE, 0x00, 0x00};
static char num_5[] = {0x00, 0x9E, 0x92, 0x92, 0x92, 0xF2, 0x00, 0x00};
static char num_6[] = {0x00, 0xFE, 0x92, 0x92, 0x92, 0xF2, 0x00, 0x00};
static char num_7[] = {0x00, 0x02, 0x02, 0x02, 0x02, 0xFE, 0x00, 0x00};
static char num_8[] = {0x00, 0xFE, 0x92, 0x92, 0x92, 0xFE, 0x00, 0x00};
static char num_9[] = {0x00, 0x9E, 0x92, 0x92, 0x92, 0xFE, 0x00, 0x00};
static char num_10[] = {0x00, 0xFE, 0x00, 0xFE, 0x82, 0x82, 0xFE, 0x00};

//*******************************************************************************
void UC1701Diagram(unsigned char ucLine, unsigned char ucRow, unsigned char ucLength, char *pcChar)
{
    int i, j;
    for (j = 0; j < ucLength; j++)
    {
        for (i = 0; i < 8; i++)
        {
            UC1701AddressSet((ucLine), (129 - (ucRow * 4) - i));
            UC1701DataWrite(pcChar[j * 8 + i]);
        }
    }
}
//*******************************************************************************
void DrawLabel() //画上坐标轴
{
    UC1701Diagram(0, 10, 1, label_1);
    UC1701Diagram(1, 10, 1, label_2);
    UC1701Diagram(2, 10, 1, label_4);
    UC1701Diagram(3, 10, 1, label_2);
    UC1701Diagram(4, 10, 1, label_4);
    UC1701Diagram(5, 10, 1, label_2);
    UC1701Diagram(6, 10, 1, label_5);
}

void DrawDiagram(float arr[10]) //arr是谐波含量数组
{
    int n, i, j;
    float yushu = 0;
    DrawLabel();

    UC1701Diagram(7, 12, 1, num_1);
    UC1701Diagram(7, 14, 1, num_2);
    UC1701Diagram(7, 16, 1, num_3);
    UC1701Diagram(7, 18, 1, num_4);
    UC1701Diagram(7, 20, 1, num_5);
    UC1701Diagram(7, 22, 1, num_6);
    UC1701Diagram(7, 24, 1, num_7);
    UC1701Diagram(7, 26, 1, num_8);
    UC1701Diagram(7, 28, 1, num_9);
    UC1701Diagram(7, 30, 1, num_10);

    for(i = 0;i < 10;i++)
    {
            n = arr[i] / (8 * BASE);     //取整
            yushu = arr[i]-n * (8 * BASE);
               for(j = 6;j > 6-n;j--)        //先画上满格部分 到底是7-n还是7-n+1
               {
                  UC1701Diagram(j,(i * 2 + 12),1,block_8_base);
              }
            int m = (int)(yushu / BASE + 0.5);       //补足部分
            switch(m)
            {
              case(0):{UC1701Diagram(6 - n,i * 2 + 12,1,block_0_base);break;}
              case(1):{UC1701Diagram(6 - n,i * 2 + 12,1,block_1_base);break;}
              case(2):{UC1701Diagram(6 - n,i * 2 + 12,1,block_2_base);break;}
              case(3):{UC1701Diagram(6 - n,i * 2 + 12,1,block_3_base);break;}
              case(4):{UC1701Diagram(6 - n,i * 2 + 12,1,block_4_base);break;}
              case(5):{UC1701Diagram(6 - n,i * 2 + 12,1,block_5_base);break;}
              case(6):{UC1701Diagram(6 - n,i * 2 + 12,1,block_6_base);break;}
              case(7):{UC1701Diagram(6 - n,i * 2 + 12,1,block_7_base);break;}
              case(8):{UC1701Diagram(6 - n,i * 2 + 12,1,block_8_base);break;}
              default:break;
          }
      }
 }
