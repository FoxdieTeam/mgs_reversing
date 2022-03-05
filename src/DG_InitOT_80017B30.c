#include "libdg.h"
#include "dgd.h"

void DG_InitOT_80017B30(DG_CHNL *pChanl, int idx)
{
    pChanl->field_5C_rect = pChanl->field_64_rect;
    pChanl->field_6C_dr_env[idx] = pChanl->field_16C_dr_env[idx];
}
