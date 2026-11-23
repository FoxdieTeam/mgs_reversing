#include "game/game.h"
#include "game/vibrate.h"
#include "game/navi.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    /* 0x00 */ GV_ACT actor;
    /* 0x20 */ CONTROL control;
    /* 0x9C */ OBJECT  body;
    /* 0x180 */ char  pad180[ 0x598 ];
    /* 0x718 */ SVECTOR adjust[ 16 ];
    /* 0x798 */ char  pad798[ 0x44 ];
    /* 0x7DC */ TARGET *target;
    /* 0x7E0 */ char  pad7E0[ 0x4C ];
    /* 0x82C */ int   field_82C;
    /* 0x830 */ void *weapon;             // NewDesertEagle (s07b_800CA2EC)
    /* 0x834 */ u_long trigger;           // weapon trigger flags
    /* 0x838 */ short field_838;
    /* 0x83A */ short field_83A;
    /* 0x83C */ void *sepia;              // sepia screen effect (NewSepia_800C5214), s07b_800C4A18
    /* 0x840 */ u_short field_840;        // 2 or 3: s07b_800C50D8 sends "go_motion"
    /* 0x842 */ char  pad842[ 0x2 ];
    /* 0x844 */ short field_844;
    /* 0x846 */ short field_846;          // < 0: run proc_id on message 0x100 (s07b_800C500C)
    /* 0x848 */ int   field_848;
    /* 0x84C */ int   field_84C;          // flags (bit 1 cleared when field_8C2 runs out)
    /* 0x850 */ int   field_850;          // flags (0x20000 set by s07b_800C473C)
    /* 0x854 */ void  ( *field_854 )( struct _Work *, int );   // current mode function (s07b_800C9B24)
    /* 0x858 */ char  pad858[ 0x8 ];
    /* 0x860 */ int   field_860;
    /* 0x864 */ SVECTOR field_864;        // knock-back velocity, decays to zero (s07b_800C627C)
    /* 0x86C */ short field_86C;          // fade counter: > 0 counts down (flag 0x80 off), < 0 counts up (on), s07b_800C4A94
    /* 0x86E */ short field_86E;          // set to 1 when control.height < 500 (s07b_800C6538)
    /* 0x870 */ SVECTOR field_870;        // direction for control.turn.vy (s07b_800C5CFC)
    /* 0x878 */ int   field_878;          // < 2001: s07b_800C7E98 switches to s07b_800C7D88
    /* 0x87C */ NAVIGATE navi;
    /* 0x89C */ MENU_BAR_CONF lifebar;
    /* 0x8A8 */ int   lifebar_rest;       // shown life, drops towards target->vital (s07b_800C7604)
    /* 0x8AC */ int   lifebar_xpos;       // script option h (default 16)
    /* 0x8B0 */ int   lifebar_ypos;
    /* 0x8B4 */ u_short field_8B4[ 5 ];   // HZD zone names, script option 't' (s07b_800CA4FC)
    /* 0x8BE */ short field_8BE;
    /* 0x8C0 */ short field_8C0;
    /* 0x8C2 */ short field_8C2;          // countdown timer, see s07b_800C5514
    /* 0x8C4 */ short field_8C4;
    /* 0x8C6 */ short field_8C6;
    /* 0x8C8 */ short field_8C8;
    /* 0x8CA */ char  pad8CA[ 0x2 ];
    /* 0x8CC */ short field_8CC;          // set to 1 when the navi target is reached (s07b_800C7AA8)
    /* 0x8CE */ char  pad8CE[ 0x2 ];
    /* 0x8D0 */ int   field_8D0;          // voice code playing (field_8E4[ 18 ]), see s07b_800C796C
    /* 0x8D4 */ SVECTOR field_8D4;        // navi target (s07b_800C7AA8)
    /* 0x8DC */ u_short *field_8DC;       // bit 0x4000 tested in s07b_800C473C
    /* 0x8E0 */ int   proc_id;
    /* 0x8E4 */ int   field_8E4[ 19 ];    // script option 'c' (s07b_800CA584)
    /* 0x930 */ int   field_930[ 11 ];    // script option 'r' (s07b_800CA5FC)
    /* 0x95C */ int   field_95C[ 8 ];     // script option 'f' (s07b_800CA674)
} Work;

void sna_act_helper2_helper2_80033054( int id, SVECTOR *vec );

int s07b_dword_800C32F8 = 0x000001C0;
int s07b_dword_800C32FC = 0x000002EE;
int s07b_dword_800C3300 = 0x000000FA;
int s07b_dword_800C3304 = 0x000004FF;
int s07b_dword_800C3308 = 0x00000000;
int s07b_dword_800C330C = 0x00000064;
int s07b_dword_800C3310 = 0x0000FC00;
int s07b_dword_800C3314 = 0x00000000;
int s07b_dword_800C3318 = 0xFE8E0014;
int s07b_dword_800C331C = 0x0000003C;
int s07b_dword_800C3320 = 0x00000000;
int s07b_dword_800C3324 = 0x0000012C;
int s07b_dword_800C3328 = 0x0258012C;
int s07b_dword_800C332C = 0x0000012C;

const char s07b_dword_800E4B4C[] = "スネーク";
const char s07b_dword_800E4B58[] = "go_motion";
const char s07b_dword_800E4B64[] = "stance";
const char s07b_dword_800E4B6C[] = "run_move";
const char s07b_dword_800E4B78[] = "set voice %d\n";

