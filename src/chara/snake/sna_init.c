#include "sna_init.h"

void sna_init_set_flags_8004E2F4(Actor_SnaInit *snake, unsigned int flags)
{
	snake->field_898_flags |= flags;
}

void sna_init_clear_flags_8004E308(Actor_SnaInit *snake, unsigned int flags)
{
  snake->field_898_flags &= ~flags;
}
