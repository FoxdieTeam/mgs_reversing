#include "map.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game.h"

extern MAP      gMapRecs_800B7910[ 16 ];
extern DG_OBJS *StageObjs_800B7890[ 32 ];
extern int      DG_CurrentGroupID;

STATIC MAP* SECTION(".sbss") pHzdIter_800ABAA0;
STATIC int  SECTION(".sbss") N_StageObjs_800ABAA4;
STATIC int  SECTION(".sbss") gMapCount_800ABAA8;
STATIC int  SECTION(".sbss") gMapsChanged_800ABAAC;

STATIC void GM_UpdateMapGroup( int preshade )
{
    MAP      *map;
    int       group, hzd_group;
    int       i, j;
    DG_OBJS **objs;
    LIT      *lit;

    map = gMapRecs_800B7910;

    group = 0;
    hzd_group = 0;

    DG_ResetFixedLight();

    for ( i = gMapCount_800ABAA8; i > 0; map++, i-- )
    {
        if ( !map->used )
        {
            continue;
        }

        objs = StageObjs_800B7890;
        group |= map->index;

        for ( j = N_StageObjs_800ABAA4; j > 0; j-- )
        {
            if ( map->index & objs[ 0 ]->group_id )
            {
                lit = map->lit;

                if ( lit )
                {
                    DG_SetFixedLight( lit->lights, lit->n_lights );

                    if ( preshade )
                    {
                        DG_MakePreshade( objs[ 0 ], lit->lights, lit->n_lights );
                    }
                }
                else
                {
                    DG_SetFixedLight( NULL, 0 );

                    if ( preshade )
                    {
                        DG_MakePreshade( objs[ 0 ], NULL, 0 );
                    }
                }
            }

            objs++;
        }

        hzd_group |= 1 << ( map->hzd->group - map->hzd->header->groups );
    }

    GM_PlayerMap = group;
    HZD_CurrentGroup = hzd_group;
    DG_CurrentGroupID = group;
    HZD_BindMapChange( group );
}

STATIC MAP *GM_GetNextMap(int name)
{
    int  i;
    MAP *map;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        map++;
    }

    map->name = name;
    map->used = 0;
    map->index = 1 << gMapCount_800ABAA8;

    gMapCount_800ABAA8++;
    return map;
}

#define MAP_FLAG (DG_FLAG_ONEPIECE | DG_FLAG_BOUND | DG_FLAG_TRANS | DG_FLAG_PAINT | DG_FLAG_TEXT)

STATIC void GM_LoadMapModel(int name, MAP *map)
{
    DG_DEF  *def;
    DG_OBJS *objs;

    def = GV_GetCache(GV_CacheID(name, 'k'));
    objs = DG_MakeObjs(def, MAP_FLAG, 0);

    DG_SetPos(&DG_ZeroMatrix);
    DG_PutObjs(objs);

    if (map->lit)
    {
        DG_MakePreshade(objs, map->lit->lights, map->lit->n_lights);
    }
    else
    {
        DG_MakePreshade(objs, NULL, 0);
    }

    DG_QueueObjs(objs);
    DG_GroupObjs(objs, map->index);

    StageObjs_800B7890[N_StageObjs_800ABAA4] = objs;
    N_StageObjs_800ABAA4++;
}

STATIC HZD_HDL *GM_LoadHazard(int name, int area, int index, int dyn_walls, int dyn_floors)
{
    HZD_MAP *hzm;
    HZD_HDL    *hzd;

    hzm = GV_GetCache(GV_CacheID(name, 'h'));
    hzd = HZD_MakeHandler(hzm, area, dyn_walls, dyn_floors);
    hzd->map = index;

    return hzd;
}

void GM_UpdateMap(void)
{
    if (gMapsChanged_800ABAAC)
    {
        GM_UpdateMapGroup(gMapsChanged_800ABAAC - 1);
        gMapsChanged_800ABAAC = 0;
    }
}

void GM_ResetMapHazard(void)
{
    int  count; // $s0
    MAP *pIter; // $s1

    pIter = gMapRecs_800B7910;
    for (count = gMapCount_800ABAA8; count > 0; pIter++, count--)
    {
        if (pIter->hzd)
        {
            HZD_FreeHandler(pIter->hzd);
        }
    }
}

void GM_ResetMapModel(void)
{
    DG_OBJS **objs;
    int       i;

    objs = StageObjs_800B7890;
    for (i = N_StageObjs_800ABAA4; i > 0; i--)
    {
        if (*objs)
        {
            DG_DequeueObjs(*objs);
            DG_FreePreshade(*objs);
            DG_FreeObjs(*objs);
        }

        *objs++ = NULL;
    }

    N_StageObjs_800ABAA4 = 0;
}

void GM_ResetMap(void)
{
    DG_OBJS **objs;
    int       i;

    objs = StageObjs_800B7890;
    for (i = 32; i > 0; --i)
    {
        *objs++ = NULL;
    }

    N_StageObjs_800ABAA4 = 0;
    gMapCount_800ABAA8 = 0;
    gMapsChanged_800ABAAC = 0;
}

