#include "blood.h"

extern int GM_CurrentMap_800AB9B0;

extern void d_blood_loader_helper_80072B24(Actor_Blood* actor_blood);

int d_blood_loader_80072B38(Actor_Blood* actor_blood)
{
    actor_blood->current_map = GM_CurrentMap_800AB9B0;
    d_blood_loader_helper_80072B24(actor_blood);
    return 0;
}
