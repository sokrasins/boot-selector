#include "key1.h"

#include <stdbool.h>

#include "hardware/gpio.h"
#include "cap_sense.h"
#include "bsp.h"

key_ctx_t key_1;

void key_1_action(key_ctx_t *key, cap_sense_evt_t evt);

void key_1_init(void)
{
    key_init(&key_1, BSP_PINDEF_KEY1, CAP_SENSE_KEY_2, key_1_action);
}

void key_1_action(key_ctx_t *key, cap_sense_evt_t evt)
{
    if (evt == CAP_SENSE_EVT_KEY_ON)
    {
        // Treat the state like a toggle switch
        key->state = key_state_toggle(key->state);
        gpio_put(key->led_pin, (bool) key->state);
    }
}