#include "boot_switch.h"

#include <stdbool.h>

#include "hardware/gpio.h"
#include "bsp/board.h"
#include "reboot.h"

#define BOOT_SWITCH_PIN 22U
#define BOOT_POLL_PERIOD 100 //ms

static bool first_switch_state = false;
static uint32_t start_ms = 0;

void boot_switch_init(void)
{
    // Config input switch
    gpio_init(BOOT_SWITCH_PIN);
    gpio_set_dir(BOOT_SWITCH_PIN, GPIO_IN);
    gpio_set_pulls(BOOT_SWITCH_PIN, true, false);

    // Get the state of the switch after pin is set up
    first_switch_state = gpio_get(BOOT_SWITCH_PIN);
}



void boot_switch_task(void)
{ 
    // Only check at a slow interval, this is lazy debouncing
    if ( board_millis() - start_ms < BOOT_POLL_PERIOD) return; // not enough time
    start_ms = board_millis();

    bool new_switch_state = gpio_get(BOOT_SWITCH_PIN);

    if (new_switch_state != first_switch_state)
    {
        // Reset the device, we'll serve the new file at next boot
        reboot(false);
    }
}

bool boot_switch_get(void)
{
    return first_switch_state;
}