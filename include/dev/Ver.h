#ifndef __VER_H__
#define __VER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define VER_MODEL_NAME_FILE      "/tmp/sysinfo/MODEL"
#define VER_TRIGGER_INFO_FILE    "/tmp/sysinfo/TRIGGER"
#define VER_AUDIO_INFO_FILE      "/tmp/sysinfo/AUDIO"

//----------------------------------------------------------------------------
// Types and defines:
//----------------------------------------------------------------------------
typedef enum {
    ver_model_none            =  0,
    ver_model_eastern         =  1
} ver_model_e;

typedef enum {
    ver_chip_s1_ch            =  0,
    ver_chip_s2_ch            =  1,
    ver_chip_s3_ch            =  2,
    ver_chip_host_ch          =  3
} ver_chip_ch_e;

typedef enum {
    ver_vis_unknown           = -1,
    ver_vis_pal               =  0,
    ver_vis_ntsc              =  1,
    ver_vis_hd_720_25p        =  2,
    ver_vis_hd_720_30p        =  3,
    ver_vis_hd_720_50p        =  4,
    ver_vis_hd_720_60p        =  5,
    ver_vis_hd_1080_25p       =  6,
    ver_vis_hd_1080_30p       =  7,
    ver_vis_hd_1080_50p       =  8,
    ver_vis_hd_1080_60p       =  9,
    ver_vis_hd_1080_i50       = 10,
    ver_vis_hd_1080_i60       = 11
} ver_vis_e;

typedef enum {
    ver_vodev_hd              =  0,
    ver_vodev_ad              =  1,
    ver_vodev_sd              =  2
} ver_vodev_e;

typedef enum {
    ver_vodev_hdmi_vga        =  0,
    ver_vodev_vga             =  1,
    ver_vodev_hdmi            =  2
} ver_vodev_if_e;

typedef enum {
    ver_vga_800_600           =  0,
    ver_vga_1024_768          =  1,
    ver_vga_1280_1024         =  2,
    ver_vga_1366_768          =  3,
    ver_vga_1440_900          =  4,
    ver_vga_800_600_75p       =  5,
    ver_vga_1024_768_75p      =  6,
    ver_hd_720_60p            =  7,
    ver_hd_1080_50i           =  8,
    ver_hd_1080_60i           =  9,
    ver_hd_1080_25p           = 10,
    ver_hd_1080_30p           = 11,
    ver_hd_1080_50p           = 12,
    ver_hd_1080_60p           = 13
} ver_disp_resol_e;

typedef enum {
    ver_mouse_cursor_sw       =  0,
    ver_mouse_cursor_hw       =  1
} ver_mouse_cursor_e;

typedef enum {
    ver_oem_esatern           =  0
} ver_oem_e;

typedef enum {
    ver_sub_model_none        =  0
} ver_sub_model_e;

typedef enum {
    ver_region_korea          =  0,
    ver_region_europe         =  1,
    ver_region_north_america  =  2
} ver_region_e;

typedef enum {
    ver_sub_oem_eastern       =  0
} ver_sub_oem_e;

typedef enum {
    ver_dvr                   =  0
} ver_group_e;

//----------------------------------------------------------------------------
// API
//----------------------------------------------------------------------------
void  ver_dump                      (void);
int   ver_init                      (void);
int   ver_deinit                    (void);
int   ver_get_video                 (void);
void  ver_set_video                 (int video);
int   ver_get_audio                 (void);
void  ver_set_audio                 (int audio);
int   ver_get_model                 (void);
void  ver_set_model                 (ver_model_e model);
int   ver_get_vis                   (void);
void  ver_set_vis                   (ver_vis_e vis);
int   ver_get_vodev                 (void);
void  ver_set_vodev                 (ver_vodev_e vodev);
int   ver_get_ch_num                (void);
int   ver_get_chipid                (void);
int   ver_get_tirggerout            (void);
int   ver_get_tirggerin             (void);
int   ver_get_hdd                   (void);
int   ver_get_vo_if                 (void);
void  ver_set_vo_if                 (ver_vodev_if_e vo_if);
int   ver_get_disp_resol            (void);
void  ver_set_disp_resol            (ver_disp_resol_e resol);
char *ver_get_model_name            (void);
int   ver_set_model_name            (void);
int   ver_set_tirgger_info          (void);
int   ver_set_audio_info            (void);
int   ver_get_mouse_cursor          (void);
void  ver_set_mouse_cursor          (ver_mouse_cursor_e cousor);
void  ver_get_vis_list              (int *parData);
void  ver_set_vis_list              (int *parData);
int   ver_get_vis_to_frame_by_ch    (int ch);
int   ver_get_vis_to_frame          (int vis);
void  ver_set_oem                   (ver_oem_e oem);
int   ver_get_oem                   (void);
void  ver_set_sub_model             (ver_sub_model_e sub_model);
int   ver_get_sub_model             (void);
int   ver_get_ref_year              (void);
void  ver_set_region                (ver_region_e region);
int   ver_get_region                (void);
int   ver_get_sub_oem               (void);
char *ver_get_1st_ifname            (void);
char *ver_get_2nd_ifname            (void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 

#endif
