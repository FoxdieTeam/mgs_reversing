#include "snowarea.h"

#include <stdlib.h>
#include "game/game.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "strcode.h"

/*----------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_USER

#define SNOWFLAKE_MAX 32

typedef struct _SnowFlake
{
    SVECTOR    pos;
    SVECTOR    f8;
    SVECTOR    rot;
    SVECTOR    f18;
    DG_PRIM   *prim;
    SVECTOR    vecs[SNOWFLAKE_MAX];
} SnowFlake;

typedef struct _Work
{
    GV_ACT     actor;
    SVECTOR    min;
    SVECTOR    max;
    SVECTOR    f30;
    SVECTOR    f38;
    int        n_entries;
    int        f44;
    SnowFlake  entries[SNOWFLAKE_MAX];
    int        colors[SNOWFLAKE_MAX];
    BOOL       is_visible;
    GV_MSG    *msgs;
} Work;

static RECT    snowflake_rect_800C359C = {0, 0, 2, 2};

/*----------------------------------------------------------------------------*/

void ColourEntries(int *colors, int n_colors)
{
    TILE tile;
    int  color;
    int  shade;

    setTile(&tile);
    color = LLOAD(&tile.r0) & RGBA_A_MASK;

    while (--n_colors >= 0)
    {
        shade = GV_RandU(64) + 192;
        *colors++ = color | shade / 2 | (shade / 2) << 8 | shade << 16;
    }
}

void LightEntries(TILE *packs1, TILE *packs2, int n_packs, int *colors)
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

void PositionEntry(SVECTOR *dst, int x0, int x1, int y0, int y1, int z0, int z1)
{
    dst->vx = ((rand() & 0xFF) * (x1 - x0)) / 256 + x0;
    dst->vy = ((rand() & 0xFF) * (y1 - y0)) / 256 + y0;
    dst->vz = ((rand() & 0xFF) * (z1 - z0)) / 256 + z0;
}

void ScaleEntry(SVECTOR *dst, SVECTOR *src, SVECTOR *scale)
{
    dst->vx = src->vx + ((rand() & 0xFF) * scale->vx) / 256;
    dst->vy = src->vy + ((rand() & 0xFF) * scale->vy) / 256;
    dst->vz = src->vz + ((rand() & 0xFF) * scale->vz) / 256;
}

void MoveEntry(Work* work, SnowFlake* entry, BOOL is_falling) {
    SVECTOR *vec;
    int      i;

    PositionEntry(&entry->pos, work->min.vx, work->max.vx, work->min.vy,
                               work->max.vy, work->min.vz, work->max.vz);

    if (is_falling)
    {
        entry->pos.vy = work->max.vy - GV_RandU(256);
    }

    PositionEntry(&entry->f18, -8, 8, -8, 8, -8, 8);

    entry->rot = DG_ZeroVector;

    ScaleEntry(&entry->f8, &work->f30, &work->f38);
    GV_AddVec3(&work->f30, &work->f38, &entry->f8);

    vec = entry->vecs;
    for (i = SNOWFLAKE_MAX; i > 0; i--)
    {
        PositionEntry(vec, -1500, 1500, -1500, 1500, -1500, 1500);
        vec++;
    }
}

void ReceiveMessage(Work *work)
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
            work->is_visible = TRUE;
            break;

        case HASH_OFF:
            work->is_visible = FALSE;
            break; 

        default:
            break;
        }

        msg++;
    }
}

int CheckEntryBounds(Work* work, SnowFlake* entry)
{
    if (entry->pos.vy < work->min.vy - 1000 || work->max.vy + 1000 < entry->pos.vy)
    {
        MoveEntry(work, entry, TRUE);
        return TRUE;
    }
    return FALSE;
}

void Act(Work *work)
{
    SnowFlake *entry;
    int        n_entries;

    entry = work->entries;

    ReceiveMessage(work);

    n_entries = work->n_entries;

    while (n_entries > 0)
    {
        if (work->is_visible == FALSE)
        {
            DG_InvisiblePrim(entry->prim);
            entry++;
        }
        else
        {
            DG_VisiblePrim(entry->prim);

            if (CheckEntryBounds(work, entry) == FALSE)
            {
                entry->pos.vy += GV_RandS(2);
                GV_AddVec3(&entry->pos, &entry->f8, &entry->pos);
                GV_AddVec3(&entry->rot, &entry->f18, &entry->rot);
            }

            DG_SetPos2(&entry->pos, &entry->rot);
            DG_PutPrim(entry->prim);

            entry++;
        }

        n_entries--;
    }
}

void Die(Work *work)
{
    int        n_entries;
    SnowFlake *entry;

    n_entries = work->n_entries;
    entry = work->entries;

    while (n_entries > 0)
    {
        GM_FreePrim(entry->prim);

        n_entries--;
        entry++;
    }
}

void GetOptions(Work *work)
{
    char *opt;
    int  n_entries;
    int  x, y, z;
    int  var_a2;

    work->n_entries = SNOWFLAKE_MAX;

    if ((opt = GCL_GetOption('l')))
    {
        GCL_StrToSV(opt, (short *)&work->min);
    }

    if ((opt = GCL_GetOption('h')))
    {
        GCL_StrToSV(opt, (short *)&work->max);
    }

    if ((opt = GCL_GetOption('s')))
    {
        GCL_StrToSV(opt, (short *)&work->f30);
    }

    if ((opt = GCL_GetOption('w')))
    {
        GCL_StrToSV(opt, (short *)&work->f38);
    }

    if ((opt = GCL_GetOption('n')))
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

        work->n_entries = (n_entries + SNOWFLAKE_MAX - 1) / SNOWFLAKE_MAX;
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

int GetResources(Work *work, int map)
{
    SnowFlake *entry;
    int        n_entries;
    DG_PRIM   *prim;

    GM_CurrentMap = map;
    ColourEntries(work->colors, SNOWFLAKE_MAX);
    entry = work->entries;
    for (n_entries = work->n_entries; n_entries > 0; n_entries--)
    {
        prim = GM_MakePrim(DG_PRIM_RECTANGLE | DG_PRIM_TILE, SNOWFLAKE_MAX, entry->vecs, &snowflake_rect_800C359C);
        entry->prim = prim;
        if (prim == NULL)
        {
            return -1;
        }
        LightEntries(prim->packs[0], prim->packs[1], SNOWFLAKE_MAX, work->colors);
        MoveEntry(work, entry, FALSE);
        
        entry++;
    }
    work->is_visible = TRUE;
    return 0;
}

void *NewSnowArea(int name, int where, int argc, char **argv) {
    Work* work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL) {
        GetOptions(work);
        GV_SetNamedActor(&work->actor, Act, Die, "snowarea.c");
        if (GetResources(work, where) < 0) {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
