#include "common.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;                                    /* 0x000 */
    CONTROL *root_ctrl;                                /* 0x020 */
    MATRIX  *root_mat;                                 /* 0x024 */
    CONTROL  control;                                  /* 0x028 */
    OBJECT   body;                                     /* 0x0A4 */
    char     pad_2B0[0x2B0 - 0xA4 - sizeof(OBJECT)];
    TARGET   field_2B0;                                /* 0x2B0 */
    char     pad_3A0[0x3A0 - 0x2B0 - sizeof(TARGET)];
    short    field_3A0;                                /* 0x3A0 */
    char     pad_3A4[0x3A4 - 0x3A0 - sizeof(short)];
    short    field_3A4;                                /* 0x3A4 */
    char     pad_3B8[0x3B8 - 0x3A4 - sizeof(short)];
    SVECTOR  field_3B8;                                /* 0x3B8 */
    char     pad_3C8[0x3C8 - 0x3B8 - sizeof(SVECTOR)];
    short    field_3C8;                                /* 0x3C8 */
    short    field_3CA;                                /* 0x3CA */
    int      field_3CC;                                /* 0x3CC */
    int      field_3D0;                                /* 0x3D0 */
    int      field_3D4;                                /* 0x3D4 */
    char     pad_3E0[0x3E0 - 0x3D4 - sizeof(int)];
    int      field_3E0;                                /* 0x3E0 */
    char     pad_7E8[0x7E8 - 0x3E0 - sizeof(int)];
    TARGET  *target;                                   /* 0x7E8 */
    void    *field_7EC;                                /* 0x7EC: current state handler */
    char     pad_7F4[0x7F4 - 0x7EC - sizeof(void *)];
    int      field_7F4;                                /* 0x7F4: frame counter */
    char     pad_7FC[0x7FC - 0x7F4 - sizeof(int)];
    int      field_7FC;                                /* 0x7FC: action id */
    int      field_800;                                /* 0x800: flags */
    char     pad_818[0x818 - 0x800 - sizeof(int)];
    short    field_818;                                /* 0x818 */
    char     pad_81C[0x81C - 0x818 - sizeof(short)];
    short    field_81C;                                /* 0x81C */
} Work;

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2a[0x4C - 0x8];
    int      field_4C;
    int      field_50;
    char     pad2b[0x60 - 0x50 - sizeof(int)];
    OBJECT  *snake_body;
    char     pad3[0x78 - 0x60 - sizeof(OBJECT *)];
    int      field_78;
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

extern Work *s19b_dword_800DE64C;

void s19b_jeep_mrl_800D2CE8(Work *work)
{
    if (work->field_3E0 == 0)
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 5);
    }
    else
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 10);
    }
}
extern void s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);

void s19b_jeep_mrl_800D2D3C(Work *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->field_3D0;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->field_3B8);
    DG_RotVector(&rot, &rot, 1);
    work->field_3A0 = rot.vx;
    work->field_3A4 = rot.vz;
    s19b_jeep_gls_800CEC24(ctl->mov.vz - 0x640, &vec);
    GV_SubVec3(&vec, &ctl->mov, &vec);
    vec.vx += work->field_3C8;
    vec.vx += rsin(work->field_3CC << 5) * 50 >> 12;
    work->field_3B8.vy = GV_VecDir2(&vec);
    work->field_3CC++;
    work->field_3D4 = GV_NearSpeed(work->field_3D4, 0x190, 0xa);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D32B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D368C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D36A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D37D0.s")
extern void s19b_jeep_mrl_800D2D3C(Work *work);

void s19b_jeep_mrl_800D3928(Work *work)
{
    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = (rand() * 60 >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);
}
int s19b_jeep_mrl_800D399C(void)
{
    return s19b_dword_800DE64C->field_3D0;
}
int s19b_jeep_mrl_800D39B4(SVECTOR *dst)
{
    *dst = s19b_dword_800DE64C->control.mov;
    return s19b_dword_800DE64C->field_3C8;
}
extern CONTROL *GM_WhereList[96];
extern int      GM_N_WhereList;

