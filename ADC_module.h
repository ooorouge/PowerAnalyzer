#ifndef ADC_MODULE_H_
#define ADC_MODULE_H_
extern void ADC0_init();
extern uint32_t flag_200ms;
extern uint32_t count_50;
extern float unit_bias_u1;
extern float unit_bias_u2;
extern float unit_bias_u3;
extern float unit_bias_i1;
extern float unit_bias_i2;
extern float unit_bias_i3;
extern float points_50_square[3];
extern unsigned short flag_event_detect;
#endif
