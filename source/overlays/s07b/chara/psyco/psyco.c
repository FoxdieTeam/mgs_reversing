#include "chara/psyco/psyco.h"

#include <stdio.h>
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/navi.h"

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode( "psycho" )
#define MOTION_DATA GV_StrCode( "psycho" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _Work {
    /* 0x000 */ GV_ACT         actor;
    /* 0x020 */ CONTROL        control;
    /* 0x09C */ OBJECT         body;
    /* 0x180 */ MOTION_CONTROL m_ctrl;
    /* 0x1D0 */ MOTION_SEGMENT m_segs1[ 17 ];
    /* 0x434 */ MOTION_SEGMENT m_segs2[ 17 ];
    /* 0x698 */ SVECTOR        rots[ 16 ];
    /* 0x718 */ SVECTOR        adjust[ 16 ];
    /* 0x798 */ MATRIX         light[ 2 ];

    /* 0x7D8 */ char pad7B8[ 0x96 ];

    /* 0x86E */ short field_86E;

    /* 0x870 */ char pad870[ 0x20 ];

    /* 0x890 */ SVECTOR pos;
    /* 0x898 */ SVECTOR rot;

    /* 0x8A0 */ char pad8A0[ 0x4C ];

    /* 0x8EC */ short field_8EC;
    /* 0x8EE */ short field_8EE;

    /* 0x8F0 */ char pad8F0[ 0x1A0 ];

    /* 0xA90 */ int      proc_id;
    /* 0xA94 */ NAVIGATE navi;
    /* 0xAB4 */ int      field_AB4;
    /* 0xAB8 */ int      field_AB8;

    /* 0xABC */ char padABC[ 0x2C ];
} Work;

int s07b_dword_800C3390 = 0x01900388;
int s07b_dword_800C3394 = 0x00F00140;
int s07b_dword_800C3398 = 0x00000078;
int s07b_dword_800C339C = 0x00240018;
int s07b_dword_800C33A0 = 0x00480030;
int s07b_dword_800C33A4 = 0x00E0002C;
int s07b_dword_800C33A8 = 0x00000040;
int s07b_dword_800C33AC = 0x800CED04;
int s07b_dword_800C33B0 = 0x800CF130;
int s07b_dword_800C33B4 = 0x800CF130;
int s07b_dword_800C33B8 = 0x800CF130;
int s07b_dword_800C33BC = 0x800CDF40;
int s07b_dword_800C33C0 = 0x800CE134;
int s07b_dword_800C33C4 = 0x800CE2A8;
int s07b_dword_800C33C8 = 0x800CE43C;
int s07b_dword_800C33CC = 0x800CE660;
int s07b_dword_800C33D0 = 0x800CE85C;
int s07b_dword_800C33D4 = 0x800CEA18;
int s07b_dword_800C33D8 = 0x00000000;
int s07b_dword_800C33DC = 0x0000FA24;
int s07b_dword_800C33E0 = 0x00000000;
int s07b_dword_800C33E4 = 0x00000064;
int s07b_dword_800C33E8 = 0x0000FC00;
int s07b_dword_800C33EC = 0x00000000;
int s07b_dword_800C33F0 = 0x00000000;
int s07b_dword_800C33F4 = 0x000005DC;
int s07b_dword_800C33F8 = 0x000002EE;
int s07b_dword_800C33FC = 0x000000FA;
int s07b_dword_800C3400 = 0x03E8012C;
int s07b_dword_800C3404 = 0x0000012C;

const char s07b_dword_800E4F5C[] = "shukan mode off\n";
const char s07b_dword_800E4F70[] = "shukan mode on\n";
const char s07b_dword_800E4F80[] = "psy shukan on %d\n";
const char s07b_dword_800E4F94[] = "psy shukan off %d\n";
const char s07b_dword_800E4FA8[] = "スネーク";
const char s07b_dword_800E4FB4[] = "attack end\n";
const char s07b_dword_800E4FC0[] = "胸像１";
const char s07b_dword_800E4FC8[] = "胸像２";

