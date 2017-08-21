#ifndef __AIFRECORD2_H__
#define	__AIFRECORD2_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_REC_VALUE_LEN   32

//----------------------------------------------------------------------------
// Structure of the Record2 Property
//----------------------------------------------------------------------------
//
typedef struct
{
    char event_impact     [8];
    char event_trigger    [8];
} record2_property_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  aif_record2_init           (void);
int  aif_record2_set_property   (record2_property_t *prop);
int  aif_record2_get_property   (record2_property_t *prop);

#ifdef __cplusplus
}
#endif

#endif /* __AIFRECORD2_H__ */
