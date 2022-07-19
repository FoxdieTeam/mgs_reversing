#include "libdg.h"
#include "game.h"
#include "idaTypes.h"
#include "rcm.h"

// nikita

extern char         aNikita[]; // "nikita"
extern char         aRcmL_0[]; // "rcl_l"
extern int          aDd_800AB878;
extern SVECTOR      dword_800AB880;
extern int          GM_CurrentMap_800AB9B0;

extern int          GV_StrCode_80016CCC(const char *string);
extern void         GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void         GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
extern DG_PRIM      *DG_MakePrim_8001BABC(int type, int prim_count, int chanl, SVECTOR *pVec, int *pRect);
extern int          DG_QueuePrim_80018274(DG_OBJS *pPrim);
extern void         DG_FreePrim_8001BC04(int param_1);
extern void         GM_FreeObject_80034BF8(OBJECT *obj);

// @todo(Voxel): Replace param_1 with Prim_Union and use the correct members. Fine for now.
void rcm_loader_helper_80066AF8(int param_1, DG_TEX *texture)
{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;

  *((char *) (param_1 + 3)) = 9;
  *((char *) (param_1 + 7)) = 0x2e;

  cVar1 = texture->field_8_offx;
  cVar5 = cVar1 + texture->field_A_width;
  *((char *) (param_1 + 7)) = 0x2e;

  cVar2 = texture->field_B_height;
  cVar3 = texture->field_9_offy;

  *((char *) (param_1 + 0xd)) = cVar3;
  *((char *) (param_1 + 0x15)) = cVar3;
  cVar6 = cVar3 + cVar2;

  *((char *) (param_1 + 0xc)) = cVar1;
  *((char *) (param_1 + 0x14)) = cVar5;
  *((char *) (param_1 + 0x1c)) = cVar1;
  *((char *) (param_1 + 0x1d)) = cVar6;
  *((char *) (param_1 + 0x24)) = cVar5;
  *((char *) (param_1 + 0x25)) = cVar6;
  *((short *) (param_1 + 0x16)) = texture->field_4_tPage;
  *((short *) (param_1 + 0xe)) = texture->field_6_clut;
}

#pragma INCLUDE_ASM("asm/Weapon/rcm_act_helper_80066B58.s")
#pragma INCLUDE_ASM("asm/Weapon/rcm_act_80066BC0.s")

void rcm_kill_80066E68(int param_1)
{
    int iVar1;

    GM_FreeObject_80034BF8((OBJECT *)(param_1 + 0x20));
    iVar1 = *(int *)(param_1 + 0x5c);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
    return;
}

int rcm_loader_80066EB0(Actor_Rcm *actor, int *a2, int a3)
{
    DG_PRIM    *pNewPrim;
    DG_TEX     *pTexture;
    OBJECT     *obj;
    int        new_var, new_var2;

    obj = &actor->f20_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, GV_StrCode_80016CCC(aNikita), 109, 0);
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
        pTexture = DG_FindTexture_8001D830(GV_StrCode_80016CCC(aRcmL_0));
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

#pragma INCLUDE_ASM("asm/Weapon/NewRCM_80066FF0.s")
