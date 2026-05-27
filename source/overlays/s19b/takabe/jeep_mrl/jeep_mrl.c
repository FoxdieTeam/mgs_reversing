#include "common.h"

extern int s19b_dword_800DE64C;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2CE8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D32B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D368C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D36A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D37D0.s")
int s19b_jeep_mrl_800D2CE8(void *work);
int s19b_jeep_mrl_800D2D3C(void *work);
int rand(void);
int GV_NearSpeed(int current_speed, int target_speed, int step_modifier);

void rpk_jeep_speed_logic(void *work)
{
    int timer;
    int rand_val;
    int target_speed;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);

    timer = *(int *)((char *)work + 0x3CC);
    if ((timer & 0x3F) == 0) {
        rand_val = rand();

        target_speed = (((rand_val * 16) - rand_val) * 4) >> 15;
        *(short *)((char *)work + 0x3CA) = target_speed - 600;
    }

    *(short *)((char *)work + 0x3C8) = GV_NearSpeed(
        *(short *)((char *)work + 0x3C8),
        *(short *)((char *)work + 0x3CA),
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
void GM_FreeTarget(void *target);
void GM_FreeControl(void *control);
void GM_FreeObject(void *object);

void s19b_jeep_mrl_800D4098(void *work)
{


    GM_FreeTarget(*(void **)((char *)work + 0x7E8));



    GM_FreeControl((char *)work + 0x28);



    GM_FreeObject((char *)work + 0xA4);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D40D4.s")
