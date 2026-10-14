#include "mgstype.h"
#include "game/camera.h"
#include "game/game.h"
#include "game/vibrate.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "okajima/blood.h"
#include "takabe/cineutil.h"
#include "chara/snake/shadow.h"

typedef struct _RopeAxis
{
    int    speed;       // 0x00
    int    saved_angle; // 0x04
    int    dir;         // 0x08
    int    step;        // 0x0C
    int    f10;         // 0x10
    int    dx;          // 0x14
    int    dz;          // 0x18
    int    angle;       // 0x1C
    int    f20;         // 0x20
    int    f24;         // 0x24
    int    f28;         // 0x28
    int    f2C;         // 0x2C
    int    target;      // 0x30
    short *pos;         // 0x34
    short *rot;         // 0x38
} RopeAxis;

typedef struct _Work
{
    GV_ACT      actor;
    CONTROL     control;
    OBJECT      object;
    char        pad_obj[0x180 - 0x9C - sizeof(OBJECT)];
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[17];
    MOTION_SEGMENT m_segs2[17];
    SVECTOR     rots[16];
    char        pad_718[0x79C - 0x718];
    MATRIX      light[2];
    DG_PRIM    *field_7DC;
    char        pad2c[0x800 - 0x7DC - sizeof(DG_PRIM *)];
    void       *field_800;
    TARGET     *target;
    SVECTOR     field_808;
    DG_PRIM    *field_810;
    char        pad3a1[0xA14 - 0x810 - sizeof(DG_PRIM *)];
    DG_PRIM    *field_A14;
    char        pad3a2[0xEA0 - 0xA14 - sizeof(DG_PRIM *)];
    int         field_EA0;
    CONTROL    *field_EA4;
    GV_PAD     *pad;
    int         field_EAC;
    int         field_EB0;
    int         field_EB4;
    int         field_EB8;
    char        pad3c0[0xEBC - 0xEB8 - sizeof(int)];
    short       field_EBC;
    short       field_EBE;
    short       field_EC0;
    short       field_EC2;
    char        pad3c[0xEC8 - 0xEC2 - sizeof(short)];
    RopeAxis    axis[2];
    int         field_F40;
    short       field_F44;
    char        pad_f46[2];
    int         field_F48;
    int         field_F4C;
    SVECTOR     field_F50;
    SVECTOR     field_F58;
    char        pad3d01[0xF60 - 0xF58 - sizeof(SVECTOR)];
    int         field_F60;
    int         field_F64;
    int         field_F68;
    char        pad3d1[0xF6C - 0xF68 - sizeof(int)];
    int         field_F6C;
    int         field_F70;
    int         field_F74;
    int         field_F78;
    int         field_F7C;
    char        pad5[0xF84 - 0xF7C - sizeof(int)];
    short       field_F84;
    short       field_F86;
    short       field_F88;
    char        pad6a0[0xF8C - 0xF88 - sizeof(short)];
    short       field_F8C;
    short       field_F8E;
    char        pad6a1[0xF94 - 0xF8E - sizeof(short)];
    short       field_F94;
    short       field_F96;
    short       field_F98;
    char        pad6a3[0xF9C - 0xF98 - sizeof(short)];
    int         field_F9C;
    int         field_FA0;
    int         field_FA4[16];
    SVECTOR     field_FE4[16];
    char        pad6a4[0x1078 - 0xFE4 - sizeof(SVECTOR) * 16];
    int         field_1078;
    int         field_107C[3];
    int         field_1088[4];
} Work;

#define TARGET_FLAG ( TARGET_AVAIL | TARGET_POWER | TARGET_SEEK )

u_char s11d_dword_800C3260[] = { 0x7F, 0x04, 0x00, 0x00 };
u_char s11d_dword_800C3264[] = { 0xE1, 0x01, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00 };
u_char s11d_dword_800C326C[] = { 0x7F, 0x06, 0x00, 0x00 };
u_char s11d_dword_800C3270[] = { 0xE1, 0x01, 0xFF, 0x04, 0xE1, 0x02, 0x4B, 0x08, 0x00, 0x00, 0x00, 0x00 };
u_char s11d_dword_800C327C[] = { 0x7F, 0x01, 0x00, 0x00 };
u_char s11d_dword_800C3280[] = { 0xAF, 0x04, 0x28, 0x03, 0x23, 0x03, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00 };
static u_char s11d_dword_800C328C[] = { 0x7F, 0x06, 0x00, 0x00 };
static u_char s11d_dword_800C3290[] = { 0xFF, 0x06, 0x00, 0x02, 0xA5, 0x06, 0x37, 0x08, 0x73, 0x02, 0x00, 0x00 };
u_char s11d_dword_800C329C[] = { 0x00, 0x01, 0x7F, 0x01, 0x00, 0x00, 0x00, 0x00 };
u_char s11d_dword_800C32A4[] = { 0x96, 0x02, 0x46, 0x04, 0x32, 0x03, 0x1E, 0x02, 0x00, 0x00, 0x00, 0x00 };
u_char s11d_dword_800C32B0[] = { 0xAA, 0x03, 0x00, 0x00 };
static u_char s11d_dword_800C32B4[] = { 0x7F, 0x01, 0x00, 0x00 };
static u_char s11d_dword_800C32B8[] = { 0xD2, 0x02, 0x00, 0x00 };
static SVECTOR s11d_dword_800C32BC = { 0, 0, 100 };
static SVECTOR s11d_dword_800C32C4 = { -1024, 0, 0 };
static SVECTOR target_size = { 300, 900, 300 };

