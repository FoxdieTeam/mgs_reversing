#include "linker.h"
#include "libdg.h"

void DG_void_active_prim_buffer_8001AAD0(DG_OBJ *pObj, int idx);

void DG_void_all_prim_buffers_8001ABA8(DG_OBJS *pObjs, int idx)
{
    int n_models;
    DG_OBJ *pObj;

    n_models = pObjs->n_models;
    for (pObj = pObjs->objs; n_models > 0; ++pObj)
    {
        DG_void_active_prim_buffer_8001AAD0(pObj, idx);
        --n_models;
    }
}

void sub_8001AC00()
{

}
