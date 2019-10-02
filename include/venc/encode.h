#ifndef __ENCODE_H__
#define __ENCODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

int encode_init                (void);
int encode_deinit              (void);
int encode_start               (EncodeEvent *pEncodeEvent);
int encode_stop                (EncodeEvent *pEncodeEvent);
int encode_set_channel_config  (EncodeEvent *pEncodeEvent);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 

#endif

