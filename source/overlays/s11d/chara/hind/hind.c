#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/control.h"

typedef struct _HindWork
{
    GV_ACT  actor;       // 0x00
    CONTROL control;     // 0x20
    DG_OBJS *field_9C;
    char    pad_a0[0x180 - 0x9C - sizeof(DG_OBJS *)];
    MATRIX  field_180;
    char    pad_1a0[0x924 - 0x180 - sizeof(MATRIX)];
    DG_PRIM *field_924;
    char    pad_928[0x978 - 0x924 - sizeof(DG_PRIM *)];
    short   f978;        // 0x978
    short   f97A;        // 0x97A
} HindWork;

int s11d_hind_800C976C(short *p, int target, int step)
{
    short val = *p;
    int   diff = target - val;

    if (diff < -step)
    {
        *p = val - step;
    }
    else if (diff > step)
    {
        *p = val + step;
    }
    else
    {
        *p = val + diff;
    }
    return *p == target;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C97B8.s")
void s11d_hind_800C97F0(HindWork *work)
{
    if (work->f978 > 0)
    {
        work->f978--;
        if (work->f978 == 0)
        {
            GM_SeSetMode(&work->control.mov, work->f97A, GM_SEMODE_BOMB);
        }
    }
}

void s11d_hind_800C9838(HindWork *work)
{
    SVECTOR svec;
    (void)svec;

    if ((GV_Time & 3) == 0)
    {
        GM_SeSetMode(&work->control.mov, 0xB6, GM_SEMODE_BOMB);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9870.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9908.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99A8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9B94.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9D60.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA424.s")
void s11d_hind_800CA49C(HindWork *work)
{
    if (work->control.mov.vz < -14000 &&
        work->control.mov.vx >= -3999 &&
        work->control.mov.vx < 3000)
    {
        work->field_9C->flag |= DG_FLAG_INVISIBLE;
    }
    else
    {
        work->field_9C->flag &= ~DG_FLAG_INVISIBLE;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA504.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA6D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CABA8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAD9C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAE6C.s")
extern void s11d_hind_800CAE6C(HindWork *work);

void s11d_hind_800CAF20(HindWork *work)
{
    CONTROL *ctrl = &work->control;
    OBJECT  *body = (OBJECT *)&work->field_9C;

    GM_ActControl(ctrl);
    work->control.mov.vy += work->control.step.vy;
    GM_ActObject2(body);
    DG_GetLightMatrix(&ctrl->mov, &work->field_180);
    s11d_hind_800C97B8(work);
    s11d_hind_800C9838(work);
    s11d_hind_800CAE6C(work);
}
void s11d_hind_800CAF9C(HindWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->field_9C);
    prim = work->field_924;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAFEC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB054.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB178.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB310.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB3A0.s")
extern int s11d_hind_800CB3A0(HindWork *work, int arg1, int arg2);
extern const char s11d_dword_800D1E48[];

HindWork *s11d_hind_800CB708(int arg1, int arg2)
{
    HindWork *work;

    work = GV_NewActor(5, sizeof(HindWork));
    if (work == NULL)
    {
        return NULL;
    }
    GV_SetNamedActor(work, s11d_hind_800CAF20, s11d_hind_800CAF9C, s11d_dword_800D1E48);
    if (s11d_hind_800CB3A0(work, arg1, arg2) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }
    return work;
}
