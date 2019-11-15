#include "FastLED.h"
#include "proto/proto.h"

#define NUM_LEDS 40
// PSU_ON is active low
#define PSU_ON 5

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);

  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show();
  }
  FastLED.show();
  pinMode(PSU_ON, OUTPUT);
  digitalWrite(PSU_ON, LOW);
  // Let PSU voltage settle - otherwise latter LEDs might not get set correctly and will latch
  delay(500);
}

#define SER_BUF_SIZE 1000

void serialHandle(uint8_t *buf, size_t len) {
  decode(buf, len);
  // Set LEDs
  if (message.led_string.leds.color == Color_BLACK) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show();
    }
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Purple; FastLED.show();
    }
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
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple; FastLED.show();
    LEDS.setBrightness(100);
  }
  FastLED.show();
}
