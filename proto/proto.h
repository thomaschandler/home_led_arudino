#ifndef _PROTO_H_

#include "stdint.h"
#include "stdbool.h"
#include "led.pb.h"

bool decode(uint8_t *buffer, uint32_t len, ControlMessage *out);

#endif /* _PROTO_H_ */
