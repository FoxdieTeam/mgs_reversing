#include "common.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT actor;       /* 0x000 */
    OBJECT objs[2];     /* 0x020, 0x104 */
    char   pad_1E8[0x2E4 - 0x1E8];
} Work;

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
void s08b_p_sphere_800D9574(Work *work)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        GM_FreeObject(&work->objs[i]);
    }
    s08b_dword_800C361C = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_p_sphere_800D95CC.s")

const char s08b_aPspherec_800E40CC[] = "p_sphere.c";

extern void s08b_p_sphere_800D8F50(Work *work);
extern int  s08b_p_sphere_800D95CC(Work *work, int arg0, int arg1);

void *s08b_p_sphere_800D9834(int arg0, int arg1)
{
    Work *work;

    if (s08b_dword_800C361C == 1)
    {
        return NULL;
    }

    work = GV_NewActor(4, sizeof(Work));
    if (work != NULL)
    {
        s08b_dword_800C361C = 1;
        GV_SetNamedActor(work, s08b_p_sphere_800D8F50, s08b_p_sphere_800D9574,
                         s08b_aPspherec_800E40CC);

        if (s08b_p_sphere_800D95CC(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
