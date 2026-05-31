#include "common.h"
#include "game/game.h"

int s08b_dword_800C3614 = 0x00000000;
int s08b_dword_800C3618 = 0x00000000;
int s08b_dword_800C361C = 0x00000000;

const char s08b_aNjaball_800E40B8[] = "nja_ball";
const char s08b_aBallhlf_800E40C4[] = "ballhlf";

void s08b_p_sphere_800D8F20(void *unused, MATRIX **m, int scale)
{
    VECTOR v;

    (void)unused;
    v.vx = scale;
    v.vy = scale;
    v.vz = scale;
    ScaleMatrix(*m, &v);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_p_sphere_800D8F50.s")
void s08b_p_sphere_800D9574(void *work)
{
    int off;
    int i = 0;

    for (off = 0x20; i < 2; off += 0xE4)
    {
        GM_FreeObject((OBJECT *)((char *)work + off));
        i++;
    }
    s08b_dword_800C361C = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_p_sphere_800D95CC.s")

const char s08b_aPspherec_800E40CC[] = "p_sphere.c";
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_p_sphere_800D9834.s")
