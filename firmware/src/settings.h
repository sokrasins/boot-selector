#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <stdint.h>

typedef enum {
    SETTINGS_OS_LINUX = 0,
    SETTINGS_OS_WINDOWS = 1,
    SETTINGS_OS_INVALID
} settings_os_t;

settings_os_t settings_read_os(void);

void settings_write_os(settings_os_t choice);

#endif /*SETTINGS_H_*/