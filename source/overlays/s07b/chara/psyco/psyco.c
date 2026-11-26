#include "chara/psyco/psyco.h"

#include <stdio.h>
#include <string.h>
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/navi.h"
#include "okajima/bullet.h"
#include "takabe/cineutil.h"
#include "menu/menuman.h"
#include "chara/snake/sna_init.h"

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode( "psycho" )
#define MOTION_DATA GV_StrCode( "psycho" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

#define TARGET_FLAG ( TARGET_AVAIL | TARGET_POWER | TARGET_PUSH | TARGET_SEEK | TARGET_TOUCH )

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
    /* 0x7E4 */ TARGET attack;
    /* 0x82C */ HOMING *hom;
    /* 0x830 */ void *sepia;              // sepia screen effect (NewSepia_800C5214), s07b_800CB0B4
    /* 0x834 */ void *field_834;          // actor, destroyed in s07b_800D13C4
    /* 0x838 */ void *kogaku;             // optical camouflage actor (NewKogaku2), NULL when off
    /* 0x83C */ int kogaku_state;         // 10 = on, -1 = off
    /* 0x840 */ int meryl_name;           // GV_SendMessage address (s07b_800CC138)
    /* 0x844 */ short state;
    /* 0x846 */ short next_state;         // taken when flags2 flag 0x10 is set; < 0: run proc_id and destroy (s07b_800CAFC8)
    /* 0x848 */ int field_848;

    /* 0x84C */ int flags;

    /* 0x850 */ int flags2;

    /* 0x854 */ void *action;
    /* 0x858 */ int time;

    /* 0x85C */ void *action2;           // runs instead of action while flags flag 0x4 is set
    /* 0x860 */ int   time2;

    /* 0x864 */ int field_864;

    /* 0x868 */ int arrived;              // touching a wall or close to point (s07b_800CB8CC)
    /* 0x86C */ short turn_step;          // while in s07b_800CDCAC (s07b_800CB8CC)

    /* 0x86E */ short field_86E;

    /* 0x870 */ SVECTOR point;           // (vx, vz), s07b_800CB9E8 picks the next one
    /* 0x878 */ SVECTOR field_878;
    /* 0x880 */ SVECTOR field_880;
    /* 0x888 */ char pad888[ 0x8 ];

    /* 0x890 */ SVECTOR pos;
    /* 0x898 */ SVECTOR rot;

    /* 0x8A0 */ int height_level;         // 0..2: index of s07b_dword_800C33F4 (control.hzd_height)

    /* 0x8A4 */ int     n_points;
    /* 0x8A8 */ SVECTOR points[ 8 ];

    /* 0x8E8 */ char pad8E8[ 0x4 ];

    /* 0x8EC */ short field_8EC;
    /* 0x8EE */ short field_8EE;

    /* 0x8F0 */ int *object_alive;        // *_alive of the thrown object (chara/psyco)
    /* 0x8F4 */ MENU_BAR_CONF lifebar;    // colours change with the max vital (s07b_800CD86C)
    /* 0x900 */ int  lifebar_rest;        // drops towards target->vital (s07b_800CD86C)
    /* 0x904 */ POLY_F4  white_screen[ 2 ];
    /* 0x934 */ POLY_FT4 hideo_b[ 2 ];
    /* 0x984 */ POLY_FT4 hideo_s[ 2 ];
    /* 0x9D4 */ POLY_FT4 hideo[ 2 ];
    /* 0xA24 */ POLY_F4  black_screen[ 2 ];
    /* 0xA54 */ DG_TEX  *hideo_tex;
    /* 0xA58 */ int  picture_count;       // finished picture attacks; < 2: goes on to s07b_800CED04
    /* 0xA5C */ int  field_A5C;           // set to 6 when the picture attack ends (s07b_800CED04)
    /* 0xA60 */ short field_A60;
    /* 0xA62 */ char blink_timer;         // set together with flags flag 0x2 (s07b_800CC9E8)
    /* 0xA63 */ char class_timer;         // target class timer, 8 when the s07b_800CBF00 counter runs out

    /* 0xA64 */ short field_A64;
    /* 0xA66 */ short field_A66;

    /* 0xA68 */ short chair_step;         // s07b_800CDF40
    /* 0xA6A */ short throw_side;         // 0..2 for the picture/book throw
    /* 0xA6C */ SVECTOR head_pos;
    /* 0xA74 */ SVECTOR player_head_pos;
    /* 0xA7C */ char padA7C[ 0x4 ];
    /* 0xA80 */ GV_PAD *pad1;             // GV_PadData[ 0 ], or [ 1 ] with the second controller
    /* 0xA84 */ GV_PAD *pad2;             // GV_PadData[ 1 ]
    /* 0xA88 */ u_char weapon_lock[ 8 ];  // 20-frame counters that make C4/claymore/grenade/Nikita/Stinger fail (s07b_800CBFB0)

    /* 0xA90 */ int      proc_id;
    /* 0xA94 */ NAVIGATE navi;
    /* 0xAB4 */ int      field_AB4;
    /* 0xAB8 */ int      field_AB8;
    /* 0xABC */ int      field_ABC[ 4 ];
    /* 0xACC */ int      field_ACC[ 6 ];
    /* 0xAE4 */ char     field_AE4[ 4 ];
} Work;

