#pragma once

#include <Arduino.h>

#define DEBUG 0

#define CAN_CS_PIN 10

#define AUDIO 2
#define SID 3

#define I_BUS CAN_47KBPS
#define P_BUS CAN_500KBPS

#if DEBUG
#define DEBUG_MESSAGE(msg) Serial.println(msg);
#else
#define DEBUG_MESSAGE(msg)
#endif
