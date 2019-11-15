#include "FastLED.h"
#include "proto/proto.h"

#define NUM_LEDS 40
// PSU_ON is active low
#define PSU_ON 5

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
