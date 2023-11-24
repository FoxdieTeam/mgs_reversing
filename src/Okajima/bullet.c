#include "bullet.h"
#include "linker.h"
#include "spark.h"
#include "libdg/libdg.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "psyq.h"
#include "Anime/animeconv/anime.h"
#include "unknown.h"

extern int GM_CurrentMap_800AB9B0;
extern int GM_GameStatus_800AB3CC;

//------------------------------------------------------------------------------

int dword_8009F6A8 = 0;

SVECTOR svec_8009F6AC[4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
SVECTOR svec_8009F6CC = {0, 400, 0, 0};
VECTOR vec_8009F6D4 = {0, 0, 0, 0};
SVECTOR svec_8009F6E4 = {0, 55536, 0, 0};
SVECTOR svec_8009F6EC = {100, 100, 100, 0};
SVECTOR svec_8009F6F4 = {0, 0, 0, 0};
SVECTOR svec_8009F6FC = {0, 400, 0, 0};

//------------------------------------------------------------------------------

void bullet_80075314(SVECTOR *pVec, int amount)
{
    svec_8009F6AC[0].vx = amount;
    svec_8009F6AC[1].vx = -amount;
    svec_8009F6AC[2].vz = amount;
    svec_8009F6AC[3].vz = -amount;
    DG_PutVector_8001BE48(svec_8009F6AC, pVec, 4);
}

void bullet_loader2_helper_80075358(BulletWork *work)
{
    Bullet_vecs *pVecs;
    int i;

    bullet_80075314(work->field_D0[0].vecs, work->field_150);

    pVecs = work->field_D0;
    for (i = 1; i > 0; i--)
    {
        pVecs[1] = pVecs[0];
        pVecs++;
    }
}

void bullet_act_helper_80075414(BulletWork *work)
{
    Bullet_vecs *pVecs;
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

void bullet_act_helper_800754E4(BulletWork *work)
{
    int i;
    SVECTOR *pDst;
    Bullet_vecs *pVecs;

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

void bullet_loader2_helper_80075610(POLY_FT4 *pPoly, DG_TEX *pTex, int arg2)
{
    int i, j;
    int r, gb;
    int x, y, w, h;

    for (i = 0; i < 1; i++)
    {
        for (j = 2; j > 0; j--)
        {
            setPolyFT4(pPoly);
            setSemiTrans(pPoly, 1);

            if (arg2 == 2)
            {
                r = 255;
                gb = 85;
            }
            else
            {
                r = GV_RandU_80017090(128) - 32;
                gb = (r / 3) * 2;
            }

            setRGB0(pPoly, r, gb, gb);

            x = pTex->field_8_offx;
            w = pTex->field_A_width;
            pPoly->u0 = pPoly->u2 = x;
            pPoly->u1 = pPoly->u3 = w + x;

            y = pTex->field_9_offy;
            h = pTex->field_B_height + 1;
            pPoly->v0 = pPoly->v1 = y + h * i;
            pPoly->v2 = pPoly->v3 = y + (h * (i + 1)) - 1;

            pPoly->tpage = pTex->field_4_tPage;
            pPoly->clut = pTex->field_6_clut;
            pPoly->tpage |= 0x60;
            pPoly++;
        }
    }
}

int bullet_loader3_8007575C(BulletWork *work, MATRIX *pMtx, int noiseLen)
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

    DG_PutVector_8001BE48(&svec_8009F6CC, &svec3, 1);

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
        GV_AddVec3_80016D00(&svec3, &svec4, &svec2);
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
    map = Map_FromId_800314C0(work->field_20);

    while (1)
    {
        f168 = work->field_168;

        if (f168 == 1 && sub_80028454(map->field_8_hzd, &svec1, &svec2, 15, 4))
        {
            sub_80028890(&work->field_118);
            work->field_130 = (Bullet_0x130 *)sub_80028820();
            work->field_16C = sub_80028830();

            if ((unsigned int)work->field_130 & 0x80000000) // pointer tagging
            {
                work->field_164 = f168;
                sub_800272E0((SVECTOR *)work->field_130, &work->field_128);
            }
            else
            {
                work->field_164 = 2;
                work->field_128.vx = work->field_130[2].field_6 * 16;
                work->field_128.vz = work->field_130[3].field_6 * 16;
                work->field_128.vy = work->field_130[4].field_6 * 16;
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

void bullet_act_80075DD4(BulletWork *work)
{
    MATRIX mtx;
    SVECTOR vec;
    int sound;
    MAP *pMapRecord;

    sound = 0;
    GM_SetCurrentMap(work->field_20);

    pMapRecord = Map_FromId_800314C0(work->field_20);
    work->field_13C += work->field_15C;

    if (work->field_138 < work->field_13C)
    {
        vec = work->field_118;
    }
    else
    {
        GV_AddVec3_80016D00(&work->field_110, &work->field_120, &vec);
    }

    if (GM_Target_8002E1B8(&work->field_110, &vec, pMapRecord->field_0_map_index_bit, &vec, work->field_148_side))
    {
        GM_Target_SetVector_8002D500(&work->field_44_target, &vec);
        sub_8002D7DC(&work->field_44_target);
        GV_DestroyActor_800151C8(&work->field_0_actor);
        return;
    }

    work->field_110 = vec;

    if (work->field_134 != 0)
    {
        work->field_24.t[0] = work->field_110.vx;
        work->field_24.t[1] = work->field_110.vy;
        work->field_24.t[2] = work->field_110.vz;

        DG_SetPos_8001BC44(&work->field_24);

        bullet_act_helper_80075414(work);
        bullet_act_helper_800754E4(work);
    }

    if (work->field_13C <= work->field_138)
    {
        return;
    }

    if ((work->field_140 == 1) && ((work->field_164 != work->field_140) || !(work->field_16C & 0x20)))
    {
        if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_09) && (work->field_164 == 2))
        {
            anime_create_8005E508(&work->field_118);
        }
        else
        {
            work->field_24.t[0] = work->field_118.vx;
            work->field_24.t[1] = work->field_118.vy;
            work->field_24.t[2] = work->field_118.vz;

            mtx = work->field_24;
            DG_ReflectMatrix_8001EDCC(&work->field_128, &mtx, &mtx);

            if (work->field_14C & 0x200)
            {
                NewSpark_80074564(&mtx, 1);
            }
            else if (work->field_14C & 0x100)
            {
                NewSpark_80074564(&mtx, 0);
            }
        }

        if ((work->field_14C & 0x400) && !(dword_8009F6A8 & 1))
        {
            anime_create_8005E508(&work->field_118);
        }

        switch (work->field_164)
        {
        case 1:
            sound = GM_GetNoiseSound_8002E614(work->field_16C, 1);
            break;

        case 2:
            sound = GM_GetNoiseSound_8002E614(work->field_130->field_6 >> 8, 2);
            break;
        }

        if (sound != 0)
        {
            if (GM_CurrentWeaponId == WEAPON_PSG1)
            {
                GM_SeSet2_80032968(0, 63, sound);
            }
            else
            {
                GM_SeSet_80032858(&work->field_118, sound);
            }
        }

        if (work->field_144_noise_len == 2)
        {
            GM_SetNoise(100, work->field_144_noise_len, &work->field_118);
        }
    }

    GV_DestroyActor_800151C8(&work->field_0_actor);
}

void bullet_kill_80076164(BulletWork *work)
{
    DG_PRIM *prim;

    prim = work->field_8C_pPrim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int bullet_SetTarget_800761A0( BulletWork *actor, int target_flags )
{
    SVECTOR pos;

    GM_SetTarget_8002DC74( &actor->field_44_target, 4, target_flags, &svec_8009F6EC );

    pos.vx = actor->field_120.vx >> 3; // divide 8 won't match
    pos.vy = actor->field_120.vy >> 3;
    pos.vz = actor->field_120.vz >> 3;

    if ( actor->field_14C & 0x800 )
    {
        GM_Target_8002DCCC( &actor->field_44_target, 0, 2, actor->field_154_hp, 0, &pos );
    }
    else
    {
        GM_Target_8002DCCC( &actor->field_44_target, 0, 1, actor->field_154_hp, 0, &pos );
    }

    return 0;
}

int bullet_loader2_80076274(BulletWork *work, MATRIX* pMtx, int arg2, int noiseLen, int whichSide)
{
    DG_PRIM *pPrim;
    DG_TEX *pTex;
    int test;

    work->field_164 = 0;
    work->field_20 = GM_CurrentMap_800AB9B0;
    work->field_24 = *pMtx;

    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&svec_8009F6FC, &work->field_110, 1);

    svec_8009F6F4.vy = -work->field_15C;
    DG_RotVector_8001BE98(&svec_8009F6F4, &work->field_120, 1);

    work->field_138 = bullet_loader3_8007575C(work, pMtx, noiseLen);
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
        pPrim = DG_GetPrim(18, 2, 0, work->field_90, NULL);
        work->field_8C_pPrim = pPrim;

        if (!pPrim)
        {
            return -1;
        }

        pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("bullet"));

        if (!pTex)
        {
            return -1;
        }

        bullet_loader2_helper_80075610(&pPrim->field_40_pBuffers[0]->poly_ft4, pTex, arg2);
        bullet_loader2_helper_80075610(&pPrim->field_40_pBuffers[1]->poly_ft4, pTex, arg2);
        bullet_loader2_helper_80075358(work);
    }

    return 0;
}

BulletWork * NewBulletEnemy_80076420(MATRIX *arg0, int whichSide, int arg2, int arg3, int arg4)
{
    BulletWork  *actor;
    SVECTOR       vec;

    actor = (BulletWork *)GV_NewActor_800150E4( 5, sizeof(BulletWork) );
    if ( actor != NULL )
    {
        GV_SetNamedActor_8001514C( (GV_ACT *)actor,
                                   (TActorFunction)&bullet_act_80075DD4,
                                   (TActorFunction)&bullet_kill_80076164,
                                   "bullet.c" );
        vec.vx = arg0->m[0][0];
        vec.vy = arg0->m[1][0];
        vec.vz = arg0->m[2][0];
        actor->field_160 = GV_VecLen3_80016D80( &vec );
        actor->field_150 = 10;
        actor->field_154_hp = 64;

        if ( arg3 == 2 )
        {
            actor->field_158 = 100000;
            actor->field_15C = 5000;
        }
        else if ( arg3 == 1 )
        {
            actor->field_158 = 10000;
            actor->field_15C = 5000;
        }
        else
        {
            actor->field_158 = 10000;
            actor->field_15C = 750;
        }

        actor->field_168 = arg4;

        if ( bullet_loader2_80076274( actor, arg0, arg2, arg3, whichSide ) < 0 )
        {
            GV_DestroyActor_800151C8( (GV_ACT *)actor );
            return NULL;
        }

        if ( bullet_SetTarget_800761A0( actor, whichSide ) < 0 )
        {
            GV_DestroyActor_800151C8( (GV_ACT *)actor );
        }

        actor->field_14C = 0x100;
        actor->field_144_noise_len = arg3;
        actor->field_134 = arg2;
        actor->field_148_side = whichSide;
    }
    return actor;
}

GV_ACT *bullet_init_80076584(MATRIX *pMtx, int whichSide, int a3, int noiseLen)
{
    SVECTOR vec;
    BulletWork *work;

    work = (BulletWork *)GV_NewActor_800150E4(5, sizeof(BulletWork));
    if ( work )
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor,
                                  (TActorFunction)&bullet_act_80075DD4,
                                  (TActorFunction)&bullet_kill_80076164,
                                  "bullet.c");
        vec.vx = pMtx->m[0][0];
        vec.vy = pMtx->m[1][0];
        vec.vz = pMtx->m[2][0];
        work->field_160 = GV_VecLen3_80016D80(&vec);
        work->field_150 = 10;

        if ( whichSide == 1 )
        {

            if ( GM_CurrentWeaponId == WEAPON_PSG1 )
            {
                work->field_154_hp = 256;
            }
            else
            {
                work->field_154_hp = 64;
            }
        }
        else
        {
            work->field_154_hp = 64;
        }

        if ( noiseLen == 2 )
        {
            work->field_158 = 100000;
            work->field_15C = 5000;
        }
        else if ( noiseLen == 1 )
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

        if ( bullet_loader2_80076274(work, pMtx, a3, noiseLen, whichSide) < 0 )
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }

        if ( bullet_SetTarget_800761A0(work, whichSide) < 0 )
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
        }

        work->field_14C = 256;
        work->field_144_noise_len = noiseLen;
        work->field_134 = a3;
        work->field_148_side = whichSide;
    }

    return &work->field_0_actor;
}

