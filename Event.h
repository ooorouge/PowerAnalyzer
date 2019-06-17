#ifndef EVENT_H_
#define EVENT_H_

extern char time_zj_1[];
extern char time_zj_2[];
extern char time_zj_3[];
extern char time_zd_1[];
extern char time_zd_2[];
extern char time_zd_3[];
extern unsigned long  time_zj_lasting[];//记录骤降[0]缓存
extern unsigned long time_zd_lasting[];
extern unsigned long time_count;
extern void zd_zj_dectect_init();
extern void zd_zj_dectect();
extern float rms_50_pick(unsigned long count_512,const float data[],const float data_temp[]);//0,1,2 phase
#endif 
