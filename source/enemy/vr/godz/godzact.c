// (VR only) this file is empty in the main executable build
// Action part of the vcd_n05 godzilla soldier (800C4DB8..800C7FD0): the meryl actions (enemy/merylaction.c) on the
// GodzWork layout, plus the "put char" effects. FIXME: functions that are not decompiled yet are relocatable asm
// (reloc/gen_godz.py act), they are called by their address based names.
#ifdef VR_EXE
#include "godzila.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/item.h"
#include "anime/animconv/anime.h"
#include "enemy/meryl.h"

// from takabe/mosaic.h
extern void *NewMosaic( MATRIX *, int, int, int );

extern GODZ_COMMAND  GodzCommand;
extern int           GODZ_EYE_LENGTH;

extern void   *NewSnow( int where );
extern void    NewBlood( MATRIX *, int );
extern void    AN_Breath( MATRIX * );
extern void   *NewLSight(SVECTOR *from, SVECTOR *to, int color);

extern int  GodzCheckPad( GodzWork *work );
extern int  GodzCheckDamage( GodzWork* work );
extern int  GodzCheckStun( GodzWork* work );
extern int  GodzCheckDir( int dir, int dist );
extern void GodzReviseReadyGun( GodzWork* work );
extern TARGET *GodzAttackForce( GodzWork *work );
extern void GodzAttackTouch( GodzWork *work );

void GodzAct_800C4DB8( GodzWork *work, int time );
void GodzAct_800C4FA0( GodzWork *work, int time );
void GodzAct_800C5278( GodzWork *work, int time );
void GodzAct_800C5308( GodzWork *work, int time );
void GodzAct_800C5388( GodzWork *work, int time );
void vcd_n05_800C5440( GodzWork *work, int time );
void GodzAct_800C5768( GodzWork *work, int time );
void GodzAct_800C57FC( GodzWork *work, int time );
void GodzAct_800C5904( GodzWork *work, int time );
void GodzAct_800C590C( GodzWork *work, int time );
void GodzAct_800C5AD4( GodzWork *work, int time );
void vcd_n05_800C5BA4( GodzWork *work, int time );
void GodzAct_800C5CF8( GodzWork *work, int time );
void GodzAct_800C5E70( GodzWork *work, int time );
void GodzAct_800C5F38( GodzWork *work, int time );
void GodzAct_800C5FF4( GodzWork *work, int time );
void GodzAct_800C62D8( GodzWork *work, int time );
void vcd_n05_800C6440( GodzWork *work, int time );
void GodzAct_800C6598( GodzWork *work, int time );
void GodzAct_800C66E4( GodzWork *work, int time );
void GodzAct_800C6814( GodzWork *work, int time );
void GodzAct_800C6F14( GodzWork *work, int time );
void GodzAct_800C70F4( GodzWork *work, int time );
void vcd_n05_800C71D8( GodzWork *work, int time );
void vcd_n05_800C7260( GodzWork *work, int time );
void vcd_n05_800C73B0( GodzWork *work );
void GodzAct_800C7658( GodzWork *work, int time );
void GodzAct_800C7724( GodzWork *work, int time );
void GodzAct_800C77F0( GodzWork *work, int time );
void GodzAct_800C7888( GodzWork *work, int time );
void GodzAct_800C7890( GodzWork *work, int time );
void GodzAct_800C7898( GodzWork *work, int time );
void GodzAct_800C78A0( GodzWork *work, int time );
void GodzAct_800C78A8( GodzWork *work, int time );
void GodzAct_800C78B0( GodzWork *work, int time );
void GodzAct_800C78B8( GodzWork *work, int time );
void GodzAct_800C78C0( GodzWork *work, int time );
void GODZ_PutBlood( GodzWork *work, int obj_idx, int count );
void GODZ_PutFog( GodzWork *work );
void GODZ_PutMark( GodzWork *work, int mark );
void vcd_n05_800C7A48( GodzWork *work );
void vcd_n05_800C7C60( GodzWork *work, int arg1 );
void GODZ_PutLSight( GodzWork *work );
void GODZ_PutBullet( GodzWork *work );
int GODZ_SetPutChar( GodzWork *work, int idx );
int GODZ_ClearPutChar( GodzWork *work, void *func );
void GODZ_ExecPutChar( GodzWork *work );

