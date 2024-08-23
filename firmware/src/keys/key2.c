#include "key2.h"

#include <stdbool.h>

#include "key1.h"
#include "cap_sense.h"
#include "bsp.h"
#include "msc_disk.h"
#include "settings.h"
#include "bsp/board.h"

key_ctx_t key_2;

void key_2_action(key_ctx_t *key, cap_sense_evt_t evt);

void key_2_init(void)
{
    key_init(&key_2, BSP_PINDEF_KEY2, CAP_SENSE_KEY_3, key_2_action);
}

void key_2_action(key_ctx_t *key, cap_sense_evt_t evt)
{
    if (key->state == KEY_STATE_OFF && evt == CAP_SENSE_EVT_KEY_ON)
    {
        tud_disconnect();
        msc_set_file((settings_os_t) key_1.state); // ON -> Win, OFF -> Linux
        sleep_ms(1000);
        tud_connect();    
    }

    if (evt == CAP_SENSE_EVT_KEY_ON) { key->state = KEY_STATE_ON; }
    else if (evt == CAP_SENSE_EVT_KEY_OFF) { key->state = KEY_STATE_OFF; }
}