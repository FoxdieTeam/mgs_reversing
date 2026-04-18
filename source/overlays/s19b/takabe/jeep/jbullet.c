#include "game/game.h"

#define EXEC_LEVEL 5

// TODO: This type of struct is seen in other places that make use of HZD_FLR.
typedef struct _BULLET_VECS
{
    SVECTOR vecs[4];
} BULLET_VECS;

typedef struct _Work
{
    GV_ACT      actor;
    int         map;
    MATRIX      world;
    TARGET      target;
    DG_PRIM    *prim;
    SVECTOR     vertices[8];
    BULLET_VECS vecs[2];
    SVECTOR     pos;
    SVECTOR     hit_point;
    SVECTOR     step;
    SVECTOR     normal;
    void       *hit_surface;
    int         mode;
    int         hit_dist;
    int         range;
    int         hit;
    int         mode2;
    int         side;
    int         spark_flag;
    int         size;
    int         life;
    int         max_dist;
    int         range_step;
    int         range_scale;
    int         hit_type;
    int         hit_test;
    int         hit_flag;
} Work;

static SVECTOR s19b_dword_800C3380[4] =
{
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

static SVECTOR s19b_dword_800C33A0 = {0, 400, 0};
static VECTOR  s19b_dword_800C33A8 = {0, 0, 0};
static SVECTOR s19b_dword_800C33B8 = {0, -15000, 0};
static SVECTOR s19b_dword_800C33C0 = {100, 100, 100};
static SVECTOR s19b_dword_800C33C8 = {0, 0, 0};
static SVECTOR s19b_dword_800C33D0 = {0, 400, 0};

void NewJeepSpark(MATRIX *, int);

static void InitVertices(SVECTOR *vecs, int scale)
{
    s19b_dword_800C3380[0].vx = scale;
    s19b_dword_800C3380[1].vx = -scale;
    s19b_dword_800C3380[2].vz = scale;
    s19b_dword_800C3380[3].vz = -scale;

    DG_PutVector(s19b_dword_800C3380, vecs, 4);
}

static void PushVertices(Work *work)
{
    BULLET_VECS *vecs;
    int          i;

    InitVertices(work->vecs[0].vecs, work->size);

    vecs = &work->vecs[0];
    for (i = 1; i > 0; i--)
    {
        vecs[1] = vecs[0];
        vecs++;
    }
}

static void PopVertices(Work *work)
{
    BULLET_VECS *vecs;
    int          i;

    vecs = &work->vecs[1];
    for (i = 1; i > 0; i--)
    {
        if (work->mode != 2)
        {
            vecs[0] = vecs[-1];
        }

        vecs--;
    }

    InitVertices(vecs->vecs, work->size);
}

static void UpdateVertices(Work *work)
{
    int          i;
    BULLET_VECS *vecs;
    SVECTOR     *verts;

    vecs = &work->vecs[0];
    verts = work->vertices;
    for (i = 1; i > 0; i--)
    {
        verts[0] = vecs[0].vecs[0];
        verts[1] = vecs[0].vecs[1];
        verts[2] = vecs[1].vecs[0];
        verts[3] = vecs[1].vecs[1];
        verts[4] = vecs[0].vecs[2];
        verts[5] = vecs[0].vecs[3];
        verts[6] = vecs[1].vecs[2];
        verts[7] = vecs[1].vecs[3];
        verts += 8;
        vecs++;
    }
}

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex, int mode)
{
    int i, j;
    int r, gb;
    int x, y, w, h;

    for (i = 0; i < 1; i++)
    {
        for (j = 2; j > 0; j--)
        {
            setPolyFT4(packs);
            setSemiTrans(packs, 1);

            if (mode == 2)
            {
                r = 255;
                gb = 85;
            }
            else
            {
                r = GV_RandU(128) - 32;
                gb = (r / 3) * 2;
            }

            setRGB0(packs, r, gb, gb);

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

            packs->tpage |= (3 << 5);
            packs++;
        }
    }
}

