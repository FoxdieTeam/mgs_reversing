#include "sndtst.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/jimctrl.h"

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

#define EXEC_LEVEL GV_ACTOR_LEVEL3

STATIC void SndtstRunScripts_800C3218( Work *work, int param_2 )
{
    int   i;
    char *pName;
    int   code;

    work->field_30 += param_2;
    if ( work->field_30 < 0 )
    {
        work->field_30 = 0;
    }

    GCL_SetArgTop( work->field_24 );

    for ( i = 0; i <= work->field_30; i++ )
    {
        if ( !GCL_GetParamResult() )
        {
            work->field_30 = i;
            break;
        }

        pName = GCL_ReadString( GCL_GetParamResult() );
        code = GCL_StrToInt( GCL_GetParamResult() );
    }

    work->field_28_name = pName;
    work->field_2C_code = code;
}

STATIC void SndtstAct_800C32D8( Work *work )
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
            GM_VoxStream( work->field_2C_code, 0 );
        }

        MENU_Locate( 160, 120, 0x2 );
        MENU_Printf( work->field_28_name );
    }
    else
    {
        MENU_Locate( 160, 120, 0x2 );
        MENU_Printf( "PLAYING" );

        if ( pPad->press & PAD_CROSS )
        {
            GM_StreamPlayStop();
        }

        if ( GM_StreamStatus() == -1 )
        {
            work->field_20 = 0;
            GM_VoxStream( work->field_2C_code, 0 );
        }

        pUnk = jimctrl_80038698();

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

            MENU_Locate( 116, 32 + i * 10, 0 );
            MENU_Printf( "%c  %c  :%d", symbol, "-0=-"[pUnk[i].field_3], pUnk[i].field_0 );
        }
    }
}

STATIC int SndtstGetResources_800C352C( Work *work, int where, int name )
{
    if ( !GCL_GetOption( 's' ) )
    {
        printf( "NO MENU\n" );
        return -1;
    }

    work->field_24 = GCL_GetParamResult();
    work->field_30 = 0;
    work->field_38 = 0;
    SndtstRunScripts_800C3218( work, 0 );
    work->field_20 = 0;

    return 0;
}

void *NewSndtst_800C3594( int name, int where, int argc, char **argv )
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &( work->actor ), SndtstAct_800C32D8, NULL, "sndtst.c" );
        if (SndtstGetResources_800C352C( work, where, name ) < 0)
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }
    }

    return (void *)work;
}
