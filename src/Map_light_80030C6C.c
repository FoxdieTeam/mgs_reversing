#include "libdg/libdg.h"
#include "linker.h"
#include "map/map.h"

extern map_record gMapRecs_800B7910[ 16 ];
extern GV_Heap    MemorySystems_800AD2F0[ 3 ];
extern DG_OBJS   *StageObjs_800B7890[ 32 ];
extern int        DG_CurrentGroupID_800AB968;
extern int        dword_800ABA0C;
extern int        dword_800AB9A8[ 2 ];

extern int        gMapCount_800ABAA8;
int               SECTION( ".sbss" ) gMapCount_800ABAA8; // force gp
extern int        N_StageObjs_800ABAA4;
int               SECTION( ".sbss" ) N_StageObjs_800ABAA4;

extern void       DG_SetFixedLight_8001A094( DG_Light *pLight, int light_count );
extern void       HZD_BindMapChange_80029A6C( int mask );

void Map_light_80030C6C( int a1 )
{
    map_record *pMap;
    int         mask;
    int         bitset;
    DG_OBJS   **pObjs;
    LitHeader  *pLitHeader;
    DG_Light   *pLight;
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
                pLitHeader = pMap->field_C_lit_file;
                pLight = (DG_Light *)&pLitHeader[ 1 ];

                if ( pLitHeader )
                {
                    DG_SetFixedLight_8001A094( pLight, pLitHeader->field_0_num_lights );

                    if ( a1 )
                    {
                        DG_MakePreshade_80031F04( pObjs[ 0 ], pLight, pLitHeader->field_0_num_lights );
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

    dword_800ABA0C = mask;
    dword_800AB9A8[ 0 ] = bitset;
    DG_CurrentGroupID_800AB968 = mask;
    HZD_BindMapChange_80029A6C( mask );
}