#include "global values.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdint.h>
#include <stdbool.h>

#include "ADC_module.h"
// #include "driverlib/fpu.h"
// #include "driverlib/sysctl.h"
// #include "driverlib/rom.h"
// #include "inc/hw_memmap.h"
// #include "inc/hw_types.h"

#define PI 3.1415926535897932384626f

//float u1_IIR[512];
float u1_rms[50];//10s内的10周期电压均方根集合
float u1_rms_temp[10];//存储2s内10个(十周期的电压/电流rms数据)
float u2_rms_temp[10];
float u3_rms_temp[10];
float i1_rms_temp[10];
float i2_rms_temp[10];
float i3_rms_temp[10];
float voltage_A_fft_temp[2][10];//存储2s内2个(十周期的电压/电流1~10次谐波数据)
float voltage_B_fft_temp[2][10];
float voltage_C_fft_temp[2][10];
float current_A_fft_temp[2][10];
float current_B_fft_temp[2][10];
float current_C_fft_temp[2][10];
float voltage_unblance_temp[10];//存储10s内10个(十周期的电压/电流不平衡度)
float current_unblance_temp[10];
float active_power_temp[10];//存储2s内10个(十周期的功率参数)
float reactive_power_temp[2];

float fft_temp[512];

float u1_fft[20];
float u2_fft[20];
float u3_fft[20];
float i1_fft[20];
float i2_fft[20];
float i3_fft[20];
float u1_bias_temp[10];
float u2_bias_temp[10];
float u3_bias_temp[10];
float i1_bias_temp[10];
float i2_bias_temp[10];
float i3_bias_temp[10];
extern void rdft(int n, int isgn, float *a, int *ip, float *w);
int ip[32]; //fft
float ww[256];//fft/sin/cos array
/***********************************************
主体函数部分
要求：分批输入10个周期的三相电压和电流的采样值，按照2s/10s刷新全局变量的值
1.函数计算方法安排:
2s刷新的数据
三相电压电流:对采集到的10个10周期数据做均方根计算
谐波：在 2s内等间隔采样2次 ,作2次谐波分析 ，计算均方根值[^1]
有功：对采集到的10个10周期数据做均方根计算
无功：对采集到的10个10周期数据做均方根计算
视在功率：对采集到的10个10周期数据做均方根计算
功率因数：对有功和视在功率2s值进行计算
10s刷新的数据
频率：略
电压上/下偏差：根据10s内10周期A相电压rms值的概率大值和小值计算
不平衡度：在10s内等间隔采样10次 ,计算均方根值[^2]
## 2.函数调用顺序安排
## 3.头文件编写：
**********************************************************************/

/****************************************************************************************/
 //输入三相量均方根值, 输出三相不平衡度
 float data_unblance(const float data1_rms,const float data2_rms,const float data3_rms)
{
    float a = data1_rms,b = data2_rms,c = data3_rms;
    float L,unblance;
        L=(a * a * a * a + b * b * b * b + c * c * c * c) / ((a * a + b * b + c * c) * (a * a + b * b + c * c));
        unblance=100 * sqrtf (1 - 2 / (1 + 1 / sqrtf(3 - 6 * L))) ;
        return unblance;
}

float probability_value_50_min(const float data[50])
{
    float temp[4];
    int i,k;
    for(i = 0;i < 4;i++)
        {
            temp[i] = data[i];
        }
    float *point = &temp[0];
    for(k = 1;k < 4;k++)
        {
                if(*point < temp[k])
                    point = &temp[k];       //*point始终指向temp[4]的最大值
            }
    for(i = 4;i < 50;i++)
    {
        if(data[i] < *point)
            {
                *point = data[i];
                for(k = 0;k < 4;k++)
                    {
                        if(*point < temp[k])point = &temp[k];
                    }
            }
    }
    return *point;
}

