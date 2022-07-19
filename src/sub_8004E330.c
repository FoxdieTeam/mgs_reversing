#include "sna_init.h"

void sub_8004E330(Actor_SnaInit *snake, unsigned int flag)
{
	snake->field_89C_pTarget = (GM_Target *)((unsigned int)snake->field_89C_pTarget | flag);
}