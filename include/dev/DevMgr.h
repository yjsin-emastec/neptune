#ifndef _DEVICE_MANAGER_H_
#define _DEVICE_MANAGER_H_

#ifdef __cplusplus
extern "C"{
#endif

enum {
    DEV_RS232_KEYPAD = 0,
    DEV_MAX,
};

int  devmgr_dev_init                    (int maxSensor, int maxAlarm);
int  devmgr_dev_deinit                  (void);
int  devmgr_dev_deinit2                 (void);
int  devmgr_uart_open                   (int id, int baudrate, int databit, int stopbit, int parity);
int  devmgr_uart_close                  (int id);
int  devmgr_rs232_read                  (int id, unsigned char *data, int size);
int  devmgr_rs232_write                 (int id, unsigned char *data, int size);
int  devmgr_set_beep                    (int on);
int  devmgr_get_trigger                 (void);
int  devmgr_hi_wdg_start                (void);
int  devmgr_hi_wdg_stop                 (void);
int  devmgr_hi_wdg_reboot               (void);
int  devmgr_hi_wdg_keep_alive           (void);
int  devmgr_hi_wdg_set_timeout          (int sec);
int  devmgr_hi_ir_init                  (void);
int  devmgr_hi_ir_deinit                (void);
int  devmgr_hi_ir_read                  (unsigned long *datah, unsigned long *datal, unsigned long *state);
void devmgr_gpio_power_led_control      (int value);
void devmgr_gpio_record_led_control     (int value);
void devmgr_gpio_gsensor_led_control    (int value);
void devmgr_gpio_network_led_control    (int value);
void devmgr_gpio_gps_led_control        (int value);

#ifdef __cplusplus
}
#endif

#endif /* _DEVICE_MANAGER_H_*/