MAP *GM_CreateMap(void)
{
    MAP *map;
    int  dyn_walls;
    int  dyn_floors;
    int  name;
    int  area;

    map = GM_GetNextMap(GCL_GetNextParamValue());

    if (GCL_GetOption('d')) // dynamic
    {
        dyn_walls = GCL_GetNextParamValue();
        dyn_floors = GCL_GetNextParamValue();
    }
    else
    {
        dyn_walls = 48;
        dyn_floors = 24;
    }

    if (!GCL_GetOption('h')) // hzd
    {
        printf("no hzd\n");
        return NULL;
    }

    name = GCL_GetNextParamValue();
    area = GCL_GetNextParamValue();
    map->hzd = GM_LoadHazard(name, area, map->index, dyn_walls, dyn_floors);

    if (GCL_GetOption('l')) // lit
    {
        map->lit = GV_GetCache(GV_CacheID(GCL_GetNextParamValue(), 'l'));
    }
    else
    {
        map->lit = NULL;
    }

    if (GCL_GetOption('k')) // kmd
    {
        while (GCL_GetParamResult())
        {
            GM_LoadMapModel(GCL_GetNextParamValue(), map);
        }
    }

    map->zone = 0;
    if (GCL_GetOption('z')) // zone
    {
        while (GCL_GetParamResult())
        {
            map->zone = map->zone | (1 << GCL_GetNextParamValue());
        }
    }

    return map;
}

STATIC void GM_SetMap(int area, int name)
{
    MAP *map;

    printf("set map %d\n", area);

    map = GM_GetNextMap(area);
    map->hzd = GM_LoadHazard(name, 0, map->index, 48, 24);
    map->lit = GV_GetCache(GV_CacheID(name, 'l'));
    GM_LoadMapModel(name, map);
}

MAP *GM_DefineMap(void)
{
    int area;
    int name;

    while (GCL_GetParamResult())
    {
        area = GCL_GetNextParamValue();
        name = GCL_GetNextParamValue();
        GM_SetMap(area, name);
    }

    return gMapRecs_800B7910;
}

int GM_AddMap(int name)
{
    MAP *map;
    int  i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (map->name == name)
        {
            printf("add map %d\n", map->index);
            map->used = 1;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        map++;
    }

    printf("addmap : not found map %d\n", name);
    return 0;
}

int GM_DelMap(int name)
{
    MAP *map;
    int  i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (map->name == name)
        {
            printf("del map %d\n", map->index);
            map->used = 0;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        map++;
    }

    printf("delmap: not found map %d\n", name);
    return 0;
}

int GM_ReloadMap(int preshade)
{
    MAP    *map;
    int     i;
    u_short name;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        map->used = 0;
        map++;
    }

    while (GCL_GetParamResult())
    {
        name = GCL_GetNextParamValue();
        GM_AddMap(name);
    }

    gMapsChanged_800ABAAC = preshade + 1;
    return 0;
}

MAP *GM_GetMap(int id)
{
    MAP *map;
    MAP *found;
    int  i;

    map = gMapRecs_800B7910;
    found = NULL;

    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (id == 0)
        {
            break;
        }

        if (id & 0x1)
        {
            found = map;
        }

        id >>= 1;
        map++;
    }

    return found;
}

MAP *GM_FindMap(int name)
{
    MAP *map;
    int  i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--, map++)
    {
        if (map->name == name)
        {
            return map;
        }
    }

    return NULL;
}

int GM_MapUsed(MAP *find)
{
    MAP *map;
    int  i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (map == find && map->used)
        {
            return 1;
        }

        map++;
    }

    return 0;
}

HZD_HDL *GM_IterHazard(HZD_HDL *cur)
{
    int i;

    if ( !cur )
    {
        pHzdIter_800ABAA0 = gMapRecs_800B7910;
    }
    else
    {
        pHzdIter_800ABAA0 = pHzdIter_800ABAA0 + 1;
    }

    for (i = gMapCount_800ABAA8 - (pHzdIter_800ABAA0 - gMapRecs_800B7910); i > 0; i--)
    {
        if (pHzdIter_800ABAA0->used)
        {
             return pHzdIter_800ABAA0->hzd;
        }

        pHzdIter_800ABAA0++;
    }

    return NULL;
}

MAP *GM_FindMapZone(int zone)
{
    MAP *map;
    int  i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (map->zone & zone)
        {
            return map;
        }

        map++;
    }

    return NULL;
}

void GM_ReshadeObjs( DG_OBJS *obj )
{
    MAP *map;
    LIT *lit;

    map = GM_GetMap( obj->group_id );
    if ( map == NULL )
    {
        printf( "Reshade NULL map\n" );
    }

    lit = map->lit;
    if( lit != NULL )
    {
        DG_MakePreshade( obj, lit->lights, lit->n_lights );
    }
}

void GM_ReshadeMapAll( void )
{
    DG_OBJS **obj;
    int       i;

    obj = StageObjs_800B7890;
    for (i = N_StageObjs_800ABAA4; i > 0; i--)
    {
        GM_ReshadeObjs(*obj);
        obj++;
    }
}
