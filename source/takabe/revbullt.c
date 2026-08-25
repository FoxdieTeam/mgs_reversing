//#include "revbullt.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "linkvar.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "anime/animconv/anime.h"
#include "game/game.h"
#include "okajima/spark.h"
#include "sound/g_sound.h"

/*---------------------------------------------------------------------------*/

#define TRAILS      1

#define SEGMENT_ATR ( HZD_SEG_NO_NAVIGATE )

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    SVECTOR  pos;
    SVECTOR  step;
    SVECTOR  start;
    MATRIX   world;
    TARGET   target;
    DG_PRIM *prim;
    SVECTOR  verts[TRAILS * 8];
    SVECTOR  trail[(TRAILS + 1) * 4];
    int      draw_trail;
    int      hitlen;
    SVECTOR  endpos;
    SVECTOR  normal;
    int      hitflag;
    int      state;
    int      unused;
    int      wallflag;
    int      bounces;
} Work;

/*---------------------------------------------------------------------------*/

static const SVECTOR bullet_step = { 0, -750, 0 };

static SVECTOR bullet_trail[4] = {
    {  15, 0,   0 },
    { -15, 0,   0 },
    {   0, 0,  15 },
    {   0, 0, -15 }
};

static SVECTOR bullet_path[2] = {
    { 0, -100,    0 },
    { 5, -10740, 32 }
};

static SVECTOR target_size = { 100, 100, 100 };

/*---------------------------------------------------------------------------*/

extern int revolver_used_bul; // from revolver.c

/*---------------------------------------------------------------------------*/

static void PutTrail(SVECTOR *verts)
{
    DG_PutVector(bullet_trail, verts, 4);
}

static void InitTrail(Work *work)
{
    SVECTOR *verts;
    int      i;

    PutTrail(work->trail);

    verts = work->trail;
    for (i = TRAILS; i > 0; i--)
    {
        memcpy(verts + 4, verts, sizeof(SVECTOR) * 4);
        verts += 4;
    }
}

static void UpdateTrail(Work *work)
{
    SVECTOR *verts;
    int      i;

    verts = work->trail + 4;
    for (i = TRAILS; i > 0; i--)
    {
        memcpy(verts, verts - 4, sizeof(SVECTOR) * 4);
        verts -= 4;
    }

    PutTrail(verts);
}

static void CopyTrail(Work *work)
{
    SVECTOR *src, *dst;
    int      i;

    src = work->trail;
    dst = work->verts;

    for (i = TRAILS; i > 0; i--)
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

    for (i = 0; i < TRAILS; i++)
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
            h = tex->h / TRAILS;
            packs->v0 = packs->v1 = y + (h + 1) * i;
            packs->v2 = packs->v3 = y + (h + 1) * (i + 1) - 1;

            packs->tpage = tex->tpage;
            packs->clut = tex->clut;

            packs->tpage |= (3 << 5);
            packs++;
        }
    }
}

static int CalculateHit(Work *work, MATRIX *world)
{
    SVECTOR  point[2];
    int      hit;
    HZD_FLR *floor;
    int      len;

    DG_SetPos(world);
    DG_PutVector(bullet_path, point, 2);

    hit = 0;

    if (HZD_OnlineHazardCheck(GM_GetMap(work->map)->hzd, &point[0], &point[1], HZD_CHK_ALL, SEGMENT_ATR))
    {
        HZD_GetOnlinePoint(&point[1]);

        floor = HZD_GetOnlineHazard();
        if (((int)floor & 0x80000000) != 0)
        {
            HZD_GetNormal(floor, &work->normal);
        }
        else
        {
            work->normal.vx = floor->p1.h * 16;
            work->normal.vz = floor->p2.h * 16;
            work->normal.vy = floor->p3.h * 16;
        }

        hit = 1;
    }

    work->endpos = point[1];

    GV_SubVec3(&point[1], &point[0], &point[0]);
    len = GV_VecLen3(&point[0]);

    work->wallflag = hit;

    return len;
}

