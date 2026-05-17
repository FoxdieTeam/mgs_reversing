#include "common.h"
#include "game/camera.h"
#include "game/control.h"
#include "game/game.h"
#include "game/target.h"
#include "game/vibrate.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "linkvar.h"

struct RopeA14Rec
{
    char  pad_00[0x2A];
    short field_2A;
};

typedef struct _RopeWork
{
    GV_ACT  actor;
    SVECTOR field_20;
    short   field_28;
    short  field_2A;
    short  field_2C;
    char   pad1a[0x36 - 0x2C - sizeof(short)];
    short  field_36;
    short  field_38;
    char   pad1b1[0x66 - 0x38 - sizeof(short)];
    short  field_66;
    char   pad1b2[0x6C - 0x66 - sizeof(short)];
    short  field_6C;
    short  field_6E;
    short  field_70;
    char   pad2a1[0x98 - 0x70 - sizeof(short)];
    short  field_98;
    char   pad2a2[0x9C - 0x98 - sizeof(short)];
    DG_OBJS *field_9C;
    char   pad2b1[0xAA - 0x9C - sizeof(DG_OBJS *)];
    short  field_AA;
    char   pad2b2[0xB6 - 0xAA - sizeof(short)];
    short  field_B6;
    char   pad2b[0x7DC - 0xB6 - sizeof(short)];
    DG_OBJS *field_7DC;
    char   pad2c[0x804 - 0x7DC - sizeof(DG_OBJS *)];
    TARGET *target;
    char   pad3a1[0xA14 - 0x804 - sizeof(TARGET *)];
    struct RopeA14Rec *field_A14;
    char   pad3a2[0xEA0 - 0xA14 - sizeof(struct RopeA14Rec *)];
    int    field_EA0;
    short *field_EA4;
    short *field_EA8;
    int    field_EAC;
    int    field_EB0;
    int    field_EB4;
    char   pad3c0[0xEBC - 0xEB4 - sizeof(int)];
    short  field_EBC;
    short  field_EBE;
    char   pad3c[0xEC8 - 0xEBC - sizeof(short) * 2];
    int    field_EC8;
    int    field_ECC;
    int    field_ED0;
    int    field_ED4;
    int    field_ED8;
    int    field_EDC;
    int    field_EE0;
    int    field_EE4;
    int    field_EE8;
    int    field_EEC;
    int    field_EF0;
    int    field_EF4;
    int    field_EF8;
    int    field_EFC;
    int    field_F00;
    int    field_F04;
    int    field_F08;
    int    field_F0C;
    int    field_F10;
    int    field_F14;
    int    field_F18;
    int    field_F1C;
    int    field_F20;
    int    field_F24;
    int    field_F28;
    int    field_F2C;
    int    field_F30;
    int    field_F34;
    int    field_F38;
    int    field_F3C;
    char   pad3d00[0xF50 - 0xF3C - sizeof(int)];
    SVECTOR field_F50;
    SVECTOR field_F58;
    char   pad3d01[0xF60 - 0xF58 - sizeof(SVECTOR)];
    int    field_F60;
    int    field_F64;
    int    field_F68;
    char   pad3d1[0xF6C - 0xF68 - sizeof(int)];
    int    field_F6C;
    int    field_F70;
    int    field_F74;
    int    field_F78;
    int    field_F7C;
    char   pad5[0xF88 - 0xF7C - sizeof(int)];
    short  field_F88;
    char   pad6a1[0xF94 - 0xF88 - sizeof(short)];
    short  field_F94;
    char   pad6a2[0xF98 - 0xF94 - sizeof(short)];
    short  field_F98;
    char   pad6a3[0xF9C - 0xF98 - sizeof(short)];
    int    field_F9C;
    int    field_FA0;
    int    field_FA4[16];
    SVECTOR field_FE4[16];
    char   pad6a4[0x107C - 0xFE4 - sizeof(SVECTOR) * 16];
    int    field_107C[3];
    int    field_1088[4];
} RopeWork;

