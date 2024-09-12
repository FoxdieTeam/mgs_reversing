#include "libdg/libdg.h"
#include "linker.h"
#include "Game/map.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"

extern MAP gMapRecs_800B7910[ 16 ];
extern GV_HEAP    MemorySystems_800AD2F0[ 3 ];
extern DG_OBJS   *StageObjs_800B7890[ 32 ];
extern int        DG_CurrentGroupID_800AB968;
extern int        GM_PlayerMap_800ABA0C;
extern int        HZD_CurrentGroup_800AB9A8;
extern MATRIX     DG_ZeroMatrix_8009D430;

extern            MAP *pHzdIter_800ABAA0;
MAP*       SECTION(".sbss") pHzdIter_800ABAA0; // force gp

extern int        gMapCount_800ABAA8;
int               SECTION( ".sbss" ) gMapCount_800ABAA8;

extern int        N_StageObjs_800ABAA4;
int               SECTION( ".sbss" ) N_StageObjs_800ABAA4;

extern int        gMapsChanged_800ABAAC;
int               SECTION(".sbss") gMapsChanged_800ABAAC;

extern void       HZD_BindMapChange_80029A6C( int mask );

void Map_light_80030C6C( int a1 )
{
    MAP *pMap;
    int         mask;
    int         bitset;
    DG_OBJS   **pObjs;
    LitHeader  *lit;
    int         i, j;

    pMap = gMapRecs_800B7910;
    mask = 0;
    bitset = 0;

    DG_ResetFixedLight();

    for ( i = gMapCount_800ABAA8; i > 0; pMap++, i-- )
    {
        if ( !pMap->used )
        {
            continue;
        }

        pObjs = StageObjs_800B7890;
        mask |= pMap->index;

        for ( j = N_StageObjs_800ABAA4; j > 0; j-- )
        {
            if ( pMap->index & pObjs[ 0 ]->group_id )
            {
                lit = pMap->lit;

                if ( lit )
                {
                    DG_SetFixedLight( lit->lights, lit->n_lights );

                    if ( a1 )
                    {
                        DG_MakePreshade( pObjs[ 0 ], lit->lights, lit->n_lights );
                    }
                }
                else
                {
                    DG_SetFixedLight( NULL, 0 );

                    if ( a1 )
                    {
                        DG_MakePreshade( pObjs[ 0 ], NULL, 0 );
                    }
                }
            }

            pObjs++;
        }

        bitset |= 1 << ( pMap->hzd->f04_area - pMap->hzd->f00_header->areas );
    }

    GM_PlayerMap_800ABA0C = mask;
    HZD_CurrentGroup_800AB9A8 = bitset;
    DG_CurrentGroupID_800AB968 = mask;
    HZD_BindMapChange_80029A6C( mask );
}

MAP *Map_GetNextFreeRecord_80030E30(int mapNameHashed)
{
    int                count;
    MAP *pIter;

    count = gMapCount_800ABAA8;
    pIter = gMapRecs_800B7910;
    while (count > 0)
    {
        --count;
        ++pIter;
    }

    pIter->name = (unsigned short)mapNameHashed;
    pIter->used = 0;
    pIter->index = 1 << gMapCount_800ABAA8;
    gMapCount_800ABAA8++;
    return pIter;
}

void Map_KmdLoad_80030E74(int pLitName, MAP *pMap)
{
    int               hashedName; // $v0
    DG_DEF           *pLitModel;  // $v0
    DG_OBJS          *pPrim;      // $s0
    struct LitHeader *lit_file;   // $a1
    int               numLights;  // $a2
    DG_LIT         *pLights;    // $a1
    int               temp;

    hashedName = GV_CacheID(pLitName, 'k');
    pLitModel = (DG_DEF *)GV_GetCache(hashedName);
    pPrim = (DG_OBJS *)DG_MakeObjs(pLitModel, 0x57, 0);
    DG_SetPos(&DG_ZeroMatrix_8009D430);
    DG_PutObjs(pPrim);
    lit_file = pMap->lit;
    if (lit_file)
    {
        numLights = lit_file->n_lights;
        pLights = lit_file->lights;
        DG_MakePreshade(pPrim, pLights, numLights);
    }
    else
    {
        numLights = 0;
        pLights = NULL;
        DG_MakePreshade(pPrim, pLights, numLights);
    }

    DG_QueueObjs(pPrim);

    temp = pMap->index;
    pPrim->group_id = temp;
    StageObjs_800B7890[N_StageObjs_800ABAA4] = pPrim;
    N_StageObjs_800ABAA4++;
}

