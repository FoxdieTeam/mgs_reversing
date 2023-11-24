#include "libdg/libdg.h"
#include "linker.h"
#include "Game/map.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"

extern MAP gMapRecs_800B7910[ 16 ];
extern GV_Heap    MemorySystems_800AD2F0[ 3 ];
extern DG_OBJS   *StageObjs_800B7890[ 32 ];
extern int        DG_CurrentGroupID_800AB968;
extern int        GM_PlayerMap_800ABA0C;
extern int        dword_800AB9A8[ 2 ];
extern MATRIX     DG_ZeroMatrix_8009D430;

extern            MAP *pHzdIter_800ABAA0;
MAP*       SECTION(".sbss") pHzdIter_800ABAA0; // force gp

extern int        gMapCount_800ABAA8;
int               SECTION( ".sbss" ) gMapCount_800ABAA8;

extern int        N_StageObjs_800ABAA4;
int               SECTION( ".sbss" ) N_StageObjs_800ABAA4;

extern int        gMapsChanged_800ABAAC;
int               SECTION(".sbss") gMapsChanged_800ABAAC;

extern void       DG_SetFixedLight_8001A094( DG_LIT *pLight, int light_count );
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

    DG_ResetFixedLight_8001A06C();

    for ( i = gMapCount_800ABAA8; i > 0; pMap++, i-- )
    {
        if ( !pMap->field_6_bUsed )
        {
            continue;
        }

        pObjs = StageObjs_800B7890;
        mask |= pMap->field_0_map_index_bit;

        for ( j = N_StageObjs_800ABAA4; j > 0; j-- )
        {
            if ( pMap->field_0_map_index_bit & pObjs[ 0 ]->group_id )
            {
                lit = pMap->field_C_lit;

                if ( lit )
                {
                    DG_SetFixedLight_8001A094( lit->lights, lit->field_0_num_lights );

                    if ( a1 )
                    {
                        DG_MakePreshade_80031F04( pObjs[ 0 ], lit->lights, lit->field_0_num_lights );
                    }
                }
                else
                {
                    DG_SetFixedLight_8001A094( NULL, 0 );

                    if ( a1 )
                    {
                        DG_MakePreshade_80031F04( pObjs[ 0 ], NULL, 0 );
                    }
                }
            }

            pObjs++;
        }

        bitset |= 1 << ( pMap->field_8_hzd->f04_area - pMap->field_8_hzd->f00_header->areas );
    }

    GM_PlayerMap_800ABA0C = mask;
    dword_800AB9A8[ 0 ] = bitset;
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

    pIter->field_4_mapNameHash = (unsigned short)mapNameHashed;
    pIter->field_6_bUsed = 0;
    pIter->field_0_map_index_bit = 1 << gMapCount_800ABAA8;
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

    hashedName = GV_CacheID_800152DC(pLitName, 'k');
    pLitModel = (DG_DEF *)GV_GetCache_8001538C(hashedName);
    pPrim = (DG_OBJS *)DG_MakeObjs_80031760(pLitModel, 0x57, 0);
    DG_SetPos_8001BC44(&DG_ZeroMatrix_8009D430);
    DG_PutObjs_8001BDB8(pPrim);
    lit_file = pMap->field_C_lit;
    if (lit_file)
    {
        numLights = lit_file->field_0_num_lights;
        pLights = (DG_LIT *)&lit_file[1];
        DG_MakePreshade_80031F04(pPrim, pLights, numLights);
    }
    else
    {
        numLights = 0;
        pLights = NULL;
        DG_MakePreshade_80031F04(pPrim, pLights, numLights);
    }

    DG_QueueObjs_80018178(pPrim);

    temp = pMap->field_0_map_index_bit;
    pPrim->group_id = temp;
    StageObjs_800B7890[N_StageObjs_800ABAA4] = pPrim;
    N_StageObjs_800ABAA4++;
}

HZD_HDL *Map_HZD_Load_80030F38(int resource_name_hashed, int flagsIndex, int bitIndex, int default_48, int default_24)
{
    int      name;     // $v0
    void    *pHzdData; // $v0
    HZD_HDL *result;   // $v0

    name = GV_CacheID_800152DC(resource_name_hashed, 'h');
    pHzdData = GV_GetCache_8001538C(name);
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
    for (count = gMapCount_800ABAA8; count > 0; count--)
    {
        if (pIter->field_8_hzd)
        {
            HZD_FreeHandler_80021C40(pIter->field_8_hzd);
        }
        ++pIter;
    }
}

void GM_FreeMapObjs_80031028()
{
    int       counter;  // $s1
    DG_OBJS **pObjIter; // $s0

    counter = N_StageObjs_800ABAA4;
    for (pObjIter = StageObjs_800B7890; counter > 0; ++pObjIter)
    {
        if (*pObjIter)
        {
            DG_DequeueObjs_800181E4(*pObjIter);
            DG_FreePreshade_80032110(*pObjIter);
            DG_FreeObjs_800318D0(*pObjIter);
        }
        *pObjIter = 0;
        --counter;
    }
    N_StageObjs_800ABAA4 = 0;
}

