#include "bsp_pindef.h"
#include "bsp/board.h"

void bsp_led_write(bool on)
{
    board_led_write(on);  
}