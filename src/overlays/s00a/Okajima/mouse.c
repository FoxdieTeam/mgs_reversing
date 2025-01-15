#include "mouse.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Okajima/blood.h"
#include "SD/g_sound.h"
#include "strcode.h"

typedef struct _MouseEntry
{
    TARGET *target;
    OBJECT  object;
    MATRIX  light[2];
    int     has_target;
    int     f12C;
    int     f130;
    int     f134;
    int     f138;
    SVECTOR f13C;
    SVECTOR f144;
    SVECTOR f14C;
    SVECTOR f154;
    char    f15C[0x8];
    SVECTOR f164;
    SVECTOR f16C;
    int     f174;
    int     f178;
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
    SVECTOR    f34[32];
    int        f134[32];
    int        f1B4;
    int        f1B8;
    int        map;
    char       f1C0[0x4];
    int        name;
    char       f1C8[0x8];
    int        f1D0;
    int        scale;
    int        proc;
    int        f1DC;
    MouseEntry entries[0];
} MouseWork;

extern int    GM_CurrentMap_800AB9B0;
extern int    GM_PlayerStatus;

#define EXEC_LEVEL 4

void s00a_mouse_800D3B68(MouseWork *work, OBJECT *object)
{
    VECTOR scale;

    scale.vx = work->scale;
    scale.vy = work->scale;
    scale.vz = work->scale;
    ScaleMatrix(&object->objs->world, &scale);
}

void s00a_mouse_800D3BB0(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *out)
{
    SVECTOR diff;
    int     y;

    GV_SubVec3(vec2, vec1, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    out->vx = (ratan2(GV_VecLen3(&diff), y) & 0xFFF) - 1024;
    out->vz = 0;
}

int s00a_mouse_800D3C30(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(result, svec);

        svec++;
        count++;
    }

    return count;
}

void s00a_mouse_800D3C84(MouseWork *work)
{
    SVECTOR     sp10;
    MouseEntry *entry;

    entry = &work->entries[work->f1B8];

    switch (entry->f180)
    {
    case 0:
        s00a_mouse_800D3BB0(&entry->f13C, &entry->f144, &sp10);

        entry->f138 = 8;
        entry->f134 = entry->f138 + GV_RandU(16);
        if (entry->f134 == 0)
        {
            entry->f134 = 1;
        }

        entry->f184 = 0;
        entry->f180 = 1;

        entry->f174 = FP_Extend(sp10.vy - entry->f154.vy) / entry->f134;
        entry->f178 = FP_Extend(sp10.vx - entry->f154.vx) / entry->f134;
        /* fallthrough */

    case 1:
        if (--entry->f138 > 0)
        {
            entry->f154.vy += entry->f174;
            entry->f154.vx += entry->f178;
            entry->f16C = entry->f154;
        }

        if (entry->f184 >= entry->f134)
        {
            entry->f17C = 1;
            entry->f180 = 0;
        }
        break;

    case 7:
        entry->f17C = 0;
        entry->f180 = 0;
        DG_VisibleObjs(entry->object.objs);
        break;
    }
}

void s00a_mouse_800D3E9C(MouseWork *work)
{
    SVECTOR     sp10;
    MouseEntry *entry;
    SVECTOR    *next;
    SVECTOR    *prev;

    entry = &work->entries[work->f1B8];

    next = &entry->f144;
    prev = &entry->f13C;

    switch (entry->f180)
    {
    case 0:
        if (entry->object.objs->bound_mode == 2 &&
            GV_RandU(2) == 0 &&
            GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_FIRST_PERSON))
        {
            if (work->f1DC != 0)
            {
                GM_SeSet(&entry->f164, 190);
            }
            else
            {
                GM_SeSet(&entry->f164, SE_MOUSE_STEP);
            }
        }

        entry->f134 = work->f2C + GV_RandS(16);
        if (entry->f134 == 0)
        {
            entry->f134 = 1;
        }

        entry->f184 = 0;
        entry->f180 = 2;

        switch (work->f134[entry->f12C])
        {
        case 0:
            entry->f14C.vx = ((next->vx - prev->vx) + (GV_RandS(4096) % work->f28)) / entry->f134;
            entry->f14C.vy = (next->vy - prev->vy) / entry->f134;
            entry->f14C.vz = ((next->vz - prev->vz) + (GV_RandS(4096) % work->f28)) / entry->f134;
            break;

        case 1:
            entry->f14C.vx = ((next->vx - prev->vx) + (GV_RandS(4096) % work->f28)) / entry->f134;
            entry->f14C.vy = (next->vy - prev->vy) / entry->f134;
            entry->f14C.vz = (next->vz - prev->vz) / entry->f134;
            break;

        case 2:
            entry->f14C.vx = (next->vx - prev->vx) / entry->f134;
            entry->f14C.vy = (next->vy - prev->vy) / entry->f134;
            entry->f14C.vz = ((next->vz - prev->vz) + (GV_RandS(4096) % work->f28)) / entry->f134;
            break;
        }

        sp10.vx = entry->f164.vx + entry->f14C.vx;
        sp10.vy = entry->f164.vy + entry->f14C.vy;
        sp10.vz = entry->f164.vz + entry->f14C.vz;
        s00a_mouse_800D3BB0(&entry->f164, &sp10, &entry->f16C);
        /* fallthrough */

    case 2:
        if (entry->f184 >= entry->f134)
        {
            entry->f17C = 2;
            entry->f180 = 0;
            return;
        }

        entry->f164.vx += entry->f14C.vx;
        entry->f164.vy += entry->f14C.vy;
        entry->f164.vz += entry->f14C.vz;

        entry->f154 = entry->f16C;

        switch (entry->f184 % 4)
        {
        case 0:
            entry->f154.vy -= 128;
            break;

        case 2:
            entry->f154.vy += 128;
            break;
        }
        break;
    }
}

