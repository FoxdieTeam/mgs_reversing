#include "animal/zako11a/zako.h"

#include <stdio.h>

/*---------------------------------------------------------------------------*/

typedef struct _PATTERN {
    short field_0;
    short set;
    short field_4;
    short field_6;
} PATTERN;

int s11a_dword_800C3574 = 0x00001676;
int s11a_dword_800C3578 = 0x0000FC18;
int s11a_dword_800C357C = 0x0000186A;
int s11a_dword_800C3580 = 0x000001F4;
int s11a_dword_800C3584 = 0x00001676;
int s11a_dword_800C3588 = 0x000007D0;

static PATTERN ActionPattern[ 32 ][ 4 ] = {
    { { 1, 0, 1, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1, 63 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1, 16 }, { 3, 1, 1, 20 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1, 29 }, { 3, 1, 1, 32 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 3, 1, 1, 41 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1, 47 }, { 3, 1, 1, 49 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 0, 2, 0, 255 } },
    { { 0, 2, 1, 255 }, { 0, 2, 1, 255 }, { 0, 2, 1, 255 }, { 0, 2, 1, 255 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};

SVECTOR s11a_dword_800C398C = {600, 1500, 600};
SVECTOR s11a_dword_800C3994 = {0, 0, 0};
SVECTOR s11a_dword_800C399C = {500, 500, 500};
SVECTOR s11a_dword_800C39A4 = {100, 0, 0};

int s11a_dword_800C39AC = 0x00000057;
int s11a_dword_800C39B0 = 0x0000003D;
int s11a_dword_800C39B4 = 0x0000003E;

/*---------------------------------------------------------------------------*/

void s11a_800D0364( Work *work )
{
    work->target_addr = ZAKO11A_PlayerAddress;
    work->target_pos = ZAKO11A_PlayerPosition;
    work->target_map = ZAKO11A_PlayerMap;
}

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D03AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0408.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0474.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0490.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0578.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D05F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D061C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0648.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D07C4.s")
void s11a_800D07C4( Work *work, int );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0818.s")
void s11a_800D0818( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0868.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D08A0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0A98.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0B38.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0BA0.s")
int s11a_800D0BA0( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0C2C.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0CB4.s")
int s11a_800D0CB4( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0D48.s")

const char s11a_dword_800D8238[] = ",ID[%d] Flag[%d] RESET ZONE [%d]\n";
const char s11a_dword_800D825C[] = "kirari01";

const int s11a_dword_800D8268 = 0x800D0E54;
const int s11a_dword_800D826C = 0x800D0E84;
const int s11a_dword_800D8270 = 0x800D0E74;
const int s11a_dword_800D8274 = 0x800D0E64;
const int s11a_dword_800D8278 = 0x800D0E94;
const int s11a_dword_800D827C = 0x800D0E94;
const int s11a_dword_800D8280 = 0x800D0E8C;
const int s11a_dword_800D8284 = 0x800D0E94;
const int s11a_dword_800D8288 = 0x800D0E94;
const int s11a_dword_800D828C = 0x800D0E5C;
const int s11a_dword_800D8290 = 0x800D0E94;
const int s11a_dword_800D8294 = 0x800D0E94;
const int s11a_dword_800D8298 = 0x800D0E94;
const int s11a_dword_800D829C = 0x800D0E94;
const int s11a_dword_800D82A0 = 0x800D0E94;
const int s11a_dword_800D82A4 = 0x800D0E94;
const int s11a_dword_800D82A8 = 0x800D0E94;
const int s11a_dword_800D82AC = 0x800D0E94;
const int s11a_dword_800D82B0 = 0x800D0E94;
const int s11a_dword_800D82B4 = 0x800D0E94;
const int s11a_dword_800D82B8 = 0x800D0E94;
const int s11a_dword_800D82BC = 0x800D0E94;
const int s11a_dword_800D82C0 = 0x800D0E94;
const int s11a_dword_800D82C4 = 0x800D0E6C;
const int s11a_dword_800D82C8 = 0x800D0E94;
const int s11a_dword_800D82CC = 0x800D0E94;
const int s11a_dword_800D82D0 = 0x800D0E94;
const int s11a_dword_800D82D4 = 0x800D0E94;
const int s11a_dword_800D82D8 = 0x800D0E94;
const int s11a_dword_800D82DC = 0x800D0E94;
const int s11a_dword_800D82E0 = 0x800D0E94;
const int s11a_dword_800D82E4 = 0x800D0E94;
const int s11a_dword_800D82E8 = 0x800D0E7C;

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0DE8.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0EB0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0F74.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D0FDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D103C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D10A0.s")

const char s11a_dword_800D82EC[] = {0x0, 0x0, 0x0, 0x0};

const int s11a_dword_800D82F0 = 0x800D1194;
const int s11a_dword_800D82F4 = 0x800D1208;
const int s11a_dword_800D82F8 = 0x800D11CC;
const int s11a_dword_800D82FC = 0x800D11DC;
const int s11a_dword_800D8300 = 0x800D11D4;

const char s11a_dword_800D8304[] = "N [%d] work->gameflag = %d\n";
const char s11a_dword_800D8320[] = "N GO GRAVEYARD !! \n";
const char s11a_dword_800D8334[] = " [%d] work->gameflag = %d\n";
const char s11a_dword_800D8350[] = " GO GRAVEYARD !! \n";

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D10E8.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D1230.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D1298.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D1328.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D13DC.s")
void s11a_800D13DC( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D142C.s")
void s11a_800D142C( Work *work );

const char s11a_dword_800D8364[] = {0x0, 0x0, 0x0, 0x0};

const int s11a_dword_800D8368 = 0x800D1574;
const int s11a_dword_800D836C = 0x800D158C;
const int s11a_dword_800D8370 = 0x800D17D0;
const int s11a_dword_800D8374 = 0x800D15A4;
const int s11a_dword_800D8378 = 0x800D15C4;
const int s11a_dword_800D837C = 0x800D15DC;
const int s11a_dword_800D8380 = 0x800D15F4;
const int s11a_dword_800D8384 = 0x800D160C;
const int s11a_dword_800D8388 = 0x800D16BC;
const int s11a_dword_800D838C = 0x800D1624;

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800D1524.s")
void s11a_800D1524( Work *work );

void s11a_800D1804( Work *work )
{
    int temp_v0;

    switch ( work->think3 )
    {
    case 5:
        s11a_800D0364( work );
        if ( s11a_800D0BA0( work ) )
        {
            work->think3 = 6;
            work->count3 = 0;
        }
        break;
    case 6:
        temp_v0 = s11a_800D0CB4( work );
        if ( temp_v0 < 0 )
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        else if ( temp_v0 > 0 )
        {
            work->think2 = 2;
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    }

    if ( work->player_dis < work->field_BFC && GM_PlayerStance == STAND )
    {
        work->think2 = 2;
        work->think3 = 16;
        work->count3 = 33;
        work->pad.press |= 0x10000;
    }

    if ( work->vision.pad == 2 ) work->alert_level = 255;
    ZAKO11ASetGopointLast();
}

void s11a_800D1904( Work *work )
{
    if ( work->think3 == 17 && s11a_800D0BA0( work ) )
    {
        work->think2 = 2;
        work->think3 = 15;
        work->count3 = 0;
    }

    if ( work->player_dis < 800 && GM_PlayerStance == STAND )
    {
        work->think2 = 2;
        work->think3 = 11;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
}

void s11a_800D1998( Work *work )
{
    switch ( work->think3 )
    {
    case 18:
        if ( work->gameflag != ZAKO11A_GameFlag )
        {
            int nextset;
            work->gameflag = ZAKO11A_GameFlag;
            nextset = ActionPattern[ ZAKO11A_GameFlag ][ work->param.index ].set;

            if ( nextset == 0 ) break;

            if ( nextset == 1 )
            {
                s11a_800D07C4( work, 2 );
                printf( " SET_QUICK !! \n" );
            }

            if ( nextset == 2 )
            {
                s11a_800D07C4( work, 1 );
                printf( " SET_CONTINUE !! \n" );
            }

            work->think2 = 2;
            work->think3 = 15;
            work->count3 = 0;
        }
        else
        {
            s11a_800D0818( work );
        }
        break;
    case 19:
        printf( " SET_NONE !! \n" );
        s11a_800D0818( work );
        work->think3 = 18;
        work->count3 = 0;
        break;
    }
}

void Think1_Phase0( Work *work )
{
    switch ( work->think2 )
    {
    case 0:
        s11a_800D13DC( work );
        break;
    case 1:
        s11a_800D1804( work );
        break;
    case 2:
        s11a_800D1524( work );
        break;
    case 3:
        s11a_800D1904( work );
        break;
    case 4:
        s11a_800D142C( work );
        break;
    case 5:
        s11a_800D1998( work );
        break;
    }
}

/*---------------------------------------------------------------------------*/

void Zako11AThink( Work *work )
{
    work->pad.dir = -1;
    work->pad.press = 0;

    work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT;

    if ( ZAKO11A_GameFlag > 0 && ZAKO11A_GameFlag < 10 )
    {
        work->alert_level = 255;
    }
    else if ( work->think3 != 18 && ZAKO11A_GameFlag == 10 )
    {
        work->alert_level = 255;
    }

    switch ( work->think1 )
    {
    case 0:
        work->act.field_1E = 1;
        Think1_Phase0( work );
        break;
    }
}
