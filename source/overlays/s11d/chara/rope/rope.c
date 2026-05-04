#include "common.h"
#include "game/camera.h"
#include "game/target.h"
#include "game/vibrate.h"

typedef struct _RopeWork
{
    GV_ACT actor;
    char   pad0[0x28 - sizeof(GV_ACT)];
    short  field_28;
    short  field_2A;
    short  field_2C;
    char   pad1[0x6E - 0x2C - sizeof(short)];
    short  field_6E;
    char   pad2[0x804 - 0x6E - sizeof(short)];
    TARGET *target;
    char   pad3a[0xEA8 - 0x804 - sizeof(TARGET *)];
    short *field_EA8;
    char   pad3b[0xEB4 - 0xEA8 - sizeof(short *)];
    int    field_EB4;
    char   pad3c[0xEDC - 0xEB4 - sizeof(int)];
    int    field_EDC;
    char   pad3d[0xF70 - 0xEDC - sizeof(int)];
    int    field_F70;
    char   pad4[0xF7C - 0xF70 - sizeof(int)];
    int    field_F7C;
} RopeWork;

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3D50.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3DF0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3E50.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4274.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C42F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4404.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C44A4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C44F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4574.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C45F8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4648.s")
extern UnkCameraStruct gUnkCameraStruct_800B77B8;

void s11d_rope_800C481C(RopeWork *work)
{
    gUnkCameraStruct_800B77B8.rotate.vy = work->field_EDC / 48 + 0x800;
    GM_CameraSetRotation(&gUnkCameraStruct_800B77B8.rotate);
}
void s11d_rope_800C486C(RopeWork *work)
{
    TARGET *target = work->target;
    work->field_F7C = 32;
    work->field_F70 |= 0x8000;
    target->class &= ~(TARGET_POWER | TARGET_SEEK);

}
void s11d_rope_800C4898(RopeWork *work, int arg1)
{
    TARGET *target = work->target;
    work->field_F7C = arg1;
    work->field_F70 |= 0x8000;
    target->class &= ~(TARGET_POWER | TARGET_SEEK);
}
void s11d_rope_800C48C0(RopeWork *work)
{
    TARGET *target = work->target;
    work->field_F70 &= ~0x8000;
    target->class |= (TARGET_POWER | TARGET_SEEK);
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C48EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4B78.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4ECC.s")
int s11d_rope_800C4F84(RopeWork *work)
{
    unsigned short v = *work->field_EA8;

    if (!(v & 0xA000))
    {
        return 0;
    }

    if (v & 0x2000)
    {
        work->field_EB4 = 1;
    }
    else
    {
        work->field_EB4 = -1;
    }
    return 1;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4FC8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C502C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5298.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C52F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5348.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5410.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C54CC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5538.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5584.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5B10.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5E74.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C61D8.s")
void s11d_rope_800C6240(RopeWork *work)
{
    work->field_6E = 0x800;
    work->field_2C = 0;
    work->field_28 = 0;
    work->field_F70 &= ~0x80;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6264.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C62E0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C634C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6478.s")
extern int s11d_dword_800C32B4;
extern int s11d_dword_800C32B8;

void s11d_rope_800C650C(void)
{
    NewPadVibration((unsigned char *)&s11d_dword_800C32B4, 1);
    NewPadVibration((unsigned char *)&s11d_dword_800C32B8, 2);
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6544.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6834.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C697C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6B18.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6CD4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6F28.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7138.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7320.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7530.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C766C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7A4C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7B2C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7D20.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7EC4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7F8C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8200.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8250.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8364.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C868C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C879C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C882C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C04.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C88.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8EE4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8FDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C90BC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C9134.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C91AC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C9500.s")