void s00a_mouse_800D4350(MouseWork *work)
{
    MouseEntry *entry;

    entry = &work->entries[work->f1B8];

    if (entry->f180 == 0 || entry->f180 == 3)
    {
        entry->f184 = 0;
        entry->f17C = 0;
        entry->f180 = 0;

        entry->f12C = entry->f130;

        if (++entry->f130 >= work->nvertices)
        {
            entry->f130 = 0;
        }

        entry->f13C.vx = entry->f164.vx;
        entry->f13C.vy = entry->f164.vy;
        entry->f13C.vz = entry->f164.vz;

        entry->f144.vx = work->f34[entry->f130].vx;
        entry->f144.vy = work->f34[entry->f130].vy;
        entry->f144.vz = work->f34[entry->f130].vz;
    }
}

void s00a_mouse_800D4430(MouseWork *work)
{
    MATRIX      sp10;
    SVECTOR     diff;
    MouseEntry *entry;
    int         height;
    int         yaw;
    int         y;
    int         pitch;

    entry = &work->entries[work->f1B8];

    switch (entry->f180)
    {
    case 0:
        if (work->f1DC != 0)
        {
            GM_SeSet2(0, 127, 191);
        }
        else if (GM_CurrentStageFlag != HASH_s00a)
        {
            GM_SeSet2(0, 127, 176);
        }

        entry->f180 = 4;
        entry->f184 = 0;
        entry->f154.vx -= GV_RandS(4096);
        entry->f154.vy -= GV_RandS(4096);
        entry->f154.vz -= GV_RandS(4096);

        RotMatrixYXZ_gte(&entry->f154, &sp10);

        sp10.t[0] = entry->f164.vx;
        sp10.t[1] = entry->f164.vy;
        sp10.t[2] = entry->f164.vz;

        if (work->proc != -1)
        {
            GCL_ExecProc(work->proc, NULL);
        }
        /* fallthrough */

    case 4:
        entry->f154.vx -= GV_RandS(256);
        entry->f154.vy -= GV_RandS(256);
        entry->f154.vz -= GV_RandS(256);

        RotMatrixYXZ_gte(&entry->f154, &sp10);

        height = (entry->f184 - 8) * 8;

        sp10.t[0] = entry->f164.vx;

        height = entry->f164.vy - height;
        sp10.t[1] = height;
        entry->f164.vy = height;

        sp10.t[2] = entry->f164.vz;

        if (entry->f184 >= 16)
        {
            entry->f180 = 5;
            entry->f184 = 0;
        }
        break;

    case 5:
        if ((entry->f184 % 4) >= 2)
        {
            DG_InvisibleObjs(entry->object.objs);
        }
        else
        {
            DG_VisibleObjs(entry->object.objs);
        }

        if (entry->f184 >= 64)
        {
            entry->f180 = 6;
            entry->f184 = 0;
        }
        break;

    case 6:
        DG_InvisibleObjs(entry->object.objs);

        if (work->f30 == 0)
        {
            entry->has_target = 0;
            GM_FreeTarget(entry->target);
            return;
        }

        if (entry->f184 >= 100)
        {
            entry->f17C = 0;
            entry->f180 = 7;

            entry->target->damaged &= ~TARGET_POWER;

            entry->f12C = 0;
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

            GV_SubVec3(&entry->f144, &entry->f13C, &diff);

            yaw = ratan2(diff.vx, diff.vz) & 0xFFF;
            entry->f16C.vy = yaw;
            entry->f154.vy = yaw;

            y = diff.vy;
            diff.vy = 0;

            pitch = ratan2(GV_VecLen3(&diff), y) & 0xFFF;

            entry->f16C.vx = pitch;
            entry->f154.vx = pitch;

            entry->f16C.vx -= 1024;
            if (entry->f16C.vx < 0)
            {
                entry->f16C.vx += 4096;
            }

            entry->f16C.vz = 0;
            entry->f154.vz = 0;

            GM_MoveTarget(entry->target, &entry->f164);
        }
        break;
    }
}

void MouseThink_800D4840(MouseWork *work)
{
    int index;

    index = work->f1B8;
    work->entries[index].f184++;

    switch (work->entries[index].f17C)
    {
    case 0:
        s00a_mouse_800D3C84(work);
        break;

    case 1:
        s00a_mouse_800D3E9C(work);
        break;

    case 2:
        s00a_mouse_800D4350(work);
        break;

    case 3:
        s00a_mouse_800D4430(work);
        break;
    }
}

