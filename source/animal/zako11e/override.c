#include "enemy/enemy.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "game/vibrate.h"
#include "okajima/bullet.h"

/*** Inlines *****************************************************************/

static inline void UnsetMode( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( ZakoWork *work, int n_action, int interp )
{
    extern short    ActTable_800C35EC[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C35EC[ n_action ], 0, interp );
}

static inline void UnsetAction( ZakoWork *work, int n_action )
{
    extern short    ActTable_800C35EC[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( ZakoWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C35EC[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];

    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}

/*****************************************************************************/

extern ZAKO_COMMAND ZakoCommand_800DF280;

void s11e_zk11ecom_800D56F8( ZakoWork* work, int time );

void s11e_zk11ecom_800D6F68( ZakoWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION9 );
    }

    if ( !( work->pad.press & 1 ) )
    {
        UnsetMode( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.rot.vy - ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy - 1024 ) & 0xFFF;
        }
    }
}

void s11e_zk11ecom_800D7034( ZakoWork* work, int time)
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION10 );
    }

    if ( !( work->pad.press & 2 ) )
    {
        UnsetMode( work );
    }
    else
    {
        if ( time < 4 )
        {
            work->vision.facedir = ( work->control.rot.vy + ( time * 256 ) ) & 0xFFF;
        }
        else
        {
            work->vision.facedir = ( work->control.rot.vy + 1024 ) & 0xFFF;
        }
    }
}

void ActOverScoutD_800D7100( ZakoWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION11 );
    }

    if ( !( work->pad.press & 4 ) )
    {
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7198( ZakoWork* work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION14 );
    }

    if ( !( work->pad.press & 0x2000 ) )
    {
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7230( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION24 );
        GM_SeSet( &work->control.mov, SE_V_ENE_SNEEZE );
    }

    if ( work->body.time2 || !( work->pad.press & 0x40 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D72E4( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION22 );
    }

    if ( time == 60 )
    {
        GM_SeSet( &work->control.mov, SE_V_ENE_YAWN );
    }

    if ( work->body.time2 || !( work->pad.press & 0x80 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D73AC( ZakoWork* work, int time )
{
    if ( time == 0 )
    {
        UnsetAction( work, ACTION23 );
    }

    if ( work->body.time2 || !( work->pad.press & 0x400 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7450( ZakoWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet( &work->control.mov, SE_V_ENE_YAWN );
    }

    if ( work->body.time2 || !( work->pad.press & 0x800 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7518( ZakoWork *work, int time )
{
    SVECTOR mov;
    work->vision.length = 0;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION19 );
    }

    if ( time == 90 )
    {
        GM_SeSet( &work->control.mov, SE_V_ENE_YAWN );
    }

    if ( time == 110 )
    {
        UnsetAction( work, ACTION20 );
    }

    if ( time > 110 )
    {
        work->act_status |= 0x10;
        if ( work->m_ctrl.info2.frame == 30 )
        {
            mov = work->control.mov;
            mov.vy += 500;
            AN_Sleep( &mov );
            GM_SeSet( &work->control.mov, SE_V_ENE_SNORE );

            if ( work->sn_dis < 1000 && ( GM_PlayerStatus & PLAYER_WATCH ) )
            {
                int res = GV_RandU( 12 );
                if ( res > 10 )
                {
                    work->pad.sound = 240;
                }
            }
        }
        if ( work->pad.press & 0x1000 )
        {
            SetZakoMode( work, s11e_zk11ecom_800D56F8 );
            UnsetMode( work );
            return;
        }
    }

    if ( !( work->pad.press & 0x200 ) )
    {
        UnsetMode( work );
    }
}

extern void AN_Unknown_800C3B7C( MATRIX *matrix );
extern SVECTOR s11e_dword_800C3668;

void s11e_zk11ecom_800D76F0( ZakoWork* work )
{
    MATRIX mat;

    DG_SetPos( &work->body.objs->objs[6].world );
    DG_MovePos( &s11e_dword_800C3668 );
    ReadRotMatrix( &mat );
    AN_Unknown_800C3B7C( &mat );
}

void s11e_zk11ecom_800D7730( ZakoWork *work, int time )
{
    int diff;
    work->vision.length = 3000;
    work->act_status |= 0x80;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
    }

    diff = time - 1000;
    if ( time >= 1000 && time < 1210 )
    {
        if ( diff == 0  || diff == 4  || diff == 8  || diff == 12 ||
             diff == 20 || diff == 28 || diff == 36 || diff == 48 ||
             diff == 60 )
        {
            GM_SeSet( &work->control.mov, SE_WET_STEP );
            s11e_zk11ecom_800D76F0( work );
        }
    }
    else if ( time > 30 && time & 1 )
    {
        GM_SeSet( &work->control.mov, SE_WET_STEP );
        if ( time > 45 )
        {
            s11e_zk11ecom_800D76F0( work );
        }
    }

    if ( !( work->pad.press & 0x800000 ) )
    {
        UnsetMode( work );
    }
}

void s11e_zk11ecom_800D7878( ZakoWork *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 )
    {
        UnsetAction( work, ACTION25 );
    }

    if ( time == 186 )
    {
        UnsetActionManual( work, ACTION26, 0xFFFF );
    }

    //?
    if ( time == 0   || time == 4   || time == 8   || time == 12  ||
         time == 20  || time == 28  || time == 36  || time == 48  ||
         time == 60  || time == 120 || time == 122 || time == 124 ||
         time == 126 || time == 180 || time == 182 || time == 184 ||
         time == 186 )
    {
        GM_SeSet( &work->control.mov, SE_WET_STEP );
        s11e_zk11ecom_800D76F0( work );
    }

    if ( ( time > 186 && work->body.time2 ) || !( work->pad.press & 0x1000000 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}
