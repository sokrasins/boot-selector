#include "key.h"

#include "hardware/gpio.h"
#include "bsp.h"
#include <stdbool.h>

#define KEY_MAX 8U

key_ctx_t *_keys[KEY_MAX];
int num_keys = 0;

key_state_t key_state_toggle(key_state_t in);

void key_init(key_ctx_t *key, unsigned int led_pin, cap_sense_key_t cap_key, key_action_t key_action)
{
    key->cap_key = cap_key;
    key->led_pin = led_pin;
    key->state = KEY_STATE_OFF;
    key->action = key_action;

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
            _keys[i]->action(_keys[i], evt);
            bsp_led_write((bool) evt);
        }
    }
}

key_state_t key_state_toggle(key_state_t in)
{
    return (in == KEY_STATE_ON ? KEY_STATE_OFF : KEY_STATE_ON);
}
