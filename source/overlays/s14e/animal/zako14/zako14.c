#define __ZAKO_BUGFIX__

#include "animal/zako14/zako.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "libgcl/libgcl.h"

/*----------------------------------------------------------------------------*/

static int ChaseDis[] = {
    3000, 4000, 7000, 8000,
    8000, 8000, 8000, 8000,
};

int s14e_dword_800C3330 = 0x000F012C;
int s14e_dword_800C3334 = 0x003C001E;

int s14e_dword_800C3338 = 0x0000005A;
int s14e_dword_800C333C = 0x75307D01;

const char s14e_dword_800DC908[] = "Err Err Err  Set time Over\n";
const char s14e_dword_800DC924[] = "Err Err Err  Set Dir Over\n";

/*----------------------------------------------------------------------------*/

// BUG: Should be void GM_ConfigControlRadarparam( CONTROL *, u_short, u_short, u_short, u_short );
extern void GM_ConfigControlRadarparam( CONTROL *ctrl, u_short dir, u_short dis, int range, u_short r );

/*----------------------------------------------------------------------------*/

void s14e_800C5958( void )
{
    return;
}

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C5960.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C59DC.s")

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C5B14.s")
void s14e_800C5B14( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C5C78.s")
void s14e_800C5C78( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C5DAC.s")

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C5E08.s")
void s14e_800C5E08( Work *work, int name, int where );

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6028.s")

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C609C.s")
void s14e_800C609C( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C60BC.s")
int s14e_800C60BC( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6158.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C61B0.s")
#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800C6208.s")
void s14e_800C6208( Work *work );

void s14e_800C62E0( Work *work, int name, int where )
{
    char *opt;
    int addr, i;

    s14e_800C5E08( work, name, where );

    work->param.index = ZAKO14SetWorkID( work );
    if ( work->param.index < 0 )
    {
        printf( "Err not enough work !!\n" );
    }

    s14e_800C6208( work );

    work->param.root = 0;
    opt = GCL_GetOption( 'r' );
    if ( opt != NULL )
    {
        work->param.root = GCL_StrToInt( opt );
    }

    work->param.life = 768;
    opt = GCL_GetOption( 'l' );
    if ( opt != NULL )
    {
        work->param.life = GCL_StrToInt( opt );
    }

    work->param.faint = 7;
    opt = GCL_GetOption( 'f' );
    if ( opt != NULL )
    {
        work->param.faint = GCL_StrToInt( opt );
    }

    work->param.damage = 64;
    opt = GCL_GetOption( 'z' );
    if ( opt != NULL )
    {
        work->param.damage = GCL_StrToInt( opt );
    }

    work->param.blood = 65;
    opt = GCL_GetOption( 'b' );
    if ( opt != NULL )
    {
        work->param.blood = GCL_StrToInt( opt );
    }

    printf( " low[pory=%d\n", work->param.low_poly );

    work->param.g_flag = 255;
    opt = GCL_GetOption( 'g' );
    if ( opt != NULL )
    {
        work->param.g_flag = GCL_StrToInt( opt );
    }

    if ( work->param.blood == 90 )
    {
        work->param.g_flag = 0;
    }

    work->chase_dis = ChaseDis[ work->param.index ];
    work->chase_index = work->param.index;

    work->param.next = 255;
    opt = GCL_GetOption( 'n' );
    if ( opt != NULL )
    {
        work->param.next = GCL_StrToInt( opt );
    }

    work->param.area = 'A';
    opt = GCL_GetOption( 'a' );
    if ( opt != NULL )
    {
        work->param.area = GCL_StrToInt( opt );
    }

    if ( work->param.area == 'S' )
    {
        s14e_800CA890( work, 1 );
    }

    work->scale = 4096;
    opt = GCL_GetOption( 's' );
    if ( opt != NULL )
    {
        work->scale += GCL_StrToInt( opt );
    }

    work->param.item = 1;

    if ( s14e_800C60BC( work ) < 0 )
    {
        fprintf( 1, "watchar.c : action point Err\n" );
    }

    work->target = GM_AllocTarget();
    if ( work->target != NULL )
    {
        s14e_800C5C78( work );
    }

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->l_count = 0;
    work->t_count = 0;
    work->mark_time = 0;
    work->next_node = 0;
    work->search_flag = 0;
    work->act_status = 0;

    work->target_pos = work->nodes[ 0 ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = GM_CurrentMap;
    work->alert_level = 0;

    work->field_9E4 = 1;
    work->vision.range = 512;
    work->vision.facedir = 0;
    work->field_B9C = 0;
    work->pad.sound = 0;
    work->pad.time = 0;
    work->vision.length = ZAKO14_EYE_LENGTH;
    work->player_pos = ZAKO14_NO_POINT;
    work->subweapon = NULL;
    work->control.mov = work->nodes[ 0 ];
    work->field_C44 = 0;
    work->param.c_root = 0;
    work->param.c_next = work->param.next;

    for ( i = 0; i < 8; i++ )
    {
        work->modetime[ i ] = 0;
    }

    work->modetime[ 7 ] = 0x7;
    work->modetime[ 4 ] = 0xFF;

    GM_ConfigControlRadarparam( &work->control, 0, 512, ZAKO14_EYE_LENGTH, 0 );

    work->start_pos = work->nodes[ 0 ];
    work->start_map = GM_CurrentMap;

    addr = HZD_GetAddress( work->control.map->hzd, &work->control.mov, -1 );
    work->field_BE8 = addr;
    work->next_addr = addr;
    work->last_addr = addr;
    work->next_pos = work->start_pos;
}

void *NewZako14( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, s14e_800C5B14, s14e_800C609C, "zako14.c" );
        s14e_800C62E0( work, name, where );
    }
    return (void *)work;
}