// thrown objects (chara/psyco/*.c); Work.object_alive points at their *_alive flag
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
short s07b_dword_800C33F0 = 0;
int s07b_dword_800C33F4[ 3 ] = { 1500, 750, 250 };  // control.hzd_height, indexed by height_level
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

    if ( work->flags2 & 0x10 )
    {
        work->flags2 &= ~0x10;
        if ( work->next_state < 0 )
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
            work->state = work->next_state;
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
        if ( --work->field_864 != 0 || ( work->flags & 1 ) )
        {
            return;
        }
        if ( !( work->flags2 & 1 ) )
        {
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        }
        s07b_800CB0B4( work, 0 );
        s07b_800CB068( 0 );
        printf( (char *)s07b_dword_800E4F5C );
    }
    else
    {
        if ( ++work->field_864 != 0 || !( work->flags & 1 ) )
        {
            return;
        }
        work->body.objs->flag |= DG_FLAG_INVISIBLE;
        s07b_800CB0B4( work, 1 );
        s07b_800CB068( 1 );
        printf( (char *)s07b_dword_800E4F70 );
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
extern int dword_8009F46C;
void SetPadMask( int mask );
void ClearPadMask( int mask );

void s07b_800CB2A4( Work *work )
{
    int      flags;
    int      yaw;
    CONTROL *player;

    s07b_800CB130( work );

    flags = work->flags;
    if ( !( flags & 1 ) )
    {
        if ( ( work->pad1->press & PAD_X ) && !dword_8009F46C &&
             !( GM_WeaponTypes[ GM_Weapon + 1 ] & 0x200 ) &&
             !( GM_ItemTypes[ GM_Item + 1 ] & 0x2 ) &&
             !( GM_PlayerStatus & PLAYER_ATTACK ) &&
             ( GM_FirstPerson == 0 || ( GM_FirstPerson == 1 && ( GM_PlayerStatus & PLAYER_STILL_WATCH ) ) ) &&
             GM_Camera.first_person )
        {
            work->flags = flags | 1;
            SetPadMask( ~0x10 );
            work->field_864 = -1;
            GM_PlayerStatus |= PLAYER_NOT_SIGHT;
            if ( GM_PlayerStatus & PLAYER_CAUTION )
            {
                ClearPadMask( 0xF000 );
            }
            printf( (char *)s07b_dword_800E4F80, work->field_864 );
        }
        if ( work->field_864 )
        {
            return;
        }
        if ( !( work->flags2 & 1 ) )
        {
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
            return;
        }
    }
    else
    {
        if ( GM_PlayerStatus & PLAYER_CAUTION )
        {
            ClearPadMask( 0xF000 );
        }
        else
        {
            SetPadMask( 0xF000 );
        }

        if ( GV_Time % 45 == 0 )
        {
            GM_SeSet2( 0, 63, SE_MASK0002 );
        }

        GM_PlayerBody->objs->flag &= ~DG_FLAG_INVISIBLE;

        GM_SnakeCamera.position.vx = work->body.objs->objs[ 6 ].world.t[ 0 ];
        GM_SnakeCamera.position.vy = work->body.objs->objs[ 6 ].world.t[ 1 ];
        GM_SnakeCamera.position.vz = work->body.objs->objs[ 6 ].world.t[ 2 ];
        GM_SnakeCamera.rotate2 = work->control.rot;
        GM_SnakeCamera.rotate2.vx = 360;
        GM_Camera.zoom = 320;
        GM_SnakeCamera.position.vy += 480;

        yaw = work->control.turn.vy;
        s07b_800CB224( work );
        GM_SnakeCamera.rotate2.vy = work->control.turn.vy;
        work->control.turn.vy = yaw;

        player = GM_PlayerControl;
        player->step.vx = 0;
        player->step.vz = 0;
        player->rot.vx = 0;
        player->rot.vz = 0;
        player->turn.vx = 0;
        player->turn.vz = 0;
        player->turn.vy = player->rot.vy;

        if ( !( work->pad1->status & PAD_X ) || !GM_Camera.first_person )
        {
            work->flags &= ~1;
            ClearPadMask( ~0x10 );
            if ( GM_Camera.first_person )
            {
                GM_PlayerBody->objs->flag |= DG_FLAG_INVISIBLE;
                GM_SnakeCamera.position = GM_PlayerPosition;
            }
            work->field_864 = 1;
            GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
            printf( (char *)s07b_dword_800E4F94, work->field_864 );
        }
        if ( work->field_864 )
        {
            return;
        }
    }

    work->body.objs->flag |= DG_FLAG_INVISIBLE;
}
void s07b_800CB2A4( Work *work );
void s07b_800CB6B0( Work *work, short x, short z, int scale )
{
    SVECTOR pos;

    work->point.vx = x;
    work->point.vz = z;
    if ( (short)scale > 0 )
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

    work->arrived = 0;
    if ( dist < work->field_86E )
    {
        work->control.step = diff;
        work->arrived = 1;
    }
    else
    {
        GV_LenVec3( &diff, &work->control.step, len, work->field_86E );
    }

    if ( work->action == s07b_800CDCAC )
    {
        work->control.turn.vy = ( work->control.turn.vy + ( work->turn_step - 1 ) * 1024 ) & 0xFFF;
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
    to = work->point;
    to.vy = 0;
    from.vy = 0;
    GV_SubVec3( &to, &from, &diff );
    len = GV_VecLen3( &diff );

    work->arrived = 0;
    if ( work->control.n_touches )
    {
        work->arrived = 1;
    }

    if ( len < work->field_86E )
    {
        work->control.step = diff;
        work->arrived = 1;
    }
    else
    {
        GV_LenVec3( &diff, &work->control.step, len, work->field_86E );
    }

    if ( work->action == s07b_800CDCAC )
    {
        work->control.turn.vy = ( work->control.turn.vy + ( work->turn_step - 1 ) * 1024 ) & 0xFFF;
    }
}


void s07b_800CB9E8( Work *work, int arg1 )
{
    SVECTOR *point;
    int      count;

    count = work->n_points;
    point = &work->points[ GV_RandU( 32 ) % count ];
    while ( point->vx == work->point.vx && point->vz == work->point.vz )
    {
        point = &work->points[ GV_RandU( 32 ) % count ];
    }

    s07b_800CB6B0( work, point->vx, point->vz, arg1 );
}
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

    switch ( work->state )
    {
    case 2:
    case 9:
        idx = work->field_8EC;
        if ( idx == 5 && work->object_alive == NULL )
        {
            idx = 6;
        }
        else if ( idx == 6 && work->object_alive == NULL )
        {
            idx = 7;
        }
        work->field_8EC = idx;
        work->action = ( (PSYCO_MODE *)&s07b_dword_800C33AC )[ idx ];
        work->time = 0;
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
    work->action = mode;
    work->time = 0;
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
    if ( work->kogaku_state != -1 )
    {
        if ( work->kogaku )
        {
            GV_DestroyActor( work->kogaku );
        }
        work->kogaku = NULL;
        work->kogaku_state = -1;
        *work->shadow_enable = 1;
    }
}

// optical camouflage on
void s07b_800CBD4C( Work *work )
{
    if ( work->kogaku_state != 10 )
    {
        work->kogaku = NewKogaku2( &work->control, &work->body, 6 );
        work->kogaku_state = 10;
        *work->shadow_enable = 0;
    }
}
void s07b_800CBDA0( Work *work )
{
    if ( !( work->flags2 & 4 ) )
    {
        work->field_878.vy = -32;
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
            work->class_timer = 8;
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

    if ( GV_PauseLevel || ( work->flags & 0x10 ) || ( GM_GameStatus & STATE_PADRELEASE ) )
    {
        return;
    }

    if ( work->state == 0 )
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

    msg.address = work->meryl_name;
    msg.message_len = 2;
    msg.message[0] = 0x491D;
    msg.message[1] = arg1;
    GV_SendMessage( &msg );
}
void s07b_800CC174( Work *work, int time )
{
    int       alt;
    u_long   *ot;
    int       i;
    int       last;
    POLY_FT4 *poly;

    alt = (short)( GM_Configuration & 0x100 );
    ot = ( DG_Chanl( 0 ) + 1 )->ot[ GV_Time & 1 ];

    if ( time == 0 )
    {
        for ( i = 0; i < 2; i++ )
        {
            poly = &work->hideo[ i ];
            if ( !alt )
            {
                poly->x0 = poly->x2 = 224;
                poly->x1 = poly->x3 = 296;
                poly->y0 = poly->y1 = 8;
                poly->y2 = poly->y3 = 40;
            }
        }
        addPrim( ot, &work->white_screen[ GV_Time & 1 ] );
    }
    else
    {
        if ( time == 64 )
        {
            for ( i = 0; i < 2; i++ )
            {
                poly = &work->hideo[ i ];
                if ( !alt )
                {
                    poly->x0 = poly->x2 = 260;
                    poly->x1 = poly->x3 = 296;
                    poly->y0 = poly->y1 = 8;
                    poly->y2 = poly->y3 = 24;
                }
            }
        }

        last = ( work->picture_count != 0 ) ? 127 : 255;
        if ( time == last )
        {
            addPrim( ot, &work->white_screen[ GV_Time & 1 ] );
        }
        else
        {
            if ( !alt )
            {
                addPrim( ot, &work->hideo[ GV_Time & 1 ] );
            }
            else if ( time >= 64 )
            {
                addPrim( ot, &work->hideo_s[ GV_Time & 1 ] );
            }
            else
            {
                addPrim( ot, &work->hideo_b[ GV_Time & 1 ] );
            }
            addPrim( ot, &work->black_screen[ GV_Time & 1 ] );
        }
    }
}
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

void s07b_800CC50C( Work *work )
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
    if ( work->object_alive && *work->object_alive <= 0 )
    {
        printf( (char *)s07b_dword_800E4FB4 );
        work->object_alive = NULL;
    }
}
void s07b_800CC6CC( void )
{
    chair_alive = -1;
    statue_alive = -1;
    pot_alive = -1;
    ox_alive = -1;
    picture_alive = -1;
    book_alive = -1;
}
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
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        }
        else
        {
            work->body.objs->flag |= DG_FLAG_INVISIBLE;
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
    work->blink_timer = arg1;
    work->flags |= 2;
    work->target->class &= ~0x94;
}
// end of the state started by s07b_800CC9E8
void s07b_800CCA10( Work *work )
{
    work->blink_timer = 0;
    work->flags &= ~2;
    work->flags2 &= ~0x200;
    work->target->class |= 0x9C;
    if ( !( work->flags2 & 1 ) )
    {
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
    }
}
// blink timer (blink_timer) and target class timer (class_timer)
void s07b_800CCA80( Work *work )
{
    if ( work->blink_timer )
    {
        if ( !( work->flags2 & 0x200 ) )
        {
            if ( work->blink_timer & 3 )
            {
                DG_VisibleObjs( work->body.objs );
            }
            else
            {
                DG_InvisibleObjs( work->body.objs );
            }
        }
        if ( --work->blink_timer == 0 )
        {
            if ( !( work->flags2 & 0x200 ) )
            {
                DG_VisibleObjs( work->body.objs );
            }
            s07b_800CCA10( work );
        }
    }

    if ( work->class_timer )
    {
        if ( --work->class_timer == 0 )
        {
            if ( !( work->flags & 2 ) )
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
void s07b_800CD25C( Work *work, int time );
void s07b_800CD40C( Work *work, int time );
void s07b_800CD594( Work *work, int time );

void s07b_800CF304( Work *work, int time );

void s07b_800CCBFC( Work *work )
{
    TARGET *target;
    int     react;
    PSYOBJ *busts[ 2 ];

    if ( ( work->flags & 2 ) || work->class_timer || ( *s07b_dword_800E5BB0 & 8 ) || GM_Vitality == 0 )
    {
        s07b_800CCA80( work );
        return;
    }

    target = work->target;
    target->vital += target->damage;
    if ( !( target->damaged & 4 ) )
    {
        return;
    }

    if ( GM_PlayerStatus & PLAYER_SECOND_CONTROLLER )
    {
        react = 1;
        if ( target->a_mode == 2 )
        {
            work->flags2 |= 0x1000;
            react = 0;
        }
    }
    else if ( ++work->field_AB8 == 8 )
    {
        react = 1;
        work->field_AB8 = 0;
    }
    else
    {
        react = 0;
    }

    if ( !react && work->field_AE4[ 0 ] && target->a_mode != 2 )
    {
        busts[ 0 ] = PSYOBJ_FindObject( GV_StrCode( s07b_dword_800E4FC0 ) );
        busts[ 1 ] = PSYOBJ_FindObject( GV_StrCode( s07b_dword_800E4FC8 ) );
        if ( busts[ 0 ] && busts[ 1 ] && ( busts[ 0 ]->flag & 0x100 ) && ( busts[ 1 ]->flag & 0x100 ) )
        {
            react = 1;
            work->flags2 |= 0x400;
        }
    }

    if ( work->body.action2 )
    {
        GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
    }

    if ( react )
    {
        if ( target->a_mode == 3 )
        {
            GM_SeSet( &work->control.mov, SE_PUNCHIT1 );
            target->vital -= ( (u_short *)&s07b_dword_800C339C )[ 0 ];
            if ( !( work->flags2 & 2 ) )
            {
                work->action2 = s07b_800CD25C;
                work->time2 = 0;
                work->field_A66 = 0;
                work->field_A64 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                work->flags |= 4;
            }
        }
        else if ( target->a_mode == 4 )
        {
            GM_SeSet( &work->control.mov, SE_KICKHIT1 );
            target->vital -= ( (u_short *)&s07b_dword_800C339C )[ 1 ];
            if ( !( work->flags2 & 2 ) )
            {
                work->action2 = s07b_800CD40C;
                work->time2 = 0;
                work->field_A66 = 0;
                work->field_A64 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                work->flags |= 4;
            }
        }
        else if ( target->a_mode == 1 )
        {
            if ( target->weapon == 5 )
            {
                target->vital -= ( (u_short *)&s07b_dword_800C33A0 )[ 1 ];
            }
            else
            {
                target->vital -= ( (u_short *)&s07b_dword_800C33A0 )[ 0 ];
            }
            if ( !( work->flags2 & 2 ) )
            {
                work->action2 = s07b_800CD25C;
                work->time2 = 0;
                work->field_A66 = 0;
                work->field_A64 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                work->flags |= 4;
            }
        }
        else
        {
            target->vital -= ( (u_short *)&s07b_dword_800C33A0 )[ 1 ];
            if ( !( work->flags2 & 2 ) )
            {
                work->action2 = s07b_800CD40C;
                work->time2 = 0;
                work->field_A66 = 0;
                work->field_A64 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                work->flags |= 4;
            }
        }

        s07b_800CC9E8( work, 8 );
        s07b_800CBDCC( work, 6 );
        s07b_800CAD54( work, 136 );
        s07b_800CCBB0( target );

        if ( target->vital <= 0 && GM_Vitality != 0 && GM_GameOverTimer == 0 )
        {
            work->action = s07b_800CF304;
            work->time = 0;
            work->field_A66 = 0;
            work->field_A64 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->flags &= ~4;
        }
    }
    else
    {
        s07b_800CCA10( work );
        s07b_800CC9E8( work, 0 );
        work->action2 = s07b_800CD594;
        work->time2 = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->flags |= 4;
        work->chair_step = target->a_mode;
        s07b_800CCBB0( target );
    }
}
void s07b_800CED04( Work *work, int time );
void s07b_800CEFF0( Work *work, int time );
void s07b_800CDAFC( Work *work, int time );

void s07b_800CCFE4( Work *work )
{
    PSYCO_MODE mode;
    int        phase;
    short      idx;

    work->flags2 &= ~0x2000;
    idx = work->state - 2;
    switch ( idx )
    {
    case 0:
        phase = (u_short)work->field_8EC;
        switch ( phase )
        {
        case 0:
            mode = s07b_800CED04;
            break;
        case 1:
        case 2:
        case 3:
            if ( (u_short)++work->field_8EC == 4 )
            {
                s07b_800CB6B0( work, -1000, -1500, 160 );
                mode = s07b_800CDCAC;
                s07b_800CBCE8( work );
                if ( !( work->flags & 1 ) )
                {
                    work->field_864 = 1;
                }
            }
            else
            {
                mode = s07b_800CEFF0;
            }
            break;
        case 5:
        case 6:
            s07b_800CB9E8( work, 160 );
            mode = s07b_800CDCAC;
            break;
        case 4:
        case 7:
        case 8:
        default:
            if ( work->action == s07b_800CDCAC )
            {
                mode = s07b_800CDCAC;
            }
            else if ( work->object_alive )
            {
                mode = ( (PSYCO_MODE *)&s07b_dword_800C33AC )[ phase ];
                work->flags2 |= 0x2000;
            }
            else
            {
                phase++;
                if ( phase == 9 )
                {
                    phase = work->picture_count >= 2;
                }
                if ( phase == 5 && work->field_AE4[ 0 ] )
                {
                    phase = 6;
                }
                work->field_8EC = phase;
                if ( phase == 1 )
                {
                    mode = s07b_800CEFF0;
                }
                else
                {
                    mode = ( (PSYCO_MODE *)&s07b_dword_800C33AC )[ phase ];
                }
            }
            break;
        }
        break;
    case 2:
    case 4:
        mode = s07b_800CDAFC;
        break;
    case 6:
        mode = s07b_800CEFF0;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    default:
        if ( work->object_alive )
        {
            mode = work->action;
            work->flags2 |= 0x2000;
        }
        else
        {
            phase = 9;
            if ( (u_short)work->field_8EC == 9 )
            {
                phase = 10;
            }
            work->field_8EC = phase;
            mode = ( (PSYCO_MODE *)&s07b_dword_800C33AC )[ phase ];
        }
        break;
    }

    work->action = mode;
    work->time = 0;
    work->field_A66 = 0;
    work->field_A64 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    if ( mode == s07b_800CEFF0 )
    {
        work->flags2 |= 0x200;
    }
    s07b_800CC9E8( work, 32 );
}



void s07b_800CCFE4( Work *work );

void s07b_800CD25C( Work *work, int time )
{
    int action;

    if ( time == 0 )
    {
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        if ( work->kogaku_state == 10 )
        {
            work->field_A64 = 1;
        }

        s07b_800CBCE8( work );
        work->flags2 &= ~1;

        action = ( GV_Time & 1 ) ? 20 : 21;
        work->body.action = -1;
        if ( work->body.action != action )
        {
            GM_ConfigObjectAction( &work->body, action, 0, 4 );
        }

        s07b_800CC9E8( work, 0 );
        work->control.step = DG_ZeroVector;
    }

    if ( work->body.is_end )
    {
        s07b_800CCFE4( work );
        work->flags &= ~4;
        if ( ( ( GM_PlayerStatus & PLAYER_SECOND_CONTROLLER ) || ( work->flags2 & 0x400 ) ) && GV_RandS( 64 ) > 0 )
        {
            if ( work->state == 2 && work->target->vital <= ( (u_short *)&s07b_dword_800C3390 )[ 1 ] )
            {
                return;
            }

            if ( work->state == 4 && work->target->vital <= *(u_short *)&s07b_dword_800C3394 )
            {
                return;
            }

            s07b_800CAD54( work, ( GV_Time & 1 ) ? 134 : 135 );
        }
    }
}
void s07b_800CD40C( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->kogaku_state == 10 )
        {
            work->field_A64 = 1;
        }

        s07b_800CBCE8( work );
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        work->flags2 &= ~1;
        if ( work->body.action != 24 )
        {
            GM_ConfigObjectAction( &work->body, 24, 0, 4 );
        }

        s07b_800CC9E8( work, 0 );
        work->control.step = DG_ZeroVector;
    }

    if ( work->body.is_end )
    {
        s07b_800CCFE4( work );
        work->flags &= ~4;
        if ( ( GM_PlayerStatus & PLAYER_SECOND_CONTROLLER ) && GV_RandS( 64 ) >= -15 )
        {
            if ( work->state == 2 && work->target->vital <= ( (u_short *)&s07b_dword_800C3390 )[ 1 ] )
            {
                return;
            }

            if ( work->state == 4 && work->target->vital <= *(u_short *)&s07b_dword_800C3394 )
            {
                return;
            }

            s07b_800CAD54( work, ( GV_Time & 1 ) ? 134 : 135 );
        }
    }
}

void s07b_800CD594( Work *work, int time )
{
    SVECTOR offset;
    MATRIX  mat;
    int     side;
    int     action;
    int     color;
    int     type;

    if ( time == 0 )
    {
        work->height_level = 0;
        GM_SeSetMode( &work->control.mov, 199, GM_SEMODE_BOMB );
        if ( !( work->flags2 & 0x1000 ) )
        {
            if ( work->field_AB8 == 1 )
            {
                s07b_800CAD54( work, 132 );
            }
            else if ( work->field_AB8 == 3 )
            {
                s07b_800CAD54( work, 132 );
            }
            else if ( work->field_AB8 == 5 )
            {
                s07b_800CAD54( work, 133 );
            }
        }

        side = !( GV_Time & 1 );
        work->field_A64 = side;
        work->flags2 &= ~0x1000;
        s07b_800CB224( work );
        work->control.rot = work->control.turn;

        if ( work->chair_step == 1 )
        {
            s07b_800CBE34( work, &mat );
            color = 0;
            type = 0;
            switch ( GM_Weapon )
            {
            case 0:
                break;
            case 1:
                if ( GM_Magazine == GM_MagazineMax || GM_Magazine < 3 )
                {
                    color = 2;
                }
                else
                {
                    type = 1;
                }
                break;
            case 9:
                type = 2;
                break;
            }
            NewBullet( &mat, 1, color, type );
        }
        work->chair_step = 0;

        work->head_pos = work->point;
        work->head_pos.pad = work->field_86E;
        offset.vy = offset.vz = 0;
        offset.vx = side ? 1400 : -1400;
        action = side ? 10 : 13;
        DG_SetPos2( &work->control.mov, &work->control.rot );
        DG_PutVector( &offset, &work->point, 1 );
        work->field_86E = 224;
        if ( work->body.action != action )
        {
            GM_ConfigObjectAction( &work->body, action, 0, 4 );
        }
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        work->flags2 &= ~1;
        if ( work->kogaku_state == 10 )
        {
            work->field_A66 = 1;
        }
        s07b_800CBCE8( work );
    }

    s07b_800CB8CC( work );
    if ( work->arrived )
    {
        work->point = work->head_pos;
        work->field_86E = work->head_pos.pad;
        s07b_800CCFE4( work );
        work->flags &= ~4;
        s07b_800CCA10( work );
        s07b_800CC9E8( work, 8 );
        work->flags2 |= 0x200;
    }
}
void s07b_800CD86C( Work *work )
{
    int now;
    int rest;
    int diff;

    if ( work->flags2 & 0x20 )
    {
        now = work->target->vital;
        if ( now < 0 )
        {
            now = 0;
        }
        rest = work->lifebar_rest;
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
                work->lifebar_rest -= 64;
            }
            else
            {
                work->lifebar_rest -= diff;
            }
        }
    }
}

