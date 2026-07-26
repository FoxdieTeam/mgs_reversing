#include "d_bloods.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim;
    SVECTOR  verts[8];
    SVECTOR  pos[2];
    SVECTOR  rot;
    int      map;
    int      time;
    SVECTOR  start_pos;
    int      type;
    int      size;
    int      max_time;
} Work;

static int blood_count;

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void Act(Work *work)
{
    SVECTOR vecs[4];
    int     dist;

    GM_CurrentMap = work->map;

    switch (work->type)
    {
    case 0:
    case 2:
        if (work->time < (work->max_time / 2))
        {
            dist = work->size * work->time * 2 / work->max_time;

            work->pos[0].vx = work->start_pos.vx;
            work->pos[0].vy = work->start_pos.vy;
            work->pos[0].vz = work->start_pos.vz;

            vecs[0].vx = (-dist * 3) / 2;
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

            DG_SetPos2(&work->pos[0], &work->rot);
            DG_PutVector(vecs, work->verts, 4);
        }

        if (work->time > (work->max_time / 4) && work->time < work->max_time)
        {
            dist = work->size * (work->time - work->max_time / 4) / (work->max_time * 3 / 4);

            work->pos[1].vx = work->start_pos.vx;
            work->pos[1].vy = work->start_pos.vy;
            work->pos[1].vz = work->start_pos.vz;

            vecs[0].vx = -dist;
            vecs[0].vy = 0;
            vecs[0].vz = (dist * 2) / 3;

            vecs[1].vx = dist;
            vecs[1].vy = 0;
            vecs[1].vz = (dist * 2) / 3;

            vecs[2].vx = -dist * 2;
            vecs[2].vy = 0;
            vecs[2].vz = (-dist * 2) / 3;

            vecs[3].vx = dist;
            vecs[3].vy = 0;
            vecs[3].vz = (-dist * 2) / 3;

            DG_SetPos2(&work->pos[1], &work->rot);
            DG_PutVector(vecs, work->verts + 4, 4);
        }

        if (work->time < work->max_time)
        {
            work->time++;
        }
        break;
    case 1:
    case 3:
        dist = work->size;

        work->pos[0].vx = work->start_pos.vx;
        work->pos[0].vy = work->start_pos.vy;
        work->pos[0].vz = work->start_pos.vz;

        vecs[0].vx = -dist * 3 / 2;
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

        DG_SetPos2(&work->pos[0], &work->rot);
        DG_PutVector(vecs, work->verts, 4);

        dist = work->size * 120 / 100;

        work->pos[1].vx = work->start_pos.vx;
        work->pos[1].vy = work->start_pos.vy;
        work->pos[1].vz = work->start_pos.vz;

        vecs[0].vx = -dist;
        vecs[0].vy = 0;
        vecs[0].vz = dist * 2 / 3;

        vecs[1].vx = dist;
        vecs[1].vy = 0;
        vecs[1].vz = dist * 2 / 3;

        vecs[2].vx = -dist * 2;
        vecs[2].vy = 0;
        vecs[2].vz = -dist * 2 / 3;

        vecs[3].vx = dist;
        vecs[3].vy = 0;
        vecs[3].vz = -dist * 2 / 3;

        DG_SetPos2(&work->pos[1], &work->rot);
        DG_PutVector(vecs, work->verts + 4, 4);
        break;
    case 4:
    case 6:
        if (blood_count < work->max_time / 2)
        {
            dist = work->size * blood_count * 2 / work->max_time;

            work->pos[0].vx = work->start_pos.vx;
            work->pos[0].vy = work->start_pos.vy;
            work->pos[0].vz = work->start_pos.vz;

            vecs[0].vx = -dist * 3 / 2;
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

            DG_SetPos2(&work->pos[0], &work->rot);
            DG_PutVector(vecs, work->verts, 4);
        }

        if (blood_count > (work->max_time / 4) && blood_count < work->max_time)
        {
            dist = work->size * (blood_count - work->max_time / 4) / (work->max_time * 3 / 4);

            work->pos[1].vx = work->start_pos.vx;
            work->pos[1].vy = work->start_pos.vy;
            work->pos[1].vz = work->start_pos.vz;

            vecs[0].vx = -dist;
            vecs[0].vy = 0;
            vecs[0].vz = dist * 2 / 3;

            vecs[1].vx = dist;
            vecs[1].vy = 0;
            vecs[1].vz = dist * 2 / 3;

            vecs[2].vx = -dist * 2;
            vecs[2].vy = 0;
            vecs[2].vz = -dist * 2 / 3;

            vecs[3].vx = dist;
            vecs[3].vy = 0;
            vecs[3].vz = -dist * 2 / 3;

            DG_SetPos2(&work->pos[1], &work->rot);
            DG_PutVector(vecs, work->verts + 4, 4);
        }

        if (blood_count < work->max_time)
        {
            blood_count++;
        }
        else
        {
            blood_count = 0;
        }

        GV_DestroyActor(work);
        break;
    case 5:
    case 7:
        dist = work->size;

        work->pos[0].vx = work->start_pos.vx;
        work->pos[0].vy = work->start_pos.vy;
        work->pos[0].vz = work->start_pos.vz;

        vecs[0].vx = -dist * 3 / 2;
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

        DG_SetPos2(&work->pos[0], &work->rot);
        DG_PutVector(vecs, work->verts, 4);

        dist = work->size * 120 / 100;

        work->pos[1].vx = work->start_pos.vx;
        work->pos[1].vy = work->start_pos.vy;
        work->pos[1].vz = work->start_pos.vz;

        vecs[0].vx = -dist;
        vecs[0].vy = 0;
        vecs[0].vz = dist * 2 / 3;

        vecs[1].vx = dist;
        vecs[1].vy = 0;
        vecs[1].vz = dist * 2 / 3;

        vecs[2].vx = -dist * 2;
        vecs[2].vy = 0;
        vecs[2].vz = -dist * 2 / 3;

        vecs[3].vx = dist;
        vecs[3].vy = 0;
        vecs[3].vz = -dist * 2 / 3;

        DG_SetPos2(&work->pos[1], &work->rot);
        DG_PutVector(vecs, work->verts + 4, 4);
        GV_DestroyActor(work);
        break;
    }
}

