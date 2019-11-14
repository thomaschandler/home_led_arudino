#include "FastLED.h"
#include "ext/nanopb/pb_decode.h"
#include "proto/led.pb.h"

#define NUM_LEDS 40
// PSU_ON is active low
#define PSU_ON 5

// Started from https://github.com/FastLED/FastLED/wiki/Overview#quick-examples

bool decode(uint8_t *buffer, uint32_t len) {
  // https://github.com/nanopb/nanopb/blob/master/examples/simple/simple.c#L52

  /* Allocate space for the decoded message. */
  ControlMessage message = ControlMessage_init_zero;

  /* Create a stream that reads from the buffer. */
  pb_istream_t stream = pb_istream_from_buffer(buffer, len);

  /* Now we are ready to decode the message. */
  bool status = pb_decode(&stream, ControlMessage_fields, &message);

  /* Check for errors... */
  if (!status)
  {
      printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
      return 1;
  }
}

CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show();
  }
  FastLED.show();
  pinMode(PSU_ON, OUTPUT);
  digitalWrite(PSU_ON, LOW);
  // Let PSU voltage settle - otherwise latter LEDs might not get set correctly and will latch
  delay(500);

  LEDS.setBrightness(100);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple; FastLED.show();
    delay(50);
  }
  FastLED.show();
  // Power down after 10s - until remote control is setup
  delay(10000);
  digitalWrite(PSU_ON, HIGH);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple; FastLED.show();
    LEDS.setBrightness(100);
  }
  FastLED.show();
}
