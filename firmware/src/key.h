#ifndef KEY_H_
#define KEY_H_

#include <stdint.h>
#include "cap_sense.h"

#define GPIO_PIN_INVALID 0xFF

typedef enum {
    KEY_STATE_OFF,
    KEY_STATE_ON,
} key_state_t;

typedef struct {
    unsigned int led_pin;
    cap_sense_key_t cap_key;
    key_state_t state;
} key_ctx_t;

void key_init(key_ctx_t *key, unsigned int led_pin, cap_sense_key_t cap_key);

void key_cap_cb(cap_sense_key_t key, cap_sense_evt_t evt, void *data);

#endif /*KEY_H_*/