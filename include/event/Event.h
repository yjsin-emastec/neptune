#ifndef _EVENT_H_
#define _EVENT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <glib.h>

#define	EA_SIGNAL_55    55
#define	EA_SIGNAL_56    56
#define	EA_SIGNAL_57    57
#define	EA_SIGNAL_58    58
#define	EA_SIGNAL_59    59
#define	EA_SIGNAL_60    60
#define	EA_SIGNAL_61    61
#define	EA_SIGNAL_62    62
#define	EA_SIGNAL_63    63

enum EventQueue {
    QUEUE_QT_CORE = 0,
    QUEUE_WORK,
    QUEUE_ENCODE,
    QUEUE_CORE,
    QUEUE_CORE_JPEG,
    QUEUE_APPMGR,
    QUEUE_NETMGR,
    QUEUE_NETIPC,
    QUEUE_DISKMGR,
    QUEUE_AUDIO,
    QUEUE_MOTION,
    QUEUE_KEY_FRAME,
    QUEUE_AUDIO_SAMPLE,
    QUEUE_ACK,
    QUEUE_EVENT_LOG,
    QUEUE_SYSTEM_LOG,
    QUEUE_MAX,
};

typedef struct _Event {
    int             source;
    int             dest;
    int             event;
    gpointer        data;
    GDestroyNotify  free_func;
    gpointer        func_data;
} Event;

void        event_init              (void);
void        event_queue_register    (int type, gpointer queue);
void        event_send              (int Source, int Dest, int nEvent, gpointer Data, GDestroyNotify Func, gpointer FuncData);
gpointer    event_get_queue         (int type);
int         event_queue_length      (int qid);
int         event_valid_qid         (int qid);

#ifdef __cplusplus
}
#endif

#endif /* _EVENT_H_ */
