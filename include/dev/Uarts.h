#ifndef __UARTS_H__
#define __UARTS_H__

#ifdef __cplusplus
extern "C"{
#endif

#define U_INIT_READY        (-2)
#define U_OPEN_READY        (-3)
#define U_INVALID_PORT      (-4)
#define U_OPEN_FAIL         (-5)

int open_uart               (char *dev, int baudrate, int databit, int stopbit, int parity);
int close_uart              (int uartfd);
int write_to_uart           (int uartfd, unsigned char *p, int nSize);
int read_from_uart          (int uartfd, unsigned char *p, int nSize);
int read_block_from_uart    (int uartfd, unsigned char *p, int size);
int uart_flush              (int uartfd);


#ifdef __cplusplus
}
#endif

#endif //__UARTS_H__
