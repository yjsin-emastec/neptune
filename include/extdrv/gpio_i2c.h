#ifndef _GPIO_I2C_H
#define _GPIO_I2C_H

#define DEV_NODE_GPIOI2C             "/dev/gpioi2c"

#define GPIO_I2C_READ                0x01
#define GPIO_I2C_WRITE               0x03

/*
 * I2C device addresses
 */
#define I2C_ADDR_ISL12022            0xDE

/*
 * device's function index
 */
#define	GPIO_I2C_DEV_FUNC_0          0

typedef struct
{
	unsigned dev_type;
	unsigned clk_freq;
	unsigned dev_addr;
	unsigned reg_addr;
	unsigned reg_data;
} gpio_i2c_access_t;

unsigned char gpio_i2c_read(unsigned char devaddress, unsigned char address, unsigned int *r_data);
void gpio_i2c_write(unsigned char devaddress, unsigned char address, unsigned char data);
#endif
