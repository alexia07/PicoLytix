#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/spi.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
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

int32_t main() {
  stdio_usb_init();
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

  watchdog_enable(WATCHDOG_TIMEOUT_MS, 1);

  // printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
  // printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
  // For more examples of clocks use see
  // https://github.com/raspberrypi/pico-examples/tree/master/clocks

  // Set up our UART
  // uart_init(UART_ID, BAUD_RATE);
  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // Use some the various UART functions to send out data
  // In a default system, printf will also output via the default UART

  // Send out a string, with CR/LF conversions
  // uart_puts(UART_ID, " Hello, UART!\n");

  // For more examples of UART use see
  // https://github.com/raspberrypi/pico-examples/tree/master/uart

  while (true) {
    printf("Hello, world!\n");
    sleep_ms(1000);
  }
}
