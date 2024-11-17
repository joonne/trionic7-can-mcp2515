#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>

#define DEBUG 0

#define CAN_CS_PIN 10

#define AUDIO 2
#define SID 3

#define I_BUS CAN_47KBPS
#define P_BUS CAN_500KBPS

#define DEBUG_MESSAGE(msg) Serial.println(msg);

#endif // DEFINES_H
