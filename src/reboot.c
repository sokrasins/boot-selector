#include "reboot.h"

#include <stddef.h>

#include "pico/bootrom.h"
#include "pico/multicore.h"

void _reboot_app(void);

void reboot(bool bootloader)
{

    // Do some core1 stuff that I don't understand yet
    multicore_reset_core1();
    multicore_launch_core1(NULL);

    if (bootloader)
    {
        // Reset to bootloader, no disabled interfaces
        reset_usb_boot(0, 0);
    }
    else
    {
        // Reset to app
        _reboot_app();
    }
}

void _reboot_app(void)
{
    // Magic incantation to perform a software reset
    *((volatile uint32_t*)(PPB_BASE + 0x0ED0C)) = 0x5FA0004;
}
