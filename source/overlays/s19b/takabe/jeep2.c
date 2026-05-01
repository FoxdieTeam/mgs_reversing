#include "common.h"
#include "game/game.h"

typedef struct _Jeep2Work
{
    /* +0x000 */ GV_ACT         actor;
    /* +0x020 */ void          *field_20;
    /* +0x024 */ CONTROL        control;
    /* +0x0A0 */ TARGET        *target;
    /* +0x0A4 */ OBJECT         jeep_b;
    /* +0x188 */ OBJECT         jeep_t;
    /* +0x26C */ OBJECT_NO_ROTS gun;
    /* +0x290 */ MATRIX         light[2];
    /* +0x2D0 */ OBJECT_NO_ROTS fhl;
    /* +0x2F4 */ OBJECT_NO_ROTS hl;
} Jeep2Work;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep2_800D667C.s")

void s19b_jeep2_800D6A70(Jeep2Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->jeep_b);
    GM_FreeObject(&work->jeep_t);
    GM_FreeObject((OBJECT *)&work->gun);
    GM_FreeObject((OBJECT *)&work->fhl);
    GM_FreeObject((OBJECT *)&work->hl);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->field_20);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep2_800D6AD8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep2_800D6B18.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep2_800D6F24.s")
