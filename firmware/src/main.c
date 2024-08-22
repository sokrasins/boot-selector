/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"

#include "msc_disk.h"
#include "console.h"
#include "boot_switch.h"
#include "reboot.h"
#include "cap_sense.h"

#include "hardware/gpio.h"

// Pin I have the LED driver connected to
#define DEMO_KEY_PIN 15U

// Callbacks
void cap_sense_cb(cap_sense_key_t key, cap_sense_evt_t evt, void *data);

/*------------- MAIN -------------*/
int main(void)
{
    board_init();
    boot_switch_init();

    // Set the file to serve based on switch state
    msc_set_file(boot_switch_get());
    //board_led_write(boot_switch_get());

    // Init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    // Hack in a pin for our switch indicator
    gpio_init(DEMO_KEY_PIN);
    gpio_set_dir(DEMO_KEY_PIN, GPIO_OUT);
    
    sleep_ms(1000);

    cap_sense_init();
    cap_sense_reg_cb(cap_sense_cb);

    while (1)
    {
        tud_task(); // tinyusb device task
        console_cdc_task(); // Consume console activity
        boot_switch_task(); // Check for state change of switch
        cap_sense_task(); // Check for changes in cap sense

        sleep_ms(10);
    }

    return 0;
}

void cap_sense_cb(cap_sense_key_t key, cap_sense_evt_t evt, void *data)
{
    // TODO printf("key: %d, evt: %d\r\n", key, evt);
    if (key == CAP_SENSE_KEY_2)
    {
        board_led_write((bool) evt);
        gpio_put(DEMO_KEY_PIN, (bool) evt);
    }
}
