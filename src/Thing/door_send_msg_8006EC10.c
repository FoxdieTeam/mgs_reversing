#include "linker.h"
#include "libgv.h"

int GV_SendMessage_80016504(GV_MSG *);

void door_send_msg_8006EC10(unsigned short addr, unsigned short a2)
{
  GV_MSG msg;

  msg.message[0] = 0xF9AD;
  msg.address = addr;
  msg.message[1] = a2;
  msg.message_len = 2;
  GV_SendMessage_80016504(&msg);
}