extern char psyco_name[ 16 ];

int s07b_800CDA04( Work *work )
{
    MENU_BAR_CONF *lifebar;

    work->lifebar_rest = work->target->vital;
    strcpy( psyco_name, "MANTIS" );
    work->lifebar.name = psyco_name;

    lifebar = &work->lifebar;
    lifebar->left[ 0 ] = 0x10;
    lifebar->left[ 1 ] = 0x6F;
    lifebar->left[ 2 ] = 0x9F;
    lifebar->right[ 0 ] = 0x1F;
    lifebar->right[ 1 ] = 0xDF;
    lifebar->right[ 2 ] = 0x7F;
    return 0;
}

const char s07b_dword_800E5020[] = "マンティス";
int s07b_800CDA04( Work *work );

void s07b_800CDA90( Work *work )
{
    work->height_level = 0;
    if ( work->body.action != 1 )
    {
        GM_ConfigObjectAction( &work->body, 1, 0, 4 );
    }

    {
        int           action = 19;
        unsigned long mask = 0x3FE;

        if ( work->body.action2 != action )
        {
            GM_ConfigObjectOverride( &work->body, action, 0, 4, mask );
        }
    }
}
void s07b_800CDA90( Work *work );
void s07b_800CBC20( Work *work );
void s07b_800CDBA4( Work *work, int time );

