#include "gamestate.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "linker.h"
#include "strctrl.h"
#include "game.h"

extern void       GM_ContinueStart_8002B62C( void );

typedef struct Over
{
	struct Actor f00_base;
	short        f20;
	short        f22;
	short        f24;
	short        f26;
	short        f28;
} Over;