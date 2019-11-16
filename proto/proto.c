#include "proto.h"

#include "pb_decode.h"

#define HAVE_STDIO 1

#ifdef HAVE_STDIO
#include "stdio.h"
#include "inttypes.h"
#endif

struct output_buf {
  uint32_t *out;
  uint32_t out_len;
  uint32_t offset;
};

// Started from https://github.com/FastLED/FastLED/wiki/Overview#quick-examples
// For submessage decoding, based off union example:
// https://github.com/nanopb/nanopb/blob/b2d04dfceaac1dc35fcde2706e56d090222d2761/examples/using_union_messages/decode.c#L18
// Submessages are encoded as string type, so will need
// pb_make_string_substream from pb_decode.h

// has_* usage:
// https://github.com/nanopb/nanopb/blob/master/examples/network_server/client.c#L61

// https://github.com/nanopb/nanopb/blob/2d8342e1849e6f095ca73566aa95e2ad2a3ce5ba/pb.h#L340
// https://github.com/nanopb/nanopb/blob/2399c48d61b582e990276e7c9ed58eda283862b3/docs/concepts.rst#decoding-callbacks
bool decode_leds(pb_istream_t *stream, const pb_field_t *field, void **arg) {
#ifdef HAVE_STDIO
  printf("decode_leds bytes_left: %d\n", (int)stream->bytes_left);
//  printf("field: %s\n", field);
#endif

  struct output_buf *out_state = (struct output_buf*) *arg;

  while (stream->bytes_left) {
    // Enums are 32-bit
    // https://developers.google.com/protocol-buffers/docs/proto3#enum
    LedState led_state = LedState_init_zero;
    if (!pb_decode(stream, LedState_fields, &led_state)) {
      return false;
    }
    // https://github.com/nanopb/nanopb/blob/b2d04dfceaac1dc35fcde2706e56d090222d2761/examples/using_union_messages/decode.c#L29
#ifdef HAVE_STDIO
  printf("led_state.color: %d\n", led_state.color);
#endif

    if (out_state->offset+1 < out_state->out_len) {
      out_state->out[out_state->offset++] = led_state.color;
    }
    else {
      // More LED states RX'd than LEDs, stop iterating
      break;
    }
  }

  return true;
}

bool decode(uint8_t *buffer, uint32_t len, uint32_t *out, uint32_t out_len) {
  // https://github.com/nanopb/nanopb/blob/master/examples/simple/simple.c#L52

  /* Allocate space for the decoded message. */
  ControlMessage message = ControlMessage_init_zero;

  struct output_buf arg = {
    .out = out,
    .out_len = out_len,
    .offset = 0
  };

  // Set up decode callback
  pb_callback_t leds_callback = {
    // https://github.com/nanopb/nanopb/blob/6a213568c13bed113ea31c6d19af2390fe0ebc64/tests/alltypes_callback/decode_alltypes_callback.c#L233
    .funcs = {
      .decode = &decode_leds
    },
    .arg = &arg
  };
  message.led_string.leds = leds_callback;
//  message.led_string = leds_callback;

  /* Create a stream that reads from the buffer. */
  pb_istream_t stream = pb_istream_from_buffer(buffer, len);

  /* Now we are ready to decode the message. */
  bool status = pb_decode(&stream, ControlMessage_fields, &message);

  /* Check for errors... */
  if (!status)
  {
#ifdef HAVE_STDIO
    printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
#endif
  return 1;
  }

#if HAVE_STDIO
//  printf("message.has_global_state: %d\n", message.global_state);
//  printf("message.led_string: %d\n", message.led_string);
#endif

//  LedString led_string;
//  status = pb_decode(&stream, LedString_fields, &led_string);
//
//  /* Check for errors... */
//  if (!status)
//  {
//#if HAVE_STDIO
//      printf("Decoding LedString failed: %s\n", PB_GET_ERROR(&stream));
//#endif
//      return 1;
//  }
//
//#if HAVE_STDIO
//  printf("LedString.leds: %s\n", led_string.leds);
//#endif

//  pb_istream_t led_string_stream;
//
//  // https://github.com/nanopb/nanopb/blob/b2d04dfceaac1dc35fcde2706e56d090222d2761/examples/using_union_messages/decode.c#L48
//  if (!pb_make_string_substream(&stream, &led_string_stream)) {
//#if HAVE_STDIO
//   printf("led_string decode failed: %s\n", PB_GET_ERROR(&stream));
//#endif
//   return -1;
//  }

  // https://github.com/nanopb/nanopb/blob/2399c48d61b582e990276e7c9ed58eda283862b3/docs/concepts.rst#field-callbacks


  return 0;
}

