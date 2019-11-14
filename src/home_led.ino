#include "FastLED.h"

#define NUM_LEDS 40
// PSU_ON is active low
#define PSU_ON 5

        CRGB leds[NUM_LEDS];
        void setup() {
          FastLED.addLeds<WS2812B, 2, GRB>(leds, NUM_LEDS);
          for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = CRGB::Black; FastLED.show(); //delay(50); 
                //leds[0] = CRGB::Black; FastLED.show(); delay(30);
                 // ok; might get hot after a while, not tested
                //LEDS.setBrightness(50); // Too bright; hot reg
                //LEDS.setBrightness(100); // Too bright; regulator on arduino smells
          }
          FastLED.show();
          pinMode(PSU_ON, OUTPUT);
          digitalWrite(PSU_ON, LOW);
          // Let PSU voltage settle - otherwise latter LEDs might not get set correctly and will latch
          delay(500);
          
          for (int i = 0; i < NUM_LEDS; i++) {
                //if (i>25) {
                leds[i] = CRGB::Purple; FastLED.show(); delay(50);
                LEDS.setBrightness(100);
                //}
                //leds[0] = CRGB::Black; FastLED.show(); delay(30);
                 // ok; might get hot after a while, not tested
                //LEDS.setBrightness(50); // Too bright; hot reg
                //LEDS.setBrightness(100); // Too bright; regulator on arduino smells
          }
          FastLED.show();
          // Power down after 10s - until remote control is setup
          delay(10000);
          digitalWrite(PSU_ON, HIGH);
        }
        void loop() { 


          for (int i = 0; i < NUM_LEDS; i++) {
                //if (i>25) {
                leds[i] = CRGB::Purple; FastLED.show(); //delay(50);
                LEDS.setBrightness(100);
                //}
                //leds[0] = CRGB::Black; FastLED.show(); delay(30);
                 // ok; might get hot after a while, not tested
                //LEDS.setBrightness(50); // Too bright; hot reg
                //LEDS.setBrightness(100); // Too bright; regulator on arduino smells
          }
          FastLED.show();
        }
