#ifndef __AIFDISPLAY_H__
#define	__AIFDISPLAY_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_DIS_VALUE_LEN   32
#define MAX_DIS_OSD_LEN     4

#define MAX_DIS_CHAN_NUMS   16
#define MAX_DIS_CHAN_NAME   128

//----------------------------------------------------------------------------
// Structure of the System Property
//----------------------------------------------------------------------------
typedef struct
{
    char video_output_hdmi       [MAX_DIS_VALUE_LEN];
    char video_output_cvbs       [MAX_DIS_VALUE_LEN];
    char cvbs_ntsc_x_value       [MAX_DIS_VALUE_LEN];
    char cvbs_ntsc_y_value       [MAX_DIS_VALUE_LEN];
    char cvbs_ntsc_width_value   [MAX_DIS_VALUE_LEN];
    char cvbs_ntsc_height_value  [MAX_DIS_VALUE_LEN];
    char cvbs_pal_x_value        [MAX_DIS_VALUE_LEN];
    char cvbs_pal_y_value        [MAX_DIS_VALUE_LEN];
    char cvbs_pal_width_value    [MAX_DIS_VALUE_LEN];
    char cvbs_pal_height_value   [MAX_DIS_VALUE_LEN];
    char channel_name            [MAX_DIS_CHAN_NUMS][MAX_DIS_CHAN_NAME];
    char osd_chname              [MAX_DIS_OSD_LEN];
    char osd_viloss              [MAX_DIS_OSD_LEN];
    char osd_status              [MAX_DIS_OSD_LEN];
    char osd_record              [MAX_DIS_OSD_LEN];
    char osd_camera              [MAX_DIS_OSD_LEN];
} display_property_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  aif_display_init            (void);
int  aif_display_set_property    (display_property_t *prop);
int  aif_display_get_property    (display_property_t *prop);

#ifdef __cplusplus
}
#endif

#endif /* __AIFDISPLAY_H__ */