extern int s11d_dword_800D1F7C;
extern int s11d_dword_800D1F80;
extern int s11d_dword_800D1F84;

extern const char s11d_aTosi_800D1D5C[]; // "to_s11i"

extern void TortureInfoKill(void);
extern void AN_DamageSmoke1(SVECTOR *world);

extern void s11d_rope_800C44A4(Work *work);
extern void s11d_rope_800C44F0(Work *work);
extern void s11d_rope_800C4574(Work *work);
extern void s11d_rope_800C45F8(Work *work);
extern void s11d_rope_800C4648(Work *work);
extern void s11d_rope_800C481C(Work *work);
extern void s11d_rope_800C48EC(Work *work);
extern void s11d_rope_800C4B78(Work *work);
extern void s11d_rope_800C4ECC(Work *work);
extern void s11d_rope_800C502C(Work *work);
extern void s11d_rope_800C5348(Work *work);
extern void s11d_rope_800C5410(void);
extern void s11d_rope_800C5584(Work *work, RopeAxis *axis, int index);
extern void s11d_rope_800C5B10(Work *work);
extern void s11d_rope_800C5E74(Work *work);
extern void s11d_rope_800C6478(Work *work);
extern void s11d_rope_800C6264(Work *work);
extern void s11d_rope_800C62E0(Work *work);
extern void s11d_rope_800C650C(void);
extern void s11d_rope_800C6544(Work *work, int arg1);
extern void s11d_rope_800C61D8(Work *work, int index);
extern void s11d_rope_800C6834(Work *work, int arg1);
extern void s11d_rope_800C7A4C(Work *work, int arg1);
extern void s11d_rope_800C7B2C(Work *work, int arg1);
extern void s11d_rope_800C7EC4(Work *work, int arg1);
extern void s11d_rope_800C7F8C(Work *work, int arg1);
extern void s11d_rope_800C697C(Work *work, int arg1);
extern void s11d_rope_800C6B18(Work *work, int arg1);

extern void s11d_rope_800C6F28(Work *work, int arg1);
extern void s11d_rope_800C7138(Work *work, int arg1);
extern void s11d_rope_800C7320(Work *work);
extern void s11d_rope_800C766C(Work *work);
extern void s11d_rope_800C8364(Work *work);
extern void s11d_rope_800C868C(Work *work);
extern int  s11d_rope_800C91AC(Work *work, int arg1, int arg2);

