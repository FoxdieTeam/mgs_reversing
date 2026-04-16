#include "linkvar.h"
#include "game/game.h"
#include "libgcl/libgcl.h"

#define EXEC_LEVEL 6

typedef struct _Work
{
    GV_ACT   actor;
    int      name;
    TARGET   target;
    SVECTOR  start;
    SVECTOR  end;
    SVECTOR  size;
    SVECTOR  field_84;
    char     pad1[0x8];
    int      n_vecs;
    SVECTOR  vecs[3];
    u_short  map;
    short    field_B2;
    short    field_B4;
    short    field_B6;
    u_short  field_B8;
    u_short  field_BA;
    u_short  field_BC;
    short    field_BE;
    SVECTOR  field_C0[16];
    SVECTOR  field_140[16];
    RECT     field_1C0[16];
    DG_PRIM *field_240[16];
    DG_TEX  *tex;
    u_short  tx;
    u_short  ty;
    u_short  tw;
    u_short  th;
} Work;

static int dsmoke2_life = 36;

void AN_DamageSmoke1( SVECTOR * );

int s11d_dsmoke2_800CC08C(Work *work, SVECTOR *pos)
{
    int yh, yl;

    if (work->start.vy > work->end.vy)
    {
        yh = work->start.vy + 2000;
        yl = work->end.vy - 2000;
    }
    else
    {
        yh = work->end.vy + 2000;
        yl = work->start.vy - 2000;
    }

    if ((pos->vy > yh) || (pos->vy < yl))
    {
        return 0;
    }

    return 1;
}

void s11d_dsmoke2_800CC0E0(Work *work, SVECTOR *arg1, SVECTOR *size)
{
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR *pos;
    SVECTOR *vec;
    int      map;
    int      hit;
    int      count;

    pos = &GM_PlayerPosition;
    vec = work->vecs;
    map = work->map;
    hit = 0;
    count = work->n_vecs;
    while (--count >= 0)
    {
        GV_AddVec3(vec, arg1, &sp18);
        GV_AddVec3(&sp18, size, &sp20);

        hit = GM_Target_8002E1B8(&sp18, &sp20, map, &sp20, ENEMY_SIDE);
        if (hit)
        {
            break;
        }

        vec++;
    }

    if (hit)
    {
        GM_MoveTarget(&work->target, pos);
        GM_PowerTarget(&work->target);
    }
}

void s11d_dsmoke2_800CC1DC(Work *work)
{
    SVECTOR sp10;
    SVECTOR size;
    u_short index;
    u_short temp_s3;
    u_short temp_s2;

    temp_s3 = work->field_B4;
    temp_s2 = work->field_BA;

    if (++work->field_BA > temp_s3)
    {
        work->field_BA = 0;
        work->field_B8 = 0;
        work->field_B2 = 0;
        return;
    }

    if (temp_s2 == 0)
    {
        GM_SeSet(&work->start, 186);
    }

    if (temp_s2 < 16)
    {
        DG_VisiblePrim(work->field_240[temp_s2]);
    }

    if (temp_s2 >= (temp_s3 - 16))
    {
        index = temp_s2 - (temp_s3 - 16);
        DG_InvisiblePrim(work->field_240[index]);
    }

    if (s11d_dsmoke2_800CC08C(work, &GM_PlayerPosition))
    {
        if (temp_s2 < 16)
        {
            size.vx = temp_s2 * work->field_84.vx;
            size.vy = temp_s2 * work->field_84.vy;
            size.vz = temp_s2 * work->field_84.vz;
        }
        else
        {
            size = work->size;
        }

        if (temp_s2 >= (temp_s3 - 16))
        {
            index = temp_s2 - (temp_s3 - 16);
            DG_InvisiblePrim(work->field_240[index]);

            sp10.vx = index * work->field_84.vx;
            sp10.vy = index * work->field_84.vy;
            sp10.vz = index * work->field_84.vz;
        }
        else
        {
            sp10 = DG_ZeroVector;
        }

        GV_SubVec3(&size, &sp10, &size);
        s11d_dsmoke2_800CC0E0(work, &sp10, &size);
    }
}

