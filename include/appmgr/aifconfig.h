#ifndef __AIFCONFIG_H__
#define	__AIFCONFIG_H__

#ifdef __cplusplus
extern "C"{
#endif

//----------------------------------------------------------------------------
// Application Interface function prototypes
//----------------------------------------------------------------------------
int  aif_config_save_to_usb      (void);
int  aif_config_load_from_usb    (void);

#ifdef __cplusplus
}
#endif

#endif /* __AIFCONFIG_H__ */
