#include "util.h"

uint8_t getHighBit(uint8_t value) {
  if (value == 0) {
    return 0xFF;
  }

  for (uint8_t i = 0; i < 8; i++) {
    if (value & (1 << i)) {
      return i;
    }
  }

  return 0xFF;
}
