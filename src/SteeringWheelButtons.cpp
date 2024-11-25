#include "SteeringWheelButtons.h"
#include <Arduino.h>

SteeringWheelButtons::STEERING_WHEEL_BUTTON
SteeringWheelButtons::decode(const unsigned char &data) {
  switch (data) {
  case 0x59: // NXT
    return STEERING_WHEEL_BUTTON::NXT;
  default:
    Serial.println("Unknown button: " + String(data));
  }
  return STEERING_WHEEL_BUTTON::NONE;
}

void SteeringWheelButtons::onFrame(unsigned char data[8]) {
  switch (SteeringWheelButtons::decode(data[0])) {
  case STEERING_WHEEL_BUTTON::NXT:
    Serial.println("NEXT");
    break;
  case STEERING_WHEEL_BUTTON::SEEK_DOWN:
    Serial.println("SEEK DOWN");
    break;
  case STEERING_WHEEL_BUTTON::SEEK_UP:
    Serial.println("SEEK UP");
    break;
  case STEERING_WHEEL_BUTTON::SRC:
    Serial.println("SRC");
    break;
  case STEERING_WHEEL_BUTTON::VOL_UP:
    Serial.println("VOL+");
    break;
  case STEERING_WHEEL_BUTTON::VOL_DOWN:
    Serial.println("VOL-");
    break;
  case STEERING_WHEEL_BUTTON::NONE:
    Serial.println("NONE");
    break;
  }
}
