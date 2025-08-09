#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "linkvar.h"
#include "okajima/spark.h"
#include "sd/g_sound.h"

typedef struct _RevbulltWork
{
    GV_ACT   actor;
    int      map;
    SVECTOR  f24;
    SVECTOR  f2C;
    SVECTOR  f34;
    MATRIX   f3C;
    TARGET   target;
    DG_PRIM *prim;
    SVECTOR  verts[8];
    SVECTOR  verts2[8];
    int      f128;
    int      f12C;
    SVECTOR  position;
    SVECTOR  normal;
    int      f140;
    int      state;
    int      f148;
    int      f14C;
    int      bounces;
} RevbulltWork;

#define SEGMENT_ATR ( HZD_SEG_NO_NAVIGATE )

const SVECTOR s04c_dword_800DBAE4 = {0, -750, 0, 0};

SVECTOR s04c_dword_800C35B0[4] = {{15, 0, 0, 0}, {-15, 0, 0, 0}, {0, 0, 15, 0}, {0, 0, -15, 0}};
SVECTOR s04c_dword_800C35D0[2] = {{0, -100, 0, 0}, {5, -10740, 32, 0}};
SVECTOR s04c_dword_800C35E0 = {100, 100, 100, 0};

int s04c_dword_800DBE20;

void *NewRevolverBullet(MATRIX *world, int bounces);

#define EXEC_LEVEL GV_ACTOR_LEVEL5

static void TransformPrim(SVECTOR *verts)
{
    DG_PutVector(s04c_dword_800C35B0, verts, 4);
}

static void PushPrim(RevbulltWork *work)
{
    SVECTOR *verts;
    int      i;

    TransformPrim(work->verts2);

    verts = work->verts2;
    for (i = 1; i > 0; i--)
    {
        memcpy(verts + 4, verts, sizeof(SVECTOR) * 4);
        verts += 4;
    }
}

static void PushPrim2(RevbulltWork *work)
{
    SVECTOR *verts;
    int      i;

    verts = &work->verts2[4];
    for (i = 1; i > 0; i--)
    {
        memcpy(verts, verts - 4, sizeof(SVECTOR) * 4);
        verts -= 4;
    }

    TransformPrim(verts);
}

static void InitPrim(RevbulltWork *work)
{
    SVECTOR *src;
    SVECTOR *dst;
    int      i;

    src = work->verts2;
    dst = work->verts;

    for (i = 1; i > 0; i--)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[4];
        dst[3] = src[5];
        dst[4] = src[2];
        dst[5] = src[3];
        dst[6] = src[6];
        dst[7] = src[7];

        dst += 8;
        src += 4;
    }
}

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex)
{
    int i, j;
    int shade;
    int x, y, w, h;

    for (i = 0; i <= 0; i++)
    {
        for (j = 2; j > 0; j--)
        {
            setPolyFT4(packs);
            setSemiTrans(packs, 1);

            shade = GV_RandS(64) + 191;
            setRGB0(packs, shade, shade, shade);

            x = tex->off_x;
            w = tex->w;
            packs->u0 = packs->u2 = x;
            packs->u1 = packs->u3 = w + x;

            y = tex->off_y;
            h = tex->h;
            packs->v0 = packs->v1 = y + (h + 1) * i;
            packs->v2 = packs->v3 = y + (h + 1) * (i + 1) - 1;

            packs->tpage = tex->tpage;
            packs->clut = tex->clut;

            packs->tpage |= 0x60;
            packs++;
        }
    }
}

static int CalculateHit(RevbulltWork *work, MATRIX *world)
{
    SVECTOR  sp18[2];
    int      ret;
    HZD_FLR *floor;
    int      len;

    DG_SetPos(world);
    DG_PutVector(s04c_dword_800C35D0, sp18, 2);

    ret = 0;
    if (HZD_LineCheck(GM_GetMap(work->map)->hzd, &sp18[0], &sp18[1], HZD_CHECK_ALL, SEGMENT_ATR))
    {
        HZD_LineNearVec(&sp18[1]);

        floor = HZD_LineNearSurface();
        if (((int)floor & 0x80000000) != 0)
        {
            HZD_SurfaceNormal(floor, &work->normal);
        }
        else
        {
            work->normal.vx = floor->p1.h * 16;
            work->normal.vz = floor->p2.h * 16;
            work->normal.vy = floor->p3.h * 16;
        }

        ret = 1;
    }

    work->position = sp18[1];

    GV_SubVec3(&sp18[1], &sp18[0], &sp18[0]);
    len = GV_VecLen3(&sp18[0]);

    work->f14C = ret;

    return len;
}