void s07b_800CDAFC( Work *work, int time )
{
    if ( time == 0 )
    {
        s07b_800CDA90( work );
        work->flags2 &= ~1;
    }

    s07b_800CBC20( work );

    if ( !( *s07b_dword_800E5BB0 & 4 ) )
    {
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->action = s07b_800CDBA4;
        work->time = 0;
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
        work->height_level = 0;
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        work->flags2 &= ~1;
    }

    s07b_800CBC20( work );

    if ( *s07b_dword_800E5BB0 & 4 )
    {
        switch ( work->state )
        {
        case 0:
            work->action = s07b_800CDAFC;
            break;
        case 4:
        case 6:
            work->field_8EC = 1;
            work->action = s07b_800CEBAC;
            break;
        default:
            s07b_800CB9E8( work, 160 );
            work->action = s07b_800CDCAC;
            break;
        }
        work->time = 0;
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
        work->height_level = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }

        work->turn_step = s07b_800CBAA4( work );
        switch ( work->turn_step )
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
        if ( !( work->flags2 & 1 ) )
        {
            GM_SeSetMode( &work->control.mov, 0xC8, GM_SEMODE_BOMB );
        }
    }

    if ( time > 24 )
    {
        work->field_86E += 4;
    }

    if ( work->state == 8 )
    {
        work->body.objs->flag |= DG_FLAG_INVISIBLE;
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
        if ( work->arrived || work->time >= 180 )
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

    if ( work->flags2 & 4 )
    {
        work->control.step.vy += 2;
    }
    else
    {
        work->control.step.vy += 34;
    }

    if ( work->state == 3 )
    {
        GM_SnakeCamera.position = work->control.mov;
    }

    s07b_800CC8D4( work );
}
void s07b_800CE134( Work *work, int time );
void s07b_800CE2A8( Work *work, int time );

void s07b_800CDF40( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->object_alive == NULL && !( work->flags2 & 0x2000 ) )
        {
            work->chair_step = 0;
            s07b_800CAD54( work, 0x81 );
            NewPsychoChair();
            work->object_alive = &chair_alive;
        }
        s07b_800CDA90( work );
        s07b_800CC89C( work, 4 );
        work->flags2 &= ~1;
    }

    s07b_800CB224( work );

    switch ( work->chair_step )
    {
    case 0:
        if ( chair_alive == 2 )
        {
            s07b_800CB6B0( work, -1000, 2000, 32 );
            work->chair_step++;
        }
        break;
    case 1:
        s07b_800CB8CC( work );
        if ( work->arrived )
        {
            s07b_800CB6B0( work, -1000, -1500, 32 );
            work->chair_step++;
        }
        break;
    case 2:
        s07b_800CB8CC( work );
        if ( work->arrived )
        {
            s07b_800CB6B0( work, -1000, 2000, 32 );
            work->chair_step = 1;
        }
        break;
    }

    if ( work->object_alive == NULL )
    {
        work->chair_step = 0;
        work->flags2 &= ~0x2000;
        if ( work->field_AE4[ 0 ] == 0 )
        {
            work->field_8EC = 5;
            work->action = s07b_800CE134;
        }
        else
        {
            work->field_8EC = 6;
            work->action = s07b_800CE2A8;
        }
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    if ( chair_alive != 2 )
    {
        work->control.step = DG_ZeroVector;
    }
}
void s07b_800CE2A8( Work *work, int time );

void s07b_800CE134( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->object_alive == NULL && !( work->flags2 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoStatue();
            work->object_alive = &statue_alive;
            s07b_800CB6B0( work, -1000, -1500, 96 );
        }
        s07b_800CC89C( work, 4 );
        work->arrived = 0;
        s07b_800CDA90( work );
        work->flags2 &= ~1;
    }

    if ( work->field_A64 == 0 && work->arrived == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->arrived )
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

    if ( work->object_alive == NULL )
    {
        work->field_8EC = 6;
        work->action = s07b_800CE2A8;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->object_alive = NULL;
        work->flags2 &= ~0x2000;
    }
}
void s07b_800CE43C( Work *work, int time );

void s07b_800CE2A8( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->object_alive == NULL && !( work->flags2 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoPot();
            work->object_alive = &pot_alive;
            s07b_800CB6B0( work, -1000, -1500, 96 );
        }
        work->arrived = 0;
        s07b_800CDA90( work );
        s07b_800CC89C( work, 4 );
        work->flags2 &= ~1;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->arrived == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->arrived )
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

    if ( work->object_alive == NULL )
    {
        work->field_8EC = 7;
        work->flags2 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->action = s07b_800CE43C;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->object_alive = NULL;
    }
}
void s07b_800CED04( Work *work, int time );

