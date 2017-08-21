#ifndef __EAIFCONFIG_H__
#define __EAIFCONFIG_H__

#ifdef __cplusplus
extern "C"{
#endif

#define	EA_CONFIG_FREE	0
#define	EA_CONFIG_LOCK	1

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    unsigned char   *stream;
    int              bytes;
    int              seq;
} EaLiveNode;

int           utils_net_updown_interface          (char *ifname, int updown);
int           utils_net_get_interface             (char *ifname, char *ip, char *mask);
int           utils_net_set_interface             (char *ifname, char *ip, char *mask);
int           utils_net_get_gateway               (char *gw);
int           utils_net_set_gateway               (char *gw);
int           utils_net_del_gateway               (char *gw);
int           utils_net_get_hwaddr                (char *ifname, char *mac);
int           utils_net_get_hwaddr1               (char *ifname, char *mac);
int           utils_net_set_hwaddr                (char *ifname, char *mac);
char         *utils_inet_ntoa_r                   (struct in_addr in, char *buf);
void          utils_net_local_live_send           (unsigned char *buf, int len, int channel, int mainStream);
void          utils_net_local_live_initialize     (int count, int portStart);
void          utils_live_audio_initialize         (void);
int           utils_sysid_get_unitid_host         (unsigned *unitid);
int           utils_sysid_get_unitid_slav         (unsigned *unitid);
int           utils_sysid_get_unitid              (unsigned *unitid);
int           utils_sysid_get_hw_version          (char *ver);
int           utils_sysid_get_sw_version          (char *ver);
int           utils_set_hw_revision               (int rev);
int           utils_get_hw_revision               (void);
int           utils_get_video_mask                (void);
int           utils_set_video_mask                (int mask);
int           utils_get_node_mask                 (void);
int           utils_set_node_mask                 (int mask);
int           utils_cfg_init                      (void);
int           utils_cfg_set_item                  (char *item, const char *value);
int           utils_cfg_get_item                  (char *item, char *value);
int           utils_cfg_save                      (void);
int           utils_cfg_backup                    (const char *dst);
int           utils_cfg_restore                   (const char *src);
int           utils_cfg_cpy_item                  (char *dst, const char *src);
int           utils_cfg_cmp_item                  (const char *item1, const char *item2);
void          utils_cfg_remove                    (void);
void          utils_cfg_init_lock                 (void);
void          utils_cfg_set_lock                  (int flag);
int           utils_cfg_get_lock                  (void);
void          utils_cfg_init_mutex                (void);
void          utils_cfg_get_from_res              (void);
void          utils_cfg_set_to_res                (void);
void          utils_cfg_erase                     (void);
char         *atime                               (time_t time);
char         *atime_absolute                      (time_t time);
time_t        tm2time                             (int year, int mon, int day, int hour, int min, int sec);
int           utils_get_hdd_nums                  (void);
int           utils_get_password                  (char *userid, char *passwd);
void          utils_swap_int                      (char *p);
void          utils_swap_int_array                (int *p, int count);
void          utils_swap_short                    (char *p);
int           utils_get_vis_from_file             (void);
int           tils_check_uplink                   (void);
int           utils_get_bootbank                  (void);
void          utils_set_bootbank                  (int);
int           utils_get_bootmode                  (void);
int           utils_getpid_host                   (void);
int           utils_set_sw_version                (void);
int           utils_get_sw_version                (char *ver);
int           utils_get_normal_total_size         (char *);
int           utils_get_event_total_size          (char *);
void          utils_set_audio_output              (int status);
int           utils_get_audio_output              (void);
int           utils_get_disk_format               (void);
void          utils_set_disk_format               (int format);
int           utils_get_model_num                 (void);
int           utils_get_sub_model                 (void);
int           utils_get_oem_num                   (void);
char         *utils_get_model_name                (void);
unsigned int  utils_get_mouse_event_count         (void);
int           utils_mark_skip_timemismatch        (void);
int           utils_get_1st_ifname                (char *ifname);
int           utils_get_2nd_ifname                (char *ifname);
int           utils_appup_device_check            (void);
int           utils_appup_device_mount            (void);
int           utils_appup_device_unmount          (void);
int           utils_appup_file_check              (char *fname, int len);
int           utils_appup_file_copy               (void);
int           utils_appup_file_copy_target        (const char *fname, int len);
int           utils_upgrade_firmware              (void);
int           utils_upgrade_firmware_pre_check    (int *);
int           utils_upgrade_firmware_check        (void);
int           utils_salv_upgrade_firmware         (void);
int           nand_erase                          (const char *mtd_device, int start_block, int block_count, int *ratio, int *percent);
int           nand_erase_no_skip_badblock         (const char *mtd_device, int start_block, int block_count);
int           nand_write                          (const char *mtd_device, int ifd, int isize, int *ratio, int *percent);
int           nand_read                           (const char *mtddev, char *rbuf, long long start, int length);
int           utils_get_work_link_up_ready        (void);
int           utils_set_work_link_up_ready        (int num);
void          utils_live_initialize               (int count, int keyCount, int bytesMain, int bytesSub);
void          utils_live_put_audio                (int channel, unsigned char *payload, int bytes, unsigned long long pts, int mainStream, int add);
void          utils_live_put_audio2               (int channel, unsigned char *payload, int bytes, unsigned long long pts, int mainStream, int add);
void          utils_live_put_audio3               (int channel, unsigned char *payload, int bytes, unsigned long pts, int mainStream, int add);
void          utils_live_put_ntp                  (int channel, unsigned long timestamp, int interleaved, int mainStream, int add);
void          utils_live_put_video                (int channel, unsigned char *payload, int bytes, unsigned long pts, int mainStream, int add, int codecype);
EaLiveNode   *utils_live_get                      (int channel, int mainStream);
void         *utils_live_get_audio                (unsigned char channel);
int           utils_get_sata_link                 (void);
int           utils_exist_usb_stick               (void);
int           utils_get_last_scsi_id              (void);
int           utils_system                        (const char *command);

#ifdef __cplusplus
}
#endif

#endif
