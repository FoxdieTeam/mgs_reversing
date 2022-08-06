#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"

void GM_ResetMemory_8002AA80(void)
{
    DG_TextureCacheInit_8001F25C();
    GV_ResetMemory_80014CF0();
    GM_ResetChara_8002A8B0();
}
