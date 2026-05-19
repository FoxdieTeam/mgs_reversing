#include "common.h"
#include "linkvar.h"
#include "game/camera.h"
#include "game/control.h"
#include "game/game.h"
#include "game/target.h"
#include "game/vibrate.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "okajima/blood.h"

typedef struct _Work
{
    GV_ACT      actor;
    CONTROL     control;
    OBJECT      object;
    char        pad_obj[0x186 - 0x9C - sizeof(OBJECT)];
    short       field_186;
    char        pad2b[0x7DC - 0x186 - sizeof(short)];
    DG_PRIM    *field_7DC;
    char        pad2c[0x800 - 0x7DC - sizeof(DG_PRIM *)];
    void       *field_800;
    TARGET     *target;
    char        pad3a0[0x810 - 0x804 - sizeof(TARGET *)];
    DG_PRIM    *field_810;
    char        pad3a1[0xA14 - 0x810 - sizeof(DG_PRIM *)];
    DG_PRIM    *field_A14;
    char        pad3a2[0xEA0 - 0xA14 - sizeof(DG_PRIM *)];
    int         field_EA0;
    short      *field_EA4;
    GV_PAD     *pad;
    int         field_EAC;
    int         field_EB0;
    int         field_EB4;
    char        pad3c0[0xEBC - 0xEB4 - sizeof(int)];
    short       field_EBC;
    short       field_EBE;
    char        pad3c[0xEC8 - 0xEBC - sizeof(short) * 2];
    int         field_EC8;
    int         field_ECC;
    int         field_ED0;
    int         field_ED4;
    int         field_ED8;
    int         field_EDC;
    int         field_EE0;
    int         field_EE4;
    int         field_EE8;
    int         field_EEC;
    int         field_EF0;
    int         field_EF4;
    int         field_EF8;
    int         field_EFC;
    int         field_F00;
    int         field_F04;
    int         field_F08;
    int         field_F0C;
    int         field_F10;
    int         field_F14;
    int         field_F18;
    int         field_F1C;
    int         field_F20;
    int         field_F24;
    int         field_F28;
    int         field_F2C;
    int         field_F30;
    int         field_F34;
    int         field_F38;
    int         field_F3C;
    char        pad3d00a[0xF44 - 0xF3C - sizeof(int)];
    short       field_F44;
    char        pad3d00b[0xF50 - 0xF44 - sizeof(short)];
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
    char        pad6a4[0x107C - 0xFE4 - sizeof(SVECTOR) * 16];
    int         field_107C[3];
    int         field_1088[4];
} Work;

#define EXEC_LEVEL  GV_ACTOR_USER
#define TARGET_FLAG ( TARGET_AVAIL | TARGET_POWER | TARGET_SEEK )

extern CONTROL *GM_WhereList[96];
extern int GM_N_WhereList;

extern GM_CameraSystemWork GM_Camera;
extern GM_SnakeCameraWork GM_SnakeCamera;

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
extern void s03b_boxall_800C9328(void);

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
extern void s11d_rope_800C5B10(Work *work);
extern void s11d_rope_800C5E74(Work *work);
extern void s11d_rope_800C6478(Work *work);
extern void s11d_rope_800C650C(void);
extern void s11d_rope_800C6834(Work *work);
extern void s11d_rope_800C6B18(Work *work);
extern void s11d_rope_800C7138(Work *work);
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
        control->evt.mov = control->mov;
        control->evt.mov.pad = control->rot.vy;
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
        rot.t[0] = mdl->pos.vx;
        rot.t[1] = mdl->pos.vy;
        rot.t[2] = mdl->pos.vz;
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
    if (work->field_EA4[2] > work->field_F88)
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

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C4648.s")

void s11d_rope_800C481C(Work *work)
{
    GM_SnakeCamera.rotate.vy = work->field_EDC / 48 + 2048;
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

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C502C.s")

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
            work->field_EA4 = (short *)ctrl;
            return;
        }
    } while (--i > 0);
}

void s11d_rope_800C5538(Work *work)
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

void s11d_rope_800C62E0(Work *work)
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

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6544.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6834.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C697C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C6B18.s")
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

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7B2C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C7D20.s")

void s11d_rope_800C7EC4(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_F74 |= 0x02000000;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_SnakeCurrentHealth = 0;
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
    dword_800AB9D4 = work->field_186;
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

    GM_GameStatus &= ~STATE_MENU_OFF;

    if (GM_PlayerControl == &work->control)
    {
        GM_PlayerControl = NULL;
    }

    if (GM_PlayerBody == &work->object)
    {
        GM_PlayerBody = NULL;
    }

    s03b_boxall_800C9328();
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
    vital = GM_SnakeMaxHealth;
    GM_SetPowerTarget(target, POWER_DECREASE, -1, vital, 0, &DG_ZeroVector);
    GM_SnakeCurrentHealth = vital;

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C882C.s")

void s11d_rope_800C8C04(Work *work)
{
    int *cluster1;
    int *cluster2;

    s11d_rope_800C5538(work);

    cluster1 = &work->field_EC8;
    cluster2 = &work->field_F04;

    cluster1[6]  = 0;                           /* field_EE0 */
    cluster1[5]  = 0;                           /* field_EDC */
    cluster2[6]  = 0;                           /* field_F1C */
    cluster2[5]  = 0;                           /* field_F18 */
    cluster1[3]  = 0x18;                        /* field_ED4 */
    cluster2[3]  = 0x40;                        /* field_F10 */
    cluster1[12] = work->field_F94;             /* field_EF8 */
    cluster2[12] = work->field_F98;             /* field_F34 */
    cluster1[13] = (int)&work->control.mov;     /* field_EFC */
    cluster2[13] = (int)&work->control.mov.vz;  /* field_F38 */
    cluster1[14] = (int)&work->control.turn.vz; /* field_F00 */
    cluster2[14] = (int)&work->control.turn.vx; /* field_F3C */
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C8C88.s")

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

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_rope_800C91AC.s")

void *NewRope(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
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
