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
    char   pad2a[0x9C - 0x6E - sizeof(short)];
    DG_OBJS *field_9C;
    char   pad2b[0x804 - 0x9C - sizeof(DG_OBJS *)];
    TARGET *target;
    char   pad3a[0xEA4 - 0x804 - sizeof(TARGET *)];
    short *field_EA4;
    short *field_EA8;
    char   pad3b[0xEB4 - 0xEA8 - sizeof(short *)];
    int    field_EB4;
    char   pad3c[0xEC8 - 0xEB4 - sizeof(int)];
    int    field_EC8;
    int    field_ECC;
    int    field_ED0;
    char   pad3c1[0xED8 - 0xED0 - sizeof(int)];
    int    field_ED8;
    char   pad3c2[0xEDC - 0xED8 - sizeof(int)];
    int    field_EDC;
    char   pad3c3[0xEE8 - 0xEDC - sizeof(int)];
    int    field_EE8;
    int    field_EEC;
    int    field_EF0;
    int    field_EF4;
    char   pad3c4[0xF04 - 0xEF4 - sizeof(int)];
    int    field_F04;
    int    field_F08;
    int    field_F0C;
    char   pad3c5[0xF14 - 0xF0C - sizeof(int)];
    int    field_F14;
    char   pad3c6a[0xF20 - 0xF14 - sizeof(int)];
    int    field_F20;
    char   pad3c6b[0xF24 - 0xF20 - sizeof(int)];
    int    field_F24;
    int    field_F28;
    int    field_F2C;
    int    field_F30;
    char   pad3d0[0xF60 - 0xF30 - sizeof(int)];
    int    field_F60;
    int    field_F64;
    int    field_F68;
    char   pad3d1[0xF70 - 0xF68 - sizeof(int)];
    int    field_F70;
    int    field_F74;
    int    field_F78;
    int    field_F7C;
    char   pad5[0xF88 - 0xF7C - sizeof(int)];
    short  field_F88;
} RopeWork;

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3D50.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3DF0.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3E50.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4274.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C42F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4404.s")
void s11d_rope_800C44A4(RopeWork *work)
{
    int flag = work->field_F74 & ~2;

    work->field_F74 = flag;
    if (work->field_F70 & 0x2000)
    {
        return;
    }
    if (work->field_EA4[2] > work->field_F88)
    {
        work->field_F74 = flag | 2;
    }
}
extern GM_CameraSystemWork GM_Camera;

void s11d_rope_800C44F0(RopeWork *work)
{
    int counter = work->field_F78;
    int next;

    if (counter == 0)
    {
        return;
    }
    if (counter > 0)
    {
        if (GM_Camera.first_person != 0)
        {
            return;
        }
        next = counter - 1;
        work->field_F78 = next;
        if (next != 0)
        {
            return;
        }
        work->field_9C->flag &= ~DG_FLAG_INVISIBLE;
    }
    else
    {
        if (GM_Camera.first_person == 0)
        {
            return;
        }
        next = counter + 1;
        work->field_F78 = next;
        if (next != 0)
        {
            return;
        }
        work->field_9C->flag |= DG_FLAG_INVISIBLE;
    }
}
typedef struct {
    unsigned short field_00;
    short          pad_02[4];
    short          field_0A;
    unsigned char  field_0C[4];
} RopeEA8Rec;

void s11d_rope_800C4574(RopeWork *work)
{
    RopeEA8Rec    *rec;
    unsigned char *bytes;
    int            i;

    work->field_F74 &= ~0x8000;

    rec = (RopeEA8Rec *)work->field_EA8;
    if (rec->field_0A == 0)
    {
        return;
    }
    if (!(rec->field_00 & 0xF000))
    {
        return;
    }

    bytes = rec->field_0C;
    for (i = 0; i < 4; i++)
    {
        if ((unsigned char)(*bytes - 0x40) >= 0x81)
        {
            work->field_F74 |= 0x8000;
            return;
        }
        bytes++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C45F8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4648.s")
extern GM_SnakeCameraWork GM_SnakeCamera;

void s11d_rope_800C481C(RopeWork *work)
{
    GM_SnakeCamera.rotate.vy = work->field_EDC / 48 + 0x800;
    GM_CameraSetRotation(&GM_SnakeCamera.rotate);
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
int s11d_rope_800C4FC8(RopeWork *work)
{
    unsigned short v;

    v = *work->field_EA8;
    if (!(v & 0x2000))
    {
        if (work->field_EB4 == 1)
        {
            return 1;
        }
    }

    v = *work->field_EA8;
    if ((v & 0x8000) == 0 && work->field_EB4 == -1)
    {
        return 1;
    }
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C502C.s")
int s11d_rope_800C5298(RopeWork *work)
{
    int flag = work->field_F74;

    if (!(flag & 0x4000))
    {
        return 0;
    }
    if (flag & 0x1000)
    {
        return 0;
    }
    if (flag & 0x400000)
    {
        return 0;
    }
    if (*work->field_EA8 & 0x20)
    {
        work->field_F74 = flag | 0x400000;
        return 1;
    }
    return 0;
}
int s11d_rope_800C52F0(RopeWork *work)
{
    unsigned short v;

    if (work->field_F74 & 0x2000)
    {
        return 0;
    }

    v = *work->field_EA8;
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
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5348.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5410.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C54CC.s")

void s11d_rope_800C5538(RopeWork *work)
{
    int *cluster1 = &work->field_EC8;  /* offsets EC8..EF4 */
    int *cluster2 = &work->field_F04;  /* offsets F04..F30 */

    cluster2[1]  = 0;  /* field_F08 */
    cluster1[1]  = 0;  /* field_ECC */
    cluster1[8]  = 0;  /* field_EE8 */
    cluster1[4]  = 0;  /* field_ED8 */
    cluster1[2]  = 0;  /* field_ED0 */
    cluster1[0]  = 0;  /* field_EC8 */
    cluster2[8]  = 0;  /* field_F24 */
    cluster2[4]  = 0;  /* field_F14 */
    cluster2[2]  = 0;  /* field_F0C */
    cluster2[0]  = 0;  /* field_F04 */
    cluster1[11] = 0;  /* field_EF4 */
    cluster1[10] = 0;  /* field_EF0 */
    cluster1[9]  = 0;  /* field_EEC */
    cluster2[11] = 0;  /* field_F30 */
    cluster2[10] = 0;  /* field_F2C */
    cluster2[9]  = 0;  /* field_F28 */
}
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
void s11d_rope_800C62E0(RopeWork *work)
{
    int *p_F04 = &work->field_F04;

    if (work->field_F74 & 0x4000)
    {
        return;
    }
    p_F04[2] = (work->field_F74 & 0x10) ? 1 : -1;
    p_F04[0] = 0x30;
    work->field_F74 |= 0x200;
    p_F04[1] = p_F04[7];
    work->field_F60 = -8;
    work->field_F68 = -8;
    if (work->field_F74 & 0x1000)
    {
        work->field_F64 = -8;
    }
}
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
