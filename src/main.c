#include "errno.h"
#include "hardware/clocks.h"
#include "hardware/watchdog.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "board/pico2.h"
#include "config/conf_board.h"
#include "modules/m_led.h"

// int64_t alarm_callback(alarm_id_t id, void *user_data) {
//   // Put your timeout handler code in here
//   return 0;
// }

int main() {
  bool rc = stdio_usb_init();
  if (!rc) {
    printf("Error: Unable to initialize USB stdio.\n");
    return -EIO;
  }

  while (!stdio_usb_connected()) {
    tight_loop_contents();
  }

  sleep_ms(500);
  printf("\n✅ USB Connected!\n");

  blink_init();

#ifdef LED_PIN
  blink_pin_forever(0, LED_PIN, 1);
#else
  blink_pin_forever(0, 6, 1);
#endif

  // Timer example code - This example fires off the callback after 2000ms
  // add_alarm_in_ms(2000, alarm_callback, NULL, false);
  // For more examples of timer use see
  // https://github.com/raspberrypi/pico-examples/tree/master/timer

  if (watchdog_caused_reboot()) {
    printf("Rebooted by Watchdog!\n");
  }

  printf("System Clock Frequency is %u Hz\n", clock_get_hz(clk_sys));
  printf("USB Clock Frequency is %u Hz\n", clock_get_hz(clk_usb));

  watchdog_enable(WATCHDOG_TIMEOUT_MS, 1);

  while (true) {
    printf("Hello, world!\n");
    sleep_ms(1000);
    watchdog_update();
  }
}