static void Act(Work *work)
{
    MATRIX  world;
    SVECTOR pos;
    int     state;

    if (work->hitflag == 0)
    {
        GM_CurrentMap = work->map;

        GV_AddVec3(&work->pos, &work->step, &pos);

        if (GM_OnlineTargetCheck(&work->pos, &pos, work->map, &work->pos, ENEMY_SIDE)
            && GM_GameOverTimer == 0
            && (GM_MoveTarget(&work->target, &work->pos), GM_PowerTarget(&work->target)))
        {
            work->hitlen = 0;
            work->wallflag = 2;
        }
        else
        {
            work->pos = pos;
        }

        work->world.t[0] = work->pos.vx;
        work->world.t[1] = work->pos.vy;
        work->world.t[2] = work->pos.vz;

        SetRotMatrix(&work->world);
        SetTransMatrix(&work->world);

        if (work->draw_trail)
        {
            UpdateTrail(work);
            CopyTrail(work);
        }

        if (GV_DiffVec3(&work->pos, &work->start) >= work->hitlen)
        {
            if (work->wallflag == 1)
            {
                ReadRotMatrix(&world);
                world.t[0] = work->endpos.vx;
                world.t[1] = work->endpos.vy;
                world.t[2] = work->endpos.vz;

                DG_ReflectMatrix(&work->normal, &world, &world);
                NewSpark(&world, 0);

                if (work->bounces > 0)
                {
                    // The call is coming from INSIDE the actor...
                    extern void *NewRevolverBullet(MATRIX *world, int bounces);

                    NewRevolverBullet(&world, work->bounces - 1);
                    AN_RecoilSmoke(&work->endpos);
                    GM_SeSetMode(&work->pos, 176, GM_SEMODE_BOMB);
                }
                else
                {
                    revolver_used_bul++;
                    GM_SeSetMode(&work->pos, SE_REBDRM01, GM_SEMODE_BOMB);
                }
            }

            work->hitflag = 1;
            work->state = 0;

            work->step = DG_ZeroVector;
        }
    }
    else
    {
        state = work->state;
        if (state == 0 && work->draw_trail)
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

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void CreateTarget(Work *work, int side)
{
    SVECTOR force;
    TARGET *target;
    int     damage;

    target = &work->target;
    GM_SetTarget(target, TARGET_POWER, side, &target_size);

    force.vx = work->step.vx / 32;
    force.vy = work->step.vy / 32;
    force.vz = work->step.vz / 32;

    if (GM_GameLevel > 0)
    {
        damage = GM_GameLevel * 6 + 48;
    }
    else
    {
        damage = 48;
    }

    GM_SetPowerTarget(target, POWER_DECREASE, 1, damage, 0, &force);
}

static int GetResources(Work *work, MATRIX *world, int visible, int instant)
{
    SVECTOR  step;
    int      len;
    DG_PRIM *prim;
    DG_TEX  *tex;

    step = bullet_step;

    work->map = GM_CurrentMap;

    work->world = *world;
    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];

    DG_SetPos(world);

    work->hitlen = CalculateHit(work, world);
    if (instant != 0)
    {
        len = work->hitlen;
        if (work->wallflag == 0)
        {
            len = 750;
        }

        step.vy = -len;
    }

    DG_RotVector(&step, &work->step, 1);

    work->start.vx = work->pos.vx;
    work->start.vy = work->pos.vy;
    work->start.vz = work->pos.vz;

    if (visible != 0)
    {
        prim = GM_MakePrim(DG_PRIM_POLY_FT4, TRAILS * 2, work->verts, NULL);
        work->prim = prim;
        if (prim == NULL)
        {
            return -1;
        }

        DG_RaisePrim(prim, 1000);

        tex = DG_GetTexture(GV_StrCode("bullet"));
        if (tex == NULL)
        {
            return -1;
        }

        InitPacks(prim->packs[0], tex);
        InitPacks(prim->packs[1], tex);
        InitTrail(work);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRevolverBullet(MATRIX *world, int bounces)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "revbullt.c");

        if (GetResources(work, world, 1, 0) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        CreateTarget(work, ENEMY_SIDE);

        work->draw_trail = 1;
        work->hitflag = 0;
        work->bounces = bounces;
        work->unused = 0;
    }

    return (void *)work;
}
