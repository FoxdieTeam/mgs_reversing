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

#define EXEC_LEVEL  GV_ACTOR_LEVEL5

#define SEGMENT_ATR ( HZD_SEG_NO_PLAYER )

// TODO: This type of struct is seen in other places that make use of HZD_FLR.
typedef struct _BULLET_VECS
{
    SVECTOR vecs[4];
} BULLET_VECS;

typedef struct _Work
{
    GV_ACT      actor;
    int         map;
    MATRIX      field_24;
    TARGET      target;
    DG_PRIM    *prim;
    SVECTOR     field_90[8];
    BULLET_VECS field_D0[2];
    SVECTOR     field_110;
    SVECTOR     field_118;
    SVECTOR     field_120;
    SVECTOR     field_128;
    HZD_FLR    *floor;
    int         field_134;
    int         field_138;
    int         field_13C;
    int         field_140;
    int         noise_len;
    int         side;
    int         flags;
    int         field_150;
    int         damage;
    int         field_158;
    int         field_15C;
    int         field_160;
    int         field_164;
    int         field_168;
    int         field_16C;
} Work;

/*---------------------------------------------------------------------------*/

STATIC int dword_8009F6A8 = 0;

STATIC SVECTOR svec_8009F6AC[4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};
STATIC SVECTOR svec_8009F6CC = {0, 400, 0, 0};
STATIC VECTOR vec_8009F6D4 = {0, 0, 0, 0};
STATIC SVECTOR svec_8009F6E4 = {0, 55536, 0, 0};
STATIC SVECTOR svec_8009F6EC = {100, 100, 100, 0};
STATIC SVECTOR svec_8009F6F4 = {0, 0, 0, 0};
STATIC SVECTOR svec_8009F6FC = {0, 400, 0, 0};

/*---------------------------------------------------------------------------*/

static void bullet_80075314(SVECTOR *pVec, int amount)
{
    svec_8009F6AC[0].vx = amount;
    svec_8009F6AC[1].vx = -amount;
    svec_8009F6AC[2].vz = amount;
    svec_8009F6AC[3].vz = -amount;
    DG_PutVector(svec_8009F6AC, pVec, 4);
}

static void bullet_80075358(Work *work)
{
    BULLET_VECS *pVecs;
    int i;

    bullet_80075314(work->field_D0[0].vecs, work->field_150);

    pVecs = work->field_D0;
    for (i = 1; i > 0; i--)
    {
        pVecs[1] = pVecs[0];
        pVecs++;
    }
}

static void bullet_80075414(Work *work)
{
    BULLET_VECS *pVecs;
    int i;

    pVecs = &work->field_D0[1];
    for (i = 1; i > 0; i--)
    {
        if (work->field_134 != 2)
        {
            pVecs[0] = pVecs[-1];
        }

        pVecs--;
    }

    bullet_80075314(pVecs->vecs, work->field_150);
}

static void bullet_800754E4(Work *work)
{
    int i;
    SVECTOR *pDst;
    BULLET_VECS *pVecs;

    pVecs = work->field_D0;
    pDst = work->field_90;

    for (i = 1; i > 0; i--)
    {
        pDst[0] = pVecs[0].vecs[0];
        pDst[1] = pVecs[0].vecs[1];
        pDst[2] = pVecs[1].vecs[0];
        pDst[3] = pVecs[1].vecs[1];
        pDst[4] = pVecs[0].vecs[2];
        pDst[5] = pVecs[0].vecs[3];
        pDst[6] = pVecs[1].vecs[2];
        pDst[7] = pVecs[1].vecs[3];

        pDst += 8;
        pVecs++;
    }
}

static void InitPacks(POLY_FT4 *packs, DG_TEX *tex, int arg2)
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

            if (arg2 == 2)
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