float probability_value_50_max(const float data[50])
{
    float temp[4];
    int i,k;
    for(i = 0;i < 4;i++)
        {
            temp[i] = data[i];
        }
    float *point = &temp[0];
    for(k = 1;k < 4;k++)
        {
                if(*point > temp[k])
                    point = &temp[k];       //*point始终指向temp[4]的最大值
            }
    for(i = 4;i < 50;i++)
    {
        if(data[i] > *point)
            {
                *point = data[i];
                for(k = 0;k < 4;k++)//*point始终指向temp[4]的最大值
                    {
                        if(*point > temp[k])
                            point = &temp[k];
                    }
            }
    }
    return *point;
}

float voltage_overdeviation(const float u1_rms[50])
{
    float L = 100 * (probability_value_50_max(u1_rms) - 220 ) / 220;
    //if(L<0)L=0;
    return fdimf(L,0);
}

float voltage_underdeviation(const float  u1_rms[50])
{
    float L=100 * (probability_value_50_min(u1_rms) - 220) / 220;
   //if(L > 0)L = 0;
   return -fdimf(0,L);
}

float THD(const float data_fft[10])
{
    float k = 0;
    int i;
     for (i = 1;i < 10;i++)                          //data_fft[2~10]存放2~10次谐波幅值
     {
         k += data_fft[i] * data_fft[i];
     }
        return  sqrtf(k) / 100;
}

//****************************************************************************************
//有功功率
float active_power(const float u1[512],const float u2[512],const float u3[512],const float i1[512],const float i2[512],const float i3[512])
 {
     int i;
     float P =0;
     for(i = 0;i < 512;i++)
         P += u1[i] * i1[i]+ u2[i] * i2[i]+ u3[i] * i3[i];
     return P/512;
 }

float reactive_power(const float u1_fft[20],const float u2_fft[20],const float u3_fft[20],const float i1_fft[20],const float i2_fft[20],const float i3_fft[20])
{
    extern float rms_2(float a, float b);

    float u1_arg = atan2f(u1_fft[1],u1_fft[0]);                             //基波相角-pi~pi
    float u1_mag = rms_2(u1_fft[1],u1_fft[0]);           //基波幅值（有效值）
    float u2_arg = atan2f(u2_fft[1],u2_fft[0]);
    float u2_mag = rms_2(u2_fft[1],u2_fft[0]);
    float u3_arg = atan2f(u3_fft[1],u3_fft[0]);
    float u3_mag = rms_2(u3_fft[1],u3_fft[0]);
    float i1_arg = atan2f(i1_fft[1],i1_fft[0]);
    float i1_mag = rms_2(i1_fft[1],i1_fft[0]);
    float i2_arg = atan2f(i2_fft[1],i2_fft[0]);
    float i2_mag = rms_2(i2_fft[1],i2_fft[0]);
    float i3_arg = atan2f(i3_fft[1],i3_fft[0]);
    float i3_mag = rms_2(i3_fft[1],i3_fft[0]);

    //float pi = 3.1415926535897932384626433;

    float u_1_real=(u1_mag * cosf(u1_arg) + u2_mag * cosf(u2_arg + 2 * PI / 3) + u3_mag * cosf(u3_arg - 2 * PI / 3) )/ 3;
    float u_1_imag=(u1_mag * sinf(u1_arg) + u2_mag * sinf(u2_arg + 2 * PI / 3) + u3_mag * sinf(u3_arg - 2 * PI / 3) )/ 3;
    float u_1_arg = atan2f(u_1_imag, u_1_real);
    float u_1_mag = hypotf(u_1_imag,u_1_real);

    float i_1_real=(i1_mag * cosf(i1_arg) + i2_mag * cosf(i2_arg + 2 * PI / 3) + i3_mag * cosf(i3_arg - 2 * PI / 3) )/ 3;
    float i_1_imag=(i1_mag * sinf(i1_arg) + i2_mag * sinf(i2_arg + 2 * PI / 3) + i3_mag * sinf(i3_arg - 2 * PI / 3) )/ 3;
    float i_1_arg = atan2f(i_1_imag, i_1_real);
    float i_1_mag = hypotf(i_1_imag,i_1_real);

    return u_1_mag * i_1_mag * sinf(u_1_arg - i_1_arg) * 3;
}
 //视在功率
 float apparent_power(float u1_rms,float u2_rms,float u3_rms,float i1_rms,float i2_rms,float i3_rms)
 {
    return u1_rms * i1_rms + u2_rms * i2_rms + u3_rms * i3_rms;
 } 