static int FindIntersection(Work *work, MATRIX *world, int mode2)
{
    SVECTOR  from;
    SVECTOR  to;
    SVECTOR  origin;
    VECTOR   end;
    VECTOR   dist;
    SVECTOR  step;
    int      t, dt;
    MAP     *map;
    HZD_FLR *floor;

    DG_PutVector(&s19b_dword_800C33A0, &origin, 1);
    from = origin;

    s19b_dword_800C33A8.vy = -work->max_dist;
    ApplyRotMatrixLV(&s19b_dword_800C33A8, &end);
    end.vx += origin.vx;
    end.vy += origin.vy;
    end.vz += origin.vz;

    if (work->max_dist > 15000)
    {
        ApplyRotMatrix(&s19b_dword_800C33B8, &dist);

        step.vx = dist.vx;
        step.vy = dist.vy;
        step.vz = dist.vz;
        GV_AddVec3(&origin, &step, &to);
        dt = 15000;
    }
    else
    {
        to.vx = end.vx;
        to.vy = end.vy;
        to.vz = end.vz;
        dt = work->max_dist;
    }

    work->hit_point = to;

    t = 0;
    map = GM_GetMap(work->map);

    while (1)
    {
        if ((work->hit_test == 1) && HZD_LineCheck(map->hzd, &from, &to, 0xF, 0x4))
        {
            HZD_LineNearVec(&work->hit_point);
            work->hit_surface = HZD_LineNearSurface();
            work->hit_flag = HZD_LineNearFlag();

            if ((int)work->hit_surface & 0x80000000)
            {
                /* hit wall */
                work->hit_type = 1;
                HZD_SurfaceNormal(work->hit_surface, &work->normal);
            }
            else
            {
                /* hit floor */
                work->hit_type = 2;
                floor = work->hit_surface;
                work->normal.vx = floor->p1.h * 16;
                work->normal.vz = floor->p2.h * 16;
                work->normal.vy = floor->p3.h * 16;
            }

            work->hit = 1;

            dist.vx = (work->hit_point.vx - origin.vx) >> 1;
            dist.vy = (work->hit_point.vy - origin.vy) >> 1;
            dist.vz = (work->hit_point.vz - origin.vz) >> 1;
            Square0(&dist, &dist);
            return SquareRoot0(dist.vx + dist.vy + dist.vz) * 2;
        }

        t += dt;
        if (t >= work->max_dist)
        {
            return work->max_dist;
        }

        from = to;

        if ((t + dt) >= work->max_dist)
        {
            to.vx = end.vx;
            to.vy = end.vy;
            to.vz = end.vz;
        }
        else
        {
            to.vx += step.vx;
            to.vy += step.vy;
            to.vz += step.vz;
        }
    }
}

