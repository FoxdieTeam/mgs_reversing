#include "sgtrect3.h"
#include "dgd.h"
#include <libgte.h>

extern void		DG_Clip_80017594(RECT *pClipRect,int dist);
extern			DG_CHNL DG_Chanls_800B1800[3];
extern char		byte_8009F5F8[];
extern PlayerStatusFlag		GM_PlayerStatus_800ABA50;

void sgtrect3_act_helper_helper_80070040(void *ot, void *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

extern void SetTransMatrix_80093248(MATRIX*);
extern void SetRotMatrix_80093218(MATRIX*);
void sgtrect3_act_helper_8007009C()
{
    DG_CHNL* chnl = &DG_Chanls_800B1800[1];
    DG_Clip_80017594(&chnl->field_5C_rect,(int)chnl->word_6BC3BC);
    SetRotMatrix_80093218(&chnl->field_10_matrix);
    SetTransMatrix_80093248(&chnl->field_10_matrix);
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_helper_800700E0.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_800701A8.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_8007020C.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070568.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070820.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070AB0.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070CAC.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_80070E14.s")

void sgtrect3_kill_80070EC0(Actor_sgtrect3* actor_sgtrect3)
{
    byte_8009F5F8[0] = 0;
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_helper_80070ECC.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_80070F4C.s")
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_init_80071010.s")
