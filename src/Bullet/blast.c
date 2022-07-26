
#pragma INCLUDE_ASM("asm/Bullet/blast_act_8006DD18.s")

#include "libdg.h"

extern void sub_8007913C(void);

void blast_kill_8006DD90(int param_1)
{
    int iVar1;

    if (*(int *)(param_1 + 0x38) < 2)
    {
        sub_8007913C();
    }
    iVar1 = *(int *)(param_1 + 0x2c);
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0(iVar1);
        DG_FreePrim_8001BC04(iVar1);
    }
}

#pragma INCLUDE_ASM("asm/Bullet/blast_8006DDEC.s")
#pragma INCLUDE_ASM("asm/Bullet/blast_8006DF8C.s")
#pragma INCLUDE_ASM("asm/Bullet/NewBlast_8006DFDC.s")
#pragma INCLUDE_ASM("asm/Bullet/NewBlast2_8006E0F0.s")
#pragma INCLUDE_ASM("asm/AN_Blast_Single_8006E224.s")
#pragma INCLUDE_ASM("asm/sub_8006E2A8.s")
#pragma INCLUDE_ASM("asm/AN_Blast_Minimini_8006E32C.s")
