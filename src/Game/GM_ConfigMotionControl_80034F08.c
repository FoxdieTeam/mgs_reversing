#include "linker.h"
#include "game.h"
#include "GM_Control.h"
#include "libgv/libgv.h"

void                 *GV_GetCache_8001538C(int hash);

int GM_ConfigMotionControl_80034F08(OBJECT *pObj, MOTION_CONTROL *pMCtrl, int name, int a4, int a5, GM_Control *pCtrl, SVECTOR *rots)
{
    pMCtrl->field_00_oar_ptr = GV_GetCache_8001538C(GV_CacheID_800152DC(name, 'o'));
    pMCtrl->field_3C = &pObj->field_18;
    pMCtrl->field_04 = 0;
    pMCtrl->field_06 = 0;
    pMCtrl->field_08 = 0;
    pMCtrl->field_0C = 0;
    pMCtrl->field_10 = a4;
    pMCtrl->field_14 = 0;
    pMCtrl->field_16 = 0;
    pMCtrl->field_18 = 0;
    pMCtrl->field_1A = 0;
    pMCtrl->field_1C = 0;
    pMCtrl->field_1E = 0;
    pMCtrl->field_20 = 0;
    pMCtrl->field_24 = -1;
    pMCtrl->field_2C = 0;
    pMCtrl->field_2E = 0;
    pMCtrl->field_30 = 0;
    pMCtrl->field_32 = 0;
    pMCtrl->interp = 0;
    pMCtrl->field_4C = rots;
    pMCtrl->field_34 = &pCtrl->field_8_vec;
    pMCtrl->step = &pCtrl->field_44_vec;
    pMCtrl->field_28 = a5;
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
