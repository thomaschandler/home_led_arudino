//#include <led.pb.h>
//#include <proto.h>

#include "FastLED.h"
#include "proto/util.h"

// AutoReset https://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection/

// Linker tricks because including these as a library causes the build not to run. Yay Arduino IDE!
#include "proto/led.pb.c"
#include "proto/proto.c"
#include "proto/util.c"

#define NUM_LEDS 40
// PSU_ON is active low
#define PSU_ON 5

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(PSU_ON, OUTPUT);
  digitalWrite(PSU_ON, HIGH);

  // Let PSU voltage settle - otherwise latter LEDs might not get set correctly and will latch
  //delay(1000);

  Serial.begin(115200);
  Serial.setTimeout(100);

  FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);
/*
  // TEST LEDS
  LEDS.setBrightness(50);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple;
  }
  FastLED.show();
  delay(10000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  */
  //digitalWrite(PSU_ON, HIGH);
  // TODO: Protobuf?
  Serial.println("READY");
}

#define SER_BUF_SIZE 1000

void serialHandle(uint8_t *buf, size_t len) {
  // Color consts are enums - 32-bit
  uint32_t out[NUM_LEDS];
  memset(out, 0, NUM_LEDS*sizeof(uint32_t));
  decoded_data_t data_out = {
    .colors = out,
    .num_colors = NUM_LEDS
  };
  // TODO: Check decode success
  decode(buf, len, &data_out);
  //Serial.println((char*)out);
  bool need_psu = false;
  // Pre-scan to make sure PSU has enough time to settle. Rough, but it'll do
  for (int i = 0; i < len; i++) {
    if (data_out.colors[i] != CRGB::Black) {
      // Need PSU
      need_psu = true;
    }
  }
  if (need_psu) {
    // power on
    digitalWrite(PSU_ON, LOW);
  }
  else {
    // power on
    digitalWrite(PSU_ON, HIGH);
  }
  // Set LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    // LED colors map directly to CRGB constants
    // https://github.com/FastLED/FastLED/blob/dcbf39933f51a2a0e4dfa0a2b3af4f50040df5c9/pixelset.h#L74
    // TODO: Despite this, cannot assign integer to leds array. Doesn't appear to be any constant helpers either...
    leds[i] = map_pb_color_to_crgb(data_out.colors[i]);
    FastLED.show();
  }
}

void serialLoop(void) {
  uint8_t buf[SER_BUF_SIZE];
  memset(buf, 0, SER_BUF_SIZE);
  // Read up to 1k, just hit timeout
  size_t n_bytes = Serial.readBytes(buf, SER_BUF_SIZE);

  if (n_bytes > 0) {
    //Serial.println("n_bytes > 0");
    //Serial.println((char*)buf);
    //Serial.println(n_bytes);
    serialHandle(buf, n_bytes);
  }
}

void loop() {
  serialLoop();
}
