#ifndef __AIFRECORD_H__
#define	__AIFRECORD_H__

#ifdef __cplusplus
extern "C"{
#endif

#define	MAX_REC_ITEM_NUMS						64
#define	MAX_REC_ITEM_NAME_LEN					40
#define	MAX_REC_ITEM_VALUE_LEN					16

//----------------------------------------------------------------------------
// Structure of the Network status
//----------------------------------------------------------------------------
typedef struct
{
    char main_resolution       [MAX_REC_ITEM_VALUE_LEN];    // quarter/full
    char main_quality          [MAX_REC_ITEM_VALUE_LEN];    // superior/high/standard
    char main_fr_hd            [MAX_REC_ITEM_VALUE_LEN];    // 0-30
    char main_fr_ntsc          [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_ntsc_full     [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_ntsc_half     [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_ntsc_quad     [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_pal           [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_pal_full      [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_pal_half      [MAX_REC_ITEM_VALUE_LEN];
    char main_fr_pal_quad      [MAX_REC_ITEM_VALUE_LEN];
    char rec_type              [MAX_REC_ITEM_VALUE_LEN];    // none/continuous/motion/sensor/schedule
    char rec_audio             [MAX_REC_ITEM_VALUE_LEN];    // on/off
    char pre_record            [MAX_REC_ITEM_VALUE_LEN];
    char post_record           [MAX_REC_ITEM_VALUE_LEN];

} record_property_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  stop_all_record    (int ch);
int  get_recode_fps     (int ch, int dual);

#ifdef __cplusplus
}
#endif

#endif /* __AIFRECORD_H__ */
