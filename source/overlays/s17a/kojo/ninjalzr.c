#include <stdlib.h>
#include <memory.h>
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "game/camera.h"

/* Ninja laser (Gray Fox's beam in the REX battle demo) */

#define N_BEAMS     7
#define N_LIGHTS    100
#define N_BUBBLES   8

typedef struct _NinjaLight
{
    u_char life;
    char   script[32];
} NinjaLight;

typedef struct _Work
{
    GV_ACT      actor;
    int         map;                    // 0x20
    DG_PRIM    *prims[N_BEAMS];         // 0x24
    SVECTOR     verts[N_BEAMS * 4];     // 0x40
    SVECTOR     offsets[N_BEAMS];       // 0x120
    int         timers[N_BEAMS];        // 0x158
    int         time_max;               // 0x174
    int         size;                   // 0x178
    int         time;                   // 0x17C
    int         laser_time;             // 0x180
    MATRIX     *root;                   // 0x184
    MATRIX      world;                  // 0x188
    NinjaLight  lights[N_LIGHTS];       // 0x1A8
    GV_ACT     *laser;                  // 0xE8C
} Work;

typedef struct _BubbleWork
{
    GV_ACT      actor;
    int         map;                    // 0x20
    DG_PRIM    *prim;                   // 0x24
    SVECTOR     verts[N_BUBBLES * 4];   // 0x28
    SVECTOR     speeds[N_BUBBLES];      // 0x128
    SVECTOR     color;                  // 0x168
    int         time;                   // 0x170
} BubbleWork;

#define EXEC_LEVEL GV_ACTOR_USER

void *NewMetalGearLaser(MATRIX *root);
void  s01a_object_800D96B8(MATRIX *world, int arg1, char arg2, char arg3, char arg4, char arg5, char arg6, char arg7, char arg8, char *ptr);

RECT ninjalzr_bubble_rect = {50, 50, 100, 100};

void s17a_800D4DC0(Work *work);
void NinjaLaser_Die(Work *work);
void NinjaLaser_AddLight(Work *work, MATRIX *world, int size, u_char r, u_char g, u_char b, u_char life, u_char arg7, u_char arg8, u_char arg9);
void       *NewNinjaLaserBubble(MATRIX *world);

void *NewNinjaLaser(MATRIX *root, int size, int time)
{
    Work   *work;
    DG_TEX *tex;
    int     i;

    tex = DG_GetTexture(GV_StrCode("blue_bonbori"));
    if (tex == NULL || (work = GV_NewActor(EXEC_LEVEL, sizeof(Work))) == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, s17a_800D4DC0, NinjaLaser_Die, "ninjalzr.c");

    work->time_max = time + 30;
    work->size = size;
    work->root = root;
    work->map = GM_CurrentMap;
    work->time = work->time_max;

    for (i = 0; i < N_BEAMS; i++)
    {
        work->prims[i] = GM_MakePrim(DG_PRIM_POLY_FT4, 1, &work->verts[i * 4], NULL);

#define PACK0   (((POLY_FT4 *)work->prims[i]->packs[0]) + 0)
#define PACK1   (((POLY_FT4 *)work->prims[i]->packs[0]) + 1)

        {
            int x, y, w, h;
            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(PACK0, x, y, w, h);
            PACK0->tpage = tex->tpage;
            PACK0->clut = tex->clut;
        }
        {
            int x, y, w, h;
            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH(PACK1, x, y, w, h);
            PACK1->tpage = tex->tpage;
            PACK1->clut = tex->clut;
        }

        PACK0->tpage = PACK0->tpage;
        PACK1->tpage = PACK1->tpage;

        setPolyFT4(PACK0);
        setPolyFT4(PACK1);
        setRGB0(PACK0, 0, 0, 0);
        setRGB0(PACK1, 0, 0, 0);
        setSemiTrans(PACK0, 1);
        setSemiTrans(PACK1, 1);

#undef PACK0
#undef PACK1
    }

    return (void *)work;
}

