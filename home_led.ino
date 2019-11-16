//#include <led.pb.h>
//#include <proto.h>

#include "FastLED.h"
#include "proto/proto.h"

// Linker tricks because including these as a library causes the build not to run. Yay Arduino IDE!
#include "proto/led.pb.c"
#include "proto/proto.c"

#define NUM_LEDS 40
// PSU_ON is active low
#define PSU_ON 5

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(PSU_ON, OUTPUT);
  digitalWrite(PSU_ON, LOW);

  // Let PSU voltage settle - otherwise latter LEDs might not get set correctly and will latch
  //delay(1000);

  Serial.begin(115200);
  Serial.setTimeout(1000);

  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show();
  }
  FastLED.show();

  // TEST LEDS
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple; FastLED.show();
    LEDS.setBrightness(100);
  }
  FastLED.show();
}

#define SER_BUF_SIZE 1000

void serialHandle(uint8_t *buf, size_t len) {
  uint8_t out[NUM_LEDS];
  decode(buf, len, out, (uint32_t) NUM_LEDS);
  // Set LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    // LED colors map directly to CRGB constants
    leds[i] = out[i];
    FastLED.show();
  }
}

void serialLoop(void) {
  uint8_t buf[SER_BUF_SIZE];
  memset(buf, 0, SER_BUF_SIZE);
  // Read up to 1k, just hit timeout
  size_t n_bytes = Serial.readBytes(buf, SER_BUF_SIZE);

  if (n_bytes > 0) {
    serialHandle(buf, n_bytes);
  }
}

void loop() {
  serialLoop();
}
