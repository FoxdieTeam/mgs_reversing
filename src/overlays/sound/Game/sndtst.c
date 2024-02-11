#include "Game/game.h"
#include "libgv/libgv.h"
#include "unknown.h"

typedef struct Work
{
    GV_ACT actor;
    int    field_20;
    char  *field_24;
    char  *field_28_name;
    int    field_2C_code;
    int    field_30;
    int    field_34;
    int    field_38;
    int    field_3C[6];
} Work;

extern GV_PAD GV_PadData_800B05C0[4];

#define EXEC_LEVEL 3

void SndtstRunScripts_800C3218( Work *work, int param_2 )
{
    int   i;
    char *pName;
    int   code;

    work->field_30 += param_2;
    if ( work->field_30 < 0 )
    {
        work->field_30 = 0;
    }

    GCL_SetArgTop_80020690( work->field_24 );

    for ( i = 0; i <= work->field_30; i++ )
    {
        if ( !GCL_Get_Param_Result_80020AA4() )
        {
            work->field_30 = i;
            break;
        }

        pName = GCL_Read_String_80020A70( GCL_Get_Param_Result_80020AA4() );
        code = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() );
    }

    work->field_28_name = pName;
    work->field_2C_code = code;
}

void SndtstAct_800C32D8( Work *work )
{
    GV_PAD               *pPad;
    int                   var_s0;
    array_800B933C_child *pUnk;
    char                  symbol;
    int                   i;

    pPad = &GV_PadData_800B05C0[0];

    if ( work->field_20 == 0 )
    {
        if ( pPad->status & (PAD_DOWN | PAD_UP) )
        {
            var_s0 = (pPad->status & PAD_UP) ? -1 : 1;

            if ( pPad->status & PAD_L1 )
            {
                var_s0 *= 10;
            }

            if ( work->field_38 == var_s0 )
            {
                if ( --work->field_34 < 0 )
                {
                    SndtstRunScripts_800C3218( work, var_s0 );
                    work->field_34 = 2;
                }
            }
            else
            {
                SndtstRunScripts_800C3218( work, var_s0 );
                work->field_34 = 10;
                work->field_38 = var_s0;
            }
        }
        else
        {
            work->field_38 = 0;
        }

        if ( pPad->press & PAD_CIRCLE )
        {
            work->field_20 = 1;
            GM_VoxStream_80037E40( work->field_2C_code, 0 );
        }

        MENU_Locate_80038B34( 160, 120, 0x2 );
        MENU_Printf_80038C38( work->field_28_name );
    }
    else
    {
        MENU_Locate_80038B34( 160, 120, 0x2 );
        MENU_Printf_80038C38( "PLAYING" );

        if ( pPad->press & PAD_CROSS )
        {
            GM_StreamPlayStop_80037D64();
        }

        if ( GM_StreamStatus_80037CD8() == -1 )
        {
            work->field_20 = 0;
            GM_VoxStream_80037E40( work->field_2C_code, 0 );
        }

        pUnk = sub_80038698();

        for ( i = 0; i < 6; i++ )
        {
            if ( pUnk[i].field_2 != 0 )
            {
                pUnk[i].field_2 = 0;
                work->field_3C[i] = 1;
            }

            if ( work->field_3C[i] > 0 )
            {
                work->field_3C[i]++;

                symbol = "-=O"[(work->field_3C[i] / 2) - 1];

                if ( work->field_3C[i] > 6 )
                {
                    work->field_3C[i] = 0;
                }
            }
            else
            {
                symbol = '0';
            }

            MENU_Locate_80038B34( 116, 32 + i * 10, 0 );
            MENU_Printf_80038C38( "%c  %c  :%d", symbol, "-0=-"[pUnk[i].field_3], pUnk[i].field_0 );
        }
    }
}

int SndtstGetResources_800C352C( Work *work, int where, int name )
{
    if ( !GCL_GetOption_80020968( 's' ) )
    {
        printf( "NO MENU\n" );
        return -1;
    }

    work->field_24 = GCL_Get_Param_Result_80020AA4();
    work->field_30 = 0;
    work->field_38 = 0;
    SndtstRunScripts_800C3218( work, 0 );
    work->field_20 = 0;

    return 0;
}

GV_ACT * NewSndtst_800C3594( int name, int where, int argc, char **argv )
{
    Work *work;

    GM_GameStatus_800AB3CC |= (GAME_FLAG_BIT_14 | GAME_FLAG_BIT_15 | GAME_FLAG_BIT_18 | GAME_FLAG_BIT_20 | GAME_FLAG_BIT_23);

    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )SndtstAct_800C32D8, NULL, "sndtst.c" );
        if (SndtstGetResources_800C352C( work, where, name ) < 0)
        {
            GV_DestroyActor_800151C8( &work->actor );
            return NULL;
        }
    }

    return &work->actor;
}