int s11d_rope_800C3D50(CONTROL *control, int arg1)
{
    if (arg1 == 0)
    {
        return 0;
    }

    HZD_PointNearSurface(control->nears);
    HZD_PointNearVec(control->nearvecs);

    if (control->nearvecs[0].vx != 0)
    {
        arg1--;
        if (arg1 == 1)
        {
            control->nearvecs[0] = control->nearvecs[1];
            control->nears[0] = control->nears[1];
            if (control->nearvecs[0].vx != 0)
            {
                arg1 = 0;
            }
        }
    }
    return arg1;
}
void s11d_rope_800C3DF0(CONTROL *control, HZD_HDL *hzd)
{
    if (!(control->skip_flag & CTRL_SKIP_TRAP))
    {
        control->event.pos = control->mov;
        control->event.pos.pad = control->rot.vy;
        HZD_EnterTrap(hzd, &control->event);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3E50.s")
void s11d_rope_800C4274(RopeWork *work)
{
    DG_SetPos2(&work->field_20, (SVECTOR *)&work->field_28);
    if (work->field_F70 & 0x80)
    {
        SVECTOR vec;
        vec.vz = 0;
        vec.vx = 0;
        vec.vy = work->field_6E;
        GV_NearExp4PV(&work->field_F58, &vec, 3);
        DG_SetPos2(&work->field_20, &work->field_F58);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C42F4.s")
extern void s11d_rope_800C7138(RopeWork *work);

void s11d_rope_800C4404(RopeWork *work)
{
    int target_y;
    int delta;
    int field_98_val;

    if (work->field_F60 < 0)
    {
        return;
    }
    if (work->field_EAC == (int)s11d_rope_800C7138)
    {
        return;
    }

    field_98_val = work->field_98;

    if (work->target->size.vy == 200)
    {
        target_y = work->field_20.vy - 250;
    }
    else
    {
        target_y = work->field_20.vy - 950;
    }

    delta = target_y - field_98_val;

    if (delta > 0 && delta < 500)
    {
        work->field_20.vy -= delta;
        return;
    }
    if (delta >= 0)
    {
        return;
    }
    if (delta < -499)
    {
        return;
    }
    work->field_20.vy += delta;
}
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
void s11d_rope_800C45F8(RopeWork *work)
{
    int diff = 3000 - work->field_20.vy;

    if (diff < 0)
    {
        work->field_A14->field_2A = 0x20;
        return;
    }
    diff /= 500;
    work->field_A14->field_2A = 0x20 - diff;
}
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
int s11d_rope_800C4DE0(RopeWork *work)
{
    int            flags;
    int            newflags;
    unsigned short ea8_val;

    flags = work->field_F74;
    newflags = flags & 0xFEFDFFFF;
    work->field_F74 = newflags;

    if (!(flags & 0x10))
    {
        return 0;
    }
    if (newflags & 0x00200000)
    {
        return 0;
    }
    if (work->field_F6C >= 0)
    {
        return 0;
    }

    work->field_F74 = newflags | 0x00200000;
    work->field_EB4 = 0;

    ea8_val = *work->field_EA8;
    if (ea8_val & 0x2000)
    {
        work->field_EB4 = 1;
    }
    else if (ea8_val & 0x8000)
    {
        work->field_EB4 = -1;
    }

    ea8_val = *work->field_EA8;
    if (ea8_val & 0x4000)
    {
        work->field_F74 |= 0x00020000;
    }
    else if (ea8_val & 0x1000)
    {
        work->field_F74 |= 0x01000000;
    }

    if (work->field_F7C != 0)
    {
        return 1;
    }
    s11d_rope_800C4898(work, 0);
    return 1;
}
void s11d_rope_800C4ECC(RopeWork *work)
{
    int flags = work->field_F70;

    if (flags & 0x6033)
    {
        return;
    }

    if (*work->field_EA8 & 0x10)
    {
        if (GM_Camera.first_person == 0)
        {
            work->field_F70 = flags | 0x1000;
            work->field_F78 = -4;
            GM_Camera.first_person = 1;
            work->field_F50 = GM_SnakeCamera.rotate2;
        }
    }
    else
    {
        if (GM_Camera.first_person != 0)
        {
            work->field_F70 = flags & ~0x1000;
            work->field_F78 = 4;
            GM_Camera.first_person = 0;
        }
    }
}
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
extern const char s11d_aTosi_800D1D5C[];

void s11d_rope_800C5348(RopeWork *work)
{
    int     code;
    u_short *names;
    int     count;
    TARGET *target;

    code = GV_StrCode(s11d_aTosi_800D1D5C);

    names = (u_short *)&work->field_38;
    count = work->field_36;
    target = work->target;

    while (count > 0)
    {
        count--;
        if (*names == code)
        {
            s11d_rope_800C4898(work, 0);
            target->vital += target->damage;
            target->damage = 0;
            target->faint = 0;
            target->damaged &= ~4;
            target->force = DG_ZeroVector;
            return;
        }
        names++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5410.s")
extern CONTROL *GM_WhereList[96];
extern int gControlCount_800AB9B4;

void s11d_rope_800C54CC(RopeWork *work)
{
    CONTROL **wherelist;
    int      i;
    u_short  target_name;
    CONTROL *ctrl;

    if (work->field_EA4)
    {
        return;
    }
    if (!work->field_EA0)
    {
        return;
    }

    wherelist = GM_WhereList;
    i = gControlCount_800AB9B4;
    target_name = (u_short)work->field_EA0;
    if (i <= 0)
    {
        return;
    }
    do
    {
        ctrl = *wherelist++;
        if (ctrl->name == target_name)
        {
            work->field_EA4 = (short *)ctrl;
            return;
        }
    } while (--i > 0);
}

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
extern SVECTOR s11d_dword_800C32BC;
extern SVECTOR s11d_dword_800C32C4;
extern void NewBlood(MATRIX *mat, int count);

void s11d_rope_800C61D8(RopeWork *work, int idx)
{
    MATRIX *mat;
    MATRIX  sp10;

    mat = &work->field_9C->objs[idx].world;

    DG_SetPos(mat);
    DG_MovePos(&s11d_dword_800C32BC);
    DG_RotatePos(&s11d_dword_800C32C4);
    ReadRotMatrix(&sp10);
    NewBlood(&sp10, 1);
}
void s11d_rope_800C6240(RopeWork *work)
{
    work->field_6E = 0x800;
    work->field_2C = 0;
    work->field_28 = 0;
    work->field_F70 &= ~0x80;
}
void s11d_rope_800C6264(RopeWork *work)
{
    int *cluster = &work->field_EC8;   /* [0]=EC8 [1]=ECC [2]=ED0 [5]=EDC [7]=EE4 */
    int  val = cluster[7];
    int  abs_val = (val < 0) ? -val : val;
    int  flag;

    if (abs_val < 0x21)
    {
        return;
    }

    cluster[2] = (cluster[5] > 0) ? -1 : 1;
    cluster[0] = 0x18;
    cluster[1] = cluster[7];
    work->field_F60 = -8;
    flag = work->field_F74 | 0x100;
    work->field_F74 = flag;
    if (flag & 0x1000)
    {
        work->field_F64 = -8;
    }
}
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
void s11d_rope_800C6478(RopeWork *work)
{
    if (work->field_EA8[1] & 0x40)
    {
        work->field_F6C = -8;
    }
    if (work->field_F6C < 0)
    {
        work->field_F6C += 1;
    }
    if (!(work->field_EA8[0] & 0x40))
    {
        work->field_F74 &= ~0x200000;
    }
    if (!(work->field_EA8[0] & 0x20))
    {
        work->field_F74 &= ~0x400000;
    }
}
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
extern void s11d_rope_800C6834(RopeWork *work);

void s11d_rope_800C7A4C(RopeWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 = (work->field_F74 & 0xFF9FFFFF) | 0x00010000;
        GM_SeSetMode(&work->field_20, 25, 1);
        work->field_F70 |= 0x100;
        if (work->field_AA != 9)
        {
            GM_ConfigObjectAction((OBJECT *)&work->field_9C, 9, 0, 4);
        }
        work->field_6E = 0x800;
        s11d_rope_800C4898(work, 0);
    }
    if (work->field_B6 != 0)
    {
        s11d_rope_800C486C(work);
        work->field_EAC = (int)s11d_rope_800C6834;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        work->field_F70 &= ~0x100;
    }
    work->field_66 -= 0x80;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7B2C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7D20.s")
extern SVECTOR GM_PlayerPosition;

void s11d_rope_800C7EC4(RopeWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 |= 0x02000000;
        work->field_70 = 0;
        work->field_6C = 0;
        GM_SnakeCurrentHealth = 0;
        if (work->field_AA != 14)
        {
            GM_ConfigObjectAction((OBJECT *)&work->field_9C, 14, 0, 4);
        }
    }
    work->field_66 -= 0x20;
    if (arg1 == 8)
    {
        GM_PlayerPosition = work->field_20;
    }
    if (arg1 == 24)
    {
        GM_GameOver();
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7F8C.s")
extern void GM_GameOver(void);

void s11d_rope_800C8200(RopeWork *work, int arg1)
{
    if (arg1 != 0)
    {
        return;
    }
    work->field_9C->flag |= DG_FLAG_INVISIBLE;
    *(int *)&work->field_7DC->def |= 0x100;
    GM_GameOver();
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8250.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8364.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C868C.s")
extern int     s11d_dword_800C32CC;
extern SVECTOR DG_ZeroVector;

int s11d_rope_800C879C(RopeWork *work)
{
    TARGET *target;
    int     vital;

    work->target = target = GM_AllocTarget();
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, 0x15, 1, (SVECTOR *)&s11d_dword_800C32CC);

    vital = GM_SnakeMaxHealth;
    GM_SetPowerTarget(target, 1, -1, vital, 0, &DG_ZeroVector);
    GM_SnakeCurrentHealth = vital;

    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C882C.s")
void s11d_rope_800C8C04(RopeWork *work)
{
    int *cluster1;
    int *cluster2;

    s11d_rope_800C5538(work);

    cluster1 = &work->field_EC8;
    cluster2 = &work->field_F04;

    cluster1[6]  = 0;                                  /* field_EE0 */
    cluster1[5]  = 0;                                  /* field_EDC */
    cluster2[6]  = 0;                                  /* field_F1C */
    cluster2[5]  = 0;                                  /* field_F18 */
    cluster1[3]  = 0x18;                               /* field_ED4 */
    cluster2[3]  = 0x40;                               /* field_F10 */
    cluster1[12] = work->field_F94;                    /* field_EF8 */
    cluster2[12] = work->field_F98;                    /* field_F34 */
    cluster1[13] = (int)&work->field_20;               /* field_EFC */
    cluster2[13] = (int)&work->field_20.vz;            /* field_F38 */
    cluster1[14] = (int)&work->field_70;               /* field_F00 */
    cluster2[14] = (int)&work->field_6C;               /* field_F3C */
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C88.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8EE4.s")
int s11d_rope_800C8FDC(RopeWork *work)
{
    int      i;
    int      j;
    SVECTOR *p1;
    int     *p2;

    i = 0;
    j = 0;

    if (GCL_GetOption('c'))
    {
        p1 = work->field_FE4;
        while (GCL_GetParamResult())
        {
            if (j == 16)
            {
                break;
            }
            GCL_StrToSV(GCL_GetParamResult(), p1);
            p1++;
            j++;
        }
    }

    if (GCL_GetOption('h'))
    {
        unsigned char *param;
        p2 = work->field_FA4;
        while ((param = GCL_GetParamResult()))
        {
            if (i == 16)
            {
                break;
            }
            *p2 = GCL_StrToInt(param);
            p2++;
            i++;
        }
    }

    work->field_F9C = j;
    work->field_FA0 = 0;
    return 0;
}
void s11d_rope_800C90BC(RopeWork *work)
{
    int  *p;
    int   i;
    unsigned char *param;

    if (!GCL_GetOption('w'))
    {
        return;
    }

    i = 0;
    p = work->field_107C;
    while ((param = GCL_GetParamResult()))
    {
        if (i == 3)
        {
            return;
        }
        *p = GCL_StrToInt(param);
        p++;
        i++;
    }
}
void s11d_rope_800C9134(RopeWork *work)
{
    int  *p;
    int   i;
    unsigned char *param;

    if (!GCL_GetOption('v'))
    {
        return;
    }

    i = 0;
    p = work->field_1088;
    while ((param = GCL_GetParamResult()))
    {
        if (i == 4)
        {
            return;
        }
        *p = GCL_StrToInt(param);
        p++;
        i++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C91AC.s")
extern const char s11d_dword_800D1DC4[];
extern void s11d_rope_800C8364(RopeWork *work);
extern void s11d_rope_800C868C(RopeWork *work);
extern int  s11d_rope_800C91AC(RopeWork *work, int arg1, int arg2);

RopeWork *s11d_rope_800C9500(int arg0, int arg1)
{
    RopeWork *work = GV_NewActor(5, sizeof(RopeWork));
    if (work == NULL)
    {
        return NULL;
    }
    GV_SetNamedActor(work, s11d_rope_800C8364, s11d_rope_800C868C, s11d_dword_800D1DC4);
    if (s11d_rope_800C91AC(work, arg0, arg1) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }
    return work;
}