const char s07b_dword_800E4FD0[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4FD4 = 0x800CD040;
const int s07b_dword_800E4FD8 = 0x800CD1BC;
const int s07b_dword_800E4FDC = 0x800CD1A4;
const int s07b_dword_800E4FE0 = 0x800CD1BC;
const int s07b_dword_800E4FE4 = 0x800CD1A4;
const int s07b_dword_800E4FE8 = 0x800CD1BC;
const int s07b_dword_800E4FEC = 0x800CD1B0;
const int s07b_dword_800E4FF0 = 0x800CD1BC;
const int s07b_dword_800E4FF4 = 0x800CD070;
const int s07b_dword_800E4FF8 = 0x800CD07C;
const int s07b_dword_800E4FFC = 0x800CD07C;
const int s07b_dword_800E5000 = 0x800CD07C;
const int s07b_dword_800E5004 = 0x800CD0F8;
const int s07b_dword_800E5008 = 0x800CD0DC;
const int s07b_dword_800E500C = 0x800CD0DC;
const int s07b_dword_800E5010 = 0x800CD0F8;
const int s07b_dword_800E5014 = 0x800CD0F8;

const char s07b_dword_800E5018[] = "MANTIS";
const char s07b_dword_800E5020[] = "マンティス";

const int s07b_dword_800E502C = 0x800CFF7C;
const int s07b_dword_800E5030 = 0x800D0064;
const int s07b_dword_800E5034 = 0x800D0178;
const int s07b_dword_800E5038 = 0x800D035C;
const int s07b_dword_800E503C = 0x800D035C;
const int s07b_dword_800E5040 = 0x800D052C;
const int s07b_dword_800E5044 = 0x800D10C4;
const int s07b_dword_800E5048 = 0x800D10D4;
const int s07b_dword_800E504C = 0x800D10E4;
const int s07b_dword_800E5050 = 0x800D10F4;
const int s07b_dword_800E5054 = 0x800D1104;
const int s07b_dword_800E5058 = 0x800D1114;
const int s07b_dword_800E505C = 0x800D1124;
const int s07b_dword_800E5060 = 0x800D1134;
const int s07b_dword_800E5064 = 0x800D1144;
const int s07b_dword_800E5068 = 0x800D1154;
const int s07b_dword_800E506C = 0x800D1164;

const char s07b_dword_800E5070[] = "メリル";
const char s07b_dword_800E5078[] = "hideo_b";
const char s07b_dword_800E5080[] = "hideo_s";
const char s07b_dword_800E5088[] = "hideo";

SVECTOR SECTION(".bss") s07b_dword_800E5BE0;

/*---------------------------------------------------------------------------*/

extern void *NewPadManager( void );

/*---------------------------------------------------------------------------*/

void s07b_800CAD54( Work *work, int se_id )
{
    SVECTOR tmp;
    int dir, turn, ang, pan;

    GV_SubVec3( &work->control.mov, &GM_PlayerPosition, &tmp );
    GV_VecLen3( &tmp );
    dir = GV_VecDir2( &tmp );

    if ( GM_Camera.first_person )
    {
        turn = GM_SnakeCamera.rotate2.vy;
        ang = dir + 1024;
    }
    else
    {
        turn = gUnkCameraStruct2_800B7868.rotate.vy;
        ang = dir + 1024;
    }

    pan = rcos( ( ang - turn ) & 4095 ) * 31 / 4096;
    if ( pan < 0 ) pan += 255;

    GM_SeSet2( pan, 63, se_id );
}

void s07b_800CAE00( Work *work )
{
    SVECTOR tmp, dir;
    CONTROL *control;
    SVECTOR *pos, *rot;
    int scale, len, diff;

    control = &work->control;

    if ( control->mov.vy < ( control->levels[ 0 ] + control->height ) )
    {
        control->mov.vy = control->levels[ 0 ] + control->height;
    }

    pos = &work->pos;
    scale = work->field_86E;
    if ( scale == 0 ) scale = 96;

    GV_SubVec3( &control->mov, pos, &tmp );

    len = GV_VecLen3( &tmp );
    if ( scale < len )
    {
        GV_LenVec3( &tmp, &dir, len, scale );
        GV_AddVec3( pos, &dir, pos );
    }
    else
    {
        *pos = control->mov;
    }

    rot = &work->rot;
    diff = GV_DiffDirS( rot->vy, control->rot.vy );
    if ( ABS( diff ) > 128 )
    {
        rot->vy += ( diff > 0 ) ?  128 : -128;
    }
    else
    {
        rot->vy = control->rot.vy;
    }

    DG_SetPos2( pos, rot );
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CAF54.s")
void s07b_800CAF54( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CAFC8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB068.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB0B4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB130.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB224.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB264.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB2A4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB6B0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB770.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB8CC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB9E8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBAA4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBB38.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBC20.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBCE8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBD4C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBDA0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBDCC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBE34.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBF00.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CBFB0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC138.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC174.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC468.s")

void s07b_800CC50C( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC514.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC578.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC67C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC6CC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC704.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC790.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC89C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC8D4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC930.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC970.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC9E8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCA10.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCA80.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCBB0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCBFC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCFE4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CD86C.s")

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDA04.s")
int s07b_800CDA04( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDA90.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDAFC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDBA4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDCAC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDF40.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CE134.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CE2A8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CE43C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CE660.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CE85C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CEA18.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CEBAC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CED04.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CEFF0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF130.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF200.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF304.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF684.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF6F0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF768.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF9A0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D075C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0774.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D098C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0A4C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0A6C.s")

void s07b_800D0B40( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0B48.s")

void s07b_800D0C8C( void )
{
    /* do nothing */
}


#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0C94.s")

void s07b_800D0DCC( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0DD4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0F94.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0FC0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D105C.s")

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1254.s")
void s07b_800D1254( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D13C4.s")
void s07b_800D13C4( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1484.s")
int s07b_800D1484( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1638.s")
void s07b_800D1638( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D187C.s")

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D18E0.s")
int s07b_800D18E0( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D195C.s")
void s07b_800D195C( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1C80.s")
void s07b_800D1C80( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1CF8.s")
void s07b_800D1CF8( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1D70.s")
void s07b_800D1D70( Work *work );

int s07b_800D1DE8( Work *work, int name, int where )
{
    CONTROL *control;
    OBJECT *body;

    control = &work->control;
    if ( GM_InitControl( control, name, where ) < 0 ) return -1;
    GM_ConfigControlString( control, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlHazard( control, 750, 300, 300 );
    control->seg_flag = HZD_SEG_NO_NAVIGATE;
    GM_ConfigControlTrapCheck( control );

    body = &work->body;
    GM_InitObject( body, BODY_DATA, BODY_FLAG, MOTION_DATA );
    GM_ConfigObjectJoint( body );
    GM_ConfigMotionControl( body, &work->m_ctrl, MOTION_DATA, work->m_segs1, work->m_segs2, control, work->rots );
    GM_ConfigObjectLight( body, work->light );
    GM_ConfigObjectAction( body, 0, 0, 0 );

    if ( GCL_GetOption( 'e' ) )
    {
        work->proc_id = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->proc_id = -1;
    }

    work->body.objs->light->t[ 0 ] = 0;
    work->body.objs->light->t[ 1 ] = 0;
    work->body.objs->light->t[ 2 ] = 0;

    if ( s07b_800D18E0( work ) < 0 ) return -1;
    if ( s07b_800D1484( work ) < 0 ) return -1;
    if ( s07b_800CDA04( work ) < 0 ) return - 1;

    s07b_800CAF54( work );
    s07b_800D1638( work );
    s07b_800D195C( work );
    s07b_800D1CF8( work );
    s07b_800D1C80( work );
    s07b_800D1D70( work );

    NagivateInit( &work->navi, control->map->hzd, &control->mov );

    work->field_AB4 = GM_SnakeCamera.track;
    work->field_AB8 = 0;
    work->field_8EC = 0;
    work->field_8EE = 0;

    GM_PlayerStatus |= PLAYER_SECOND_AVAILABLE;
    GM_GameStatus |= STATE_RADAR_OFF;

    NewPadManager();

    s07b_dword_800E5BE0 = control->mov;
    return 0;
}

void *NewPsychoMantis( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER2, sizeof(Work) );
    if ( work == NULL ) return NULL;

    GV_SetNamedActor(work, s07b_800D1254, s07b_800D13C4, "psyco.c" );
    if ( s07b_800D1DE8( work, name, where ) < 0 )
    {
        GV_DestroyActor( work );
        return NULL;
    }

    return (void *)work;
}
