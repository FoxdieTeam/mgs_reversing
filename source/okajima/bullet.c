#include "bullet.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "linkvar.h"
#include "anime/animconv/anime.h"

#include "okajima/spark.h"      // for NewSpark

/*---------------------------------------------------------------------------*/

#define SEGMENT_ATR ( HZD_SEG_NO_PLAYER )

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    MATRIX   world;
    TARGET   target;
    DG_PRIM *prim;
    SVECTOR  verts[8];
    SVECTOR  trail[8];
    SVECTOR  pos;
    SVECTOR  hitpos;
    SVECTOR  step;
    SVECTOR  normal;
    HZD_FLR *seg;
    int      color; // 0 = invisible, 1 = visible, 2 = red
    int      hit_dist;
    int      dist;
    int      hit;
    int      type;
    int      side;
    int      flag;
    int      size;
    int      damage;
    int      length;
    int      speed;
    int      scale;
    int      seg_flag;
    int      hittest;
    int      seg_atr;
} Work;

/*---------------------------------------------------------------------------*/

static int bullet_count = 0;

static SVECTOR bullet_trail[4] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

static SVECTOR svec_8009F6CC = {0, 400, 0};
static VECTOR  vec_8009F6D4 = {0, 0, 0};
static SVECTOR svec_8009F6E4 = {0, 55536, 0};
static SVECTOR target_size = {100, 100, 100};
static SVECTOR bullet_step = {0, 0, 0};
static SVECTOR bullet_pos = {0, 400, 0};

/*---------------------------------------------------------------------------*/

static void PutTrail(SVECTOR *verts, int size)
{
    bullet_trail[0].vx = size;
    bullet_trail[1].vx = -size;
    bullet_trail[2].vz = size;
    bullet_trail[3].vz = -size;
    DG_PutVector(bullet_trail, verts, 4);
}

static void InitTrail(Work *work)
{
    SVECTOR *verts;
    int      i;

    PutTrail(work->trail, work->size);

    verts = work->trail;
    for (i = 1; i > 0; i--)
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
    for (i = 1; i > 0; i--)
    {
        if (work->color != 2)
        {
            memcpy(verts, verts - 4, sizeof(SVECTOR) * 4);
        }
        verts -= 4;
    }

    PutTrail(verts, work->size);
}

static void CopyTrail(Work *work)
{
    SVECTOR *src;
    SVECTOR *dst;
    int      i;

    src = work->trail;
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

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex, int color)
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

            if (color == 2)
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
            h = tex->h + 1;
            packs->v0 = packs->v1 = y + h * i;
            packs->v2 = packs->v3 = y + (h * (i + 1)) - 1;

            packs->tpage = tex->tpage;
            packs->clut = tex->clut;
            packs->tpage |= 0x60;
            packs++;
        }
    }
}

