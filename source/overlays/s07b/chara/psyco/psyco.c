#include "chara/psyco/psyco.h"

#include <stdio.h>
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/navi.h"
#include "takabe/cineutil.h"
#include "menu/menuman.h"

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

    /* 0x7D8 */ void *shadow;             // NewHumanShadow2 (s07b_800CAF54)
    /* 0x7DC */ int *shadow_enable;       // 0 while camouflaged, 1 otherwise
    /* 0x7E0 */ TARGET *target;
    /* 0x7E4 */ char pad7E4[ 0x48 ];
    /* 0x82C */ HOMING *hom;
    /* 0x830 */ void *sepia;              // sepia screen effect (NewSepia_800C5214), s07b_800CB0B4
    /* 0x834 */ void *field_834;          // actor, destroyed in s07b_800D13C4
    /* 0x838 */ void *kogaku;             // optical camouflage actor (NewKogaku2), NULL when off
    /* 0x83C */ int field_83C;            // camouflage state: 10 = on, -1 = off
    /* 0x840 */ u_short field_840;        // actor address for GV_SendMessage (s07b_800CC138)
    /* 0x842 */ char pad842[ 0x2 ];
    /* 0x844 */ short field_844;
    /* 0x846 */ short field_846;          // < 0: destroy on message 0x10
    /* 0x848 */ int field_848;

    /* 0x84C */ int field_84C;

    /* 0x850 */ int field_850;            // flags (bit 2 checked in s07b_800CBDA0)

    /* 0x854 */ void *field_854;
    /* 0x858 */ int field_858;

    /* 0x85C */ char pad85C[ 0x8 ];

    /* 0x864 */ int field_864;

    /* 0x868 */ int field_868;            // 1 when touching a wall or close to field_870 (s07b_800CB8CC)
    /* 0x86C */ short field_86C;          // turn direction step while in s07b_800CDCAC (s07b_800CB8CC)

    /* 0x86E */ short field_86E;

    /* 0x870 */ SVECTOR field_870;        // current point (vx, vz), s07b_800CB9E8 picks a different one
    /* 0x878 */ char pad878[ 0x2 ];
    /* 0x87A */ short field_87A;
    /* 0x87C */ char pad87C[ 0x14 ];

    /* 0x890 */ SVECTOR pos;
    /* 0x898 */ SVECTOR rot;

    /* 0x8A0 */ int field_8A0;            // cleared in s07b_800CDA90

    /* 0x8A4 */ int     n_points;
    /* 0x8A8 */ SVECTOR points[ 8 ];

    /* 0x8E8 */ char pad8E8[ 0x4 ];

    /* 0x8EC */ short field_8EC;
    /* 0x8EE */ short field_8EE;

    /* 0x8F0 */ int *field_8F0;           // counter of an attack; cleared when it runs out (s07b_800CC67C)
    /* 0x8F4 */ MENU_BAR_CONF lifebar;    // colours change with the max vital (s07b_800CD86C)
    /* 0x900 */ int  field_900;           // vital after being clamped (s07b_800D0DD4)
    /* 0x904 */ char pad904[ 0x154 ];
    /* 0xA58 */ int  field_A58;           // < 2: picture attack goes on to s07b_800CED04 (s07b_800CE660)
    /* 0xA5C */ char padA5C[ 0x6 ];
    /* 0xA62 */ char field_A62;           // set together with field_84C bit 1 (s07b_800CC9E8)
    /* 0xA63 */ char field_A63;           // set to 8 when the s07b_800CBF00 counter runs out

    /* 0xA64 */ short field_A64;
    /* 0xA66 */ short field_A66;

    /* 0xA68 */ char padA68[ 0x2 ];
    /* 0xA6A */ short field_A6A;          // side 0..2 for the picture/book throw (GV_RandU % 3)
    /* 0xA6C */ char padA6C[ 0x14 ];
    /* 0xA80 */ GV_PAD *pad;             // GV_PadData[ 0 ] or [ 1 ] (second controller), set in s07b_800D1254
    /* 0xA84 */ char padA84[ 0x4 ];
    /* 0xA88 */ u_char weapon_lock[ 5 ];  // 20-frame counters that make C4/claymore/grenade/Nikita/Stinger fail (s07b_800CBFB0)
    /* 0xA8D */ char padA8D[ 0x3 ];

    /* 0xA90 */ int      proc_id;
    /* 0xA94 */ NAVIGATE navi;
    /* 0xAB4 */ int      field_AB4;
    /* 0xAB8 */ int      field_AB8;
    /* 0xABC */ int      field_ABC[ 4 ];
    /* 0xACC */ int      field_ACC[ 6 ];
    /* 0xAE4 */ char     field_AE4[ 4 ];
} Work;

// thrown objects (chara/psyco/*.c); Work.field_8F0 points at their *_alive flag
extern int book_alive;
extern int chair_alive;
extern int ox_alive;
extern int picture_alive;
extern int pot_alive;
extern int statue_alive;
void *NewPsychoBook( int side );
void *NewPsychoChair( void );
void *NewPsychoOx( void );
void *NewPsychoPicture( int side );
void *NewPsychoPot( void );
void *NewPsychoSonic( MATRIX *world, int dir, int speed, int vital );
void *NewPsychoStatue( void );

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
SVECTOR s07b_dword_800C33D8 = { 0, 0, -1500, 0 };   // offset from s07b_dword_800E5BB8 (s07b_800CBC20)
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
        turn = gUnkCameraStruct2.rotate.vy;
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

extern void *NewHumanShadow2( CONTROL *root_ctrl, OBJECT *root_obj, SVECTOR units, int **enabled );

// create Mantis's shadow (same pattern as animal/meryl72/meryl72.c)
void s07b_800CAF54( Work *work )
{
    SVECTOR indices;

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewHumanShadow2( &work->control, &work->body, indices, &work->shadow_enable );
}

