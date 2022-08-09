#include "sgtrect3.h"
#include "libdg/dgd.h"
#include <LIBGTE.H>
#include "psyq.h"

// stinger missile first person HUD + stinger HUD?

extern DG_CHNL          DG_Chanls_800B1800[3];
extern char             byte_8009F5F8[];
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void sgtrect3_act_helper_helper_80070040(void *ot, void *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

void sgtrect3_act_helper_8007009C()
{
    DG_CHNL *chnl = &DG_Chanls_800B1800[1];
    DG_Clip_80017594(&chnl->field_5C_clip_rect, chnl->field_4C_clip_distance);
    SetRotMatrix_80093218(&chnl->field_10_transformation_matrix);
    SetTransMatrix_80093248(&chnl->field_10_transformation_matrix);
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_helper_800700E0.s") // 200 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_800701A8.s")        // 100 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_8007020C.s")        // 860 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070568.s")        // 696 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070820.s")        // 656 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070AB0.s")        // 508 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_helper_80070CAC.s")        // 360 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_act_80070E14.s")               // 172 bytes

void sgtrect3_kill_80070EC0(Actor_sgtrect3 *actor_sgtrect3)
{
    byte_8009F5F8[0] = 0;
}

#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_helper_80070ECC.s") // 128 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_loader_80070F4C.s")        // 196 bytes
#pragma INCLUDE_ASM("asm/Thing/sgtrect3_init_80071010.s")          // 268 bytes