static int CalculateHit(Work *work, MATRIX *world, int type)
{
    SVECTOR svec1, svec2, svec3;
    VECTOR  vec1, vec2;
    SVECTOR svec4;
    MAP    *map;
    int     i;
    int     x, y, z;
    int     any_clamped, clamp_value;
    int     shift, divisor;
    int     f158_clamped, f158_iter;

    DG_PutVector(&svec_8009F6CC, &svec3, 1);

    svec1 = svec3;
    vec_8009F6D4.vy = -work->length;

    ApplyRotMatrixLV(&vec_8009F6D4, &vec1);

    vec1.vx += svec3.vx;
    vec1.vy += svec3.vy;
    vec1.vz += svec3.vz;

    any_clamped = 0;

    if (work->length > 0x7fff)
    {
        for (shift = 3, f158_iter = work->length >> 15; !(f158_iter & 4); f158_iter <<= 1)
        {
            shift -= 1;
        }
    }
    else
    {
        shift = 0;
    }
    x = vec1.vx;

    if (x < -0x8000)
    {
        clamp_value = -0x8000;
        vec1.vx = clamp_value;
    }

    else if (x > 0x7fff)
    {
        clamp_value = 0x7fff;
        vec1.vx = clamp_value;
    }

    else
    {
        goto skip_clamp_x;
    }

    clamp_value = (clamp_value - svec3.vx) >> shift;
    divisor = (x - svec3.vx) >> shift;

    vec1.vy = (((vec1.vy - svec3.vy) * clamp_value) / divisor) + svec3.vy;
    vec1.vz = (((vec1.vz - svec3.vz) * clamp_value) / divisor) + svec3.vz;

    any_clamped = 1;

skip_clamp_x:
    y = vec1.vy;

    if (y < -0x8000)
    {
        clamp_value = -0x8000;
        vec1.vy = clamp_value;
    }
    else if (y > 0x7fff)
    {
        clamp_value = 0x7fff;
        vec1.vy = clamp_value;
    }
    else
    {
        goto skip_clamp_y;
    }

    clamp_value = (clamp_value - svec3.vy) >> shift;
    divisor = (y - svec3.vy) >> shift;

    vec1.vx = (((vec1.vx - svec3.vx) * clamp_value) / divisor) + svec3.vx;
    vec1.vz = (((vec1.vz - svec3.vz) * clamp_value) / divisor) + svec3.vz;

    any_clamped = 1;

skip_clamp_y:
    z = vec1.vz;

    if (z < -0x8000)
    {
        clamp_value = -0x8000;
        vec1.vz = clamp_value;
    }
    else if (z > 0x7fff)
    {
        clamp_value = 0x7fff;
        vec1.vz = clamp_value;
    }
    else
    {
        goto skip_clamp_z;
    }

    clamp_value = (clamp_value - svec3.vz) >> shift;
    divisor = (z - svec3.vz) >> shift;

    vec1.vy = (((vec1.vy - svec3.vy) * clamp_value) / divisor) + svec3.vy;
    vec1.vx = (((vec1.vx - svec3.vx) * clamp_value) / divisor) + svec3.vx;

    any_clamped = 1;

skip_clamp_z:
    if (any_clamped)
    {
        vec2.vx = (vec1.vx - svec3.vx) >> shift;
        vec2.vy = (vec1.vy - svec3.vy) >> shift;
        vec2.vz = (vec1.vz - svec3.vz) >> shift;

        Square0(&vec2, &vec2);
        work->length = SquareRoot0(vec2.vx + vec2.vy + vec2.vz) << shift;
    }

    if (work->length > 10000)
    {
        ApplyRotMatrix(&svec_8009F6E4, &vec2);
        svec4.vx = vec2.vx;
        svec4.vy = vec2.vy;
        svec4.vz = vec2.vz;
        GV_AddVec3(&svec3, &svec4, &svec2);
        f158_clamped = 10000;
    }
    else
    {
        svec2.vx = vec1.vx;
        svec2.vy = vec1.vy;
        svec2.vz = vec1.vz;
        f158_clamped = work->length;
    }

    work->hitpos = svec2;

    i = 0;
    map = GM_GetMap(work->map);

    while (1)
    {
        if (work->hittest == 1 && HZD_OnlineHazardCheck(map->hzd, &svec1, &svec2, HZD_CHK_ALL, SEGMENT_ATR))
        {
            HZD_GetOnlinePoint(&work->hitpos);
            work->seg = HZD_GetOnlineHazard();
            work->seg_atr = HZD_GetOnlineHazardAtr();

            if ((unsigned int)work->seg & 0x80000000) // Wall
            {
                work->seg_flag = 1;
                HZD_GetNormal(work->seg, &work->normal);
            }
            else // seg
            {
                work->seg_flag = 2;
                work->normal.vx = work->seg->p1.h * 16;
                work->normal.vz = work->seg->p2.h * 16;
                work->normal.vy = work->seg->p3.h * 16;
            }

            work->hit = 1;

            vec2.vx = (work->hitpos.vx - svec3.vx) >> 1;
            vec2.vy = (work->hitpos.vy - svec3.vy) >> 1;
            vec2.vz = (work->hitpos.vz - svec3.vz) >> 1;

            Square0(&vec2, &vec2);
            return SquareRoot0(vec2.vx + vec2.vy + vec2.vz) * 2;
        }

        i += f158_clamped;

        if (i >= work->length)
        {
            return work->length;
        }

        svec1 = svec2;

        if (i + f158_clamped >= work->length)
        {
            svec2.vx = vec1.vx;
            svec2.vy = vec1.vy;
            svec2.vz = vec1.vz;
        }
        else
        {
            svec2.vx += svec4.vx;
            svec2.vy += svec4.vy;
            svec2.vz += svec4.vz;
        }
    }
}

