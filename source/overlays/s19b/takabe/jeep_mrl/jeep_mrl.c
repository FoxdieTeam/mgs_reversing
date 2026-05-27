#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

extern int s19b_dword_800DE64C;

typedef struct JeepWork
{
    char        pad_0x00[0x3C8];   
    short       current_speed;     
    short       target_speed;      
    int         timer;             
    
    char        pad_before_target[0x418];
    TARGET     *target;            
} JeepWork;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2CE8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D32B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D368C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D36A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D37D0.s")

int GV_NearSpeed(int current_speed, int target_speed, int step_modifier);

void rpk_jeep_speed_logic(JeepWork *work)
{
    int rand_val;
    int target_speed;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);

    if ((work->timer & 0x3F) == 0) {
        rand_val = rand();

        target_speed = (((rand_val * 16) - rand_val) * 4) >> 15;
        work->target_speed = target_speed - 600;
    }

    work->current_speed = GV_NearSpeed(
        work->current_speed,
        work->target_speed,
        30
    );
}


int s19b_jeep_mrl_800D399C(void)
{
    return *(int *)((char *)s19b_dword_800DE64C + 0x3D0);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D39B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D39F0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3A54.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3CA8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3D30.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3E98.s")


void s19b_jeep_mrl_800D4098(JeepWork *work)
{
    GM_FreeTarget(work->target);
    

    GM_FreeControl((char *)work + 0x28);
    GM_FreeObject((char *)work + 0xA4);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D40D4.s")
