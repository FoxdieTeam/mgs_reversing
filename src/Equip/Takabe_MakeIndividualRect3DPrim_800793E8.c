#include "Game/game.h"
#include "Script_tbl_map_8002BB44.h"
#include "Game/GM_Control.h"
#include "map/map.h"
#include "libdg/libdg.h"
#include <LIBGPU.H>

extern int GM_CurrentMap_800AB9B0;
int        SECTION(".sbss") GM_CurrentMap_800AB9B0;

// TODO: move to header
void Takabe_MakeIndividualRect3DPrim_helper_80079284(void);

static inline void DG_GroupPrim(prim, group_id) DG_PRIM *prim;
int                group_id;
{
    prim->group_id = group_id;
}

DG_PRIM *Takabe_MakeIndividualRect3DPrim_800793E8(int prim_count, SVECTOR *pVec)
{
    DG_PRIM *pNewPrim;

    pNewPrim = DG_MakePrim_8001BABC(0x2012, prim_count, 0, pVec, 0);
    if (pNewPrim)
    {
        DG_QueuePrim_80018274((DG_OBJS *)pNewPrim);
        DG_GroupPrim(pNewPrim, GM_CurrentMap_800AB9B0);
    }
    pNewPrim->field_50_pFn = (TPrim_Fn)Takabe_MakeIndividualRect3DPrim_helper_80079284;
    pNewPrim->field_48_prim_count = prim_count;
    return pNewPrim;
}