const char s07b_dword_800E4B88[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4B8C = 0x800C531C;
const int s07b_dword_800E4B90 = 0x800C531C;
const int s07b_dword_800E4B94 = 0x800C5360;
const int s07b_dword_800E4B98 = 0x800C5374;
const int s07b_dword_800E4B9C = 0x800C531C;

const char s07b_dword_800E4BA0[] = "MERYL";

const char s07b_dword_800E4BA8[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4BAC = 0x800C81EC;
const int s07b_dword_800E4BB0 = 0x800C8338;
const int s07b_dword_800E4BB4 = 0x800C8368;
const int s07b_dword_800E4BB8 = 0x800C842C;
const int s07b_dword_800E4BBC = 0x800C846C;

const char s07b_dword_800E4BC0[] = {0x0, 0x0, 0x0, 0x0};

const int s07b_dword_800E4BC4 = 0x800C9DC4;
const int s07b_dword_800E4BC8 = 0x800C9DD4;
const int s07b_dword_800E4BCC = 0x800C9DE4;
const int s07b_dword_800E4BD0 = 0x800C9DF4;
const int s07b_dword_800E4BD4 = 0x800C9E04;
const int s07b_dword_800E4BD8 = 0x800C9E14;
const int s07b_dword_800E4BDC = 0x800C9E24;
const int s07b_dword_800E4BE0 = 0x800C9E34;
const int s07b_dword_800E4BE4 = 0x800C9E44;

const char s07b_dword_800E4BE8[] = "meryl";
const char s07b_dword_800E4BF0[] = "mel_07b";
const char s07b_dword_800E4BF8[] = "meryl07b.c";

/* TODO: split out psyco.c data */
int SECTION(".bss") s07b_dword_800E5BA0;
int SECTION(".bss") s07b_dword_800E5BA4;
int SECTION(".bss") s07b_dword_800E5BA8;
int SECTION(".bss") s07b_dword_800E5BAC;
int SECTION(".bss") s07b_dword_800E5BB0;
int SECTION(".bss") s07b_dword_800E5BB4;
int SECTION(".bss") s07b_dword_800E5BB8;
int SECTION(".bss") s07b_dword_800E5BBC;
int SECTION(".bss") s07b_dword_800E5BC0;
int SECTION(".bss") s07b_dword_800E5BC4;
int SECTION(".bss") s07b_dword_800E5BC8;
int SECTION(".bss") s07b_dword_800E5BCC;
int SECTION(".bss") s07b_dword_800E5BD0;
int SECTION(".bss") s07b_dword_800E5BD4;
int SECTION(".bss") s07b_dword_800E5BD8;
int SECTION(".bss") s07b_dword_800E5BDC;

/*---------------------------------------------------------------------------*/

// is the character inside the HZD event zone 'name'? (loop as in chara/snake/sna_init.c)
int s07b_800C46F0( CONTROL *control, int name, int check )
{
    int      i;
    u_short *zone;

    if ( !check )
    {
        return 0;
    }

    zone = control->evt.inside;
    for ( i = control->evt.n_inside; i > 0; i-- )
    {
        if ( *zone++ == name )
        {
            return 1;
        }
    }

    return 0;
}
void s07b_800C77A8( Work *work, int time );
void s07b_800C796C( Work *work, int time );

// is Snake inside the zone field_8B4[1]? (only checked outside first person view)
void s07b_800C77A8( Work *work, int time );

int s07b_800C473C( Work *work )
{
    CONTROL **control;
    int       zone;
    int       check;

    control = &GM_PlayerControl;
    zone = work->field_8B4[ 1 ];
    check = 0;
    if ( work->field_854 != s07b_800C77A8 && GM_Camera.first_person == 0 )
    {
        check = *work->field_8DC & 0x4000;
        check = check > 0;
    }

    if ( s07b_800C46F0( *control, zone, check ) )
    {
        work->field_850 |= 0x20000;
        return 1;
    }

    return 0;
}

// is Snake inside the zone field_8B4[4] with item 17 equipped?
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C47D4.s")
// distance and direction to the player, refresh the navigation address
void s07b_800C4854( Work *work )
{
    SVECTOR diff;
    SVECTOR pos;
    SVECTOR player;

    player = GM_PlayerPosition;
    player.vy = GM_PlayerControl->levels[ 0 ];
    pos = work->control.mov;
    pos.vy = work->control.levels[ 0 ];
    GV_SubVec3( &player, &pos, &diff );
    work->field_878 = GV_VecLen3( &diff );
    work->field_870 = diff;

    if ( GV_Time % 120 == 0 )
    {
        work->navi.addr = -1;
    }

    work->navi.addr = HZD_GetAddress( work->control.map->hzd, &work->control.mov, work->navi.addr );
}
void s07b_800C4974( Work *work )
{
    int diff;

    diff = GV_DiffDirS( work->control.turn.vy, work->control.rot.vy );
    if ( diff > 128 )
    {
        diff = 128;
    }
    else if ( diff < -128 )
    {
        diff = -128;
    }
    work->control.turn.vz = diff;
}
void s07b_800C49CC( int arg0 )
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
void s07b_800C4A18( Work *work, int on )
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
void s07b_800C4A94( Work *work )
{
    if ( work->field_86C == 0 )
    {
        return;
    }

    if ( work->field_86C > 0 )
    {
        if ( work->field_84C & 1 )
        {
            return;
        }
        if ( --work->field_86C == 0 )
        {
            work->body.objs->flag &= ~0x80;
            s07b_800C4A18( work, 0 );
            s07b_800C49CC( 0 );
        }
    }
    else
    {
        if ( !( work->field_84C & 1 ) )
        {
            return;
        }
        if ( ++work->field_86C == 0 )
        {
            work->body.objs->flag |= 0x80;
            s07b_800C4A18( work, 1 );
            s07b_800C49CC( 1 );
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C4B58.s")
void s07b_800C5B14( Work *work, int arg1 );

void s07b_800C4E90( Work *work )
{
    SVECTOR diff;
    int     dir;

    GV_SubVec3( &GM_PlayerPosition, &work->control.mov, &diff );
    dir = GV_VecDir2( &diff ) & 0xFFF;

    if ( !work->body.objs->adjust )
    {
        work->adjust[ 6 ].vy = 0;
        work->control.turn.vy = dir;
        work->control.interp = 8;
        return;
    }

    dir = GV_DiffDirS( dir, work->control.rot.vy );
    if ( dir > -0x300 && dir < 0x300 )
    {
        work->adjust[ 6 ].vy = GV_NearExp8( work->adjust[ 6 ].vy, -dir );
    }
    else
    {
        work->adjust[ 6 ].vy = 0;
        work->control.turn.vy = GV_VecDir2( &diff ) & 0xFFF;
        work->control.interp = 8;
    }
    s07b_800C5B14( work, 0 );
}
extern void *NewBlood( MATRIX *world, int count );

// blood effect at model part 'part'
void s07b_800C4F50( Work *work, int part )
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ part ].world );
    DG_MovePos( (SVECTOR *)&s07b_dword_800C3308 );
    DG_RotatePos( (SVECTOR *)&s07b_dword_800C3310 );
    ReadRotMatrix( &world );
    NewBlood( &world, 1 );
}
// muzzle flash at model part 4 (pattern as in chara/meryl07b/desert.c)
void s07b_800C4FB8( Work *work )
{
    MATRIX  world;
    DG_OBJ *obj;

    obj = &work->body.objs->objs[ 4 ];
    DG_SetPos( &obj->world );
    DG_MovePos( (SVECTOR *)&s07b_dword_800C3318 );
    ReadRotMatrix( &world );
    AN_SocomFlash( &obj->world, &world, 0 );
}
extern short s07b_dword_800C33F0;

void s07b_800C500C( Work *work )
{
    GCL_ARGS args;
    long     argv[4];

    if ( work->field_850 & 0x100 )
    {
        work->field_850 &= ~0x100;
        if ( work->field_846 < 0 )
        {
            if ( work->proc_id >= 0 && GM_Vitality != 0 && GM_GameOverTimer == 0 )
            {
                args.argc = 4;
                args.argv = argv;
                argv[0] = work->target->vital;
                argv[1] = s07b_dword_800C33F0;
                argv[2] = work->control.mov.vx;
                argv[3] = work->control.mov.vz;
                GCL_ExecProc( work->proc_id, &args );
            }
        }
        else
        {
            work->field_844 = work->field_846;
            work->field_848 = 0;
        }
    }
}
void s07b_800C50D8( Work *work )
{
    GV_MSG msg;

    if ( GM_Vitality != 0 && ( work->field_840 == 2 || work->field_840 == 3 ) )
    {
        msg.address = GV_StrCode( s07b_dword_800E4B4C );
        msg.message_len = 6;
        msg.message[0] = GV_StrCode( s07b_dword_800E4B58 );
        msg.message[1] = 0;
        msg.message[2] = -1;
        msg.message[3] = -1;
        msg.message[4] = 1;
        msg.message[5] = 0x572;
        GV_SendMessage( &msg );
    }
}
void s07b_800C5160( int arg0, int arg1 )
{
    GV_MSG msg;

    if ( GM_Vitality )
    {
        msg.address = GV_StrCode( s07b_dword_800E4B4C );
        msg.message_len = 4;
        msg.message[0] = GV_StrCode( s07b_dword_800E4B64 );
        msg.message[1] = arg0;
        msg.message[2] = -1;
        msg.message[3] = arg1 | 0x400;
        GV_SendMessage( &msg );
    }
}
void s07b_800C51DC( Work *work )
{
    GV_MSG msg;

    if ( GM_Vitality != 0 && (u_short)( work->field_840 - 2 ) < 2 )
    {
        s07b_800C5160( 0, 30 );
        msg.address = GV_StrCode( s07b_dword_800E4B4C );
        msg.message_len = 7;
        msg.message[ 0 ] = GV_StrCode( s07b_dword_800E4B6C );
        msg.message[ 1 ] = work->control.mov.vx;
        msg.message[ 2 ] = work->control.mov.vy;
        msg.message[ 3 ] = work->control.mov.vz;
        msg.message[ 4 ] = 1500;
        msg.message[ 5 ] = 1054;
        s07b_800C4854( work );
        if ( work->field_878 < 1500 )
        {
            msg.message[ 6 ] = work->control.turn.vy + 0x400;
        }
        else
        {
            msg.message[ 6 ] = 0xFFFF;
        }
        GV_SendMessage( &msg );
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C52B8.s")
void s07b_800C7C64( Work *work, int time );

void s07b_800C53A0( Work *work )
{
    if ( (u_short)work->field_844 < 2 )
    {
        if ( !( GM_PlayerStatus & 1 ) )
        {
            work->field_8C0 = 0;
            return;
        }
        if ( work->field_878 < 4001 &&
             GV_DiffDirAbs( GM_PlayerControl->rot.vy, GV_VecDir2( &work->field_870 ) ) >= 0x709 &&
             ++work->field_8C0 >= 151 )
        {
            if ( work->field_8BE < 4 )
            {
                work->field_8BE++;
            }
            work->field_8C0 = 0;
            work->field_854 = s07b_800C7C64;
            work->field_860 = 0;
            work->field_8C6 = 0;
            work->field_8C4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
void s07b_800C5490( void )
{
    if ( GM_GameOverTimer == 0 && GM_Vitality != 0 )
    {
        GM_GameOverTimer = -2;
    }
}
void s07b_800C54C0( Work *work, int time )
{
    work->field_8C2 = time;
    work->field_84C |= 2;
    work->target->class &= ~0x96;
}

void s07b_800C54E8( Work *work )
{
    work->field_8C2 = 0;
    work->field_84C &= ~2;
    work->target->class |= 0x9E;
}

void s07b_800C5514( Work *work )
{
    if ( work->field_8C2 != 0 )
    {
        if ( --work->field_8C2 == 0 )
        {
            s07b_800C54E8( work );
        }
    }
}
void s07b_800C5554( TARGET *target )
{
    target->a_mode = 0;
    target->damage = 0;
    target->damaged &= ~0x86;
    target->force = DG_ZeroVector;
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C5598.s")
void s07b_800C5B14( Work *work, int both )
{
    SVECTOR diff;
    SVECTOR from;
    SVECTOR to;
    SVECTOR vec;
    int     dir;
    SVECTOR *adjust;

    from.vx = GM_PlayerBody->objs->objs[ 5 ].world.t[ 0 ];
    from.vy = GM_PlayerBody->objs->objs[ 5 ].world.t[ 1 ];
    from.vz = GM_PlayerBody->objs->objs[ 5 ].world.t[ 2 ];
    to.vx = work->body.objs->objs[ 5 ].world.t[ 0 ];
    to.vy = work->body.objs->objs[ 5 ].world.t[ 1 ];
    to.vz = work->body.objs->objs[ 5 ].world.t[ 2 ];
    GV_SubVec3( &from, &to, &diff );
    vec.vz = SquareRoot0( diff.vx * diff.vx + diff.vz * diff.vz );
    vec.vx = diff.vy;
    dir = -GV_VecDir2( &vec );
    if ( dir < -0x800 )
    {
        dir += 0x1000;
    }
    adjust = work->adjust;
    adjust[ 6 ].vx = GV_NearExp4( adjust[ 6 ].vx, dir );

    if ( both )
    {
        to.vx = work->body.objs->objs[ 2 ].world.t[ 0 ];
        to.vy = work->body.objs->objs[ 2 ].world.t[ 1 ];
        to.vz = work->body.objs->objs[ 2 ].world.t[ 2 ];
        GV_SubVec3( &from, &to, &diff );
        vec.vz = SquareRoot0( diff.vx * diff.vx + diff.vz * diff.vz );
        vec.vx = diff.vy;
        dir = -GV_VecDir2( &vec );
        if ( dir < -0x800 )
        {
            dir += 0x1000;
        }
        adjust[ 2 ].vx = GV_NearExp4( adjust[ 2 ].vx, dir );
        adjust[ 7 ].vx = GV_NearExp4( adjust[ 7 ].vx, dir );
    }
}
void s07b_800C5DC4( Work *work, int time );

void s07b_800C5CFC( Work *work, int time )
{
    int action;

    if ( time == 0 )
    {
        if ( work->body.action != 0 )
        {
            GM_ConfigObjectAction( &work->body, 0, 0, 4 );
        }
        action = 2;
        if ( work->body.action2 != action )
        {
            GM_ConfigObjectOverride( &work->body, action, 0, 4, 0x3FE );
        }
        work->field_83A = 1;
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    s07b_800C4854( work );
    action = GV_VecDir2( &work->field_870 );
    work->control.turn.vy = action;

    if ( time == 100 )
    {
        work->field_854 = s07b_800C5DC4;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C7F48( Work *work, int time );
void s07b_800C6000( Work *work, int time );

void s07b_800C5DC4( Work *work, int time )
{
    int i;
    int trigger;
    int motion;

    if ( time == 0 )
    {
        if ( work->body.action != 0 )
        {
            GM_ConfigObjectAction( &work->body, 0, 0, 4 );
        }
        motion = 2;
        if ( work->body.action2 != motion )
        {
            GM_ConfigObjectOverride( &work->body, motion, 0, 4, 0x3FE );
        }
        work->field_83A = 1;
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    s07b_800C4854( work );

    if ( work->field_878 > 3000 )
    {
        work->field_854 = s07b_800C7F48;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
        return;
    }

    if ( work->field_838 == 0 )
    {
        work->field_854 = s07b_800C6000;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    s07b_800C5B14( work, 1 );

    trigger = 1;
    if ( work->field_83A == 1 )
    {
        if ( ++work->field_8C4 > 32 )
        {
            motion = 3;
            if ( work->body.action2 != motion )
            {
                GM_ConfigObjectOverride( &work->body, motion, 0, 4, 0x3FE );
            }
            trigger = 3;
            work->field_83A = 2;
            work->field_8C4 = 0;
            work->field_838--;
        }
    }
    else if ( work->body.time2 != 0 )
    {
        motion = 2;
        if ( work->body.action2 != motion )
        {
            GM_ConfigObjectOverride( &work->body, motion, 0, 4, 0x3FE );
        }
        work->field_83A = 1;
        work->field_8C4 = 0;
    }

    work->trigger = trigger;
    work->control.turn.vy = GV_VecDir2( &work->field_870 );
}
void s07b_800C6000( Work *work, int time )
{
    int i;
    int act;
    int motion;

    if ( time == 0 )
    {
        act = 4;
        motion = 0xFFFF;
        if ( work->body.action2 != act )
        {
            GM_ConfigObjectOverride( &work->body, act, 0, act, motion );
        }
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
        work->field_838 = 7;
    }
    if ( time == 126 )
    {
        GM_SeSetMode( &work->control.mov, 0x2F, 1 );
    }
    if ( work->body.time2 )
    {
        work->field_854 = s07b_800C5DC4;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C7F48( Work *work, int time );
void s07b_800C7D88( Work *work, int time );

void s07b_800C8140( Work *work, int time );
void s07b_800C8510( Work *work, int time );

void s07b_800C60F0( Work *work, int time )
{
    void ( *mode )( Work *, int );
    int act;

    if ( time == 0 )
    {
        act = ( GV_Time & 1 ) ? 5 : 6;
        work->body.action = -1;
        if ( work->body.action != act )
        {
            GM_ConfigObjectAction( &work->body, act, 0, 4 );
        }
    }

    if ( work->body.is_end )
    {
        switch ( (u_short)work->field_844 )
        {
        case 0:
        case 1:
            mode = s07b_800C8510;
            break;
        case 4:
            mode = s07b_800C7F48;
            break;
        case 6:
            mode = s07b_800C8140;
            break;
        default:
            mode = s07b_800C7D88;
            break;
        }
        work->field_854 = mode;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C6634( Work *work, int time );

void s07b_800C61D8( Work *work, int time )
{
    if ( time == 0 )
    {
        s07b_800C54C0( work, 0 );
        if ( work->body.action != 7 )
        {
            GM_ConfigObjectAction( &work->body, 7, 0, 4 );
        }
    }
    if ( time == 36 )
    {
        GM_SeSetMode( &work->control.mov, 0x33, 1 );
    }
    if ( work->body.is_end )
    {
        work->field_8C8 = 3;
        work->field_854 = s07b_800C6634;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C52B8( Work *work );

void s07b_800C627C( Work *work, int time )
{
    int dir;

    if ( time == 0 )
    {
        if ( work->body.action != 9 )
        {
            GM_ConfigObjectAction( &work->body, 9, 0, 4 );
        }
        dir = GV_VecDir2( &work->field_864 ) + 0x800;
        work->control.turn.vy = dir;
        work->control.rot.vy = dir;
        s07b_800C54C0( work, 0 );
        GM_SeSetMode( &work->control.mov, 0x8B, 1 );
        if ( work->target->vital <= 0 )
        {
            work->field_84C |= 8;
            if ( work->field_840 == 2 || work->field_840 == 3 )
            {
                s07b_800C52B8( work );
            }
        }
    }

    if ( work->body.is_end )
    {
        work->field_854 = s07b_800C6634;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_8C8 = 1;
        return;
    }

    if ( work->control.height < 500 )
    {
        work->field_86E = 1;
        work->target->class |= 0x20;
    }

    if ( time == 16 )
    {
        GM_SeSetMode( &work->control.mov, 0x33, 1 );
    }

    if ( time > 16 )
    {
        GV_NearExp8V( &work->field_864, &DG_ZeroVector, 3 );
    }

    work->control.step.vx += work->field_864.vx;
    work->control.step.vz += work->field_864.vz;
}
void s07b_800C52B8( Work *work );

void s07b_800C63F4( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 13 )
        {
            GM_ConfigObjectAction( &work->body, 13, 0, 4 );
        }
        work->control.turn.vy = GM_PlayerControl->turn.vy + 0x800;
        s07b_800C54C0( work, 0 );
    }

    if ( work->control.height < 500 )
    {
        work->field_86E = 1;
        work->target->class |= 0x20;
    }

    if ( time == 20 )
    {
        GM_SeSetMode( &work->control.mov, 0x33, 1 );
        if ( work->target->vital <= 0 )
        {
            work->field_84C |= 8;
            if ( work->field_840 == 2 || work->field_840 == 3 )
            {
                s07b_800C52B8( work );
            }
            else
            {
                GM_SeSetMode( &work->control.mov, 0x8B, 1 );
            }
        }
        else
        {
            GM_SeSetMode( &work->control.mov, 0x8A, 1 );
        }
    }

    if ( work->body.is_end )
    {
        work->field_854 = s07b_800C6634;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_8C8 = 2;
    }
}
void s07b_800C6538( Work *work, int time )
{
    TARGET *target;

    if ( time == 0 )
    {
        if ( work->body.action != 30 )
        {
            GM_ConfigObjectAction( &work->body, 30, 0, 4 );
        }
        s07b_800C54C0( work, 0 );
    }

    if ( work->control.height < 500 )
    {
        work->field_86E = 1;
        work->target->class |= 0x20;
    }

    if ( work->body.is_end )
    {
        target = work->target;
        work->field_854 = s07b_800C6634;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_8C8 = 1;
        target->faint = 0;
        return;
    }

    if ( time == 53 )
    {
        GM_SeSetMode( &work->control.mov, 0x51, 1 );
    }

    if ( time == 75 )
    {
        GM_SeSetMode( &work->control.mov, 0x33, 1 );
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6634.s")
void s07b_800C6964( Work *work, int time )
{
    void ( *mode )( Work *, int );
    int act;

    if ( time == 0 )
    {
        s07b_800C54E8( work );
        act = ( work->field_8C8 == 1 ) ? 19 : 20;
        if ( work->body.action != act )
        {
            GM_ConfigObjectAction( &work->body, act, 0, 4 );
        }
    }

    if ( work->control.height > 500 )
    {
        work->field_86E = 0;
    }

    if ( work->body.is_end )
    {
        work->field_84C &= ~4;
        work->field_8C8 = 0;
        if ( work->field_840 == 3 )
        {
            s07b_800C54E8( work );
        }
        work->target->class &= ~0x20;
        switch ( (u_short)work->field_844 )
        {
        case 0:
        case 1:
            mode = s07b_800C8510;
            break;
        case 4:
            mode = s07b_800C7F48;
            break;
        case 6:
            mode = s07b_800C8140;
            break;
        default:
            mode = s07b_800C7D88;
            break;
        }
        work->field_854 = mode;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C6D80( Work *work, int time );
void s07b_800C6E54( Work *work, int time );

void s07b_800C6C5C( Work *work, int time );
void s07b_800C7040( Work *work, int time );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C6AA4.s")
int s07b_800C6AA4( Work *work, int action );

void s07b_800C6B8C( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 15 )
        {
            GM_ConfigObjectAction( &work->body, 15, 0, 4 );
        }
        work->control.turn.vy = GM_PlayerControl->turn.vy;
        GM_SeSetMode( &work->control.mov, 0xBE, 1 );
    }

    if ( ++work->field_82C > 50 )
    {
        if ( work->body.action != 35 )
        {
            GM_ConfigObjectAction( &work->body, 35, 0, 4 );
        }
        if ( ( work->field_82C & 7 ) == 0 )
        {
            NewPadVibration( (unsigned char *)&s07b_dword_800C3304, 2 );
        }
    }
    s07b_800C6AA4( work, -1 );
}
void s07b_800C6C5C( Work *work, int time )
{
    SVECTOR vec;

    if ( time == 0 )
    {
        work->target->class |= 0x20;
        if ( work->body.action != 18 )
        {
            GM_ConfigObjectAction( &work->body, 18, 0, 4 );
        }
        s07b_800C54C0( work, 0 );
    }

    if ( time == 10 )
    {
        GM_SeSetMode( &work->control.mov, 0x51, 1 );
    }

    if ( time == 34 )
    {
        GM_SeSetMode( &work->control.mov, 0x33, 1 );
    }

    if ( work->control.height < 500 )
    {
        work->field_86E = 1;
    }

    vec.vy = 0;
    vec.vx = 0;
    vec.vz = 16;
    DG_RotVector( &vec, &work->control.step, 1 );

    if ( work->body.is_end )
    {
        work->field_8C8 = 2;
        work->field_854 = s07b_800C6634;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_850 &= ~4;
    }
}
void s07b_800C6E54( Work *work, int time );

void s07b_800C6D80( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 16 )
        {
            GM_ConfigObjectAction( &work->body, 16, 0, 4 );
        }
        GM_SeSetMode( &work->control.mov, 0xBE, 1 );
        work->field_82C = 0;
    }

    if ( work->body.is_end )
    {
        if ( work->target->vital <= 0 )
        {
            s07b_800C5490();
            work->field_854 = s07b_800C6E54;
            work->field_860 = 0;
            work->field_8C6 = 0;
            work->field_8C4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            return;
        }
        work->field_854 = s07b_800C6B8C;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    s07b_800C6AA4( work, 0x26 );
}
void s07b_800C73F0( Work *work, int time );

void s07b_800C6E54( Work *work, int time )
{
    SVECTOR vec;

    if ( time == 0 )
    {
        if ( work->body.action != 17 )
        {
            GM_ConfigObjectAction( &work->body, 17, 0, 4 );
        }
        work->target->vital = 0;
        work->target->damage = 0;
        work->target->captured = 0;
        s07b_800C5554( work->target );
        work->target->class |= 0x20;
        GM_GameStatus |= 0x10000000;
        work->field_84C |= 8;
        s07b_800C5490();
        GM_SeSetMode( &work->control.mov, 0xBF, 1 );
        if ( work->field_840 == 2 || work->field_840 == 3 )
        {
            GM_VoxQueueDelay( work->field_8E4[ 13 ], 4 );
        }
    }

    if ( time == 58 )
    {
        GM_SeSetMode( &work->control.mov, 0x51, 1 );
    }

    if ( time == 71 )
    {
        GM_SeSetMode( &work->control.mov, 0x33, 1 );
    }

    if ( time >= 49 && time < 60 )
    {
        vec.vy = 0;
        vec.vx = 0;
        vec.vz = 96;
        DG_RotVector( &vec, &work->control.step, 1 );
    }

    if ( work->control.height < 500 )
    {
        work->field_86E = 1;
    }

    if ( work->body.is_end )
    {
        if ( work->body.action != 14 )
        {
            GM_ConfigObjectAction( &work->body, 14, 0, 4 );
        }
        work->field_86E = 1;
        work->field_854 = s07b_800C73F0;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_850 &= ~4;
        if ( work->field_840 < 2 || work->field_840 == 4 )
        {
            s07b_800C52B8( work );
        }
    }
}
void s07b_800C7040( Work *work, int time )
{
    SVECTOR pos;
    MATRIX  rot;

    if ( time == 0 )
    {
        if ( work->body.action != 15 )
        {
            GM_ConfigObjectAction( &work->body, 15, 0, 4 );
        }
    }

    if ( ++work->field_82C > 50 )
    {
        if ( work->body.action != 35 )
        {
            GM_ConfigObjectAction( &work->body, 35, 0, 4 );
        }
        if ( ( work->field_82C & 7 ) == 0 )
        {
            NewPadVibration( (unsigned char *)&s07b_dword_800C3304, 2 );
        }
    }

    if ( !s07b_800C6AA4( work, 13 ) )
    {
        work->control.turn.vy = GM_PlayerControl->turn.vy;
        DG_SetPos2( &GM_PlayerControl->mov, &GM_PlayerControl->rot );
        DG_MovePos( (SVECTOR *)&s07b_dword_800C3320 );
        ReadRotMatrix( &rot );
        pos.vx = rot.t[ 0 ];
        pos.vy = rot.t[ 1 ];
        pos.vz = rot.t[ 2 ];
        GV_SubVec3( &pos, &work->control.mov, &work->control.step );
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C714C.s")
void s07b_800C73F0( Work *work, int time )
{
    SVECTOR rot;

    if ( time == 0 )
    {
        work->field_84C |= 0xC;
        s07b_800C54C0( work, 0 );
        GM_GameStatus |= 0x10000000;
        if ( GM_Vitality != 0 )
        {
            if ( GM_ItemTypes[ GM_Item + 1 ] & 0x2 )
            {
                GM_Item = IT_None;
            }
            if ( GM_WeaponTypes[ GM_Weapon + 1 ] & 0x200 )
            {
                GM_Weapon = WP_None;
            }
            GCL_ExecProc( work->field_930[ 7 ], NULL );
            GCL_ExecProc( work->field_930[ 8 ], NULL );
        }
        GM_ConfigMotionAdjust( &work->body, work->adjust );
        s07b_800C4854( work );
        if ( !( GM_PlayerStatus & 0x340 ) )
        {
            GM_PlayerControl->turn.vy = GV_VecDir2( &work->field_870 ) + 0x800;
        }
    }

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );

    if ( GM_Camera.first_person == 0 && GM_Vitality != 0 )
    {
        GM_SnakeCamera.position = work->control.mov;
        GM_CameraSetTrack( 2500 );
        rot.vx = 640;
        rot.vy = 0x800;
        rot.vz = 0;
        if ( work->control.mov.vz > 10000 )
        {
            rot.vy = 0;
        }
        GM_CameraSetRotation( &rot );
    }

    if ( work->field_8C4 == 0 && ++work->field_8C6 > 64 && GM_GameOverTimer == -2 )
    {
        s07b_800C51DC( work );
        s07b_800C50D8( work );
        GM_GameOverTimer = 0;
        GM_GameOver();
        work->field_8C4 = 1;
    }
}
void s07b_800C7604( Work *work )
{
    int now;
    int rest;
    int diff;

    if ( !( work->field_850 & 0x400 ) )
    {
        return;
    }

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

    MENU_DrawBar2( work->lifebar_ypos, rest, now, GM_VitalityMax, &work->lifebar );

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
typedef struct { char s[ 6 ]; } NAME6;

int s07b_800C76C8( Work *work )
{
    MENU_BAR_CONF *bar;

    if ( GCL_GetOption( 'h' ) )
    {
        work->lifebar_xpos = GCL_StrToInt( GCL_NextStr() );
        work->lifebar_ypos = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->lifebar_xpos = 16;
        work->lifebar_ypos = 40;
    }
    work->lifebar_rest = work->target->vital;
    *(NAME6 *)&s07b_dword_800E5BA0 = *(NAME6 *)s07b_dword_800E4BA0;
    work->lifebar.name = (char *)&s07b_dword_800E5BA0;
    bar = &work->lifebar;
    bar->left[ 0 ] = 31;
    bar->left[ 1 ] = 191;
    bar->left[ 2 ] = 95;
    bar->right[ 0 ] = 31;
    bar->right[ 1 ] = 191;
    bar->right[ 2 ] = 95;
    bar->height = 1;
    return 0;
}
void s07b_800C7AA8( Work *work, int time );

void s07b_800C77A8( Work *work, int time )
{
    int r;
    int i;

    if ( time == 0 )
    {
        r = GV_RandU( 16 ) % 3;
        if ( work->body.action != 26 )
        {
            GM_ConfigObjectAction( &work->body, 26, 0, 4 );
        }
        work->field_8D0 = work->field_8E4[ r ];
        GM_VoxInit();
        if ( GM_Vitality != 0 )
        {
            GM_VoxQueueDelay( work->field_8E4[ r ], 4 );
        }
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );

    if ( GM_VoxCodeEnd( work->field_8D0 ) )
    {
        switch ( (u_short)work->field_844 )
        {
        case 0:
        case 2:
            work->field_854 = s07b_800C7D88;
            work->field_860 = 0;
            work->field_8C6 = 0;
            work->field_8C4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            break;
        case 1:
        default:
            work->field_854 = s07b_800C7AA8;
            work->field_860 = 0;
            work->field_8C6 = 0;
            work->field_8C4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            break;
        }
        work->field_850 &= ~0x20000;
        s07b_800C54E8( work );
        GM_GameStatus &= ~0x10000000;
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
    }

    s07b_800C4854( work );
    s07b_800C4E90( work );
}

void s07b_800C796C( Work *work, int time )
{
    int i;

    if ( time == 0 )
    {
        GV_RandU( 16 );
        if ( work->body.action != 26 )
        {
            GM_ConfigObjectAction( &work->body, 26, 0, 4 );
        }
        work->field_8D0 = work->field_8E4[ 18 ];
        GM_VoxInit();
        if ( GM_Vitality != 0 )
        {
            GM_VoxQueueDelay( work->field_8E4[ 18 ], 4 );
        }
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );

    if ( GM_VoxCodeEnd( work->field_8D0 ) )
    {
        work->field_854 = s07b_800C7D88;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800C54E8( work );
        GM_GameStatus &= ~0x10000000;
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
    }

    s07b_800C4854( work );
    s07b_800C4E90( work );
}
// the negation must happen on an int (lh, not lhu)
static inline int s07b_Negate( short value )
{
    return -value;
}

void s07b_800C7AA8( Work *work, int time )
{
    SVECTOR dir;

    if ( time == 0 )
    {
        if ( work->body.action != 25 )
        {
            GM_ConfigObjectAction( &work->body, 25, 0, 4 );
        }
        NavigateSetTarget( &work->navi, work->control.map->hzd, &work->field_8D4 );
        if ( work->field_8CC == 0 )
        {
            GCL_ExecProc( work->field_930[ 1 ], NULL );
        }
    }

    s07b_800C4854( work );

    switch ( work->field_8C4 )
    {
    case 0:
        if ( !( GM_PlayerStatus & 0x2204 ) && work->field_8CC == 0 &&
             GM_PlayerPosition.vz > work->control.mov.vz )
        {
            dir = work->field_870;
            dir.vx = s07b_Negate( dir.vx );
            dir.vz = s07b_Negate( dir.vz );
            GM_PlayerControl->turn.vy = GV_VecDir2( &dir );
        }
        GM_ZoneNavi( &work->navi, &work->control );
        if ( NavigateGetTargetDist( &work->navi, &work->control.mov ) < 500 )
        {
            work->field_8C4 = 1;
            GM_GameStatus &= ~0x10000000;
            s07b_800C54E8( work );
            if ( work->body.action != 24 )
            {
                GM_ConfigObjectAction( &work->body, 24, 0, 4 );
            }
            work->field_8CC = 1;
        }
        break;
    case 1:
        s07b_800C4E90( work );
        break;
    }
}
void s07b_800C4854( Work *work );
void s07b_800C7D88( Work *work, int time );


void s07b_800C7C64( Work *work, int time )
{
    int idx;

    if ( time == 0 )
    {
        idx = work->field_8BE;
        if ( work->body.action != 24 )
        {
            GM_ConfigObjectAction( &work->body, 24, 0, 4 );
        }
        GM_ConfigMotionAdjust( &work->body, work->adjust );
        GM_VoxInit();
        if ( GM_Vitality != 0 )
        {
            GM_VoxQueueDelay( work->field_8E4[ idx + 14 ], 4 );
        }
    }

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );
    s07b_800C4854( work );
    s07b_800C4E90( work );

    if ( work->field_8C4 == 0 && time >= 5 && GM_StreamStatus() == 2 )
    {
        work->field_8C4 = 1;
    }

    if ( work->field_8C4 != 0 && GM_StreamStatus() != 2 )
    {
        work->field_854 = s07b_800C7D88;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C7E98( Work *work, int time );

void s07b_800C7D88( Work *work, int time )
{
    int i;

    if ( time == 0 )
    {
        if ( work->body.action != 24 )
        {
            GM_ConfigObjectAction( &work->body, 24, 0, 4 );
        }
        GM_ConfigMotionAdjust( &work->body, work->adjust );
    }

    s07b_800C4854( work );

    if ( work->field_878 > 3000 )
    {
        if ( ++work->field_8C4 >= 5 )
        {
            GM_ConfigMotionAdjust( &work->body, NULL );
            for ( i = 0; i < 16; i++ )
            {
                work->adjust[ i ] = DG_ZeroVector;
            }
            work->field_854 = s07b_800C7E98;
            work->field_860 = 0;
            work->field_8C6 = 0;
            work->field_8C4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            return;
        }
    }
    else
    {
        work->field_8C4 = 0;
    }

    s07b_800C4E90( work );
    s07b_800C53A0( work );
}
void s07b_800C4854( Work *work );
void s07b_800C7D88( Work *work, int time );

void s07b_800C7E98( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 25 )
        {
            GM_ConfigObjectAction( &work->body, 25, 0, 4 );
        }
        work->navi.target_next = -1;
    }

    if ( work->field_878 <= 2000 )
    {
        work->field_854 = s07b_800C7D88;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    s07b_800C4854( work );
    NavigateSetTargetPlayer( &work->navi );
    GM_ZoneNavi( &work->navi, &work->control );
    s07b_800C4974( work );
}
void s07b_800C7F48( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( work->body.action != 1 )
        {
            GM_ConfigObjectAction( &work->body, 1, 0, 4 );
        }
        work->navi.target_next = -1;
    }

    s07b_800C4854( work );

    if ( work->field_878 <= 2000 )
    {
        if ( work->body.action != 0 )
        {
            GM_ConfigObjectAction( &work->body, 0, 0, 4 );
        }
        work->field_854 = s07b_800C5DC4;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        NavigateSetTargetPlayer( &work->navi );
        GM_ZoneNavi( &work->navi, &work->control );
    }
}
void s07b_800C8010( Work *work, int time )
{
    int action;
    int act;

    if ( time == 0 )
    {
        act = work->body.action;
        if ( act != 10 && act != 14 && act != 8 )
        {
            if ( act != 7 )
            {
                GM_ConfigObjectAction( &work->body, 7, 0, 4 );
            }
        }
        else
        {
            work->field_86E = 1;
            if ( act == 10 )
            {
                work->field_8C8 = 1;
            }
            else
            {
                work->field_8C8 = 2;
            }
            work->field_84C |= 4;
        }
        s07b_800C54C0( work, 0 );
    }

    action = work->body.action;
    if ( action == 7 )
    {
        if ( time == 36 )
        {
            GM_SeSetMode( &work->control.mov, 0x33, 1 );
        }
        if ( work->body.action == action && work->body.is_end )
        {
            work->field_86E = 1;
            work->field_8C8 = 2;
            work->field_84C |= 4;
            if ( work->body.action != 8 )
            {
                GM_ConfigObjectAction( &work->body, 8, 0, 4 );
            }
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8140.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C84FC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8510.s")
void OpenCinemaScreen( int type, int time );
void CloseCinemaScreen( void );

void s07b_800C89E0( Work *work, int time )
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
        s07b_800C54C0( work, 0 );
        if ( work->body.action != 26 )
        {
            GM_ConfigObjectAction( &work->body, 26, 0, 4 );
        }
        GM_VoxQueue( work->field_8E4[ 4 ] );
        GCL_ExecProc( work->field_930[ 0 ], NULL );
        GM_ConfigMotionAdjust( &work->body, work->adjust );
        OpenCinemaScreen( 1, 10000 );
    }

    if ( GM_VoxCodeStart( work->field_8E4[ 4 ] ) )
    {
        GCL_ExecProc( work->field_930[ 10 ], NULL );
        work->field_8C6 = 1;
    }

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );

    if ( work->body.is_end && work->body.action == 26 )
    {
        GM_ConfigObjectAction( &work->body, 27, 0, 4 );
    }

    if ( work->field_8C6 > 0 && ++work->field_8C6 == 126 )
    {
        work->field_854 = s07b_800C7D88;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800C54E8( work );
        GM_GameStatus &= ~0x2000;
        work->field_850 |= 0x400;
        CloseCinemaScreen();
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C8BB4.s")
void s07b_800C4E90( Work *work );

void s07b_800C8F9C( Work *work, int time )
{
    if ( time == 0 && work->body.action != 19 )
    {
        GM_ConfigObjectAction( &work->body, 19, 0, 4 );
    }

    if ( work->field_8C4 == 0 )
    {
        if ( work->body.is_end )
        {
            work->field_84C &= ~4;
            if ( work->body.action != 0 )
            {
                GM_ConfigObjectAction( &work->body, 0, 0, 4 );
            }
            work->field_8C4++;
        }
    }
    else
    {
        s07b_800C4E90( work );
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9044.s")
void s07b_800C9304( Work *work )
{
    int     n_msgs;
    GV_MSG *msg;
    int     val;
    int     none;
    int     flag;
    int     act;

    if ( work->control.n_msg == 0 )
    {
        return;
    }

    n_msgs = work->control.n_msg;
    msg = &work->control.msg[ n_msgs ] - 1;
    if ( n_msgs > 0 )
    {
        none = -1;
        flag = 0x10000;
        act = 24;
        do
        {
            switch ( msg->message[ 0 ] )
            {
            case 0x491D:
                val = msg->message[ 1 ];
                if ( (u_short)( val + 1 ) < 10 )
                {
                    work->field_846 = val;
                    work->field_850 |= 0x100;
                }
                break;
            case 0xA7DE:
                work->field_846 = none;
                work->field_850 |= 0x100;
                break;
            case 0x5E8B:
                work->field_850 |= flag;
                if ( work->body.action != act )
                {
                    GM_ConfigObjectAction( &work->body, 24, 0, 4 );
                }
                break;
            case 0x9A1F:
                work->field_850 &= ~0x10000;
                break;
            }
            n_msgs--;
            msg--;
        } while ( n_msgs > 0 );
    }
}
int s07b_800C47D4( Work *work );

void s07b_800C9454( Work *work, int time )
{
    int i;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust( &work->body, work->adjust );
        work->field_854 = s07b_800C7D88;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    switch ( work->field_840 )
    {
    case 0:
        if ( s07b_800C46F0( GM_PlayerControl, work->field_8B4[ 2 ], work->field_854 != s07b_800C7C64 ) )
        {
            GM_GameStatus |= 0x10000000;
            if ( work->field_854 == s07b_800C7D88 || work->field_854 == s07b_800C7E98 )
            {
                s07b_800C54C0( work, 0 );
                s07b_800C5554( work->target );
                GM_ConfigMotionAdjust( &work->body, NULL );
                for ( i = 0; i < 16; i++ )
                {
                    work->adjust[ i ] = DG_ZeroVector;
                }
                work->field_854 = s07b_800C7AA8;
                work->field_860 = 0;
                work->field_8C6 = 0;
                work->field_8C4 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                work->field_846 = 1;
                work->field_850 |= 0x100;
                break;
            }
        }
        if ( s07b_800C473C( work ) && work->field_854 != s07b_800C7C64 )
        {
            GM_GameStatus |= 0x10000000;
            if ( work->field_854 == s07b_800C7D88 || work->field_854 == s07b_800C7E98 )
            {
                s07b_800C54C0( work, 0 );
                s07b_800C5554( work->target );
                work->field_854 = s07b_800C77A8;
                work->field_860 = 0;
                work->field_8C6 = 0;
                work->field_8C4 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
            }
        }
        break;
    case 4:
        if ( s07b_800C47D4( work ) && work->field_854 != s07b_800C7C64 )
        {
            GM_GameStatus |= 0x10000000;
            if ( work->field_854 == s07b_800C7D88 || work->field_854 == s07b_800C7E98 )
            {
                s07b_800C54C0( work, 0 );
                s07b_800C5554( work->target );
                work->field_854 = s07b_800C796C;
                work->field_860 = 0;
                work->field_8C6 = 0;
                work->field_8C4 = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
            }
        }
        break;
    }
}
int  s07b_800C473C( Work *work );
void s07b_800C77A8( Work *work, int time );

void s07b_800C96B8( Work *work )
{
    if ( s07b_800C473C( work ) )
    {
        GM_GameStatus |= 0x10000000;

        if ( work->body.action == 24 )
        {
            s07b_800C54C0( work, 0 );
            s07b_800C5554( work->target );
            work->field_854 = s07b_800C77A8;
            work->field_860 = 0;
            work->field_8C6 = 0;
            work->field_8C4 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9738.s")
void s07b_800C4B58( Work *work );

void s07b_800C9954( Work *work )
{
    if ( GM_Vitality != 0 && GM_GameOverTimer == 0 )
    {
        s07b_800C4B58( work );
    }
}
void s07b_800C5CFC( Work *work, int time );

void s07b_800C9994( Work *work, int time )
{
    int i;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
        work->field_850 |= 0x400;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800C5CFC;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800C54E8( work );
    }
}
void s07b_800C8010( Work *work, int time );

void s07b_800C9A58( Work *work, int time )
{
    int i;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800C8010;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800C54C0( work, 0 );
        s07b_800C5554( work->target );
    }
}
void s07b_800C8F9C( Work *work, int time );

void s07b_800C9B24( Work *work, int time )
{
    if ( GM_Vitality != 0 && GM_GameOverTimer == 0 && time == 0 )
    {
        s07b_800C54C0( work, 0 );
        work->field_854 = s07b_800C8F9C;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C9044( Work *work, int time );

void s07b_800C9B94( Work *work, int time )
{
    int i;

    if ( GM_Vitality != 0 && GM_GameOverTimer == 0 && time == 0 )
    {
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
        work->field_84C &= ~4;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800C9044;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s07b_800C9C74( Work *work, int time )
{
    int i;

    if ( time == 0 )
    {
        GM_ConfigMotionAdjust( &work->body, NULL );
        for ( i = 0; i < 16; i++ )
        {
            work->adjust[ i ] = DG_ZeroVector;
        }
        work->field_84C &= ~4;
        if ( work->body.action2 != 0 )
        {
            GM_ConfigObjectOverride( &work->body, 0, 0, 4, 0 );
        }
        work->field_854 = s07b_800C8140;
        work->field_860 = 0;
        work->field_8C6 = 0;
        work->field_8C4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        s07b_800C54E8( work );
        s07b_dword_800E5BC0 = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800C9D44.s")
int s07b_800CA1FC( Work *work )
{
    int     life;
    int     faint;
    TARGET *target;

    if ( GCL_GetOption( 'l' ) )
    {
        life = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        life = GM_VitalityMax;
    }
    if ( (u_short)( work->field_840 - 1 ) < 2 )
    {
        life = s07b_dword_800C32F8;
    }
    if ( life < 32 )
    {
        life = 32;
    }
    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget( target, 0x9F, 2, (SVECTOR *)&s07b_dword_800C3328 );
    faint = 20;
    if ( work->field_840 == 3 )
    {
        faint = 12;
    }
    GM_SetPowerTarget( target, 1, -1, life, faint, &DG_ZeroVector );
    return 0;
}
extern u_short desert_damage;
void *NewDesertEagle( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *trigger, int side );

int s07b_800CA2EC( Work *work )
{
    int i;
    int level;

    work->weapon = NewDesertEagle( &work->control, &work->body, 4, &work->trigger, 2 );

    if ( GCL_GetOption( 'x' ) )
    {
        level = GM_GameLevel;
        if ( level < 0 )
        {
            level = 0;
        }
        for ( i = 0; i < level; i++ )
        {
            GCL_GetNextInt();
        }
        desert_damage = GCL_GetNextInt();
    }

    work->field_838 = 7;
    work->field_854 = s07b_800C7D88;
    work->field_860 = 0;
    work->field_8C6 = 0;
    work->field_8C4 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    s07b_dword_800E5BB0 = (int)&work->field_84C;
    NagivateInit( &work->navi, work->control.map->hzd, &work->control.mov );

    work->field_8DC = (u_short *)GV_PadData;
    work->control.hzd_height = 750;
    work->field_846 = -1;
    work->sepia = NULL;

    if ( GCL_GetOption( 'v' ) )
    {
        GCL_StrToSV( GCL_NextStr(), (short *)&work->field_8D4 );
    }
    if ( GCL_GetOption( 's' ) )
    {
        work->field_840 = GCL_StrToInt( GCL_NextStr() );
    }
    if ( GCL_GetOption( 'g' ) )
    {
        if ( GCL_StrToInt( GCL_NextStr() ) == 1 )
        {
            work->field_850 |= 0x400;
        }
    }
    if ( GCL_GetOption( 'm' ) )
    {
        work->field_844 = GCL_StrToInt( GCL_NextStr() );
    }
    if ( (u_short)work->field_844 == 8 && work->body.action != 8 )
    {
        GM_ConfigObjectAction( &work->body, 8, 0, 0 );
    }
    if ( GCL_GetOption( 'e' ) )
    {
        work->proc_id = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->proc_id = -1;
    }
    return 0;
}
// read the zone names of script option 't' (max 5), or use the two defaults
void s07b_800CA4FC( Work *work )
{
    int      i;
    u_short *out;
    char    *param;

    if ( GCL_GetOption( 't' ) )
    {
        i = 0;
        out = work->field_8B4;
        while ( ( param = GCL_NextStr() ) )
        {
            if ( i == 5 )
            {
                break;
            }
            *out++ = GCL_StrToInt( param );
            i++;
        }
    }
    else
    {
        work->field_8B4[ 0 ] = 0xEC92;
        work->field_8B4[ 1 ] = 0x2FB7;
    }
}
// read the numbers of script option 'c' (max 19)
void s07b_800CA584( Work *work )
{
    int   i;
    int  *out;
    char *param;

    if ( GCL_GetOption( 'c' ) )
    {
        i = 0;
        out = work->field_8E4;
        while ( ( param = GCL_NextStr() ) )
        {
            if ( i == 19 )
            {
                break;
            }
            *out++ = GCL_StrToInt( param );
            i++;
        }
    }
}

// read the numbers of script option 'r' (max 11)
void s07b_800CA5FC( Work *work )
{
    int   i;
    int  *out;
    char *param;

    if ( GCL_GetOption( 'r' ) )
    {
        i = 0;
        out = work->field_930;
        while ( ( param = GCL_NextStr() ) )
        {
            if ( i == 11 )
            {
                break;
            }
            *out++ = GCL_StrToInt( param );
            i++;
        }
    }
}

// read the numbers of script option 'f' (max 8)
void s07b_800CA674( Work *work )
{
    int   i;
    int  *out;
    char *param;

    if ( GCL_GetOption( 'f' ) )
    {
        i = 0;
        out = work->field_95C;
        while ( ( param = GCL_NextStr() ) )
        {
            if ( i == 8 )
            {
                break;
            }
            *out++ = GCL_StrToInt( param );
            i++;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA6EC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800CA8F8.s")
