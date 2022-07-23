#include "libdg.h"
#include "game.h"
#include "idaTypes.h"
#include "rcm.h"
#include "libdg.h"

// nikita

extern char         aNikita[]; // "nikita"
extern char         aRcmL_0[]; // "rcl_l"
extern int          aDd_800AB878;
extern SVECTOR      dword_800AB880;
extern const char 	aRcmC[];
extern int          GM_CurrentMap_800AB9B0;
extern short 		d_800AB9EC_mag_size;
extern short 		dword_800ABA2C;

extern int          GV_StrCode_80016CCC(const char *string);
extern void         GM_ConfigObjectRoot_80034C5C(OBJECT *obj, OBJECT *parent_obj, int num_parent);
extern void         GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
extern DG_PRIM      *DG_MakePrim_8001BABC(int type, int prim_count, int chanl, SVECTOR *pVec, int *pRect);
extern int          DG_QueuePrim_80018274(DG_OBJS *pPrim);
extern void         GM_FreeObject_80034BF8(OBJECT *obj);



void rcm_loader_helper_80066AF8(POLY_FT4 *poly,DG_TEX *texture)
{
    u_char offx;
    u_char offy;
    u_char offx_width;
    u_char offy_height;
    
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    
    offx = texture->field_8_offx;
    offx_width = offx + texture->field_A_width;

    offy = texture->field_9_offy;
    offy_height = offy + texture->field_B_height;

    setUV4(poly, offx, offy, offx_width, offy, offx, offy_height, offx_width, offy_height);
    poly->tpage = texture->field_4_tPage;
    poly->clut = texture->field_6_clut;
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

void rcm_act_80066BC0(int param_1,int param_2,int param_3,unsigned int param_4);

Actor_Rcm *NewRCM_80066FF0(int param_1,OBJECT *parent_obj,int num_parent,int param_4,int param_5)
{
	Actor_Rcm *rcm;
	int iVar1;

	rcm = (Actor_Rcm *)GV_NewActor_800150E4(6,100);
	if (rcm != (Actor_Rcm *)0x0)
	{
		GV_SetNamedActor_8001514C((Actor *)rcm,rcm_act_80066BC0,rcm_kill_80066E68,aRcmC);
		iVar1 = rcm_loader_80066EB0(rcm,parent_obj,num_parent);
		
		if (iVar1 < 0)
		{
			GV_DestroyActor_800151C8((Actor *)rcm);
			return (Actor_Rcm *)0x0;
		}
		
		rcm->f44 = param_1;
		rcm->f48 = (int)parent_obj;
		rcm->f4c = num_parent;
		rcm->f50 = param_4;
		rcm->f54 = param_5;
		rcm->f60 = 0;
		rcm->f58 = 0;
	}
	dword_800ABA2C = 0;
	d_800AB9EC_mag_size = 0;
	return rcm;
}
