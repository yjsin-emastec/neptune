#ifndef _KEYPADCODE_H_
#define _KEYPADCODE_H_

#ifdef __cplusplus
extern "C"{
#endif

/* ************************************************************************* */
/* keypad key code (KPD_KEY_)                                                */
/* ************************************************************************* */

/* ************************************************************************* */
/* Remote controller key code (RC_KEY_)                                      */
/* ************************************************************************* */
#define RC_KEY_POWER            (0x61)
#define RC_KEY_ESC              (0x62)
#define RC_KEY_UP               (0x63)
#define RC_KEY_LEFT             (0x64)
#define RC_KEY_SELECT           (0x65)
#define RC_KEY_RIGHT            (0x66)
#define RC_KEY_DOWN             (0x67)
#define RC_KEY_SETUP            (0x68)
#define RC_KEY_SEARCH           (0x69)
#define RC_KEY_REW              (0x6a)
#define RC_KEY_PLAY             (0x6b)
#define RC_KEY_FF               (0x6c)
#define RC_KEY_AUDIO            (0x6d)
#define RC_KEY_FREW             (0x6e)
#define RC_KEY_FADJ             (0x6f)
#define RC_KEY_ARCH             (0x70)
#define RC_KEY_STATUS           (0x71)
#define RC_KEY_SPLIT            (0x72)
#define RC_KEY_1                (0x73)
#define RC_KEY_2                (0x74)
#define RC_KEY_3                (0x75)
#define RC_KEY_4                (0x76)
#define RC_KEY_5                (0x77)
#define RC_KEY_6                (0x78)
#define RC_KEY_7                (0x79)
#define RC_KEY_8                (0x7a)
#define RC_KEY_9                (0x7b)
#define RC_KEY_0                (0x7c)

/* ************************************************************************* */
/* key event                                                                 */
/* ************************************************************************* */
#define KPD_EVENT_ERR           (0x00)
#define KPD_EVENT_POWER         (0x01)
#define KPD_EVENT_ESC           (0x02)
#define KPD_EVENT_UP            (0x03)
#define KPD_EVENT_LEFT          (0x04)
#define KPD_EVENT_SELECT        (0x05)
#define KPD_EVENT_RIGHT         (0x06)
#define KPD_EVENT_DOWN          (0x07)
#define KPD_EVENT_SETUP         (0x08)
#define KPD_EVENT_SEARCH        (0x09)
#define KPD_EVENT_REW           (0x0a)
#define KPD_EVENT_PLAY_PAUSE    (0x0b)
#define KPD_EVENT_FF            (0x0c)
#define KPD_EVENT_AUDIO         (0x0d)
#define KPD_EVENT_FREW          (0x0e)
#define KPD_EVENT_FADJ          (0x0f)
#define KPD_EVENT_ARCHIVE       (0x10)
#define KPD_EVENT_STATUS        (0x11)
#define KPD_EVENT_SPLIT         (0x12)
#define KPD_EVENT_1             (0x13)
#define KPD_EVENT_2             (0x14)
#define KPD_EVENT_3             (0x15)
#define KPD_EVENT_4             (0x16)
#define KPD_EVENT_5             (0x17)
#define KPD_EVENT_6             (0x18)
#define KPD_EVENT_7             (0x19)
#define KPD_EVENT_8             (0x1a)
#define KPD_EVENT_9             (0x1b)
#define KPD_EVENT_10            (0x1c)

/* ************************************************************************* */
/* keypad control                                                            */
/* ************************************************************************* */
#define KPD_WD_ALIVE             0x41 // NOTE: alive command.   'A'
#define KPD_RESET                0x42 // NOTE: reset.           'B'
#define KPD_PW_CONTROL           0x43 // NOTE: power control.   'C'
#define KPD_WD_ENABLE            0x44 // NOTE: enable  wdog.    'D'
#define KPD_WD_DISABLE           0x45 // NOTE: disable wdog.    'E'
#define KPD_POWER                0x47 // NOTE: power off.       'G'

#ifdef __cplusplus
}
#endif

#endif /* _KEYPADCODE_H_ */