static void Act(RevbulltWork *work)
{
    MATRIX  world;
    SVECTOR sp38;
    int     state;

    if (work->f140 == 0)
    {
        GM_CurrentMap = work->map;

        GV_AddVec3(&work->f24, &work->f2C, &sp38);

        if (GM_Target_8002E1B8(&work->f24, &sp38, work->map, &work->f24, ENEMY_SIDE)
            && GM_GameOverTimer == 0
            && (GM_MoveTarget(&work->target, &work->f24), GM_PowerTarget(&work->target)))
        {
            work->f12C = 0;
            work->f14C = 2;
        }
        else
        {
            work->f24 = sp38;
        }

        work->f3C.t[0] = work->f24.vx;
        work->f3C.t[1] = work->f24.vy;
        work->f3C.t[2] = work->f24.vz;

        SetRotMatrix(&work->f3C);
        SetTransMatrix(&work->f3C);

        if (work->f128 != 0)
        {
            PushPrim2(work);
            InitPrim(work);
        }

        if (GV_DiffVec3(&work->f24, &work->f34) >= work->f12C)
        {
            if (work->f14C == 1)
            {
                ReadRotMatrix(&world);
                world.t[0] = work->position.vx;
                world.t[1] = work->position.vy;
                world.t[2] = work->position.vz;

                DG_ReflectMatrix(&work->normal, &world, &world);
                NewSpark(&world, 0);

                if (work->bounces > 0)
                {
                    NewRevolverBullet(&world, work->bounces - 1);
                    NewAnime_8005E508(&work->position);
                    GM_SeSetMode(&work->f24, 176, GM_SEMODE_BOMB);
                }
                else
                {
                    s04c_dword_800DBE20++;
                    GM_SeSetMode(&work->f24, SE_REBDRM01, GM_SEMODE_BOMB);
                }
            }

            work->f140 = 1;
            work->state = 0;

            work->f2C = DG_ZeroVector;
        }
    }
    else
    {
        state = work->state;
        if (state == 0 && work->f128 != 0)
        {
            DG_InvisiblePrim(work->prim);
        }

        if (state > 2)
        {
            GV_DestroyActor(&work->actor);
            return;
        }

        work->state = state + 1;
    }
}

static void Die(RevbulltWork *work)
{
    GM_FreePrim(work->prim);
}

static void CreateTarget(RevbulltWork *work, int side)
{
    SVECTOR pos;
    TARGET *target;
    int     damage;

    target = &work->target;
    GM_SetTarget(target, TARGET_POWER, side, &s04c_dword_800C35E0);

    pos.vx = work->f2C.vx / 32;
    pos.vy = work->f2C.vy / 32;
    pos.vz = work->f2C.vz / 32;

    if (GM_DifficultyFlag > 0)
    {
        damage = (GM_DifficultyFlag * 6) + 48;
    }
    else
    {
        damage = 48;
    }

    GM_Target_8002DCCC(target, 1, 1, damage, 0, &pos);
}

static int GetResources(RevbulltWork *work, MATRIX *world, int visible, int arg3)
{
    SVECTOR  sp18;
    int      k500 = 1000;
    int      height;
    DG_PRIM *prim;
    DG_TEX  *tex;

    sp18 = s04c_dword_800DBAE4;

    work->map = GM_CurrentMap;

    work->f3C = *world;
    work->f24.vx = world->t[0];
    work->f24.vy = world->t[1];
    work->f24.vz = world->t[2];

    DG_SetPos(world);

    work->f12C = CalculateHit(work, world);
    if (arg3 != 0)
    {
        height = work->f12C;
        if (work->f14C == 0)
        {
            height = 750;
        }

        sp18.vy = -height;
    }

    DG_RotVector(&sp18, &work->f2C, 1);

    work->f34.vx = work->f24.vx;
    work->f34.vy = work->f24.vy;
    work->f34.vz = work->f24.vz;

    if (visible != 0)
    {
        prim = DG_GetPrim(DG_PRIM_POLY_FT4, 2, 0, work->verts, NULL);
        work->prim = prim;
        if (prim == NULL)
        {
            return -1;
        }

        prim->field_2E_k500 = k500;

        tex = DG_GetTexture(GV_StrCode("bullet"));
        if (tex == NULL)
        {
            return -1;
        }

        InitPacks(&prim->packs[0]->poly_ft4, tex);
        InitPacks(&prim->packs[1]->poly_ft4, tex);
        PushPrim(work);
    }

    return 0;
}

void *NewRevolverBullet(MATRIX *world, int bounces)
{
    RevbulltWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(RevbulltWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "revbullt.c");

        if (GetResources(work, world, 1, 0) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        CreateTarget(work, ENEMY_SIDE);

        work->f128 = 1;
        work->f140 = 0;
        work->bounces = bounces;
        work->f148 = 0;
    }

    return (void *)work;
}