static void InitPacks(POLY_FT4 *packs0, POLY_FT4 *packs1, int n_packs, DG_TEX *tex, int type)
{
    while (--n_packs >= 0)
    {
        setPolyFT4(packs0);
        setSemiTrans(packs0, 1);

        setPolyFT4(packs1);
        setSemiTrans(packs1, 1);

        DG_SetPacketTexture4(packs0, tex);
        DG_SetPacketTexture4(packs1, tex);

        if (type > 1 && type < 6)
        {
            setRGB0(packs0, 0, 0, 32);
            setRGB0(packs1, 0, 0, 32);
        }
        else
        {
            setRGB0(packs0, 90, 128, 128);
            setRGB0(packs1, 90, 128, 128);
        }

        packs0++;
        packs1++;
    }
}

static int InitState(Work *work, SVECTOR *pos, int type, int size, int speed)
{
    work->time = 0;
    work->start_pos = *pos;
    work->type = type;
    work->size = size;
    work->max_time = speed;
    return 0;
}

static int InitPrim(Work *work, int type)
{
    SVECTOR  pos;
    SVECTOR  vecs[4];
    int      i;
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->rot = DG_ZeroVector;

    for (i = 0; i < 2; i++)
    {
        pos.vx = work->start_pos.vx;
        pos.vy = work->start_pos.vy;
        pos.vz = work->start_pos.vz;

        work->pos[i] = pos;

        setVector(&vecs[0], 0, 0, 0);
        setVector(&vecs[1], 0, 0, 0);
        setVector(&vecs[2], 0, 0, 0);
        setVector(&vecs[3], 0, 0, 0);

        DG_SetPos2(&work->pos[i], &DG_ZeroVector);
        DG_PutVector(vecs, &work->verts[i * 4], 4);
    }

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, work->verts, NULL);
    if (prim == NULL) return -1;

    DG_RaisePrim(prim, -500);

    tex = DG_GetTexture(GV_StrCode("ketchap"));
    if (tex == NULL) return -1;

    InitPacks(prim->packs[0], prim->packs[1], 2, tex, type);
    return 0;
}

static int GetResources(Work *work, SVECTOR *pos, int type, int size, int speed)
{
    work->map = GM_CurrentMap;

    InitState(work, pos, type, size, speed);

    if (InitPrim(work, type) == -1)
    {
        GV_DestroyActor(work);
    }

    return 0;
}

void *NewKetchap_s(SVECTOR *pos, int type, int size, int speed)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "d_bloods.c");

        if (GetResources(work, pos, type, size, speed) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
