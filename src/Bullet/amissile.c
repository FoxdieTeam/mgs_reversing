#include "Game/object.h"
#include "Game/target.h"
#include "amissile.h"

// stinger missile?

#pragma INCLUDE_ASM("asm/Bullet/amissile_loader_helper_8006D1F4.s") // 172 bytes
#pragma INCLUDE_ASM("asm/Bullet/amissile_act_helper_8006D2A0.s")    // 220 bytes
#pragma INCLUDE_ASM("asm/Bullet/amissile_act_helper_8006D37C.s")    // 644 bytes

int amissile_act_helper_8006D600(void)
{
    return 0;
}

#pragma INCLUDE_ASM("asm/Bullet/amissile_act_8006D608.s")    // 916 bytes

extern int        dword_8009F490;
extern GM_Target *target_800BDF00;

void amissile_kill_8006D99C(Actor_amissile *pActor)
{
    DG_OBJS *pPrim;

    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    pPrim = (DG_OBJS *)pActor->field_134_prim;

    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }

    if (target_800BDF00)
    {
        target_800BDF00 = 0;
    }

    dword_8009F490 = 0;
}

extern MATRIX DG_ZeroMatrix_8009D430;

int amissile_loader_8006DA0C(Actor_amissile *pActor, MATRIX *pMtx, int arg2)
{
    GM_Control *pCtrl = &pActor->field_20_ctrl;
    OBJECT *pKmd;
    DG_OBJS *pObjs;
    RECT *pRect;
    DG_PRIM *pNewPrim;
    SVECTOR vector;
    int i;
    DG_TEX *pTex;

    if (Res_Control_init_loader_8002599C(pCtrl, 0, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);
    GM_ConfigControlHazard_8002622C(pCtrl, 100, 50, 50);

    pKmd = &pActor->field_9C_kmd;

    pCtrl->field_55_flags |= 4;
    pCtrl->field_59 = 8;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)pKmd, 0x76AB, 0x36D, 0);

    pObjs = pKmd->objs;

    if (!pObjs)
    {
        return -1;
    }

    pObjs->world = *pMtx;
    GM_ConfigObjectLight_80034C44(pKmd, &pActor->field_C0_matrix);

    pKmd->objs->objs[0].raise = -500;

    pRect = &pActor->field_138_rect;
    pRect->x = pRect->y = 30;
    pRect->w = pRect->h = 60;

    pActor->field_134_prim = pNewPrim = DG_GetPrim(0x412, 4, 0, pActor->field_140_svector_4Array, pRect);

    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos2_8001BC8C(&pCtrl->field_0_position, &pCtrl->field_8_rotator);

    vector.vz = 0;
    vector.vx = 0;
    vector.vy = 500;

    for (i = 0; i < 4; i++)
    {
        DG_RotVector_8001BE98(&vector, &pActor->field_140_svector_4Array[i], 1);
        vector.vy += 2000;
    }

    pTex = DG_GetTexture_8001D830(0xE4CC);

    if (!pTex)
    {
        return -1;
    }

    amissile_loader_helper_8006D1F4(pNewPrim->field_40_pBuffers[0], pTex);
    amissile_loader_helper_8006D1F4(pNewPrim->field_40_pBuffers[1], pTex);

    pNewPrim->world = DG_ZeroMatrix_8009D430;
    pNewPrim->type |= 0x100;
    return 0;
}

extern SVECTOR DG_ZeroVector_800AB39C;

extern const char aRmissileC[]; // = "amissile.c"

Actor_amissile * NewAMissile_8006DC50(MATRIX *pMtx, int arg2)
{
    Actor_amissile *pActor = (Actor_amissile *)GV_NewActor_800150E4(6, sizeof(Actor_amissile));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&amissile_act_8006D608,
                                  (TActorFunction)&amissile_kill_8006D99C, aRmissileC);

        if (amissile_loader_8006DA0C(pActor, pMtx, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        pActor->field_124 = 30;
        pActor->field_120 = 0;
        pActor->field_128 = 0;
        pActor->field_12C_svector = DG_ZeroVector_800AB39C;
    }

    return pActor;
}
