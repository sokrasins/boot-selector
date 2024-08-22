#ifndef BSP_PINDEF_H_
#define BSP_PINDEF_H_

#include <stdbool.h>

#define BSP_PINDEF_KEY1 15U
#define BSP_PINDEF_KEY2 14U

#define BSP_PINDEF_SDA  4U
#define BSP_PINDEF_SCL  5U

void bsp_led_write(bool on);

#endif /*BSP_PINDEF_H_*/
