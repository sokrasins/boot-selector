#include "key.h"

#include "hardware/gpio.h"
#include <stdbool.h>

#define KEY_MAX 8U

key_ctx_t *_keys[KEY_MAX];
int num_keys = 0;

key_state_t key_state_toggle(key_state_t in);

void key_init(key_ctx_t *key, unsigned int led_pin, cap_sense_key_t cap_key)
{
    key->cap_key = cap_key;
    key->led_pin = led_pin;
    key->state = KEY_STATE_OFF;

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    if (num_keys < KEY_MAX)
    {
        _keys[num_keys] = key;
        num_keys++;
    }
}

void key_cap_cb(cap_sense_key_t key, cap_sense_evt_t evt, void *data)
{
    for (int i=0; i<num_keys; i++)
    {
        if (_keys[i]->cap_key == key)
        {
            if (evt == CAP_SENSE_EVT_KEY_ON)
            {
                _keys[i]->state = key_state_toggle(_keys[i]->state);
                gpio_put(_keys[i]->led_pin, (bool) _keys[i]->state);
            }
        }
    }
}

key_state_t key_state_toggle(key_state_t in)
{
    return (in == KEY_STATE_ON ? KEY_STATE_OFF : KEY_STATE_ON);
}