void GM_ResetMapObjs_800310A0()
{
    DG_OBJS **v0; // $v0
    int       i;  // $v1

    v0 = StageObjs_800B7890;
    for (i = 32; i > 0; --i)
    {
        *v0++ = 0;
    }

    N_StageObjs_800ABAA4 = 0;
    gMapCount_800ABAA8 = 0;
    gMapsChanged_800ABAAC = 0;
}

MAP *GCL_Command_mapdef_impl_800310D0(void)
{
    MAP *map;
    int         d1, d2;

    map = Map_GetNextFreeRecord_80030E30(GCL_GetNextParamValue_80020AD4());

    if (GCL_GetOption_80020968('d'))
    {
        d1 = GCL_GetNextParamValue_80020AD4();
        d2 = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        d1 = 0x30;
        d2 = 0x18;
    }

    if (!GCL_GetOption_80020968('h')) // hzm
    {
        printf("no hzd\n");
        return 0;
    }

    map->field_8_hzd = Map_HZD_Load_80030F38(GCL_GetNextParamValue_80020AD4(), GCL_GetNextParamValue_80020AD4(),
                                             map->field_0_map_index_bit, d1, d2);

    if (GCL_GetOption_80020968('l')) // lit
    {
        map->field_C_lit = GV_GetCache_8001538C(GV_CacheID_800152DC(GCL_GetNextParamValue_80020AD4(), 'l'));
    }
    else
    {
        map->field_C_lit = 0;
    }

    if (GCL_GetOption_80020968('k')) // kmd
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            Map_KmdLoad_80030E74(GCL_GetNextParamValue_80020AD4(), map);
        }
    }

    map->field_10_zone_id = 0;
    if (GCL_GetOption_80020968('z')) // zone
    {
        while (GCL_Get_Param_Result_80020AA4())
        {
            map->field_10_zone_id = map->field_10_zone_id | (1 << GCL_GetNextParamValue_80020AD4());
        }
    }

    return map;
}

void GM_SetMap_80031244(int mapNum, int resourceNameHashed)
{
    MAP *pMapRec; // $s0
    printf("set map %d\n", mapNum);
    pMapRec = Map_GetNextFreeRecord_80030E30(mapNum);
    pMapRec->field_8_hzd = Map_HZD_Load_80030F38(resourceNameHashed, 0, pMapRec->field_0_map_index_bit, 48, 24);
    pMapRec->field_C_lit = GV_GetCache_8001538C(GV_CacheID_800152DC(resourceNameHashed, 'l'));
    Map_KmdLoad_80030E74(resourceNameHashed, pMapRec);
}

MAP *Map_ScriptLoadMapBlocks_800312D0()
{
    int nameHashed; // $v0
    int mapNum;     // $s0

    while (GCL_Get_Param_Result_80020AA4())
    {
        mapNum = GCL_GetNextParamValue_80020AD4();
        nameHashed = GCL_GetNextParamValue_80020AD4();
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
        if (pRecIter->field_4_mapNameHash == mapName)
        {
            printf("add map %d\n", pRecIter->field_0_map_index_bit);
            pRecIter->field_6_bUsed = 1;
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
        if (pRecIter->field_4_mapNameHash == mapName)
        {
            printf("del map %d\n", pRecIter->field_0_map_index_bit);
            pRecIter->field_6_bUsed = 0;
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
        pIter->field_6_bUsed = 0;
        --counter;
    }
    while (GCL_Get_Param_Result_80020AA4())
    {
        NextParamValue_80020AD4 = GCL_GetNextParamValue_80020AD4();
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
        if (map->field_4_mapNameHash == mapNameHash)
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
            if (current_map->field_6_bUsed)
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
        if (pHzdIter_800ABAA0->field_6_bUsed )
        {
             return pHzdIter_800ABAA0->field_8_hzd;
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

    if (gMapCount_800ABAA8 > 0)
    {
        do
        {
            if ((ptr->field_10_zone_id & zone_id) != 0)
            {
                return ptr;
            }
            i--;
            ptr++;
        } while (i > 0);
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
    lit = map->field_C_lit;
    if( lit != NULL )
    {
        DG_MakePreshade_80031F04( obj, lit->lights, lit->field_0_num_lights ) ;
    }
}

void GM_ReshadeMapAll_800316C4() // from memleak
{
    DG_OBJS **obj;
    int       i;

    obj = StageObjs_800B7890;
    for (i = N_StageObjs_800ABAA4; i > 0; --i)
    {
        GM_ReshadeObjs_80031660(*obj);
        obj++;
    }
}
