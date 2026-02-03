#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "menu/menuman.h"

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF3DC.s")

void s04c_revolver_800CF418(void)
{
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF420.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF4A0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF518.s")
void s04c_revolver_800CF584(void *s0)
{
    // Check if the short at offset 0xB0 is NOT 9
    if (*(short *)((char *)s0 + 0xb0) != 9)
    {
        // Added (OBJECT *) cast here
        GM_ConfigObjectOverride((OBJECT *)((char *)s0 + 0xa0), 9, 0, 4, -1);
    }
    // Set short at offset 0x19C to 0
    *(short *)((char *)s0 + 0x19c) = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF5D0.s")
void s04c_revolver_800CF650(void *s0)
{
    // Check if the short at offset 0xB0 is NOT 13
    if (*(short *)((char *)s0 + 0xb0) != 13)
    {
        // Added (OBJECT *) cast here
        GM_ConfigObjectOverride((OBJECT *)((char *)s0 + 0xa0), 13, 0, 4, -1);
    }
    *(short *)((char *)s0 + 0x19c) = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF69C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF71C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF748.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF7AC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF7FC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF868.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF8D8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFAF0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFBE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFC3C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFC6C.s")

void s04c_revolver_800CFD08(SVECTOR *arg0, int arg1)
{
    switch (arg1)
    {
    case 0:
        arg0->vx = -15000 - arg0->vx;
        break;

    case 1:
        arg0->vx = 5000 - arg0->vx;
        break;

    case 2:
        arg0->vz = 2000 - arg0->vz;
        break;

    case 3:
        arg0->vz = 22000 - arg0->vz;
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFD84.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFE44.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CFED4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D00B4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D02C8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D03C0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D03EC.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0418.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0444.s")

void s04c_revolver_800D04B8(int *arg0, int arg1)
{
    arg0[0] = arg1;
    arg0[1] = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D04C4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D07F4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0A94.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D0DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1120.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D11C8.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1318.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1364.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D149C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D158C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D15D4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D168C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1760.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D184C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1BE4.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1C60.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D1CE0.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800D2028.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revbullt_800D20BC.s")
