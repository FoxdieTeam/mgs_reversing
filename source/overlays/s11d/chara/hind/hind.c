#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/control.h"

typedef struct _Work
{
    GV_ACT   actor; 
    CONTROL  control;
    OBJECT   body;
    char     pad_object[0x180 - 0x9C - sizeof(OBJECT)];
    MATRIX   field_180;
    char     pad_1a0[0x1C4 - 0x180 - sizeof(MATRIX)];
    int      field_1C4;
    u_char   field_1C8;
    char     pad_1c9[0x1CC - 0x1C8 - sizeof(u_char)];
    u_short  field_1CC;
    u_short  field_1CE;
    char     pad_1d0[0x1E8 - 0x1CC - sizeof(u_short) * 2];
    short    field_1E8;
    short    field_1EA;
    short    field_1EC;
    char     pad_1ee[0x1F0 - 0x1EC - sizeof(short)];
    short    field_1F0;
    char     pad_1f2[0x1F4 - 0x1F0 - sizeof(short)];
    short    field_1F4;
    short    field_1F6;
    char     pad_1f8[0x202 - 0x1F8];
    u_short  field_202[8];
    char     pad_212[0x910 - 0x212];
    u_short *field_910;
    u_short  field_914;
    u_short  field_916;
    int      field_918;
    char     pad_91c[0x924 - 0x918 - sizeof(int)];
    DG_PRIM *field_924;
    char     pad_928[0x93C - 0x924 - sizeof(DG_PRIM *)];
    int      field_93C[7];
    int      field_958;
    char     pad_95c[0x978 - 0x958 - sizeof(int)];
    short    f978;
    short    f97A;
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

extern const char s11d_dword_800D1E48[]; // "hind.c"

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

void s11d_hind_800C97B8(Work *work)
{
    OBJECT *body;
    int     rot;

    body = &work->body;

    rot = body->rots[1].vy;
    rot = (body->rots[1].vy + work->field_1F4) & 0xFFF;
    body->rots[1].vy = rot;

    rot = body->rots[2].vx;
    rot = (rot + work->field_1F6) & 0xFFF;
    body->rots[2].vx = rot;
}

void s11d_hind_800C97F0(Work *work)
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

void s11d_hind_800C9838(Work *work)
{
    SVECTOR svec;
    (void)svec;

    if ((GV_Time & 3) == 0)
    {
        GM_SeSetMode(&work->control.mov, 182, GM_SEMODE_BOMB);
    }
}

void s11d_hind_800C9870(Work *work)
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
            work->field_1CE = ((u_char *)work->field_910)[6] >> 5;
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

void s11d_hind_800C9908(Work *work, int arg1)
{
    u_short *event;
    int masked;
    int shifted;

    arg1--;
    work->field_914 = arg1;
    event = (u_short *)((char *)work + (arg1 * 256 + 0x210));
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
    if ((((u_char *)work->field_910)[6] >> 5) == 4)
    {
        *(int *)&work->field_1C8 |= 0x80;
    }
}

void s11d_hind_800C99A8(Work *work)
{
    int a1 = (work->field_910[3] & 0x1C00) >> 10;
    if (a1 == 0)
    {
        a1 = work->field_914 + 1;
    }

    s11d_hind_800C9908(work, a1);
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99F4.s")
void s11d_hind_800C99F4(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9B94.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9D60.s")

void s11d_hind_800CA424(Work *work)
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

void s11d_hind_800CA49C(Work *work)
{
    if (work->control.mov.vz < -14000 && work->control.mov.vx >= -3999 && work->control.mov.vx < 3000)
    {
        DG_InvisibleObjs(work->body.objs);
    }
    else
    {
        DG_VisibleObjs(work->body.objs);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA504.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA6D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CABA8.s")

void s11d_hind_800CAD9C(Work *work)
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
    if ((((u_char *)work->field_910)[6] >> 5) == 4)
    {
        *(int *)&work->field_1C8 |= 0x80;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAE6C.s")
void s11d_hind_800CAE6C(Work *work);

void s11d_hind_800CAF20(Work *work)
{
    CONTROL *ctrl = &work->control;
    OBJECT  *body = &work->body;

    GM_ActControl(ctrl);
    work->control.mov.vy += work->control.step.vy;
    GM_ActObject2(body);
    DG_GetLightMatrix(&ctrl->mov, &work->field_180);
    s11d_hind_800C97B8(work);
    s11d_hind_800C9838(work);
    s11d_hind_800CAE6C(work);
}

void s11d_hind_800CAF9C(Work *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    prim = work->field_924;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int s11d_hind_800CAFEC(char *arg0, char *arg1, char *arg2)
{
    register int   count asm("a3");
    register char *src asm("a0");
    register char *src1 asm("v1");
    register char *dst0 asm("t0");
    register char *dst1 asm("a2");
    register int   value asm("v0");

    value = *(unsigned short *)arg0;
    __asm__ volatile("" : "+r"(value));
    count = value & 0xFFFF;
    count--;
    *(short *)arg1 = value;
    src = *(char **)(arg0 + 4);
    dst0 = arg2;

    if (count >= 0)
    {
        dst1 = arg2 + 6;
        src1 = src + 6;

        do
        {
            value = *(unsigned short *)(src + 0);
            src += 8;
            *(short *)(dst0 + 0) = value;
            value = *(unsigned short *)(src1 - 2);
            count--;
            *(short *)(dst1 - 4) = value;
            value = *(unsigned short *)(src1 - 4);
            dst0 += 8;
            *(short *)(dst1 - 2) = value;
            value = *(unsigned short *)(src1 + 0);
            src1 += 8;
            *(short *)(dst1 + 0) = value;
            dst1 += 8;
        } while (count >= 0);
    }

    return 0;
}

int s11d_hind_800CB054(char *work)
{
    register char *s5 asm("s5");
    register int   s4 asm("s4");
    register char *s3 asm("s3");
    register char *s2 asm("s2");
    register int   s1 asm("s1");
    register int   s0 asm("s0");
    register int   v0 asm("v0");
    register int   v1 asm("v1");
    register int   a0 asm("a0");
    char          *ptr;

    s5 = work;
    ptr = *(char **)(s5 + 0x4C);
    __asm__ volatile("" : : : "memory");
    ptr = *(char **)(ptr + 0x8);
    __asm__ volatile("nop");
    ptr = *(char **)ptr;
    s3 = s5 + 0x202;
    s2 = *(char **)(ptr + 0x18);
    s4 = *(short *)(ptr + 0xE);
    s0 = 0;
    *(short *)(s5 + 0x200) = s4;

    if (s4 > 0)
    {
        s1 = 0x210;
        do
        {
            if (s11d_hind_800CAFEC(s2, s3, s5 + s1) < 0)
            {
                return -1;
            }
            s1 += 0x100;
            s0++;
            s2 += 8;
            s3 += 2;
        } while (s0 < s4);
    }

    *(short *)(s5 + 0x1F0) = 0x20;
    if (GCL_GetOption(0x72) == 0)
    {
        return -1;
    }

    v0 = GCL_StrToInt(GCL_NextStr());
    s11d_hind_800C9908(s5, v0);

    __asm__ volatile(".set noreorder
"
                     "lw    $3, 0x910(%1)
"
                     "lh    %0, 0x22(%1)
"
                     "lwl   $7, 0x3($3)
"
                     "lwr   $7, 0x0($3)
"
                     "lwl   $8, 0x7($3)
"
                     "lwr   $8, 0x4($3)
"
                     "swl   $7, 0x23(%1)
"
                     "swr   $7, 0x20(%1)
"
                     "swl   $8, 0x27(%1)
"
                     "swr   $8, 0x24(%1)
"
                     ".set reorder
"
                     : "=r"(a0)
                     : "r"(s5)
                     : "$3", "$7", "$8", "memory");

    __asm__ volatile(".set noreorder
"
                     "lw    %1, 0x1C8(%3)
"
                     "addu  %0, $0, $0
"
                     "sh    %2, 0x22(%3)
"
                     "addiu %2, $0, -0x21
"
                     "sw    $0, 0x918(%3)
"
                     "and   %1, %1, %2
"
                     ".set reorder
"
                     : "=r"(v0), "=r"(v1), "+r"(a0)
                     : "r"(s5)
                     : "memory");
    *(int *)(s5 + 0x1C8) = v1;
    return v0;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB178.s")

void s11d_hind_800CB310(Work *work)
{
    int *p;
    int  i;
    u_char *param;

    if (!GCL_GetOption('h'))
    {
        return;
    }

    i = 0;
    p = work->field_93C;
    while ((param = GCL_NextStr()))
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
int s11d_hind_800CB3A0(Work *work, int name, int where);

void *NewHind(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, s11d_hind_800CAF20, s11d_hind_800CAF9C, s11d_dword_800D1E48);

    if (s11d_hind_800CB3A0(work, name, where) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    return work;
}
