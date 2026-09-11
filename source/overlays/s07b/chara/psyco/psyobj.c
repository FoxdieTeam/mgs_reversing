#include "chara/psyco/psyco.h"

#include "game/game.h"

typedef struct _Work {
    GV_ACT  actor;
    char    pad20[ 0x154 ];
    u_short field_174;
    char    pad176[ 0x34 ];
} Work;

int s07b_dword_800C3454 = 0x00000000;
int s07b_dword_800C3458 = 0x00000000;
int s07b_dword_800C345C = 0xFFFFFFFF;
int s07b_dword_800C3460 = 0xFFFFFFFF;
int s07b_dword_800C3464 = 0x00000000;
int s07b_dword_800C3468 = 0x00000000;
int s07b_dword_800C346C = 0x00000000;
int s07b_dword_800C3470 = 0x00000000;
int s07b_dword_800C3474 = 0x00000000;
int s07b_dword_800C3478 = 0x00000000;
int s07b_dword_800C347C = 0x00000024;

const char s07b_dword_800E5110[] = "timeout %d\n";
const char s07b_dword_800E511C[] = "07b_o11";
const char s07b_dword_800E5124[] = "shadow";

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D27A8.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D28EC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2988.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2A0C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2A50.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2A64.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2C3C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2C4C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2C5C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2C6C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2CB4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2CEC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2CFC.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2D48.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2DC4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2E14.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D2F2C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D30B4.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3308.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3494.s")

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3634.s")
void s07b_800D3634( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3760.s")
void s07b_800D3760( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D385C.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3A18.s")
#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3C68.s")

#pragma INCLUDE_ASM("asm/overlays/s07b/s07b_800D3DC0.s")
int s07b_800D3DC0( Work *work, int arg0, int arg1 );

void *NewPsychoObject( int arg0, int arg1 )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, s07b_800D3634, s07b_800D3760, "psyobj.c" );
        if ( s07b_800D3DC0( work, arg0, arg1 ) < 0 )
        {
            GV_DestroyActor( work );
            if ( work->field_174 == 0xFFFF ) return (void *)work;
            return NULL;
        }
    }
    return (void *)work;
}
