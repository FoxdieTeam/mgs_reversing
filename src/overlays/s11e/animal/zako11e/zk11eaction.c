#include "../../../s00a/Enemy/enemy.h"

/****Inlines**********************************************************************************************/

static inline void UnsetMode( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
}

static inline void SetAction( ZakoWork *work, int n_action, int interp )
{
    extern short    ActTable_800C35EC[];
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->body ), ActTable_800C35EC[ n_action ], 0, interp );
}

static inline void UnsetAction( ZakoWork *work, int n_action )
{
    extern short    ActTable_800C35EC[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( ZakoWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C35EC[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ n_action ], 0, ACTINTERP, a4 );
}

static inline void UnsetAction2( ZakoWork *work )
{
    extern short    ActTable_800C35EC[];

    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C35EC[ STANDSTILL ], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor_800151D8( work->subweapon );
}

/*********************************************************************************************************/

extern ZAKO_COMMAND ZakoCommand_800DF280;
extern int ZAKO_EYE_LENGTH_800C3904;

extern int CheckPad_800D4A28( ZakoWork *work );
extern int CheckDamage_800D46A0( ZakoWork * work );

extern void s11e_zk11ecom_800D4DD4( ZakoWork *work, int time );

void ActStandStill_800D4C2C(ZakoWork* work, int time )
{
    SetTargetClass( work->target, TARGET_FLAG );
    work->act_status |= 1;

    if ( ZakoCommand_800DF280.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO_EYE_LENGTH_800C3904 ;

    if ( time == 0 )
    {
        SetAction( work, STANDSTILL, ACTINTERP );
    }

    if ( CheckDamage_800D46A0( work ) || CheckPad_800D4A28( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    if ( work->pad.dir >= 0 )
    {
        if ( GV_DiffDirAbs_8001706C( work->control.field_8_rot.vy, work->pad.dir ) < 0x100 )
        {
            if ( work->pad.mode & 0x1 )
            {
                SetAction( work, ACTION2, ACTINTERP );
            }
            else
            {
                SetAction( work, ACTION1, ACTINTERP );
            }
            SetZakoMode( work, s11e_zk11ecom_800D4DD4 );

        }
        else
        {
            work->control.field_4C_turn.vy = work->pad.dir;
        }
    }
    work->vision.facedir =work->control.field_8_rot.vy;
}

extern int s11e_zk11ecom_800D47D4( int, int ) ;

void s11e_zk11ecom_800D4DD4( ZakoWork* work, int time )
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

    SetTargetClass( work->target, TARGET_FLAG );

    if ( ZakoCommand_800DF280.mode == TOP_COMM_TRAVEL )
    {
        work->target->class |= TARGET_C4 ;
    }

    work->vision.length = ZAKO_EYE_LENGTH_800C3904 ;

    if ( CheckDamage_800D46A0( work ) || CheckPad_800D4A28( work ) )
    {
        UnsetMode( work ) ;
        return ;
    }

    dist = -1;
    ctrl = &(work->control );
    dir = work->pad.dir;
    field_8E0 = work->field_8E0;
    svec = work->control.field_60_vecs_ary;

    if ( (work->pad.mode & 0x1) && ( work->field_8E0 != ACTION2 ) )
    {
        SetAction( work, ACTION2, ACTINTERP );
    }

    if ( dir >= 0 )
    {
        s0 = ctrl->field_58;
        if ( s0 > 0 )
        {
            dist = GV_VecDir2_80016EF8( svec );

            if ( s0 >= 2 )
            {
                tmp = GV_VecDir2_80016EF8( &ctrl->field_60_vecs_ary[1] );
                if ( GV_DiffDirAbs_8001706C( dir, tmp ) < GV_DiffDirAbs_8001706C( dir, dist ) )
                {
                    dist = tmp;
                }
            }
        }
    }

    if ( dir < 0 )
    {
        SetZakoMode( work, ActStandStill_800D4C2C);
        UnsetMode( work ) ;
        return;
    }


    switch ( s11e_zk11ecom_800D47D4( dir, dist ) )
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
        do { ctrl->field_8_rot.vy = dir; } while (0); //probably a macro
    }
    ctrl->field_4C_turn.vy = dir;
    interval = 0;

    if ( field_8E0 == 1 )
    {
        interval = 50;
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

    ctrl->field_44_step.vx = x >> 12;

    z = interval * rcos( dir );

    if ( z < 0 )
    {
        z += 0xFFF;
    }

    ctrl->field_44_step.vz = z >> 12;
    work->vision.facedir = work->control.field_8_rot.vy;
}

extern void s11e_zk11ecom_800D603C( ZakoWork* work, int time ) ;

void s11e_zk11ecom_800D506C( ZakoWork* work, int time )
{
    if ( time == 0 )
    {
        work->field_8DC = 3;
        SetAction( work, ACTION35, 4 );
    }

    if ( !( CheckDamage_800D46A0( work ) ) && ( work->body.is_end ) )
    {
        work->pad.tmp = 0;
        SetZakoMode( work, s11e_zk11ecom_800D603C );
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D50FC.s")

void s11e_zk11ecom_800D51E4(ZakoWork* work, int time )
{

}

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D51EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5360.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5410.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D54C8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5620.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D56F8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D57A0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5A84.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5B04.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5E78.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D5EEC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D603C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D61B4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D627C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D638C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D649C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D69F8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6BD8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6CE8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6DDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D6F68.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7034.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7100.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7198.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7230.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D72E4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D73AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7450.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7518.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D76F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7730.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7878.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7A14.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7A84.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7AE8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7C10.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7CAC.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7D44.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7E8C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D7EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8004.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D804C.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800D8080.s")
