#include "d_bloodr.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  verts[16];
    SVECTOR  pos[4];
    SVECTOR  rot;
    int      map;
    char     unused[4];
    int      time;
    int      height;
} Work;

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void Act(Work *work)
{
    SVECTOR vecs[4];
    SVECTOR rot;
    SVECTOR diff;
    int     dist;
    int     i;

    GM_SetCurrentMap(work->map);

    if (work->time > 10 && work->time < 200)
    {
        dist = (work->time - 10) * 3 / 2;
        for (i = 0; i < 4; i++)
        {
            vecs[0].vx = -dist;
            vecs[0].vy = 0;
            vecs[0].vz = dist;

            vecs[1].vx = dist;
            vecs[1].vy = 0;
            vecs[1].vz = dist;

            vecs[2].vx = -dist;
            vecs[2].vy = 0;
            vecs[2].vz = -dist;

            vecs[3].vx = dist;
            vecs[3].vy = 0;
            vecs[3].vz = -dist;

            rot = work->rot;
            rot.vy += i * 200;

            DG_SetPos2(&work->pos[i], &work->rot);
            DG_PutVector(vecs, &work->verts[i * 4], 4);
        }
    }

    if (work->time < 200 && ++work->time == 100)
    {
        GM_PlayerStatus |= PLAYER_KETCHUP;
    }

    if (work->time >= 100)
    {
        if (GM_PlayerStatus & PLAYER_GROUND)
        {
            GV_SubVec3(&GM_PlayerPosition, &work->pos[0], &diff);

            if (GV_VecLen3(&diff) > 640)
            {
                GM_PlayerStatus &= ~PLAYER_KETCHUP;
            }
            else
            {
                GM_PlayerStatus |= PLAYER_KETCHUP;
            }
        }
        else
        {
            GM_PlayerStatus &= ~PLAYER_KETCHUP;
        }
    }
}

static void InitPacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        setRGB0(packs0, 0, 255, 255);
        DG_SetPacketTexture4(packs0, tex);

        setRGB0(packs1, 0, 255, 255);
        DG_SetPacketTexture4(packs1, tex);

        packs0->tpage |= (2 << 5);
        packs0++;

        packs1->tpage |= (2 << 5);
        packs1++;
    }
}

static int InitPrim(Work *work)
{
    int      unit[4];
    SVECTOR  vecs[4];
    int      i;
    DG_PRIM *prim;
    DG_TEX  *tex;

    unit[0] = 0;
    unit[1] = 5;
    unit[2] = 2;
    unit[3] = 7;

    work->rot = DG_ZeroVector;

    for (i = 0; i < 4; i++)
    {
        work->pos[i].vx = GM_PlayerBody->objs->objs[unit[i]].world.t[0];
        work->pos[i].vy = GM_PlayerBody->objs->objs[0].world.t[1] - work->height;
        work->pos[i].vz = GM_PlayerBody->objs->objs[unit[i]].world.t[2];

        setVector(&vecs[0], 0, 0, 0);
        setVector(&vecs[1], 0, 0, 0);
        setVector(&vecs[2], 0, 0, 0);
        setVector(&vecs[3], 0, 0, 0);

        DG_SetPos2(&work->pos[i], &work->rot);
        DG_PutVector(vecs, &work->verts[i * 4], 4);
    }

    work->prim  = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 4, work->verts, NULL);
    if (prim == NULL) return -1;

    prim->raise = 0;

    tex = DG_GetTexture(GV_StrCode("ketchap_grey"));
    if (tex == NULL) return -1;

    InitPacks(prim->packs[0], prim->packs[1], 4, tex);
    return 0;
}

static int GetResources(Work *work, int map)
{
    work->map = map;
    work->time = 0;
    work->height = GM_PlayerControl->height;

    GM_SetCurrentMap(map);

    if (InitPrim(work) == -1)
    {
        GV_DestroyActor(work);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewKetchapRing(int map)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER2, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "d_bloodr.c");

        if (GetResources(work, map) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
