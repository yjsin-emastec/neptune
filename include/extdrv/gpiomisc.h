#ifndef _GPIO_MISC_H
#define _GPIO_MISC_H

#include <linux/ioctl.h>

#define GPIO_MISC_IOC_MAGIC                    'm'

#if defined (HI3531D)
#define GPIO_MISC_GET_TRIGGER                  _IOR(GPIO_MISC_IOC_MAGIC, 0x01, unsigned long)
#define GPIO_MISC_SET_BUZZER                   _IOW(GPIO_MISC_IOC_MAGIC, 0x02, unsigned long)
#define GPIO_MISC_SET_BUZZER_ON                _IOW(GPIO_MISC_IOC_MAGIC, 0x03, unsigned long)
#define GPIO_MISC_SET_BUZZER_OFF               _IOW(GPIO_MISC_IOC_MAGIC, 0x04, unsigned long)
#define GPIO_MISC_SET_LED_PWR_RED              _IOW(GPIO_MISC_IOC_MAGIC, 0x05, unsigned long)
#define GPIO_MISC_SET_LED_GREEN_0              _IOW(GPIO_MISC_IOC_MAGIC, 0x06, unsigned long)
#define GPIO_MISC_SET_LED_GREEN_1              _IOW(GPIO_MISC_IOC_MAGIC, 0x07, unsigned long)
#define GPIO_MISC_SET_LED_GREEN_2              _IOW(GPIO_MISC_IOC_MAGIC, 0x08, unsigned long)
#define GPIO_MISC_SET_LED_ALL_ON               _IOW(GPIO_MISC_IOC_MAGIC, 0x09, unsigned long)
#define GPIO_MISC_SET_LED_ALL_OFF              _IOW(GPIO_MISC_IOC_MAGIC, 0x0A, unsigned long)
#define GPIO_MISC_GET_POWER_STATUS             _IOW(GPIO_MISC_IOC_MAGIC, 0x0B, unsigned long)
#elif defined (HI3521)
#define GPIO_MISC_GET_TRIGGER                  _IOR(GPIO_MISC_IOC_MAGIC, 0x01, unsigned long)
#define GPIO_MISC_SET_BUZZER                   _IOW(GPIO_MISC_IOC_MAGIC, 0x02, unsigned long)
#define GPIO_MISC_SET_BUZZER_ON                _IOW(GPIO_MISC_IOC_MAGIC, 0x03, unsigned long)
#define GPIO_MISC_SET_BUZZER_OFF               _IOW(GPIO_MISC_IOC_MAGIC, 0x04, unsigned long)
#define GPIO_MISC_SET_POWER_BOARD              _IOW(GPIO_MISC_IOC_MAGIC, 0x05, unsigned long)
#define GPIO_MISC_SET_LED_POWER_RED            _IOW(GPIO_MISC_IOC_MAGIC, 0x06, unsigned long)
#define GPIO_MISC_SET_LED_0_RECORD_YELLOW      _IOW(GPIO_MISC_IOC_MAGIC, 0x07, unsigned long)
#define GPIO_MISC_SET_LED_0_IMPACT_GREEN       _IOW(GPIO_MISC_IOC_MAGIC, 0x08, unsigned long)
#define GPIO_MISC_SET_LED_0_OFF_ALL            _IOW(GPIO_MISC_IOC_MAGIC, 0x09, unsigned long)
#define GPIO_MISC_SET_LED_1_NETWORK_YELLOW     _IOW(GPIO_MISC_IOC_MAGIC, 0x0A, unsigned long)
#define GPIO_MISC_SET_LED_1_TRIGGER_GREEN      _IOW(GPIO_MISC_IOC_MAGIC, 0x0B, unsigned long)
#define GPIO_MISC_SET_LED_1_OFF_ALL            _IOW(GPIO_MISC_IOC_MAGIC, 0x0C, unsigned long)
#define GPIO_MISC_SET_LED_2_GPS_YELLOW         _IOW(GPIO_MISC_IOC_MAGIC, 0x0D, unsigned long)
#define GPIO_MISC_SET_LED_2_GPS_GREEN          _IOW(GPIO_MISC_IOC_MAGIC, 0x0E, unsigned long)
#define GPIO_MISC_SET_LED_2_OFF_ALL            _IOW(GPIO_MISC_IOC_MAGIC, 0x0F, unsigned long)
#define GPIO_MISC_GET_POWER_STATUS             _IOW(GPIO_MISC_IOC_MAGIC, 0x10, unsigned long)
#define GPIO_MISC_SET_CAMERA1                  _IOW(GPIO_MISC_IOC_MAGIC, 0x11, unsigned long)
#endif

#endif
