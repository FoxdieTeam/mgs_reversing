#include "linker.h"
#include "door.h"
#include "libgv.h"
#include "gcl.h"
#include "libdg.h"

int GV_SendMessage_80016504(GV_MSG *);
void sub_80032858(SVECTOR *a1, int a2);
int mts_nullsub_8_8008BB98(int, const char *, ...);

extern int dword_800ABA0C;

void door_send_msg_8006EC10(unsigned short addr, unsigned short a2)
{
  GV_MSG msg;

  msg.message[0] = 0xF9AD;
  msg.address = addr;
  msg.message[1] = a2;
  msg.message_len = 2;
  GV_SendMessage_80016504(&msg);
}

void door_act_helper_8006EC48(struct Actor_Door *pDoor)
{
  int v1;
  GCL_ARGS arg_struct;
  long args[4];

  if (pDoor->field_100_param_f_v >= 0)
  {
    v1 = 54732;
    if (pDoor->field_E2_maybe_state == 2)
    {
      v1 = 3538;
    }

    args[0] = v1;
    args[1] = pDoor->field_F0;
    args[2] = (unsigned short)pDoor->field_F6_map_num;

    arg_struct.argc = 3;
    arg_struct.argv = args;

    GCL_ExecProc_8001FF2C(pDoor->field_100_param_f_v, &arg_struct);
  }
}
