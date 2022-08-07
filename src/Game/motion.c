#include "linker.h"
#include "game.h"
#include "GM_Control.h"
#include "libgv/libgv.h"
#include "unknown.h"

#pragma INCLUDE_ASM("asm/sub_80034EAC.s")

int GM_ConfigMotionControl_80034F08(OBJECT *pObj, MOTION_CONTROL *pMCtrl, int name, void *a4, void* a5, GM_Control *pCtrl,
                                    SVECTOR *rots)
{
    pMCtrl->field_00_oar_ptr = GV_GetCache_8001538C(GV_CacheID_800152DC(name, 'o'));
    pMCtrl->field_3C = &pObj->field_18;
    pMCtrl->field_04.field_0 = 0;
    pMCtrl->field_04.field_2 = 0;
    pMCtrl->field_04.field_4 = 0;
    pMCtrl->field_04.field_8 = 0;
    pMCtrl->field_04.field_C = a4;
    pMCtrl->field_04.field_10 = 0;
    pMCtrl->field_04.field_12 = 0;
    pMCtrl->field_04.field_14 = 0;
    pMCtrl->field_04.field_16 = 0;
    pMCtrl->field_1C.field_0 = 0;
    pMCtrl->field_1C.field_2 = 0;
    pMCtrl->field_1C.field_4 = 0;
    pMCtrl->field_1C.field_8 = -1;
    pMCtrl->field_1C.field_10 = 0;
    pMCtrl->field_1C.field_12 = 0;
    pMCtrl->field_1C.field_14 = 0;
    pMCtrl->field_1C.field_16 = 0;
    pMCtrl->interp = 0;
    pMCtrl->field_4C = rots;
    pMCtrl->field_34 = &pCtrl->field_8_vec;
    pMCtrl->step = &pCtrl->field_44_vec;
    pMCtrl->field_1C.field_C = a5;
    pObj->objs->rots = rots;
    pObj->objs->waist_rot = &pMCtrl->field_44;
    pObj->m_ctrl = pMCtrl;
    return 0;
}

int GM_ConfigMotionAdjust_80035008(OBJECT *pObj, SVECTOR *adjust)
{
    pObj->objs->adjust = adjust;
    return 0;
}

#pragma INCLUDE_ASM("asm/sub_8003501C.s")

void sub_800350D4(MOTION_CONTROL *pCtrl, int a2, int a3)
{
    Motion_0x18* pSub;

    MATRIX mtx; // [sp+10h] [-20h] BYREF
    ReadRotMatrix_80092DD8(&mtx);

    pSub = &pCtrl->field_1C;
    if ( pSub->field_0 )
    {
        sub_8003603C(pCtrl, pSub);
    }
    
    if ( !a3 )
    {
        Process_Oar_8003518C(pCtrl, pSub, a2);

    }
    else
    {
        sub_800360EC(pCtrl, pSub, a2, a3);
    }
    
    if ( pSub->field_0 == 1 )
    {
        pSub->field_14 = 2;
        pSub->field_10 = a2;
    }
    else
    {
        pSub->field_14 = 1;
        pSub->field_10 = a2;
    }
    
    SetRotMatrix_80093218(&mtx);
}

#pragma INCLUDE_ASM("asm/Process_Oar_8003518C.s")
#pragma INCLUDE_ASM("asm/Kmd_Oar_Inflate_800353E4.s")
#pragma INCLUDE_ASM("asm/sub_8003556C.s")
#pragma INCLUDE_ASM("asm/oar_related_800356FC.s")
#pragma INCLUDE_ASM("asm/sub_80035F34.s")

void sub_80035FFC(MOTION_CONTROL *pCtrl)
{
    sub_8003603C(pCtrl, &pCtrl->field_04);
}

void sub_8003601C(MOTION_CONTROL *pCtrl)
{
    sub_8003603C(pCtrl, &pCtrl->field_1C);
}

#pragma INCLUDE_ASM("asm/sub_8003603C.s")
#pragma INCLUDE_ASM("asm/sub_800360EC.s")
#pragma INCLUDE_ASM("asm/sub_80036388.s")
#pragma INCLUDE_ASM("asm/negate_rots_800366B8.s")
