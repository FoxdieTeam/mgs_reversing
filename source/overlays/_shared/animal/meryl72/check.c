#include "meryl72.h"

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

extern void s07c_meryl72_unk1_800CA408( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CA538( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9F98( Meryl72Work *work, int time ) ;
extern int s07c_meryl72_unk1_800C7D1C( Meryl72Work* work ) ;
extern int s07c_meryl72_unk1_800C7C9C( Meryl72Work* work ) ;
extern int s07c_meryl72_unk1_800C7F14( Meryl72Work* work ) ;
extern void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);

void ExecProc_800C7C58( Meryl72Work *work, int mode )
{
    GCL_ARGS    args ;
    long        data[4] ;
    if ( work->proc_id < 0 ) return ;
    args.argc = 1 ;
    args.argv = data ;
    data[0] = mode ;
    GCL_ExecProc( work->proc_id, &args ) ;
}

extern void s07c_meryl72_unk1_800C9970( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9B30( Meryl72Work *work, int time ) ;

int s07c_meryl72_unk1_800C7C9C( Meryl72Work* work )
{
    TARGET *target;

    target= work->target;
    if (  target->damaged & 2 )
    {
        if ( target->a_mode == 0x24 )
        {
            SetMode( work, s07c_meryl72_unk1_800C9970 ) ;
        }
        else
        {
            SetMode( work, s07c_meryl72_unk1_800C9B30 ) ;
        }
        target->damaged = 0;
        return 1;
    }
    return 0;
}

int s07c_meryl72_unk1_800C7D00( Meryl72Work* work )
{
    int check;
    check = work->target->damaged & 0x20;
    return check > 0;
}

int s07c_meryl72_unk1_800C7D1C( Meryl72Work *work )
{
    TARGET *target;

    target = work->target;
    if ( ( target->damaged & TARGET_POWER ) )
    {
        switch ( target->a_mode )
        {
        case 3:
            target->scale = DG_ZeroVector;
            target->life -= GM_SnakeMaxHealth / 48;

            if ( ( target->faint <= 0 ) || ( ( target->life << 16 ) <= 0 ) )
            {
                work->f8BC.field_14 = 1;
                SetMode( work, s07c_meryl72_unk1_800CA538 ) ;

            }
            else
            {
                SetMode( work, s07c_meryl72_unk1_800CA408 ) ;
            }
            break;
        case 4:
            work->f8BC.field_14 = 0;
            target->life -= GM_SnakeMaxHealth / 32;
            SetMode( work, s07c_meryl72_unk1_800CA538 ) ;
            break;
        case 1:
            target->scale = DG_ZeroVector;
            if ( target->life <= 0 )
            {
                work->f8BC.field_14 = 1;
                SetMode( work, s07c_meryl72_unk1_800CA538 ) ;
            }
            else
            {
                SetMode( work, s07c_meryl72_unk1_800CA408 ) ;
            }
            break;
        case 2:
            work->f8BC.field_14 = 3;
            SetMode( work, s07c_meryl72_unk1_800CA538 ) ;
        }

        target->life_lost = 0;
        target->damaged = 0;

        if ( target->life <= 0 && !GM_GameOverTimer && GM_SnakeCurrentHealth > 0 )
        {
            ExecProc_800C7C58( work, 1 ) ;
            GM_GameOver();
            GM_GameOverTimer = -2;
        }

        return 1;
    }
    return 0;
}

int s07c_meryl72_unk1_800C7F14(Meryl72Work* work)
{
    if ( GM_GameStatus & 2 && work->control.map->index & GM_PlayerMap)
    {
        SetMode(work, s07c_meryl72_unk1_800C9F98);
        return 1;
    }
    return 0;
}

int CheckDamage_800C7F6C(Meryl72Work* work )
{
    if ( s07c_meryl72_unk1_800C7D1C( work ) || s07c_meryl72_unk1_800C7C9C( work ) || s07c_meryl72_unk1_800C7F14( work ) )
    {
        work->target->class = TARGET_AVAIL ;
        return 1;
    }
    return 0;
}

int s07c_meryl72_unk1_800C7FCC( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void ReviseReadyGun_800C8020( Meryl72Work* work )
{
    int trans;
    int near;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ( ratan2( work->sn_dis, trans  )  & 0xFFF ) - 0x400;

    if (trans > 0x100)
    {
        trans = 0x100;
    }
    else if (trans < -0x100)
    {
        trans = -0x100;
    }

    work->rots[21].vx = trans;
    near = GV_DiffDirS( work->control.rot.vy, work->sn_dir );
    if ( ( near + 0x1FF ) < 0x3FFu)
    {
        work->rots[21].vy = near;
    }
}

void s07c_meryl72_unk1_800C80B4( Meryl72Work* work )
{
    sna_act_helper2_helper2_80033054( work->control.name, &work->rots[22] );
}

const SVECTOR rp_shift_800D4830  = { -200,  100, 900 };
const SVECTOR rp_shift2_800D4838 = { -200, -500, 600 };
const SVECTOR force_800D4840     = { 5, 0, 100 };
const SVECTOR size_800D4848      = { 400, 200, 400 };

int AttackForce_800C80DC( Meryl72Work * work, int check )
{
    TARGET *target;

    SVECTOR svec;
    SVECTOR rp_shift;
    SVECTOR rp_shift2;
    SVECTOR force;
    SVECTOR force2;
    SVECTOR size;

    rp_shift  = rp_shift_800D4830; /* 右パンチ */
    rp_shift2 = rp_shift2_800D4838;
    force     = force_800D4840;
    memset(&force2, 0, 8);
    size      = size_800D4848;

    target = &work->punch;
    GM_SetTarget( target, TARGET_POWER, ENEMY_SIDE, &size );
    DG_SetPos2( &work->control.mov, &work->control.rot );

    if ( !check )
    {
        DG_RotVector( &force, &svec, 1 );
        GM_Target_8002DCCC( target, 0, 2, 16, 1, &svec );
        DG_PutVector( &rp_shift, &work->punch.center, 1 );
    }
    else
    {
        DG_RotVector( &force2, &svec, 1 );
        GM_Target_8002DCCC( target, 0, 2, 16, 1, &svec );
        DG_PutVector( &rp_shift2, &work->punch.center, 1 );
    }

    return GM_PowerTarget( target );
}

int s07c_meryl72_unk1_800C829C( Meryl72Work * work )
{
    if ( GM_CurrentItemId != 8 )
    {
        if ( ( GM_SnakeCurrentHealth < 17 ) )
        {
           if ( GM_CurrentItemId == 13 )
           {
               if ( 1 == GM_FrozenItemsState )
               {
                   return 1;
               }
           }
           else
           {
               return 1;
           }
        }
    }
    else if ( GM_SnakeCurrentHealth < 9 )
    {
        return 1;
    }
    return 0;
}

int CheckPad_800C8308( Meryl72Work *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CAD30 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CADEC );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetMode2( work, ActOverScoutD_800CAEA8 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CAF30 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CAFB8 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CB038 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CB0B8 );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CB134 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetMode2( work, s07c_meryl72_unk1_800CB1B4 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetMode( work, s07c_meryl72_unk1_800C88EC );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetMode( work, s07c_meryl72_unk1_800C8970 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetMode( work, s07c_meryl72_unk1_800C8A30 );
        return 1;
    }

    if ( press & 0x4000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C8BC4 );
        return 1;
    }

    if ( press & 0x800000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C8E74 );
        return 1;
    }

    if ( press & 0x1000000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C8C7C );
        return 1;
    }

    if ( press & 0x2000000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C9000 );
        return 1;
    }

    if ( press & 0x4000000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C90C8 );
        return 1;
    }

    if ( press & 0x20000000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C9190 );
        return 1;
    }

    if ( press & 0x10000000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C9258 );
        return 1;
    }

    if ( press & 0x40000000 )
    {
        SetMode( work, s07c_meryl72_unk1_800C9318 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetMode( work, ActReadyGun_800C9428 );
        return 1;
    }

    return 0;
}