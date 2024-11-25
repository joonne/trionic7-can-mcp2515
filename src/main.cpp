#include "SteeringWheelButtons.h"
#include "communication.h"
#include "defines.h"
#include "mcp_can.h"
#include "mcp_can_dfs.h"
#include <Arduino.h>

MCP_CAN CAN(CAN_CS_PIN);

unsigned char CDC_HEARTBEAT_CMD[8] = {0xE0, 0x00, 0x3F, 0x31,
                                      0xFF, 0xFF, 0xFF, 0xD0};
unsigned char CDC_HANDSHAKE_CMD[8] = {0x32, 0x00, 0x00, 0x16,
                                      0x01, 0x02, 0x00, 0x00};

void cdcHeartbeat() {
  CAN.sendMsgBuf(static_cast<unsigned long>(CAN_MESSAGE::CDC_HEARTBEAT), 8,
                 CDC_HEARTBEAT_CMD);
}

void cdcHandshake() {
  CAN.sendMsgBuf(
      static_cast<unsigned long>(CAN_MESSAGE::CDC_HANDSHAKE_RESPONSE), 8,
      CDC_HANDSHAKE_CMD);
}

void readCanBus() {
  uint8_t len;
  uint8_t data[8];
  unsigned long id;

  cdcHeartbeat();

  if (CAN.checkReceive() == CAN_NOMSG) {
    Serial.println("No message received");
    return;
  }

  if (CAN.readMsgBuf(&id, &len, data) == CAN_OK) {
    switch (static_cast<CAN_MESSAGE>(id)) {
    case CAN_MESSAGE::CDC_HANDSHAKE_REQUEST: {
      Serial.println("CDC_HANDSHAKE_REQUEST");
      return cdcHandshake();
    }
    case CAN_MESSAGE::STEERING_WHEEL_BUTTONS: {
      Serial.println("STEEERING_WHEEL_BUTTONS");
      return SteeringWheelButtons::onFrame(data);
    }
    default: {
      Serial.println("UNKNOWN CAN ID: " + String(id));
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
  readCanBus();
  delay(500);
}