static int bullet_8007575C(Work *work, MATRIX *pMtx, int noise_len)
{
    SVECTOR     svec1, svec2, svec3;
    VECTOR      vec1, vec2;
    SVECTOR     svec4;
    MAP *map;
    int         i;
    int         x, y, z;
    int         any_clamped, clamp_value;
    int         shift, divisor;
    int         f158_clamped, f158_iter;
    int         f168;

    DG_PutVector(&svec_8009F6CC, &svec3, 1);

    svec1 = svec3;
    vec_8009F6D4.vy = -work->field_158;

    ApplyRotMatrixLV(&vec_8009F6D4, &vec1);

    vec1.vx += svec3.vx;
    vec1.vy += svec3.vy;
    vec1.vz += svec3.vz;

    any_clamped = 0;

    if (work->field_158 > 0x7fff)
    {
        for (shift = 3, f158_iter = work->field_158 >> 15; !(f158_iter & 4); f158_iter <<= 1)
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
        work->field_158 = SquareRoot0(vec2.vx + vec2.vy + vec2.vz) << shift;
    }

    if (work->field_158 > 10000)
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
        f158_clamped = work->field_158;
    }

    work->field_118 = svec2;

    i = 0;
    map = GM_GetMap(work->map);

    while (1)
    {
        f168 = work->field_168;

        if (f168 == 1 && HZD_LineCheck(map->hzd, &svec1, &svec2, HZD_CHECK_ALL, SEGMENT_ATR))
        {
            HZD_LineNearVec(&work->field_118);
            work->floor = HZD_LineNearSurface();
            work->field_16C = HZD_LineNearFlag();

            if ((unsigned int)work->floor & 0x80000000) // Wall
            {
                work->field_164 = f168;
                HZD_SurfaceNormal(work->floor, &work->field_128);
            }
            else // Floor
            {
                work->field_164 = 2;
                work->field_128.vx = work->floor->p1.h * 16;
                work->field_128.vz = work->floor->p2.h * 16;
                work->field_128.vy = work->floor->p3.h * 16;
            }

            work->field_140 = 1;

            vec2.vx = (work->field_118.vx - svec3.vx) >> 1;
            vec2.vy = (work->field_118.vy - svec3.vy) >> 1;
            vec2.vz = (work->field_118.vz - svec3.vz) >> 1;

            Square0(&vec2, &vec2);
            return SquareRoot0(vec2.vx + vec2.vy + vec2.vz) * 2;
        }

        i += f158_clamped;

        if (i >= work->field_158)
        {
            return work->field_158;
        }

        svec1 = svec2;

        if (i + f158_clamped >= work->field_158)
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
    MATRIX mtx;
    SVECTOR vec;
    int sound;
    MAP *map;

    sound = 0;
    GM_SetCurrentMap(work->map);

    map = GM_GetMap(work->map);
    work->field_13C += work->field_15C;

    if (work->field_138 < work->field_13C)
    {
        vec = work->field_118;
    }
    else
    {
        GV_AddVec3(&work->field_110, &work->field_120, &vec);
    }

    if (GM_Target_8002E1B8(&work->field_110, &vec, map->index, &vec, work->side))
    {
        GM_MoveTarget(&work->target, &vec);
        GM_PowerTarget(&work->target);
        GV_DestroyActor(&work->actor);
        return;
    }

    work->field_110 = vec;

    if (work->field_134 != 0)
    {
        work->field_24.t[0] = work->field_110.vx;
        work->field_24.t[1] = work->field_110.vy;
        work->field_24.t[2] = work->field_110.vz;

        DG_SetPos(&work->field_24);

        bullet_80075414(work);
        bullet_800754E4(work);
    }

    if (work->field_13C <= work->field_138)
    {
        return;
    }

    if ((work->field_140 == 1) && ((work->field_164 != work->field_140) || !(work->field_16C & 0x20)))
    {
        if ((GM_GameStatus & GAME_FLAG_BIT_09) && (work->field_164 == 2))
        {
            NewAnime_8005E508(&work->field_118);
        }
        else
        {
            work->field_24.t[0] = work->field_118.vx;
            work->field_24.t[1] = work->field_118.vy;
            work->field_24.t[2] = work->field_118.vz;

            mtx = work->field_24;
            DG_ReflectMatrix(&work->field_128, &mtx, &mtx);

            if (work->flags & 0x200)
            {
                NewSpark(&mtx, 1);
            }
            else if (work->flags & 0x100)
            {
                NewSpark(&mtx, 0);
            }
        }

        if ((work->flags & 0x400) && !(dword_8009F6A8 & 1))
        {
            NewAnime_8005E508(&work->field_118);
        }

        switch (work->field_164)
        {
        case 1:
            sound = GM_GetNoiseSound(work->field_16C, 1);
            break;

        case 2:
            sound = GM_GetNoiseSound(work->floor->b1.h >> 8, 2);
            break;
        }

        if (sound != 0)
        {
            if (GM_CurrentWeaponId == WP_Rifle)
            {
                GM_SeSet2(0, 63, sound);
            }
            else
            {
                GM_SeSet(&work->field_118, sound);
            }
        }

        if (work->noise_len == 2)
        {
            GM_SetNoise(100, work->noise_len, &work->field_118);
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
    SVECTOR pos;

    GM_SetTarget( &work->target, TARGET_POWER, side, &svec_8009F6EC );

    pos.vx = work->field_120.vx >> 3; // divide 8 won't match
    pos.vy = work->field_120.vy >> 3;
    pos.vz = work->field_120.vz >> 3;

    if ( work->flags & 0x800 )
    {
        GM_Target_8002DCCC( &work->target, 0, 2, work->damage, 0, &pos );
    }
    else
    {
        GM_Target_8002DCCC( &work->target, 0, 1, work->damage, 0, &pos );
    }

    return 0;
}

static int GetResources(Work *work, MATRIX* pMtx, int arg2, int noise_len, int side)
{
    DG_PRIM *pPrim;
    DG_TEX *pTex;
    int test;

    work->field_164 = 0;
    work->map = GM_CurrentMap;
    work->field_24 = *pMtx;

    DG_SetPos(pMtx);
    DG_PutVector(&svec_8009F6FC, &work->field_110, 1);

    svec_8009F6F4.vy = -work->field_15C;
    DG_RotVector(&svec_8009F6F4, &work->field_120, 1);

    work->field_138 = bullet_8007575C(work, pMtx, noise_len);
    work->field_13C = 0;

    if (work->field_160 != 0)
    {
        work->field_138 = (work->field_138 * work->field_160) >> 12;
    }

    if (arg2 == 0)
    {
        return 0;
    }

    test = arg2 <= 2;
    if ((arg2 >= 0) && test)
    {
        pPrim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, work->field_90, NULL);
        work->prim = pPrim;

        if (!pPrim)
        {
            return -1;
        }

        pTex = DG_GetTexture(GV_StrCode("bullet"));

        if (!pTex)
        {
            return -1;
        }

        InitPacks(pPrim->packs[0], pTex, arg2);
        InitPacks(pPrim->packs[1], pTex, arg2);
        bullet_80075358(work);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBulletEnemy(MATRIX *pMtx, int side, int arg2, int noise_len, int arg4)
{
    Work    *work;
    SVECTOR  vec;

    work = GV_NewActor( EXEC_LEVEL, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &work->actor, Act, Die, "bullet.c" );
        vec.vx = pMtx->m[0][0];
        vec.vy = pMtx->m[1][0];
        vec.vz = pMtx->m[2][0];
        work->field_160 = GV_VecLen3( &vec );
        work->field_150 = 10;
        work->damage = 64;

        if ( noise_len == 2 )
        {
            work->field_158 = 100000;
            work->field_15C = 5000;
        }
        else if ( noise_len == 1 )
        {
            work->field_158 = 10000;
            work->field_15C = 5000;
        }
        else
        {
            work->field_158 = 10000;
            work->field_15C = 750;
        }

        work->field_168 = arg4;

        if ( GetResources( work, pMtx, arg2, noise_len, side ) < 0 )
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }

        if ( SetTarget( work, side ) < 0 )
        {
            GV_DestroyActor( &work->actor );
        }

        work->flags = 0x100;
        work->noise_len = noise_len;
        work->field_134 = arg2;
        work->side = side;
    }
    return (void *)work;
}

void *NewBullet(MATRIX *pMtx, int side, int a3, int noise_len)
{
    SVECTOR vec;
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if ( work )
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bullet.c");
        vec.vx = pMtx->m[0][0];
        vec.vy = pMtx->m[1][0];
        vec.vz = pMtx->m[2][0];
        work->field_160 = GV_VecLen3(&vec);
        work->field_150 = 10;

        if ( side == PLAYER_SIDE )
        {
            if ( GM_CurrentWeaponId == WP_Rifle )
            {
                work->damage = 256;
            }
            else
            {
                work->damage = 64;
            }
        }
        else
        {
            work->damage = 64;
        }

        if ( noise_len == 2 )
        {
            work->field_158 = 100000;
            work->field_15C = 5000;
        }
        else if ( noise_len == 1 )
        {
            work->field_158 = 10000;
            work->field_15C = 5000;
        }
        else
        {
            work->field_158 = 10000;
            work->field_15C = 750;
        }

        work->field_168 = 1;

        if ( GetResources(work, pMtx, a3, noise_len, side) < 0 )
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        if ( SetTarget(work, side) < 0 )
        {
            GV_DestroyActor(&work->actor);
        }

        work->flags = 0x100;
        work->noise_len = noise_len;
        work->field_134 = a3;
        work->side = side;
    }

    return (void *)work;
}

