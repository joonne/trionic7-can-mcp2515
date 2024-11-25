#include "CdChanger.h"
#include "SteeringWheelButtons.h"
#include "communication.h"
#include "defines.h"
#include "mcp_can.h"
#include "mcp_can_dfs.h"
#include <Arduino.h>

MCP_CAN CAN(CAN_CS_PIN);
CdChanger CDC(CAN);

void readCanBus() {
  uint8_t len;
  uint8_t data[8];
  unsigned long id;

  if (CAN.checkReceive() == CAN_NOMSG) {
    Serial.println("No message received");
    return;
  }

  if (CAN.readMsgBuf(&id, &len, data) == CAN_OK) {
    switch (static_cast<CAN_MESSAGE_ID_IN>(id)) {
    case CAN_MESSAGE_ID_IN::CDC_HANDSHAKE_REQUEST: {
      Serial.println("CDC_HANDSHAKE_REQUEST");
      return CDC.handshake();
    }
    case CAN_MESSAGE_ID_IN::STEERING_WHEEL_BUTTONS: {
      Serial.println("STEEERING_WHEEL_BUTTONS");
      return SteeringWheelButtons::onFrame(data);
    }
    default: {
      Serial.println("UNKNOWN CAN MESSAGE ID: " + String(id));
      return;
    }
    }
  }
}

void setup() {
  Serial.begin(115200);

  while (CAN.begin(MCP_ANY, I_BUS, MCP_8MHZ) != CAN_OK) {
    Serial.println("CAN BUS FAIL!");
    delay(100);
  }
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  CDC.heartbeat();
  readCanBus();
  delay(500);
}
