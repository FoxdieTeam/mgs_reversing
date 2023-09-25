#include "Game/linkvarbuf.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "Game/game.h"

typedef struct _PadWork
{
    int field_00;
    int press;
    int field_08;
    int tmp;
    int time;
} PadWork;

typedef struct _Work
{
    GV_ACT       field_0_actor;
    CONTROL      field_20_control;
    OBJECT       field_9C_object;
    char         field_C0_padding[0x820];
    short        field_8E0;
    short        field_8E2;
    short        field_8E4;
    short        field_8E6;
    char         field_8E8_padding[0x04];
    void*        field_8EC_func;
    void*        field_8F0_func;
    int          field_8F4;
    int          field_8F8;
    int          actend;                     //0x8FC
    SVECTOR     *field_900;
    char         field_904_padding[0x220];
    int          field_B24;                  //0xB24
    unsigned int count3;                     //0xB28
    int          field_B2C;
    int          field_B30;
    PadWork      pad;                        //0xB34
    char         field_B48_padding[0x20];
    GV_ACT      *field_B68_other_actor;
    char         field_B64_padding[0x1F];
    short        field_B8C_facedir; //vision.facedir
    short        field_B8E;
    short        field_B90;
    char         field_B92_padding[0x96];
    int          sn_dir;                     //0xC28
} Work;

int	Think3_BikkuriGetUp_800CC568( Work* work )
{
    if( work->count3 == 0){
        work->pad.press |= 0x00001000  ;
    } else  if( work->count3 > 90 || work->actend ){
 
        return 1 ;
    }
    work->count3 ++ ;
    return 0 ;
}

extern int DirectTrace_800CC154( Work* work, int time );

int Think3_GoNext_800CC514( Work* work ) {
    if ( work->pad.time ) {
        (work->pad.press |= (  work->pad.tmp  )) ;
        work->pad.time -- ;
    }

    if ( DirectTrace_800CC154( work, 350 ) ) {
        return 1 ;
    }

    return 0 ;
}