void s07b_800CE43C( Work *work, int time )
{
    int x;

    if ( time == 0 )
    {
        if ( work->object_alive == NULL && !( work->flags2 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoOx();
            work->object_alive = &ox_alive;
        }
        work->arrived = 0;
        s07b_800CB6B0( work, 0, 500, 96 );
        s07b_800CDA90( work );
        work->control.turn.vy = 0;
        s07b_800CC89C( work, 4 );
        work->flags2 &= ~1;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->arrived == 0 )
    {
        s07b_800CB770( work );
        if ( work->arrived )
        {
            work->height_level = 1;
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

    if ( work->object_alive == NULL )
    {
        work->field_8EC = 8;
        work->object_alive = NULL;
        work->flags2 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }

        work->throw_side = GV_RandU( 64 ) % 3;
        if ( work->throw_side == 0 )
        {
            x = -5000;
        }
        else if ( work->throw_side == 1 )
        {
            x = -500;
        }
        else
        {
            x = 4000;
        }
        s07b_800CB6B0( work, x, -1250, 160 );

        work->action = s07b_800CDCAC;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->object_alive = NULL;
    }
}
void s07b_800CEFF0( Work *work, int time );

void s07b_800CE660( Work *work, int time )
{
    int x;

    if ( time == 0 )
    {
        if ( work->object_alive == NULL && book_alive <= 0 && !( work->flags2 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoPicture( work->throw_side );
            NewPsychoBook( work->throw_side );
            work->object_alive = &picture_alive;
        }

        work->arrived = 0;
        if ( work->throw_side == 0 )
        {
            x = -5000;
        }
        else if ( work->throw_side == 1 )
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
        work->flags2 &= ~1;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->arrived == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->arrived )
        {
            work->height_level = 1;
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

    if ( work->object_alive == NULL )
    {
        work->flags2 &= ~0x2000;
        work->throw_side = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->object_alive = NULL;
        if ( work->picture_count < 2 )
        {
            work->field_8EC = 0;
            work->action = s07b_800CED04;
        }
        else
        {
            work->field_8EC = 1;
            work->action = s07b_800CEFF0;
        }
        work->time = 0;
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
        if ( work->object_alive == NULL && !( work->flags2 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoPot();
            if ( !work->field_AE4[ 0 ] )
            {
                NewPsychoStatue();
            }
            NewPsychoOx();
            work->object_alive = &pot_alive;
        }
        work->arrived = 0;
        work->flags2 &= ~1;
        s07b_800CB6B0( work, -500, -1250, 96 );
        s07b_800CDA90( work );
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->arrived == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->arrived )
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

    if ( work->object_alive == NULL )
    {
        work->field_8EC = 10;
        work->flags2 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->action = s07b_800CEA18;
        work->time = 0;
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
        if ( work->object_alive == NULL && !( work->flags2 & 0x2000 ) )
        {
            s07b_800CAD54( work, 0x81 );
            NewPsychoChair();
            NewPsychoPicture( 1 );
            NewPsychoBook( 1 );
            work->object_alive = &chair_alive;
        }
        work->arrived = 0;
        work->flags2 &= ~1;
        s07b_800CB6B0( work, -500, -1250, 96 );
        s07b_800CDA90( work );
    }

    s07b_800CB224( work );

    if ( work->field_A64 == 0 && work->arrived == 0 )
    {
        s07b_800CB8CC( work );
        if ( work->arrived )
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

    if ( work->object_alive == NULL )
    {
        work->field_8EC = 9;
        work->flags2 &= ~0x2000;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->action = s07b_800CE85C;
        work->time = 0;
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
        work->flags2 &= ~1;
    }

    if ( time == 23 )
    {
        s07b_800CAD54( work, 0x82 );
    }

    if ( work->body.is_end )
    {
        work->field_8EC++;
        switch ( work->state )
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
        work->action = mode;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800CC174( Work *work, int arg1 );

void s07b_800CED04( Work *work, int time )
{
    int action;
    int state;
    int wait;

    if ( time == 0 )
    {
        if ( GV_Time & 1 )
        {
            action = 16;
        }
        else
        {
            action = 17;
        }
        if ( work->body.action != action )
        {
            GM_ConfigObjectAction( &work->body, action, 0, 4 );
        }
        work->flags2 &= ~1;
        s07b_800CCA10( work );
        s07b_800CC9E8( work, 0 );
        s07b_800CAD54( work, 141 );
        GM_GameStatus |= STATE_MENU_DISABLE | STATE_RADIO_OFF;
    }

    s07b_800CB224( work );

    state = work->field_A64;
    switch ( state )
    {
    case 0:
        if ( work->body.is_end )
        {
            if ( work->body.action != 1 )
            {
                GM_ConfigObjectAction( &work->body, 1, 0, 4 );
            }
            s07b_800CB9E8( work, 160 );
            work->field_A60 = 1;
            work->field_A64 = 1;
            GM_AlertMode = 10;
            work->control.mov.vx = work->point.vx;
            work->control.mov.vz = work->point.vz;
            GM_GameStatus |= STATE_PADRELEASE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF;
            GV_PauseLevel |= 4;
            GM_SetSound( SNG_FOUTP_SS, SD_ASYNC );
            work->flags2 |= 0x80;
            if ( work->field_834 )
            {
                GV_DestroyOtherActor( work->field_834 );
            }
            work->field_834 = NULL;
            GM_GameStatus &= ~STATE_NOSLOW;
        }
        break;
    case 1:
        GM_PlayerStatus |= PLAYER_NOT_SIGHT;
        s07b_800CC174( work, work->field_A66 );
        if ( work->picture_count == 0 )
        {
            wait = 256;
        }
        else
        {
            wait = 128;
        }
        if ( work->field_A66 == 0 )
        {
            s07b_800CC6CC();
        }
        if ( ++work->field_A66 == wait )
        {
            s07b_800CCA10( work );
            GM_AlertMode = 0;
            work->field_A60 = 0;
            work->field_A5C = 6;
            work->field_8EC = state;
            work->picture_count++;
            s07b_800CBD4C( work );
            work->flags2 |= 1;
            GM_GameStatus &= ~(STATE_PADRELEASE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF);
            GV_PauseLevel &= ~4;
            work->body.objs->flag |= DG_FLAG_INVISIBLE;
            work->action = s07b_800CF130;
            work->time = 0;
            work->field_A66 = 0;
            work->field_A64 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_SetSound( SNG_FIN_S, SD_ASYNC );
            work->flags2 &= ~0x80;
            GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
        }
        break;
    }
}
void s07b_800CEFF0( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        s07b_800CBD4C( work );
        work->flags2 |= 1;
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
        GM_SeSetMode( &work->control.mov, 0xB3, GM_SEMODE_BOMB );
        DG_InvisibleObjs( work->body.objs );
        s07b_800CB9E8( work, 160 );
        work->action = s07b_800CDCAC;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->flags2 |= 0x200;
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
        work->flags2 |= 1;
        if ( work->state == 2 )
        {
            s07b_800CAD54( work, 0x80 );
        }
        s07b_800CC89C( work, 3 );
    }
    s07b_800CC8D4( work );
    s07b_800CB224( work );
    if ( time == *(u_short *)&s07b_dword_800C33A8 )
    {
        work->action = s07b_800CF200;
        work->time = 0;
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
        work->flags2 &= ~1;
        s07b_800CBCE8( work );
        if ( !( work->flags & 1 ) )
        {
            work->field_864 = 1;
        }
        work->action = s07b_800CEBAC;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
extern int dword_800BDD28;
extern int dword_8009F444;
extern int dword_8009F434;
extern int dword_8009F49C;
extern int dword_8009F480;
void *NewFadeInOut( int mode, int shade );

void s07b_800CF304( Work *work, int time )
{
    SVECTOR diff;
    SVECTOR ofs;
    SVECTOR from;
    SVECTOR to;
    int     len;

    if ( time == 0 )
    {
        s07b_800CC6CC();
        GM_SetSound( SNG_FOUTP_SS, SD_ASYNC );
        dword_800BDD28 = 0;
        dword_8009F444 = 0;
        dword_8009F434 = 0;
        dword_8009F49C = 0;
        dword_8009F480 = 0;
        work->flags |= 0x10;
        GM_GameStatus |= STATE_PADRELEASE | STATE_MENU_DISABLE | STATE_LIFE_OFF;
        GM_PlayerStatus |= PLAYER_NOT_SIGHT;
        work->flags2 &= ~8;
        s07b_800CC9E8( work, 0 );
        s07b_800CBCE8( work );
        s07b_800CB068( 0 );
        s07b_800CB0B4( work, 0 );
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        if ( work->body.action != 22 )
        {
            GM_ConfigObjectAction( &work->body, 22, 0, 4 );
        }
        s07b_800CAD54( work, 137 );

        from = work->control.mov;
        from.vy = 1500;
        to = GM_PlayerPosition;
        to.vy = 1500;
        GV_SubVec3( &from, &to, &diff );
        len = GV_VecLen3( &diff );
        GV_LenVec3( &diff, &ofs, len, 1500 );
        GV_SubVec3( &from, &ofs, &work->head_pos );
        work->control.step = DG_ZeroVector;
    }

    if ( work->body.height < 1000 )
    {
        work->height_level = 1;
    }
    if ( work->body.height < 500 )
    {
        work->height_level = 2;
    }

    if ( time == 33 || time == 43 || time == 55 )
    {
        GM_SeSetMode( &work->control.mov, SE_DOWN0002, GM_SEMODE_BOMB );
    }

    GM_Camera.first_person = 1;
    GM_SnakeCamera.position = work->head_pos;
    GV_SubVec3( &work->control.mov, &GM_PlayerPosition, &diff );
    GM_PlayerControl->turn.vy = GV_VecDir2( &diff );
    GM_PlayerBody->objs->flag |= DG_FLAG_INVISIBLE;

    if ( work->field_A64 == 0 )
    {
        if ( work->body.is_end )
        {
            if ( work->body.action != 23 )
            {
                GM_ConfigObjectAction( &work->body, 23, 0, 4 );
            }
            work->field_A64++;
        }
    }
    else
    {
        if ( work->field_A64 == 32 )
        {
            NewFadeInOut( 0, 48 );
        }
        if ( ++work->field_A64 == 96 )
        {
            work->next_state = -1;
            work->flags2 |= 0x10;
            s07b_800CC138( work, -1 );
            GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
        }
    }
}

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
        work->height_level = 0;
    }
}

void s07b_800CF6F0( Work *work, int time )
{
    if ( time == 0 )
    {
        GM_GameStatus |= STATE_PADRELEASE;
    }

    if ( time == 48 && GM_Vitality != 0 && GM_GameOverTimer == 0 )
    {
        work->flags &= ~0x10;
        s07b_800CC138( work, -1 );
    }
}
void s07b_800CF768( Work *work, int time )
{
    SVECTOR diff;

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
        s07b_800CC930();
        work->height_level = 0;
        OpenCinemaScreen( 1, 30000 );
        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        GM_VoxQueue( work->field_ABC[ 3 ] );
        s07b_800CBCE8( work );
        s07b_800CB068( 0 );
        s07b_800CB0B4( work, 0 );
        work->flags2 &= ~1;
        s07b_800CB224( work );
        s07b_800CC9E8( work, 0 );
        work->arrived = 0;
    }

    DG_VisibleObjs( work->body.objs );

    if ( !( GM_PlayerStatus & PLAYER_DOWNED ) )
    {
        GV_SubVec3( &work->control.mov, &GM_PlayerPosition, &diff );
        GM_PlayerControl->turn.vy = GV_VecDir2( &diff );
    }

    switch ( work->field_A64 )
    {
    case 0:
        GM_SnakeCamera.position = work->control.mov;
        GM_SnakeCamera.track = 3200;
        if ( GM_VoxEnd() )
        {
            work->field_A64++;
        }
        break;
    case 1:
        s07b_800CBC20( work );
        work->action = s07b_800CDCAC;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        break;
    }
}
void s07b_800CF9A0( Work *work, int time )
{
    SVECTOR from;
    SVECTOR to;
    int     action;

    if ( time == 0 )
    {
        GM_SeSetMode( &work->control.mov, 129, GM_SEMODE_BOMB );
        action = work->body.action;
        if ( action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        action = 19;
        if ( work->body.action2 != action )
        {
            GM_ConfigObjectOverride( &work->body, action, 0, 4, 0x3FE );
        }
        s07b_800CC138( work, 7 );
    }

    switch ( work->field_A64 )
    {
    case 0:
        GM_PlayerBody->objs->flag |= DG_FLAG_INVISIBLE;
        GM_PlayerStatus |= PLAYER_NOT_SIGHT;
        from = work->control.mov;
        to.vx = GM_PlayerBody->objs->objs[ 6 ].world.t[ 0 ];
        to.vy = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
        to.vz = GM_PlayerBody->objs->objs[ 6 ].world.t[ 2 ];
        s07b_800CC578( &from, &to, 4000, &work->control.turn.vy, &GM_PlayerControl->turn.vy );
        if ( ++work->field_A66 == 120 )
        {
            CloseCinemaScreen();
            GM_Camera.first_person = 0;
            GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY);
            if ( work->body.action2 )
            {
                GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
            }
            work->field_A64++;
            work->field_A66 = 0;
        }
        break;
    case 1:
        if ( ++work->field_A66 == 6 )
        {
            GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
            GM_PlayerBody->objs->flag &= ~DG_FLAG_INVISIBLE;
            GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY);
            GM_GameStatus |= STATE_RADAR_OFF;
            s07b_800CCA10( work );
            work->next_state = 4;
            work->flags2 |= 0x10;
            work->flags &= ~0x10;
        }
        break;
    }
}
int GM_StreamStatus( void );

static inline int s07b_VecDist( SVECTOR *a, SVECTOR *b, SVECTOR *diff )
{
    GV_SubVec3( a, b, diff );
    return GV_VecLen3( diff );
}

void s07b_800CFBF8( Work *work, int time )
{
    MATRIX  mat;
    SVECTOR from;
    SVECTOR to;
    SVECTOR ofs;
    SVECTOR vec[ 3 ];
    int     i;
    int     meryl_zone;
    int     snake_zone;

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
        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
        GM_PlayerStatus |= PLAYER_NOT_SIGHT;
        s07b_800CCA10( work );
        s07b_800CC9E8( work, 0 );
        if ( work->body.action2 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        work->control.step = DG_ZeroVector;
        s07b_800CB068( 0 );
        s07b_800CB0B4( work, 0 );
        OpenCinemaScreen( 1, 30000 );
        s07b_800CC930();

        vec[ 1 ] = GM_PlayerPosition;
        vec[ 1 ].vy = 0;
        vec[ 2 ] = s07b_dword_800E5BB8;
        vec[ 2 ].vy = 0;
        if ( s07b_VecDist( &vec[ 1 ], &vec[ 2 ], &vec[ 0 ] ) < 2501 )
        {
            meryl_zone = 0;
            if ( s07b_dword_800E5BB8.vx < -5500 )
            {
                meryl_zone = 1;
            }
            else if ( s07b_dword_800E5BB8.vx > 4000 )
            {
                meryl_zone = 2;
            }
            else if ( s07b_dword_800E5BB8.vz < -3250 )
            {
                meryl_zone = 3;
            }
            else if ( s07b_dword_800E5BB8.vz > 3250 )
            {
                meryl_zone = 4;
            }

            snake_zone = 0;
            if ( GM_PlayerPosition.vx < -5500 )
            {
                snake_zone = 1;
            }
            else if ( GM_PlayerPosition.vx > 4000 )
            {
                snake_zone = 2;
            }
            else if ( GM_PlayerPosition.vz < -3250 )
            {
                snake_zone = 3;
            }
            else if ( GM_PlayerPosition.vz > 3250 )
            {
                snake_zone = 4;
            }

            if ( meryl_zone == snake_zone && meryl_zone != 0 )
            {
                work->flags2 |= 0x800;
            }
        }
    }

    if ( time < 64 )
    {
        return;
    }

    if ( time == 64 )
    {
        s07b_800CC514( 0, 2 );
        work->flags2 &= ~0x20;
    }

    sna_act_helper2_helper2_80033054( GV_StrCode( s07b_dword_800E5020 ), &work->adjust[ 6 ] );
    if ( GM_VoxCodeEnd( work->field_ABC[ 0 ] ) )
    {
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
    }

    switch ( work->field_A64 )
    {
    case 0:
        if ( work->field_A66 == 0 )
        {
            if ( work->body.action != 0 )
            {
                GM_ConfigObjectAction( &work->body, 0, 0, 4 );
            }
            GM_VoxQueue( work->field_ABC[ 0 ] );
            work->field_A66 = 1;
        }
        else if ( GM_StreamStatus() == 2 )
        {
            GM_ConfigMotionAdjust( &work->body, work->adjust );
            s07b_800CC138( work, 5 );
            work->field_A64 = 1;
            work->field_A66 = 0;
            work->head_pos.vx = work->body.objs->objs[ 6 ].world.t[ 0 ];
            work->head_pos.vy = work->body.objs->objs[ 6 ].world.t[ 1 ];
            work->head_pos.vz = work->body.objs->objs[ 6 ].world.t[ 2 ];
            work->player_head_pos.vx = GM_PlayerBody->objs->objs[ 6 ].world.t[ 0 ];
            work->player_head_pos.vy = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
            work->player_head_pos.vz = GM_PlayerBody->objs->objs[ 6 ].world.t[ 2 ];
        }
        break;

    case 1:
        if ( !( work->flags2 & 0x800 ) )
        {
            s07b_800CC578( &work->head_pos, &work->player_head_pos, 2000, &work->control.turn.vy, &GM_PlayerControl->turn.vy );
            GM_SnakeCamera.rotate2.vx = -160;
            GM_SnakeCamera.position.vy -= 750;
        }
        else
        {
            GM_Camera.first_person = 1;
            s07b_800CC970( &DG_ZeroVector, &work->control.mov, 2000 );
            GM_SnakeCamera.position.vy = 1500;
            GM_SnakeCamera.rotate2.vy = GV_VecDir2( &work->control.mov );
        }
        s07b_800CC790( work, 1 );
        if ( ++work->field_A66 == 194 )
        {
            if ( work->body.action != 19 )
            {
                GM_ConfigObjectAction( &work->body, 19, 0, 4 );
            }
        }
        if ( work->field_A66 >= 195 )
        {
            s07b_800CB264( work );
        }
        if ( work->field_A66 == 245 )
        {
            work->field_A64 = 2;
        }
        break;

    case 2:
        if ( !( work->flags2 & 0x800 ) )
        {
            from = s07b_dword_800E5BB8;
            to.vx = GM_PlayerBody->objs->objs[ 6 ].world.t[ 0 ];
            to.vy = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
            to.vz = GM_PlayerBody->objs->objs[ 6 ].world.t[ 2 ];
            ofs.vz = ofs.vy = 0;
            ofs.vx = 2000;
            ReadRotMatrix( &mat );
            DG_SetPos2( &to, &GM_PlayerControl->rot );
            DG_RotVector( &ofs, &ofs, 1 );
            GV_AddVec3( &to, &ofs, &to );
            DG_SetPos( &mat );
            s07b_800CC578( &from, &to, 2000, NULL, NULL );
            GM_SnakeCamera.rotate2.vx = 300;
            GM_SnakeCamera.position.vy += 750;
        }
        else
        {
            GM_Camera.first_person = 1;
            s07b_800CC970( &DG_ZeroVector, &s07b_dword_800E5BB8, 1000 );
            GM_SnakeCamera.position.vy = 1500;
            GM_SnakeCamera.rotate2.vx = 720;
            GM_SnakeCamera.rotate2.vy = GV_VecDir2( &s07b_dword_800E5BB8 );
        }
        s07b_800CC790( work, 0 );
        s07b_800CC790( work, 1 );
        if ( ++work->field_A66 == 294 )
        {
            *s07b_dword_800E5BB0 |= 0x200;
        }
        if ( work->field_A66 == 354 )
        {
            work->head_pos = s07b_dword_800E5BB8;
            work->field_A64 = 3;
        }
        break;

    case 3:
    case 4:
        if ( !( work->flags2 & 0x800 ) )
        {
            from = work->head_pos;
            to.vx = GM_PlayerBody->objs->objs[ 6 ].world.t[ 0 ];
            to.vy = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
            to.vz = GM_PlayerBody->objs->objs[ 6 ].world.t[ 2 ];
            ofs.vx = 2000;
            ofs.vy = 0;
            ofs.vz = 300;
            ReadRotMatrix( &mat );
            DG_SetPos2( &to, &GM_PlayerControl->rot );
            DG_RotVector( &ofs, &ofs, 1 );
            GV_AddVec3( &to, &ofs, &to );
            DG_SetPos( &mat );
            s07b_800CC578( &from, &to, 1000, NULL, NULL );
            GM_SnakeCamera.rotate2.vx = -420;
            GM_SnakeCamera.position.vy -= 300;
        }
        else
        {
            GM_Camera.first_person = 1;
            s07b_800CC970( &DG_ZeroVector, &s07b_dword_800E5BB8, 750 );
            GM_SnakeCamera.position.vy = 1500;
            GM_SnakeCamera.rotate2.vy = GV_VecDir2( &s07b_dword_800E5BB8 );
        }
        s07b_800CC790( work, 0 );
        s07b_800CC790( work, 1 );
        if ( work->field_A64 == 3 )
        {
            if ( !( *s07b_dword_800E5BB0 & 0x200 ) )
            {
                GM_VoxQueue( work->field_ABC[ 1 ] );
                work->field_A64 = 4;
                work->field_A66 = 0;
            }
        }
        else if ( ++work->field_A66 == 58 )
        {
            work->field_A64 = 5;
            work->field_A66 = 0;
        }
        break;

    case 5:
        if ( !( work->flags2 & 0x800 ) )
        {
            *s07b_dword_800E5BB0 |= 0x2000;
            from.vx = GM_PlayerBody->objs->objs[ 6 ].world.t[ 0 ];
            from.vy = GM_PlayerBody->objs->objs[ 6 ].world.t[ 1 ];
            from.vz = GM_PlayerBody->objs->objs[ 6 ].world.t[ 2 ];
            ofs.vx = ofs.vy = 0;
            ofs.vz = 1000;
            ReadRotMatrix( &mat );
            DG_SetPos2( &from, &GM_PlayerControl->rot );
            DG_RotVector( &ofs, &to, 1 );
            GV_AddVec3( &from, &to, &to );
            DG_SetPos( &mat );
            s07b_800CC970( &DG_ZeroVector, &s07b_dword_800E5BB8, 1500 );
            s07b_800CC578( &from, &to, 1500, &GM_PlayerControl->turn.vy, NULL );
        }
        else
        {
            GM_Camera.first_person = 1;
            s07b_800CC970( &DG_ZeroVector, &GM_PlayerPosition, 750 );
            GM_SnakeCamera.position.vy = 1500;
            GM_SnakeCamera.rotate2.vy = GV_VecDir2( &GM_PlayerPosition );
        }
        s07b_800CC790( work, 0 );
        GM_PlayerBody->objs->flag &= ~DG_FLAG_INVISIBLE;
        if ( GM_VoxCodeEnd( work->field_ABC[ 1 ] ) )
        {
            s07b_800CCA10( work );
            work->next_state = 6;
            work->flags2 |= 0x30;
            GCL_ExecProc( work->field_ACC[ 4 ], NULL );
            *s07b_dword_800E5BB0 |= 0x400;
            GM_GameStatus = ( GM_GameStatus & ~(STATE_PADRELEASE | STATE_PAUSE_ONLY) ) | STATE_RADAR_OFF;
            CloseCinemaScreen();
            GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
            work->flags &= ~0x10;
            GM_Camera.first_person = 0;
        }
        break;
    }
}
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
        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
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
        work->flags2 &= ~0x20;
        OpenCinemaScreen( 1, 30000 );
        work->control.step = DG_ZeroVector;
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        s07b_800CB068( 0 );
        s07b_800CB0B4( work, 0 );
        GM_VoxQueue( work->field_ABC[ 2 ] );
        s07b_800CC930();
    }

    GM_SnakeCamera.position = work->control.mov;
    GM_SnakeCamera.track = 3200;

    if ( GM_VoxEnd() )
    {
        GM_GameStatus = ( GM_GameStatus & ~(STATE_PADRELEASE | STATE_PAUSE_ONLY) ) | STATE_RADAR_OFF;
        s07b_800CCA10( work );
        CloseCinemaScreen();
        work->next_state = 8;
        work->flags2 |= 0x20;
        work->flags &= ~0x10;
        work->flags2 |= 0x10;
    }
}
void s07b_800D098C( Work *work, int time )
{
    if ( time == 0 )
    {
        work->action = s07b_800CDBA4;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CC89C( work, 1 );
    }

    s07b_800CB2A4( work );

    if ( ( *s07b_dword_800E5BB0 & 0x1008 ) == 0x1000 && GM_GameOverTimer == 0 )
    {
        work->next_state = 1;
        work->action = s07b_800CF6F0;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->flags |= 0x10;
        work->flags2 |= 0x10;
    }
}
void s07b_800CB2A4( Work *work );

void s07b_800D0A4C( Work *work, int time )
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
        work->action = s07b_800CED04;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    s07b_800CB2A4( work );
    s07b_800CCBFC( work );

    if ( work->target->vital <= ( (u_short *)&s07b_dword_800C3390 )[ 1 ] )
    {
        GM_GameStatus |= STATE_PADRELEASE;
        if ( !( work->flags & 4 ) )
        {
            work->next_state = 3;
            work->flags2 |= 0x10;
            s07b_800CC6CC();
            work->action = s07b_800CF768;
            work->time = 0;
            work->field_A66 = 0;
            work->field_A64 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->flags |= 0x10;
        }
    }
}

void s07b_800D0B40( Work *work, int time )
{
    /* do nothing */
}

void s07b_800CFBF8( Work *work, int time );

void s07b_800D0B48( Work *work, int time )
{
    int *flags;

    if ( time == 0 )
    {
        s07b_800CC138( work, 4 );
        work->action = s07b_800CDBA4;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CC89C( work, 1 );
    }

    s07b_800CCBFC( work );
    s07b_800CB2A4( work );

    flags = s07b_dword_800E5BB0;
    if ( ( *flags & 0x1000 ) || work->target->vital <= *(u_short *)&s07b_dword_800C3394 )
    {
        GM_GameStatus |= STATE_PADRELEASE;
        if ( work->flags & 4 )
        {
            return;
        }

        if ( !( *flags & 0x800 ) )
        {
            s07b_800CC138( work, 8 );
        }

        if ( work->target->vital < *(u_short *)&s07b_dword_800C3394 )
        {
            work->target->vital = *(u_short *)&s07b_dword_800C3394;
        }

        work->next_state = 5;
        work->action = s07b_800CFBF8;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->flags |= 0x10;
        work->flags2 |= 0x10;
    }
}

void s07b_800D0C8C( Work *work, int time )
{
    /* do nothing */
}


void s07b_800D0774( Work *work, int time );

void s07b_800D0C94( Work *work, int time )
{
    if ( time == 0 )
    {
        work->action = s07b_800CDBA4;
        work->time = 0;
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
        GM_GameStatus |= STATE_PADRELEASE;
        if ( !( work->flags & 4 ) )
        {
            if ( !( *s07b_dword_800E5BB0 & 0x800 ) )
            {
                s07b_800CC138( work, 8 );
            }
            if ( work->target->vital < ( (u_short *)&s07b_dword_800C3394 )[ 1 ] )
            {
                work->target->vital = ( (u_short *)&s07b_dword_800C3394 )[ 1 ];
            }
            work->next_state = 7;
            work->action = s07b_800D0774;
            work->time = 0;
            work->field_A66 = 0;
            work->field_A64 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->flags |= 0x10;
            work->flags2 |= 0x10;
        }
    }
}

void s07b_800D0DCC( Work *work, int time )
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
            work->lifebar_rest = data[ 3 ];
        }
        work->action = s07b_800CEFF0;
        work->time = 0;
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

    if ( work->target->vital <= *(u_short *)&s07b_dword_800C3398 && !( work->flags & 4 ) )
    {
        work->next_state = 9;
        work->flags2 |= 0x10;
        s07b_800CBCE8( work );
        if ( !( work->flags & 1 ) )
        {
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
            work->field_864 = 1;
        }
        s07b_800CB6B0( work, -500, -1250, 160 );
        s07b_800CCA10( work );
        work->action = s07b_800CDCAC;
        work->time = 0;
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

void s07b_800D0F94( Work *work, int time )
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
        work->flags &= ~0x4;
        DG_VisibleObjs( GM_PlayerBody->objs );
        work->action = s07b_800CF684;
        work->time = 0;
        work->field_A66 = 0;
        work->field_A64 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800CB0B4( work, 0 );
        s07b_800CB068( 0 );
    }
}

