#include "proto.h"

#include "stdio.h"

int main(int nargs, char *argv[]) {
//  if (nargs != 2) {
//    // Accept only proto
//    return -1;
//  }

  ControlMessage message;
  printf("Decode 1\n");
  // TODO: Handle NULLs
  decode((uint8_t*)"\x12\x02\x0a\x00", 4, &message);
  char data[] = {0x12, 0x08, 0x0a, 0x02, 0x08, 0x03, 0x0a, 0x02, 0x08, 0x01};
  printf("Decode 2\n");
  decode((uint8_t*)data, 10, &message);
//  printf("led_string[0].leds[0].color: %d\n", message.led_string.leds.color);
}