void s17a_800D4DC0(Work *work)
{
    VECTOR   scale;
    SVECTOR  vec;
    SVECTOR  rot;
    MATRIX   world;
    MATRIX   mtx;
    SVECTOR *verts;
    int      i;
    int      half;
    int      n_beams;
    int      mask, base;
    int      t;

    if (work->time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    GM_CurrentMap = work->map;

    if (--work->laser_time <= 0)
    {
        if (work->laser)
        {
            GV_DestroyActor(work->laser);
        }
        work->laser = NULL;
    }

    for (i = 0; i < N_LIGHTS; i++)
    {
        if ((signed char)--work->lights[i].life < 0)
        {
            work->lights[i].life = 0;
        }
    }

    DG_SetPos(work->root);
    vec.vx = 1024;
    vec.vy = 0;
    vec.vz = 0;
    DG_RotatePos(&vec);
    vec.vx = 0;
    vec.vy = 0;
    vec.vz = 350;
    DG_MovePos(&vec);
    ReadRotMatrix(&world);
    ReadRotMatrix(&work->world);

    i = work->size / 10;
    half = i >> 1;
    work->world.t[0] += rand() % i - half;
    work->world.t[1] += rand() % i - half;
    work->world.t[2] += rand() % i - half;

    t = work->time;
    if (t > 30)
    {
        i = t - 30;
        NinjaLaser_AddLight(work, &world, work->size >> 1, 127 / i, 127 / i, 255 / i, 6, 0, 0, 0);

        n_beams = ((work->time_max - work->time) * 7) / (work->time_max - 30);
        mask = ((work->time - 30) * 8) / (work->time_max - 30);
        base = ((work->time - 30) * 7) / (work->time_max - 30);

        for (i = 0; i < n_beams; i++)
        {
            if (work->timers[i] == 0)
            {
                work->offsets[i].vx = (rand() & (work->size >> 1)) - (work->size >> 2);
                work->offsets[i].vy = (rand() & (work->size >> 1)) - (work->size >> 2);
                work->offsets[i].vz = work->size + ((rand() & (work->size >> 1)) - (work->size >> 2));
                work->timers[i] = (rand() & mask) + base + 5;

                ((POLY_FT4 *)work->prims[i]->packs[0])[0].r0 = 128;
                ((POLY_FT4 *)work->prims[i]->packs[0])[0].g0 = 128;
                ((POLY_FT4 *)work->prims[i]->packs[0])[0].b0 = 255;
                ((POLY_FT4 *)work->prims[i]->packs[0])[1].r0 = 118;
                ((POLY_FT4 *)work->prims[i]->packs[0])[1].g0 = 118;
                ((POLY_FT4 *)work->prims[i]->packs[0])[1].b0 = 245;
            }
            else
            {
                work->offsets[i].vx -= work->offsets[i].vx / work->timers[i];
                work->offsets[i].vy -= work->offsets[i].vy / work->timers[i];
                work->offsets[i].vz -= work->offsets[i].vz / work->timers[i];
                work->timers[i]--;
            }

            verts = &work->verts[i * 4];
            memset(verts, 0, sizeof(SVECTOR) * 4);

            work->verts[i * 4 + 0].vx = -(work->size >> 5);
            work->verts[i * 4 + 0].vy = -(work->size >> 5);
            work->verts[i * 4 + 1].vx = -(work->size >> 5);
            work->verts[i * 4 + 1].vy = work->size >> 5;
            work->verts[i * 4 + 2].vx = work->size >> 5;
            work->verts[i * 4 + 2].vy = -(work->size >> 5);
            work->verts[i * 4 + 3].vx = work->size >> 5;
            work->verts[i * 4 + 3].vy = work->size >> 5;

            vec.vx = (world.t[0] - gUnkCameraStruct2_800B7868.position.vx) >> 2;
            vec.vy = (world.t[1] - gUnkCameraStruct2_800B7868.position.vy) >> 2;
            vec.vz = (world.t[2] - gUnkCameraStruct2_800B7868.position.vz) >> 2;

            rot.vx = -ratan2(vec.vy, SquareRoot0(vec.vx * vec.vx + vec.vz * vec.vz));
            rot.vy = ratan2(vec.vx, vec.vz);
            rot.vz = 0;

            DG_SetPos2(&DG_ZeroVector, &rot);
            DG_PutVector(verts, verts, 4);

            DG_SetPos(&world);
            vec = work->offsets[i];
            DG_PutVector(&vec, &vec, 1);
            DG_SetPos2(&vec, &DG_ZeroVector);
            DG_PutVector(verts, verts, 4);
        }
    }
    else if (t == 30)
    {
        for (i = 0; i < N_BEAMS; i++)
        {
            GM_FreePrim(work->prims[i]);
        }

        work->laser_time = 10;
        work->laser = NewMetalGearLaser(&work->world);
    }
    else
    {
        if (t == 10)
        {
            DG_SetPos(&world);
            vec.vx = 1024;
            vec.vy = 0;
            vec.vz = 0;
            DG_RotatePos(&vec);
            ReadRotMatrix(&mtx);
            scale.vx = 512;
            scale.vy = 512;
            scale.vz = 512;
            ScaleMatrix(&mtx, &scale);
            NewNinjaLaserBubble(&mtx);
        }

        if (work->time >= 7)
        {
            i = 30 - work->time;
            NinjaLaser_AddLight(work, &world, work->size, 127 / i, 127 / i, 255 / i, 6, 0, 0, 0);
        }

        if (work->time >= 11)
        {
            memset(&vec, 0, sizeof(SVECTOR));
            vec.vz = work->size >> 2;
            DG_SetPos(&world);
            DG_MovePos(&vec);
            ReadRotMatrix(&mtx);
            i = 30 - work->time;
            NinjaLaser_AddLight(work, &mtx, work->size >> 1, 95 / i, 95 / i, 255 / i, 6, 0, 0, 0);
        }

        if (work->time >= 16)
        {
            memset(&vec, 0, sizeof(SVECTOR));
            vec.vz = work->size >> 1;
            DG_SetPos(&world);
            DG_MovePos(&vec);
            ReadRotMatrix(&mtx);
            i = 30 - work->time;
            NinjaLaser_AddLight(work, &mtx, work->size >> 1, 63 / i, 63 / i, 255 / i, 6, 0, 0, 0);
        }
    }

    work->time--;
}

void NinjaLaser_Die(Work *work)
{
    if (work->laser)
    {
        GV_DestroyActor(work->laser);
    }
}

void NinjaLaser_AddLight(Work *work, MATRIX *world, int size, u_char r, u_char g, u_char b, u_char life, u_char arg7, u_char arg8, u_char arg9)
{
    int i;

    for (i = 0; i < N_LIGHTS; i++)
    {
        if (work->lights[i].life == 0)
        {
            break;
        }
    }

    if (i < N_LIGHTS)
    {
        work->lights[i].life = life + 1;
        s01a_object_800D96B8(world, size, r, g, b, life, arg7, arg8, arg9, work->lights[i].script);
    }
}

/*---------------------------------------------------------------------------*/

static void BubbleAct(BubbleWork *work);
static void BubbleDie(BubbleWork *work);

void *NewNinjaLaserBubble(MATRIX *world)
{
    int         i;
    BubbleWork *work;
    DG_TEX     *tex;
    DG_PRIM    *prim;
    POLY_FT4   *packs;
    SVECTOR     dir;
    SVECTOR     ofs;
    SVECTOR     verts[4];
    int         ang;
    int         len;

    tex = DG_GetTexture(GV_StrCode("awa_3"));
    if (tex == NULL || (work = GV_NewActor(EXEC_LEVEL, sizeof(BubbleWork))) == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, BubbleAct, BubbleDie, "ninjalzr.c");

    work->time = 8;
    work->color.vx = 255;
    work->color.vy = 255;
    work->color.vz = 255;
    work->map = GM_CurrentMap;

    DG_SetPos(world);

    for (i = 0; i < N_BUBBLES; i++)
    {
        ang = GV_RandU(4096);
        dir.vx = rcos(ang);
        dir.vz = rsin(ang);

        len = GV_RandU(256) + 64;
        dir.vy = len;
        dir.vx /= (short)len;
        dir.vz /= (short)len;

        ofs.vx = GV_RandS(512);
        ofs.vy = GV_RandS(512);
        ofs.vz = GV_RandS(512);

        verts[0].vx = dir.vx;
        verts[0].vy = dir.vy;
        verts[0].vz = dir.vz;

        verts[1].vx = dir.vx + ofs.vx;
        verts[1].vy = dir.vy + ofs.vy;
        verts[1].vz = dir.vz + ofs.vz;

        verts[2].vx = dir.vx - ofs.vx;
        verts[2].vy = dir.vy - ofs.vy;
        verts[2].vz = dir.vz - ofs.vz;

        verts[3].vx = dir.vx * 4;
        verts[3].vy = dir.vy * 4;
        verts[3].vz = dir.vz * 4;

        DG_RotVector(verts, &work->speeds[i], 1);
        DG_PutVector(verts, &work->verts[i * 4], 4);
    }

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, N_BUBBLES, work->verts, &ninjalzr_bubble_rect);
    work->prim = prim;

    packs = prim->packs[0];
    for (i = 0; i < N_BUBBLES; i++)
    {
        int x, y, w, h;

        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);
        packs->tpage = tex->tpage;
        packs->clut = tex->clut;
        packs->tpage |= 0x20;
        setRGB0(packs, 127, 255, 255);
        packs++;
    }

    packs = work->prim->packs[1];
    for (i = 0; i < N_BUBBLES; i++)
    {
        int x, y, w, h;

        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);
        packs->tpage = tex->tpage;
        packs->clut = tex->clut;
        packs->tpage |= 0x20;
        setRGB0(packs, 127, 255, 255);
        packs++;
    }

    return (void *)work;
}