void harmonic(const float data_fft[20],float *data_mag)
{
    int i;
    for(i=0;i<10;i++)
    {
        data_mag[i] = rms_2(data_fft[2*i], data_fft[2*i+1]);//有效值
    }
}
void fft_pick(const float data_fft_source[512],float data_fft[20])
{
    int i;
    for(i=0;i<10;i++)
    {
        data_fft[2*i]=data_fft_source[20*i+20]/256;//幅值实部
        data_fft[2*i+1]=data_fft_source[20*i+21]/256;
    }
}
 //**************************************************************************************

float rms_512(const float data[512])
{
    float total = 0;
    int count;
    for(count = 0;count < 512;count++)
    {
        total += data[count] * data[count];
    }
    return sqrtf(total / 512);
}
float rms_10(const float data[10])
{
    float total = 0;
    int count;
    for(count = 0;count < 10;count++)
    {
        total += data[count] * data[count];
    }
    return sqrtf(total / 10);
}
float rms_2(float a, float b)
{
    return sqrtf((a*a+b*b)/2);
}
/*
//IIR三阶低通滤波函数 截止频率50HZ 采样频率2.56kHZ
void IIR_filter(const float u1[512],float u1_filter[512])
{
    float A[3] = {1,-1.8705,0.88465};
    float B[3] = {1,2,1};
    float w_x[3] = {0};
    float w_y[3] = {0};
    float Gain = 0.0035434;
    int i;
    for(i = 0;i < 512;i++)
    {
        w_x[0] = u1[i];
        w_y[0] = (B[0] * w_x[0] + B[1] * w_x[1] + B[2] * w_x[2]) * Gain - w_y[1] * A[1] - w_y[2] * A[2];
        u1_filter[i] = w_y[0];      //u1_filter[i] = w_y[0] / A[0];
        w_x[2] = w_x[1];
        w_x[1] = w_x[0];
        w_y[2] = w_y[1];
        w_y[1] = w_y[0];
    }
}
*/
//**************************************************************************************
void calculate_init()
{
    rdft(512, 1, fft_temp, ip, ww);//initialize the sin/cos array
}
void calculate_200ms(int i)//i=0~9//200ms调用一次该函数
{
    u1_rms_temp[i] = rms_512(u1);//每十周期记录一次数据，持续两秒
    u2_rms_temp[i] = rms_512(u2);//每单位的i代表10周期
    u3_rms_temp[i] = rms_512(u3);
    i1_rms_temp[i] = rms_512(i1);
    i2_rms_temp[i] = rms_512(i2);
    i3_rms_temp[i] = rms_512(i3);

    //IIR_filter(u1, u1_IIR);

    active_power_temp[i] = active_power(u1,u2,u3,i1,i2,i3);
}
float reverse_u(float basewave,float unit_bias)
{
        float a = basewave/256/250*1.6f/1.414213562f;
        float b = -unit_bias / 250*1.6f/1.414213562f;
        if(a<0)
            return  0.56749*a+b-0.006f;//1.654//
        else
            return -0.49894f*a+b-0.0012f;
}
float reverse_i(float basewave)
{
        float a = basewave/256/1*1.6f/1.414213562f;
        if(a<0)
            return  0.56749*a+1.648f;
        else
            return -0.49894f*a+1.6528f;
}
void calculate_1s(int i,int j)//i=0~9,j=0~1
{

    int n;
    float a;
        for(n=0;n<512;n++)  fft_temp[n]=u1[n];
        rdft(512, 1, fft_temp, ip, ww);
        fft_pick(fft_temp,u1_fft);

            u1_bias_temp[i]=reverse_u(fft_temp[0],unit_bias_u1);

        for(n=0;n<512;n++)  fft_temp[n]=u2[n];
        rdft(512, 1, fft_temp, ip, ww);
        fft_pick(fft_temp,u2_fft);
        u2_bias_temp[i]= reverse_u(fft_temp[0],unit_bias_u2);

        for(n=0;n<512;n++)  fft_temp[n]=u3[n];
        rdft(512, 1, fft_temp, ip, ww);
        fft_pick(fft_temp,u3_fft);
        u3_bias_temp[i]= reverse_u(fft_temp[0],unit_bias_u3);

        for(n=0;n<512;n++)  fft_temp[n]=i1[n];
        rdft(512, 1, fft_temp, ip, ww);
        fft_pick(fft_temp,i1_fft);
        i1_bias_temp[i]= reverse_i(fft_temp[0]);

    for(n=0;n<512;n++)  fft_temp[n]=i2[n];
        rdft(512, 1, fft_temp, ip, ww);
        fft_pick(fft_temp,i2_fft);
        i2_bias_temp[i]= reverse_i(fft_temp[0]);

    for(n=0;n<512;n++)  fft_temp[n]=i3[n];
        rdft(512, 1, fft_temp, ip, ww);
        fft_pick(fft_temp,i3_fft);
        i3_bias_temp[i]= reverse_i(fft_temp[0]);

          harmonic(u1_fft, &voltage_A_fft_temp[j]);
          harmonic(u2_fft, &voltage_B_fft_temp[j]);
          harmonic(u3_fft, &voltage_C_fft_temp[j]);
          harmonic(i1_fft, &current_A_fft_temp[j]);
          harmonic(i2_fft, &current_B_fft_temp[j]);
          harmonic(i3_fft, &current_C_fft_temp[j]);

        reactive_power_temp[j] = reactive_power(u1_fft, u2_fft, u3_fft, i1_fft, i2_fft, i3_fft);

    int m = 5 * (i % 2);
    voltage_unblance_temp[i] = data_unblance(u1_rms_temp[m], u2_rms_temp[m], u3_rms_temp[m]);
    current_unblance_temp[i] = data_unblance(i1_rms_temp[m], i2_rms_temp[m], i3_rms_temp[m]);
}
void calculate_2s(int j)//j=0~4
{
    int i;
    u1_rms_2s = rms_10(u1_rms_temp);
    u2_rms_2s = rms_10(u2_rms_temp);
    u3_rms_2s = rms_10(u3_rms_temp);
    i1_rms_2s = rms_10(i1_rms_temp);
    i2_rms_2s = rms_10(i2_rms_temp);
    i3_rms_2s = rms_10(i3_rms_temp);

    for(i = 0;i < 10;i++)
        {
            voltage_A_fft_2s[i] = rms_2(voltage_A_fft_temp[0][i], voltage_A_fft_temp[1][i]) / u1_rms_2s  * 100.0f;
            voltage_B_fft_2s[i] = rms_2(voltage_B_fft_temp[0][i], voltage_B_fft_temp[1][i]) / u2_rms_2s  * 100.0f;
            voltage_C_fft_2s[i] = rms_2(voltage_C_fft_temp[0][i], voltage_C_fft_temp[1][i]) / u3_rms_2s  * 100.0f;
            current_A_fft_2s[i] = rms_2(current_A_fft_temp[0][i], current_A_fft_temp[1][i]) / i1_rms_2s  * 100.0f;
            current_B_fft_2s[i] = rms_2(current_B_fft_temp[0][i], current_B_fft_temp[1][i]) / i2_rms_2s  * 100.0f;
            current_C_fft_2s[i] = rms_2(current_C_fft_temp[0][i], current_C_fft_temp[1][i]) / i3_rms_2s  * 100.0f;//
        }

    voltage_A_harmonic_2s = THD(voltage_A_fft_2s);
    voltage_B_harmonic_2s = THD(voltage_B_fft_2s);
    voltage_C_harmonic_2s = THD(voltage_C_fft_2s);
    current_A_harmonic_2s = THD(current_A_fft_2s);
    current_B_harmonic_2s = THD(current_B_fft_2s);
    current_C_harmonic_2s = THD(current_C_fft_2s);

    for(i = 0;i < 10;i++)
        {
        u1_rms[10 * j + i] = u1_rms_temp[i];//每隔两秒将10个10周期的电压rms值写入u1_rms数组一共50个，即10s
        }

    active_power_2s = rms_10(active_power_temp);
    reactive_power_2s = rms_2(reactive_power_temp[0], reactive_power_temp[1]);
    apparent_power_2s = apparent_power(u1_rms_2s,u2_rms_2s,u3_rms_2s,i1_rms_2s,i2_rms_2s,i3_rms_2s);
    power_factor_2s = active_power_2s / apparent_power_2s;
}
void calculate_10s()
{
    voltage_overdeviation_10s = voltage_overdeviation(u1_rms);
    voltage_underdeviation_10s = voltage_underdeviation(u1_rms);
    voltage_unblance_10s = rms_10(voltage_unblance_temp);
    current_unblance_10s = rms_10(current_unblance_temp);

    unit_bias_u1 = -rms_10(u1_bias_temp) * 250/1.6f*1.414213562f;
    unit_bias_u2 = -rms_10(u2_bias_temp) * 250/1.6f*1.414213562f;
    unit_bias_u3 = -rms_10(u3_bias_temp) * 250/1.6f*1.414213562f;
    unit_bias_i1 = -rms_10(i1_bias_temp) * 1/ 1.6f *1.414213562f;
    unit_bias_i2 = -rms_10(i2_bias_temp) * 1/ 1.6f *1.414213562f;
    unit_bias_i3 = -rms_10(i3_bias_temp) * 1/ 1.6f *1.414213562f;
}


