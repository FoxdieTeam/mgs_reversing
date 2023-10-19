#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Okajima/blood.h"

typedef struct _MouseEntry
{
    TARGET *target;
    OBJECT  object;
    SVECTOR rots[24];
    MATRIX  light[2];
    int     has_target;
    int     f12C;
    int     f130;
    char    pad[0x8];
    SVECTOR f13C;
    SVECTOR f144;
    char    f14C[0x8];
    SVECTOR f154;
    char    f15C[0x8];
    SVECTOR f164;
    char    f16C[0x2];
    short   f16E;
    char    f170[0xC];
    int     f17C;
    int     f180;
    int     f184;
} MouseEntry;

typedef struct _MouseWork
{
    GV_ACT     actor;
    int        nvertices;
    int        nentries;
    int        f28;
    int        f2C;
    int        f30;
    SVECTOR    f34[31];
    int        f12C;
    int        f130;
    int        f134[32];
    int        f1B4;
    int        f1B8;
    int        map;
    char       f1C0[0x4];
    int        name;
    char       f1C8[0x8];
    int        f1D0;
    int        scale;
    int        f1D8;
    int        f1DC;
    MouseEntry entries[0];
} MouseWork;

extern MATRIX DG_ZeroMatrix_8009D430;
extern int    GM_CurrentMap_800AB9B0;

extern const char aMouse[];  // = "mouse"
extern const char aMouseC[]; // = "mouse.c"

#define EXEC_LEVEL 4

void s00a_mouse_800D3B68(MouseWork *, OBJECT *);
int  s00a_mouse_800D3C30(int, SVECTOR *);
void s00a_mouse_800D4840(MouseWork *);

void s00a_mouse_800D4904(MouseWork *work)
{
    MATRIX      sp10;
    SVECTOR     sp30;
    MouseEntry *entry;
    int         i;
    TARGET     *target;
    OBJECT     *object;

    GM_CurrentMap_800AB9B0 = work->map;

    entry = work->entries;
    for (i = 0; i < work->nentries; i++, entry++)
    {
        if (entry->has_target == 1)
        {
            target = entry->target;

            sp30 = entry->f164;
            GM_Target_SetVector_8002D500(target, &sp30);

            if (target->field_6_flags & TARGET_POWER && entry->f17C != 3)
            {
                entry->f17C = 3;
                entry->f180 = 0;

                sp10 = DG_ZeroMatrix_8009D430;
                sp10.t[0] = sp30.vx;
                sp10.t[1] = sp30.vy;
                sp10.t[2] = sp30.vz;
                NewBlood_80072728(&sp10, 1);
            }
        }

        DG_SetPos2_8001BC8C(&sp30, &entry->f154);

        object = &entry->object;
        DG_VisibleObjs(entry->object.objs);
        GM_ActObject2_80034B88(object);

        if (work->f1D0 != 0)
        {
            entry->object.objs->light->t[0] = 64;
            entry->object.objs->light->t[1] = 64;
            entry->object.objs->light->t[2] = 64;
            DG_AmbientObjs(entry->object.objs);
        }
        else
        {
            DG_UnAmbientObjs(entry->object.objs);
        }

        s00a_mouse_800D3B68(work, object);

        if (GM_CurrentItemId == ITEM_THERM_G)
        {
            DG_AmbientObjs(object->objs);
            DG_GetLightMatrix2_8001A5D8(&sp30, entry->light);
        }

        work->f1B8 = i;
        s00a_mouse_800D4840(work);
    }
}

