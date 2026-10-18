// (VR only) this file is empty in the main executable build
// Snow of the vcd_n05 (godzilla) mission: an older revision of thing/snow.c with fixed parameters (no GCL options) that
// uses the library rand()/GV_RandU().
#ifdef VR_EXE


#include <stdlib.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

typedef struct _SnowEntry
{
    SVECTOR  pos;
    SVECTOR  f8;
    SVECTOR  rot;
    SVECTOR  f18;
    DG_PRIM *prim;
    SVECTOR  vecs[32];
} SnowEntry;

typedef struct _Work
{
    GV_ACT    actor;
    SVECTOR   min;
    SVECTOR   max;
    SVECTOR   f30;
    SVECTOR   f38;
    int       n_entries;
    int       f44;
    SnowEntry entries[32];
    int       colors[32];
    int       f2548;
    int       f254C;
    int       f2550;
    int       f2554;
    GV_MSG   *msgs;
} Work;

/*---------------------------------------------------------------------------*/

SVECTOR snow_svec_800C3854 = {-5000, 0, -10000, 0};
SVECTOR snow_svec_800C385C = {5000, 8000, 10000, 0};
SVECTOR snow_svec_800C3864 = {0, -50, 0, 0};
RECT    snow_rect_800C386C = {0, 0, 2, 2};

void Snow_800C5234(TILE *packs, int n_packs, int *colors)
{
    while (--n_packs >= 0)
    {
        LSTORE(*colors++, &packs->r0);
        packs++;
    }
}

void Snow_800C5260(int *colors, int n_colors)
{
    TILE tile;
    int  color;
    int  shade;

    setTile(&tile);
    color = LLOAD(&tile.r0) & RGBA_A_MASK;

    while (--n_colors >= 0)
    {
        shade = GV_RandU(128) + 128;
        *colors++ = color | shade / 2 | (shade / 2) << 8 | shade << 16;
    }
}

// FIXME: relocatable asm; the loop of the C version below is identical but the original addresses the tile fields from
// the end of the packet (+0xE) with other scheduling.
void Snow_800C52F0(TILE *packs1, TILE *packs2, int n_packs, int *colors);
#pragma INCLUDE_ASM_RELOC("source/thing/vr/reloc/SnowInitPacks.s")
#if 0 /* NON_MATCHING */
void Snow_800C52F0(TILE *packs1, TILE *packs2, int n_packs, int *colors)
{
    int rnd;

    while (--n_packs >= 0)
    {
        rnd = GV_RandU(4) + 2;

        setTile(packs1);
        setWH(packs1, 1, rnd);
        LSTORE(*colors, &packs1->r0);

        setTile(packs2);
        setWH(packs2, 1, rnd);
        LSTORE(*colors, &packs2->r0);

        packs1++;
        packs2++;
        colors++;
    }
}
#endif

void Snow_800C53A0(SVECTOR *dst, int x0, int x1, int y0, int y1, int z0, int z1)
{
    dst->vx = ((rand() & 0xFF) * (x1 - x0)) / 256 + x0;
    dst->vy = ((rand() & 0xFF) * (y1 - y0)) / 256 + y0;
    dst->vz = ((rand() & 0xFF) * (z1 - z0)) / 256 + z0;
}

void Snow_800C547C(SVECTOR *dst, SVECTOR *src, SVECTOR *scale)
{
    dst->vx = src->vx + ((rand() & 0xFF) * scale->vx) / 256;
    dst->vy = src->vy + ((rand() & 0xFF) * scale->vy) / 256;
    dst->vz = src->vz + ((rand() & 0xFF) * scale->vz) / 256;
}

