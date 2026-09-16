#include "game/game.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    /* 0x000 */ GV_ACT actor;
    /* 0x020 */ char   pad20[ 0x330 ];
} Work;

int s11a_dword_800C3270 = 0x00000101;
int s11a_dword_800C3274 = 0x000001FF;
int s11a_dword_800C3278 = 0x00780078;
int s11a_dword_800C327C = 0x00F000F0;
int s11a_dword_800C3280 = 0x012D012D;
int s11a_dword_800C3284 = 0x0000012D;

const char s11a_dword_800D77F8[] = "cam_arm";
const char s11a_dword_800D7800[] = "camera_l";
const char s11a_dword_800D780C[] = "s_camera";

/*---------------------------------------------------------------------------*/

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4A30.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4A5C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4AB0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4B3C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4C34.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4CC4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4D28.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4D94.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4EB4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4F2C.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C4FA4.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5044.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5188.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C52C8.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5370.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5480.s")

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C54FC.s")
void s11a_800C54FC( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C58C0.s")
void s11a_800C58C0( Work *work, int, int );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5AE0.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5B50.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5BC8.s")
#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5CB0.s")
int s11a_800C5CB0( Work *work, int name, int where );

#pragma INCLUDE_ASM("asm/overlays/s11a/s11a_800C5E24.s")
void s11a_800C5E24( Work *work );

void *NewCamera2( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(Work) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, s11a_800C54FC, s11a_800C5E24, "camera2.c" );
        if ( s11a_800C5CB0( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        s11a_800C58C0( work, name, where );
    }
    return (Work *)work;
}
