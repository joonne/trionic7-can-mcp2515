#pragma once

#include "communication.h"
#include <Arduino.h>

void readCanBus();
void steeringWheelActions(STEERING_WHEEL action);
uint8_t getHighBit(const uint8_t value);
