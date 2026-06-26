#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;       /* 0x000 */
    CONTROL control;     /* 0x020 */
    OBJECT  body;        /* 0x09C */
    MATRIX  field_180;   /* 0x180 */
    char    pad_1A0[0x1C0 - 0x1A0];
    TARGET  target;      /* 0x1C0 */
    char    pad_208[0x228 - 0x208];
    SVECTOR *field_228;  /* 0x228 */
    SVECTOR field_22C;   /* 0x22C */
    char    pad_234[0x238 - 0x234];
    int     field_238;   /* 0x238 */
    int     field_23C;   /* 0x23C */
    int    *field_240;   /* 0x240 */
    int     field_244;   /* 0x244 */
    int     field_248;   /* 0x248 */
} Work;

typedef struct _Casing
{
    GV_ACT   actor;     /* 0x00 */
    int      field_20;  /* 0x20 */
    DG_PRIM *field_24;  /* 0x24 */
    char     pad_28[0x68 - 0x28];
    int      field_68;  /* 0x68 */
    int      field_6C;  /* 0x6C */
    int      field_70;  /* 0x70 */
    int      field_74;  /* 0x74 */
} Casing;

typedef struct _Smoke
{
    GV_ACT  actor;     /* 0x00 */
    int     field_20;  /* 0x20 */
    SVECTOR field_24;  /* 0x24 */
    SVECTOR field_2C;  /* 0x2C */
    int     field_34;  /* 0x34 */
    TARGET  target;    /* 0x38 */
} Smoke;

extern const char s05a_dword_800E34D4[]; /* = "m1e1shel.c" */

extern void *s05a_800DBF58(int arg0, SVECTOR *arg1, SVECTOR *arg2);
void s05a_800DBED0(Smoke *work);
void s05a_800DBF50(void *work);

