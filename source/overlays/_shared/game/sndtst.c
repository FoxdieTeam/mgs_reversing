#include "sndtst.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/jimctrl.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL3

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

/*---------------------------------------------------------------------------*/

static void RunScripts( Work *work, int param_2 )
{
    int   i;
    char *name;
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

        name = GCL_ReadString( GCL_GetParamResult() );
        code = GCL_StrToInt( GCL_GetParamResult() );
    }

    work->field_28_name = name;
    work->field_2C_code = code;
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    GV_PAD               *pad;
    int                   var_s0;
    array_800B933C_child *pUnk;
    char                  symbol;
    int                   i;

    pad = &GV_PadData[0];

    if ( work->field_20 == 0 )
    {
        if ( pad->status & (PAD_DOWN | PAD_UP) )
        {
            var_s0 = (pad->status & PAD_UP) ? -1 : 1;

            if ( pad->status & PAD_L1 )
            {
                var_s0 *= 10;
            }

            if ( work->field_38 == var_s0 )
            {
                if ( --work->field_34 < 0 )
                {
                    RunScripts( work, var_s0 );
                    work->field_34 = 2;
                }
            }
            else
            {
                RunScripts( work, var_s0 );
                work->field_34 = 10;
                work->field_38 = var_s0;
            }
        }
        else
        {
            work->field_38 = 0;
        }

        if ( pad->press & PAD_CIRCLE )
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

        if ( pad->press & PAD_CROSS )
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

/*---------------------------------------------------------------------------*/

static int GetResources( Work *work, int where, int name )
{
    if ( !GCL_GetOption( 's' ) )
    {
        printf( "NO MENU\n" );
        return -1;
    }

    work->field_24 = GCL_GetParamResult();
    work->field_30 = 0;
    work->field_38 = 0;
    RunScripts( work, 0 );
    work->field_20 = 0;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSoundTest( int name, int where, int argc, char **argv )
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &( work->actor ), Act, NULL, "sndtst.c" );
        if (GetResources( work, where, name ) < 0)
        {
            GV_DestroyActor( &work->actor );
            return NULL;
        }
    }

    return (void *)work;
}
