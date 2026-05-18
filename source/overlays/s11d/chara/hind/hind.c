#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/control.h"

typedef struct _HindWork
{
    GV_ACT  actor;       // 0x00
    CONTROL control;     // 0x20
    DG_OBJS *field_9C;
    char    pad_a0[0x180 - 0x9C - sizeof(DG_OBJS *)];
    MATRIX  field_180;
    char    pad_1a0[0x1C4 - 0x180 - sizeof(MATRIX)];
    int     field_1C4;
    unsigned char field_1C8;
    char    pad_1c9[0x1CC - 0x1C8 - sizeof(unsigned char)];
    unsigned short field_1CC;
    unsigned short field_1CE;
    char    pad_1d0[0x1E8 - 0x1CC - sizeof(unsigned short) * 2];
    short   field_1E8;
    short   field_1EA;
    short   field_1EC;
    char    pad_1ee[0x1F0 - 0x1EC - sizeof(short)];
    short   field_1F0;
    char    pad_1f2[0x202 - 0x1F0 - sizeof(short)];
    unsigned short field_202[8];
    char    pad_212[0x910 - 0x212];
    unsigned short *field_910;
    unsigned short  field_914;
    unsigned short field_916;
    int     field_918;
    char    pad_91c[0x924 - 0x918 - sizeof(int)];
    DG_PRIM *field_924;
    char    pad_928[0x93C - 0x924 - sizeof(DG_PRIM *)];
    int     field_93C[7];
    int     field_958;
    char    pad_95c[0x978 - 0x958 - sizeof(int)];
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
extern void s11d_hind_800C97B8(HindWork *work);

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
void s11d_hind_800C9870(HindWork *work)
{
    int v1 = (work->field_910[3] & 0x300) >> 8;

    if (v1 == 3)
    {
        GV_DestroyActor(work);
        return;
    }

    if (v1 == 1)
    {
        if (*(int *)&work->field_1C8 & 2)
        {
            work->field_1CC = 1;
            work->field_1CE = ((unsigned char *)work->field_910)[6] >> 5;
            return;
        }
    }
    else if (v1 != 2)
    {
        return;
    }

    work->field_1CC = 0;
    work->field_1CE = 0xFFFF;
    work->field_1C4 = 0;
}
void s11d_hind_800C9908(HindWork *work, int arg1)
{
    unsigned short *event;
    int masked;
    int shifted;

    arg1--;
    work->field_914 = arg1;
    event = (unsigned short *)((char *)work + (arg1 * 256 + 0x210));
    work->field_916 = 1;
    work->field_910 = event;

    masked = event[3] & 0x1F;
    shifted = masked << 5;
    if (shifted != 0)
    {
        work->field_1F0 = shifted;
    }

    if (*(int *)&work->field_1C8 & 0x10)
    {
        *(int *)&work->field_1C8 |= 0x20;
        work->field_958 = 0;
        work->field_1EA = 0;
        work->field_1E8 = 0;
        work->field_1EC = work->control.mov.vy;
    }

    *(int *)&work->field_1C8 &= ~0x80;
    if ((((unsigned char *)work->field_910)[6] >> 5) == 4)
    {
        *(int *)&work->field_1C8 |= 0x80;
    }
}
extern void s11d_hind_800C9908(HindWork *work, int arg1);

void s11d_hind_800C99A8(HindWork *work)
{
    int a1 = (work->field_910[3] & 0x1C00) >> 10;
    if (a1 == 0)
    {
        a1 = work->field_914 + 1;
    }
    s11d_hind_800C9908(work, a1);
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99F4.s")
extern void s11d_hind_800C99F4(HindWork *work);
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9B94.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9D60.s")
extern SVECTOR GM_PlayerPosition;

void s11d_hind_800CA424(HindWork *work)
{
    SVECTOR svec_b;
    SVECTOR svec_a;

    if (work->field_1C8 >> 7)
    {
        svec_a = GM_PlayerPosition;
        svec_a.vx = 0;
        GV_SubVec3(&svec_a, &work->control.mov, &svec_b);
        work->control.turn.vy = GV_VecDir2(&svec_b);
    }
}
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
void s11d_hind_800CAD9C(HindWork *work)
{
    int masked;
    int shifted;

    s11d_hind_800C99F4(work);
    if (work->field_918 == 0)
    {
        return;
    }

    s11d_hind_800C9870(work);

    if (work->field_916 == work->field_202[work->field_914])
    {
        s11d_hind_800C99A8(work);
        return;
    }

    work->control.interp = 0xF;
    work->field_910 += 4;
    work->field_916++;

    masked = work->field_910[3] & 0x1F;
    shifted = masked << 5;
    if (shifted != 0)
    {
        work->field_1F0 = shifted;
    }

    *(int *)&work->field_1C8 &= ~0x80;
    if ((((unsigned char *)work->field_910)[6] >> 5) == 4)
    {
        *(int *)&work->field_1C8 |= 0x80;
    }
}
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
void s11d_hind_800CB310(HindWork *work)
{
    int *p;
    int  i;
    unsigned char *param;

    if (!GCL_GetOption('h'))
    {
        return;
    }

    i = 0;
    p = work->field_93C;
    while ((param = GCL_GetParamResult()))
    {
        if (i == 7)
        {
            break;
        }
        *p = GCL_StrToInt(param);
        p++;
        i++;
    }

    *(int *)&work->field_1C8 |= 0x10;
}
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