/****************************************************************************************三相电压电流有效值
int i=0,j=0;
for(i=0;i<10;i++)u1_rms_temp[i]=rms_512(u1);//每十周期记录一次数据，持续两秒
for(i=0;i<10;i++)u2_rms_temp[i]=rms_512(u2);//每单位的i代表10周期
for(i=0;i<10;i++)u3_rms_temp[i]=rms_512(u3);
for(i=0;i<10;i++)i1_rms_temp[i]=rms_512(i1);
for(i=0;i<10;i++)i2_rms_temp[i]=rms_512(i2);
for(i=0;i<10;i++)i3_rms_temp[i]=rms_512(i3);

u1_rms_2s=rms_10(u1_rms_temp);
u2_rms_2s=rms_10(u2_rms_temp);
u3_rms_2s=rms_10(u3_rms_temp);
i1_rms_2s=rms_10(i1_rms_temp);
i2_rms_2s=rms_10(i2_rms_temp);
i3_rms_2s=rms_10(i3_rms_temp);
***********************************************************************************************频率
frequency_10s;//??
***********************************************************************************************谐波分析，THD
for(i=0;i<2;i++)harmonic(u1,voltage_A_fft_temp[i][10]);//每隔1s记录一次数据，持续两秒
for(i=0;i<2;i++)harmonic(u2,voltage_B_fft_temp[i][10]);
for(i=0;i<2;i++)harmonic(u3,voltage_C_fft_temp[i][10]);//每单位的i代表50周期
for(i=0;i<2;i++)harmonic(i1,current_A_fft_temp[i][10]);
for(i=0;i<2;i++)harmonic(i2,current_B_fft_temp[i][10]);
for(i=0;i<2;i++)harmonic(i3,current_C_fft_temp[i][10]);

//每单位的j代表一次谐波
for(j=0;j<10;j++)voltage_A_fft_2s[j]=sqrtf((voltage_A_fft_temp[0][j]*voltage_A_fft_temp[0][j]+voltage_A_fft_temp[1][j]*voltage_A_fft_temp[1][j])/2f);//谐波有效值做均方根
for(j=0;j<10;j++)voltage_B_fft_2s[j]=sqrtf((voltage_B_fft_temp[0][j]*voltage_B_fft_temp[0][j]+voltage_B_fft_temp[1][j]*voltage_B_fft_temp[1][j])/2f);
for(j=0;j<10;j++)voltage_C_fft_2s[j]=sqrtf((voltage_C_fft_temp[0][j]*voltage_C_fft_temp[0][j]+voltage_C_fft_temp[1][j]*voltage_C_fft_temp[1][j])/2f);
for(j=0;j<10;j++)current_A_fft_2s[j]=sqrtf((current_A_fft_temp[0][j]*current_A_fft_temp[0][j]+current_A_fft_temp[1][j]*current_A_fft_temp[1][j])/2f);
for(j=0;j<10;j++)current_B_fft_2s[j]=sqrtf((current_B_fft_temp[0][j]*current_B_fft_temp[0][j]+current_B_fft_temp[1][j]*current_B_fft_temp[1][j])/2f);
for(j=0;j<10;j++)current_C_fft_2s[j]=sqrtf((current_C_fft_temp[0][j]*current_C_fft_temp[0][j]+current_C_fft_temp[1][j]*current_C_fft_temp[1][j])/2f);

voltage_A_harmonic_2s=THD(voltage_A_fft_2s,u1_rms_2s);//须在u1_rms_2s刷新后再计算
voltage_B_harmonic_2s=THD(voltage_B_fft_2s,u2_rms_2s);//不确定能否这样计算
voltage_C_harmonic_2s=THD(voltage_C_fft_2s,u3_rms_2s);
current_A_harmonic_2s=THD(current_A_fft_2s,i1_rms_2s);
current_B_harmonic_2s=THD(current_B_fft_2s,i2_rms_2s);
current_C_harmonic_2s=THD(current_C_fft_2s,i3_rms_2s);
***********************************************************************************************电压上下偏差
for(j=0;j<5;j++)//每单位j代表2s
for(i=0;i<10;i++)
    u1_rms[10*j+i]=u1_rms_temp[i];//每隔两秒将10个10周期的电压rms值写入u1_rms数组一共50个，即10s
voltage_overdeviation_10s=voltage_overdeviation(u1_rms);
voltage_underdeviation_10s=voltage_underdeviation(u1_rms);
***********************************************************************************************电压电流三相不平衡度
for(i=0;i<10;i++)//每单位的i代表50周期,每隔1s测一次
voltage_unblance_temp[i]=data_unblance(u1_rms_temp[m],u2_rms_temp[m],u3_rms_temp[m]);
for(i=0;i<10;i++)
current_unblance_temp[i]=data_unblance(i1_rms_temp[m],i2_rms_temp[m],i3_rms_temp[m]);

voltage_unblance_10s=rms_10(voltage_unblance_temp);
current_unblance_10s=rms_10(current_unblance_temp);
***********************************************************************************************功率参数
for(i=0;i<10;i++)active_power_temp[i]=active_power(u1,u2,u3,i1,i2,i3);
for(i=0;i<10;i++)reactive_power_temp[i]=reactive_power(u1,u2,u3,i1,i2,i3);
//for(i=0;i<10;i++)apparent_power_temp[i]=apparent_power(u1_rms_2s,u2_rms_2s,u3_rms_2s,i1_rms_2s,i2_rms_2s,i3_rms_2s);

active_power_2s=rms_10(active_power_temp);
reactive_power_2s=rms_10(reactive_power_temp);
apparent_power_2s=apparent_power(u1_rms_2s,u2_rms_2s,u3_rms_2s,i1_rms_2s,i2_rms_2s,i3_rms_2s);//不确定能否这样计算
power_factor_2s=active_power_2s/apparent_power_2s;
***********************************************************************************************/