void s07b_800D105C( Work *work )
{
    void ( *mode )( Work *, int );
    int time;

    s07b_800CAFC8( work );
    s07b_800CC50C( work );

    time = work->field_848;
    if ( time < 160000 )
    {
        work->field_848 = time + 1;
    }

    switch ( work->state )
    {
    case 0:
        s07b_800D098C( work, time );
        break;
    case 1:
        s07b_800D0A4C( work, time );
        break;
    case 2:
        s07b_800D0A6C( work, time );
        break;
    case 3:
        s07b_800D0B40( work, time );
        break;
    case 4:
        s07b_800D0B48( work, time );
        break;
    case 5:
        s07b_800D0C8C( work, time );
        break;
    case 6:
        s07b_800D0C94( work, time );
        break;
    case 7:
        s07b_800D0DCC( work, time );
        break;
    case 8:
        s07b_800D0DD4( work, time );
        break;
    case 9:
        s07b_800D0F94( work, time );
        break;
    case 10:
    game_over:
        s07b_800D0FC0( work, time );
        break;
    }

    if ( GM_GameOverTimer != 0 || GM_Vitality == 0 || ( *s07b_dword_800E5BB0 & 8 ) )
    {
        if ( work->state != 10 )
        {
            time = 0;
            work->state = 10;
            work->field_848 = 1;
            goto game_over;
        }
    }

    s07b_800CC67C( work );
    s07b_800CBDA0( work );
    s07b_800CC468( work );

    if ( work->flags & 4 )
    {
        time = work->time2;
        mode = work->action2;
        if ( time < 16000 )
        {
            work->time2 = time + 1;
        }
    }
    else
    {
        time = work->time;
        mode = work->action;
        if ( time < 16000 )
        {
            work->time = time + 1;
        }
    }

    mode( work, time );
    s07b_800CC704( work );
    s07b_800CBFB0( work );
}

