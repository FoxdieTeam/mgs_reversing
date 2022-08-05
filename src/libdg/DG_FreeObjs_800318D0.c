#include "linker.h"
#include "libdg.h"

void DG_FreeObjs_800318D0(DG_OBJS *pObjs)
{
    int n_models;
    DG_OBJ *pObj;

    n_models = pObjs->n_models;
    pObj = pObjs->objs;
    while ( n_models > 0)
    {
        DG_FreeObjPacket_8001AAD0(pObj, 0);
        DG_FreeObjPacket_8001AAD0(pObj, 1);
        --n_models;
         ++pObj;
    }
    DG_FreePreshade_80032110(pObjs);
    GV_Free_80016230(pObjs);
}

void sub_80031944(DG_OBJS *a1, SVECTOR *a2)
{
    a1->rots = a2;
}

void sub_8003194C(DG_OBJS *a1, SVECTOR *a2)
{
    a1->movs = a2;
}
