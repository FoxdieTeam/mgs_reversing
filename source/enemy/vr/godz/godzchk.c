// (VR only) this file is empty in the main executable build
#ifdef VR_EXE
#include "godzila.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

extern void s10a_zk10action_800CAA80( GodzWork *work, int time );
extern void s10a_zk10action_800CAA88( GodzWork *work, int time );
extern void s10a_zk10action_800CAB70( GodzWork *work, int time );
extern void GodzActReadyGun( GodzWork *work, int time );
extern void s10a_zk10action_800CAF50( GodzWork *work, int time );
extern void s10a_zk10action_800CAF58( GodzWork *work, int time );
extern void s10a_zk10action_800CAF60( GodzWork *work, int time );
extern void s10a_zk10action_800CAF68( GodzWork *work, int time );
extern void s10a_zk10action_800CAF70( GodzWork *work, int time );
extern void s10a_zk10action_800CAF78( GodzWork *work, int time );
extern void s10a_zk10action_800CAF80( GodzWork *work, int time );
extern void s10a_zk10action_800CAF88( GodzWork *work, int time );
extern void s10a_zk10action_800CAF90( GodzWork *work, int time );
extern void s10a_zk10action_800CAF98( GodzWork *work, int time );
extern void s10a_zk10action_800CAFA0( GodzWork *work, int time );

/* the guards of this stage can not be damaged */
int GodzCheckDamage( GodzWork *work )
{
    return 0;
}

int GodzCheckDir( int dir, int dist )
{
    int diff ;
    if ( dist < 0 || dir < 0 ) return 0 ;

    diff = GV_DiffDirS( dir, dist ) ;

    if ( diff + 0x380 > 0x700u ) return 0 ;
    if ( diff >= 0 ) return 1 ;

    return 2 ;
}

void GodzReviseReadyGun( GodzWork* work )
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

int GodzCheckPad( GodzWork *work )
{
    int press = work->pad.press;

    if ( press & 0x01 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF50 );
        return 0;
    }

    if ( press & 0x02 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF58 );
        return 0;
    }

    if ( press & 0x04 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF60 );
        return 0;
    }

    if ( press & 0x2000 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF68 );
        return 0;
    }

    if ( press & 0x40 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF70 );
        return 0;
    }

    if ( press & 0x80 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF78 );
        return 0;
    }

    if ( press & 0x400 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF80 );
        return 0;
    }

    if ( press & 0x800 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF88 );
        return 0;
    }

    if ( press & 0x200 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF90 );
        return 0;
    }

    if ( press & 0x800000 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAF98 );
        return 0;
    }

    if ( press & 0x1000000 )
    {
        SetGodzMode2( work, s10a_zk10action_800CAFA0 );
        return 0;
    }

    if ( press & 0x100 )
    {
        SetGodzMode( work, s10a_zk10action_800CAA80 );
        return 1;
    }

    if ( press & 0x20 )
    {
        SetGodzMode( work, s10a_zk10action_800CAA88 );
        return 1;
    }

    if ( press & SP_DANBOWLKERI )
    {
        SetGodzMode( work, s10a_zk10action_800CAB70 );
        return 1;
    }

    if ( press & 0x30000 )
    {
        SetGodzMode( work, GodzActReadyGun );
        work->adjust[2].vx = 0;
        return 1;
    }

    return 0;
}
#endif
