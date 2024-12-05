#include "meryl72.h"
#include "Game/linkvarbuf.h"

extern void s07c_meryl72_unk1_800CA408( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CA538( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9F98( Meryl72Work *work, int time ) ;
extern int s07c_meryl72_unk1_800C7D1C( Meryl72Work* work ) ;
extern int s07c_meryl72_unk1_800C7C9C( Meryl72Work* work ) ;
extern int s07c_meryl72_unk1_800C7F14( Meryl72Work* work ) ;
void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);

extern int GM_GameOverTimer ;
extern SVECTOR DG_ZeroVector ;
extern int GM_PlayerMap_800ABA0C ;
extern OBJECT  *GM_PlayerBody_800ABA20 ;

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
            SetModeFields( work, s07c_meryl72_unk1_800C9970 ) ;
        }
        else
        {
            SetModeFields( work, s07c_meryl72_unk1_800C9B30 ) ;
        }
        target->damaged = 0;
        return 1;
    }
    return 0;
}

int s07c_meryl72_unk1_800C7D00( Meryl72Work* work ) {
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
            target->field_2C_vec = DG_ZeroVector;
            target->field_26_hp -= GM_SnakeMaxHealth / 48;
            
            if ( ( target->field_2A <= 0 ) || ( ( target->field_26_hp << 16 ) <= 0 ) )
            {
                work->f8BC.field_14 = 1;
                SetModeFields( work, s07c_meryl72_unk1_800CA538 ) ;

            }
            else
            {
                SetModeFields( work, s07c_meryl72_unk1_800CA408 ) ;
            }
            break;
        case 4:
            work->f8BC.field_14 = 0;
            target->field_26_hp -= GM_SnakeMaxHealth / 32;
            SetModeFields( work, s07c_meryl72_unk1_800CA538 ) ;
            break;
        case 1:
            target->field_2C_vec = DG_ZeroVector;
            if ( target->field_26_hp <= 0 )
            {
                work->f8BC.field_14 = 1;
                SetModeFields( work, s07c_meryl72_unk1_800CA538 ) ;
            }
            else
            {
                SetModeFields( work, s07c_meryl72_unk1_800CA408 ) ;
            }
            break;
        case 2:
            work->f8BC.field_14 = 3;
            SetModeFields( work, s07c_meryl72_unk1_800CA538 ) ;
        }

        target->field_28 = 0;
        target->damaged = 0;
    
        if ( target->field_26_hp <= 0 && !GM_GameOverTimer && GM_SnakeCurrentHealth > 0 )
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
    if ( GM_GameStatus & 2 && work->control.map->index & GM_PlayerMap_800ABA0C)
    {
        SetModeFields(work, s07c_meryl72_unk1_800C9F98);
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

    trans = ( ( GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
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
    sna_act_helper2_helper2_80033054( work->control.name, &work->rots[22].vx );
}