#ifndef _GPIO_DEVS_H_
#define _GPIO_DEVS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <linux/ioctl.h>
#include <extdrv/gpiomisc.h>

typedef struct _GpioDevsRW
{
    unsigned int     inOut;
    unsigned int     dev;
    unsigned int     num;
    unsigned int     value;
} GpioDevsRW;

typedef struct
{
    unsigned long    irkey_datah;
    unsigned long    irkey_datal;
    unsigned long    irkey_state_code;
} irkey_info_s;

#define GPIO_DEVS_IOC_MAGIC           't'
/* value - 1 use HIIR,  value - 0 - don't use HIIR */
#define GPIO_DEVS_HIIR                _IOWR(GPIO_DEVS_IOC_MAGIC, 3, GpioDevsRW)

#define WATCHDOG_IOCTL_BASE           'W'
#define WDIOC_GETSUPPORT              _IOR(WATCHDOG_IOCTL_BASE, 0, struct watchdog_info)
#define WDIOC_SETOPTIONS              _IOR(WATCHDOG_IOCTL_BASE, 4, int)
#define WDIOC_KEEPALIVE               _IOR(WATCHDOG_IOCTL_BASE, 5, int)
#define WDIOC_SETTIMEOUT              _IOWR(WATCHDOG_IOCTL_BASE, 6, int)

#define WDIOS_DISABLECARD             0x0001 /* Turn off the watchdog timer */
#define WDIOS_ENABLECARD              0x0002 /* Turn on the watchdog timer */

int  gpio_dev_get_acc_power_status    (void);
int  gpio_dev_get_trigger             (int *value);
int  gpio_dev_set_buzzer              (int value);
int  gpio_dev_set_buzzer_on           (void);
int  gpio_dev_set_buzzer_off          (void);
int  gpio_dev_set_power_led           (int value);
int  gpio_dev_set_led_0               (int value);
int  gpio_dev_set_led_1               (int value);
int  gpio_dev_set_led_2               (int value);
int  gpio_dev_hi_wdg_start            (void);
int  gpio_dev_hi_wdg_stop             (void);
int  gpio_dev_hi_wdg_reboot           (void);
int  gpio_dev_hi_wdg_keep_alive       (void);
int  gpio_dev_hi_wdg_set_timeout      (int sec);
void gpio_dev_hi_ir_enable            (int Enable);
int  gpio_dev_hi_ir_start             (void);
int  gpio_dev_hi_ir_stop              (void);
int  gpio_dev_hi_ir_read              (unsigned long *datah, unsigned long *datal, unsigned long *state);

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_DEVS_H_*/