void s11d_dsmoke2_800CC418(Work *work)
{
    int index;

    index = work->field_B8;
    if (index >= 16)
    {
        work->field_BE = 16;
    }
    else
    {
        work->field_BE++;
        DG_VisiblePrim(work->field_240[index]);
    }

    work->field_B8++;

    if (s11d_dsmoke2_800CC08C(work, &GM_PlayerPosition))
    {
        s11d_dsmoke2_800CC0E0(work, &DG_ZeroVector, &work->size);
    }
}

void s11d_dsmoke2_800CC4B8(Work *work)
{
    int       i;
    DG_PRIM  *prim;
    POLY_FT4 *pack;
    int       x, y, w, h;
    int       xs, ys;

    x = work->tx;
    y = work->ty;
    h = work->th;
    w = work->tw;

    for (i = 0; i < 16; i++)
    {
        prim = work->field_240[i];
        pack = prim->packs[GV_Clock];

        if (prim->type & DG_PRIM_INVISIBLE)
        {
            continue;
        }

        xs = GV_RandU(1024) % 7;
        ys = GV_RandU(1024) % 4;

        pack->u0 = pack->u2 = x + (w * xs) / 8;
        pack->u1 = pack->u3 = x + (w * (xs + 1)) / 8 - 1;

        pack->v0 = pack->v1 = y + (h * ys) / 4;
        pack->v2 = pack->v3 = y + (h * (ys + 1)) / 4 - 1;
    }
}

void s11d_dsmoke2_800CC648(Work *work)
{
    GM_CurrentMap = work->map;

    if (work->field_BC != 0)
    {
        work->field_BC--;
        return;
    }

    if (work->field_B4 >= 0)
    {
        if (work->field_B2 == 0)
        {
            if (work->field_B8 == work->field_B6)
            {
                work->field_B2 = 1;
            }

            if ((work->field_B8 >= (work->field_B6 - 24)) && (work->field_B8 < (work->field_B6 - 18)))
            {
                if (work->field_B8 == work->field_B6 - 24)
                {
                    GM_SeSet(&work->start, 176);
                }

                AN_DamageSmoke1(&work->start);
            }

            work->field_B8++;
        }
        else
        {
            s11d_dsmoke2_800CC1DC(work);
        }
    }
    else
    {
        s11d_dsmoke2_800CC418(work);
    }

    s11d_dsmoke2_800CC4B8(work);
}

void s11d_dsmoke2_800CC730(Work *work)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        GM_FreePrim(work->field_240[i]);
    }
}

