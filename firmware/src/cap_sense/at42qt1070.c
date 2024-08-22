#include "at42qt1070.h"
#include "at42qt1070_regs.h"

#include "bsp_i2c.h"

// Debug until there's a real driver
status_t i2c_read(uint8_t addr, uint8_t reg, uint8_t *val) { return STATUS_OK; }
status_t i2c_write(uint8_t addr, uint8_t reg, uint8_t val) { return STATUS_OK; }

status_t at42qt_init(void)
{
    return bsp_i2c_init(AT42QT1070_ADDR);
}

status_t at42qt_get_chipid(uint8_t *major, uint8_t *minor)
{
    uint8_t data = 0;

    // TODO: This pops an error every time. Figure out why.
    status_t status = bsp_i2c_read(AT42QT_CHIP_ID, &data);
    //if (STATUS_OK != status) return status;

    *major = (data >> 4);
    *minor = (data & 0b00001111);

    return STATUS_OK;
}

status_t at42qt_get_fwversion(uint8_t *version)
{
    status_t status = bsp_i2c_read(AT42QT_FIRMWARE_VERSION, version);
    return status;
}

status_t at42qt_get_status(at42qt_status_t *det_status)
{
    status_t status = bsp_i2c_read(AT42QT_DET_STATUS, &det_status->byte);
    return status;
}

status_t at42qt_get_key_status(uint8_t *key_status)
{
    status_t status = bsp_i2c_read(AT42QT_KEY_STATUS, key_status);
    return status;   
}

status_t at42qt_get_key_signal(at42qt_key_t key, uint16_t *signal)
{
    uint8_t reg = 0;
    status_t status;

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_KEY_0_SIG_MSB;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_KEY_1_SIG_MSB;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_KEY_2_SIG_MSB;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_KEY_3_SIG_MSB;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_KEY_4_SIG_MSB;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_KEY_5_SIG_MSB;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_KEY_6_SIG_MSB;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    uint8_t data = 0;

    status = bsp_i2c_read(reg, &data);
    if (STATUS_OK != status) return status;

    *signal = ((uint16_t) data) << 8;
    
    status = bsp_i2c_read(reg+1, &data);
    if (STATUS_OK != status) return status;

    *signal |= data;

    return STATUS_OK;
}

status_t at42qt_get_ref_data(at42qt_key_t key, uint16_t *data)
{
    uint8_t reg = 0;
    status_t status;

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_REF_DATA_0_MSB;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_REF_DATA_1_MSB;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_REF_DATA_2_MSB;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_REF_DATA_3_MSB;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_REF_DATA_4_MSB;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_REF_DATA_5_MSB;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_REF_DATA_6_MSB;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    uint8_t val = 0;

    status = bsp_i2c_read(reg, &val);
    if (STATUS_OK != status) return status;

    *data = ((uint16_t) val) << 8;
    
    status = bsp_i2c_read(reg+1, &val);
    if (STATUS_OK != status) return status;

    *data |= val;

    return STATUS_OK;    
}

status_t at42qt_set_neg_thresh(at42qt_key_t key, uint8_t thresh)
{
    uint8_t reg = 0;

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_NTHR_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_NTHR_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_NTHR_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_NTHR_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_NTHR_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_NTHR_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_NTHR_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    return bsp_i2c_write(reg, thresh);
}

status_t at42qt_get_neg_thresh(at42qt_key_t key, uint8_t *thresh)
{
    uint8_t reg = 0;

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_NTHR_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_NTHR_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_NTHR_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_NTHR_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_NTHR_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_NTHR_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_NTHR_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    return bsp_i2c_read(reg, thresh);
}

status_t at42qt_set_avg_factor(at42qt_key_t key, at42qt_avg_factor_t factor)
{
    status_t status;
    uint8_t reg = 0;  
    uint8_t data = 0; 

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_AVE_AKS_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_AVE_AKS_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_AVE_AKS_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_AVE_AKS_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_AVE_AKS_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_AVE_AKS_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_AVE_AKS_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    status = bsp_i2c_read(reg, &data);
    if (STATUS_OK != status) return status;

    data &= 0b00000011;
    data |= ((int) factor << 2);

    return bsp_i2c_write(reg, data);
}

status_t at42qt_get_avg_factor(at42qt_key_t key, at42qt_avg_factor_t *factor)
{
    status_t status;
    uint8_t reg = 0;  
    uint8_t data = 0; 

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_AVE_AKS_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_AVE_AKS_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_AVE_AKS_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_AVE_AKS_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_AVE_AKS_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_AVE_AKS_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_AVE_AKS_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    status = bsp_i2c_read(reg, &data);
    if (STATUS_OK != status) return status;

    *factor = (at42qt_avg_factor_t) (data >> 2);
    
    return STATUS_OK;
}

status_t at42qt_set_key_suppression_group(at42qt_key_t key, at42qt_supp_group_t group)
{
    status_t status;
    uint8_t reg = 0;  
    uint8_t data = 0; 

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_AVE_AKS_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_AVE_AKS_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_AVE_AKS_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_AVE_AKS_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_AVE_AKS_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_AVE_AKS_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_AVE_AKS_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    status = bsp_i2c_read(reg, &data);
    if (STATUS_OK != status) return status;

    data &= 0b11111100;
    data |= group;

    return bsp_i2c_write(reg, data);
}

status_t at42qt_get_key_suppression_group(at42qt_key_t key, at42qt_supp_group_t *group)
{
    status_t status;
    uint8_t reg = 0;  
    uint8_t data = 0; 

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_AVE_AKS_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_AVE_AKS_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_AVE_AKS_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_AVE_AKS_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_AVE_AKS_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_AVE_AKS_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_AVE_AKS_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    status = bsp_i2c_read(reg, &data);
    if (STATUS_OK != status) return status;

    *group = (at42qt_avg_factor_t) (data & 0b00000011);
    
    return STATUS_OK;
}

status_t at42qt_set_det_integrator(at42qt_key_t key, uint8_t integrator)
{
    status_t status;
    uint8_t reg = 0;  

    if (integrator < 2)
    {
        return STATUS_BAD_PARAMS;
    }

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_DI_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_DI_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_DI_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_DI_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_DI_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_DI_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_DI_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    return bsp_i2c_write(reg, integrator);
}

status_t at42qt_get_det_integrator(at42qt_key_t key, uint8_t *integrator)
{
    status_t status;
    uint8_t reg = 0;  

    switch (key)
    {
        case AT42QT_KEY_0:
            reg = AT42QT_DI_KEY_0;
            break;
        case AT42QT_KEY_1:
            reg = AT42QT_DI_KEY_1;
            break;
        case AT42QT_KEY_2:
            reg = AT42QT_DI_KEY_2;
            break;
        case AT42QT_KEY_3:
            reg = AT42QT_DI_KEY_3;
            break;
        case AT42QT_KEY_4:
            reg = AT42QT_DI_KEY_4;
            break;
        case AT42QT_KEY_5:
            reg = AT42QT_DI_KEY_5;
            break;
        case AT42QT_KEY_6:
            reg = AT42QT_DI_KEY_6;
            break;
        default:
            return STATUS_BAD_PARAMS;
    }

    return bsp_i2c_read(reg, integrator);
}
