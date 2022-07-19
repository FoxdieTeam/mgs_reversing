#include "sna_init.h"

void SetSnakeFlag_8004E2F4(Actor_SnaInit *snake, unsigned int flag)
{
	snake->field_898_flags |= flag;
}