HZD_HDL *Map_HZD_Load_80030F38(int resource_name_hashed, int flagsIndex, int bitIndex, int default_48, int default_24)
{
    int      name;     // $v0
    void    *pHzdData; // $v0
    HZD_HDL *result;   // $v0

    name = GV_CacheID(resource_name_hashed, 'h');
    pHzdData = GV_GetCache(name);
    result = HZD_MakeHandler_80021AE0(pHzdData, flagsIndex, default_48, default_24);

    result->f08_areaIndex = bitIndex;
    return result;
}

void Map_80030FA4()
{
    if (gMapsChanged_800ABAAC)
    {
        Map_light_80030C6C(gMapsChanged_800ABAAC - 1);
        gMapsChanged_800ABAAC = 0;
    }
}

void GM_DieMap_80030FD0()
{
    int                count; // $s0
    MAP        *pIter; // $s1

    pIter = gMapRecs_800B7910;
    for (count = gMapCount_800ABAA8; count > 0; pIter++, count--)
    {
        if (pIter->hzd)
        {
            HZD_FreeHandler_80021C40(pIter->hzd);
        }
    }
}

void GM_FreeMapObjs_80031028()
{
    int       counter;  // $s1
    DG_OBJS **pObjIter; // $s0

    counter = N_StageObjs_800ABAA4;
    for (pObjIter = StageObjs_800B7890; counter > 0; counter--, pObjIter++)
    {
        if (*pObjIter)
        {
            DG_DequeueObjs(*pObjIter);
            DG_FreePreshade(*pObjIter);
            DG_FreeObjs(*pObjIter);
        }
        *pObjIter = NULL;
    }
    N_StageObjs_800ABAA4 = 0;
}

void GM_ResetMapObjs_800310A0()
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

