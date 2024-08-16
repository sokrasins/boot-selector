#ifndef BSP_I2C_H_
#define BSP_I2C_H_

#include <stddef.h>
#include <stdint.h>

#include "status.h"

status_t bsp_i2c_init(uint8_t addr);

status_t bsp_i2c_read(uint8_t reg, uint8_t *val);

status_t bsp_i2c_write(uint8_t reg, uint8_t val);

#endif /*BSP_I2C_H_*/