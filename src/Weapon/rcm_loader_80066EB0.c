#include "acm.h"
#include "libdg.h"
#include "idaTypes.h"

extern char         aNikita[];
extern char         aRcmL_0[];

extern int          aDd_800AB878;
extern SVECTOR      dword_800AB880;
extern int          GM_CurrentMap_800AB9B0;

extern int          GV_Strcode_80016CCC(const char *string);
extern void         GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void         GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
extern DG_PRIM      *DG_MakePrim_8001BABC(int type, int prim_count, int chanl, SVECTOR *pVec, int *pRect);
extern int          DG_QueuePrim_80018274(DG_OBJS *pPrim);

int rcm_loader_80066EB0(Actor_Rcm *actor, int *a2, int a3)
{
    DG_PRIM    *pNewPrim;
    DG_TEX     *pTexture;
    OBJECT     *obj;
    int        new_var, new_var2;

    obj = &actor->f20_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, GV_Strcode_80016CCC(aNikita), 109, 0);
    if (!obj->objs)
        return -1;
    
    GM_ConfigObjectRoot_80034C5C(obj, (OBJECT*)a2, a3);
    
    pNewPrim = DG_MakePrim_8001BABC(1042, 1, 0, &dword_800AB880, &aDd_800AB878);
    if (pNewPrim)
    {
        DG_QueuePrim_80018274((DG_OBJS*)pNewPrim);
        new_var2 = GM_CurrentMap_800AB9B0;
        pNewPrim->group_id = new_var2;
    }
    
    actor->f5c_prim = pNewPrim;
    if (pNewPrim)
    {
        pTexture = DG_FindTexture_8001D830(GV_Strcode_80016CCC(aRcmL_0));
        if (pTexture)
        {
            rcm_loader_helper_80066AF8(pNewPrim->field_40_pBuffers[0], (int)pTexture);
            rcm_loader_helper_80066AF8(pNewPrim->field_40_pBuffers[1], (int)pTexture);
            new_var = 0x48;
            pNewPrim->root = (int)(*a2 + ((a3 * 0x5C) + new_var));
            return 0;
        }
    }
    
    return -1;
}