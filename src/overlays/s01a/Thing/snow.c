#include "psyq.h"
#include "libdg/libdg.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/camera.h"

typedef struct _SnowEntry
{
    SVECTOR  pos;
    SVECTOR  f8;
    SVECTOR  rot;
    SVECTOR  f18;
    DG_PRIM *prim;
    SVECTOR  vecs[32];
} SnowEntry;

typedef struct _SnowWork
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
} SnowWork;

extern SVECTOR          DG_ZeroVector_800AB39C;
extern SVECTOR         *GM_lpsvectWind_800AB3D8;
extern int              GV_Clock_800AB920;
extern int              GM_CurrentMap_800AB9B0;
extern CONTROL         *GM_WhereList_800B56D0[96];
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

SVECTOR snow_svec_800C3854 = {-5000, 0, -10000, 0};
SVECTOR snow_svec_800C385C = {5000, 8000, 10000, 0};
SVECTOR snow_svec_800C3864 = {0, -50, 0, 0};
RECT    snow_rect_800C386C = {0, 0, 2, 2};

#define EXEC_LEVEL 5

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
    color = LLOAD(&tile.r0) & 0xFF000000;

    while (--n_colors >= 0)
    {
        shade = GV_RandU(128) + 128;
        *colors++ = color | shade / 2 | (shade / 2) << 8 | shade << 16;
    }
}

void Snow_800C52F0(TILE *packs1, TILE *packs2, int n_packs, int *colors)
{
    int rnd;

    while (--n_packs >= 0)
    {
        rnd = GV_RandU(2) + 1;

        setTile(packs1);
        LSTORE(*colors, &packs1->r0);
        setWH(packs1, rnd, rnd);

        setTile(packs2);
        LSTORE(*colors, &packs2->r0);
        setWH(packs2, rnd, rnd);

        packs1++;
        packs2++;
        colors++;
    }
}

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

void Snow_800C5544(SnowWork *work, SnowEntry *entry, int arg2, SVECTOR *target)
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

    entry->rot = DG_ZeroVector_800AB39C;

    if (GM_lpsvectWind_800AB3D8 != NULL)
    {
        if (work->f2548 == 1)
        {
            wind = *GM_lpsvectWind_800AB3D8;

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

        Snow_800C547C(&entry->f8, GM_lpsvectWind_800AB3D8, &work->f38);
        GV_AddVec3(GM_lpsvectWind_800AB3D8, &work->f38, &entry->f8);
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

void Snow_800C592C(SnowWork *work)
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

int Snow_800C59C8(SnowWork *work, SnowEntry *entry)
{
    SVECTOR  target;
    SVECTOR  scaled;
    SVECTOR  front;
    SVECTOR *targetp;
    int      diff;

    GV_SubVec3(&gUnkCameraStruct2_800B7868.center, &gUnkCameraStruct2_800B7868.eye, &front);
    GV_LenVec3(&front, &scaled, GV_VecLen3(&front), work->f2550);
    GV_AddVec3(&gUnkCameraStruct2_800B7868.eye, &scaled, &target);

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

void SnowAct_800C5B2C(SnowWork *work)
{
    SnowEntry *entry;
    int        n_entries;

    if (GM_lpsvectWind_800AB3D8 == NULL)
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

            DG_SetPos2_8001BC8C(&entry->pos, &entry->rot);

            if (work->f254C != 0)
            {
                Snow_800C5234(&entry->prim->packs[GV_Clock_800AB920]->tiles, 32, work->colors);
            }

            DG_PutPrim_8001BE00(&entry->prim->world);
            entry++;
        }

        n_entries--;
    }
}

void SnowDie_800C5C6C(SnowWork *work)
{
    int        n_entries;
    SnowEntry *entry;
    DG_PRIM   *prim;

    n_entries = work->n_entries;
    entry = work->entries;

    while (n_entries > 0)
    {
        prim = entry->prim;
        if (prim != NULL)
        {
            DG_DequeuePrim_800182E0(prim);
            DG_FreePrim_8001BC04(prim);
        }

        n_entries--;
        entry++;
    }
}

void SnowGetOptions_800C5CD4(SnowWork *work)
{
    char *opt;
    int n_entries;
    int x, y, z;
    int var_a2;

    work->min = snow_svec_800C3854;
    work->max = snow_svec_800C385C;
    work->f30 = snow_svec_800C3864;
    work->f38 = DG_ZeroVector_800AB39C;

    work->n_entries = 32;

    opt = GCL_GetOption('l');
    if (opt != NULL)
    {
        GCL_StrToSV(opt, &work->min);
    }

    opt = GCL_GetOption('h');
    if (opt != NULL)
    {
        GCL_StrToSV(opt, &work->max);
    }

    opt = GCL_GetOption('s');
    if (opt != NULL)
    {
        GCL_StrToSV(opt, &work->f30);
    }

    opt = GCL_GetOption('w');
    if (opt != NULL)
    {
        GCL_StrToSV(opt, &work->f38);
    }

    opt = GCL_GetOption('n');
    if (opt != NULL)
    {
        n_entries = GCL_StrToInt(opt);

        if (n_entries <= 0)
        {
            n_entries = 1;
        }

        if (n_entries > 1024)
        {
            n_entries = 1024;
        }

        work->n_entries = (n_entries + 31) / 32;
    }

    work->f2550 = 6000;
    if (GCL_GetOption('c'))
    {
        work->f2550 = GCL_StrToInt(GCL_GetParamResult());
    }

    if (GCL_GetOption('f'))
    {
        work->f254C = GCL_StrToInt(GCL_GetParamResult());
    }

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

int SnowGetResources_800C5F40(SnowWork *work, int map)
{
    SnowEntry *entry;
    int        n_entries;
    DG_PRIM   *prim;

    GM_CurrentMap_800AB9B0 = map;

    Snow_800C5260(work->colors, 32);

    entry = work->entries;
    for (n_entries = work->n_entries; n_entries > 0; n_entries--)
    {
        prim = DG_GetPrim(0x409, 32, 0, entry->vecs, &snow_rect_800C386C);
        entry->prim = prim;
        if (prim == NULL)
        {
            return -1;
        }

        Snow_800C52F0(&prim->packs[0]->tiles, &prim->packs[1]->tiles, 32, work->colors);
        Snow_800C5544(work, entry, 0, &GM_WhereList_800B56D0[0]->mov);

        entry++;
    }

    work->f2554 = 1;
    return 0;
}

GV_ACT * NewSnow_800C6058(int name, int where, int argc, char **argv)
{
    SnowWork *work;

    work = (SnowWork *)GV_NewActor(EXEC_LEVEL, sizeof(SnowWork));
    if (work != NULL)
    {
        SnowGetOptions_800C5CD4(work);

        GV_SetNamedActor(&work->actor, (TActorFunction)SnowAct_800C5B2C, (TActorFunction)SnowDie_800C5C6C, "snow.c");

        if (SnowGetResources_800C5F40(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
