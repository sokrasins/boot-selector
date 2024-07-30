#include "console.h"

#include <stdint.h>

#include "tusb.h"
#include "reboot.h"

#define CDC_MAX_CMD_BUF 256U
#define CDC_MAX_BEFORE_CLEAR (CDC_MAX_CMD_BUF / 2)

#define CONSOLE_UNREC_CMD "Unrecognized command"
#define CONSOLE_BOOT_MODE "Boot mode"

bool _console_parse(char *cmd, int len);

char buf[CDC_MAX_CMD_BUF];
uint32_t idx = 0;

void console_cdc_task(void)
{
    // connected and there are data available
    if ( tud_cdc_available() )
    {
        // read data
        uint32_t count = tud_cdc_read(&buf[idx], sizeof(buf) - idx);

        // Echo back
        tud_cdc_write(&buf[idx], count);

        idx += count;
        
        // Check for a valid command
        if(_console_parse(buf, idx))
        {
            memset(buf, 0, CDC_MAX_CMD_BUF);
            idx = 0;
        }

        // Flush output
        tud_cdc_write_flush();
    }
}

// PRIVATE FUNCTIONS

bool _console_parse(char *cmd, int len)
{
  bool reset = false;
  bool valid_cmd = false;
  
  if (len > CDC_MAX_BEFORE_CLEAR)
  {
    reset = true;
  }

  if (cmd[len-1] == '\r')
  {
    reset = true;
    if (strcmp(cmd, "boot\r") == 0)
    {
      valid_cmd = true;
      tud_cdc_write(CONSOLE_BOOT_MODE, sizeof(CONSOLE_BOOT_MODE) - 1); 

      reboot(true);
    }

    if (!valid_cmd)
    {
      tud_cdc_write(CONSOLE_UNREC_CMD, sizeof(CONSOLE_UNREC_CMD) - 1); 
    }

  }

  return reset;
}

// UNUSED CALLBACKS

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
  (void) itf;
  (void) rts;

  // TODO set some indicator
  if ( dtr )
  {
    // Terminal connected
  }else
  {
    // Terminal disconnected
  }
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf)
{
  (void) itf;
}