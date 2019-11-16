#ifndef _PROTO_H_

#include "stdint.h"
#include "stdbool.h"
#include "led.pb.h"

struct decoded_data {
  uint32_t *colors;
  uint32_t num_colors;
  uint32_t brightness;
};

typedef struct decoded_data decoded_data_t;

bool decode(uint8_t *buffer, uint32_t len, decoded_data_t *data);

#endif /* _PROTO_H_ */
