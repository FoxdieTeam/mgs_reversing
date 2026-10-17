#include "sn_in_ef.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/
// VR: streaks of light shrinking towards Snake while he appears (created by snake_e1.c)

#define EXEC_LEVEL      GV_ACTOR_USER

#define STREAK_COUNT    32
#define STREAK_RADIUS   50

// streak state
enum
{
    STREAK_WAIT,                // waiting for a random delay
    STREAK_SHRINK,              // moving towards the centre, fading out
    STREAK_RESET                // restart
};

typedef struct _Work
{
    GV_ACT      actor;
    int         field_20;                   // 0x020
    int         map;                        // 0x024
    DG_PRIM    *prim;                       // 0x028
    SVECTOR     verts[STREAK_COUNT][4];     // 0x02C
    int         states[STREAK_COUNT];       // 0x42C (STREAK_*)
    SVECTOR     pos;                        // 0x4AC
    SVECTOR     rots[STREAK_COUNT];         // 0x4B4
    SVECTOR     offsets[STREAK_COUNT];      // 0x5B4 (pad: delay)
    int         lengths[STREAK_COUNT][2];   // 0x6B4 (distance of the outer and the inner end)
    int         field_7B4;                  // 0x7B4
    int         size;                       // 0x7B8
    int        *done;                       // 0x7BC (set by the snake_e1 actor)
    SVECTOR     color;                      // 0x7C0
} Work;

/*---------------------------------------------------------------------------*/

static void SetPackets(Work *work, POLY_FT4 *poly, int count, DG_TEX *tex)
{
    while (--count >= 0)
    {
        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 0, 0, 0);
        DG_SetPacketTexture4(poly, tex);
        poly->tpage |= 0x20;
        poly++;
    }
}

static int InitStreaks(Work *work, int size)
{
    SVECTOR     vec;
    SVECTOR     angle;
    DG_PRIM    *prim;
    DG_TEX     *tex;
    SVECTOR    *rot;
    SVECTOR    *offset;
    int        *state;
    int        *outer;
    int        *inner;
    int         i;

    work->size = size;

    tex = DG_GetTexture(GV_StrCode("rcm_l"));
    if (tex == NULL)
    {
        return -1;
    }

    prim = GM_MakePrim(DG_PRIM_POLY_FT4, STREAK_COUNT, work->verts[0], NULL);
    work->prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->raise = 0;

    SetPackets(work, prim->packs[0], STREAK_COUNT, tex);
    SetPackets(work, prim->packs[1], STREAK_COUNT, tex);

    vec.vx = STREAK_RADIUS;
    vec.vy = 0;
    vec.vz = 0;

    angle.vx = 0;
    angle.vz = 0;

    // FIXME: one pointer per array (and per column of lengths), advanced in this
    // order, steers gcc's induction variables / register allocation to the original
    rot = work->rots;
    offset = work->offsets;
    state = work->states;
    outer = &work->lengths[0][0];
    inner = &work->lengths[0][1];

    for (i = 0; i < STREAK_COUNT; outer += 2, inner += 2, i++, rot++, state++, offset++)
    {
        rot->vx = -GV_RandU(512);
        rot->vy = GV_RandU(4096);
        rot->vz = 0;
        *state = STREAK_WAIT;

        angle.vy = rot->vy;
        DG_SetPos2(&DG_ZeroVector, &angle);
        DG_PutVector(&vec, offset, 1);

        offset->pad = GV_RandU(32);

        *outer = work->size / 2 + (work->size * GV_RandU(4096)) / 8192;
        *inner = *outer * 7 / 8;
    }

    return 0;
}

static void UpdateStreaks(Work *work)
{
    SVECTOR     vec;
    SVECTOR     ends[2];
    SVECTOR     angle;
    SVECTOR     color;
    POLY_FT4   *poly;
    int         i;
    SVECTOR    *vert0;
    SVECTOR    *vert1;
    SVECTOR    *vert2;
    SVECTOR    *vert3;
    int        *state;
    SVECTOR    *rot;
    SVECTOR    *offset;
    int        *outer;
    int        *inner;

    // FIXME: one pointer per vertex column (and per column of lengths), advanced in
    // this order, steers gcc's induction variables / register allocation to the original
    vert0 = &work->verts[0][0];
    vert1 = &work->verts[0][1];
    vert2 = &work->verts[0][2];
    vert3 = &work->verts[0][3];
    state = work->states;
    rot = work->rots;
    outer = &work->lengths[0][0];
    inner = &work->lengths[0][1];
    offset = work->offsets;

    poly = work->prim->packs[GV_Clock];

    ends[0] = DG_ZeroVector;
    ends[1] = DG_ZeroVector;

    vec.vx = STREAK_RADIUS;
    vec.vy = 0;
    vec.vz = 0;

    angle.vx = 0;
    angle.vz = 0;

    for (i = 0; i < STREAK_COUNT; outer += 2, inner += 2, i++,
         vert0 += 4, vert1 += 4, vert2 += 4, vert3 += 4, state++, rot++, offset++, poly++)
    {
        switch (*state)
        {
        case STREAK_WAIT:
            if (--offset->pad < 0)
            {
                setRGB0(poly, work->color.vx, work->color.vy, work->color.vz);
                *state = STREAK_SHRINK;
            }
            break;

        case STREAK_SHRINK:
            ends[1].vz = *inner;
            *outer = *outer * 7 / 8 - 10;
            ends[0].vz = *outer;
            *inner = *inner * 3 / 4 - 10;

            if (*outer < 0)
            {
                *outer = 0;
                *state = STREAK_RESET;
            }

            if (*inner < 0)
            {
                *inner = 0;
            }

            color.vx = (work->color.vx * *outer) / work->size;
            color.vy = (work->color.vy * *outer) / work->size;
            color.vz = (work->color.vz * *outer) / work->size;
            setRGB0(poly, color.vx, color.vy, color.vz);

            DG_SetPos2(&work->pos, rot);
            DG_PutVector(ends, vert0, 2);

            *vert2 = *vert0;
            *vert3 = *vert1;

            vert2->vx += offset->vx;
            vert2->vy += offset->vy;
            vert2->vz += offset->vz;

            vert3->vx += offset->vx;
            vert3->vy += offset->vy;
            vert3->vz += offset->vz;
            break;

        case STREAK_RESET:
            setRGB0(poly, 0, 0, 0);

            rot->vx = -GV_RandU(512);
            rot->vy = GV_RandU(4096);
            rot->vz = 0;
            *state = STREAK_WAIT;

            angle.vy = rot->vy;
            DG_SetPos2(&DG_ZeroVector, &angle);
            DG_PutVector(&vec, offset, 1);

            offset->pad = 0;

            *outer = work->size / 2 + (work->size * GV_RandU(4096)) / 8192;
            *inner = *outer * 7 / 8;
            break;
        }
    }

    if (*work->done == 1)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Act(Work *work)
{
    GM_SetCurrentMap(GM_PlayerMap);
    work->prim->group_id = GM_PlayerMap; // FIXME: not DG_GroupPrim (reloads GM_PlayerMap as halfword)
    UpdateStreaks(work);
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(Work *work, MATRIX *world, int size, int *done, SVECTOR *color)
{
    work->field_7B4 = 0;
    work->done = done;

    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];

    work->color = *color;

    if (InitStreaks(work, size) < 0)
    {
        return -1;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSnakeInEffect(MATRIX *world, int size, int *done, int map, SVECTOR *color)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "sn_in_ef.c");

        work->map = map;

        if (GetResources(work, world, size, done, color) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
