#ifndef __AENC_H__
#define __AENC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

void aenc_set_record (int channel, int start);
int  aenc_get_fd     (int channel);
int  aenc_start      (void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 

#endif

