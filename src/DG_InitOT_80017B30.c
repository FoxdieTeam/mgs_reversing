#include "libdg.h"
#include "dgd.h"

void DG_InitOT_80017B30(DG_CHNL *pChanl, int idx)
{
    pChanl->dword_6BC3C8_pStructure_rect = pChanl->dword_6BC3D0_rect;
    pChanl->dword_6BC3D8_dst[idx] = pChanl->dword_6BC4D8_src_dr_env1[idx];
}
