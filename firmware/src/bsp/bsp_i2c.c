#include "bsp_i2c.h"

#include "hardware/i2c.h"
#include "status.h"

uint8_t _addr;

status_t bsp_i2c_init(uint8_t addr) 
{
    status_t status = STATUS_OK;
    _addr = addr;
    int err = i2c_init(i2c_default, 400 * 1000);
    if (err != 0)
    {
        status = STATUS_ERR;
    }

    return status;
}

status_t bsp_i2c_read(uint8_t reg, uint8_t *val) 
{
    status_t status = STATUS_OK;

    int err = i2c_write_blocking(i2c_default, _addr, &reg, 1, true);
    err |= i2c_read_blocking(i2c_default, _addr, val, 1, false);

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

    int err = i2c_write_blocking(i2c_default, _addr, buf, 2, false);

    if (err != 0)
    {
        status = STATUS_ERR;
    }

    return status;
}