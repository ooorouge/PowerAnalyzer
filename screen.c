#include <math.h>
#include "zimo.h"
#include "uc1701.h"
#include "global values.h"
#include "DrawDiagram.h"
#include "Event.h"

int sprintf_wtf(float data, char *pcBuf, int prec) //返回字符串起始位置,prec表示小数点后位数
{
    char *p = &pcBuf[6];                                                 //pcBuf[7]存放'/0'
    unsigned long n = (unsigned long)(fabsf(data) * powf(10, prec) + 0.5f); //获得整数数字
    int count1 = 0, count2 = 0;
    do
    {
        if (count1 == prec)
        {
            *p-- = '.';
        }
        *p-- = (n % 10) + '0';
        n /= 10;
        count1++;
    } while (count1 <= prec); //先输出小数部分和小数点,还有个位数字

    while (n != 0) //再输出整数部分
    {
        *p-- = (n % 10) + '0';
        n /= 10;
        count2++; //count2表示整数部分长度-1
    }
    return 7 - (prec + count2 + 2);
}

void UC1701DataClear(int m,int n,int l)//m=0~3,n=0~15,l=1~16
{
        unsigned char j;
        n=129-8*n;

        for(j=n;j>n-8*l;j--)
        {
            UC1701AddressSet(2*m,j);
            UC1701DataWrite(0x00);
            UC1701AddressSet(2*m+1,j);
            UC1701DataWrite(0x00);
        }
}
void screen11_datareclear()
{
    UC1701DataClear(0,10,5);
    UC1701DataClear(1,10,5);
    UC1701DataClear(2,10,5);
    UC1701DataClear(3,10,5);
}
void screen11_datarefresh()
{
    char temp0[8] = {0};
    char temp1[8] = {0};
    char temp2[8] = {0};
    char temp3[8] = {0};

    int len0 = sprintf_wtf(u1_rms_2s, temp0, 1);
    int len1 = sprintf_wtf(u2_rms_2s, temp1, 1);
    int len2 = sprintf_wtf(u3_rms_2s, temp2, 1);
    int len3 = sprintf_wtf(voltage_unblance_10s, temp3, 1);

    UC1701CharDispaly(0, len0 + 8, &temp0[len0]);
    UC1701CharDispaly(1, len1 + 8, &temp1[len1]);
    UC1701CharDispaly(2, len2 + 8, &temp2[len2]);
    UC1701CharDispaly(3, len3 + 8, &temp3[len3]);
}
void screen11() //三相电压和不平衡度
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "A"); //A相电压
    UC1701ChineseDispaly(0, 1, 4, xdy);
    UC1701CharDispaly(0, 15, "V");

    UC1701CharDispaly(1, 0, "B"); //B相电压
    UC1701ChineseDispaly(1, 1, 4, xdy);
    UC1701CharDispaly(1, 15, "V");

    UC1701CharDispaly(2, 0, "C"); //C相电压
    UC1701ChineseDispaly(2, 1, 4, xdy);
    UC1701CharDispaly(2, 15, "V");

    UC1701CharDispaly(3, 0, "U"); //U不平衡度
    UC1701ChineseDispaly(3, 1, 5, bphd);
    UC1701CharDispaly(3, 15, "%");

    screen11_datarefresh();
}
void screen12_datareclear()
{
    UC1701DataClear(0,10,5);
    UC1701DataClear(1,10,5);
    UC1701DataClear(2,10,5);
    UC1701DataClear(3,10,5);
}
void screen12_datarefresh()
{
    char temp0[8] = {0};
    char temp1[8] = {0};
    char temp2[8] = {0};
    char temp3[8] = {0};
    
    int len0 = sprintf_wtf(i1_rms_2s, temp0, 3);
    int len1 = sprintf_wtf(i2_rms_2s, temp1, 3);
    int len2 = sprintf_wtf(i3_rms_2s, temp2, 3);
    int len3 = sprintf_wtf(current_unblance_10s, temp3, 1);

    UC1701CharDispaly(0, len0 + 8, &temp0[len0]);
    UC1701CharDispaly(1, len1 + 8, &temp1[len1]);
    UC1701CharDispaly(2, len2 + 8, &temp2[len2]);
    UC1701CharDispaly(3, len3 + 8, &temp3[len3]);
}
void screen12() //三相电流和不平衡度
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "A"); //A相电流
    UC1701ChineseDispaly(0, 1, 4, xdl);
    UC1701CharDispaly(0, 15, "A");

    UC1701CharDispaly(1, 0, "B"); //B相电流
    UC1701ChineseDispaly(1, 1, 4, xdl);
    UC1701CharDispaly(1, 15, "A");

    UC1701CharDispaly(2, 0, "C"); //C相电流
    UC1701ChineseDispaly(2, 1, 4, xdl);
    UC1701CharDispaly(2, 15, "A");

    UC1701CharDispaly(3, 0, "I"); //I不平衡度
    UC1701ChineseDispaly(3, 1, 5, bphd);
    UC1701CharDispaly(3, 15, "%");

    screen12_datarefresh();
}
void screen13_datareclear()
{
    UC1701DataClear(0,9,5);
    UC1701DataClear(1,9,5);
    UC1701DataClear(2,9,5);
    UC1701DataClear(3,12,4);
}
void screen13_datarefresh()
{
    char temp0[8] = {0};
    char temp1[8] = {0};
    char temp2[8] = {0};
    char temp3[8] = {0};

    int len0 = sprintf_wtf(active_power_2s, temp0, 1);
    int len1 = sprintf_wtf(reactive_power_2s, temp1, 1);
    int len2 = sprintf_wtf(apparent_power_2s, temp2, 1);
    int len3 = sprintf_wtf(power_factor_2s, temp3, 2);

    UC1701CharDispaly(0, len0 + 7, &temp0[len0]);
    UC1701CharDispaly(1, len1 + 7, &temp1[len1]);
    UC1701CharDispaly(2, len2 + 7, &temp2[len2]);
    UC1701CharDispaly(3, len3 + 9, &temp3[len3]);

    if(reactive_power_2s < 0)
        UC1701CharDispaly(1, 9, "-");
}

