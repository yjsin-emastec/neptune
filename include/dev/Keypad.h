#ifndef _KEYPAD_H_
#define _KEYPAD_H_

int          keypad_init               (int sourceQ, int destQ);
int          keypad_deinit             (void);
int          keypad_set_remocon_id     (int id);
int          keypad_power_control      (void);
int          keypad_power_off          (void);
int          keypad_reset              (void);
int          keypad_wdg_enable         (void);
int          keypad_wdg_disable        (void);
int          keypad_wdg_alive          (void);
int          keypad_led_init           (int vidNum);
int          keypad_led_control        (unsigned char led);
int          keypad_set_sendevent      (int on);
unsigned int keypad_get_event_count    (void);

#endif /* _KEYPAD_H_ */