#define SE_GODZ_ROAR  0x87  // sound mode of the "G" soldier
#define SE_GODZ_ROAR2 0x80
#define SE_GODZ_HIT  0x8B   // sound effect of the soldier hit
#define SE_GODZ_FALL 0x8E   // sound effect of the soldier falling down

// animation table of the soldier (index = action number, see enemy/meryl.h)
short GodzActTable[54] =
{
    19, 20, 10, 22, 9, 34, 35, 36, 45, 13, 12, 26, 15, 14, 16, 27,
    8, 46, 50, 21, 30, 31, 32, 33, 37, 52, 53, 25, 5, 2, 42, 4,
    39, 40, 6, 7, 38, 3, 41, 17, 18, 43, 23, 24, 28, 29, 0, 1,
    51, 17, 18, 43, 22, 0
};

short godz_act_data_133C[10] = { 768, 895, 768, 895, 768, 895, 768, 895, 0, 0 };
short godz_act_data_1350[10] = { 632, 1254, 1204, 1279, 1736, 1164, 1636, 2620, 0, 0 };

SVECTOR godz_svec_1364 = { 0, 0, 100, 0 };
SVECTOR godz_svec_136C = { -1024, 0, 0, 0 };
SVECTOR godz_svec_1374 = { 0, 0, 100, 0 };
SVECTOR godz_svec_137C = { -1024, 0, 0, 0 };

void *GodzPutFuncList[4] =
{
    vcd_n05_800C7A48,
    vcd_n05_800C7C60,
    GODZ_PutLSight,
    GODZ_PutBullet
};

SVECTOR godz_svec_1394 = { 512, 1151, 0, 0 };
SVECTOR godz_svec_139C = { 948, 1656, 1596, 0 };
SVECTOR godz_svec_13A4 = { 5, -500, 80, 0 };


// the soldier has 5 hit boxes
static inline void SetTargetsClass( GodzWork *work, unsigned int flag )
{
    int i;
    TARGET **target;

    for ( i = 0, target = work->targets ; i < 5 ; target++, i++ )
    {
        SetTargetClass( *target, flag );
    }
}

/****Inlines**********************************************************************************************/
static inline void UnsetMode( GodzWork *work )
{
        work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), GodzActTable[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void UnsetMode2( GodzWork *work )
{
        work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), GodzActTable[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;

    if ( work->field_B74 )
    {
        GV_DestroyOtherActor( work->field_B74 );
        work->field_B74 = 0;
    }

}

static inline void SetAction( GodzWork *work, int n_action, int interp )
{
        work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), GodzActTable[ n_action ], 0, interp );
}

