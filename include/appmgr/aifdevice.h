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
    char camera_mirror04        [8];
    char camera_mirror05        [8];
    char camera_mirror06        [8];
    char camera_mirror07        [8];
    char camera_flip00          [8];
    char camera_flip01          [8];
    char camera_flip02          [8];
    char camera_flip03          [8];
    char camera_flip04          [8];
    char camera_flip05          [8];
    char camera_flip06          [8];
    char camera_flip07          [8];
    char camera_rotate00        [8];
    char camera_rotate01        [8];
    char camera_rotate02        [8];
    char camera_rotate03        [8];
    char camera_rotate04        [8];
    char camera_rotate05        [8];
    char camera_rotate06        [8];
    char camera_rotate07        [8];
    char trigger1_source        [8];
    char trigger2_source        [8];
    char trigger3_source        [8];
    char trigger4_source        [8];
    char trigger5_source        [8];
    char trigger6_source        [8];
    char trigger7_source        [8];
    char trigger8_source        [8];
    char trigger1_delay         [8];
    char trigger2_delay         [8];
    char trigger3_delay         [8];
    char trigger4_delay         [8];
    char trigger5_delay         [8];
    char trigger6_delay         [8];
    char trigger7_delay         [8];
    char trigger8_delay         [8];
    char trigger1_priority      [8];
    char trigger2_priority      [8];
    char trigger3_priority      [8];
    char trigger4_priority      [8];
    char trigger5_priority      [8];
    char trigger6_priority      [8];
    char trigger7_priority      [8];
    char trigger8_priority      [8];
    char trigger1_audio         [8]; // [OUTPUT | MUTE]
    char trigger2_audio         [8]; // [OUTPUT | MUTE]
    char trigger3_audio         [8]; // [OUTPUT | MUTE]
    char trigger4_audio         [8]; // [OUTPUT | MUTE]
    char trigger5_audio         [8]; // [OUTPUT | MUTE]
    char trigger6_audio         [8]; // [OUTPUT | MUTE]
    char trigger7_audio         [8]; // [OUTPUT | MUTE]
    char trigger8_audio         [8]; // [OUTPUT | MUTE]
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
