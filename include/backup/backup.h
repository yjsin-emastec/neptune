#ifndef _BACKUP_H_
#define _BACKUP_H_

#ifdef __cplusplus
	 extern "C"{
#endif

#include "avilib.h"
//#include "nsf/dvrplayerformat.h"


#define DEV_DIR             "/dev"
#define USBINFO_DIR_PREFIX  "sd"
//#define USBMOUNT_DIR        "/mnt/usb"
#define USBMOUNT_DIR        "/backup"

#define CONFIG_DIR          "/config"
#define LOG_DIR             "/log"
#define UPGRADE_DIR         "/upgrade"
#define FW_LIST_NUM         19

#define RESERVED_DIR_1        "/reserve1"
#define RESERVED_DIR_2        "/reserve2"

#define VIDEO_SET_XVID		"XVID"
#define VIDEO_SET_H264		"H264"
#define VIDEO_SET_RGB		"RGB"

#define AUD_SAMPLE_RATE		(8000)
#define AUD_BITS			(8)

#define FORCE_RESERVE		1
#define UNFORCE_RESERVE	    0

#define JPEG_FLAG	        1
#define AVI_FLAG	        2
#define DVR_FLAG	        3


///////////////////////////////////////////////////////////
// USB Storage
///////////////////////////////////////////////////////////
int check_usb(void);
int mount_usb(void);
int unmount_usb(void);
int check_usb_free_size(int *freeSize);
int save_config_to_usb();
int find_config_file_in_usb(const char *file);
int load_config_from_usb();
int read_config_from_usb(char *buf, int *size);
int create_log_file_in_usb(char *file, FILE **pfd);
int create_media_file_in_usb(int media, char *szDir, char *fileName, FILE **pfd);


///////////////////////////////////////////////////////////
// HDD Reserved Storage
///////////////////////////////////////////////////////////
int clear_reserved_disk(int resvNum) ;
int get_reserved_free_size(int resvNum, int *freeSize);
int create_media_file_in_reserved(int media, char *fileName, FILE **pfd);

///////////////////////////////////////////////////////////
// CD/DVD Storage
///////////////////////////////////////////////////////////
int cddvd_init(char *cdrom_fd_device);
int cddvd_deinit(void);

int cddvd_open_tray(int immed);
int cddvd_close_tray(int immed);

//int cddvd_check_media(char *avi_file_name, int *Media_Remain_Siez, int *Video_File_Size);
int cddvd_check_media(int *freeSize);

int cddvd_write_file(char * avi_file_name, int force_reserve, int backupFlg);
int cddvd_finish(void);

///////////////////////////////////////////////////////////
// NSF file make
///////////////////////////////////////////////////////////
/*
int nsf_open(char *File_Name);
int nsf_close(int file_fd);
int nsf_update_header(int fd, dvr_format_header dvr_header);
int nsf_write_nfs_data(int file_fd, char *data, int len);
int nsf_finish(int fd, dvr_format_header dvr_header, int video_ch, int audio_ch);
*/

#ifdef __cplusplus
}
#endif

#endif /* _BACKUP_H_ */

