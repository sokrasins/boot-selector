#ifndef CAP_SENSE_H_
#define CAP_SENSE_H_

#include "status.h"

typedef enum {
    CAP_SENSE_KEY_1 = 0,
    CAP_SENSE_KEY_2,
    CAP_SENSE_KEY_3,
    CAP_SENSE_KEY_MAX,
} cap_sense_key_t;

typedef enum {
    CAP_SENSE_EVT_KEY_OFF,
    CAP_SENSE_EVT_KEY_ON,
} cap_sense_evt_t;

typedef void (*cap_sense_cb_t)(cap_sense_key_t key, cap_sense_evt_t evt, void *data);

status_t cap_sense_init(void);

void cap_sense_task(void);

status_t cap_sense_reg_cb(cap_sense_cb_t cb);

#endif /*CAP_SENSE_H_*/