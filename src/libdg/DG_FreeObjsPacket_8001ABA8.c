#include "linker.h"
#include "libdg.h"
#include <libgpu.h>

extern void GV_FreeMemory2_80016078(unsigned int, void **);
int DG_AllocPacks_8001A670(DG_OBJ *pObj, int idx);
void DG_InitPolyGT4Pack_8001A6E4(DG_OBJ *pPrim, int idx);
void DG_WriteObjPacketUV_8001A774(DG_OBJ *pObj, int idx);
void DG_WriteObjPacketRGB_8001A9B8(DG_OBJ *pDGObj, int idx);

extern int GV_Clock_800AB920;

int DG_MakeObjPacket_8001AA50(DG_OBJ *pPrim, int idx, int flags)
{
    if (DG_AllocPacks_8001A670(pPrim, idx) < 0)
    {
        return -1;
    }

    DG_InitPolyGT4Pack_8001A6E4(pPrim, idx);

    if ((flags & 1) != 0)
    {
        DG_WriteObjPacketUV_8001A774(pPrim, idx);
    }

    if ((flags & 2) != 0)
    {
        DG_WriteObjPacketRGB_8001A9B8(pPrim, idx);
    }

    return 0;
}

void DG_FreeObjPacket_8001AAD0(DG_OBJ *pObj, int idx)
{
    POLY_GT4 **ppPack;

    ppPack = &pObj->packs[idx];
    if (*ppPack)
    {
        GV_FreeMemory2_80016078(idx, (void**)ppPack);
        *ppPack = 0;
    }
}

int DG_MakeObjsPacket_8001AB14(DG_OBJS *pObjs, int idx)
{

    int flag = pObjs->flag;
    int n_models = pObjs->n_models;

    DG_OBJ *pObj = pObjs->objs;
    while (n_models > 0)
    {
        if (!pObj->packs[idx])
        {
            if (DG_MakeObjPacket_8001AA50(pObj, idx, flag) < 0)
            {
                return -1;
            }
        }
        pObj++;
        n_models--;
    }
    return 0;
}

void DG_FreeObjsPacket_8001ABA8(DG_OBJS *pObjs, int idx)
{
    int n_models;
    DG_OBJ *pObj;

    n_models = pObjs->n_models;
    for (pObj = pObjs->objs; n_models > 0; ++pObj)
    {
        DG_FreeObjPacket_8001AAD0(pObj, idx);
        --n_models;
    }
}

void DG_PrimStart_8001AC00()
{
}

typedef struct _Prim_Point
{
    short x;
    short y;
} Prim_Point;

void DG_8001AC08(Prim_Point *xy0, Prim_Point *xy1, Prim_Point *xy2, Prim_Point *xy3)
{
    int x0 = xy0->x;
    int x1 = xy1->x;
    int y0 = xy0->y;
    int y1 = xy1->y;
    int x1_x0_diff = x1 - x0;
    int y1_y0_diff = y1 - y0;

    if ( x1_x0_diff < 0 )
    {
        x1_x0_diff = -x1_x0_diff;
    }

    if ( y1_y0_diff < 0 )
    {
        y1_y0_diff = -y1_y0_diff;
    }

    if ( y1_y0_diff >= x1_x0_diff )
    {
        xy2->x = x0 + 2;
        xy2->y = y0;
        xy3->x = x1 + 2;
        xy3->y = y1;
    }
    else
    {
        xy2->y = y0 + 1;
        xy2->x = x0;
        xy3->x = x1;
        xy3->y = y1 + 1;
    }
}

void DG_8001AC74(DG_PRIM *pPrims, int prim_type)
{
    // TODO: Check if these prim types are actually correct when we have more context
    if ( prim_type == 21 )
    {
        int n_prims;
        POLY_FT4 *i = (POLY_FT4 *)pPrims->field_40_pBuffers[GV_Clock_800AB920];
        for (n_prims = (signed short)pPrims->n_prims ; n_prims > 0; --n_prims )
        {
            DG_8001AC08((Prim_Point *)&i->x0, (Prim_Point *)&i->x1, (Prim_Point *)&i->x2, (Prim_Point *)&i->x3);
            i++;
        }
    }
    else // prim_type == 22 ?
    {
        int n_prims;
        POLY_GT4 *i = (POLY_GT4 *)pPrims->field_40_pBuffers[GV_Clock_800AB920];
        for (n_prims = (signed short)pPrims->n_prims ; n_prims > 0; --n_prims )
        {
            DG_8001AC08((Prim_Point *)&i->x0, (Prim_Point *)&i->x1, (Prim_Point *)&i->x2, (Prim_Point *)&i->x3);
            i++;
        }
    }
}

