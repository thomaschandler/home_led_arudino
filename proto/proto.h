#ifndef _PROTO_H_

#include "stdint.h"
#include "stdbool.h"
#include "led.pb.h"

bool decode(uint8_t *buffer, uint32_t len, uint8_t *out, uint32_t out_len);

#endif /* _PROTO_H_ */
