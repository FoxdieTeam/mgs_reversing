#include "libgcl/libgcl.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

/* Same as everywhere else, though size is different */
typedef struct _TEXT {
    SPRT  sprt[ 10 ];
    char *string;
    short num;
    short unk[ 9 ];
} TEXT;

typedef struct _Work {
    /* 0x000 */ GV_ACT   actor;
    /* 0x020 */ GV_PAD  *pad;
    /* 0x024 */ DG_PRIM *prim;
    /* 0x028 */ DG_PRIM *prim_cur;
    /* 0x02C */ POLY_FT4 pol[ 16 ];
    /* 0x2AC */ POLY_FT4 pol_cur[ 9 ];
    /* 0x414 */ int      end_proc;
    /* 0x418 */ int      time_proc;
    /* 0x41C */ int      z[ 16 ];
    /* 0x45C */ int      z_cur[ 9 ];
    /* 0x480 */ int      time;
    /* 0x484 */ int      state;
    /* 0x488 */ int      play_hours;
    /* 0x48C */ int      play_minutes;
    /* 0x490 */ int      play_seconds;
    /* 0x494 */ int      field_494;
    /* 0x498 */ int      field_498;
    /* 0x49C */ int      field_49C;
    /* 0x4A0 */ int      field_4A0;
    /* 0x4A4 */ int      field_4A4;
    /* 0x4A8 */ int      field_4A8;
    /* 0x4AC */ int      field_4AC;
    /* 0x4B0 */ int      field_4B0;
    /* 0x4B4 */ int      field_4B4;
    /* 0x4B8 */ KCB      kcb[ 1 ];

    /* 0x4E4 */ char pad4B8[ 0x1c ];

    /* 0x500 */ TEXT    text[ 1 ];
    /* 0x5E0 */ int     font_x;
    /* 0x5E4 */ int     clut_x;
    /* 0x5E8 */ int     font_y;
    /* 0x5EC */ int     clut_y;
    /* 0x5F0 */ int     select;
    /* 0x5F4 */ int     count;
    /* 0x5F8 */ int     field_5F8;
} Work;

/*---------------------------------------------------------------------------*/

extern u_char rank_dword_800CBA7C[ 4 ];