void *s05a_800DBD14(SVECTOR *arg0, SVECTOR *arg1);
void *s05a_800DB684(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DAE58.s")
void s05a_800DB278(Work *work)
{
    SVECTOR vec;
    int s0;
    int s2 = 0;

    work->field_22C = work->control.mov;
    GM_ActControl(&work->control);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix2(&work->control.mov, &work->field_180);
    GM_MoveTarget(&work->target, &work->control.mov);
    work->field_244++;
    if (work->field_244 < 2)
        s05a_800DBF58(s2, &work->control.mov, &work->control.rot);

    if (work->field_228 == 0)
    {
        DG_SetPos2(&work->control.mov, &work->control.rot);
        vec.vx = 0;
        vec.vy = 0;
        vec.vz = work->field_23C;
        DG_RotVector(&vec, &work->control.step, 1);
    }
    else
    {
        int dist;
        vec.vx = work->field_228->vx - work->control.mov.vx;
        vec.vy = work->field_228->vy - work->control.mov.vy;
        vec.vz = work->field_228->vz - work->control.mov.vz;
        dist = SquareRoot0(vec.vx * vec.vx + vec.vy * vec.vy + vec.vz * vec.vz);
        if (dist == 0) dist = 1;
        work->control.step.vx = vec.vx * work->field_23C / dist;
        work->control.step.vy = vec.vy * work->field_23C / dist;
        work->control.step.vz = vec.vz * work->field_23C / dist;
        work->control.turn.vx = -ratan2(vec.vy, SquareRoot0(vec.vx * vec.vx + vec.vz * vec.vz));
        work->control.turn.vy = ratan2(vec.vx, vec.vz);
        work->control.turn.vz = 0;
    }

    s0 = work->control.n_touches;
    if (s0 > 0)
        s0 = GM_CheckControlTouches(&work->control, work->field_248);
    if (s0 > 0 || (s2 = GM_PowerTarget(&work->target)) != 0 || work->field_244 >= work->field_238 ||
        work->control.mov.vx < -0x6978 || work->control.mov.vx >= 0x6979 ||
        work->control.mov.vy < -0x6978 || work->control.mov.vy >= 0x6979 ||
        work->control.mov.vz < -0x6978 || work->control.mov.vz >= 0x6979)
    {
        if (s2 != 0) *work->field_240 = 1;
        else if (s0 > 0) *work->field_240 = 2;
        else *work->field_240 = 3;
        GM_SeSetPan(&work->control.mov, 0xB7, 0x3F);
        s05a_800DBD14(&work->control.mov, &work->control.rot);
        GV_DestroyActor(work);
    }
    else
    {
        s05a_800DB684(work);
    }
}

void s05a_800DB654(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DB684.s")

void s05a_800DBA94(Casing *work)
{
    GM_CurrentMap = work->field_20;
    work->field_68++;
    work->field_6C -= 25;
    if (work->field_6C < 0)
    {
        work->field_6C = 0;
    }
    work->field_70 -= 22;
    if (work->field_70 < 0)
    {
        work->field_70 = 0;
    }
    work->field_74 -= 19;
    if (work->field_74 < 0)
    {
        work->field_74 = 0;
    }
    setRGB0((POLY_FT4 *)work->field_24->packs[0], work->field_6C, work->field_70, work->field_74);
    setRGB0((POLY_FT4 *)work->field_24->packs[0] + 1, work->field_6C, work->field_70, work->field_74);
    setRGB0((POLY_FT4 *)work->field_24->packs[1], work->field_6C, work->field_70, work->field_74);
    setRGB0((POLY_FT4 *)work->field_24->packs[1] + 1, work->field_6C, work->field_70, work->field_74);
    if (work->field_68 >= 11)
    {
        GV_DestroyActor(work);
    }
}

void s05a_800DBC44(Casing *work)
{
    DG_PRIM *prim = work->field_24;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

typedef struct _CasingTex
{
    char    pad_00[4];
    u_short field_04; /* 0x04 -> tpage */
    u_short field_06; /* 0x06 -> clut */
    u_char  field_08; /* 0x08 -> u */
    u_char  field_09; /* 0x09 -> v */
    u_char  field_0A; /* 0x0A -> w */
    u_char  field_0B; /* 0x0B -> h */
} CasingTex;

void s05a_800DBC80(POLY_FT4 *poly, CasingTex *src)
{
    int i;

    for (i = 0; i < 2; i++, poly++)
    {
        setPolyFT4(poly);
        {
            int u = src->field_08;
            int w = src->field_0A;
            int uw = u + w;
            int v = src->field_09;
            int h = src->field_0B;

            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = uw;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h;
            poly->u3 = uw;
            poly->v3 = v + h;
        }
        poly->tpage = src->field_04;
        poly->clut = src->field_06;
        poly->code |= 2;
        poly->tpage |= 0x60;
    }
}

void *s05a_800DBD14(SVECTOR *arg0, SVECTOR *arg1)
{
    Smoke *work;
    SVECTOR force;
    SVECTOR size;

    memset(&force, 0, 8);
    work = GV_NewActor(GV_ACTOR_USER, sizeof(Smoke));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, s05a_800DBED0, s05a_800DBF50, s05a_dword_800E34D4);
    work->field_34 = 0;
    work->field_20 = GM_CurrentMap;
    work->field_24 = *arg0;
    work->field_2C = *arg1;

    setVector(&size, 0x3E8, 0x3E8, 0x3E8);
    force.vx = 0x64;
    GM_SetTarget(&work->target, 4, 0, &size);
    GM_SetPowerTarget(&work->target, 7, 2, 5, 2, &force);
    GM_MoveTarget(&work->target, &work->field_24);
    GM_PowerTarget(&work->target);

    setVector(&size, 0x7D0, 0x7D0, 0x7D0);
    force.vx = 0x32;
    GM_SetTarget(&work->target, 4, 0, &size);
    GM_SetPowerTarget(&work->target, 7, 2, 1, 3, &force);
    GM_MoveTarget(&work->target, &work->field_24);
    GM_PowerTarget(&work->target);

    sub_800790E8();
    return work;
}

void s05a_800DBED0(Smoke *work)
{
    int n;

    GM_CurrentMap = work->field_20;
    n = work->field_34 + 1;
    work->field_34 = n;
    if (n == 1)
    {
        s05a_800DBF58(1, &work->field_24, &work->field_2C);
    }
    else if (n == 2)
    {
        sub_8007913C();
    }
    else if (n >= 30)
    {
        GV_DestroyActor(work);
    }
}

void s05a_800DBF50(void *work)
{
    /* do nothing */
}