const char s07b_dword_800E5070[] = "メリル";
const char s07b_dword_800E5078[] = "hideo_b";
const char s07b_dword_800E5080[] = "hideo_s";
const char s07b_dword_800E5088[] = "hideo";


void s07b_800D105C( Work *work );
void s07b_800CD86C( Work *work );

void s07b_800D1254( Work *work )
{
    int      mask;
    TARGET  *target;
    TARGET  *target2;

    mask = ( (u_char)work->flags2 >> 7 ) ? 0 : 6;
    if ( GV_PauseLevel & mask )
    {
        return;
    }

    if ( GM_PlayerStatus & PLAYER_SECOND_CONTROLLER )
    {
        work->pad1 = &GV_PadData[ 1 ];
    }
    else
    {
        work->pad1 = &GV_PadData[ 0 ];
    }

    GM_ActMotion( &work->body );
    work->control.hzd_height = work->control.levels[ 0 ] + s07b_dword_800C33F4[ work->height_level ];
    GM_ActControl( &work->control );
    s07b_800CAE00( work );
    GM_ActObject( &work->body );
    DG_GetLightMatrix2( &work->control.mov, work->light );
    GM_MoveTarget( work->target, &work->control.mov );

    // The loop notes of this do/while keep the height store before the target load (gcc sched barrier)
    do {
        work->control.height = work->body.height;
    } while ( 0 );

    target = work->target;
    work->control.turn.vz = 0;
    s07b_dword_800C33F0 = target->vital;
    s07b_800D105C( work );

    target2 = work->target;
    target2->force = work->control.step;
    GM_PushTarget( target2 );
    s07b_800CD86C( work );
    s07b_dword_800E5BE0 = work->control.mov;
}

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

    GM_SetTarget( target, TARGET_FLAG, ENEMY_SIDE, (SVECTOR *)&s07b_dword_800C3400 );
    GM_SetPowerTarget( target, POWER_DECREASE, -1, *(u_short *)&s07b_dword_800C3390, 0, &DG_ZeroVector );
    hom = GM_SetHomingTarget( &work->body.objs->objs[ 6 ].world, &work->control );
    work->hom = hom;
    hom->flag = 1;
    s07b_dword_800C33F0 = target->vital;
    return 0;
}
int s07b_800D1484( Work *work );