const char rank_dword_800E09A0[] = "PLAY TIME /";
const char rank_dword_800E09AC[] = "%d";
const char rank_dword_800E09B0[] = ":";
const char rank_dword_800E09B4[] = "SAVE /";
const char rank_dword_800E09BC[] = "TIMES";
const char rank_dword_800E09C4[] = "CONTINUE /";
const char rank_dword_800E09D0[] = "BEING FOUND /";
const char rank_dword_800E09E0[] = "ENEMIES /";
const char rank_dword_800E09EC[] = "KILLED";
const char rank_dword_800E09F4[] = "RATIONS /";
const char rank_dword_800E0A00[] = "USED";
const char rank_dword_800E0A08[] = "GAME LEVEL /";
const char rank_dword_800E0A18[] = "VERY EASY";
const char rank_dword_800E0A24[] = "EASY";
const char rank_dword_800E0A2C[] = "NORMAL";
const char rank_dword_800E0A34[] = "HARD";
const char rank_dword_800E0A3C[] = "EXTREME";
const char rank_dword_800E0A44[] = "USED ITEM /";
const char rank_dword_800E0A50[] = "STEALTH";
const char rank_dword_800E0A58[] = "BANDANA";
const char rank_dword_800E0A60[] = "USED ITEMS /";
const char rank_dword_800E0A70[] = "CODE NAME";
const char rank_dword_800E0A7C[] = "SPECIAL ITEMS";
const char rank_dword_800E0A8C[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0A90 = 0x800D6BC8;
const int rank_dword_800E0A94 = 0x800D6BD4;
const int rank_dword_800E0A98 = 0x800D6BE0;
const int rank_dword_800E0A9C = 0x800D6BEC;
const int rank_dword_800E0AA0 = 0x800D6BF8;
const char rank_dword_800E0AA4[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0AA8 = 0x800D6D3C;
const int rank_dword_800E0AAC = 0x800D6D48;
const int rank_dword_800E0AB0 = 0x800D6D54;
const int rank_dword_800E0AB4 = 0x800D6D60;
const int rank_dword_800E0AB8 = 0x800D6D6C;
const char rank_dword_800E0ABC[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0AC0 = 0x800D6EF8;
const int rank_dword_800E0AC4 = 0x800D6F04;
const int rank_dword_800E0AC8 = 0x800D6F10;
const int rank_dword_800E0ACC = 0x800D6F1C;
const int rank_dword_800E0AD0 = 0x800D6F28;
const char rank_dword_800E0AD4[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0AD8 = 0x800D89BC;
const int rank_dword_800E0ADC = 0x800D89C8;
const int rank_dword_800E0AE0 = 0x800D89D4;
const int rank_dword_800E0AE4 = 0x800D89E0;
const int rank_dword_800E0AE8 = 0x800D89EC;
const char rank_dword_800E0AEC[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0AF0 = 0x800D8B30;
const int rank_dword_800E0AF4 = 0x800D8B3C;
const int rank_dword_800E0AF8 = 0x800D8B48;
const int rank_dword_800E0AFC = 0x800D8B54;
const int rank_dword_800E0B00 = 0x800D8B60;
const char rank_dword_800E0B04[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0B08 = 0x800D8CEC;
const int rank_dword_800E0B0C = 0x800D8CF8;
const int rank_dword_800E0B10 = 0x800D8D04;
const int rank_dword_800E0B14 = 0x800D8D10;
const int rank_dword_800E0B18 = 0x800D8D1C;
const char rank_dword_800E0B1C[] = "ERROR!!\n";
const char rank_dword_800E0B28[] = "Your Rank is %d\n";
const char rank_dword_800E0B3C[] = "big_back_l";
const char rank_dword_800E0B48[] = "big_back_r";
const char rank_dword_800E0B54[] = "mc_no = %d\n";
const char rank_dword_800E0B60[] = "radar stealth mugen = %d %d %d\n";
const char rank_dword_800E0B80[] = "spe_no = %d\n";
const char rank_dword_800E0B90[] = "camera stealth mugen = %d %d %d\n";
const char rank_dword_800E0BB4[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0BB8 = 0x800D9008;
const int rank_dword_800E0BBC = 0x800D9008;
const int rank_dword_800E0BC0 = 0x800D9010;
const int rank_dword_800E0BC4 = 0x800D9018;
const int rank_dword_800E0BC8 = 0x800D9020;
const char rank_dword_800E0BCC[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0BD0 = 0x800D9090;
const int rank_dword_800E0BD4 = 0x800D9090;
const int rank_dword_800E0BD8 = 0x800D9098;
const int rank_dword_800E0BDC = 0x800D90A0;
const int rank_dword_800E0BE0 = 0x800D90A8;
const char rank_dword_800E0BE4[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0BE8 = 0x800D9100;
const int rank_dword_800E0BEC = 0x800D9100;
const int rank_dword_800E0BF0 = 0x800D9108;
const int rank_dword_800E0BF4 = 0x800D9110;
const int rank_dword_800E0BF8 = 0x800D9118;
const char rank_dword_800E0BFC[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C00 = 0x800D9180;
const int rank_dword_800E0C04 = 0x800D9180;
const int rank_dword_800E0C08 = 0x800D9188;
const int rank_dword_800E0C0C = 0x800D9190;
const int rank_dword_800E0C10 = 0x800D9198;
const char rank_dword_800E0C14[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C18 = 0x800D91F0;
const int rank_dword_800E0C1C = 0x800D91F0;
const int rank_dword_800E0C20 = 0x800D91F8;
const int rank_dword_800E0C24 = 0x800D9200;
const int rank_dword_800E0C28 = 0x800D9208;
const char rank_dword_800E0C2C[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C30 = 0x800D9264;
const int rank_dword_800E0C34 = 0x800D9264;
const int rank_dword_800E0C38 = 0x800D926C;
const int rank_dword_800E0C3C = 0x800D9274;
const int rank_dword_800E0C40 = 0x800D927C;
const char rank_dword_800E0C44[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C48 = 0x800D92D8;
const int rank_dword_800E0C4C = 0x800D92D8;
const int rank_dword_800E0C50 = 0x800D92E0;
const int rank_dword_800E0C54 = 0x800D92E8;
const int rank_dword_800E0C58 = 0x800D92F0;
const char rank_dword_800E0C5C[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C60 = 0x800D9354;
const int rank_dword_800E0C64 = 0x800D9354;
const int rank_dword_800E0C68 = 0x800D935C;
const int rank_dword_800E0C6C = 0x800D9364;
const int rank_dword_800E0C70 = 0x800D936C;
const char rank_dword_800E0C74[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C78 = 0x800D93BC;
const int rank_dword_800E0C7C = 0x800D93BC;
const int rank_dword_800E0C80 = 0x800D93C4;
const int rank_dword_800E0C84 = 0x800D93CC;
const int rank_dword_800E0C88 = 0x800D93D4;
const char rank_dword_800E0C8C[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0C90 = 0x800D9418;
const int rank_dword_800E0C94 = 0x800D9418;
const int rank_dword_800E0C98 = 0x800D9420;
const int rank_dword_800E0C9C = 0x800D9428;
const int rank_dword_800E0CA0 = 0x800D9430;
const char rank_dword_800E0CA4[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0CA8 = 0x800D9488;
const int rank_dword_800E0CAC = 0x800D9488;
const int rank_dword_800E0CB0 = 0x800D9490;
const int rank_dword_800E0CB4 = 0x800D9498;
const int rank_dword_800E0CB8 = 0x800D94A0;
const char rank_dword_800E0CBC[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0CC0 = 0x800D94F0;
const int rank_dword_800E0CC4 = 0x800D94F0;
const int rank_dword_800E0CC8 = 0x800D94F8;
const int rank_dword_800E0CCC = 0x800D9500;
const int rank_dword_800E0CD0 = 0x800D9508;
const char rank_dword_800E0CD4[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0CD8 = 0x800D954C;
const int rank_dword_800E0CDC = 0x800D954C;
const int rank_dword_800E0CE0 = 0x800D9554;
const int rank_dword_800E0CE4 = 0x800D955C;
const int rank_dword_800E0CE8 = 0x800D9688;
const char rank_dword_800E0CEC[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0CF0 = 0x800D95AC;
const int rank_dword_800E0CF4 = 0x800D95AC;
const int rank_dword_800E0CF8 = 0x800D95B4;
const int rank_dword_800E0CFC = 0x800D95BC;
const int rank_dword_800E0D00 = 0x800D95C4;
const char rank_dword_800E0D04[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0D08 = 0x800D9614;
const int rank_dword_800E0D0C = 0x800D9614;
const int rank_dword_800E0D10 = 0x800D961C;
const int rank_dword_800E0D14 = 0x800D9624;
const int rank_dword_800E0D18 = 0x800D962C;
const char rank_dword_800E0D1C[] = {0x0, 0x0, 0x0, 0x0};
const int rank_dword_800E0D20 = 0x800D9670;
const int rank_dword_800E0D24 = 0x800D9670;
const int rank_dword_800E0D28 = 0x800D9678;
const int rank_dword_800E0D2C = 0x800D9680;
const int rank_dword_800E0D30 = 0x800D9688;

/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D4CB8.s")
void rank_800D4CB8( Work *work, int );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D4E2C.s")
void rank_800D4E2C( Work *work, int );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D4F70.s")
void rank_800D4F70( Work *work, u_long *ot );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D51EC.s") // done
void rank_800D51EC( Work *work, int, int );

void *rank_800D523C( KCB *kcb )
{
    return kcb->cbuffer;
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D5248.s") // done
void rank_800D5248( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D536C.s")
void rank_800D536C( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D705C.s")
void rank_800D705C( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D8E64.s")

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D8EE4.s")
void rank_800D8EE4( Work *work );

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800D98D4.s") // do_cursor
void rank_800D98D4( Work *work, int, int, int, int, int, int );

void rank_800D9BB8( Work *work )
{
    int time, shade, flag;
    POLY_FT4 *p;

    time = work->time;
    p = work->pol;

    if ( time < 9 )
    {
        int y;

        work->z[ 2 ] = 768;
        work->z[ 3 ] = 768;

        y = 206 - time * 30;
        setXYWH( &p[ 2 ], y, -17, 68, 12 );

        y = time * 30 - 274;
        setXYWH( &p[ 3 ], y, -17, 68, 12 );

        if ( time == 1 ) GM_SeSet2( 0, 63, SE_MENU_RANKING );
    }
    else if ( time < 13 )
    {
        /* do nothing */
    }
    else if ( time < 17 )
    {
        shade = ( time - 12 ) * 255 / 4;
        rank_800D98D4( work, -34, -17, 68, 12, shade, 0 );
    }
    else if ( time < 25 )
    {
        shade = 255;
        rank_800D98D4( work, -34, -17, 68, 12, shade, 0 );
    }
    else if ( time < 29 )
    {
        shade = 255 - ( time - 24 ) * 255 / 4;
        rank_800D98D4( work, -34, -17, 68, 12, shade, 0 );
    }
    else if ( time < 33 )
    {
        int y;

        y = -17 - ( time - 28 ) * 20;
        setXYWH( &p[ 2 ], -34, y, 68, 12 );
        setXYWH( &p[ 3 ], -34, y, 68, 12 );
    }
    else if ( time < 43 )
    {
        int s;

        work->z[ 0 ] = 768;
        work->z[ 1 ] = 768;
        work->z[ 2 ] = 256;
        work->z[ 3 ] = 256;

        setXYWH( &p[ 0 ], -160, -112, 160, 224 );
        setXYWH( &p[ 1 ], 0, -112, 160, 224 );

        s = ( time - 32 ) * 64 / 10;
        setRGB0( &p[ 0 ], s, s, s );
        setRGB0( &p[ 1 ], s, s, s );
    }
    else
    {
        work->state = 1;
        work->z[ 4 ] = 256;
        work->z[ 5 ] = 256;

        switch ( work->field_498 )
        {
        case 0:
            setXYWH( &p[ 4 ], 125, -63, 4, 71 );
            setXYWH( &p[ 5 ], -125, -63, 4, 71 );
            break;
        case 1:
            setXYWH( &p[ 4 ], 125, -63, 4, 68 );
            setXYWH( &p[ 5 ], -125, -63, 4, 68 );
            break;
        case 2:
            setXYWH( &p[ 4 ], 125, -67, 4, 79 );
            setXYWH( &p[ 5 ], -125, -67, 4, 79 );
            break;
        case 3:
            setXYWH( &p[ 4 ], 125, -73, 4, 89 );
            setXYWH( &p[ 5 ], -125, -73, 4, 89 );
            break;
        }

        work->z[ 12 ] = 256;
        {
            int x;

            x = rank_dword_800CBA7C[ work->field_494 ];
            setXY4( &p[ 12 ], -x + 40, 30, x + 40, 30, -x + 40, 38, x + 40, 38 );
        }

        if ( work->field_4A8 == 1 )
        {
            if ( work->field_4AC == 1 )
            {
                work->z[ 13 ] = 256;
                setXYWH( &p[ 13 ], -34, 65, 68, 9 );
            }
            else if ( work->field_4B0 == 1 )
            {
                work->z[ 14 ] = 256;
                setXYWH( &p[ 14 ], -38, 65, 76, 9 );
            }
            else if ( work->field_4B4 == 1 )
            {
                work->z[ 15 ] = 256;
                setXYWH( &p[ 15 ], -38, 75, 76, 9 );
            }
        }
        else if ( work->field_4A8 == 2 )
        {
            flag = 0;

            if ( work->field_4AC == 1 )
            {
                flag = 1;
                work->z[ 13 ] = 256;
                setXYWH( &p[ 13 ], -34, 65, 68, 9 );
            }

            if ( work->field_4B0 == 1 )
            {
                work->z[ 14 ] = 256;

                if ( flag == 0 )
                {
                    setXYWH( &p[ 14 ], -38, 65, 76, 9 );
                }
                else
                {
                    setXYWH( &p[ 14 ], -38, 77, 76, 9 );
                }
            }

            if ( work->field_4B4 == 1 )
            {
                work->z[ 15 ] = 256;
                setXYWH( &p[ 15 ], -38, 77, 76, 9 );
            }
        }
        else if ( work->field_4A8 == 0 )
        {
            work->z[ 13 ] = 0;
            work->z[ 14 ] = 0;
            work->z[ 15 ] = 0;
        }
        else
        {
            work->z[ 13 ] = 256;
            work->z[ 14 ] = 256;
            work->z[ 15 ] = 256;
            setXYWH( &p[ 13 ], -34, 65, 68, 9 );
            setXYWH( &p[ 14 ], -38, 77, 76, 9 );
            setXYWH( &p[ 15 ], -38, 89, 76, 9 );
        }
    }
}

void rank_800DA1DC( Work *work )
{
    if ( work->pad->press )
    {
        work->state = 2;
        work->time = 0;
    }
}

void rank_800DA204( Work *work )
{
    int time, r, g, b, i;
    POLY_FT4 *p;

    time = work->time;
    p = work->pol;

    if ( time <= 32 )
    {
        r = 64 - time * 2;
        g = 64 - time * 2;
        b = 64 - time * 2;
        setRGB0( &p[ 0 ], r, g, b );
        setRGB0( &p[ 1 ], r, g, b );

        r = 46 - time * 46 / 32;
        g = 72 - time * 72 / 32;
        b = 61 - time * 61 / 32;
        setRGB0( &p[ 2 ], r, g, b );
        setRGB0( &p[ 3 ], r, g, b );

        r = 82 - time * 82 / 32;
        g = 140 - time * 140 / 32;
        b = 123 - time * 123 / 32;
        setRGB0( &p[ 4 ], r, g, b );
        setRGB0( &p[ 5 ], r, g, b );

        r = 140 - time * 140 / 32;
        g = 181 - time * 181 / 32;
        b = 181 - time * 181 / 32;
        setRGB0( &p[ 6 ], r, g, b );
        setRGB0( &p[ 7 ], r, g, b );
        setRGB0( &p[ 8 ], r, g, b );
        setRGB0( &p[ 9 ], r, g, b );
        setRGB0( &p[ 10 ], r, g, b );
        setRGB0( &p[ 11 ], r, g, b );

        r = 165 - time * 165 / 32;
        g = 74 - time * 74 / 32;
        b = 74 - time * 74 / 32;
        setRGB0( &p[ 12 ], r, g, b );

        r = 74 - time * 74 / 32;
        g = 107 - time * 107 / 32;
        b = 148 - time * 148 / 32;
        setRGB0( &p[ 13 ], r, g, b );
        setRGB0( &p[ 14 ], r, g, b );
        setRGB0( &p[ 15 ], r, g, b );
    }
    else
    {
        for ( i = 0; i < 16; i++ )
        {
            work->z[ i ] = 0;
        }

        rank_800D51EC( work, 0, 0 );

        work->state = 3;
        work->select = 0;
        work->count = 0;

        if ( GM_GameLevel == GM_LEVEL_VERYEASY )
        {
            GCL_ExecProc( work->time_proc, NULL );
            GV_DestroyActor( work );
        }
    }
}

void rank_800DA504( Work *work )
{
    int i;

    for ( i = 0; i < 9; i++ )
    {
        work->z_cur[ i ] = 0;
    }
}

void DrawSaveDialog( Work *work )
{
    u_long *ot;
    u_short press;

    ot = DG_Chanl( 1 )->ot[ GV_Clock ];
    press = work->pad->press;

    switch ( work->select )
    {
    case 0:
        if ( work->count < 5 )
        {
            MENU_Locate( 45, 90, 0x10 );
            MENU_Color( 86, 137, 116 );
            MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

            rank_800D98D4( work, -115, -27, 230, 15, 255, 1 );
        }
        else if ( work->count < 10 )
        {
            MENU_Locate( 45, 90 - ( work->count - 4 ) * 8, 0x10 );
            MENU_Color( 86, 137, 116 );
            MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

            rank_800D98D4( work, -115, -27, 230, 15, 255, 1 );
        }
        else if ( work->count < 11 )
        {
            MENU_Locate( 45, 50, 0x10 );
            MENU_Color( 86, 137, 116 );
            MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

            MENU_Locate( 100, 105, 0x10 );
            MENU_Color( 192, 192, 192 );
            MENU_Printf( "YES" );

            MENU_Locate( 200, 105, 0x10 );
            MENU_Color( 46, 72, 61 );
            MENU_Printf( "NO" );

            rank_800D98D4( work, -115, -27, 230, 15, 255, 1 );
        }
        else if ( work->count < 14 )
        {
            MENU_Locate( 45, 50, 0x10 );
            MENU_Color( 86, 137, 116 );
            MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

            MENU_Locate( 100, 105, 0x10 );
            MENU_Color( 192, 192, 192 );
            MENU_Printf( "YES" );

            MENU_Locate( 200, 105, 0x10 );
            MENU_Color( 46, 72, 61 );
            MENU_Printf( "NO" );

            rank_800D98D4( work, ( work->count - 10 ) * 47 / 3 - 115, ( work->count - 10 ) * 5 - 27, 230 - ( work->count - 10 ) * 190 / 3, 15, 255, 1 );
        }
        else
        {
            work->select = 1;

            MENU_Locate( 45, 50, 0x10 );
            MENU_Color( 86, 137, 116 );
            MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

            MENU_Locate( 100, 105, 0x10 );
            MENU_Color( 192, 192, 192 );
            MENU_Printf( "YES" );

            MENU_Locate( 200, 105, 0x10 );
            MENU_Color( 46, 72, 61 );
            MENU_Printf( "NO" );

            rank_800D98D4( work, -68, -12, 40, 15, 255, 1 );
            rank_800D51EC( work, 0, 0x6739 );
        }
        break;
    case 1:
        MENU_Locate( 45, 50, 0x10 );
        MENU_Color( 86, 137, 116 );
        MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

        MENU_Locate( 100, 105, 0x10 );
        MENU_Color( 192, 192, 192 );
        MENU_Printf( "YES" );

        MENU_Locate( 200, 105, 0x10 );
        MENU_Color( 46, 72, 61 );
        MENU_Printf( "NO" );

        rank_800D98D4( work, -68, -12, 40, 15, 255, 1 );

        if ( press & PAD_RIGHT )
        {
            work->select = 2;
            GM_SeSet2( 0, 63, SE_MENU_CURSOR );
        }
        else if ( press & PAD_CIRCLE )
        {
            GCL_ExecProc( work->end_proc, NULL );
            GV_DestroyActor( work );
        }
        else if ( press & PAD_CROSS )
        {
            GM_SeSet2( 0, 63, SE_MENU_EXIT );
            work->state = 4;
            work->time = 0;
            rank_800DA504( work );
        }
        break;
    case 2:
        MENU_Locate( 45, 50, 0x10 );
        MENU_Color( 86, 137, 116 );
        MENU_Printf( "SAVE COMPLETED MISSION DATA?" );

        MENU_Locate( 100, 105, 0x10 );
        MENU_Color( 46, 72, 61 );
        MENU_Printf( "YES" );

        MENU_Locate( 200, 105, 0x10 );
        MENU_Color( 192, 192, 192 );
        MENU_Printf( "NO" );

        rank_800D98D4( work, 28, -12, 40, 15, 255, 1 );

        if ( press & PAD_LEFT )
        {
            work->select = 1;
            GM_SeSet2( 0, 63, SE_MENU_CURSOR );
        }
        else if ( press & PAD_CIRCLE )
        {
            GM_SeSet2( 0, 63, SE_MENU_EXIT );
            work->state = 4;
            work->time = 0;
            rank_800DA504( work );
        }
        else if ( press & PAD_CROSS )
        {
            GM_SeSet2( 0, 63, SE_MENU_EXIT );
            work->state = 4;
            work->time = 0;
            rank_800DA504( work );
        }
        break;
    }

    rank_800D4F70( work, ot );
    work->count++;
}

void DrawFadeOut( Work *work )
{
    u_long *ot;
    int shade, color, i;

    ot = DG_Chanl( 1 )->ot[ GV_Clock ];

    shade = 25 - work->time * 25 / 16;
    color = shade << 10 | shade << 5 | shade;

    if ( work->time <= 16 )
    {
        for ( i = 0; i < 1; i++ )
        {
            rank_800D51EC( work, i, color );
        }
    }
    else
    {
        GCL_ExecProc( work->time_proc, NULL );
        GV_DestroyActor( work );
    }

    rank_800D4F70( work, ot );
}

static void Act( Work *work )
{
    switch ( work->state )
    {
    case 0:
        rank_800D9BB8( work );
        break;
    case 1:
        rank_800D536C( work );
        rank_800DA1DC( work );
        break;
    case 2:
        rank_800DA204( work );
        rank_800D705C( work );
        break;
    case 3:
        DrawSaveDialog( work );
        break;
    case 4:
        DrawFadeOut( work );
        break;
    }

    rank_800D5248( work );
    work->time++;
}

static void Die( Work *work )
{
    int i;
    void *buffer;

    GM_FreePrim( work->prim );
    GM_FreePrim( work->prim_cur );

    for ( i = 0; i < 1; i++ )
    {
        buffer = rank_800D523C( &work->kcb[ i ] );
        GV_FreeMemory( GV_NORMAL_MEMORY, buffer );
    }
}

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800DAD08.s") // done, Init_Res_NT

#pragma INCLUDE_ASM("asm/overlays/rank/rank_800DAD78.s") // done, Init_Res
void rank_800DAD78( Work *work, int, POLY_FT4 *, int, int, int, int, int, int );

int rank_800DAEFC( Work *work, int map )
{
    POLY_FT4 *po;
    int i;

    GM_CurrentMap = map;

    work->font_x = 896;
    work->clut_x = 256;
    work->font_y = 896;
    work->clut_y = 276;

    work->prim = GM_MakePrim( DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 16, NULL, NULL );
    work->prim_cur = GM_MakePrim( DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, NULL, NULL );

    po = work->pol;
    i = 0;

    rank_800DAD78( work, GV_StrCode( "back_l" ), po, -160, -112, 0, 112, 0, 0 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "back_r" ), po, 0, -112, 160, 112, 0, 0 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_rank" ), po, -34, -94, 34, -82, 1, 0 );
    setRGB0( po, 46, 72, 61 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_rank" ), po, -34, -94, 34, -82, 1, 0 );
    setRGB0( po, 46, 72, 61 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line1" ), po, 125, -57, 129, 13, 0, 1 );
    setRGB0( po, 82, 140, 123 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line1" ), po, -125, -57, -121, 13, 0, 1 );
    setRGB0( po, 82, 140, 123 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line2" ), po, 8, -52, 90, -51, 0, 2 );
    setRGB0( po, 140, 181, 181 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line2" ), po, 8, -38, 44, -37, 0, 2 );
    setRGB0( po, 140, 181, 181 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line2" ), po, 8, -24, 44, -23, 0, 2 );
    setRGB0( po, 140, 181, 181 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line2" ), po, 8, -10, 44, -9, 0, 2 );
    setRGB0( po, 140, 181, 181 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line2" ), po, 8, 4, 44, 5, 0, 2 );
    setRGB0( po, 140, 181, 181 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_line2" ), po, 8, 18, 44, 19, 0, 2 );
    setRGB0( po, 140, 181, 181 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_fox" ), po, -22, 34, 22, 42, 0, 0 );
    setRGB0( po, 165, 74, 74 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_spe_camera" ), po, -22, 33, 22, 42, 0, 0 );
    setRGB0( po, 74, 107, 148 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_spe_stealth" ), po, -22, 33, 22, 42, 0, 0 );
    setRGB0( po, 74, 107, 148 );
    po++;
    work->z[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "rank_spe_mugen" ), po, -22, 33, 22, 42, 0, 0 );
    setRGB0( po, 74, 107, 148 );
    po++;
    work->z[ i ] = 0;
    i++;

    po = work->pol_cur;
    i = 0;

    rank_800DAD78( work, GV_StrCode( "cur_lu" ), po, 0, 0, 0, 0, 1, 0 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_ru" ), po, 0, 0, 0, 0, 1, 0 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_ld" ), po, 0, 0, 0, 0, 1, 0 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_rd" ), po, 0, 0, 0, 0, 1, 0 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_u" ), po, 0, 0, 0, 0, 1, 2 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_d" ), po, 0, 0, 0, 0, 1, 2 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_l" ), po, 0, 0, 0, 0, 1, 1 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_r" ), po, 0, 0, 0, 0, 1, 1 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    rank_800DAD78( work, GV_StrCode( "cur_c" ), po, 0, 0, 0, 0, 1, 3 );
    po++;
    work->z_cur[ i ] = 0;
    i++;

    work->pad = &GV_PadData[ 2 ];

    if ( GCL_GetOption( 'x' ) )
    {
        work->field_5F8 = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->field_5F8 = 0;
    }

    if ( GCL_GetOption( 'e' ) )
    {
        work->end_proc = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->end_proc = -1;
    }

    if ( GCL_GetOption( 't' ) )
    {
        work->time_proc = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        work->time_proc = -1;
    }

    for ( i = 0; i < 1; i++ )
    {
        work->text[ i ].string = GCL_GetString( GCL_NextStr() );
        work->text[ i ].num = 0;
        rank_800D4CB8( work, i );
    }

    for ( i = 0; i < 1; i++ )
    {
        rank_800D4E2C( work, i );
        rank_800D51EC( work, i, 0 );
    }

    if ( work->field_5F8 == 0 )
    {
        work->time = 0;
        work->state = 0;

        work->play_hours = GM_PlayTimeHours;
        work->play_minutes = GM_PlayTimeSeconds / 60;
        work->play_seconds = GM_PlayTimeSeconds % 60;

        work->field_498 = 0;
        work->field_49C = 0;
        work->field_4A0 = 0;
        work->field_4A4 = 0;
        work->field_4A8 = 0;
        work->field_4AC = 0;
        work->field_4B0 = 0;
        work->field_4B4 = 0;

        work->count = 0;
        rank_800D8EE4( work );
    }
    else if ( work->field_5F8 == 1 )
    {
        for ( i = 0; i < 16; i++ )
        {
            work->z[ i ] = 0;
        }

        rank_800D51EC( work, 0, 0 );
        work->state = 3;

        work->select = 0;
        work->count = 0;
    }

    rank_800D5248( work );
    return 0;
}

void *NewRanking( int name, int where )
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor( GV_ACTOR_MANAGER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "rank.c" );
        if ( rank_800DAEFC( work, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
