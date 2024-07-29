#ifndef BOOT_SWITCH_H_
#define BOOT_SWITCH_H_

#include <stdbool.h>

void boot_switch_init(void);

void boot_switch_task(void);

bool boot_switch_get(void);

#endif /*BOOT_SWITCH_H_*/