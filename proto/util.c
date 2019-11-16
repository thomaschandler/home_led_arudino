#include "util.h"

CRGB map_pb_color_to_crgb(uint32_t pb_color) {
  switch (pb_color) {
    case 0xff:
			return CRGB::Blue;
		case 0x8000:
			return CRGB::Green;
		case 0xff0000:
			return CRGB::Red;
		case 0x800080:
			return CRGB::Purple;
    default:
      return CRGB::Black;
  }
}