MAP *GM_Command_mapdef_impl_800310D0(void)
{
    MAP *map;
    int         d1, d2;

    map = Map_GetNextFreeRecord_80030E30(GCL_GetNextParamValue());

    if (GCL_GetOption('d'))
    {
        d1 = GCL_GetNextParamValue();
        d2 = GCL_GetNextParamValue();
    }
    else
    {
        d1 = 0x30;
        d2 = 0x18;
    }

    if (!GCL_GetOption('h')) // hzm
    {
        printf("no hzd\n");
        return 0;
    }

    map->hzd = Map_HZD_Load_80030F38(GCL_GetNextParamValue(), GCL_GetNextParamValue(),
                                             map->index, d1, d2);

    if (GCL_GetOption('l')) // lit
    {
        map->lit = GV_GetCache(GV_CacheID(GCL_GetNextParamValue(), 'l'));
    }
    else
    {
        map->lit = 0;
    }

    if (GCL_GetOption('k')) // kmd
    {
        while (GCL_GetParamResult())
        {
            Map_KmdLoad_80030E74(GCL_GetNextParamValue(), map);
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

void GM_SetMap_80031244(int mapNum, int resourceNameHashed)
{
    MAP *pMapRec; // $s0
    printf("set map %d\n", mapNum);
    pMapRec = Map_GetNextFreeRecord_80030E30(mapNum);
    pMapRec->hzd = Map_HZD_Load_80030F38(resourceNameHashed, 0, pMapRec->index, 48, 24);
    pMapRec->lit = GV_GetCache(GV_CacheID(resourceNameHashed, 'l'));
    Map_KmdLoad_80030E74(resourceNameHashed, pMapRec);
}

MAP *Map_ScriptLoadMapBlocks_800312D0()
{
    int nameHashed; // $v0
    int mapNum;     // $s0

    while (GCL_GetParamResult())
    {
        mapNum = GCL_GetNextParamValue();
        nameHashed = GCL_GetNextParamValue();
        GM_SetMap_80031244(mapNum, nameHashed);
    }
    return gMapRecs_800B7910;
}

int GM_AddMap_80031324(int mapName)
{
    int                counter;  // $v1
    MAP *pRecIter; // $a1

    pRecIter = gMapRecs_800B7910;

    for (counter = gMapCount_800ABAA8; counter > 0; counter--)
    {
        if (pRecIter->name == mapName)
        {
            printf("add map %d\n", pRecIter->index);
            pRecIter->used = 1;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        pRecIter++;
    }

    printf("addmap : not found map %d\n", mapName);
    return 0;
}

int GM_DelMap_800313C0(int mapName)
{
    int                counter;  // $v1
    MAP *pRecIter; // $a1

    pRecIter = gMapRecs_800B7910;

    for (counter = gMapCount_800ABAA8; counter > 0; counter--)
    {
        if (pRecIter->name == mapName)
        {
            printf("del map %d\n", pRecIter->index);
            pRecIter->used = 0;
            gMapsChanged_800ABAAC = 1;
            return 1;
        }

        pRecIter++;
    }

    printf("delmap: not found map %d\n", mapName);
    return 0;
}

int Map_ScriptReloadMaps_80031450(int a1)
{
    int                counter;                 // $v1
    MAP *pIter;                   // $v0
    unsigned short     NextParamValue_80020AD4; // $v0

    counter = gMapCount_800ABAA8;
    for (pIter = gMapRecs_800B7910; counter > 0; ++pIter)
    {
        pIter->used = 0;
        --counter;
    }
    while (GCL_GetParamResult())
    {
        NextParamValue_80020AD4 = GCL_GetNextParamValue();
        GM_AddMap_80031324(NextParamValue_80020AD4);
    }
    gMapsChanged_800ABAAC = a1 + 1;
    return 0;
}

MAP *Map_FromId_800314C0(int id)
{
    MAP *pRecIter; // $a1
    int                counter;  // $v1
    MAP *pFound;   // $a2

    pRecIter = gMapRecs_800B7910;
    counter = gMapCount_800ABAA8;
    pFound = 0;
    while (counter > 0)
    {
        if (!id)
        {
            break;
        }

        if ((id & 1) != 0)
        {
            pFound = pRecIter;
        }

        id >>= 1;
        pRecIter++;
        counter--;
    }
    return pFound;
}

MAP *Map_FindByNum_80031504(int mapNameHash)
{
    MAP *map;
    int         i;

    map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (map->name == mapNameHash)
        {
            return map;
        }
        map++;
    }
    return 0;
}

int sub_8003153C(MAP *map)
{
    MAP *current_map;
    int         i;

    current_map = gMapRecs_800B7910;
    for (i = gMapCount_800ABAA8; i > 0; i--)
    {
        if (current_map == map)
        {
            if (current_map->used)
            {
                return 1;
            }
        }
        current_map++;
    }
    return 0;
}

HZD_HDL * Map_Enum_Get_Hzd_80031580(HZD_HDL *pPrevious)
{
    int count; // $v1

    if ( !pPrevious )
    {
        pHzdIter_800ABAA0 = gMapRecs_800B7910;
    }
    else
    {
        pHzdIter_800ABAA0 = pHzdIter_800ABAA0 + 1;

    }

    count = gMapCount_800ABAA8 - (pHzdIter_800ABAA0 - gMapRecs_800B7910);

    while(count > 0)
    {
        if (pHzdIter_800ABAA0->used )
        {
             return pHzdIter_800ABAA0->hzd;
        }
        pHzdIter_800ABAA0++;
        count--;
    }
    return 0;
}

MAP *Map_FindByZoneId_80031624(int zone_id)
{
    MAP *ptr;
    int         i;

    ptr = (MAP *)&gMapRecs_800B7910;
    i = gMapCount_800ABAA8;

    while (i > 0)
    {
        if (ptr->zone & zone_id)
        {
            return ptr;
        }
        i--;
        ptr++;
    }

    return 0;
}

void GM_ReshadeObjs_80031660( DG_OBJS *obj )
{
    MAP *map;
    LitHeader *lit;

    map = Map_FromId_800314C0( obj->group_id );
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

void GM_ReshadeMapAll_800316C4() // from memleak
{
    DG_OBJS **obj;
    int       i;

    obj = StageObjs_800B7890;
    for (i = N_StageObjs_800ABAA4; i > 0; obj++, i--)
    {
        GM_ReshadeObjs_80031660(*obj);
    }
}
