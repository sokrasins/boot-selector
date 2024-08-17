#include "bsp_i2c.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "status.h"

uint8_t _addr;

#define PICO_I2C_INSTANCE   i2c0
#define PICO_I2C_SDA_PIN    6
#define PICO_I2C_SCL_PIN    7

status_t bsp_i2c_init(uint8_t addr) 
{
    status_t status = STATUS_OK;
    _addr = addr;
    int err = i2c_init(PICO_I2C_INSTANCE, 400 * 1000);
    if (err != 0)
    {
        status = STATUS_ERR;
    }

    gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);

    return status;
}

status_t bsp_i2c_read(uint8_t reg, uint8_t *val) 
{
    status_t status = STATUS_OK;

    int err = i2c_write_blocking(PICO_I2C_INSTANCE, _addr, &reg, 1, true);
    err |= i2c_read_blocking(PICO_I2C_INSTANCE, _addr, val, 1, false);

    if (err != 0)
    {
        status = STATUS_ERR;
    }

    return status;
}

status_t bsp_i2c_write(uint8_t reg, uint8_t val) 
{
    status_t status = STATUS_OK;
    
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = val; 

    int err = i2c_write_blocking(PICO_I2C_INSTANCE, _addr, buf, 2, false);

    if (err != 0)
    {
        status = STATUS_ERR;
    }

    return status;
}