void Snow_800C5544(Work *work, SnowEntry *entry, int arg2, SVECTOR *target)
{
    SVECTOR  wind;
    int      s0;
    SVECTOR *vec;
    int      i;

    Snow_800C53A0(&entry->pos, work->min.vx, work->max.vx, work->min.vy, work->max.vy, work->min.vz, work->max.vz);

    if (arg2 != 0)
    {
        switch (work->f44)
        {
        case 0:
            entry->pos.vx = work->max.vx;
            break;

        case 1:
            entry->pos.vx = work->min.vx;
            break;

        case 2:
            entry->pos.vy = work->max.vy;
            break;

        case 3:
            entry->pos.vy = work->min.vy;
            break;

        case 4:
            entry->pos.vz = work->max.vz;
            break;

        case 5:
            entry->pos.vz = work->min.vz;
            break;
        }
    }

    GV_AddVec3(target, &entry->pos, &entry->pos);
    Snow_800C53A0(&entry->f18, -8, 8, -8, 8, -8, 8);

    entry->rot = DG_ZeroVector;

    if (GM_lpsvectWind != NULL)
    {
        if (work->f2548 == 1)
        {
            wind = *GM_lpsvectWind;

            if (wind.vx < 0)
            {
                wind.vx = -wind.vx;
            }

            if (wind.vy < 0)
            {
                wind.vy = -wind.vy;
            }

            if (wind.vz < 0)
            {
                wind.vz = -wind.vz;
            }

            s0 = 2;
            if (wind.vx >= wind.vy)
            {
                if (wind.vz <= wind.vx)
                {
                    s0 = 0;
                    wind.vz = wind.vx;
                }
            }
            else if (wind.vz <= wind.vy)
            {
                s0 = 1;
                wind.vz = wind.vy;
            }

            Snow_800C53A0(&entry->pos, work->min.vx / 2, work->max.vx / 2, work->min.vy / 2, work->max.vy / 2, work->min.vz / 2, work->max.vz / 2);

            switch (s0 * 2 + (wind.vz > 0))
            {
            case 0:
                entry->pos.vx = work->min.vx;
                break;

            case 1:
                entry->pos.vx = work->max.vx;
                break;

            case 2:
                entry->pos.vy = work->min.vy;
                break;

            case 3:
                entry->pos.vy = work->max.vy;
                break;

            case 4:
                entry->pos.vz = work->min.vz;
                break;

            case 5:
                entry->pos.vz = work->max.vz;
                break;
            }
        }

        Snow_800C547C(&entry->f8, GM_lpsvectWind, &work->f38);
        GV_AddVec3(GM_lpsvectWind, &work->f38, &entry->f8);
    }
    else
    {
        Snow_800C547C(&entry->f8, &work->f30, &work->f38);
        GV_AddVec3(&work->f30, &work->f38, &entry->f8);
    }

    vec = entry->vecs;
    for (i = 32; i > 0; i--)
    {
        Snow_800C53A0(vec, -3000, 3000, -3000, 3000, -3000, 3000);
        vec++;
    }
}

void Snow_800C592C(Work *work)
{
    int     n_msgs;
    GV_MSG *msg;

    n_msgs = GV_ReceiveMessage(GV_StrCode("雪"), &work->msgs);
    if (n_msgs <= 0)
    {
        return;
    }

    msg = work->msgs;
    while (--n_msgs >= 0)
    {
        switch (msg->message[0])
        {
        case HASH_ON:
            work->f2554 = 1;
            break;

        case HASH_OFF:
            work->f2554 = 0;
            break;

        default:
            work->f2550 = msg->message[0];
            break;
        }

        msg++;
    }
}

int Snow_800C59C8(Work *work, SnowEntry *entry)
{
    SVECTOR  target;
    SVECTOR  scaled;
    SVECTOR  front;
    SVECTOR *targetp;
    int      diff;

    GV_SubVec3(&gUnkCameraStruct2_800B7868.target, &gUnkCameraStruct2_800B7868.position, &front);
    GV_LenVec3(&front, &scaled, GV_VecLen3(&front), work->f2550);
    GV_AddVec3(&gUnkCameraStruct2_800B7868.position, &scaled, &target);

    targetp = &target;

    diff = entry->pos.vx - targetp->vx;
    if (diff >= (work->min.vx - 1000) && diff <= (work->max.vx + 1000))
    {
        diff = entry->pos.vy - targetp->vy;
        if (diff >= (work->min.vy - 1000) && diff <= (work->max.vy + 1000))
        {
            diff = entry->pos.vz - targetp->vz;
            if (diff >= (work->min.vz - 1000) && diff <= (work->max.vz + 1000))
            {
                return 0;
            }
        }
    }

    Snow_800C5544(work, entry, 1, targetp);
    return 1;
}

