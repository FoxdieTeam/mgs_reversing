#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "menu/menuman.h"

typedef struct RevolverWork
{
    char            actor_pad[0x20];
    char            control_pad1[8]; 
    short           control_vx;     
    short           control_vy;     
    short           control_vz;      
    short           control_rot_y;   
    char            control_pad2[24];
    void           *m_info;        
    short           control_status;  
    char            control_pad3[82];
    char            body[16];       
    short           field_B0;        
    short           field_B2;        
    char            ptr_pad[0];      
    void           *field_B4;       
    char            pad2[0xE4];      
    short           field_19C;       
    short           field_19E;
    char            pad3[0x14];      
    short           field_1B4;       
    short           field_1B6;
    char            pad4[0x6C8];    
    int             field_880;       
    int             field_884;
    int             field_888;       
} RevolverWork;


void s04c_revolver_800CF3DC(int sound_id) {
    register int s0_sound_id = sound_id;

    if (GM_StreamStatus() != 2) {
        GM_SeSet2(0, 0x3f, s0_sound_id);
    }
}

void s04c_revolver_800CF418(void)
{
}

void s04c_revolver_800CF420(RevolverWork *work)
{

    if (work->field_B0 != 14)
    {

        work->field_888 = 1;

        {

            void *ctrl = work->field_B4;
            unsigned char *m_info_ptr = *(unsigned char **)((char *)ctrl + 0x28);
            

            *(unsigned short *)(m_info_ptr + 0x26) += 2048;
            

            work->control_rot_y += 2048;
        }


        GM_ConfigObjectOverride(work->body, 14, 0, 4, -1);

        {
            void *ctrl = work->field_B4;
            *(unsigned short *)((char *)ctrl + 0x2C) = 3;
        }


        work->field_19C = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF4A0.s")


void s04c_revolver_800CF518(RevolverWork *work)
{
    work->field_888 = 0;

    GM_ConfigObjectOverride(&work->body, 3, 0, 4, 0);

    work->field_1B4 = 0;

    if (work->field_880 == 0)
    {
        __asm__ volatile("" : : : "$4", "memory"); 
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
}

void s04c_revolver_800CF584(RevolverWork *work)
{
    if (work->field_B0 != 9)
    {
        GM_ConfigObjectOverride(&work->body, 9, 0, 4, -1);
    }
    
    work->field_19C = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF5D0.s")

void s04c_revolver_800CF650(RevolverWork *work)
{

    if (work->field_B0 != 13)
    {

        GM_ConfigObjectOverride(work->body, 13, 0, 4, -1);
    }
    
   
    work->field_19C = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF69C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF71C.s")
#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_revolver_800CF748.s")

void s04c_revolver_800CF7AC(RevolverWork *work) 
{
    work->field_880 = 0;

    GM_ConfigObjectAction(&work->body, 0, 0, 4);

    if (work->field_888 != 0) 
    {
        *(int *)((char *)work + 0x190) = -1;
        *(int *)((char *)work + 0x1A8) = 0;
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
