#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;       /* 0x000 */
    CONTROL control;     /* 0x020 */
    OBJECT  body;        /* 0x09C */
    MATRIX  light[2];    /* 0x180 */
    TARGET  target;      /* 0x1C0 */
    MATRIX  field_208;   /* 0x208 */
    SVECTOR *field_228;  /* 0x228 */
    SVECTOR field_22C;   /* 0x22C */
    int     field_234;   /* 0x234 */
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
    SVECTOR  verts[8];  /* 0x28 */
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
void  s05a_800DB278(Work *work);
void  s05a_800DB654(Work *work);

void *s05a_800DAE58(int name, MATRIX *mat, int side, SVECTOR *target_pos, int vital, int range, int speed, int *result)
{
    Work   *work;
    SVECTOR vec1;
    SVECTOR vec2;
    int     dist;
    short   h;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }
    work->field_228 = target_pos;
    work->field_234 = vital;
    work->field_23C = speed;
    work->field_240 = result;
    work->field_238 = range / speed;
    GV_SetNamedActor(work, s05a_800DB278, s05a_800DB654, s05a_dword_800E34D4);

    if (GM_InitControl(&work->control, 0, 0) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    work->field_208 = *mat;
    DG_SetPos(mat);
    memset(&vec1, 0, 8);
    vec2.vx = 0;
    vec2.vy = 0;
    vec2.vz = 0x64;
    DG_PutVector(&vec1, &vec1, 1);
    DG_PutVector(&vec2, &vec2, 1);
    vec2.vx -= vec1.vx;
    vec2.vy -= vec1.vy;
    vec2.vz -= vec1.vz;
    dist = SquareRoot0(vec2.vx * vec2.vx + vec2.vz * vec2.vz);
    work->control.rot.vx = -ratan2(vec2.vy, dist);
    work->control.rot.vy = ratan2(vec2.vx, vec2.vz);
    work->control.rot.vz = 0;
    work->control.turn = work->control.rot;
    work->control.mov.vx = mat->t[0];
    work->control.mov.vy = mat->t[1];
    work->control.mov.vz = mat->t[2];

    GM_InitObject(&work->body, name, 0x36D, 0);
    GM_ConfigObjectLight(&work->body, work->light);

    vec1.vx = work->body.objs->def->ux - work->body.objs->def->lx;
    vec1.vy = work->body.objs->def->uy - work->body.objs->def->ly;
    vec1.vz = work->body.objs->def->uz - work->body.objs->def->lz;
    GM_ConfigControlHazard(&work->control, vec1.vx, vec1.vy, vec1.vz);

    h = vec1.vy;
    if (h < vec1.vx) h = vec1.vx;
    work->field_248 = h;
    {
        int r, s;
        r = vec1.vz;
        if (r < h) r = h;
        work->field_248 = r;
        s = work->field_23C;
        if (s < r) s = r;
        work->field_248 = s * 3 / 5;
    }

    vec1.vx = work->field_248;
    vec1.vy = work->field_248;
    vec1.vz = work->field_248;
    GM_SetTarget(&work->target, 4, side, &vec1);

    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = 0;
    DG_SetPos2(&vec1, &work->control.rot);
    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = work->field_23C / 10;
    DG_PutVector(&vec1, &vec1, 1);
    GM_SetPowerTarget(&work->target, 0, -1, work->field_234, 0, &vec1);
    return work;
}
void s05a_800DB278(Work *work)
{
    SVECTOR vec;
    int s0;
    int s2 = 0;

    work->field_22C = work->control.mov;
    GM_ActControl(&work->control);
    GM_ActObject2(&work->body);
    DG_GetLightMatrix2(&work->control.mov, &work->light[0]);
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
extern const char s05a_dword_800E34E0[];
void s05a_800DBA94(Casing *work);
void s05a_800DBC44(Casing *work);
void s05a_800DBC80(POLY_FT4 *poly, DG_TEX *src);

void *s05a_800DB684(Work *parent)
{
    Casing  *casing;
    DG_PRIM *prim;
    DG_TEX  *tex;
    SVECTOR  off1;
    SVECTOR  off2;

    casing = GV_NewActor(GV_ACTOR_USER, sizeof(Casing));
    if (casing == NULL)
    {
        return NULL;
    }
    GV_SetNamedActor(casing, s05a_800DBA94, s05a_800DBC44, s05a_dword_800E34D4);

    casing->field_6C = 0xFF;
    casing->field_70 = 0xE0;
    casing->field_74 = 0xC0;
    casing->field_20 = GM_CurrentMap;

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, casing->verts, NULL);
    casing->field_24 = prim;
    tex = DG_GetTexture(GV_StrCode(s05a_dword_800E34E0));
    s05a_800DBC80((POLY_FT4 *)casing->field_24->packs[0], tex);
    s05a_800DBC80((POLY_FT4 *)casing->field_24->packs[1], tex);
    casing->field_24->raise = 0x3E8;

    off1.vx = parent->body.objs->def->lx - parent->body.objs->def->ux;
    off1.vy = parent->body.objs->def->ly - parent->body.objs->def->uy;
    off1.vz = 0;
    off2.vx = -off1.vx;
    off2.vz = 0;
    off2.vy = -off1.vy;
    DG_SetPos2(&DG_ZeroVector, &parent->control.rot);
    DG_PutVector(&off1, &off1, 1);
    DG_PutVector(&off2, &off2, 1);

    casing->verts[0].vx = parent->field_22C.vx;
    casing->verts[0].vy = parent->field_22C.vy + off2.vy;
    casing->verts[0].vz = parent->field_22C.vz;
    casing->verts[1].vx = parent->field_22C.vx;
    casing->verts[1].vy = parent->field_22C.vy + off1.vy;
    casing->verts[1].vz = parent->field_22C.vz;
    casing->verts[4].vx = parent->field_22C.vx + off2.vx;
    casing->verts[4].vy = parent->field_22C.vy;
    casing->verts[4].vz = parent->field_22C.vz;
    casing->verts[5].vx = parent->field_22C.vx + off1.vx;
    casing->verts[5].vy = parent->field_22C.vy;
    casing->verts[5].vz = parent->field_22C.vz;
    casing->verts[2].vx = parent->control.mov.vx;
    casing->verts[2].vy = parent->control.mov.vy + off2.vy;
    casing->verts[2].vz = parent->control.mov.vz;
    casing->verts[3].vx = parent->control.mov.vx;
    casing->verts[3].vy = parent->control.mov.vy + off1.vy;
    casing->verts[3].vz = parent->control.mov.vz;
    casing->verts[6].vx = parent->control.mov.vx + off2.vx;
    casing->verts[6].vy = parent->control.mov.vy;
    casing->verts[6].vz = parent->control.mov.vz;
    casing->verts[7].vx = parent->control.mov.vx + off1.vx;
    casing->verts[7].vy = parent->control.mov.vy;
    casing->verts[7].vz = parent->control.mov.vz;

    setRGB0((POLY_FT4 *)casing->field_24->packs[0], casing->field_6C, casing->field_70, casing->field_74);
    setRGB0((POLY_FT4 *)casing->field_24->packs[0] + 1, casing->field_6C, casing->field_70, casing->field_74);
    setRGB0((POLY_FT4 *)casing->field_24->packs[1], casing->field_6C, casing->field_70, casing->field_74);
    setRGB0((POLY_FT4 *)casing->field_24->packs[1] + 1, casing->field_6C, casing->field_70, casing->field_74);

    return casing;
}

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

void s05a_800DBC80(POLY_FT4 *poly, DG_TEX *src)
{
    int i;

    for (i = 0; i < 2; i++, poly++)
    {
        setPolyFT4(poly);
        {
            int u = src->off_x;
            int w = src->w;
            int uw = u + w;
            int v = src->off_y;
            int h = src->h;

            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = uw;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h;
            poly->u3 = uw;
            poly->v3 = v + h;
        }
        poly->tpage = src->tpage;
        poly->clut = src->clut;
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
