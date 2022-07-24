#include "linker.h"
#include "gcl.h"
#include "kernel.h"
#include "game.h"
#include "libdg.h"

extern void GM_FreeControl_800260CC(int param_1);
extern void GM_FreeObject_80034BF8(OBJECT *obj);

#pragma INCLUDE_ASM("asm/Game/item_act_try_add_ammo2_8003330C.s")
#pragma INCLUDE_ASM("asm/Game/item_act_try_add_ammo_80033384.s")
#pragma INCLUDE_ASM("asm/Game/item_act_helper_800333F8.s")
#pragma INCLUDE_ASM("asm/Game/item_all_items_and_weapons_unknown2_80033500.s")
#pragma INCLUDE_ASM("asm/Game/item_all_items_and_weapons_unknown_80033560.s")
#pragma INCLUDE_ASM("asm/Game/item_act_helper_800335D0.s")

void item_init_prim_buffer_800336A4(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1
  
    setPolyFT4(prims);
    setSemiTrans(prims, 1);    

    t_u0 = tex->field_8_offx;
    t_u1 = t_u0 + tex->field_A_width;

    t_v0 = tex->field_9_offy;
    t_v2 = t_v0 + tex->field_B_height;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->field_4_tPage;
    prims->clut = tex->field_6_clut;
}

#pragma INCLUDE_ASM("asm/Game/item_act_helper_80033704.s")
#pragma INCLUDE_ASM("asm/Game/item_act_80033784.s")

void item_kill_80033F88(int param_1)
{
    char *pScript;
    int iVar2;

    GM_FreeControl_800260CC(param_1 + 0x20);
    GM_FreeObject_80034BF8((OBJECT *)(param_1 + 0x9c));
    iVar2 = *(int *)(param_1 + 0x15c);
    if (iVar2 != 0)
    {
        DG_DequeuePrim_800182E0(iVar2);
        DG_FreePrim_8001BC04(iVar2);
    }
    if ((*(char *)(param_1 + 0x112) == '\x02') &&
        (pScript = *(char **)(param_1 + 0x120),  pScript != NULL))
    {
        if ((int)pScript < 0)
        {
            GCL_ExecBlock_80020118(pScript, NULL);
        }
        else 
        {
            GCL_ExecProc_8001FF2C((unsigned int)pScript, NULL);
        }
    }
    return;
}

#pragma INCLUDE_ASM("asm/Game/item_init_helper_helper_80034020.s")
#pragma INCLUDE_ASM("asm/Game/item_init_helper_800340D0.s")
#pragma INCLUDE_ASM("asm/Game/item_init_800344F8.s")
#pragma INCLUDE_ASM("asm/Game/item_init_helper_800345C0.s")
#pragma INCLUDE_ASM("asm/Game/item_init_80034758.s")
