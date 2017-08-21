#ifndef __AIFSTORAGE_H__
#define	__AIFSTORAGE_H__

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_STO_VALUE_LEN	16

//----------------------------------------------------------------------------
// Structure of the System Property
//----------------------------------------------------------------------------
typedef struct
{
    char overwrite            [MAX_STO_VALUE_LEN];      // overwrite on/off
    char recording_limit      [MAX_STO_VALUE_LEN];      // limitted recording on/off
    char limit_days           [MAX_STO_VALUE_LEN];      // limitted recording period
    char temperature_limit    [MAX_STO_VALUE_LEN];      // limit of HDD's temperature
    char alarm                [MAX_STO_VALUE_LEN];      // alarm on/off
    char buzzer               [MAX_STO_VALUE_LEN];      // buzzer on/off

} storage_property_t;

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  aif_storage_init            (void);
int  aif_storage_set_property    (storage_property_t *prop);
int  aif_storage_get_property    (storage_property_t *prop);

#ifdef __cplusplus
}
#endif

#endif /* __AIFSYSTEM_H__ */
