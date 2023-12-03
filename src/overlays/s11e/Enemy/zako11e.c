#include "zako11e.h"

void s11e_zako11e_800D34C8( void )
{
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D34D0.s")
void s11e_zako11e_800D34D0( DG_OBJS* objs, DG_DEF* def )
{
    int i;
    DG_OBJ *obj;
    DG_FreeObjsPacket_8001ABA8( objs, 0 );
    DG_FreeObjsPacket_8001ABA8( objs, 1 );

    objs->def = def;
    obj = objs->objs;
    for ( i = 0 ; i < 16 ; i++ )
    {
        obj->model   = &def->model[ i ];
        obj->n_packs =  def->model[ i ].numFaces_4;
        obj++;
    }
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D354C.s")
extern GM_Camera GM_Camera_800B77E8;
extern int GM_PlayerMap_800ABA0C;

void s11e_zako11e_800D354C( ZakoWork *work )
{
    if ( work->visible )
    {
        if ( work->param_low_poly == 1 )
        {
            if ( GM_GameStatus_800AB3CC & 0x50 || GM_Camera_800B77E8.field_22 )
            {
                if ( work->field_180 != work->param_low_poly )
                {
                    work->field_180 = work->param_low_poly;
                    s11e_zako11e_800D34D0( work->body.objs, work->def );
                }
            }
            else if ( work->field_180 )
            {
                work->field_180 = 0;
                s11e_zako11e_800D34D0( work->body.objs, work->kmd );
            }
        }
        DG_VisibleObjs( work->body.objs );
        DG_VisibleObjs( work->field_7A4.objs );
        work->field_AF4[0] = 1;
        work->field_AFC[0] = 1;
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
        DG_InvisibleObjs( work->field_7A4.objs );
        work->field_AF4[0] = 0;
        work->field_AFC[0] = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3684.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3800.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3934.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3990.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3BD8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3C84.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3CA4.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3D40.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3D98.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3DF0.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D3EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zako11e_800D42E0.s")