static void Act(Work *work)
{
    MATRIX  inv;
    SVECTOR pos;
    MAP    *map;

    GM_CurrentMap = work->map;
    map = GM_GetMap(work->map);

    work->range += work->range_step;
    if (work->range > work->hit_dist)
    {
        pos = work->hit_point;
    }
    else
    {
        GV_AddVec3(&work->pos, &work->step, &pos);
    }

    if (GM_Target_8002E1B8(&work->pos, &pos, map->index, &pos, work->side))
    {
        GM_MoveTarget(&work->target, &pos);
        GM_PowerTarget(&work->target);
        GV_DestroyActor(work);
        return;
    }

    work->pos = pos;

    if (work->mode != 0)
    {
        work->world.t[0] = work->pos.vx;
        work->world.t[1] = work->pos.vy;
        work->world.t[2] = work->pos.vz;
        DG_SetPos(&work->world);
        PopVertices(work);
        UpdateVertices(work);
    }

    if (work->range > work->hit_dist)
    {
        if (work->hit == 1)
        {
            work->world.t[0] = work->hit_point.vx;
            work->world.t[1] = work->hit_point.vy;
            work->world.t[2] = work->hit_point.vz;
            inv = work->world;
            DG_ReflectMatrix(&work->normal, &inv, &inv);

            if (work->spark_flag & 0x200)
            {
                NewJeepSpark(&inv, 1);
            }
            else if (work->spark_flag & 0x100)
            {
                NewJeepSpark(&inv, work->mode2 == 2);
            }

            GM_SeSet(&work->hit_point, SE_REBDRM01);

            if (work->mode2 == 2)
            {
                GM_SetNoise(100, 2, &work->hit_point);
            }
        }

        GV_DestroyActor(work);
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int InitTarget(Work *work, int side)
{
    SVECTOR scale;
    TARGET *trg;

    trg = &work->target;
    GM_SetTarget(trg, TARGET_POWER, side, &s19b_dword_800C33C0);

    scale.vx = work->step.vx >> 3;
    scale.vy = work->step.vy >> 3;
    scale.vz = work->step.vz >> 3;

    if (side == PLAYER_SIDE)
    {
        GM_Target_8002DCCC(trg, 3, 1, work->life, 0, &scale);
    }
    else
    {
        GM_Target_8002DCCC(trg, 3, 1, (work->life * 2) / 3, 0, &scale);
    }

    return 0;
}

static int GetResources(Work *work, MATRIX *world, int mode, int mode2, int side)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->hit_type = 0;
    work->map = GM_CurrentMap;
    work->world = *world;

    DG_SetPos(world);
    DG_PutVector(&s19b_dword_800C33D0, &work->pos, 1);

    s19b_dword_800C33C8.vy = -work->range_step;
    DG_RotVector(&s19b_dword_800C33C8, &work->step, 1);

    work->hit_dist = FindIntersection(work, world, mode2);
    work->range = 0;

    if (work->range_scale != 0)
    {
        work->range_step = (work->range_step * work->range_scale) >> 12;
    }

    if (mode == 0)
    {
        return 0;
    }

    if (mode >= 0)
    {
        if (mode < 3)
        {
            work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, work->vertices, NULL);
            if (prim == NULL)
            {
                return -1;
            }

            tex = DG_GetTexture(GV_StrCode("bullet"));
            if (tex == NULL)
            {
                return -1;
            }

            InitPacks(prim->packs[0], tex, mode);
            InitPacks(prim->packs[1], tex, mode);

            PushVertices(work);
        }
    }

    return 0;
}

void *NewJeepBullet(MATRIX *world, int side, int mode, int mode2)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "jbullet.c");

        vec.vx = world->m[0][0];
        vec.vy = world->m[1][0];
        vec.vz = world->m[2][0];

        work->range_scale = GV_VecLen3(&vec);
        work->size = 10;
        work->life = 64;

        if (mode2 == 2)
        {
            work->max_dist = 100000;
            work->range_step = 5000;
        }
        else
        {
            work->max_dist = 15000;
            work->range_step = 750;
        }

        work->hit_test = 1;

        if (GetResources(work, world, mode, mode2, side) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        if (InitTarget(work, side) < 0)
        {
            GV_DestroyActor(work);
        }

        work->spark_flag = 0x100;
        work->mode2 = mode2;
        work->mode = mode;
        work->side = side;
    }

    return work;
}

void *NewJeepBullet2(MATRIX *world, int side, int mode, int mode2)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "jbullet.c");

        vec.vx = world->m[0][0];
        vec.vy = world->m[1][0];
        vec.vz = world->m[2][0];

        work->range_scale = GV_VecLen3(&vec);
        work->size = 10;
        work->life = 64;

        if (mode2 == 2)
        {
            work->max_dist = 100000;
            work->range_step = 5000;
        }
        else
        {
            work->max_dist = 15000;
            work->range_step = 750;
        }

        work->hit_test = 0;

        if (GetResources(work, world, mode, mode2, side) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        if (InitTarget(work, side) < 0)
        {
            GV_DestroyActor(work);
        }

        work->spark_flag = 0x100;
        work->mode2 = mode2;
        work->mode = mode;
        work->side = side;
    }

    return work;
}