void s07b_800CAFC8( Work *work )
{
    GCL_ARGS args;
    long     argv[1];

    if ( work->field_850 & 0x10 )
    {
        work->field_850 &= ~0x10;
        if ( work->field_846 < 0 )
        {
            if ( work->proc_id >= 0 )
            {
                args.argc = 1;
                args.argv = argv;
                argv[0] = work->target->vital;
                GCL_ExecProc( work->proc_id, &args );
            }
            GV_DestroyActor( work );
        }
        else
        {
            work->field_844 = work->field_846;
            work->field_848 = 0;
        }
    }
}
void s07b_800CB068( int arg0 )
{
    GV_MSG msg;

    msg.address = 0xC4C3;
    msg.message_len = 2;
    msg.message[0] = arg0 ? 0xD182 : 0x6B;
    msg.message[1] = 0x400;
    GV_SendMessage( &msg );
}

extern void *NewSepia_800C5214( void );

// sepia screen effect on/off (not switched on while item 5 or 6 is equipped)
void s07b_800CB0B4( Work *work, int on )
{
    if ( on )
    {
        if ( GM_Item != 5 && GM_Item != 6 && !work->sepia )
        {
            work->sepia = NewSepia_800C5214();
        }
    }
    else
    {
        if ( work->sepia )
        {
            GV_DestroyOtherActor( work->sepia );
        }
        work->sepia = NULL;
    }
}
void s07b_800CB0B4( Work *work, int );

void s07b_800CB130( Work *work )
{
    if ( work->field_864 == 0 )
    {
        return;
    }
    if ( work->field_864 > 0 )
    {
        if ( --work->field_864 != 0 || ( work->field_84C & 1 ) )
        {
            return;
        }
        if ( !( work->field_850 & 1 ) )
        {
            work->body.objs->flag &= ~0x80;
        }
        s07b_800CB0B4( work, 0 );
        s07b_800CB068( 0 );
        printf( s07b_dword_800E4F5C );
    }
    else
    {
        if ( ++work->field_864 != 0 || !( work->field_84C & 1 ) )
        {
            return;
        }
        work->body.objs->flag |= 0x80;
        s07b_800CB0B4( work, 1 );
        s07b_800CB068( 1 );
        printf( s07b_dword_800E4F70 );
    }
}
void s07b_800CB224( Work *work )
{
    SVECTOR diff;

    GV_SubVec3( &GM_PlayerPosition, &work->control.mov, &diff );
    work->control.turn.vy = GV_VecDir2( &diff );
}

extern SVECTOR s07b_dword_800E5BB8;

