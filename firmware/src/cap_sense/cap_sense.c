#include "cap_sense.h"

#include <stddef.h>
#include "at42qt1070.h"

static cap_sense_cb_t _cb = NULL;
static  uint8_t old_key_state;

uint8_t major = 0;
uint8_t minor = 0;
uint8_t version = 0;

status_t cap_sense_init(void)
{
    status_t status = at42qt_init();

    at42qt_get_chipid(&major, &minor);
    at42qt_get_fwversion(&version);

    return status;

    // TODO: Set up cap sense sensitivity and stuff
}

void cap_sense_task(void)
{
    // stuff
    uint8_t new_key_state;
    status_t status = at42qt_get_key_status(&new_key_state);

    uint8_t key_changes = old_key_state ^ new_key_state;

    for (uint8_t i=0; i<8; i++)
    {
        if ((key_changes >> i) & 1)
        {
            if (_cb != NULL)
            {
                _cb(CAP_SENSE_KEY_1+i, (cap_sense_evt_t) ((new_key_state >> i) & 1), NULL);
            }
        }
    }

    old_key_state = new_key_state;
}

status_t cap_sense_reg_cb(cap_sense_cb_t cb)
{
    status_t status = STATUS_BAD_PARAMS;

    if(cb != NULL)
    {
        _cb = cb;
        status = STATUS_OK;
    }

    return status;
}

uint8_t cap_get_major(void)
{
    return major;
}


uint8_t cap_get_minor(void)
{
    return minor;
}

uint8_t cap_get_version(void)
{
    return version;
}
