#include "enemy.h"

int Think3_GoNext_800CC514( WatcherWork* work ) {
    if ( work->pad.time ) {
        (work->pad.press |= (  work->pad.tmp  )) ;
        work->pad.time -- ;
    }

    if ( DirectTrace_800CC154( work, 350 ) ) {
        return 1 ;
    }

    return 0 ;
}

int	Think3_BikkuriGetUp_800CC568( WatcherWork* work )
{
    if( work->count3 == 0){
        work->pad.press |= 0x00001000  ;
    } else  if( work->count3 > 90 || work->actend ){

        return 1 ;
    }
    work->count3 ++ ;
    return 0 ;
}

int	Think3_NoiseModeWatch_800CC5C0( WatcherWork *work )
{
    if ( work->act_status & 0x00000080  )
    {
        work->pad.press |= 0x00800000  ;
    }

    if( work->count3 == 0)
    {
        if(	EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
        {
            if( work->modetime[(  T_NOISE  )]  <= 1 )
            {
                work->pad.sound = (  0x88   ) ;
            }
            if( work->modetime[(  T_NOISE  )]  <= 3 )
            {
                ENE_PutMark_800C9378( work ,BW_MARK );
            }
            if ( !(work->act_status & 0x00000080 ) )
            {
                work->pad.dir = work->sn_dir;
            }
        }
        else
        {
            if( work->modetime[(  T_NOISE  )] ) return 1;
            work->pad.sound = 0x95;
            ENE_PutMark_800C9378( work ,BW_MARK );
            work->pad.dir = work->sn_dir;
        }
    }
    else
    {
        work->pad.dir = -1;
    }

    switch( work->modetime[(  T_NOISE  )] )
    {
        case 0:
            if( work->count3 >= 16)
            {
                if(	EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
                {
                    if ( !(work->act_status & 0x00000080 ) )
                    {
                        work->pad.sound = 0xF1;
                    }
                }
                return 1;
            }
            break;
        case 1:
        case 2:
            if ( work->count3 >= 48 )
            {
                return 1;
            }
            break;
        case 3:
            return 1;
    }
    work->count3++;
    return 0;
}