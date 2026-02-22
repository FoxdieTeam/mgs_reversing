#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "menu/menuman.h"

void s04c_revolver_800CF3DC(int sound_id) {
    /* s0 is used to preserve the argument across the first function call */
    register int s0_sound_id = sound_id;

    /* 0xc: Call to check if the stream is busy */
    if (GM_StreamStatus() != 2) {
        GM_SeSet2(0, 0x3f, s0_sound_id);
    }
}

void s04c_revolver_800CF418(void)
{
}

void s04c_revolver_800CF420(void *work)
{
    // Target 10: lh v1, 0xb0(s0)
    // Accessing the 'is_end' flag at offset 0xb0
    if (*(short *)((char *)work + 0xb0) != 14)
    {
        // Target 28: sw v0, 0x888(s0)
        // Setting field_888 to 1
        *(int *)((char *)work + 0x888) = 1;

        {
            // Target 20: lw v1, 0xb4(s0) 
            // Accessing m_ctrl which is at offset 0xb4
            unsigned char *m_ctrl = *(unsigned char **)((char *)work + 0xb4);
            
            // Target 2c: lw v1, 0x28(v1)
            unsigned char *m_info = *(unsigned char **)(m_ctrl + 0x28);
            
            // Target 34/40: Update rot.y at m_info + 0x26
            *(unsigned short *)(m_info + 0x26) += 2048;
        }

        // Target 44/50: Update rot.vy at offset 0x2e
        *(unsigned short *)((char *)work + 0x2e) += 2048;

        // Target 24/58: GM_ConfigObjectOverride(&body, 14, 0, 4, -1)
        // 'body' starts at offset 0xa0
        GM_ConfigObjectOverride((void *)((char *)work + 0xa0), 14, 0, 4, -1);

        {
            // Target 60: lw v1, 0xb4(s0) (Reloading m_ctrl)
            unsigned char *m_ctrl = *(unsigned char **)((char *)work + 0xb4);
            
            // Target 68: sh v0, 0x2c(v1)
            *(unsigned short *)(m_ctrl + 0x2c) = 3;
        }

        // Target 6c: sh zero, 0x19c(s0)
        // Note: Your typedef called this field_9B4 but used offset 0x19c. 
        // We use the 0x19c offset to match the assembly target.
        *(short *)((char *)work + 0x19c) = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF4A0.s")
void s04c_revolver_800CF518(void *s0)
{
    void *s1;
    int check;

    s1 = (char *)s0 + 0xa0;
    *(int *)((char *)s0 + 0x888) = 0;

    GM_ConfigObjectOverride(s1, 3, 0, 4, 0);

    check = *(int *)((char *)s0 + 0x880);
    
    *(short *)((char *)s0 + 0x1b4) = 0;

    if (check == 0)
    {
        // Keep your clobber here to protect the function arguments
        __asm__ volatile("" : : : "$4", "memory"); 

        GM_ConfigObjectAction(s1, 0, 0, 4);
    }
}
void s04c_revolver_800CF584(void *s0)
{
  
    if (*(short *)((char *)s0 + 0xb0) != 9)
    {
        
        GM_ConfigObjectOverride((OBJECT *)((char *)s0 + 0xa0), 9, 0, 4, -1);
    }
    
    *(short *)((char *)s0 + 0x19c) = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF5D0.s")
void s04c_revolver_800CF650(void *s0)
{
    
    if (*(short *)((char *)s0 + 0xb0) != 13)
    {
        
        GM_ConfigObjectOverride((OBJECT *)((char *)s0 + 0xa0), 13, 0, 4, -1);
    }
    *(short *)((char *)s0 + 0x19c) = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF69C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF71C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF748.s")
void s04c_revolver_800CF7AC(void *work) {
    register char *s0 = (char *)work;

    /* Offset 0x880 */
    *(int *)(s0 + 0x880) = 0;

    /* * We cast to (OBJECT *) to match the declaration in game/game.h.
     * This stops the 'incompatible pointer type' build error.
     */
    GM_ConfigObjectAction((OBJECT *)(s0 + 0xA0), 0, 0, 4);

    /* Offset 0x888 */
    if (*(int *)(s0 + 0x888) != 0) {
        *(int *)(s0 + 0x190) = -1;
        *(int *)(s0 + 0x1A8) = 0;
    }
}
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