int s11d_rope_800C3D50(CONTROL *control, int arg1)
{
    if (arg1 == 0)
    {
        return 0;
    }

    HZD_GetNearHazard(control->segs);
    HZD_GetNearVector(control->vecs);

    if (control->vecs[0].vx != 0)
    {
        arg1--;
        if (arg1 == 1)
        {
            control->vecs[0] = control->vecs[1];
            control->segs[0] = control->segs[1];
            if (control->vecs[0].vx != 0)
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
        control->evt.coord = control->mov;
        control->evt.coord.pad = control->rot.vy;
        HZD_EnterTrap(hzd, &control->evt);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C3E50.s")

void s11d_rope_800C4274(Work *work)
{
    DG_SetPos2(&work->control.mov, &work->control.rot);
    if (work->field_F70 & 0x80)
    {
        SVECTOR vec;
        vec.vz = 0;
        vec.vx = 0;
        vec.vy = work->control.turn.vy;
        GV_NearExp4PV(&work->field_F58, &vec, 3);
        DG_SetPos2(&work->control.mov, &work->field_F58);
    }
}

void s11d_rope_800C42F4(DG_OBJS *objs, VECTOR *out)
{
    MATRIX   mat;
    MATRIX   rot;
    SVECTOR *rots;
    DG_OBJ  *obj;
    DG_MDL  *mdl;
    int      i;

    mat = objs->world;
    rots = objs->rots;
    obj = objs->objs;

    for (i = 0; i < 5; i++)
    {
        mdl = obj->model;
        RotMatrixZYX(rots, &rot);
        rot.t[0] = mdl->tx;
        rot.t[1] = mdl->ty;
        rot.t[2] = mdl->tz;
        CompMatrix(&mat, &rot, &mat);
        obj++;
        rots++;
    }

    out->vx = mat.t[0];
    out->vy = mat.t[1];
    out->vz = mat.t[2];
}

void s11d_rope_800C4404(Work *work)
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

    field_98_val = work->control.levels[0];

    if (work->target->size.vy == 200)
    {
        target_y = work->control.mov.vy - 250;
    }
    else
    {
        target_y = work->control.mov.vy - 950;
    }

    delta = target_y - field_98_val;

    if (delta > 0 && delta < 500)
    {
        work->control.mov.vy -= delta;
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
    work->control.mov.vy += delta;
}

void s11d_rope_800C44A4(Work *work)
{
    int flag = work->field_F74 & ~2;

    work->field_F74 = flag;
    if (work->field_F70 & 0x2000)
    {
        return;
    }
    if (work->field_EA4->mov.vz > work->field_F88)
    {
        work->field_F74 = flag | 2;
    }
}

void s11d_rope_800C44F0(Work *work)
{
    if (work->field_F78 != 0)
    {
        if (work->field_F78 > 0)
        {
            if (GM_Camera.first_person == 0 && --work->field_F78 == 0)
            {
                DG_VisibleObjs(work->object.objs);
            }
        }
        else
        {
            if (GM_Camera.first_person != 0 && ++work->field_F78 == 0)
            {
                DG_InvisibleObjs(work->object.objs);
            }
        }
    }
}

void s11d_rope_800C4574(Work *work)
{
    GV_PAD *pad;
    u_char *analog;
    int     i;

    work->field_F74 &= ~0x8000;

    pad = work->pad;
    if (pad->analog == 0)
    {
        return;
    }

    if (!(pad->status & PAD_UDLR))
    {
        return;
    }

    analog = &pad->right_dx;
    for (i = 0; i < 4; i++)
    {
        if ((u_char)(*analog - 64) > 128)
        {
            work->field_F74 |= 0x8000;
            break;
        }
        analog++;
    }
}

void s11d_rope_800C45F8(Work *work)
{
    int diff;

    diff = 3000 - work->control.mov.vy;
    if (diff < 0)
    {
        work->field_A14->prim_count = 32;
    }
    else
    {
        diff /= 500;
        work->field_A14->prim_count = 32 - diff;
    }
}

void s11d_rope_800C4648(Work *work)
{
    SVECTOR cam;
    SVECTOR diff;
    int     idx;
    int     next;

    if (work->field_EAC == (int)s11d_rope_800C6544)
    {
        return;
    }
    if (work->field_F70 & 0x1000)
    {
        return;
    }

    next = -1;
    idx = work->field_FA0;
    if (idx != work->field_F9C - 1)
    {
        next = idx + 1;
    }

    if (work->field_FA4[idx] < work->control.mov.vy)
    {
        if (idx > 0)
        {
            idx--;
        }
    }
    else if (next != -1)
    {
        next = idx + 1;
        if (work->control.mov.vy < work->field_FA4[next])
        {
            idx = next;
        }
    }

    work->field_FA0 = idx;

    cam = GM_SnakeCamera.rotate;
    cam.vz = GM_SnakeCamera.track;
    GV_SubVec3(&work->field_FE4[idx], &cam, &diff);

    if (abs(diff.vz) > 64)
    {
        diff.vz = (diff.vz > 0) ? 64 : -64;
    }
    GM_SnakeCamera.track += diff.vz;
    GM_CameraSetTrack(GM_SnakeCamera.track);

    diff.vz = 0;
    if (abs(diff.vx) > 8)
    {
        diff.vx = (diff.vx > 0) ? 8 : -8;
    }
    if (abs(diff.vy) > 8)
    {
        diff.vy = (diff.vy > 0) ? 8 : -8;
    }
    GV_AddVec3(&GM_SnakeCamera.rotate, &diff, &GM_SnakeCamera.rotate);
    GM_CameraSetRotation(&GM_SnakeCamera.rotate);
}

void s11d_rope_800C481C(Work *work)
{
    GM_SnakeCamera.rotate.vy = work->axis[0].dx / 48 + 2048;
    GM_CameraSetRotation(&GM_SnakeCamera.rotate);
}

void s11d_rope_800C486C(Work *work)
{
    TARGET *target = work->target;
    work->field_F7C = 32;
    work->field_F70 |= 0x8000;
    target->class &= ~(TARGET_POWER | TARGET_SEEK);

}

void s11d_rope_800C4898(Work *work, int arg1)
{
    TARGET *target = work->target;
    work->field_F7C = arg1;
    work->field_F70 |= 0x8000;
    target->class &= ~(TARGET_POWER | TARGET_SEEK);
}

void s11d_rope_800C48C0(Work *work)
{
    TARGET *target = work->target;
    work->field_F70 &= ~0x8000;
    target->class |= (TARGET_POWER | TARGET_SEEK);
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C48EC.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4B78.s")

int s11d_rope_800C4DE0(Work *work)
{
    int flags;
    int newflags;

    flags = work->field_F74;
    newflags = flags & ~0x1020000;
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

    if (work->pad->status & PAD_RIGHT)
    {
        work->field_EB4 = 1;
    }
    else if (work->pad->status & PAD_LEFT)
    {
        work->field_EB4 = -1;
    }

    if (work->pad->status & PAD_DOWN)
    {
        work->field_F74 |= 0x00020000;
    }
    else if (work->pad->status & PAD_UP)
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

void s11d_rope_800C4ECC(Work *work)
{
    int flags = work->field_F70;

    if (flags & 0x6033)
    {
        return;
    }

    if (work->pad->status & PAD_TRIANGLE)
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

int s11d_rope_800C4F84(Work *work)
{
    if (!(work->pad->status & (PAD_LEFT | PAD_RIGHT)))
    {
        return 0;
    }

    if (work->pad->status & PAD_RIGHT)
    {
        work->field_EB4 = 1;
    }
    else
    {
        work->field_EB4 = -1;
    }
    return 1;
}

int s11d_rope_800C4FC8(Work *work)
{
    if (!(work->pad->status & PAD_RIGHT) && work->field_EB4 == 1)
    {
        return 1;
    }

    if (!(work->pad->status & PAD_LEFT) && work->field_EB4 == -1)
    {
        return 1;
    }

    return 0;
}

void s11d_rope_800C502C(Work *work)
{
    RopeAxis *axis1 = &work->axis[0];
    RopeAxis *axis2 = &work->axis[1];
    int  action;
    int  pad;

    if (work->field_F74 & 0x10000)
    {
        work->field_F74 &= ~0x800000;
        work->field_EC2 = 0;
    }

    if (work->field_F74 & 0x800000)
    {
        if (work->object.action != 0xF)
        {
            GM_ConfigObjectAction(&work->object, 0xF, 0, 0);
        }

        work->field_EC2--;
        if (work->field_EC2 == 0)
        {
            work->field_F74 = (work->field_F74 & ~0x800000) | 0x100;
            if (axis1->dir != 0)
            {
                work->control.turn.vy = -(axis1->dir * 0x600);
            }
        }
    }

    if (work->field_F74 & 0x810000)
    {
        if (work->field_F74 & 0x10000)
        {
            work->field_F74 &= ~0xF00;
            axis1->speed = 0;
            axis1->dir = 0;
        }
        else
        {
            work->field_F74 &= ~0x500;
            axis2->speed = 0;
            axis2->dir = 0;
        }
    }
    else
    {
        if (!(work->field_F74 & 0x100))
        {
            s11d_rope_800C6264(work);
        }
        if (!(work->field_F74 & 0x200))
        {
            s11d_rope_800C62E0(work);
        }
    }

    if (work->field_F74 & 0x300)
    {
        action = work->object.action;
        if (action != 5 && action != 7 && action != 9)
        {
            if (action != 1)
            {
                GM_ConfigObjectAction(&work->object, 1, 0, 4);
            }

            pad = work->pad->status;
            if (pad & (PAD_LEFT | PAD_RIGHT))
            {
                work->control.turn.vy = (pad & PAD_LEFT) ? 0x600 : -0x600;
            }
        }
    }

    if (work->field_F74 & 0x100)
    {
        s11d_rope_800C5584(work, &work->axis[0], 0);
    }
    if (work->field_F74 & 0x200)
    {
        s11d_rope_800C5584(work, &work->axis[1], 1);
    }

    if (work->field_F74 & 0x400)
    {
        axis1->dir = 0;
        axis1->speed = 0;
        work->field_F74 &= ~0x400;
    }
    if (work->field_F74 & 0x800)
    {
        axis2->dir = 0;
        axis2->speed = 0;
        work->field_F74 &= ~0x800;
    }
}

int s11d_rope_800C5298(Work *work)
{
    if (!(work->field_F74 & 0x4000))
    {
        return 0;
    }

    if (work->field_F74 & 0x1000)
    {
        return 0;
    }

    if (work->field_F74 & 0x400000)
    {
        return 0;
    }

    if (work->pad->status & PAD_CIRCLE)
    {
        work->field_F74 |= 0x400000;
        return 1;
    }

    return 0;
}

int s11d_rope_800C52F0(Work *work)
{
    if (work->field_F74 & PAD_RIGHT)
    {
        return 0;
    }
    else if (!(work->pad->status & ( PAD_LEFT | PAD_RIGHT )))
    {
        return 0;
    }
    else if (work->pad->status & PAD_RIGHT)
    {
        work->field_EB4 = 1;
    }
    else
    {
        work->field_EB4 = -1;
    }

    return 1;
}

void s11d_rope_800C5348(Work *work)
{
    int     code;
    u_short *names;
    int     count;
    TARGET *target;

    code = GV_StrCode(s11d_aTosi_800D1D5C);

    names = work->control.evt.inside;
    count = work->control.evt.n_inside;
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

void s11d_rope_800C54CC(Work *work)
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
    i = GM_N_WhereList;
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
            work->field_EA4 = ctrl;
            return;
        }
    } while (--i > 0);
}

void s11d_rope_800C5538(Work *work)
{
    RopeAxis *axis1 = &work->axis[0];
    RopeAxis *axis2 = &work->axis[1];

    axis2->saved_angle = 0;
    axis1->saved_angle = 0;
    axis1->f20 = 0;
    axis1->f10 = 0;
    axis1->dir = 0;
    axis1->speed = 0;
    axis2->f20 = 0;
    axis2->f10 = 0;
    axis2->dir = 0;
    axis2->speed = 0;
    axis1->f2C = 0;
    axis1->f28 = 0;
    axis1->f24 = 0;
    axis2->f2C = 0;
    axis2->f28 = 0;
    axis2->f24 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5584.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5B10.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C5E74.s")

void s11d_rope_800C61D8(Work *work, int index)
{
    MATRIX *mat;
    MATRIX  sp10;

    mat = &work->object.objs->objs[index].world;

    DG_SetPos(mat);
    DG_MovePos(&s11d_dword_800C32BC);
    DG_RotatePos(&s11d_dword_800C32C4);
    ReadRotMatrix(&sp10);
    NewBlood(&sp10, 1);
}

void s11d_rope_800C6240(Work *work)
{
    work->control.turn.vy = 0x800;
    work->control.rot.vz = 0;
    work->control.rot.vx = 0;
    work->field_F70 &= ~0x80;
}

void s11d_rope_800C6264(Work *work)
{
    RopeAxis *axis = &work->axis[0];
    int       val = axis->angle;
    int       abs_val = (val < 0) ? -val : val;
    int       flag;

    if (abs_val < 0x21)
    {
        return;
    }

    axis->dir = (axis->dx > 0) ? -1 : 1;
    axis->speed = 0x18;
    axis->saved_angle = axis->angle;
    work->field_F60 = -8;
    flag = work->field_F74 | 0x100;
    work->field_F74 = flag;
    if (flag & 0x1000)
    {
        work->field_F64 = -8;
    }
}

void s11d_rope_800C62E0(Work *work)
{
    RopeAxis *axis = &work->axis[1];

    if (work->field_F74 & 0x4000)
    {
        return;
    }
    axis->dir = (work->field_F74 & 0x10) ? 1 : -1;
    axis->speed = 0x30;
    work->field_F74 |= 0x200;
    axis->saved_angle = axis->angle;
    work->field_F60 = -8;
    work->field_F68 = -8;
    if (work->field_F74 & 0x1000)
    {
        work->field_F64 = -8;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C634C.s")

void s11d_rope_800C6478(Work *work)
{
    if (work->pad->press & PAD_CROSS)
    {
        work->field_F6C = -8;
    }

    if (work->field_F6C < 0)
    {
        work->field_F6C++;
    }

    if (!(work->pad->status & PAD_CROSS))
    {
        work->field_F74 &= ~0x200000;
    }

    if (!(work->pad->status & PAD_CIRCLE))
    {
        work->field_F74 &= ~0x400000;
    }
}

void s11d_rope_800C650C(void)
{
    NewPadVibration(s11d_dword_800C32B4, 1);
    NewPadVibration(s11d_dword_800C32B8, 2);
}

void s11d_rope_800C6544(Work *work, int arg1)
{
    SVECTOR rot;
    int     vz;

    if (arg1 == 0)
    {
        work->field_F74 |= 0x10000;
        GM_GameStatus |= 0x10020000;
        OpenCinemaScreen(1, 0x7530);

        rot.vx = -0x2A8;
        rot.vy = 0x800;
        rot.vz = 0;
        GM_CameraSetRotation(&rot);
        GM_CameraSetTrack(0x8FC);

        work->field_F70 |= 2;
        if (work->object.action != 0x11)
        {
            GM_ConfigObjectAction(&work->object, 0x11, 0, 4);
        }

        work->field_EBE = 0x8FC;
        s11d_rope_800C4898(work, 0);
        GM_VoxInit();
        GM_VoxQueueDelay(work->field_1088[1], 4);
        work->field_810->raise = 500;
        work->field_A14->raise = 500;
    }

    GM_VoxTick();

    switch (work->field_EBC)
    {
    case 0:
        if (work->field_EBE < 0x3E80)
        {
            work->field_EBE += 0x60;
            GM_CameraSetTrack(work->field_EBE);
        }

        if (work->field_F74 & 0x2000)
        {
            work->field_810->raise = 0x5DC;
            work->field_A14->raise = 0x5DC;
            s11d_rope_800C650C();
            GM_SeSetMode(&work->control.mov, 0xB2, 1);
            if (work->object.action != 0xB)
            {
                GM_ConfigObjectAction(&work->object, 0xB, 0, 4);
            }
            work->field_EBE = 0;
            work->field_F44 = 0;
            work->field_EBC++;
        }

        work->control.step.vy -= 0xC;
        break;

    case 1:
        vz = work->field_F98;
        GV_NearExp4V(&work->control.mov.vz, &vz, 1);
        work->field_EBE++;
        if (work->field_EBE == 0x3C)
        {
            GCL_ExecProc(work->field_107C[0], NULL);
            work->field_EBC++;
        }
        break;

    case 2:
        work->field_EBE++;
        if (work->field_EBE == 0xBE)
        {
            GCL_ExecProc(work->field_107C[1], NULL);
        }
        if (work->field_EBE == 0xC4)
        {
            GM_SeSetMode(&work->field_EA4->mov, 0xBC, 1);
        }
        if (work->field_EBE == 0x64)
        {
            GM_VoxQueue(work->field_1088[3]);
        }
        if (work->field_EBE == 0x118)
        {
            GCL_ExecProc(work->field_107C[2], NULL);
            GM_GameStatus = (GM_GameStatus & 0xEFFDFFFF) | 0x8000;
            work->field_EAC = (int)s11d_rope_800C6834;
            work->field_EB0 = 0;
            work->field_EBE = 0;
            work->field_EBC = 0;
            CloseCinemaScreen();
            s11d_rope_800C48C0(work);
        }
        break;
    }
}
void s11d_rope_800C6834(Work *work, int arg1)
{
    short  vz;

    if (arg1 == 0)
    {
        work->field_F74 |= 0x10000;
        work->field_F58 = work->control.rot;
        work->field_F70 = (work->field_F70 & ~0xFF) | 0x80;
        work->field_F74 &= ~0xF00;
        s11d_rope_800C5538(work);
        if (work->object.action != 0xB)
        {
            GM_ConfigObjectAction(&work->object, 0xB, 0, 4);
        }
        work->field_F44 = 0;
    }

    vz = work->field_F98;
    GV_NearExp4V(&work->control.mov.vz, &vz, 1);

    if (s11d_rope_800C5298(work))
    {
        s11d_rope_800C6240(work);
        GM_SeSetMode(&work->control.mov, 0xb7, 1);
        work->field_EAC = (int)s11d_rope_800C6B18;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        return;
    }

    if (s11d_rope_800C4DE0(work))
    {
        s11d_rope_800C6240(work);
        work->field_EAC = (int)s11d_rope_800C766C;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        return;
    }

    if (s11d_rope_800C4F84(work))
    {
        work->field_EAC = (int)s11d_rope_800C697C;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        return;
    }

    work->control.step.vy -= 0x80;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C697C.s")

extern void s11d_rope_800C6CD4(Work *work, int arg1);
extern void s11d_rope_800C7530(Work *work, int arg1);
void s11d_rope_800C6B18(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 |= 0x10000;
        work->field_F70 = (work->field_F70 & ~0xFF) | 1;

    if (work->object.action != 7)
       {
            GM_ConfigObjectAction(&work->object, 7, 0, 4);
        }

        work->field_EB8 = 0;
        work->field_EB4 = 0;

        work->target->size.vy = 0xC8;
        work->control.turn.vy  = 0x800;
        work->field_F44 = 0x1C2;
    }

    if (arg1 < 4)
    {
        (work->field_EBC)++;
        work->control.step.vy += 0x50;
    }

    if (work->object.is_end != 0)
    {
        work->field_EAC = (int)s11d_rope_800C6CD4;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        return;
    }

    if (!(work->pad->status & PAD_CIRCLE))
    {
        work->field_F68 = -4;
        if (work->field_EBC >= 5)
        {
            work->field_EBC = 4;
        }
        work->field_EBE = 1;
    }

    if (work->field_EBE == 1)
    {
        int ebc;

        work->control.step.vy -= 0x50;
        ebc = (unsigned short)work->field_EBC - 1;
        work->field_EBC = ebc;

        if ((short)ebc == 0)
        {
            work->target->size.vy = 0x384;

            if ( work->field_F74 & 0x2000)
            {
                GM_SeSetMode(&work->control.mov, 0xb2, 1);
                s11d_rope_800C650C();
                work->field_EAC = (int)s11d_rope_800C6834;
            }
            else
            {
                work->field_EAC = (int)s11d_rope_800C7530;
            }

            work->field_EB0 = 0;
            work->field_EBE = 0;
            work->field_EBC = 0;
        }
    }

work->control.step.vz -= 0x6C;
}
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6CD4.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6F28.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7138.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7320.s")

void s11d_rope_800C7530(Work *work, int arg1)
{
    void *state_fn;

    if (arg1 == 0)
    {
        work->field_F74 &= ~0x10000;
        work->field_F70 &= ~0xFF;
        if (work->object.action != 1)
        {
            GM_ConfigObjectAction(&work->object, 1, 0, 4);
        }
        work->field_F44 = 0;
    }

    if (!(work->field_F74 & 0x300))
    {
        if (work->object.action != 1)
        {
            GM_ConfigObjectAction(&work->object, 1, 0, 4);
        }

        if (work->pad->status & PAD_LEFT)
        {
            work->control.turn.vy = 1536;
        }
        else if (work->pad->status & PAD_RIGHT)
        {
            work->control.turn.vy = -1536;
        }
    }

    if (work->field_F74 & 0x2000)
    {
        GM_SeSetMode(&work->control.mov, 0xb2, 1);
        s11d_rope_800C650C();
        state_fn = s11d_rope_800C6834;
    }
    else if (s11d_rope_800C5298(work))
    {
        state_fn = s11d_rope_800C6B18;
    }
    else if (s11d_rope_800C4DE0(work))
    {
        state_fn = s11d_rope_800C766C;
    }
    else
    {
        return;
    }

    work->field_EAC = (int)state_fn;
    work->field_EB0 = 0;
    work->field_EBE = 0;
    work->field_EBC = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C766C.s")

void s11d_rope_800C7A4C(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 = (work->field_F74 & 0xFF9FFFFF) | 0x00010000;
        GM_SeSetMode(&work->control.mov, 25, 1);
        work->field_F70 |= 0x100;
        if (work->object.action != 9)
        {
            GM_ConfigObjectAction(&work->object, 9, 0, 4);
        }
        work->control.turn.vy = 0x800;
        s11d_rope_800C4898(work, 0);
    }
    if (work->object.is_end != 0)
    {
        s11d_rope_800C486C(work);
        work->field_EAC = (int)s11d_rope_800C6834;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        work->field_F70 &= ~0x100;
    }
    work->control.step.vy -= 0x80;
}

void s11d_rope_800C7B2C(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 &= 0xFF9FFFFF;
        work->field_F74 &= ~0x10000;
        GM_SeSetMode(&work->control.mov, 25, 1);
        work->field_F70 |= 0x100;
        if (work->object.action != 9)
        {
            GM_ConfigObjectAction(&work->object, 9, 0, 4);
        }
        work->control.turn.vy = 0x800;
        s11d_rope_800C4898(work, 0);
    }

    if (work->field_F74 & 0x2000)
    {
        if (work->field_EBC == 0)
        {
            work->field_EBC = 1;
        }
    }

    if (work->field_EBC == 1)
    {
        work->field_EBC = 2;
        work->field_F74 |= 0x10000;
        work->control.step.vy -= 0x80;
    }

    if (work->field_F74 & 0x2000)
    {
        s11d_rope_800C486C(work);
        work->field_F70 &= ~0x100;
        GM_SeSetMode(&work->control.mov, 0xb2, 1);
        s11d_rope_800C650C();
        work->field_EAC = (int)s11d_rope_800C6834;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        return;
    }

    if (s11d_rope_800C5298(work))
    {
        s11d_rope_800C486C(work);
        work->field_F70 &= ~0x100;
        GM_SeSetMode(&work->control.mov, 0xb7, 1);
        work->field_EAC = (int)s11d_rope_800C6B18;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        return;
    }

    if (s11d_rope_800C4DE0(work))
    {
        s11d_rope_800C486C(work);
        work->field_EAC = (int)s11d_rope_800C766C;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        work->field_F70 &= ~0x100;
        return;
    }

    if (work->object.is_end)
    {
        s11d_rope_800C486C(work);
        work->field_EAC = (int)s11d_rope_800C7530;
        work->field_EB0 = 0;
        work->field_EBE = 0;
        work->field_EBC = 0;
        work->field_F70 &= ~0x100;
    }
}
void s11d_rope_800C7D20(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        if (work->object.action != 0xD)
        {
            GM_ConfigObjectAction(&work->object, 0xD, 0, 4);
        }
        work->field_F44 = 0x1C2;
        if (work->control.mov.vy < -0x1770)
        {
            GM_SeSetMode(&work->control.mov, 0xB3, 1);
        }
        else
        {
            GM_SeSetMode(&work->control.mov, 0xB1, 1);
        }
        NewPadVibration(s11d_dword_800C328C, 1);
        NewPadVibration(s11d_dword_800C3290, 2);
        work->field_F74 |= 0x02000000;
    }

    if (work->control.mov.vy >= -0x36AF)
    {
        work->control.step.vz = 0x30;
    }
    else
    {
        work->control.step.vz = 0;
    }

    if (arg1 >= 10)
    {
        work->control.step.vy = -0x80;
    }
    else
    {
        work->control.step.vy = -0x20;
    }

    if (!(work->control.grounded & 1))
    {
        work->control.turn.vx = -0x400;
    }

    if (work->object.height < -work->control.step.vy)
    {
        work->control.step.vy = 8 - work->object.height;
    }

    if (arg1 == 0x10)
    {
        if (work->control.mov.vy < -0x3E80)
        {
            work->field_EAC = (int)s11d_rope_800C7EC4;
            work->field_EB0 = 0;
            work->field_EBE = 0;
            work->field_EBC = 0;
        }
        else
        {
            work->field_EAC = (int)s11d_rope_800C7F8C;
            work->field_EB0 = 0;
            work->field_EBE = 0;
            work->field_EBC = 0;
            work->field_F74 &= ~0x02000000;
        }
    }

    work->control.step.vy /= 2;
}

void s11d_rope_800C7EC4(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 |= 0x02000000;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_Vitality = 0;
        if (work->object.action != 14)
        {
            GM_ConfigObjectAction(&work->object, 14, 0, 4);
        }
    }
    work->control.step.vy -= 0x20;
    if (arg1 == 8)
    {
        GM_PlayerPosition = work->control.mov;
    }
    if (arg1 == 24)
    {
        GM_GameOver();
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7F8C.s")

void s11d_rope_800C8200(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        DG_InvisibleObjs(work->object.objs);
        DG_InvisiblePrim(work->field_7DC);
        GM_GameOver();
    }
}

void s11d_rope_800C8250(Work *work)
{
    void (*state_fn)(Work *, int);

    work->control.step = DG_ZeroVector;

    s11d_rope_800C54CC(work);
    s11d_rope_800C44A4(work);
    s11d_rope_800C4648(work);
    s11d_rope_800C481C(work);
    s11d_rope_800C4574(work);
    s11d_rope_800C44F0(work);
    s11d_rope_800C5348(work);
    s11d_rope_800C48EC(work);
    s11d_rope_800C4B78(work);
    s11d_rope_800C4ECC(work);
    s11d_rope_800C45F8(work);
    s11d_rope_800C6478(work);
    s11d_rope_800C5B10(work);

    state_fn = (void (*)(Work *, int))work->field_EAC;
    state_fn(work, work->field_EB0++);

    s11d_rope_800C5E74(work);
    s11d_rope_800C502C(work);

    s11d_dword_800D1F84 = (work->field_F70 & 2) > 0;
    GM_PlayerAction = work->object.action;
    dword_800AB9D4 = work->m_ctrl.info1.frame;
    s11d_rope_800C5410();
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8364.s")

void s11d_rope_800C868C(Work *work)
{
    TortureInfoKill();

    GV_DestroyActor(work->field_800);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);
    GM_FreeTarget(work->target);

    GM_FreePrim(work->field_810);
    GM_FreePrim(work->field_A14);
    GM_FreePrim(work->field_7DC);

    GM_GameStatus &= ~STATE_MENU_DISABLE;

    if (GM_PlayerControl == &work->control)
    {
        GM_PlayerControl = NULL;
    }

    if (GM_PlayerBody == &work->object)
    {
        GM_PlayerBody = NULL;
    }

    GM_VoxInit();
}

int s11d_rope_800C879C(Work *work)
{
    TARGET *target;
    int     vital;

    work->target = target = GM_AllocTarget();
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_FLAG, PLAYER_SIDE, &target_size);
    vital = GM_VitalityMax;
    GM_SetPowerTarget(target, POWER_DECREASE, -1, vital, 0, &DG_ZeroVector);
    GM_Vitality = vital;

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C882C.s")
int s11d_rope_800C882C(Work *work);

void s11d_rope_800C8C04(Work *work)
{
    RopeAxis *axis1;
    RopeAxis *axis2;

    s11d_rope_800C5538(work);

    axis1 = &work->axis[0];
    axis2 = &work->axis[1];

    axis1->dz = 0;
    axis1->dx = 0;
    axis2->dz = 0;
    axis2->dx = 0;
    axis1->step = 0x18;
    axis2->step = 0x40;
    axis1->target = work->field_F94;
    axis2->target = work->field_F98;
    axis1->pos = &work->control.mov.vx;
    axis2->pos = &work->control.mov.vz;
    axis1->rot = &work->control.turn.vz;
    axis2->rot = &work->control.turn.vx;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C88.s")
int s11d_rope_800C8C88(Work *work);

void s11d_rope_800C8EE4(Work *work)
{
    short  *base = (short *)&work->field_F84;
    u_char *param;

    param = GCL_GetOption('a');
    if (param)
    {
        GCL_StrToSV(param, &base[4]);
    }
    else
    {
        base[4] = 0x1770;
        base[5] = 0x6590;
    }
    ((short *)&s11d_dword_800D1F7C)[0] = base[5];
    ((short *)&s11d_dword_800D1F80)[0] = base[4];

    param = GCL_GetOption('i');
    if (param)
    {
        GCL_StrToSV(param, base);
    }
    else
    {
        base[0] = -0x1B58;
        base[1] = -0x30D4;
        base[2] = 0;
    }
    ((short *)&s11d_dword_800D1F7C)[1] = base[1];
    ((short *)&s11d_dword_800D1F80)[1] = base[0];

    param = GCL_GetOption('r');
    if (param)
    {
        GCL_StrToSV(param, (short *)&base[8]);
    }
    else
    {
        base[8] = -0xBB8;
        base[9] = 0x7530;
        base[10] = 0x258;
    }
}

int s11d_rope_800C8FDC(Work *work)
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
        while (GCL_NextStr())
        {
            if (j == 16)
            {
                break;
            }
            GCL_StrToSV(GCL_NextStr(), (short *)p1);
            p1++;
            j++;
        }
    }

    if (GCL_GetOption('h'))
    {
        u_char *param;
        p2 = work->field_FA4;
        while ((param = GCL_NextStr()))
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

void s11d_rope_800C90BC(Work *work)
{
    int  *p;
    int   i;
    u_char *param;

    if (!GCL_GetOption('w'))
    {
        return;
    }

    i = 0;
    p = work->field_107C;
    while ((param = GCL_NextStr()))
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

void s11d_rope_800C9134(Work *work)
{
    int  *p;
    int   i;
    u_char *param;

    if (!GCL_GetOption('v'))
    {
        return;
    }

    i = 0;
    p = work->field_1088;
    while ((param = GCL_NextStr()))
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

int s11d_rope_800C91AC(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *object;
    SVECTOR  indices;
    void    *shadow;

    control = &work->control;
    work->pad = &GV_PadData[2];

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, 0, 0x1C2, 0x1C2);
    work->field_F44 = 0x1C2;
    control->seg_flag = 1;
    GM_ConfigControlAttribute(control, 1);
    GM_ConfigControlTrapCheck(control);

    GM_PlayerControl = control;
    GM_PlayerPosition = work->control.mov;

    object = &work->object;
    GM_InitObject(object, GV_StrCode("snake"), 0x2D, GV_StrCode("sne_11d"));
    GM_ConfigObjectJoint(object);
    GM_ConfigMotionControl(object, &work->m_ctrl, GV_StrCode("sne_11d"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(object, work->light);
    GM_ConfigObjectAction(object, 0, 0, 0);

    object->objs->objs[0].raise = 500;
    object->objs->objs[1].raise = 500;

    if (s11d_rope_800C879C(work) < 0)
    {
        return -1;
    }
    if (s11d_rope_800C882C(work) < 0)
    {
        return -1;
    }
    if (s11d_rope_800C8C88(work) < 0)
    {
        return -1;
    }
    if (s11d_rope_800C8FDC(work) < 0)
    {
        return -1;
    }

    s11d_rope_800C8EE4(work);
    s11d_rope_800C90BC(work);
    s11d_rope_800C9134(work);

    if (GCL_GetOption('n'))
    {
        work->field_EA0 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_EA0 = 0;
    }

    if (GCL_GetOption('e'))
    {
        work->field_1078 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_1078 = -1;
    }

    GM_PlayerBody = object;
    work->field_EAC = (int)s11d_rope_800C6544;
    work->field_EB0 = 0;
    work->field_EB8 = 0;
    work->field_EB4 = 0;
    work->field_EBE = 0;
    work->field_EBC = 0;
    s11d_rope_800C8C04(work);

    work->field_F50 = DG_ZeroVector;
    work->field_808 = work->control.mov;
    work->field_F40 = 0x2710;
    work->field_F44 = 0x1C2;
    work->field_F4C = -1;
    work->field_F48 = 0;
    work->field_F70 = 0;
    work->field_F74 = 0;
    work->field_F78 = 0;
    work->field_F7C = 0;
    work->field_F60 = 0;
    work->field_F64 = 0;
    work->field_F68 = 0;

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    shadow = NewShadow(control, object, indices);
    work->field_800 = shadow;
    if (shadow == NULL)
    {
        return -1;
    }

    s11d_dword_800D1F84 = 0;
    GM_GameStatus |= STATE_NOSLOW;
    return 0;
}

void *NewRope(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, s11d_rope_800C8364, s11d_rope_800C868C, "rope.c");

    if (s11d_rope_800C91AC(work, name, where) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    return (void *)work;
}