void s07b_800CB264( Work *work )
{
    SVECTOR diff;

    GV_SubVec3( &s07b_dword_800E5BB8, &work->control.mov, &diff );
    work->control.turn.vy = GV_VecDir2( &diff );
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB2A4.s")
void s07b_800CB2A4( Work *work );
void s07b_800CB6B0( Work *work, short x, short z, short scale )
{
    SVECTOR pos;

    work->field_870.vx = x;
    work->field_870.vz = z;
    if ( scale > 0 )
    {
        work->field_86E = scale;
    }

    pos.vx = x;
    pos.vy = 0;
    pos.vz = z;
    NavigateSetTarget( &work->navi, work->control.map->hzd, &pos );

    pos = work->control.mov;
    pos.vy -= work->control.height;
    work->navi.addr = HZD_GetAddress( work->control.map->hzd, &pos, work->navi.addr );
    GM_ZoneNavi( &work->navi, &work->control );
}
void s07b_800CDCAC( Work *work, int time );

void s07b_800CB770( Work *work )
{
    SVECTOR from;
    SVECTOR to;
    SVECTOR diff;
    int     dist;
    int     len;

    from = work->control.mov;
    from.vy = 0;
    work->navi.addr = HZD_GetAddress( work->control.map->hzd, &from, work->navi.addr );
    GM_ZoneNavi( &work->navi, &work->control );
    dist = NavigateGetTargetDist( &work->navi, &work->control.mov );

    to = work->navi.next_pos;
    to.vy = 0;
    GV_SubVec3( &to, &from, &diff );
    len = GV_VecLen3( &diff );

    work->field_868 = 0;
    if ( dist < work->field_86E )
    {
        work->control.step = diff;
        work->field_868 = 1;
    }
    else
    {
        GV_LenVec3( &diff, &work->control.step, len, work->field_86E );
    }

    if ( work->field_854 == s07b_800CDCAC )
    {
        work->control.turn.vy = ( work->control.turn.vy + ( work->field_86C - 1 ) * 1024 ) & 0xFFF;
    }
}
void s07b_800CDCAC( Work *work, int time );

void s07b_800CB8CC( Work *work )
{
    SVECTOR from;
    SVECTOR to;
    SVECTOR diff;
    int     len;

    from = work->control.mov;
    to = work->field_870;
    to.vy = 0;
    from.vy = 0;
    GV_SubVec3( &to, &from, &diff );
    len = GV_VecLen3( &diff );

    work->field_868 = 0;
    if ( work->control.n_touches )
    {
        work->field_868 = 1;
    }

    if ( len < work->field_86E )
    {
        work->control.step = diff;
        work->field_868 = 1;
    }
    else
    {
        GV_LenVec3( &diff, &work->control.step, len, work->field_86E );
    }

    if ( work->field_854 == s07b_800CDCAC )
    {
        work->control.turn.vy = ( work->control.turn.vy + ( work->field_86C - 1 ) * 1024 ) & 0xFFF;
    }
}


#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CB9E8.s")
int s07b_800CBAA4( Work *work )
{
    SVECTOR diff;
    int     dir;

    GV_SubVec3( &work->navi.next_pos, &work->control.mov, &diff );
    dir = ( GV_VecDir2( &diff ) - ( work->control.turn.vy & 0xFFF ) ) & 0xFFF;
    if ( dir < 0x800 )
    {
        if ( dir < 0x100 )
        {
            return 1;
        }
        if ( dir > 0x500 )
        {
            return 3;
        }
        return 4;
    }
    if ( dir > 0xF00 )
    {
        return 1;
    }
    if ( dir < 0xB00 )
    {
        return 3;
    }
    return 2;
}
void s07b_800CF130( Work *work, int time );

void s07b_800CF9A0( Work *work, int time );
typedef void ( *PSYCO_MODE )( Work *, int );

void s07b_800CBB38( Work *work )
{
    u_short    idx;
    PSYCO_MODE mode;

    switch ( work->field_844 )
    {
    case 2:
    case 9:
        idx = work->field_8EC;
        if ( idx == 5 && work->field_8F0 == NULL )
        {
            idx = 6;
        }
        else if ( idx == 6 && work->field_8F0 == NULL )
        {
            idx = 7;
        }
        work->field_8EC = idx;
        work->field_854 = ( (PSYCO_MODE *)&s07b_dword_800C33AC )[ idx ];
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    case 8:
        mode = s07b_800CF130;
        break;
    case 3:
        mode = s07b_800CF9A0;
        break;
    default:
        return;
    }
    work->field_854 = mode;
    work->field_858 = 0;
    work->field_A66 = 0;
    work->field_A64 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
void s07b_800CB8CC( Work *work );

void s07b_800CBC20( Work *work )
{
    MATRIX  mat;
    SVECTOR diff;
    SVECTOR rot;
    SVECTOR pos;

    GV_SubVec3( &GM_PlayerPosition, &s07b_dword_800E5BB8, &diff );
    rot.vz = 0;
    rot.vx = 0;
    rot.vy = GV_VecDir2( &diff );
    DG_SetPos2( &s07b_dword_800E5BB8, &rot );
    DG_MovePos( &s07b_dword_800C33D8 );
    ReadRotMatrix( &mat );
    pos.vx = mat.t[ 0 ];
    pos.vy = mat.t[ 1 ];
    pos.vz = mat.t[ 2 ];
    s07b_800CB6B0( work, pos.vx, pos.vz, 0x60 );
    s07b_800CB8CC( work );
    s07b_800CB224( work );
}
extern void *NewKogaku2( CONTROL *control, OBJECT *object, int num_parent );

// optical camouflage off
void s07b_800CBCE8( Work *work )
{
    if ( work->field_83C != -1 )
    {
        if ( work->kogaku )
        {
            GV_DestroyActor( work->kogaku );
        }
        work->kogaku = NULL;
        work->field_83C = -1;
        *work->shadow_enable = 1;
    }
}

// optical camouflage on
void s07b_800CBD4C( Work *work )
{
    if ( work->field_83C != 10 )
    {
        work->kogaku = NewKogaku2( &work->control, &work->body, 6 );
        work->field_83C = 10;
        *work->shadow_enable = 0;
    }
}
void s07b_800CBDA0( Work *work )
{
    if ( !( work->field_850 & 4 ) )
    {
        work->field_87A = -32;
        work->control.step.vy -= 32;
    }
}
extern void *NewBlood( MATRIX *world, int count );

// blood effect at model part 'part'
void s07b_800CBDCC( Work *work, int part )
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ part ].world );
    DG_MovePos( (SVECTOR *)&s07b_dword_800C33E0 );
    DG_RotatePos( (SVECTOR *)&s07b_dword_800C33E8 );
    ReadRotMatrix( &world );
    NewBlood( &world, 1 );
}
void s07b_800CBE34( Work *work, MATRIX *mat )
{
    SVECTOR diff;
    SVECTOR rot;
    SVECTOR vec;

    rot.vz = 0;
    GV_SubVec3( &work->control.mov, &GM_PlayerPosition, &diff );
    rot.vy = GV_VecDir2( &diff );
    vec.vx = diff.vy;
    vec.vz = SquareRoot0( diff.vx * diff.vx + diff.vz * diff.vz );
    rot.vx = ( -GV_VecDir2( &vec ) - 0x400 ) & 0xFFF;
    RotMatrixYXZ( &rot, mat );
    mat->t[ 0 ] = work->control.mov.vx;
    mat->t[ 1 ] = work->control.mov.vy;
    mat->t[ 2 ] = work->control.mov.vz;
}
void s07b_800CBF00( Work *work, u_char *counter, u_char limit, int *done, int start )
{
    if ( start && *counter == 0 )
    {
        (*counter)++;
        s07b_800CAD54( work, 0x84 );
    }

    if ( *done )
    {
        *done = 0;
    }

    if ( *counter )
    {
        (*counter)++;
        if ( *counter == limit )
        {
            *done = 1;
            *counter = 0;
            work->field_A63 = 8;
        }
    }
}
extern int dword_800BDD28;
extern int dword_8009F434;
extern int dword_8009F444;
extern int dword_8009F474;
extern int dword_8009F480;
extern int dword_8009F49C;
extern int amissile_alive_8009F490;

