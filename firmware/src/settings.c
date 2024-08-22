#include "settings.h"

#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)

const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

settings_os_t settings_read_os(void)
{
    settings_os_t ret = (settings_os_t)*flash_target_contents;
    if (ret > SETTINGS_OS_INVALID)
    {
        ret = SETTINGS_OS_LINUX;
    }

    return ret;
}

void settings_write_os(settings_os_t choice)
{
    uint8_t buf[8];
    buf[0] = 1;

    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, buf, 8);  
    restore_interrupts(interrupts);
}