void MouseAct_800D4904(MouseWork *work)
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
            GM_MoveTarget(target, &sp30);

            if (target->damaged & TARGET_POWER && entry->f17C != 3)
            {
                entry->f17C = 3;
                entry->f180 = 0;

                sp10 = DG_ZeroMatrix;
                sp10.t[0] = sp30.vx;
                sp10.t[1] = sp30.vy;
                sp10.t[2] = sp30.vz;
                NewBlood(&sp10, 1);
            }
        }

        DG_SetPos2(&sp30, &entry->f154);

        object = &entry->object;
        DG_VisibleObjs(entry->object.objs);
        GM_ActObject2(object);

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
            DG_GetLightMatrix2(&sp30, entry->light);
        }

        work->f1B8 = i;
        MouseThink_800D4840(work);
    }
}

int s00a_mouse_800D4B60(MouseWork *work, int name, int unused)
{
    SVECTOR     diff;
    SVECTOR     scale;
    char       *opt;
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

    opt = GCL_GetOption('r');
    if (opt != 0)
    {
        work->f28 = GCL_StrToInt(opt);
        if (work->f28 <= 0)
        {
            work->f28 = 1;
        }
    }
    else
    {
        work->f28 = 1;
    }

    opt = GCL_GetOption('l');
    if (opt != 0)
    {
        work->f2C = GCL_StrToInt(opt) + 1;
    }

    opt = GCL_GetOption('d');
    if (opt != 0)
    {
        work->f30 = GCL_StrToInt(opt);
    }

    opt = GCL_GetOption('v');
    if (opt != 0)
    {
        work->nvertices = s00a_mouse_800D3C30(opt, work->f34);
    }
    else
    {
        work->nvertices = 0;
    }

    opt = GCL_GetOption('w');
    if (opt != 0)
    {
        work->f1D0 = GCL_StrToInt(opt);
    }
    else
    {
        work->f1D0 = 0;
    }

    opt = GCL_GetOption('s');
    if (opt != 0)
    {
        work->scale = GCL_StrToInt(opt);
        if (work->scale > 24576)
        {
            work->scale = 24576;
        }
    }
    else
    {
        work->scale = 4096;
    }

    map = GM_GetMap(work->map);

    opt = GCL_GetOption('n');
    if (opt != 0)
    {
        work->f1B4 = GCL_StrToInt(opt);
    }
    else
    {
        work->f1B4 = 0;
    }

    if ((work->f1B4 + 1) > map->hzd->header->n_routes)
    {
        work->f1B4 = 0;
    }

    route = &map->hzd->header->routes[work->f1B4];

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

        GV_SubVec3(&entry->f144, &entry->f13C, &diff);
        entry->f16C.vy = ratan2(diff.vx, diff.vz) & 0xFFF;

        entry->target = target = GM_AllocTarget();
        if (target)
        {
            entry->has_target = 1;

            scale.vx = (work->scale * 100) / 4096;
            scale.vy = (work->scale * 100) / 4096;
            scale.vz = (work->scale * 100) / 4096;

            GM_SetTarget(target, TARGET_SEEK | TARGET_POWER | TARGET_AVAIL, ENEMY_SIDE, &scale);
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

    opt = GCL_GetOption('k');
    if (opt != 0)
    {
        work->proc = GCL_StrToInt(opt);
    }
    else
    {
        work->proc = -1;
    }

    opt = GCL_GetOption('h');
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

int MouseGetResources_800D50F4(MouseWork *work, int name, int map)
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

        model = GV_StrCode("mouse");
        GM_InitObject(object, model, 0x26D, 0);

        GM_ConfigObjectJoint(object);
        GM_ConfigObjectLight(object, entry->light);
    }

    return 0;
}

void MouseDie_800D51A4(MouseWork *work)
{
    int i;

    for (i = 0; i < work->nentries; i++)
    {
        GM_FreeObject(&work->entries[i].object);

        if (work->entries[i].has_target)
        {
            GM_FreeTarget(work->entries[i].target);
        }
    }
}

GV_ACT *NewMouse_800D5234(int name, int where, int argc, char **argv)
{
    char      *opt;
    int        nentries;
    MouseWork *work;

    opt = GCL_GetOption('m');
    if (opt != 0)
    {
        nentries = GCL_StrToInt(opt);

        if (nentries > 16)
        {
            nentries = 16;
        }
    }
    else
    {
        nentries = 1;
    }

    work = (MouseWork *)GV_NewActor(EXEC_LEVEL, sizeof(MouseWork) + sizeof(MouseEntry) * nentries);
    if (work != NULL)
    {
        work->nentries = nentries;
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)MouseAct_800D4904, (GV_ACTFUNC)MouseDie_800D51A4, "mouse.c");

        if (MouseGetResources_800D50F4(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        s00a_mouse_800D4B60(work, name, where);
    }

    return &work->actor;
}
