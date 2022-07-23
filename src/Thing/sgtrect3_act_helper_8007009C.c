#include "dgd.h"
#include <sys/types.h>
#include <libgte.h>

extern void DG_Clip_80017594(RECT *pClipRect,int dist);
extern DG_CHNL DG_Chanls_800B1800[3];

void sgtrect3_act_helper_8007009C()
{
    DG_CHNL* chnl = &DG_Chanls_800B1800[1];
    DG_Clip_80017594(&chnl->field_5C_rect,(int)chnl->word_6BC3BC);
    SetRotMatrix_80093218(&chnl->field_10_matrix);
    SetTransMatrix_80093248(&chnl->field_10_matrix);
}