void screen13() //功率参数
{
    UC1701Clear();


    UC1701ChineseDispaly(0, 0, 4, yggl); //有功功率
    UC1701CharDispaly(0, 8, ":");
    UC1701ChineseDispaly(0, 14, 1, w);

    UC1701ChineseDispaly(1, 0, 4, wggl); //无功功率
    UC1701CharDispaly(1, 8, ":");
    UC1701ChineseDispaly(1, 14, 1, f);

    UC1701ChineseDispaly(2, 0, 4, szgl); //视在功率
    UC1701CharDispaly(2, 8, ":");
    UC1701CharDispaly(2, 14, "VA");

    UC1701ChineseDispaly(3, 0, 4, glys); //功率因数
    UC1701CharDispaly(3, 8, ":");

    screen13_datarefresh();
}

void screen21_datareclear()
{
    UC1701DataClear(0,11,4);
    UC1701DataClear(1,11,4);
    UC1701DataClear(2,11,4);

}
void screen21_datarefresh()
{
    char temp0[8] = {0};
    char temp1[8] = {0};
    char temp2[8] = {0};

    int len0 = sprintf_wtf(voltage_A_harmonic_2s, temp0, 1);
    int len1 = sprintf_wtf(voltage_B_harmonic_2s, temp1, 1);
    int len2 = sprintf_wtf(voltage_C_harmonic_2s, temp2, 1);

    UC1701CharDispaly(0, len0 + 8, &temp0[len0]);
    UC1701CharDispaly(1, len1 + 8, &temp1[len1]);
    UC1701CharDispaly(2, len2 + 8, &temp2[len2]);
}
void screen21() //三相电压THD
{
    UC1701Clear();


    UC1701CharDispaly(0, 0, "A"); //A相电压THD
    UC1701ChineseDispaly(0, 1, 3, xdy);
    UC1701CharDispaly(0, 7, "THD:");
    UC1701CharDispaly(0, 15, "%");

    UC1701CharDispaly(1, 0, "B"); //B相电压THD
    UC1701ChineseDispaly(1, 1, 3, xdy);
    UC1701CharDispaly(1, 7, "THD:");
    UC1701CharDispaly(1, 15, "%");

    UC1701CharDispaly(2, 0, "C"); //C相电压THD
    UC1701ChineseDispaly(2, 1, 3, xdy);
    UC1701CharDispaly(2, 7, "THD:");
    UC1701CharDispaly(2, 15, "%");

    screen21_datarefresh();
}
void screen22_datareclear()
{
    UC1701DataClear(0,11,4);
    UC1701DataClear(1,11,4);
    UC1701DataClear(2,11,4);
}
void screen22_datarefresh()
{
    char temp0[8] = {0};
    char temp1[8] = {0};
    char temp2[8] = {0};
    int len0 = sprintf_wtf(current_A_harmonic_2s, temp0, 1);
    int len1 = sprintf_wtf(current_B_harmonic_2s, temp1, 1);
    int len2 = sprintf_wtf(current_C_harmonic_2s, temp2, 1);

    UC1701CharDispaly(0, len0 + 8, &temp0[len0]);
    UC1701CharDispaly(1, len1 + 8, &temp1[len1]);
    UC1701CharDispaly(2, len2 + 8, &temp2[len2]);
}
void screen22() //三相电流THD
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "A"); //A相电流THD
    UC1701ChineseDispaly(0, 1, 3, xdl);
    UC1701CharDispaly(0, 7, "THD:");
    UC1701CharDispaly(0, 15, "%");

    UC1701CharDispaly(1, 0, "B"); //B相电流THD
    UC1701ChineseDispaly(1, 1, 3, xdl);
    UC1701CharDispaly(1, 7, "THD:");
    UC1701CharDispaly(1, 15, "%");

    UC1701CharDispaly(2, 0, "C"); //C相电流THD
    UC1701ChineseDispaly(2, 1, 3, xdl);
    UC1701CharDispaly(2, 7, "THD:");
    UC1701CharDispaly(2, 15, "%");

    screen22_datarefresh();
}
void screen23_datareclear()
{
    UC1701DataClear(0,10,5);
    UC1701DataClear(1,10,5);
    UC1701DataClear(2,9,5);
}
void screen23_datarefresh()
{
    char temp0[8] = {0};
    char temp1[8] = {0};
    char temp2[8] = {0};

    int len0 = sprintf_wtf(voltage_overdeviation_10s, temp0, 1);
    int len1 = sprintf_wtf(voltage_underdeviation_10s, temp1, 1);
    int len2 = sprintf_wtf(frequency_10s, temp2, 2);

    UC1701CharDispaly(0, len0 + 8, &temp0[len0]);
    UC1701CharDispaly(1, len1 + 8, &temp1[len1]);
    UC1701CharDispaly(2, len2 + 7, &temp2[len2]);
}
void screen23()//电压偏差,频率
{
    UC1701Clear();

    UC1701ChineseDispaly(0, 0, 5, dyspc); //(A相)电压上偏差
    UC1701CharDispaly(0, 10, ":");
    UC1701CharDispaly(0, 15, "%");

    UC1701ChineseDispaly(1, 0, 5, dyxpc); //(A相)电压下偏差
    UC1701CharDispaly(1, 10, ":");
    UC1701CharDispaly(1, 15, "%");

    UC1701ChineseDispaly(2, 0, 2, pl); //(A相)频率
    UC1701CharDispaly(2, 4, ":");
    UC1701CharDispaly(2, 14, "Hz");

    screen23_datarefresh();
}