static inline void UnsetAction( GodzWork *work, int n_action )
{
    
    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), GodzActTable[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( GodzWork *work, int n_action, int a4 )
{
    
    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), GodzActTable[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( GodzWork *work )
{
    
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), GodzActTable[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor( work->subweapon );
}

void GodzAct_800C4DB8( GodzWork* work, int time )
{
    SetTargetsClass( work, TARGET_FLAG );
    work->act_status |= 1;

    if ( GodzCommand.mode == TOP_COMM_TRAVEL )
    {
        SetTargetsClass( work, TARGET_C4 );
    }

    work->vision.length = GODZ_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
        printf( "okiagari end!! %d !!!\\n", work->control.turn.vx );
    }

    if ( GodzCheckDamage( work ) || GodzCheckPad( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }


    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs( work->control.rot.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.mode & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetGodzMode( work, GodzAct_800C4FA0 );

        }
        else
        {
            work->control.turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir = work->control.rot.vy;
}

void GodzAct_800C4FA0( GodzWork* work, int time )
{
    int x, z;
    int s0;
    int interval;
    int tmp;
    int dist;
    CONTROL * ctrl;
    int field_8E0;
    int dir;
    SVECTOR* svec;

    SetTargetsClass( work, TARGET_FLAG );
    work->act_status |= 1;

    if ( GodzCommand.mode == TOP_COMM_TRAVEL )
    {
        SetTargetsClass( work, TARGET_C4 );
    }

    work->vision.length = GODZ_EYE_LENGTH ;

    if ( GodzCheckDamage( work ) || GodzCheckPad( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->unknown.last_set;
    svec = work->control.vecs;

    if ( (work->pad.mode & 0x1) && ( work->unknown.last_set != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->n_touches;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2( &ctrl->vecs[1] );
                if ( GV_DiffDirAbs( dir, tmp ) < GV_DiffDirAbs( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetGodzMode( work, GodzAct_800C4DB8);
        UnsetMode( work ) ;
        return;
    }


    switch ( GodzCheckDir( dir, dist ) )
    {
    case 1:
        dir = (dist - 1024) & 0xFFF;
        break;
    case 2:
        dir = (dist + 1024) & 0xFFF;
        break;
    }


    if ( !work->body.objs->bound_mode )
    {
        do { ctrl->rot.vy = dir; } while (0); //probably a macro
    }
    ctrl->turn.vy = dir;
    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 40;
    }
    else if ( field_8E0 == 2 )
    {
        interval = 100;
    }

    x = interval * rsin( dir );

    if ( x < 0 )
    {
        x += 0xFFF;
    }

    ctrl->step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->step.vz = z >> 12;
    work->vision.facedir = work->control.rot.vy;
}

void GodzAct_800C5278( GodzWork* work, int time )
{
    if ( time == 0 )
    {
        work->unknown.field_14 = 3;
        SetAction( work, ACTION35, 4 );
    }

    if ( !( GodzCheckDamage( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetGodzMode( work, vcd_n05_800C6440 );
    }
}

void GodzAct_800C5308( GodzWork *work, int time )
{
    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    work->control.turn.vy = work->pad.dir;

    if ( !( work->pad.press & 0x10000000 ) )
    {
        SetGodzMode( work, GodzAct_800C4DB8 );
    }
}

void GodzAct_800C5388( GodzWork *work, int time )
{
    if ( time == 0 )
    {
        if ( work->param.blood == 'G' )
        {
            SetAction( work, ACTION46, ACTINTERP );
            GM_SeSetMode( &work->control, SE_GODZ_ROAR, 1 );
        }
        else
        {
            SetAction( work, ACTION47, ACTINTERP );
            GM_SeSetMode( &work->control, SE_GODZ_ROAR2, 1 );
        }
    }

    if ( work->body.is_end )
    {
        SetGodzMode( work, GodzAct_800C4DB8 );
    }
}

#pragma INCLUDE_ASM_RELOC("source/enemy/vr/godz/reloc/godzact_0.s")

void GodzAct_800C5768( GodzWork *work, int time )
{
    if ( time == 0 )
    {
        work->visible = 0;
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( time == 90 )
    {
        if ( work->field_C4C >= 0 )
        {
            GCL_ExecProc( work->field_C4C, NULL );
        }
    }

    if ( time == 60 )
    {
        NewSnow( work->control.map->index );
    }
}

void GodzAct_800C57FC( GodzWork *work, int time )
{
    CONTROL *ctrl;

    SetTargetsClass( work, TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;
    ctrl = &( work->control );

    if ( time == 0 )
    {
        SetAction( work, ACTION16, ACTINTERP );
    }

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    if ( work->body.is_end || !( work->pad.press & 0x20 ) )
    {
        SetGodzMode( work, GodzAct_800C4DB8 );
        return;
    }

    ctrl->turn.vy = work->pad.dir;
    ctrl->step.vx = 0;
    ctrl->step.vz = 0;
    work->vision.facedir = work->control.rot.vy;
}

void GodzAct_800C5904( GodzWork *work, int time )
{
}

void GodzAct_800C590C( GodzWork* work, int time )
{
    int press;
    SetTargetsClass( work, TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;
    press = work->pad.press;

    if ( time == 0 )
    {
        if ( press & 0x10000 )
        {
            SetAction( work, ACTION3, ACTINTERP ) ;
        }
        else
        {
            SetAction( work, ACTION5, ACTINTERP );
        }
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
        GM_SeSetMode( &work->control.mov, 0xB2, GM_SEMODE_BOMB ) ;
    }

    GodzReviseReadyGun( work );
    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    if ( !(press & 0x30000) )
    {
        SetGodzMode( work, GodzAct_800C4DB8 ) ;
        return ;
    }

    if ( press & 0x40000 )
    {
        SetGodzModeFields( work, GodzAct_800C5AD4 ) ;
        return;
    }

    if ( press & 0x80000 )
    {
        SetGodzMode( work, vcd_n05_800C5BA4 ) ;
        return;
    }

    if ( press & 0x100000 )
    {
        SetGodzModeFields( work, GodzAct_800C5CF8 ) ;
        return;
    }

    if ( press & 0x200000 )
    {
        SetGodzModeFields( work, GodzAct_800C5E70 ) ;
        return;
    }

    work->control.turn.vy = work->pad.dir;
    work->vision.facedir = work->control.rot.vy;
}

void GodzAct_800C5AD4( GodzWork* work, int time )
{
    SetTargetsClass( work, TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION4, 0 ) ;
        GODZ_SetPutChar( work, 3 ) ;
        GM_ConfigMotionAdjust( &( work->body ), work->adjust ) ;
    }

    GodzReviseReadyGun( work );

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    SetGodzModeFields( work, GodzAct_800C590C );
}

#pragma INCLUDE_ASM_RELOC("source/enemy/vr/godz/reloc/godzact_1.s")

void GodzAct_800C5CF8( GodzWork* work, int time )
{
    SetTargetsClass( work, TARGET_FLAG ) ;
    work->vision.length = GODZ_EYE_LENGTH ;         /* 視力 */

    if ( time == 0 )
    {
        extern  void    *NewGrenadeEnemy( CONTROL *, OBJECT *, int, u_long *, SVECTOR *, int ) ;

        SetAction( work, GRENADE, ACTINTERP ) ;
        work->subweapon = NewGrenadeEnemy( &(work->control), &(work->body), 9,
                                     &(work->trigger), &GM_PlayerPosition, ENEMY_SIDE ) ;
    }

    if ( time > ACTINTERP )
    {
        work->trigger |= WEAPON_TAKE ;
    }
    if ( time == 17 )
    {
        GM_SeSet( &( work->control.mov ), SE_PINNUKI ) ;
    }
    if ( time == 45 )
    {
        work->trigger |= WEAPON_TRIG2 ;
    }

    if ( GodzCheckDamage( work ) )
    {
        GV_DestroyOtherActor( work->subweapon ) ;
        return ;
    }


    if ( work->body.is_end )
    {
        GV_DestroyOtherActor( work->subweapon ) ;
        SetGodzMode( work, GodzAct_800C590C );
    }
}

void GodzAct_800C5E70( GodzWork* work, int time )
{
    SetTargetsClass( work, TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;

    if ( time == 0 )
    {
        SetAction( work, ACTION8, 0 );
    }

    if ( time == 3 )
    {
        if ( GodzAttackForce( work ) )
        {
            GM_SeSet( &( work->control.mov ), SE_HIT );
        }
    }

    work->control.turn.vy = work->sn_dir;

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    if ( work->body.is_end )
    {
        SetGodzMode( work, GodzAct_800C590C );
    }
}

void GodzAct_800C5F38( GodzWork* work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction( work, ACTION21, ACTINTERP ) ;
    }

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    SetTargetsClass( work, TARGET_FLAG );

    if ( work->body.is_end )
    {
        work->actend = 1;
        SetGodzMode( work, GodzAct_800C4DB8 );
    }
}

void GodzAct_800C5FF4( GodzWork* work, int time )
{
    CONTROL *ctrl;
    TARGET  *target;

    target = work->targets[0];
    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        work->unknown.field_14 = 6;
        SetAction( work, ACTION31, ACTINTERP );
    }

    if ( time - 8 < 12u )
    {
        GodzAttackTouch( work );
    }

    if ( work->unknown.last_set == 31 )
    {
        if ( time == 22 )
        {

            if ( ctrl->mov.vy - ctrl->levels[0] < 2000 )
            {
                GM_SeSet( &ctrl->mov, 0xC3 ) ;
                GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
                GODZ_PutBlood( work, 6, 0 ) ;
                GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            }
        }
        if ( work->body.is_end )
        {
            if ( !ctrl->grounded )
            {
                SetAction( work, ACTION40, ACTINTERP );
            }
            else
            {
                SetGodzMode( work, vcd_n05_800C6440 );
            }
        }
    }
    else
    {
        if ( ctrl->grounded )
        {
            GM_SeSet( &ctrl->mov, 0xC3 ) ;
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &work->control.mov ) ;
            GODZ_PutBlood( work, 6, 1 ) ;
            SetGodzMode( work, vcd_n05_800C6440 );
        }
    }
    if ( time < 24 )
    {
        ctrl->turn = *target->field_1C;
    }

    if ( time < 22 )
    {
        work->control.hzd_height = -32767;
    }
}

void GodzAct_800C62D8( GodzWork *work, int time )
{
    CONTROL *ctrl;
    int time_offset;

    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->vision.length = 0;
    work->act_status |= 0x8;

    if ( time == 0 )
    {
        SetAction( work, ACTION32, ACTINTERP ) ;
    }

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    time_offset = 10;

    if ( time == time_offset )
    {
        work->unknown.field_14 = 1;
        SetAction( work, ACTION37, ACTINTERP ) ;
    }
    else
    {
        SetTargetsClass( work, TARGET_FLAG );
    }

    if ( time == time_offset + 24 )
    {
        GM_SeSet( &ctrl->mov, SE_ENEMY_COLLAPSE );
    }

    if ( time == time_offset + 46 )
    {
        GM_SeSet( &ctrl->mov, SE_HIT_FLOOR );
    }

    if ( time >= time_offset + 50 && work->body.is_end )
    {
        SetGodzMode( work, vcd_n05_800C6440 ) ;
    }
}

#pragma INCLUDE_ASM_RELOC("source/enemy/vr/godz/reloc/godzact_2.s")

void GodzAct_800C6598( GodzWork* work, int time )
{
    work->unknown.field_1E = 0;
    work->act_status |= 0x08;

    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            if ( work->field_B6A >= 0x5A )
            {
                SetAction( work, ACTION44, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION42, ACTINTERP );
            }
        }
        else
        {
            if ( work->field_B6A >= 0x5A )
            {
                SetAction( work, ACTION45, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION43, ACTINTERP );
            }
        }
    }

    if ( work->body.is_end )
    {
        SetGodzMode( work, GodzAct_800C4DB8 );
    }
}

void GodzAct_800C66E4( GodzWork* work, int time )
{
    TARGET* target;

    work->unknown.field_1E = 0;
    SetTargetsClass( work, TARGET_FLAG );
    work->vision.length = GODZ_EYE_LENGTH ;
    work->act_status |= 0x08;

    if ( GodzCheckDamage( work ) )
    {
        return ;
    }

    target = work->targets[0];
    if (time == 0 )
    {
        SetAction( work, ACTION15, ACTINTERP ) ;

        GM_SeSet( &work->control.mov, SE_GODZ_HIT );
        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, SE_PUNCH_HIT );
            GODZ_PutFog( work );
        }
        else
        {
            GODZ_PutBlood( work, 5, 0 );

        }
    }

    if ( work->body.is_end)
    {
        SetGodzMode( work, GodzAct_800C4DB8 ) ;
    }
}

void GodzAct_800C6814( GodzWork *work, int time )
{
    CONTROL* ctrl;
    WatcherUnk *unk;

    unk = &work->unknown;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;
    work->control.step = work->targets[0]->force;


    ctrl = &work->control;
    if ( time == 0 )
    {
        switch( unk->field_14 )
        {
        case 0:
            GM_SeSet( &ctrl->mov, SE_PUNCH_HIT );
            SetAction( work, ACTION34, ACTINTERP );
            GM_SeSet( &ctrl->mov, 0xC3 );
            GODZ_PutBlood( work, 5, 0 );
            work->field_B6A = 17;
            break;
        case 1:
            SetAction( work, ACTION37, ACTINTERP );
            if ( work->targets[0]->vital <= 0 )
            {
                if ( GM_Weapon == WP_Rifle )
                {
                    GODZ_PutBlood( work, 6, 2 );
                }
                else
                {
                    GODZ_PutBlood( work, 6, 1 );
                }
            }
            else
            {
                GODZ_PutBlood( work, 5, 0 );

            }
            GM_SeSet( &ctrl->mov, 0xC3 );
            work->field_B6A = 46;
            break;
        case 3:
            GM_SeSet( &ctrl->mov, 0xC3 );
            SetAction( work, ACTION35, ACTINTERP );
            GODZ_PutBlood( work, 5, 0 );
            work->field_B6A = 17;
            break;
        case 2:
            GM_SeSet( &ctrl->mov, 0xC4 );
            SetAction( work, ACTION36, ACTINTERP );
            GODZ_PutBlood( work, 5, 0 );
            work->field_B6A = 22;
            break;
        case 4:
            GM_SeSet( &ctrl->mov, 0x90 );
            GM_SeSet( &ctrl->mov, 0xBF );
            SetAction( work, ACTION29, ACTINTERP );
            work->field_B6A = 67;
            break;
        case 5:
            SetAction( work, ACTION30, ACTINTERP );
            work->field_B6A = 15;
        break;
        }
    }

    if ( time == 2 && work->targets[0]->vital <= 0 && GM_GameOverTimer == 0 && GM_Vitality > 0 )
    {
        if ( work->field_C4C >= 0 )
        {
            GCL_ExecProc( work->field_C4C, 0 );
        }

        GM_GameOver();
        GM_GameOverTimer = -2;
        GM_GameStatus |= STATE_PADRELEASE;

        if ( GM_StreamStatus() == -1 )
        {
            GM_VoxStream( work->field_C44, 0 );
        }
    }

    switch( unk->field_14 )
    {
    case 0:
        if ( time < 12 )
        {
            ctrl->turn.vy += 170;
        }

        if ( time - 7 < 23u )
        {
            GodzAttackTouch( work );
        }

        if ( time < 20 )
        {
            work->control.hzd_height = -32767;
        }
        break;
    case 1:
        if ( time == 24 )
        {
            GM_SeSet( &ctrl->mov, SE_ENEMY_COLLAPSE );
        }
        break;
    case 3:
        if ( time - 7 < 23u )
        {
            GodzAttackTouch( work );
        }
        if ( time < 15 )
        {
            ctrl->hzd_height = -32767;
        }
        break;
    case 2:
        if ( time - 7 < 23u )
        {
            GodzAttackTouch( work );
        }
        if ( time < 20 )
        {
            ctrl->hzd_height = -32767;
        }
        break;
    case 4:
    case 5:
        work->act_status |= 0x04;
        break;
    }

    if ( time > 16 && ctrl->grounded )
    {
        ctrl->step = DG_ZeroVector;
    }

    if ( time == work->field_B6A )
    {
        if (ctrl->mov.vy - ctrl->levels[0] < 2000)
        {
            GM_SeSet( &ctrl->mov, SE_HIT_FLOOR ) ;
            GM_SetNoise( 0x64, 4, &ctrl->mov ) ;
            GODZ_PutBlood( work, 6, 0 ) ;
        }
    }

    if ( work->body.is_end )
    {
        work->unknown.field_1E = 1;
        work->targets[0]->force = DG_ZeroVector;
        if ( work->targets[0]->vital <= 0 )
        {
            SetGodzMode( work, GodzAct_800C70F4 );
        }
        else
        {
            SetGodzMode( work, vcd_n05_800C6440 );
        }
    }
}

void GodzAct_800C6F14( GodzWork* work, int time )
{
    CONTROL *ctrl;

    ctrl = &work->control;
    work->unknown.field_1E = 0;
    work->act_status |= 0x8;

    ctrl->step = work->targets[0]->force;

    if ( time == 0 && work->unknown.field_14 != 2 )
    {
        GM_SeSet( &ctrl->mov, SE_GODZ_FALL );
    }

    if ( time > 16 && ctrl->grounded )
    {
        ctrl->step = DG_ZeroVector;
    }

    if ( work->unknown.last_set < 39 )
    {

        if ( work->body.is_end )
        {
            if ( work->unknown.field_14 < 3 )
            {
                if ( work->unknown.field_14 == 1 )
                {
                    SetAction( work, ACTION41, ACTINTERP );
                }
                else
                {
                    SetAction( work, ACTION39, ACTINTERP );
                }
            }
            else
            {
                SetAction( work, ACTION40, ACTINTERP );
            }
        }
    }
    else if ( ctrl->grounded )
    {
        work->unknown.field_1E = 1;
        work->targets[0]->force = DG_ZeroVector;
        GM_SeSet( &ctrl->mov, SE_HIT_FLOOR );
        GODZ_PutBlood( work, 6, 1 );
        SetGodzMode( work, GodzAct_800C70F4 );
    }
}

void GodzAct_800C70F4( GodzWork *work, int time )
{
    work->act_status |= 0x40;
    if ( time == 0 )
    {
        if ( work->unknown.field_14 < 3 )
        {
            if ( work->unknown.field_14 == 1 )
            {
                SetAction( work, ACTION51, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION49, ACTINTERP );
            }
        }
        else
        {
            SetAction( work, ACTION50, ACTINTERP );
        }
        GM_ConfigControlAttribute( &work->control, 0 );
        work->alert_level = 0;

        if ( GM_GameOverTimer == -2 )
        {
            GM_GameOverTimer = 1;
        }
    }

    if ( time > 450 && GM_StreamStatus() == -1  )
    {
        GM_GameOver();
    }
}

#pragma INCLUDE_ASM_RELOC("source/enemy/vr/godz/reloc/godzact_3.s")

void GodzAct_800C7658( GodzWork* work, int time )
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

void GodzAct_800C7724( GodzWork* work, int time)
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

void GodzAct_800C77F0( GodzWork* work, int time )
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

void GodzAct_800C7888( GodzWork *work, int time )
{
}

void GodzAct_800C7890( GodzWork *work, int time )
{
}

void GodzAct_800C7898( GodzWork *work, int time )
{
}

void GodzAct_800C78A0( GodzWork *work, int time )
{
}

void GodzAct_800C78A8( GodzWork *work, int time )
{
}

void GodzAct_800C78B0( GodzWork *work, int time )
{
}

void GodzAct_800C78B8( GodzWork *work, int time )
{
}

void GodzAct_800C78C0( GodzWork *work, int time )
{
}

void GODZ_PutBlood( GodzWork* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos( &godz_svec_1364 );
    DG_RotatePos( &godz_svec_136C );
    ReadRotMatrix( &mat );
    NewBlood( &mat, count );
}

void GODZ_PutFog(GodzWork *work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &godz_svec_1374 );
    DG_RotatePos( &godz_svec_137C );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    AN_Fog( &svec );
}

void GODZ_PutMark( GodzWork *work, int mark )
{
    MATRIX *mat;
    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    mat = &work->body.objs->objs[6].world;
    if( mark == 0 )
    {
        COM_CallBikkuriSe( &work->control.mov , 0x10 );
    }

    if ( work->mark_time )
    {
        GV_DestroyOtherActor( work->mark );
    }

    work->mark = AN_HeadMark( mat , mark ) ;
    work->mark_time = 30;
}

#pragma INCLUDE_ASM_RELOC("source/enemy/vr/godz/reloc/godzact_4.s")

void GODZ_PutLSight( GodzWork* work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

void GODZ_PutBullet( GodzWork *work )
{
    MATRIX* mat;
    SVECTOR svec;
    MATRIX local_mat;

    svec = DG_ZeroVector;
    svec.vx = GV_RandS( 16 );
    svec.vz = GV_RandU( 128 );
    mat = &work->body.objs->objs[4].world;

    DG_SetPos( mat );
    DG_MovePos( &godz_svec_13A4 );
    DG_RotatePos( &svec );
    ReadRotMatrix( &local_mat );

    if ( GV_Time & 3 )
    {
        NewBulletEnemy( &local_mat, ENEMY_SIDE, 1, 0, 1 );
    }
    else
    {
        NewBulletEnemy( &local_mat, ENEMY_SIDE, 1, 0, 0 );
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );
    AN_BulletSmoke( mat, 0 );
    AN_FamasFlash( &local_mat );
    GODZ_ClearPutChar( work, GODZ_PutBullet );
}

int GODZ_SetPutChar( GodzWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[ i ] == NULL )
        {
            work->field_B10[ i ] = GodzPutFuncList[ idx ];
            return 1;
        }
    }
    return 0;
}

int GODZ_ClearPutChar( GodzWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[ i ] == func )
        {
            work->field_B10[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

void GODZ_ExecPutChar( GodzWork* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B10[i] )
        {
            PUTFUNC func = work->field_B10[i];
            func( work );
        }
    }
}

#endif
