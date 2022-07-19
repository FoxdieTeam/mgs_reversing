#include "sna_init.h"

extern void GM_ClearPlayerStatusFlag_8004E2D4(unsigned int param_1);
extern void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags);


void sub_8004F2EC(Actor_SnaInit *snake)
{
  GM_ClearPlayerStatusFlag_8004E2D4(0x800000);
  sna_init_clear_flags_8004E308(snake, 1);
  **(ushort **)&snake->field_8A0 = **(ushort **)&snake->field_8A0 | 0x9e;
  return;
}