void s07b_800CBFB0( Work *work )
{
    u_char act;
    u_char act2;

    if ( GV_PauseLevel || ( work->field_84C & 0x10 ) || ( GM_GameStatus & 0x10000000 ) )
    {
        return;
    }

    if ( work->field_844 == 0 )
    {
        dword_800BDD28 = 0;
        dword_8009F444 = 0;
        dword_8009F434 = 0;
        dword_8009F49C = 0;
        dword_8009F480 = 0;
        return;
    }

    act2 = (u_char)GM_PlayerBody->action2;
    act = (u_char)GM_PlayerBody->action;
    s07b_800CBF00( work, &work->weapon_lock[ 0 ], 20, &dword_8009F434, act2 == 0x31 || act2 == 0x36 || act == 0x38 );
    s07b_800CBF00( work, &work->weapon_lock[ 1 ], 20, &dword_8009F444, act == 0x3A );
    s07b_800CBF00( work, &work->weapon_lock[ 2 ], 20, &dword_800BDD28, act2 == 0x32 );
    s07b_800CBF00( work, &work->weapon_lock[ 3 ], 20, &dword_8009F474, act2 == 0x51 );
    s07b_800CBF00( work, &work->weapon_lock[ 4 ], 20, &dword_8009F49C, amissile_alive_8009F490 );
}
void s07b_800CC138( Work *work, int arg1 )
{
    GV_MSG msg;

    msg.address = work->field_840;
    msg.message_len = 2;
    msg.message[0] = 0x491D;
    msg.message[1] = arg1;
    GV_SendMessage( &msg );
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC174.s")
extern int *s07b_dword_800E5BB0;

void s07b_800CC468( Work *work )
{
    SVECTOR diff;
    int     len;
    int     track;

    if ( *s07b_dword_800E5BB0 & 8 )
    {
        return;
    }

    GV_SubVec3( &work->control.mov, &GM_PlayerPosition, &diff );
    len = GV_VecLen3( &diff );

    track = 7000;
    if ( len > 3500 )
    {
        track = ( len / 8 ) * 16;
    }
    if ( track > 10000 )
    {
        track = 10000;
    }

    GM_SnakeCamera.track = work->field_AB4 = GV_NearExp8( work->field_AB4, track );
}

void s07b_800CC50C( void )
{
    /* do nothing */
}

void s07b_800CC514( int arg0, int arg1 )
{
    GV_MSG msg;

    msg.address = GV_StrCode( s07b_dword_800E4FA8 );
    msg.message_len = 4;
    msg.message[0] = 0x3238;
    msg.message[1] = arg0;
    msg.message[2] = -1;
    msg.message[3] = arg1;
    GV_SendMessage( &msg );
}
// place the camera at distance len from pos, looking at it from target's side
void s07b_800CC578( SVECTOR *pos, SVECTOR *target, int len, short *dir_back, short *dir )
{
    SVECTOR diff;
    SVECTOR vec;
    SVECTOR eye;

    target->vy = pos->vy;
    GV_SubVec3( pos, target, &diff );
    GV_LenVec3( &diff, &vec, GV_VecLen3( &diff ), len );
    GV_SubVec3( pos, &vec, &eye );
    GM_Camera.first_person = 1;
    GM_SnakeCamera.rotate2.vy = GV_VecDir2( &diff );
    GM_SnakeCamera.position = eye;

    if ( dir_back )
    {
        *dir_back = ( GM_SnakeCamera.rotate2.vy + 0x800 ) & 0xFFF;
    }

    if ( dir )
    {
        *dir = GM_SnakeCamera.rotate2.vy;
    }
}
void s07b_800CC67C( Work *work )
{
    if ( work->field_8F0 && *work->field_8F0 <= 0 )
    {
        printf( s07b_dword_800E4FB4 );
        work->field_8F0 = NULL;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CC6CC.s")
// floating: bob up and down with the change of a sine wave over GV_Time
void s07b_800CC704( Work *work )
{
    int t;

    t = GV_Time % 128;
    t = rsin( t * 32 ) - rsin( ( t - 1 ) * 32 );
    work->control.step.vy += t * 160 / 4096;
}
// hide the body (first call) or the player (later) when it is close to the camera
void s07b_800CC790( Work *work, int arg1 )
{
    SVECTOR diff;

    if ( arg1 == 0 )
    {
        GV_SubVec3( &work->control.mov, &GM_SnakeCamera.position, &diff );
        if ( GV_VecLen3( &diff ) < GM_SnakeCamera.track + 500 )
        {
            DG_InvisibleObjs( work->body.objs );
        }
        else
        {
            DG_VisibleObjs( work->body.objs );
        }
    }
    else
    {
        GV_SubVec3( &GM_PlayerControl->mov, &GM_SnakeCamera.position, &diff );
        if ( GV_VecLen3( &diff ) < GM_SnakeCamera.track + 500 )
        {
            DG_InvisibleObjs( GM_PlayerBody->objs );
        }
        else
        {
            DG_VisibleObjs( GM_PlayerBody->objs );
        }
    }
}
void s07b_800CC89C( Work *work, int arg1 )
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    args.argv = argv;
    argv[0] = arg1;
    GCL_ExecProc( work->field_ACC[5], &args );
}
void s07b_800CC8D4( Work *work )
{
    if ( work->kogaku )
    {
        if ( GM_Item == 6 )
        {
            work->body.objs->flag &= ~0x80;
        }
        else
        {
            work->body.objs->flag |= 0x80;
        }
    }
}
extern int dword_8009F470;
extern int dword_8009F480;
extern int amissile_alive_8009F490;
extern int dword_8009F49C;

void s07b_800CC930( void )
{
    if ( dword_8009F470 )
    {
        dword_8009F480 = 1;
    }
    if ( amissile_alive_8009F490 )
    {
        dword_8009F49C = 1;
    }
}
// put Snake's camera (x/z) at distance 'dist' from 'base', in the direction of 'from'
void s07b_800CC970( SVECTOR *from, SVECTOR *base, int dist )
{
    SVECTOR diff;
    SVECTOR out;

    GV_SubVec3( from, base, &diff );
    GV_LenVec3( &diff, &out, GV_VecLen3( &diff ), dist );
    GM_SnakeCamera.position.vx = base->vx + out.vx;
    GM_SnakeCamera.position.vz = base->vz + out.vz;
}
void s07b_800CC9E8( Work *work, int arg1 )
{
    work->field_A62 = arg1;
    work->field_84C |= 2;
    work->target->class &= ~0x94;
}
// end of the state started by s07b_800CC9E8
void s07b_800CCA10( Work *work )
{
    work->field_A62 = 0;
    work->field_84C &= ~2;
    work->field_850 &= ~0x200;
    work->target->class |= 0x9C;
    if ( !( work->field_850 & 1 ) )
    {
        work->body.objs->flag &= ~0x80;
    }
}
// blink timer (field_A62) and target class timer (field_A63)
void s07b_800CCA80( Work *work )
{
    if ( work->field_A62 )
    {
        if ( !( work->field_850 & 0x200 ) )
        {
            if ( work->field_A62 & 3 )
            {
                DG_VisibleObjs( work->body.objs );
            }
            else
            {
                DG_InvisibleObjs( work->body.objs );
            }
        }
        if ( --work->field_A62 == 0 )
        {
            if ( !( work->field_850 & 0x200 ) )
            {
                DG_VisibleObjs( work->body.objs );
            }
            s07b_800CCA10( work );
        }
    }

    if ( work->field_A63 )
    {
        if ( --work->field_A63 == 0 )
        {
            if ( !( work->field_84C & 2 ) )
            {
                work->target->class |= 0x9C;
            }
        }
        else
        {
            work->target->class &= ~0x94;
        }
    }
}
void s07b_800CCBB0( TARGET *target )
{
    target->a_mode = 0;
    target->damage = 0;
    target->faint = 0;
    target->damaged &= ~0x84;
    target->force = DG_ZeroVector;
    target->weapon = -1;
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCBFC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CCFE4.s")
void s07b_800CD86C( Work *work )
{
    int now;
    int rest;
    int diff;

    if ( work->field_850 & 0x20 )
    {
        now = work->target->vital;
        if ( now < 0 )
        {
            now = 0;
        }
        rest = work->field_900;
        if ( rest < now )
        {
            rest = now;
        }
        if ( *(u_short *)&s07b_dword_800C3390 > 0x400 )
        {
            work->lifebar.right[ 0 ] = 0x3C00 / *(u_short *)&s07b_dword_800C3390 + 16;
            work->lifebar.right[ 1 ] = 0x1C000 / *(u_short *)&s07b_dword_800C3390 + 63;
            work->lifebar.right[ 2 ] = -0x8000 / *(u_short *)&s07b_dword_800C3390 - 64;
        }
        MENU_DrawBar2( 28, rest, now, *(u_short *)&s07b_dword_800C3390, &work->lifebar );
        diff = rest - now;
        if ( diff > 0 )
        {
            if ( diff >= 64 )
            {
                work->field_900 -= 64;
            }
            else
            {
                work->field_900 -= diff;
            }
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDA04.s")
int s07b_800CDA04( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDA90.s")
void s07b_800CDA90( Work *work );
void s07b_800CBC20( Work *work );
void s07b_800CDBA4( Work *work, int time );

void s07b_800CDAFC( Work *work, int time )
{
    if ( time == 0 )
    {
        s07b_800CDA90( work );
        work->field_850 &= ~1;
    }

    s07b_800CBC20( work );

    if ( !( *s07b_dword_800E5BB0 & 4 ) )
    {
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800CDBA4;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CB9E8( Work *work, int arg1 );
void s07b_800CEBAC( Work *work, int time );
void s07b_800CDCAC( Work *work, int time );

void s07b_800CDBA4( Work *work, int time )
{
    if ( time == 0 )
    {
        work->field_8A0 = 0;
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        work->field_850 &= ~1;
    }

    s07b_800CBC20( work );

    if ( *s07b_dword_800E5BB0 & 4 )
    {
        switch ( work->field_844 )
        {
        case 0:
            work->field_854 = s07b_800CDAFC;
            break;
        case 4:
        case 6:
            work->field_8EC = 1;
            work->field_854 = s07b_800CEBAC;
            break;
        default:
            s07b_800CB9E8( work, 160 );
            work->field_854 = s07b_800CDCAC;
            break;
        }
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CDCAC( Work *work, int time )
{
    int act;

    if ( time == 0 )
    {
        work->field_8A0 = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }

        work->field_86C = s07b_800CBAA4( work );
        switch ( work->field_86C )
        {
        case 1:
            act = 2;
            break;
        case 2:
            act = 11;
            break;
        case 3:
            act = 5;
            break;
        case 4:
            act = 8;
            break;
        default:
            act = 11;
            break;
        }
        if ( work->body.action != act )
        {
            GM_ConfigObjectAction( &work->body, act, 0, 4 );
        }

        work->field_A64 = 0;
        if ( !( work->field_850 & 1 ) )
        {
            GM_SeSetMode( &work->control.mov, 0xC8, 1 );
        }
    }

    if ( time > 24 )
    {
        work->field_86E += 4;
    }

    if ( work->field_844 == 8 )
    {
        work->body.objs->flag |= 0x80;
    }

    switch ( work->field_A64 )
    {
    case 0:
        if ( work->body.is_end )
        {
            act = work->body.action + 2;
            if ( work->body.action != act )
            {
                GM_ConfigObjectAction( &work->body, act, 0, 4 );
            }
            work->field_A64 = 1;
        }
        break;
    case 1:
        s07b_800CB770( work );
        if ( work->field_868 || work->field_858 >= 180 )
        {
            act = work->body.action - 1;
            if ( work->body.action != act )
            {
                GM_ConfigObjectAction( &work->body, act, 0, 4 );
            }
            work->field_A64 = 2;
        }
    case 2:
        if ( work->body.is_end )
        {
            s07b_800CBB38( work );
        }
        break;
    }

    if ( work->field_850 & 4 )
    {
        work->control.step.vy += 2;
    }
    else
    {
        work->control.step.vy += 34;
    }

    if ( work->field_844 == 3 )
    {
        GM_SnakeCamera.position = work->control.mov;
    }

    s07b_800CC8D4( work );
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CDF40.s")
void s07b_800CE2A8( Work *work, int time );

void s07b_800CE134( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->field_8F0 == NULL && !( work->field_850 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoStatue();
            work->field_8F0 = &statue_alive;
            s07b_800CB6B0( work, -1000, -1500, 96 );
        }
        s07b_800CC89C( work, 4 );
        work->field_868 = 0;
        s07b_800CDA90( work );
        work->field_850 &= ~1;
    }

    if ( work->field_A64 == 0 && work->field_868 == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->field_868 )
        {
            if ( work->body.action2 != 0 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            if ( work->body.action != 18 )
            {
                GM_ConfigObjectAction( &work->body, 18, 0, 4 );
            }
            work->field_A64 = 1;
        }
    }

    s07b_800CB224( work );

    if ( work->field_8F0 == NULL )
    {
        work->field_8EC = 6;
        work->field_854 = s07b_800CE2A8;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_8F0 = NULL;
        work->field_850 &= ~0x2000;
    }
}
void s07b_800CE43C( Work *work, int time );

void s07b_800CE2A8( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->field_8F0 == NULL && !( work->field_850 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoPot();
            work->field_8F0 = &pot_alive;
            s07b_800CB6B0( work, -1000, -1500, 96 );
        }
        work->field_868 = 0;
        s07b_800CDA90( work );
        s07b_800CC89C( work, 4 );
        work->field_850 &= ~1;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->field_868 == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->field_868 )
        {
            if ( work->body.action2 != 0 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            if ( work->body.action != 18 )
            {
                GM_ConfigObjectAction( &work->body, 18, 0, 4 );
            }
            work->field_A64 = 1;
        }
    }

    if ( work->field_8F0 == NULL )
    {
        work->field_8EC = 7;
        work->field_850 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800CE43C;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_8F0 = NULL;
    }
}
void s07b_800CED04( Work *work, int time );

void s07b_800CE43C( Work *work, int time )
{
    int x;

    if ( time == 0 )
    {
        if ( work->field_8F0 == NULL && !( work->field_850 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoOx();
            work->field_8F0 = &ox_alive;
        }
        work->field_868 = 0;
        s07b_800CB6B0( work, 0, 500, 96 );
        s07b_800CDA90( work );
        work->control.turn.vy = 0;
        s07b_800CC89C( work, 4 );
        work->field_850 &= ~1;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->field_868 == 0 )
    {
        s07b_800CB770( work );
        if ( work->field_868 )
        {
            work->field_8A0 = 1;
            if ( work->body.action2 != 0 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            if ( work->body.action != 18 )
            {
                GM_ConfigObjectAction( &work->body, 18, 0, 4 );
            }
            work->field_A64 = 1;
        }
    }

    if ( work->field_8F0 == NULL )
    {
        work->field_8EC = 8;
        work->field_8F0 = NULL;
        work->field_850 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }

        work->field_A6A = GV_RandU( 64 ) % 3;
        if ( work->field_A6A == 0 )
        {
            x = -5000;
        }
        else if ( work->field_A6A == 1 )
        {
            x = -500;
        }
        else
        {
            x = 4000;
        }
        s07b_800CB6B0( work, x, -1250, 160 );

        work->field_854 = s07b_800CDCAC;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_8F0 = NULL;
    }
}
void s07b_800CEFF0( Work *work, int time );

void s07b_800CE660( Work *work, int time )
{
    int x;

    if ( time == 0 )
    {
        if ( work->field_8F0 == NULL && book_alive <= 0 && !( work->field_850 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoPicture( work->field_A6A );
            NewPsychoBook( work->field_A6A );
            work->field_8F0 = &picture_alive;
        }

        work->field_868 = 0;
        if ( work->field_A6A == 0 )
        {
            x = -5000;
        }
        else if ( work->field_A6A == 1 )
        {
            x = -500;
        }
        else
        {
            x = 4000;
        }
        s07b_800CB6B0( work, x, -1250, 96 );
        s07b_800CDA90( work );
        work->control.turn.vy = 0;
        s07b_800CC89C( work, 4 );
        work->field_850 &= ~1;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->field_868 == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->field_868 )
        {
            work->field_8A0 = 1;
            if ( work->body.action2 != 0 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            if ( work->body.action != 18 )
            {
                GM_ConfigObjectAction( &work->body, 18, 0, 4 );
            }
            work->field_A64 = 1;
        }
    }

    if ( work->field_8F0 == NULL )
    {
        work->field_850 &= ~0x2000;
        work->field_A6A = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_8F0 = NULL;
        if ( work->field_A58 < 2 )
        {
            work->field_8EC = 0;
            work->field_854 = s07b_800CED04;
        }
        else
        {
            work->field_8EC = 1;
            work->field_854 = s07b_800CEFF0;
        }
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CEA18( Work *work, int time );


void s07b_800CE85C( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->field_8F0 == NULL && !( work->field_850 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoPot();
            if ( !work->field_AE4[ 0 ] )
            {
                NewPsychoStatue();
            }
            NewPsychoOx();
            work->field_8F0 = &pot_alive;
        }
        work->field_868 = 0;
        work->field_850 &= ~1;
        s07b_800CB6B0( work, -500, -1250, 96 );
        s07b_800CDA90( work );
        work->body.objs->flag &= ~0x80;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->field_868 == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->field_868 )
        {
            if ( work->body.action2 != 0 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            if ( work->body.action != 18 )
            {
                GM_ConfigObjectAction( &work->body, 18, 0, 4 );
            }
            work->field_A64 = 1;
        }
    }

    if ( work->field_8F0 == NULL )
    {
        work->field_8EC = 10;
        work->field_850 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800CEA18;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CE85C( Work *work, int time );

void s07b_800CEA18( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->field_8F0 == NULL && !( work->field_850 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoChair();
            NewPsychoPicture( 1 );
            NewPsychoBook( 1 );
            work->field_8F0 = &chair_alive;
        }
        work->field_868 = 0;
        work->field_850 &= ~1;
        s07b_800CB6B0( work, -500, -1250, 96 );
        s07b_800CDA90( work );
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->field_868 == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->field_868 )
        {
            if ( work->body.action2 != 0 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            if ( work->body.action != 18 )
            {
                GM_ConfigObjectAction( &work->body, 18, 0, 4 );
            }
            work->field_A64 = 1;
        }
    }

    if ( work->field_8F0 == NULL )
    {
        work->field_8EC = 9;
        work->field_850 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800CE85C;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CDCAC( Work *work, int time );
void s07b_800CDAFC( Work *work, int time );
void s07b_800CEFF0( Work *work, int time );

void s07b_800CEBAC( Work *work, int time )
{
    void ( *mode )( Work *, int );
    u_short *data;

    if ( time == 0 )
    {
        if ( work->body.action != 15 )
        {
            GM_ConfigObjectAction( &work->body, 15, 0, 4 );
        }
        s07b_800CB224( work );
        data = (u_short *)&s07b_dword_800C339C;
        NewPsychoSonic( &work->body.objs->objs[ 4 ].world, work->control.turn.vy, data[ 5 ], data[ 4 ] );
        s07b_800CC89C( work, 3 );
        work->field_850 &= ~1;
    }

    if ( time == 23 )
    {
        s07b_800CAD54( work, 0x82 );
    }

    if ( work->body.is_end )
    {
        work->field_8EC++;
        switch ( work->field_844 )
        {
        case 2:
            if ( (u_short)work->field_8EC == 4 )
            {
                s07b_800CB6B0( work, -1000, -1500, 160 );
                mode = s07b_800CDCAC;
            }
            else
            {
                mode = s07b_800CEFF0;
            }
            break;
        case 4:
        case 6:
            mode = s07b_800CDAFC;
            break;
        case 8:
            mode = s07b_800CEFF0;
            break;
        default:
            return;
        }
        work->field_854 = mode;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CED04.s")
void s07b_800CEFF0( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        s07b_800CBD4C( work );
        work->field_850 |= 1;
        s07b_800CC9E8( work, 0 );
        s07b_800CC89C( work, 3 );
    }

    if ( GV_Time & 1 )
    {
        DG_VisibleObjs( work->body.objs );
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
    }

    if ( time == 16 )
    {
        GM_SeSetMode( &work->control.mov, 0xB3, 1 );
        DG_InvisibleObjs( work->body.objs );
        s07b_800CB9E8( work, 160 );
        work->field_854 = s07b_800CDCAC;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_850 |= 0x200;
        s07b_800CC9E8( work, 24 );
        work->hom->flag = 0;
    }
}
void s07b_800CF200( Work *work, int time );

void s07b_800CF130( Work *work, int time )
{
    if ( time == 0 )
    {
        work->hom->flag = 1;
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        work->field_850 |= 1;
        if ( work->field_844 == 2 )
        {
            s07b_800CAD54( work, 0x80 );
        }
        s07b_800CC89C( work, 3 );
    }
    s07b_800CC8D4( work );
    s07b_800CB224( work );
    if ( time == *(u_short *)&s07b_dword_800C33A8 )
    {
        work->field_854 = s07b_800CF200;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CEBAC( Work *work, int time );

// blink (visible every other frame) for 16 frames
void s07b_800CF200( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        s07b_800CC89C( work, 3 );
    }

    if ( GV_Time & 1 )
    {
        DG_VisibleObjs( work->body.objs );
    }
    else
    {
        DG_InvisibleObjs( work->body.objs );
    }

    if ( time == 16 )
    {
        work->field_850 &= ~1;
        s07b_800CBCE8( work );
        if ( !( work->field_84C & 1 ) )
        {
            work->field_864 = 1;
        }
        work->field_854 = s07b_800CEBAC;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF304.s")

// mode function: reset the animations on the first frame (time == 0)
void s07b_800CF684( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        work->field_8A0 = 0;
    }
}

void s07b_800CF6F0( Work *work, int time )
{
    if ( time == 0 )
    {
        GM_GameStatus |= 0x10000000;
    }

    if ( time == 48 && GM_Vitality != 0 && GM_GameOverTimer == 0 )
    {
        work->field_84C &= ~0x10;
        s07b_800CC138( work, -1 );
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF768.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CF9A0.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D075C.s")
void OpenCinemaScreen( int type, int time );
void CloseCinemaScreen( void );

void s07b_800D0774( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( GM_ItemTypes[ GM_Item + 1 ] & 0x2 )
        {
            GM_Item = IT_None;
        }
        if ( GM_WeaponTypes[ GM_Weapon + 1 ] & 0x200 )
        {
            GM_Weapon = WP_None;
        }
        GM_GameStatus |= 0x104A2000;
        s07b_800CCA10( work );
        s07b_800CC9E8( work, 0 );
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_850 &= ~0x20;
        OpenCinemaScreen( 1, 30000 );
        work->control.step = DG_ZeroVector;
        work->body.objs->flag &= ~0x80;
        s07b_800CB068( 0 );
        s07b_800CB0B4( work, 0 );
        GM_VoxQueue( work->field_ABC[ 2 ] );
        s07b_800CC930();
    }

    GM_SnakeCamera.position = work->control.mov;
    GM_SnakeCamera.track = 3200;

    if ( GM_VoxEnd() )
    {
        GM_GameStatus = ( GM_GameStatus & ~0x104A2000 ) | 0x400000;
        s07b_800CCA10( work );
        CloseCinemaScreen();
        work->field_846 = 8;
        work->field_850 |= 0x20;
        work->field_84C &= ~0x10;
        work->field_850 |= 0x10;
    }
}
void s07b_800D098C( Work *work, int time )
{
    if ( time == 0 )
    {
        work->field_854 = s07b_800CDBA4;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CC89C( work, 1 );
    }

    s07b_800CB2A4( work );

    if ( ( *s07b_dword_800E5BB0 & 0x1008 ) == 0x1000 && GM_GameOverTimer == 0 )
    {
        work->field_846 = 1;
        work->field_854 = s07b_800CF6F0;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_84C |= 0x10;
        work->field_850 |= 0x10;
    }
}
void s07b_800CB2A4( Work *work );

void s07b_800D0A4C( Work *work )
{
    s07b_800CB2A4( work );
}
void s07b_800CED04( Work *work, int time );
void s07b_800CF768( Work *work, int time );
void s07b_800CCBFC( Work *work );
void s07b_800CC6CC( void );

void s07b_800D0A6C( Work *work, int time )
{
    if ( time == 0 )
    {
        work->field_854 = s07b_800CED04;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    s07b_800CB2A4( work );
    s07b_800CCBFC( work );

    if ( work->target->vital <= ( (u_short *)&s07b_dword_800C3390 )[ 1 ] )
    {
        GM_GameStatus |= 0x10000000;
        if ( !( work->field_84C & 4 ) )
        {
            work->field_846 = 3;
            work->field_850 |= 0x10;
            s07b_800CC6CC();
            work->field_854 = s07b_800CF768;
            work->field_858 = 0;
            work->field_A66 = 0;
            work->field_A64 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_84C |= 0x10;
        }
    }
}

void s07b_800D0B40( void )
{
    /* do nothing */
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D0B48.s")

void s07b_800D0C8C( void )
{
    /* do nothing */
}


void s07b_800D0774( Work *work, int time );

void s07b_800D0C94( Work *work, int time )
{
    if ( time == 0 )
    {
        work->field_854 = s07b_800CDBA4;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CC89C( work, 2 );
    }

    s07b_800CB2A4( work );
    s07b_800CCBFC( work );

    if ( ( *s07b_dword_800E5BB0 & 0x800 ) || work->target->vital <= ( (u_short *)&s07b_dword_800C3394 )[ 1 ] )
    {
        GM_GameStatus |= 0x10000000;
        if ( !( work->field_84C & 4 ) )
        {
            if ( !( *s07b_dword_800E5BB0 & 0x800 ) )
            {
                s07b_800CC138( work, 8 );
            }
            if ( work->target->vital < ( (u_short *)&s07b_dword_800C3394 )[ 1 ] )
            {
                work->target->vital = ( (u_short *)&s07b_dword_800C3394 )[ 1 ];
            }
            work->field_846 = 7;
            work->field_854 = s07b_800D0774;
            work->field_858 = 0;
            work->field_A66 = 0;
            work->field_A64 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_84C |= 0x10;
            work->field_850 |= 0x10;
        }
    }
}

void s07b_800D0DCC( void )
{
    /* do nothing */
}

void s07b_800CB2A4( Work *work );
void s07b_800CCBFC( Work *work );

void s07b_800D0DD4( Work *work, int time )
{
    u_short *data;

    if ( time == 0 )
    {
        data = (u_short *)&s07b_dword_800C3390;
        if ( work->target->vital > data[ 3 ] )
        {
            work->target->vital = data[ 3 ];
            work->field_900 = data[ 3 ];
        }
        work->field_854 = s07b_800CEFF0;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CCA10( work );
        work->field_8EC = 1;
        s07b_800CC89C( work, 3 );
    }

    s07b_800CB2A4( work );
    s07b_800CCBFC( work );

    if ( time < 32 )
    {
        GM_SnakeCamera.position = work->control.mov;
        GM_SnakeCamera.track = 3200;
    }

    if ( work->target->vital <= *(u_short *)&s07b_dword_800C3398 && !( work->field_84C & 4 ) )
    {
        work->field_846 = 9;
        work->field_850 |= 0x10;
        s07b_800CBCE8( work );
        if ( !( work->field_84C & 1 ) )
        {
            work->body.objs->flag &= ~0x80;
            work->field_864 = 1;
        }
        s07b_800CB6B0( work, -500, -1250, 160 );
        s07b_800CCA10( work );
        work->field_854 = s07b_800CDCAC;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_8EC = 9;
        s07b_800CC89C( work, 4 );
    }

    s07b_800CB2A4( work );
}
void s07b_800CB2A4( Work *work );
void s07b_800CCBFC( Work *work );

void s07b_800D0F94( Work *work )
{
    s07b_800CB2A4( work );
    s07b_800CCBFC( work );
}

void s07b_800D0FC0( Work *work, int arg1 )
{
    if ( arg1 == 0 )
    {
        CloseCinemaScreen();
        GM_Camera.first_person = 0;
        work->field_864 = 1;
        work->field_84C &= ~0x4;
        DG_VisibleObjs( GM_PlayerBody->objs );
        work->field_854 = s07b_800CF684;
        work->field_858 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CB0B4( work, 0 );
        s07b_800CB068( 0 );
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D105C.s")

void s07b_800D105C( Work *work );
void s07b_800CD86C( Work *work );

void s07b_800D105C( Work *work );
void s07b_800CD86C( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1254.s")
void s07b_800D1254( Work *work );

extern int dword_800BDD28;
extern int dword_8009F444;
extern int dword_8009F434;

void s07b_800D13C4( Work *work )
{
    s07b_800CBCE8( work );

    if ( work->shadow )
    {
        GV_DestroyOtherActor( work->shadow );
    }
    if ( work->sepia )
    {
        GV_DestroyOtherActor( work->sepia );
    }
    if ( work->field_834 )
    {
        GV_DestroyOtherActor( work->field_834 );
    }

    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );
    GM_FreeTarget( work->target );

    dword_800BDD28 = 0;
    dword_8009F444 = 0;
    dword_8009F434 = 0;
    dword_8009F49C = 0;
    dword_8009F480 = 0;
    GM_ResetHomingTarget( work->hom );
    GM_VoxInit();
}
void s07b_800D13C4( Work *work );

int s07b_800D1484( Work *work )
{
    int      level;
    int      i;
    u_short *data;
    TARGET  *target;
    HOMING  *hom;

    if ( GCL_GetOption( 'l' ) )
    {
        GCL_GetNextInt();
    }

    if ( GCL_GetOption( 'x' ) )
    {
        level = GM_GameLevel;
        if ( level < 0 )
        {
            level = 0;
        }
        for ( i = 0; i < level * 5; i++ )
        {
            GCL_GetNextInt();
        }
        i = 0;
        data = (u_short *)&s07b_dword_800C3390;
        for ( ; i < 5; i++ )
        {
            *data++ = GCL_GetNextInt();
        }
    }

    if ( GCL_GetOption( 'y' ) )
    {
        level = GM_GameLevel;
        if ( level < 0 )
        {
            level = 0;
        }
        for ( i = 0; i < level * 7; i++ )
        {
            GCL_GetNextInt();
        }
        i = 0;
        data = (u_short *)&s07b_dword_800C339C;
        for ( ; i < 7; i++ )
        {
            *data++ = GCL_GetNextInt();
        }
    }

    target = GM_AllocTarget();
    work->target = target;
    if ( !target )
    {
        return -1;
    }

    GM_SetTarget( target, 0x9D, 2, (SVECTOR *)&s07b_dword_800C3400 );
    GM_SetPowerTarget( target, 1, -1, *(u_short *)&s07b_dword_800C3390, 0, &DG_ZeroVector );
    hom = GM_SetHomingTarget( &work->body.objs->objs[ 6 ].world, &work->control );
    work->hom = hom;
    hom->flag = 1;
    *(u_short *)&s07b_dword_800C33F0 = target->vital;
    return 0;
}
int s07b_800D1484( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D1638.s")
void s07b_800D1638( Work *work );

int s07b_800D187C( HZD_PAT *patrol, int *count, SVECTOR *data )
{
    int n_points;
    HZD_PTP *point;

    n_points = *count = patrol->n_points;
    point = patrol->points;
    while ( --n_points >= 0 )
    {
        data->vx = point->x;
        data->vy = point->y;
        data->vz = point->z;
        data->pad = point->command;
        point++;
        data++;
    }

    return 0;
}

int s07b_800D18E0( Work *work )
{
    int route_no;
    HZD_HDL *hzd;
    HZD_PAT *route;

    if ( GCL_GetOption( 'r' ) )
    {
        route_no = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        route_no = 0;
    }

    hzd = work->control.map->hzd;
    route = hzd->def->routes;
    route += route_no;

    if ( s07b_800D187C( route, &work->n_points, work->points ) < 0 ) return -1;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D195C.s")
void s07b_800D195C( Work *work );

void s07b_800D1C80( Work *work )
{
    int i;
    int *data;
    char *str;

    if ( GCL_GetOption( 't' ) )
    {
        i = 0;
        data = work->field_ABC;
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 4 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

void s07b_800D1CF8( Work *work )
{
    int i;
    int *data;
    char *str;

    if ( GCL_GetOption( 'c' ) )
    {
        i = 0;
        data = work->field_ACC;
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 6 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

void s07b_800D1D70( Work *work )
{
    int i;
    char *data, *str;

    if ( GCL_GetOption( 'f' ) )
    {
        i = 0;
        data = work->field_AE4;
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 4 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

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