extern int *s07b_dword_800E5BD8;

void s07b_800D1638( Work *work )
{
    int     i;
    u_char *lock;

    s07b_dword_800E5BD8 = &work->flags;
    work->flags = 0;
    work->flags2 = 0;
    work->point = DG_ZeroVector;
    work->field_880 = DG_ZeroVector;
    work->field_878 = DG_ZeroVector;
    work->pos = work->control.mov;
    work->rot = work->control.rot;
    work->field_A60 = 0;
    work->blink_timer = 0;
    work->class_timer = 0;
    work->field_A66 = 0;
    work->field_A64 = 0;
    work->throw_side = 0;
    work->chair_step = 0;
    work->head_pos = DG_ZeroVector;
    work->pad1 = &GV_PadData[ 0 ];
    work->pad2 = &GV_PadData[ 1 ];
    work->sepia = NULL;
    work->field_834 = NULL;

    if ( GCL_GetOption( 'm' ) )
    {
        work->state = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->state = 0;
    }

    work->field_848 = 0;
    work->next_state = -1;

    if ( GCL_GetOption( 'n' ) )
    {
        work->meryl_name = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->meryl_name = GV_StrCode( s07b_dword_800E5070 );
    }

    work->kogaku_state = -1;

    if ( GCL_GetOption( 'k' ) && GCL_StrToInt( GCL_NextStr() ) )
    {
        s07b_800CBD4C( work );
    }

    if ( GCL_GetOption( 'g' ) && GCL_StrToInt( GCL_NextStr() ) )
    {
        work->flags2 |= 0x20;
    }

    i = 7;
    lock = (u_char *)work + i;
    for ( ; i >= 0; i-- )
    {
        lock[ 0xA88 ] = 0;
        lock--;
    }

    work->height_level = 0;
    work->control.hzd_height = s07b_dword_800C33F4[ 0 ];
    work->object_alive = NULL;
}
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

void s07b_800D195C( Work *work )
{
    DG_TEX   *tex_b;
    DG_TEX   *tex_s;
    int       i;
    POLY_FT4 *poly;
    POLY_F4  *tile;

    tex_b = DG_GetTexture( GV_StrCode( s07b_dword_800E5078 ) );
    tex_s = DG_GetTexture( GV_StrCode( s07b_dword_800E5080 ) );
    work->hideo_tex = DG_GetTexture( GV_StrCode( s07b_dword_800E5088 ) );

    for ( i = 0; i < 2; i++ )
    {
        poly = &work->hideo[ i ];
        setPolyFT4( poly );
        poly->r0 = poly->g0 = poly->b0 = 128;
        poly->x0 = poly->x2 = 224;
        poly->x1 = poly->x3 = 296;
        poly->y0 = poly->y1 = 8;
        poly->y2 = poly->y3 = 40;
        DG_SetPacketTexture( poly, work->hideo_tex );
        poly->tpage = work->hideo_tex->tpage;
        poly->clut = work->hideo_tex->clut;

        poly = &work->hideo_b[ i ];
        setPolyFT4( poly );
        poly->r0 = poly->g0 = poly->b0 = 128;
        poly->x0 = poly->x2 = 192;
        poly->x1 = poly->x3 = 312;
        poly->y0 = poly->y1 = 8;
        poly->y2 = poly->y3 = 36;
        DG_SetPacketTexture4( poly, tex_b );

        poly = &work->hideo_s[ i ];
        setPolyFT4( poly );
        poly->r0 = poly->g0 = poly->b0 = 128;
        poly->x0 = poly->x2 = 252;
        poly->x1 = poly->x3 = 312;
        poly->y0 = poly->y1 = 8;
        poly->y2 = poly->y3 = 22;
        DG_SetPacketTexture4( poly, tex_s );

        tile = &work->black_screen[ i ];
        setPolyF4( tile );
        tile->r0 = tile->g0 = tile->b0 = 0;
        tile->x0 = tile->x2 = 0;
        tile->x1 = tile->x3 = 320;
        tile->y0 = tile->y1 = 0;
        tile->y2 = tile->y3 = 224;

        tile = &work->white_screen[ i ];
        tile->r0 = tile->g0 = tile->b0 = 255;
        setPolyF4( tile );
        tile->x0 = tile->x2 = 0;
        tile->x1 = tile->x3 = 320;
        tile->y0 = tile->y1 = 0;
        tile->y2 = tile->y3 = 224;
    }

    work->picture_count = 0;
    work->field_A5C = 0;
}
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