void screen33() //电压暂降事件
{
    UC1701Clear();
    extern void time_display(int n,int m,char start_time[], unsigned int last_time);
    UC1701ChineseDispaly(0, 2, 6, dyzjsj);
    time_display(1,0,time_zj_1,time_zj_lasting[1]);
    time_display(2,0,time_zj_2,time_zj_lasting[2]);
    time_display(3,0,time_zj_3,time_zj_lasting[3]);
}

void screen31() //A相电压频谱图
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "A");
    UC1701ChineseDispaly(0, 2, 1, xiang);
    UC1701ChineseDispaly(1, 0, 2, dy);
    UC1701ChineseDispaly(2, 0, 2, xb);
    UC1701ChineseDispaly(3, 0, 2, hl);

    DrawDiagram(voltage_A_fft_2s);
}
void screen32() //A相电流频谱图
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "A");
    UC1701ChineseDispaly(0, 2, 1, xiang);
    UC1701ChineseDispaly(1, 0, 2, dl);
    UC1701ChineseDispaly(2, 0, 2, xb);
    UC1701ChineseDispaly(3, 0, 2, hl);

    DrawDiagram(current_A_fft_2s);
}
void screen41() //B相电压频谱图
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "B");
    UC1701ChineseDispaly(0, 2, 1, xiang);
    UC1701ChineseDispaly(1, 0, 2, dy);
    UC1701ChineseDispaly(2, 0, 2, xb);
    UC1701ChineseDispaly(3, 0, 2, hl);

    DrawDiagram(voltage_B_fft_2s);
}
void screen42() //B相电流频谱图
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "B");
    UC1701ChineseDispaly(0, 2, 1, xiang);
    UC1701ChineseDispaly(1, 0, 2, dl);
    UC1701ChineseDispaly(2, 0, 2, xb);
    UC1701ChineseDispaly(3, 0, 2, hl);

    DrawDiagram(current_B_fft_2s);
}
// void zero_num_display(int m, int n, unsigned int num)
// {
//     if(num<10)
//     {
//         UC1701CharDispaly(m,n,"0");
//         UC1701DisplayN(m,n+1,num);
//     }
//     else
//         UC1701DisplayN(m,n,num);
// }
void time_display(int n,int m,char start_time[], unsigned int last_time)//第n行,m相
{
    //UC1701DisplayN(n,0,n);
    if(m == 0) UC1701CharDispaly(n,0,"A");
    else if(m == 1) UC1701CharDispaly(n,0,"B");
    else if(m == 2) UC1701CharDispaly(n,0,"C");

    UC1701CharDispaly(n,1,".");
    UC1701CharDispaly(n,2,start_time);

    if(last_time<1000)
        {
            UC1701CharDispaly(n,14,"ms");
            if(last_time<10)
                UC1701DisplayN(n,13,last_time);
            else if(last_time < 100)
                UC1701DisplayN(n,12,last_time);
            else
                UC1701DisplayN(n,11,last_time);
        }
    else if(last_time>1000 && last_time+500 <1000000)
        {
            char temp[8] = {0};
            int weishu = 1+(int)log10f(last_time);//不可靠
            int len= sprintf_wtf(((float)last_time)/1000,temp,6-weishu);//?0
            UC1701CharDispaly(n,15,"s");
            UC1701CharDispaly(n,len+9,&temp[len]);//？？？
        }
    else if(last_time+500 <10000000)
        {
            UC1701DisplayN(n,11,(last_time+500)/1000);
        }
        else
            UC1701CharDispaly(n,11,"9999s");
}
void screen43() //电压中断事件
{
    UC1701Clear();
    UC1701ChineseDispaly(0, 2, 6, dyzdsj);
    time_display(1,0,time_zd_1,time_zd_lasting[1]);
    time_display(2,0,time_zd_2,time_zd_lasting[2]);
    time_display(3,0,time_zd_3,time_zd_lasting[3]);
}
void screen51() //C相电压频谱图
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "C");
    UC1701ChineseDispaly(0, 2, 1, xiang);
    UC1701ChineseDispaly(1, 0, 2, dy);
    UC1701ChineseDispaly(2, 0, 2, xb);
    UC1701ChineseDispaly(3, 0, 2, hl);

    DrawDiagram(voltage_C_fft_2s);
}
void screen52() //C相电流频谱图
{
    UC1701Clear();

    UC1701CharDispaly(0, 0, "C");
    UC1701ChineseDispaly(0, 2, 1, xiang);
    UC1701ChineseDispaly(1, 0, 2, dl);
    UC1701ChineseDispaly(2, 0, 2, xb);
    UC1701ChineseDispaly(3, 0, 2, hl);

    DrawDiagram(current_C_fft_2s);
}
void screen(unsigned char line,unsigned char row)//屏幕选择函数
{
        unsigned char screen[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15};
         switch(screen[line - 1][row - 1])
                {
                    case(1):{screen11();break;}
                    case(2):{screen12();break;}
                    case(3):{screen13();break;}
                    case(4):{screen32();break;}

                    case(5):{screen42();break;}
                    case(6):{screen52();break;}
                    case(7):{screen31();break;}
                    case(8):{screen41();break;}

                    case(9):{screen51();break;}
                    case(10):{screen23();break;}
                    case(11):{screen21();break;}
                    case(12):{screen22();break;}
                    
                    case(13):{screen43();break;}
                    case(14):{screen33();break;}

                    default:break;
                }
}
