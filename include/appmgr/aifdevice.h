#ifndef __AIFDEVICE_H__
#define	__AIFDEVICE_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_DEV_VALUE_LEN   32

//----------------------------------------------------------------------------
// Structure of the Device Property
//----------------------------------------------------------------------------

typedef struct
{
    char buzzer_output          [8];
    char gsensor_level          [4];
    char camera_mirror00        [8];
    char camera_mirror01        [8];
    char camera_mirror02        [8];
    char camera_mirror03        [8];
    char camera_flip00          [8];
    char camera_flip01          [8];
    char camera_flip02          [8];
    char camera_flip03          [8];
    char trigger1_source        [8];
    char trigger2_source        [8];
    char trigger3_source        [8];
    char trigger4_source        [8];
    char trigger1_delay         [8];
    char trigger2_delay         [8];
    char trigger3_delay         [8];
    char trigger4_delay         [8];
    char trigger1_priority      [8];
    char trigger2_priority      [8];
    char trigger3_priority      [8];
    char trigger4_priority      [8];
} device_property_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  aif_device_init            (void);
int  aif_device_set_property    (device_property_t *prop);
int  aif_device_get_property    (device_property_t *prop);

#ifdef __cplusplus
}
#endif

#endif /* __AIFDEVICE_H__ */