int s00a_mouse_800D4B60(MouseWork *work, int name, int unused)
{
    SVECTOR     diff;
    SVECTOR     scale;
    int         opt;
    MAP        *map;
    HZD_PAT    *route;
    HZD_PTP    *point;
    int         i;
    MouseEntry *entry;
    TARGET     *target;
    SVECTOR    *prev;
    SVECTOR    *next;
    int         dx, dz;

    work->name = name;

    opt = GCL_GetOption_80020968('r');
    if (opt != 0)
    {
        work->f28 = GCL_StrToInt_800209E8((char *)opt);
        if (work->f28 <= 0)
        {
            work->f28 = 1;
        }
    }
    else
    {
        work->f28 = 1;
    }

    opt = GCL_GetOption_80020968('l');
    if (opt != 0)
    {
        work->f2C = GCL_StrToInt_800209E8((char *)opt) + 1;
    }

    opt = GCL_GetOption_80020968('d');
    if (opt != 0)
    {
        work->f30 = GCL_StrToInt_800209E8((char *)opt);
    }

    opt = GCL_GetOption_80020968('v');
    if (opt != 0)
    {
        work->nvertices = s00a_mouse_800D3C30(opt, work->f34);
    }
    else
    {
        work->nvertices = 0;
    }

    opt = GCL_GetOption_80020968('w');
    if (opt != 0)
    {
        work->f1D0 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f1D0 = 0;
    }

    opt = GCL_GetOption_80020968('s');
    if (opt != 0)
    {
        work->scale = GCL_StrToInt_800209E8((char *)opt);
        if (work->scale > 24576)
        {
            work->scale = 24576;
        }
    }
    else
    {
        work->scale = 4096;
    }

    map = Map_FromId_800314C0(work->map);

    opt = GCL_GetOption_80020968('n');
    if (opt != 0)
    {
        work->f1B4 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f1B4 = 0;
    }

    if ((work->f1B4 + 1) > map->field_8_hzd->f00_header->n_routes)
    {
        work->f1B4 = 0;
    }

    route = &map->field_8_hzd->f00_header->routes[work->f1B4];

    work->nvertices = route->n_points;
    if (work->nvertices <= 0)
    {
        return -1;
    }
    else if (work->nvertices >= 32)
    {
        return -1;
    }

    point = route->points;
    for (i = 0; i < work->nvertices; i++)
    {
        work->f34[i].vx = point->x;
        work->f34[i].vy = point->y;
        work->f34[i].vz = point->z;
        point++;
    }

    for (i = 0; i < work->nentries; i++)
    {
        entry = &work->entries[i];

        entry->f12C = 0;
        entry->f17C = 0;
        entry->f180 = 0;
        entry->f184 = 0;
        entry->f130 = 1;

        entry->f13C.vx = work->f34[entry->f12C].vx;
        entry->f13C.vy = work->f34[entry->f12C].vy;
        entry->f13C.vz = work->f34[entry->f12C].vz;

        entry->f164.vx = entry->f13C.vx;
        entry->f164.vy = entry->f13C.vy;
        entry->f164.vz = entry->f13C.vz;

        entry->f144.vx = work->f34[entry->f130].vx;
        entry->f144.vy = work->f34[entry->f130].vy;
        entry->f144.vz = work->f34[entry->f130].vz;

        GV_SubVec3_80016D40(&entry->f144, &entry->f13C, &diff);
        entry->f16E = ratan2(diff.vx, diff.vz) & 0xFFF;

        entry->target = target = GM_AllocTarget_8002D400();
        if (target)
        {
            entry->has_target = 1;

            scale.vx = (work->scale * 100) / 4096;
            scale.vy = (work->scale * 100) / 4096;
            scale.vz = (work->scale * 100) / 4096;

            GM_SetTarget_8002DC74(target, TARGET_SEEK | TARGET_POWER | TARGET_AVAIL, ENEMY_SIDE, &scale);
        }
        else
        {
            entry->has_target = 0;
        }
    }

    for (i = 0; i < work->nvertices; i++)
    {
        work->f134[i] = 0;

        if (i == work->nvertices - 2)
        {
            prev = &work->f34[i + 1];
            next = &work->f34[0];
        }
        else if (i == work->nvertices - 1)
        {
            prev = &work->f34[0];
            next = &work->f34[1];
        }
        else
        {
            prev = &work->f34[i + 1];
            next = &work->f34[i + 2];
        }

        if (next->vy != prev->vy)
        {
            dx = next->vx - prev->vx;
            if (dx < 0)
            {
                dx = -dx;
            }

            dz = next->vz - prev->vz;
            if (dz < 0)
            {
                dz = -dz;
            }

            if (dx < dz)
            {
                work->f134[i] = 1;
            }
            else
            {
                work->f134[i] = 2;
            }
        }

        prev = &work->f34[i];
        if (i == (work->nvertices - 1))
        {
            next = &work->f34[0];
        }
        else
        {
            next = &work->f34[i + 1];
        }

        if (next->vy != prev->vy)
        {
            dx = next->vx - prev->vx;
            if (dx < 0)
            {
                dx = -dx;
            }

            dz = next->vz - prev->vz;
            if (dz < 0)
            {
                dz = -dz;
            }

            if (dx < dz)
            {
                work->f134[i] = 1;
            }
            else
            {
                work->f134[i] = 2;
            }
        }
    }

    opt = GCL_GetOption_80020968('k');
    if (opt != 0)
    {
        work->f1D8 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f1D8 = -1;
    }

    opt = GCL_GetOption_80020968('h');
    if (opt != 0)
    {
        work->f1DC = 1;
    }
    else
    {
        work->f1DC = 0;
    }

    return 0;
}

int s00a_mouse_800D50F4(MouseWork *work, int name, int map)
{
    int         i;
    MouseEntry *entry;
    OBJECT     *object;
    int         model;

    work->map = map;

    for (i = 0; i < work->nentries; i++)
    {
        entry = &work->entries[i];
        object = &entry->object;

        model = GV_StrCode_80016CCC(aMouse);
        GM_InitObject_80034A18(object, model, 0x26D, 0);

        GM_ConfigObjectJoint_80034CB4(object);
        GM_ConfigObjectLight_80034C44(object, entry->light);
    }

    return 0;
}

void s00a_mouse_800D51A4(MouseWork *work)
{
    int i;

    for (i = 0; i < work->nentries; i++)
    {
        GM_FreeObject_80034BF8(&work->entries[i].object);

        if (work->entries[i].has_target)
        {
            GM_FreeTarget_8002D4B0(work->entries[i].target);
        }
    }
}

GV_ACT * s00a_mouse_800D5234(int name, int where)
{
    int        opt;
    int        nentries;
    MouseWork *work;

    opt = GCL_GetOption_80020968('m');
    if (opt != 0)
    {
        nentries = GCL_StrToInt_800209E8((char *)opt);

        if (nentries > 16)
        {
            nentries = 16;
        }
    }
    else
    {
        nentries = 1;
    }

    work = (MouseWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(MouseWork) + sizeof(MouseEntry) * nentries);
    if (work != NULL)
    {
        work->nentries = nentries;
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_mouse_800D4904, (TActorFunction)s00a_mouse_800D51A4, aMouseC);

        if (s00a_mouse_800D50F4(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        s00a_mouse_800D4B60(work, name, where);
    }

    return &work->actor;
}
