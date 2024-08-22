#include "console.h"

#include <stdint.h>

#include "tusb.h"
#include "reboot.h"
#include "cap_sense.h"

#define CDC_MAX_CMD_BUF 256U
#define CDC_MAX_BEFORE_CLEAR (CDC_MAX_CMD_BUF / 2)

#define CONSOLE_UNREC_CMD "    Unrecognized command\r\n"
#define CONSOLE_BOOT_MODE "    Boot mode\r\n"

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
    char output[100];

    tud_cdc_write("\r\n", 3); 
    reset = true;
    if (strcmp(cmd, "boot\r") == 0)
    {
      valid_cmd = true;
      tud_cdc_write(CONSOLE_BOOT_MODE, sizeof(CONSOLE_BOOT_MODE) - 1); 

      reboot(true);
    }
    else if (strcmp(cmd, "maj\r") == 0)
    {
      valid_cmd = true;
      int size = sprintf(output, "    major: %d\r\n", cap_get_major());
      tud_cdc_write(output, size);
    }
    else if (strcmp(cmd, "min\r") == 0)
    {
      valid_cmd = true;
      int size = sprintf(output, "    minor: %d\r\n", cap_get_minor());
      tud_cdc_write(output, size);
    }
    else if (strcmp(cmd, "ver\r") == 0)
    {
      valid_cmd = true;
      int size = sprintf(output, "    version: %d\r\n", cap_get_version());
      tud_cdc_write(output, size);
    }
    else if (strcmp(cmd, "keys\r") == 0)
    {
      valid_cmd = true;
      uint8_t new_key_state = 0;
      at42qt_get_key_status(&new_key_state);
      int size = sprintf(output, "    key state: %d\r\n", new_key_state);
      tud_cdc_write(output, size);
    }

    if (!valid_cmd)
    {
      tud_cdc_write(CONSOLE_UNREC_CMD, sizeof(CONSOLE_UNREC_CMD) - 1); 
    }

    //tud_cdc_write("\r\n", 3); 

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