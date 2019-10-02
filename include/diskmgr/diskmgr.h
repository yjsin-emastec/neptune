#ifndef __DISKMGR_H__
#define __DISKMGR_H__


#ifdef __cplusplus
extern "C"{
#endif

struct _n_cal_data_t {
	int type;
	int now;
	int dataCount;
	caldata_t calData[60];	
};

struct _n_tl_data_t {
	int type;
	int now;
	int dataCount;
	int dlsType;
	time_search_info_t timeSearchInfo[25];
	unsigned long boundary;
};


extern int diskmgr_event_user_initialize();

extern unsigned long diskmgr_get_format_total_file_count(void);
extern unsigned long diskmgr_get_format_remove_file_count(void);

int diskmgr_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISKMGR_H__ */