int s11d_dsmoke2_800CC794(Work *work)
{
    DG_TEX   *tex;
    SVECTOR  *vert;
    SVECTOR  *sp18;
    RECT     *rect;
    int       shade;
    int       i, j;
    int       height;
    int       rad;
    DG_PRIM  *prim;
    POLY_FT4 *pack;
    int       x, y, w, h;

    tex = work->tex = DG_GetTexture(GV_StrCode("smoke"));
    work->tx = tex->off_x;
    work->ty = tex->off_y;
    work->tw = tex->w + 1;
    work->th = tex->h + 1;
    if (tex == NULL)
    {
        return -1;
    }

    vert = work->field_C0;
    sp18 = work->field_140;
    rect = work->field_1C0;
    shade = 96;

    for (i = 0; i < 16; i++, vert++, rect++, sp18++)
    {
        if (i < 8)
        {
            height = i * 30 + 750;
        }
        else
        {
            height = (i - 8) * 120 + 1000;
        }

        rad = GV_VecLen3(&work->field_84) / 2;
        rect->x = rad * 3;
        rect->w = rect->x * 2;
        rect->y = height / 2;
        rect->h = height;

        vert->vx = work->start.vx + work->field_84.vx * i + GV_RandS(64);
        vert->vy = work->start.vy + work->field_84.vy * i + GV_RandS(64);
        vert->vz = work->start.vz + work->field_84.vz * i + GV_RandS(64);

        *sp18 = *vert;

        work->field_240[i] = prim = GM_MakePrim(0x412, 1, vert, rect);
        if (prim == NULL)
        {
            return -1;
        }

        shade -= 5;

        prim->raise = 500;
        DG_InvisiblePrim(prim);

        for (j = 0; j < 2; j++)
        {
            pack = prim->packs[j];
            setPolyFT4(pack);
            setSemiTrans(pack, 1);
            setRGB0(pack, shade, shade, shade);

            x = tex->off_x;
            w = tex->w;
            pack->u0 = pack->u2 = x;
            pack->u1 = pack->u3 = x + (w + 1) / 8 - 1;

            y = tex->off_y;
            h = tex->h;
            pack->v0 = pack->v1 = y;
            pack->v2 = pack->v3 = y + (h + 1) / 4 - 1;

            pack->tpage = tex->tpage;
            pack->clut = tex->clut;

            pack->tpage = (pack->tpage & ~0x60) | (1 << 5);
        }
    }

    return 0;
}

int s11d_dsmoke2_800CCAB4(Work *work)
{
    SVECTOR size;
    int     difficulty;
    int     i;

    GCL_StrToSV(GCL_GetOption('s'), &work->start);
    GCL_StrToSV(GCL_GetOption('e'), &work->end);

    GCL_GetOption('i');
    work->field_B4 = GCL_StrToInt(GCL_GetParamResult());
    work->field_B6 = GCL_StrToInt(GCL_GetParamResult());
    work->field_BC = GCL_StrToInt(GCL_GetOption('d'));
    work->field_B8 = 0;
    work->field_BA = 0;

    GV_SubVec3(&work->end, &work->start, &work->size);

    work->field_84.vx = work->size.vx / 16;
    work->field_84.vy = work->size.vy / 16;
    work->field_84.vz = work->size.vz / 16;

    difficulty = GM_DifficultyFlag;
    if (difficulty < DIFFICULTY_EASY)
    {
        difficulty = DIFFICULTY_EASY;
    }

    if (GCL_GetOption('x'))
    {
        for (i = 0; i < difficulty; i++)
        {
            GCL_GetNextParamValue();
        }

        dsmoke2_life = GCL_GetNextParamValue();
    }

    size.vx = size.vy = size.vz = 250;
    GM_SetTarget(&work->target, 4, 2, &size);
    GM_Target_8002DCCC(&work->target, 3, 2, dsmoke2_life, -1, &DG_ZeroVector);

    work->field_B2 = 0;
    work->field_BE = 0;
    return 0;
}

void s11d_dsmoke2_800CCC60(Work *work)
{
    int      count;
    SVECTOR *vec;
    char    *res;

    count = 0;

    if (GCL_GetOption('b'))
    {
        vec = work->vecs;

        while ((res = GCL_GetParamResult()))
        {
            if (count == 3)
            {
                break;
            }

            GCL_StrToSV(res, vec);
            vec++;
            count++;
        }
    }

    work->n_vecs = count;
}

int DSGetResources(Work *work, int name, int where)
{
    GM_CurrentMap = where;

    if (s11d_dsmoke2_800CCAB4(work) < 0)
    {
        return -1;
    }

    s11d_dsmoke2_800CCC60(work);

    if (s11d_dsmoke2_800CC794(work) < 0)
    {
        return -1;
    }

    work->name = name;
    work->map = GM_CurrentMap;
    return 0;
}

void *NewDamageSmoke2(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s11d_dsmoke2_800CC648, s11d_dsmoke2_800CC730, "dsmoke2.c");

        if (DSGetResources(work, name, where) >= 0)
        {
            return work;
        }

        GV_DestroyActor(work);
    }

    return NULL;
}
