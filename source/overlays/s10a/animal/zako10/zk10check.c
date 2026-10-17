#include "zako10.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

extern void s10a_zk10action_800CAA80( Zako10Work *work, int time );
extern void s10a_zk10action_800CAA88( Zako10Work *work, int time );
extern void s10a_zk10action_800CAB70( Zako10Work *work, int time );
extern void Zako10ActReadyGun( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF50( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF58( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF60( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF68( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF70( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF78( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF80( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF88( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF90( Zako10Work *work, int time );
extern void s10a_zk10action_800CAF98( Zako10Work *work, int time );
extern void s10a_zk10action_800CAFA0( Zako10Work *work, int time );

/* the guards of this stage can not be damaged */
int Zako10CheckDamage( Zako10Work *work )
{
    return 0;
}

int Zako10CheckDir( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void Zako10ReviseReadyGun( Zako10Work* work )
{
    int trans;
    int rotx;

    trans = ( ( GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1] ) );
    trans = ratan2( work->sn_dis, trans  )  & 0xFFF;

    rotx = GV_NearExp8( work->adjust[2].vx, trans - 0x400 );
    work->adjust[2].vx = rotx;  /* 右腕 */
    work->adjust[6].vx = rotx;  /* 頭 */
    if ( rotx < 0 )             /* 左腕 */
    {
        work->adjust[7].vx = rotx * 3 ;
    }
    else
    {
        work->adjust[7].vx = ( rotx * 3 ) / 2 ;
    }
}

int Zako10CheckPad( Zako10Work *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF50 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF58 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF60 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF68 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF70 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF78 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF80 );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF88 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF90 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAF98 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetZako10Mode2( work, s10a_zk10action_800CAFA0 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetZako10Mode( work, s10a_zk10action_800CAA80 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetZako10Mode( work, s10a_zk10action_800CAA88 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetZako10Mode( work, s10a_zk10action_800CAB70 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetZako10Mode( work, Zako10ActReadyGun );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}
