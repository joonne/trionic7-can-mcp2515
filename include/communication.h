#pragma once

enum SID_MESSAGE {
  ORDER,
  IDK,
  ROW,
  LETTER0,
  LETTER1,
  LETTER2,
  LETTER3,
  LETTER4
};

enum class CAN_ID : unsigned long int {
  STEERING_WHEEL_BUTTONS = 0x290,
  RADIO_MSG = 0x328,
  RADIO_PRIORITY = 0x348,
  O_SID_MSG = 0x33F,
  O_SID_PRIORITY = 0x358,
  TEXT_PRIORITY = 0x368,
  LIGHTING = 0x410,
  SPEED_RPM = 0x460,
  CDC_HEARTBEAT = 0x3C8,
  CDC_HANDSHAKE_REQUEST = 0x6A1,
  CDC_HANDSHAKE_RESPONSE = 0x6A2,
};

enum class STEERING_WHEEL : unsigned char {
  NXT = 2,
  SEEK_DOWN = 3,
  SEEK_UP = 4,
  SRC = 5,
  VOL_UP = 6,
  VOL_DOWN = 7
};

enum class SID_BUTTON : unsigned char {
  NPANEL = 3,
  UP = 4,
  DOWN = 5,
  SET = 6,
  CLR = 7
};
