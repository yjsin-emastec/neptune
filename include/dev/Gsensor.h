#ifndef _GSENSOR_H_
#define _GSENSOR_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
    GESNSOR_LEVEL1 = 1,
    GESNSOR_LEVEL2,
    GESNSOR_LEVEL3,
    GESNSOR_LEVEL4,
    GESNSOR_LEVEL5,
    GESNSOR_MAX
} GSENSOR_LEVEL_TYPE_E;

int  gsensor_init           (void);
int  gsensor_deinit         (void);
int  gsensor_data_read      (int *x, int *y, int *z);
void gsensor_config         (void);
int  gsensor_get_rawdata    (int *x, int *y, int *z);

#ifdef __cplusplus
}
#endif

#endif /* _GSENSOR_H_*/