static void BubbleAct(BubbleWork *work)
{
    SVECTOR   color;
    POLY_FT4 *packs;
    int       i;
    int       k;

    GM_CurrentMap = work->map;

    if (--work->time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    k = work->time * 10;
    color.vx = (work->color.vx * k) / 256;
    color.vy = (work->color.vy * k) / 256;
    color.vz = (work->color.vz * k) / 256;

    packs = work->prim->packs[GV_Clock];

    for (i = 0; i < N_BUBBLES; i++)
    {
        work->verts[i * 4].vx += work->speeds[i].vx;
        work->verts[i * 4].vy += work->speeds[i].vy;
        work->verts[i * 4].vz += work->speeds[i].vz;
        work->verts[i * 4 + 1].vx += work->speeds[i].vx;
        work->verts[i * 4 + 1].vy += work->speeds[i].vy;
        work->verts[i * 4 + 1].vz += work->speeds[i].vz;
        work->verts[i * 4 + 2].vx += work->speeds[i].vx;
        work->verts[i * 4 + 2].vy += work->speeds[i].vy;
        work->verts[i * 4 + 2].vz += work->speeds[i].vz;
        work->verts[i * 4 + 3].vx += work->speeds[i].vx;
        work->verts[i * 4 + 3].vy += work->speeds[i].vy;
        work->verts[i * 4 + 3].vz += work->speeds[i].vz;

        setRGB0(packs, color.vx, color.vy, color.vz);
        packs++;
    }
}

static void BubbleDie(BubbleWork *work)
{
    GM_FreePrim(work->prim);
}
