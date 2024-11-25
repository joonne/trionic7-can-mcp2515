#ifndef CD_CHANGER_H
#define CD_CHANGER_H

#include "mcp_can.h"

class CdChanger {
public:
  CdChanger(MCP_CAN can);
  void handshake();
  void heartbeat();

private:
  MCP_CAN _can;
};

#endif // "CD_CHANGER_H"
