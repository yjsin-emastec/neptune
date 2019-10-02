#ifndef __LIS331DLH_H__
#define __LIS331DLH_H__

#include <linux/ioctl.h>

typedef struct _lis331dlh_reg_rw
{
	unsigned int chip;
	unsigned int addr;
	int value;
} lis331dlh_reg_rw;

typedef struct _lis331dlh_acc_data
{
	int x;
	int y;
	int z;
} lis331dlh_acc_data;

#define LIS331DLH_G_2G 0x00
#define LIS331DLH_G_4G 0x10
#define LIS331DLH_G_8G 0x30

#define LIS331DLH_IOC_MAGIC            't'

#define LIS331DLH_CMD_READ_REG		_IOWR(LIS331DLH_IOC_MAGIC, 1, lis331dlh_reg_rw)
#define LIS331DLH_CMD_WRITE_REG		_IOW(LIS331DLH_IOC_MAGIC, 2, lis331dlh_reg_rw)
#define LIS331DLH_CMD_READ_SENSOR	_IOR(LIS331DLH_IOC_MAGIC, 3, lis331dlh_acc_data)
#define LIS331DLH_CMD_WRITE_SENSOR	_IOW(LIS331DLH_IOC_MAGIC, 4, lis331dlh_acc_data)

#endif /*__LIS331DLH__ */