BulletWork * NewBulletEx_80076708(
    int a1, MATRIX* pMtx, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    BulletWork* work; // $s0
    int flags; // $v1
    SVECTOR vec; // [sp+18h] [-28h] BYREF
    MATRIX mtx; // [sp+20h] [-20h] BYREF

    work = (BulletWork*)GV_NewActor_800150E4(5, sizeof(BulletWork));
    if (!work)
    {
        return 0;
    }

    GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)bullet_act_80075DD4,
        (TActorFunction)bullet_kill_80076164, "bullet.c");
    work->field_14C = a1;
    work->field_150 = a6 / 2;
    work->field_154_hp = a7;
    work->field_158 = a8;
    work->field_15C = a9;
    DG_SetPos_8001BC44(pMtx);
    vec.vx = -1024;
    vec.vy = 0;
    vec.vz = 0;
    DG_RotatePos_8001BD64(&vec);
    ReadRotMatrix(&mtx);

    if ((work->field_14C & 0x1000) != 0)
    {
        work->field_168 = 0;
    }
    else
    {
        work->field_168 = 1;
    }

    if (bullet_loader2_80076274(work, &mtx, a4, a5, a3) < 0)
    {
        GV_DestroyActor_800151C8(&work->field_0_actor);
        return 0;
    }
    else
    {
        if (bullet_SetTarget_800761A0(work, a3) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
        }
        flags = work->field_14C;
        work->field_144_noise_len = a5;
        work->field_134 = a4;
        work->field_148_side = a3;
        if ((flags & 1) != 0)
        {
            anime_create_8005D604(pMtx); // ??
        }
        else if ((flags & 2) != 0)
        {
            anime_create_8005D6BC(pMtx, 0);
        }
        else if ((flags & 4) != 0)
        {
            anime_create_8005D6BC(pMtx, 1);
        }
        else if ((flags & 8) != 0)
        {
            anime_create_8005D988(pMtx, pMtx, 0);
        }
        else if ((flags & 0x10) != 0)
        {
            anime_create_8005D988(pMtx, pMtx, 1);
        }
        else if ((flags & 0x20) != 0)
        {
            anime_create_8005E334(pMtx);
        }

        ++dword_8009F6A8;
        return work;
    }

    return 0;
}

BulletWork * sub_8007692C(MATRIX *pMtx, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    SVECTOR vec; // [sp+28h] [-28h] BYREF
    MATRIX mtx; // [sp+30h] [-20h] BYREF

    DG_SetPos_8001BC44(pMtx);
    vec.vx = 1024;
    vec.vy = 0;
    vec.vz = 0;
    DG_RotatePos_8001BD64(&vec);
    ReadRotMatrix(&mtx);
    return NewBulletEx_80076708(256, &mtx, a2, a3, a4, a5, a6, a7, a8);
}
