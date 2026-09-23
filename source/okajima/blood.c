#include "blood.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "strcode.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "anime/animconv/anime.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    SVECTOR  speed[16];
    SVECTOR  verts[64];
    int      time;
    int      n_packs;
} Work;

/*---------------------------------------------------------------------------*/

static RECT prim_rect = {50, 50, 100, 100};

static void InitVerts(MATRIX *world, SVECTOR *speed, SVECTOR *verts, int n_packs, int count)
{
    SVECTOR vecs[4];
    int     limit;
    int     scale;
    int     orig;
    int     ang;
    int     x, y, z;
    int     rx, ry, rz;

    orig = n_packs;

    DG_SetPos(world);

    switch (count)
    {
    case 0:
        limit = 4;
        scale = 4;
        break;
    case 1:
        limit = 4;
        scale = 4;
        break;
    case 2:
        limit = n_packs >> 1;
        scale = 1;
        break;
    default:
        limit = 0;
        scale = 1;
        break;
    }

    while (--n_packs >= 0)
    {
        ang = GV_RandU(4096);
        x = rcos(ang) >> 2;
        z = rsin(ang) >> 2;
        y = GV_RandU(128) + 32;

        x /= y;
        z /= y;

        if (limit >= n_packs)
        {
            y = -y / scale;
            x /= scale;
            z /= scale;
        }

        vecs[0].vx = x;
        vecs[0].vy = y;
        vecs[0].vz = z;

        vecs[3].vx = x * 8;
        vecs[3].vy = y * 8;
        vecs[3].vz = z * 8;

        rx = GV_RandS(64);
        ry = GV_RandS(64);
        rz = GV_RandS(64);

        vecs[1].vx = x + rx;
        vecs[1].vy = y + ry;
        vecs[1].vz = z + rz;

        vecs[2].vx = x - rx;
        vecs[2].vy = y - ry;
        vecs[2].vz = z - rz;

        DG_RotVector(vecs, speed, 1);
        DG_PutVector(vecs, verts, 4);

        if (n_packs >= (orig - 1))
        {
            speed->vx /= 4;
            speed->vy /= 4;
            speed->vz /= 4;
        }

        speed += 1;
        verts += 4;
    }
}

static void UpdateVerts(SVECTOR *speed, SVECTOR *verts, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = speed->vx;
        y = speed->vy;
        z = speed->vz;

        applyVector(&verts[0], x, y, z, +=);
        applyVector(&verts[3], x, y, z, +=);
        applyVector(&verts[1], x, y, z, +=);
        applyVector(&verts[2], x, y, z, +=);

        verts += 4;

        speed->vx = x;
        speed->vy = y - 11;
        speed->vz = z;
        speed++;
    }
}

static void InitPacks(POLY_FT4 *packs, int n_packs, DG_TEX *tex, int count)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        DG_SetPacketTexture4(packs, tex);

        // Some silly code to force the compiler
        // to emit "li t2, 2" and not clobber
        // a3 register (storing "count" variable).
        if (count == 2)
        {
            packs->tpage |= (1 << 5);
        }
        else
        {
            packs->tpage |= (1 << 5);
        }

        packs++;
    }
}

static void ShadePacks(POLY_FT4 *packs, int n_packs, int shade)
{
    while (--n_packs >= 0)
    {
        setRGB0(packs, shade, shade, shade);
        packs++;
    }
}

static void Act(Work *work)
{
    int      time;
    DG_PRIM *prim;

    GM_SetCurrentMap(work->map);

    time = --work->time;
    if (time <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    UpdateVerts(work->speed, work->verts, work->n_packs);

    prim = work->prim;
    ShadePacks(prim->packs[0], work->n_packs, time * 8);
    ShadePacks(prim->packs[1], work->n_packs, time * 8);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, int count)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->map = GM_CurrentMap;

    if (count <= 10)
    {
        work->n_packs = 16;
    }
    else
    {
        work->n_packs = count - 10;
    }

    InitVerts(world, work->speed, work->verts, work->n_packs, count);

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, work->n_packs, work->verts, &prim_rect);
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode("blood_1"));

    if (!tex)
    {
        return -1;
    }

    InitPacks(prim->packs[0], work->n_packs, tex, count);
    InitPacks(prim->packs[1], work->n_packs, tex, count);

    work->time = 16;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBlood(MATRIX *world, int count)
{
    SVECTOR vec;
    SVECTOR speed;
    SVECTOR pos;
    Work   *work;
    int     angle;
    short   scale;
    int     i;

    work = NULL;

    if (count <= 10)
    {
        DG_SetPos(world);

        angle = GV_RandU(4096);
        vec.vx = rcos(angle) / 4;
        vec.vz = rsin(angle) / 4;

        scale = GV_RandU(128) + 32;
        vec.vx /= scale;
        vec.vy = scale;
        vec.vz /= scale;

        DG_RotVector(&vec, &speed, 1);
        DG_PutVector(&vec, &pos, 1);

        speed.vx /= 4;
        speed.vy /= 4;
        speed.vz /= 4;

        AN_Blood_Mist(&pos, &speed);
    }

    for (i = 0; i < count; i++)
    {
        work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
        if (work == NULL)
        {
            continue;
        }

        GV_SetNamedActor(work, Act, Die, "blood.c");

        if (GetResources(work, world, count) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}

/*---------------------------------------------------------------------------*/

static const char anm_blood_form_script[] = {
    0x00,0x2A,0x01,0x00, 0x05,0x01,0xFE,0x02, 0x00,0x01,0x08,0x00, 0xB0,0xB0,0x0C,0x00,
    0x05,0x01,0xFF,0x0A, 0x00,0x64,0x00,0x64, 0x02,0x00,0x01,0x0D, 0x0C,0x00,0x05,0x01,
    0xFF,0x0A,0x00,0x1E, 0x00,0x1E,0x08,0xE8, 0xF8,0xF8,0x02,0x00, 0x01,0x0D,0x0F
};

static ANIMATION anm_blood_form = {
    PCX_BLOOD_2,                // tex
    1,                          // texdev_x
    1,                          // texdev_y
    1,                          // n_anime
    1,                          // n_verts
    500,                        // raise
    3,                          // amb
    300,                        // size_w
    300,                        // size_h
    200,                        // v
    NULL,                       // pre_script
    (void *)anm_blood_form_script // script
};

void AN_Blood_Mist( SVECTOR *pos, SVECTOR *speed )
{
    ANIMATION *anm;
    PRESCRIPT  pre;
    SVECTOR   *spd;

    spd = &pre.speed;

    pre.pos.vx = pos->vx;
    pre.pos.vy = pos->vy;
    pre.pos.vz = pos->vz;

    spd->vx = speed->vx;
    spd->vy = speed->vy;
    spd->vz = speed->vz;

    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &anm_blood_form;
    anm->pre_script = &pre;

    pre.scr_num = 0;
    NewAnime( NULL, 0, anm );
}
