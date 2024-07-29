#include <stdbool.h>

// Invoked when device is mounted
void tud_mount_cb(void)
{
  // STUB
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  // STUB
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  // STUB
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  // STUB
}