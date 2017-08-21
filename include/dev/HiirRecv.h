#ifndef _HIIR_RECV_H_
#define _HIIR_RECV_H_

int hiir_init      (void);
int hiir_deinit    (void);
int get_hiir_data  (unsigned char *data, int size);

#endif /* _HIIR_RECV_H_ */
