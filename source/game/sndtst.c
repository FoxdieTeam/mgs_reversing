#include "sndtst.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/jimctrl.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT actor;
    int    playing;
    char  *script;
    char  *name;
    int    code;
    int    field_30;
    int    field_34;
    int    field_38;
    int    field_3C[ PAKU_MAX - 1 ];
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

    GCL_SetArgTop( work->script );

    for ( i = 0; i <= work->field_30; i++ )
    {
        if ( GCL_NextStr() == NULL )
        {
            work->field_30 = i;
            break;
        }

        name = GCL_GetString( GCL_NextStr() );
        code = GCL_StrToInt( GCL_NextStr() );
    }

    work->name = name;
    work->code = code;
}

/*---------------------------------------------------------------------------*/

static void Act( Work *work )
{
    GV_PAD *pad;
    int     var_s0;
    PAKU   *paku;
    char    eye;
    int     i;

    pad = &GV_PadData[0];

    if ( work->playing == 0 )
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
            work->playing = 1;
            GM_VoxStream( work->code, 0 );
        }

        MENU_Locate( 160, 120, 0x2 );
        MENU_Printf( work->name );
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
            work->playing = 0;
            GM_VoxStream( work->code, 0 );
        }

        paku = jimctrl_80038698();

        for ( i = 0; i < PAKU_MAX - 1; i++ )
        {
            if ( paku[i].eye != 0 )
            {
                paku[i].eye = 0;
                work->field_3C[i] = 1;
            }

            if ( work->field_3C[i] > 0 )
            {
                work->field_3C[i]++;

                eye = "-=O"[(work->field_3C[i] / 2) - 1];

                if ( work->field_3C[i] > 6 )
                {
                    work->field_3C[i] = 0;
                }
            }
            else
            {
                eye = '0';
            }

            MENU_Locate( 116, 32 + i * 10, 0 );
            MENU_Printf( "%c  %c  :%d", eye, "-0=-"[paku[i].mouth], paku[i].id );
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

    work->script = GCL_NextStr();
    work->field_30 = 0;
    work->field_38 = 0;
    RunScripts( work, 0 );
    work->playing = 0;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSoundTest( int name, int where, int argc, char **argv )
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor( GV_ACTOR_PREV2, sizeof( Work ) );
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
