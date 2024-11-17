#include "util.h"
#include <Arduino.h>
#include <unity.h>

void test_getHighBit() {
  TEST_ASSERT_EQUAL(0, getHighBit(0x01)); // First set bit at position 0
  TEST_ASSERT_EQUAL(7, getHighBit(0x80)); // First set bit at position 7 (MSB)
  TEST_ASSERT_EQUAL(1, getHighBit(0xAA)); // First set bit at position 1
  TEST_ASSERT_EQUAL(0, getHighBit(0x55)); // First set bit at position 0
  TEST_ASSERT_EQUAL(0xFF, getHighBit(0x00)); // No set bits (should return 0xFF)
}

void setup() { Serial.begin(9600); }

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_getHighBit);
  UNITY_END();
}