int s19b_jeep_mrl_800D39F0(void)
{
    CONTROL **where = GM_WhereList;
    MAP      *map   = (*where)->map;
    int       count = 0;
    int       n;

    for (n = GM_N_WhereList; n > 0; n--)
    {
        CONTROL *control = *where;
        if ((control->radar_atr & 1) && control->map == map)
        {
            count++;
        }
        where++;
    }
    return count;
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3A54.s")
extern SVECTOR s19b_dword_800C39D0[];
extern int s19b_dword_800C399C;
extern int s19b_dword_800C3994;
extern void *NewPadVibration(unsigned char *, int);

void s19b_jeep_mrl_800D3CA8(Work *work, int arg1)
{
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(&s19b_dword_800C39D0[arg1], &work->field_2B0.center, 1);
    work->field_2B0.vital = 8;
    if (GM_PowerTarget(&work->field_2B0) == 0)
    {
        return;
    }
    NewPadVibration((unsigned char *)&s19b_dword_800C399C, 1);
    NewPadVibration((unsigned char *)&s19b_dword_800C3994, 0);
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3D30.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3E98.s")
void s19b_jeep_mrl_800D4098(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}
extern void s19b_jeep_mrl_800D3D30(Work *work);
extern int  s19b_jeep_mrl_800D3E98(Work *work, int name, int arg2);
extern const char s19b_dword_800DDDF8[];
extern const char s19b_aMeryl_800DDDCC[];

void *s19b_jeep_mrl_800D40D4(int arg0, int arg1, int arg2)
{
    Work *work = GV_NewActor(GV_ACTOR_AFTER, 0x820);

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_mrl_800D3D30, s19b_jeep_mrl_800D4098,
                         s19b_dword_800DDDF8);
        work->root_ctrl = (CONTROL *)arg0;
        work->root_mat = (MATRIX *)arg1;
        if (s19b_jeep_mrl_800D3E98(work, GV_StrCode(s19b_aMeryl_800DDDCC), arg2) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}

extern void s19b_jeep_mrl_800D424C(Work *work, int arg1);
extern void s19b_jeep_mrl_800D4290(Work *work, int arg1);
extern void s19b_jeep_mrl_800D43AC(Work *work, int arg1);
extern void s19b_jeep_mrl_800D4414(Work *work, int arg1);
extern void s19b_jeep_mrl_800D4574(Work *work, int arg1);
extern void s19b_jeep_mrl_800D46D4(Work *work, int arg1);

int s19b_jeep_mrl_800D4188(Work *work)
{
    int flags = work->field_800;

    if (flags & 2)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D46D4;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 1)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D424C;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x20)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D4414;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x200)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D4574;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 0x1000)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D43AC;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if ((flags & 0x10000) == 0)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D4290;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_jeep_mrl_800D424C(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    s19b_jeep_mrl_800D4188(work);
}
void s19b_jeep_mrl_800D4290(Work *work, int arg1)
{
    SVECTOR sp10;
    int     diff;

    if (arg1 == 0)
    {
        work->field_7FC = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    if ((Takabe_JeepSystem.field_4C & 1) && GV_RandU(0x100) < 0x14)
    {
        GM_SeSet(&work->control.mov, work->field_81C);
    }
    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &sp10);

    diff = (GM_PlayerControl->rot.vy - work->control.rot.vy) - work->root_ctrl->rot.vy;
    diff &= 0xFFF;
    if (diff & 0x800)
    {
        diff -= 0x1000;
    }
    if (diff < -0x400)
    {
        diff = -0x400;
    }
    if (diff > 0x400)
    {
        diff = 0x400;
    }
    /* scratch slot at 0x7E4 */
    *(int *)((char *)work + 0x7E4) = diff;

    if (work->field_800 & 0x10000)
    {
        *(int *)((char *)work + 0x7E4) = 0;
        if (s19b_jeep_mrl_800D4188(work) == 0)
        {
            work->field_7EC = (void *)s19b_jeep_mrl_800D424C;
            work->field_7F4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
void s19b_jeep_mrl_800D43AC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }
    if (work->field_800 & 0x10000)
    {
        work->field_7EC = (void *)s19b_jeep_mrl_800D424C;
        work->field_7F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
extern void s19b_jeep_mrl_800D4488(Work *work, int arg1);
extern void s19b_jeep_mrl_800D4500(Work *work, int arg1);
extern void s19b_jeep_mrl_800D45E8(Work *work, int arg1);
extern void s19b_jeep_mrl_800D4660(Work *work, int arg1);

void s19b_jeep_mrl_800D4414(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D4488;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4488(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 8;
        GM_ConfigObjectAction(&work->body, 8, 0, 0);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->field_800 & 0x20000) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D4500;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4500(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 9;
        GM_ConfigObjectAction(&work->body, 9, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D424C;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4574(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 1;
        GM_ConfigObjectAction(&work->body, 1, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D45E8;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D45E8(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 2;
        GM_ConfigObjectAction(&work->body, 2, 0, 0);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->field_800 & 0x20000) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D4660;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_jeep_mrl_800D4660(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 3;
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }
    if (s19b_jeep_mrl_800D4188(work) != 0) return;
    if (work->body.is_end == 0) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D424C;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s19b_jeep_mrl_800D46D4(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_7FC = 0xD;
        GM_ConfigObjectAction(&work->body, 0xD, 0, 4);
        GM_SeSet(&work->control.mov, work->field_818);
    }
    if (work->body.is_end == 0) return;
    work->field_7EC = (void *)s19b_jeep_mrl_800D424C;
    work->field_7F4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s19b_jeep_mrl_800D4744(Work *work)
{
    void (*fn)(Work *, int);
    int   old = work->field_7F4;

    work->field_7F4 = old + 1;
    fn = (void (*)(Work *, int))work->field_7EC;
    if (fn == 0)
    {
        fn = s19b_jeep_mrl_800D424C;
        work->field_7EC = (void *)fn;
        work->field_7FC = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }
    fn(work, old);
}

void s19b_jeep_mrl_800D47B8(Work *work)
{
    work->field_800 = Takabe_JeepSystem.field_50;
    Takabe_JeepSystem.field_50 &= 0xFFFF0000;
    s19b_jeep_mrl_800D4744(work);
}
