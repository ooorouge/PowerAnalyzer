#ifndef KEY_KEY_H_
#define KEY_KEY_H_
extern uint16_t screen_flag;
extern uint16_t screen_line;
extern uint16_t screen_row;

extern uint16_t flag_up;
extern uint16_t flag_down;
extern uint16_t flag_enter;
extern uint16_t flag_back;
extern void key_init();
extern void key_polling();
#endif /* KEY_KEY_H_ */
