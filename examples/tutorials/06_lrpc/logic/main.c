#include <lrpc.h>
#include <stdio.h>
#include <string.h>
#include <timer.h>

// Every 500 ms use the RNG service to randomly select an LED to turn on or
// off and then use the LED service to control that LED.

uint8_t _number_of_leds = 0;

int main(void)
{
  // Uses the LED service to get how many LEDs are on the board.
  _number_of_leds = lrpc_call("get_number_of_leds", []);
  printf("Number of LEDs: %d\n", _number_of_leds);

  // // Then randomly turn on and off LEDs using the two services.
  // while (1)
  // {
  //   uint16_t random = lrpc_call("get_two_random_bytes", []);

  //   // 0xFF looks like 00000000 00000000 00000000 11111111
  //   // When doing a bitwise and (&), it masks (make zeros) all but the lowest 8 bits
  //   // Therefore, we do & 0xFF to get only the last 8 bits.
  //   uint8_t led_index = (random & 0xFF) % _number_of_leds;
  //   // Randomly choose to turn it on or off.
  //   uint8_t led_state = (random >> 8) > 0x7F;
  //   // Set an LED with the LED service.
  //   lrpc_call("set_led", [ led_index, led_state ]);

  //   delay_ms(500);
  // }

  return 0;
}