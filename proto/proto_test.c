#include "proto.h"

#include "stdio.h"

#define BUF_SIZE 100

int main(int nargs, char *argv[]) {
//  if (nargs != 2) {
//    // Accept only proto
//    return -1;
//  }

/*  char buf[BUF_SIZE];
  printf("Decode 1\n");
  // TODO: Handle NULLs
  decode((uint8_t*)"\x12\x02\x0a\x00", 4, (uint8_t *)buf, BUF_SIZE);*/
  char data[] = {   0x0a, 0x02, 0x08, 0x32, 0x12, 0x13, 0x0a, 0x05, 0x08, 0x80, 0x81, 0x80,
   0x04, 0x0a, 0x05, 0x08, 0x80, 0x80, 0xfc, 0x07, 0x0a, 0x03, 0x08, 0xff,
   0x01
    };
  printf("Decode 2\n");
  uint32_t buf2[BUF_SIZE];
  memset(buf2, 0, BUF_SIZE*sizeof(uint32_t));
  decoded_data_t data_out = {
    .colors = buf2,
    .num_colors = BUF_SIZE
  };

  decode((uint8_t*)data, 25, &data_out);
  printf("data_out.brightness: %d\n", data_out.brightness);
  printf("Done\n");
}