// FIXME: relocatable asm; the C version below differs in the register allocation (work/n_entries swapped)
void SnowAct(Work *work);
#pragma INCLUDE_ASM_RELOC("source/thing/vr/reloc/SnowAct.s")
#if 0 /* NON_MATCHING */
void SnowAct(Work *work)
{
    int        n_entries;
    SnowEntry *entry;

    if (GM_lpsvectWind == NULL)
    {
        work->f2548 = 0;
    }
    else if (work->f2548 != 1)
    {
        work->f2548 = 1;
    }

    entry = work->entries;

    Snow_800C592C(work);

    n_entries = work->n_entries;

    while (n_entries > 0)
    {
        if (work->f2554 == 0)
        {
            DG_InvisiblePrim(entry->prim);
            entry++;
        }
        else
        {
            DG_VisiblePrim(entry->prim);

            if (!Snow_800C59C8(work, entry))
            {
                GV_AddVec3(&entry->pos, &entry->f8, &entry->pos);
                GV_AddVec3(&entry->rot, &entry->f18, &entry->rot);
            }

            DG_SetPos2(&entry->pos, &entry->rot);

            if (work->f254C != 0)
            {
                Snow_800C5234(entry->prim->packs[GV_Clock], 32, work->colors);
            }

            DG_PutPrim(entry->prim);
            entry++;
        }

        n_entries--;
    }
}
#endif

void SnowDie(Work *work)
{
    int        n_entries;
    SnowEntry *entry;

    n_entries = work->n_entries;
    entry = work->entries;

    while (n_entries > 0)
    {
        GM_FreePrim(entry->prim);

        n_entries--;
        entry++;
    }
}

// FIXME: relocatable asm; the original keeps (n_entries + 31) / 32 unfolded and stores the constants in another order
void SnowGetOptions(Work *work);
#pragma INCLUDE_ASM_RELOC("source/thing/vr/reloc/SnowGetOptions.s")
#if 0 /* NON_MATCHING */
void SnowGetOptions(Work *work)
{
    int n_entries;
    int x, y, z;
    int var_a2;

    work->min = snow_svec_800C3854;
    work->max = snow_svec_800C385C;
    work->f30 = snow_svec_800C3864;
    work->f38 = DG_ZeroVector;

    work->n_entries = 32;

    work->min.vx = -5000;
    work->min.vy = 0;
    work->min.vz = -5000;
    work->max.vx = 5000;
    work->max.vy = 5000;
    work->max.vz = 5000;
    work->f30.vx = 50;
    work->f30.vy = -400;
    work->f30.vz = 0;
    work->f38.vx = 0;
    work->f38.vy = -200;
    work->f38.vz = 0;

    n_entries = 256;
    work->n_entries = (n_entries + 31) / 32;

    x = work->f30.vx;
    y = work->f30.vy;
    z = work->f30.vz;

    if (x < 0)
    {
        x = -x;
    }

    if (y < 0)
    {
        y = -y;
    }

    if (z < 0)
    {
        z = -z;
    }

    var_a2 = 2;
    if (x >= y)
    {
        if (x >= z)
        {
            var_a2 = 0;
            z = x;
        }
    }
    else if (y >= z)
    {
        var_a2 = 1;
        z = y;
    }

    work->f44 = var_a2 * 2 + (z > 0);
}
#endif

int SnowGetResources(Work *work, int map)
{
    SnowEntry *entry;
    int        n_entries;
    DG_PRIM   *prim;

    GM_CurrentMap = map;

    Snow_800C5260(work->colors, 32);

    entry = work->entries;
    for (n_entries = work->n_entries; n_entries > 0; n_entries--)
    {
        prim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_TILE, 32, entry->vecs, &snow_rect_800C386C);
        entry->prim = prim;
        if (prim == NULL)
        {
            return -1;
        }

        Snow_800C52F0(prim->packs[0], prim->packs[1], 32, work->colors);
        setSemiTrans((TILE *)prim->packs[0], 1);
        setSemiTrans((TILE *)prim->packs[1], 1);
        Snow_800C5544(work, entry, 0, &GM_WhereList[0]->mov);

        entry++;
    }

    work->f2554 = 1;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSnow(int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        SnowGetOptions(work);

        GV_SetNamedActor(&work->actor, SnowAct, SnowDie, "rain.c");

        if (SnowGetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
#endif
