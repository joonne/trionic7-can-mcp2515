#include "communication.h"
#include "defines.h"
#include "headers.h"
#include "mcp_can.h"
#include "mcp_can_dfs.h"
#include <Arduino.h>

MCP_CAN CAN(CAN_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (CAN.begin(MCP_ANY, I_BUS, MCP_8MHZ) != CAN_OK) {
    delay(100);
  }
  CAN.setMode(MCP_NORMAL);
}

void loop() { readCanBus(); }

unsigned char CDC_HEARTBEAT_CMD[8] = {0xE0, 0x00, 0x3F, 0x31,
                                      0xFF, 0xFF, 0xFF, 0xD0};
unsigned char CDC_HANDSHAKE_CMD[8] = {0x62, 0x00, 0x00, 0x16,
                                      0x01, 0x02, 0x00, 0x00};

void cdcHeartbeat() {
  CAN.sendMsgBuf(static_cast<unsigned long>(CAN_ID::CDC_HEARTBEAT), 8,
                 CDC_HEARTBEAT_CMD);
}

void cdcHandshake() {
  CAN.sendMsgBuf(static_cast<unsigned long>(CAN_ID::CDC_HANDSHAKE_RESPONSE), 8,
                 CDC_HANDSHAKE_CMD);
}

void readCanBus() {
  uint8_t len;
  uint8_t data[8];
  unsigned long id;

  cdcHeartbeat();

  if (CAN.checkReceive() == CAN_NOMSG) {
    DEBUG_MESSAGE("No message received");
    return;
  }

  if (CAN.readMsgBuf(&id, &len, data) == CAN_OK) {
    switch (static_cast<CAN_ID>(id)) {
    case CAN_ID::CDC_HANDSHAKE_REQUEST: {
      DEBUG_MESSAGE("CD_CHANGER_REQUEST");
      return cdcHandshake();
    }
    case CAN_ID::STEERING_WHEEL_BUTTONS: {
      auto action = getHighBit(data[AUDIO]);
      DEBUG_MESSAGE("IBUS_BUTTONS: " + String(action));
      return steeringWheelActions(static_cast<STEERING_WHEEL>(action));
    }
    default: {
      DEBUG_MESSAGE("Unknown CAN ID: " + String(id));
      return;
    }
    }
  }
}

void steeringWheelActions(STEERING_WHEEL action) {
  switch (action) {
  case STEERING_WHEEL::NXT:
    DEBUG_MESSAGE("NEXT");
    break;
  case STEERING_WHEEL::SEEK_DOWN:
    DEBUG_MESSAGE("SEEK DOWN");
    break;
  case STEERING_WHEEL::SEEK_UP:
    DEBUG_MESSAGE("SEEK UP");
    break;
  case STEERING_WHEEL::SRC:
    DEBUG_MESSAGE("SRC");
    break;
  case STEERING_WHEEL::VOL_UP:
    DEBUG_MESSAGE("VOL+");
    break;
  case STEERING_WHEEL::VOL_DOWN:
    DEBUG_MESSAGE("VOL-");
    break;
  }
}

/*
  Checks every bit of the given value until finds the first high bit and then
  returns the position of that; or if none are high, returns 0xFF (255).
  @param value
  @return - first high bit of the given value or 0xFF
*/
uint8_t getHighBit(uint8_t value) {
  if (!value) {
    return 0xFF;
  }

  for (uint8_t i = 0; i < 8; i++) {
    if (value >> i & 1) {
      return i;
    }
  }

  return 0xFF;
}