void *NewBulletEx(int flag, MATRIX* pMtx, int side, int a4, int noise_len, int a6, int damage, int a8, int a9)
{
    Work* work; // $s0
    int flags; // $v1
    SVECTOR vec; // [sp+18h] [-28h] BYREF
    MATRIX mtx; // [sp+20h] [-20h] BYREF

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (!work)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "bullet.c");
    work->flags = flag;
    work->field_150 = a6 / 2;
    work->damage = damage;
    work->field_158 = a8;
    work->field_15C = a9;
    DG_SetPos(pMtx);
    vec.vx = -1024;
    vec.vy = 0;
    vec.vz = 0;
    DG_RotatePos(&vec);
    ReadRotMatrix(&mtx);

    if ((work->flags & 0x1000) != 0)
    {
        work->field_168 = 0;
    }
    else
    {
        work->field_168 = 1;
    }

    if (GetResources(work, &mtx, a4, noise_len, side) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }
    else
    {
        if (SetTarget(work, side) < 0)
        {
            GV_DestroyActor(&work->actor);
        }
        flags = work->flags;
        work->noise_len = noise_len;
        work->field_134 = a4;
        work->side = side;
        if ((flags & 1) != 0)
        {
            NewAnime_8005D604(pMtx); // ??
        }
        else if ((flags & 2) != 0)
        {
            NewAnime_8005D6BC(pMtx, 0);
        }
        else if ((flags & 4) != 0)
        {
            NewAnime_8005D6BC(pMtx, 1);
        }
        else if ((flags & 8) != 0)
        {
            NewAnime_8005D988(pMtx, pMtx, 0);
        }
        else if ((flags & 0x10) != 0)
        {
            NewAnime_8005D988(pMtx, pMtx, 1);
        }
        else if ((flags & 0x20) != 0)
        {
            NewAnime_8005E334(pMtx);
        }

        ++dword_8009F6A8;
        return (void *)work;
    }

    return NULL;
}

void *NewBullet2(MATRIX *pMtx, int side, int a3, int noise_len, int a5, int damage, int a7, int a8)
{
    SVECTOR vec;
    MATRIX mtx;

    DG_SetPos(pMtx);
    vec.vx = 1024;
    vec.vy = 0;
    vec.vz = 0;
    DG_RotatePos(&vec);
    ReadRotMatrix(&mtx);
    return NewBulletEx(0x100, &mtx, side, a3, noise_len, a5, damage, a7, a8);
}
