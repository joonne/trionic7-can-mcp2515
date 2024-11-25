#include "CdChanger.h"
#include "communication.h"

unsigned char CDC_HEARTBEAT_CMD[8] = {0xE0, 0x00, 0x3F, 0x31,
                                      0xFF, 0xFF, 0xFF, 0xD0};
unsigned char CDC_HANDSHAKE_CMD[8] = {0x32, 0x00, 0x00, 0x16,
                                      0x01, 0x02, 0x00, 0x00};

CdChanger::CdChanger(MCP_CAN can) : _can(can) {}

void CdChanger::heartbeat() {
  _can.sendMsgBuf(static_cast<unsigned long>(CAN_MESSAGE_ID_OUT::CDC_HEARTBEAT),
                  8, CDC_HEARTBEAT_CMD);
}

void CdChanger::handshake() {
  _can.sendMsgBuf(
      static_cast<unsigned long>(CAN_MESSAGE_ID_OUT::CDC_HANDSHAKE_RESPONSE), 8,
      CDC_HANDSHAKE_CMD);
}