static void Act(Work *work)
{
    MATRIX world;
    SVECTOR vec;
    int sound;
    MAP *map;

    sound = 0;
    GM_SetCurrentMap(work->map);

    map = GM_GetMap(work->map);
    work->dist += work->speed;

    if (work->hit_dist < work->dist)
    {
        vec = work->hitpos;
    }
    else
    {
        GV_AddVec3(&work->pos, &work->step, &vec);
    }

    if (GM_OnlineTargetCheck(&work->pos, &vec, map->index, &vec, work->side))
    {
        GM_MoveTarget(&work->target, &vec);
        GM_PowerTarget(&work->target);
        GV_DestroyActor(&work->actor);
        return;
    }

    work->pos = vec;

    if (work->color != 0)
    {
        work->world.t[0] = work->pos.vx;
        work->world.t[1] = work->pos.vy;
        work->world.t[2] = work->pos.vz;

        DG_SetPos(&work->world);

        UpdateTrail(work);
        CopyTrail(work);
    }

    if (work->dist <= work->hit_dist)
    {
        return;
    }

    if ((work->hit == 1) && ((work->seg_flag != 1) || !(work->seg_atr & HZD_SEG_NO_BULLET)))
    {
        if ((GM_GameStatus & GAME_FLAG_BIT_09) && (work->seg_flag == 2))
        {
            AN_RecoilSmoke(&work->hitpos);
        }
        else
        {
            work->world.t[0] = work->hitpos.vx;
            work->world.t[1] = work->hitpos.vy;
            work->world.t[2] = work->hitpos.vz;

            world = work->world;
            DG_ReflectMatrix(&work->normal, &world, &world);

            if (work->flag & BULLET_RECOILHEAVYSPARK)
            {
                NewSpark(&world, 1);
            }
            else if (work->flag & BULLET_RECOILSPARK)
            {
                NewSpark(&world, 0);
            }
        }

        if ((work->flag & BULLET_RECOILSMOKE) && !(bullet_count & 1))
        {
            AN_RecoilSmoke(&work->hitpos);
        }

        switch (work->seg_flag)
        {
        case 1:
            sound = GM_GetNoiseSound(work->seg_atr, 1);
            break;

        case 2:
            sound = GM_GetNoiseSound(work->seg->b1.h >> 8, 2);
            break;
        }

        if (sound != 0)
        {
            if (GM_Weapon == WP_Rifle)
            {
                GM_SeSet2(0, 63, sound);
            }
            else
            {
                GM_SeSet(&work->hitpos, sound);
            }
        }

        if (work->type == 2)
        {
            GM_SetNoise(100, work->type, &work->hitpos);
        }
    }

    GV_DestroyActor(&work->actor);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int SetTarget( Work *work, int side )
{
    SVECTOR force;

    GM_SetTarget( &work->target, TARGET_POWER, side, &target_size );

    force.vx = work->step.vx >> 3;
    force.vy = work->step.vy >> 3;
    force.vz = work->step.vz >> 3;

    if ( work->flag & BULLET_BLAST )
    {
        GM_SetPowerTarget( &work->target, POWER_ONCE, 2, work->damage, 0, &force );
    }
    else
    {
        GM_SetPowerTarget( &work->target, POWER_ONCE, 1, work->damage, 0, &force );
    }

    return 0;
}

static int GetResources(Work *work, MATRIX *world, int color, int type, int side)
{
    DG_PRIM *prim;
    DG_TEX  *tex;
    int      valid;

    work->seg_flag = 0;
    work->map = GM_CurrentMap;
    work->world = *world;

    DG_SetPos(world);
    DG_PutVector(&bullet_pos, &work->pos, 1);

    bullet_step.vy = -work->speed;
    DG_RotVector(&bullet_step, &work->step, 1);

    work->hit_dist = CalculateHit(work, world, type);
    work->dist = 0;

    if (work->scale != 0)
    {
        work->hit_dist = (work->hit_dist * work->scale) >> 12;
    }

    if (color == 0)
    {
        return 0;
    }

    /* TODO: Fix */
    valid = color <= 2;
    if ((color >= 0) && valid)
    {
        work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, work->verts, NULL);
        if (!prim)
        {
            return -1;
        }

        tex = DG_GetTexture(GV_StrCode("bullet"));
        if (!tex)
        {
            return -1;
        }

        InitPacks(prim->packs[0], tex, color);
        InitPacks(prim->packs[1], tex, color);
        InitTrail(work);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBulletEnemy(MATRIX *world, int side, int color, int type, int hittest)
{
    Work    *work;
    SVECTOR  vec;

    work = GV_NewActor( GV_ACTOR_USER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &work->actor, Act, Die, "bullet.c" );
        vec.vx = world->m[0][0];
        vec.vy = world->m[1][0];
        vec.vz = world->m[2][0];
        work->scale = GV_VecLen3( &vec );
        work->size = 10;
        work->damage = 64;

        if ( type == 2 )
        {
            work->length = 100000;
            work->speed = 5000;
        }
        else if ( type == 1 )
        {
            work->length = 10000;
            work->speed = 5000;
        }
        else
        {
            work->length = 10000;
            work->speed = 750;
        }

        work->hittest = hittest;

        if ( GetResources( work, world, color, type, side ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }

        if ( SetTarget( work, side ) < 0 )
        {
            GV_DestroyActor( &work->actor );
        }

        work->flag = BULLET_RECOILSPARK;
        work->type = type;
        work->color = color;
        work->side = side;
    }
    return (void *)work;
}

void *NewBullet(MATRIX *world, int side, int color, int type)
{
    SVECTOR vec;
    Work   *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if ( work )
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bullet.c");

        setVector(&vec, world->m[0][0], world->m[1][0], world->m[2][0]);
        work->scale = GV_VecLen3(&vec);
        work->size = 10;

        if ( ( side == PLAYER_SIDE ) && ( GM_Weapon == WP_Rifle ) )
        {
            work->damage = 256;
        }
        else
        {
            work->damage = 64;
        }

        if ( type == 2 )
        {
            work->length = 100000;
            work->speed = 5000;
        }
        else if ( type == 1 )
        {
            work->length = 10000;
            work->speed = 5000;
        }
        else
        {
            work->length = 10000;
            work->speed = 750;
        }

        work->hittest = 1;

        if ( GetResources(work, world, color, type, side) < 0 )
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        if ( SetTarget(work, side) < 0 )
        {
            GV_DestroyActor(&work->actor);
        }

        work->flag = BULLET_RECOILSPARK;
        work->type = type;
        work->color = color;
        work->side = side;
    }
    return (void *)work;
}

void *NewBulletEx(int flag, MATRIX *world, int side, int color, int type, int size, int damage, int length, int speed)
{
    SVECTOR vec;
    MATRIX  mat;
    Work   *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (!work)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "bullet.c");

    work->flag = flag;
    work->size = size / 2;
    work->damage = damage;
    work->length = length;
    work->speed = speed;

    DG_SetPos(world);
    setVector(&vec, -1024, 0, 0);
    DG_RotatePos(&vec);
    ReadRotMatrix(&mat);

    if (work->flag & BULLET_NO_HZD)
    {
        work->hittest = 0;
    }
    else
    {
        work->hittest = 1;
    }

    if (GetResources(work, &mat, color, type, side) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    if (SetTarget(work, side) < 0)
    {
        GV_DestroyActor(&work->actor);
    }

    work->type = type;
    work->color = color;
    work->side = side;

    if (work->flag & BULLET_FLASH)
    {
        AN_FamasFlash(world);
    }
    else if (work->flag & BULLET_SMOKE0)
    {
        AN_BulletSmoke(world, 0);
    }
    else if (work->flag & BULLET_SMOKE1)
    {
        AN_BulletSmoke(world, 1);
    }
    else if (work->flag & BULLET_FLASHSOCOM0)
    {
        AN_SocomFlash(world, world, 0);
    }
    else if (work->flag & BULLET_FLASHSOCOM1)
    {
        AN_SocomFlash(world, world, 1);
    }
    else if (work->flag & BULLET_FLASHHEAVY)
    {
        AN_HeavyFlash(world);
    }

    bullet_count++;
    return (void *)work;
}

void *NewBullet2(MATRIX *world, int side, int color, int type, int size, int damage, int length, int speed)
{
    SVECTOR vec;
    MATRIX  mat;

    DG_SetPos(world);
    setVector(&vec, 1024, 0, 0);
    DG_RotatePos(&vec);
    ReadRotMatrix(&mat);
    return NewBulletEx(BULLET_RECOILSPARK, &mat, side, color, type, size, damage, length, speed);
}
