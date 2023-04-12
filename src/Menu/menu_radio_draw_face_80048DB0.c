#include "menuman.h"
#include "mts/mts_new.h"

extern int       dword_800AB6E0;
int              dword_800AB6E0;

extern menu_0x14 stru_800BDA48[ 2 ];

static inline void draw_face_anim(menu_chara_struct_sub *a1, int i, menu_chara_struct *chara_struct, MenuPrim *prim)
{
    switch ( a1->field_0_animState )
    {
    case 0:
        return;

    case 1:
        if ( a1->field_A > 0 )
        {
            a1->field_A--;
        }
        else
        {
            if ( stru_800BDA48[ i ].field_2_bTaskWup )
            {
                mts_wup_tsk_8008A540( 6 );
                stru_800BDA48[ i ].field_2_bTaskWup = 0;
            }
            menu_radio_draw_face_helper6_800486A0( a1, i );
            menu_radio_draw_face_helper2_800486F4( a1, i );
        }
        break;

    case 2:
        if ( a1->field_A > 0 )
        {
            a1->field_A--;
        }
        else if ( a1->field_E < 1 )
        {
            if ( !sub_80046C90( a1, i, a1->field_14_face_anim.full_anim, a1->field_8_animFrameNum + 1 ) &&
                 ( a1->field_E = 0x7000, stru_800BDA48[ i ].field_2_bTaskWup != 0 ) )
            {
                mts_wup_tsk_8008A540( 6 );
                stru_800BDA48[ i ].field_2_bTaskWup = 0;
            }
        }
        else
        {
            a1->field_E--;
        }
        break;

    case 3:
        menu_radio_draw_face_helper3_800487DC( chara_struct, i );
    case 4:
    default:
        break;
    }

    menu_radio_draw_face_helper5_8004896C( prim, a1, i );
}

void             menu_radio_draw_face_80048DB0( Actor_MenuMan *pActor, menu_chara_struct *chara_struct )
{
    menu_chara_struct_sub *chara_struct_sub;
    MenuPrim              *prim;
    int                    i;

    if ( chara_struct == NULL ) 
    {
        return;
    }
    if ( !chara_struct->field_1C_radioDatFragment )
    {
        chara_struct->field_3C[ 0 ].field_0_animState = 0;
        chara_struct->field_3C[ 1 ].field_0_animState = 0;
    }
    prim = pActor->field_20_otBuf;
    dword_800AB6E0 = dword_800AB6E0 + 1;

    if ( dword_800AB6E0 > 0x6d )
    {
        dword_800AB6E0 = 0;
    }
    for ( i = 0; i < 2; i++ )
    {
        chara_struct_sub = &chara_struct->field_3C[ i ];
        menu_radio_draw_face_helper_800470F4( i );
        if ( chara_struct->field_38 != 0 )
        {
            draw_face_anim(chara_struct_sub, i, chara_struct, prim);
        }
        menu_radio_draw_face_helper4_80048868( prim, chara_struct_sub, i );
    }
}
