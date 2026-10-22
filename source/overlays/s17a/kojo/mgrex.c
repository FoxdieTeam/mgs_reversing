#include <stdio.h>
#include "mgstype.h"
#include "libgcl/libgcl.h"
#include "mgrex.h"

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_AMBIENT )
#define PART_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )
#define LIQUID_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

#define DEG(x)      ((x) * 4096 / 360)
#define METER(x)    ((x) * 1000)
#define SPEED(x)    (((x) * 1000000) / 108000)  /* km/h to mm/frame */

/* the state of REX is kept here between two loads of the stage */
MGREX_WORK mgrex_saved = {{0}};
char       mgrex_name[] = "MG-REX";

void MgRex_Act(MGREX_WORK *work);
void MgRex_Die(MGREX_WORK *work);
void s17a_800DEBB4(MGREX_WORK *work, int action, int arg2);
void s17a_800E37D4(MGREX_WORK *work, HZD_SEG *segs);
void s17a_800E3B00(MGREX_WORK *work, HZD_SEG *segs);

#define GET_INT(dst)            opt = GCL_NextStr(); if (opt) { (dst) = GCL_StrToInt(opt); }
#define GET_VALUE(dst, conv)    opt = GCL_NextStr(); if (opt) { (dst) = conv(GCL_StrToInt(opt)); }

void *NewMetalGearRex(int name, int where)
{
    MGREX_WORK *work;
    char       *opt;
    SVECTOR     size;
    MENU_BAR_CONF *life_bar;
    int         mode;
    int         i;

    if (name != 0x4754)
    {
        GV_ZeroMemory(&mgrex_saved, sizeof(MGREX_WORK));
        printf("mem clear ok!\n");
        return (void *)-1;
    }

    work = GV_NewActor(GV_ACTOR_USER, sizeof(MGREX_WORK));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, MgRex_Act, MgRex_Die, "mgrex.c");

    work->name = name;
    work->where = where;

    if (GM_InitControl(&work->control, 0, where) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    work->light[0].t[0] = mgrex_saved.light[0].t[0];
    work->light[0].t[1] = mgrex_saved.light[0].t[1];
    work->light[0].t[2] = mgrex_saved.light[0].t[2];
    if (GCL_GetOption('a'))
    {
        work->light[0].t[0] = 16;
        work->light[0].t[1] = 16;
        work->light[0].t[2] = 16;
        GET_INT(work->light[0].t[0]);
        GET_INT(work->light[0].t[1]);
        GET_INT(work->light[0].t[2]);
    }

    work->f5AC = mgrex_saved.f5AC;
    work->f5B0 = mgrex_saved.f5B0;
    work->f5B4 = mgrex_saved.f5B4;
    work->f5B8 = mgrex_saved.f5B8;
    if (GCL_GetOption('e'))
    {
        GET_VALUE(work->f5AC, METER);
        GET_VALUE(work->f5B0, DEG);
        GET_VALUE(work->f5B4, DEG);
        GET_INT(work->f5B8);
    }

    work->f5D4 = mgrex_saved.f5D4;
    work->f5D8 = mgrex_saved.f5D8;
    work->f5DC = mgrex_saved.f5DC;
    work->f5E0 = mgrex_saved.f5E0;
    if (GCL_GetOption('c'))
    {
        GET_VALUE(work->f5D4, METER);
        GET_VALUE(work->f5D8, METER);
        GET_VALUE(work->f5DC, METER);
        GET_VALUE(work->f5E0, METER);
    }

    work->f5BC = mgrex_saved.f5BC;
    work->f5C0 = mgrex_saved.f5C0;
    work->f5C4 = mgrex_saved.f5C4;
    work->f5C8 = mgrex_saved.f5C8;
    work->f5CC = mgrex_saved.f5CC;
    work->f5D0 = mgrex_saved.f5D0;
    if (GCL_GetOption('d'))
    {
        GET_INT(work->f5BC);
        GET_INT(work->f5C0);
        GET_INT(work->f5C4);
        GET_INT(work->f5C8);
        GET_INT(work->f5CC);
        GET_INT(work->f5D0);
    }

    work->f5E4 = mgrex_saved.f5E4;
    work->f5E8 = mgrex_saved.f5E8;
    work->f5EC = mgrex_saved.f5EC;
    if (GCL_GetOption('s'))
    {
        GET_INT(work->f5E4);
        GET_VALUE(work->f5E8, DEG);
        GET_VALUE(work->f5EC, DEG);
    }

    work->f5F0 = mgrex_saved.f5F0;
    work->f5F4 = mgrex_saved.f5F4;
    work->f5F8 = mgrex_saved.f5F8;
    work->f5FC = mgrex_saved.f5FC;
    work->f600 = mgrex_saved.f600;
    work->f604 = mgrex_saved.f604;
    work->f608 = mgrex_saved.f608;
    work->f60C = mgrex_saved.f60C;
    work->f610 = mgrex_saved.f610;
    work->f614 = mgrex_saved.f614;
    work->f618 = mgrex_saved.f618;
    work->f61C = mgrex_saved.f61C;
    work->f620 = mgrex_saved.f620;
    if (GCL_GetOption('g'))
    {
        GET_INT(work->f5F0);
        GET_INT(work->f5F4);
        GET_VALUE(work->f5F8, 1 +);
        GET_VALUE(work->f5FC, DEG);
        GET_VALUE(work->f600, DEG);
        GET_VALUE(work->f604, DEG);
        GET_VALUE(work->f608, DEG);
        GET_VALUE(work->f60C, DEG);
        GET_VALUE(work->f610, DEG);
        GET_INT(work->f614);
        GET_INT(work->f618);
        GET_VALUE(work->f61C, METER);
        GET_VALUE(work->f620, SPEED);
    }

    work->f624 = mgrex_saved.f624;
    work->f628 = mgrex_saved.f628;
    work->f62C = mgrex_saved.f62C;
    work->f630 = mgrex_saved.f630;
    work->f634 = mgrex_saved.f634;
    work->f638 = mgrex_saved.f638;
    work->f63C = mgrex_saved.f63C;
    work->f640 = mgrex_saved.f640;
    work->f644 = mgrex_saved.f644;
    work->f648 = mgrex_saved.f648;
    work->f64C = mgrex_saved.f64C;
    work->f650 = mgrex_saved.f650;
    work->f654 = mgrex_saved.f654;
    work->f658 = mgrex_saved.f658;
    work->f65C = mgrex_saved.f65C;
    if (GCL_GetOption('l'))
    {
        GET_INT(work->f624);
        GET_INT(work->f628);
        GET_VALUE(work->f62C, DEG);
        GET_VALUE(work->f630, DEG);
        GET_VALUE(work->f634, DEG);
        GET_VALUE(work->f638, DEG);
        GET_VALUE(work->f63C, DEG);
        GET_INT(work->f640);
        GET_INT(work->f644);
        GET_VALUE(work->f648, METER);
        GET_VALUE(work->f64C, SPEED);
        GET_VALUE(work->f650, DEG);
        if ((opt = GCL_NextStr()) != NULL) work->f654 = MIN(MAX(GCL_StrToInt(opt), 0), 255);
        if ((opt = GCL_NextStr()) != NULL) work->f658 = MIN(MAX(GCL_StrToInt(opt), 0), 255);
        if ((opt = GCL_NextStr()) != NULL) work->f65C = MIN(MAX(GCL_StrToInt(opt), 0), 255);
    }

    work->f660 = mgrex_saved.f660;
    work->f664 = mgrex_saved.f664;
    work->f668 = mgrex_saved.f668;
    work->f66C = mgrex_saved.f66C;
    work->f670 = mgrex_saved.f670;
    work->f674 = mgrex_saved.f674;
    work->f678 = mgrex_saved.f678;
    work->f67C = mgrex_saved.f67C;
    work->f680 = mgrex_saved.f680;
    work->f684 = mgrex_saved.f684;
    if (GCL_GetOption('m'))
    {
        work->f684 = NULL;
        GET_INT(work->f660);
        GET_INT(work->f664);
        GET_VALUE(work->f668, 1 +);
        GET_VALUE(work->f66C, DEG);
        GET_VALUE(work->f670, DEG);
        GET_INT(work->f674);
        GET_INT(work->f678);
        GET_VALUE(work->f67C, METER);
        GET_VALUE(work->f680, SPEED);
        if ((opt = GCL_NextStr()) != NULL && GCL_StrToInt(opt) == 1)
        {
            work->f684 = &GM_PlayerPosition;
        }
    }

    work->control.mov = mgrex_saved.control.mov;
    work->control.turn = mgrex_saved.control.turn;
    work->f688 = mgrex_saved.f688;
    work->f690 = mgrex_saved.f690;
    work->f698 = mgrex_saved.f698;
    work->f6A0 = mgrex_saved.f6A0;
    work->f6A8 = mgrex_saved.f6A8;
    work->f6B0 = mgrex_saved.f6B0;
    if (GCL_GetOption('p'))
    {
        GET_VALUE(work->control.mov.vx, METER);
        GET_VALUE(work->control.mov.vy, METER);
        GET_VALUE(work->control.mov.vz, METER);
        GET_VALUE(work->control.turn.vx, DEG);
        GET_VALUE(work->control.turn.vy, DEG);
        GET_VALUE(work->control.turn.vz, DEG);
        GET_INT(work->f688.pad);
        GET_VALUE(work->f688.vx, METER);
        GET_VALUE(work->f688.vy, METER);
        GET_VALUE(work->f688.vz, METER);
        GET_INT(work->f690.pad);
        GET_VALUE(work->f690.vx, DEG);
        GET_VALUE(work->f690.vy, DEG);
        GET_VALUE(work->f690.vz, DEG);
        GET_INT(work->f698.pad);
        GET_VALUE(work->f698.vx, METER);
        GET_VALUE(work->f698.vy, METER);
        GET_VALUE(work->f698.vz, METER);
        GET_INT(work->f6A0.pad);
        GET_VALUE(work->f6A0.vx, DEG);
        GET_VALUE(work->f6A0.vy, DEG);
        GET_VALUE(work->f6A0.vz, DEG);
        GET_INT(work->f6A8.pad);
        GET_VALUE(work->f6A8.vx, METER);
        GET_VALUE(work->f6A8.vy, METER);
        GET_VALUE(work->f6A8.vz, METER);
        GET_INT(work->f6B0.pad);
        GET_VALUE(work->f6B0.vx, DEG);
        GET_VALUE(work->f6B0.vy, DEG);
        GET_VALUE(work->f6B0.vz, DEG);
    }
    else
    {
        if (work->f698.pad)
        {
            work->control.mov = mgrex_saved.f698;
        }

        if (work->f6A0.pad)
        {
            work->control.turn = mgrex_saved.f6A0;
        }
    }

    if (GCL_GetOption('z'))
    {
        work->f1764 = -1;
        work->f1768 = -1;
        GET_INT(work->f1768);
        GET_INT(work->f1764);
    }
    else
    {
        work->f1764 = mgrex_saved.f1764;
        work->f1768 = mgrex_saved.f1768;
    }

    if (work->f5BC > 0)
    {
        work->mode = 0;
    }
    else
    {
        work->mode = 3;
    }

    if (GCL_GetOption('b'))
    {
        mode = GCL_StrToInt(GCL_NextStr());
        if (mode == 0)
        {
            work->mode = 0;
        }
        else if (mode == 1)
        {
            work->mode = 3;
        }
        else if (mode == 2)
        {
            work->mode = 5;
        }
    }

    work->control.r_sphere = -2;
    work->control.interp = 0;
    GM_ConfigControlAttribute(&work->control, 5);

    GM_InitObject(&work->objWaist, GV_StrCode("mgrexw"), BODY_FLAG, 0);
    GM_ConfigObjectJoint(&work->objWaist);
    GM_ConfigMotionControl(&work->objWaist, &work->body_m_ctrl, GV_StrCode("mgrexw"), work->body_m_segs1, work->body_m_segs2, &work->body_control, work->body_rots);
    GM_ConfigMotionAdjust(&work->objWaist, work->body_adjust);
    GM_ConfigObjectLight(&work->objWaist, work->light);
    work->body_m_ctrl.rot = &work->control.rot;
    work->objWaist.objs->waist_rot = NULL;

    GM_InitObject(&work->leg_l, GV_StrCode("mgrexll"), BODY_FLAG, 0);
    GM_ConfigObjectJoint(&work->leg_l);
    GM_ConfigMotionControl(&work->leg_l, &work->leg_l_m_ctrl, GV_StrCode("mgrexll"), work->leg_l_m_segs1, work->leg_l_m_segs2, &work->leg_l_control, work->leg_l_rots);
    GM_ConfigMotionAdjust(&work->leg_l, work->leg_l_adjust);
    GM_ConfigObjectLight(&work->leg_l, work->light);
    GM_ConfigObjectRoot(&work->leg_l, &work->objWaist, 0);
    work->leg_l.objs->waist_rot = NULL;

    GM_InitObject(&work->leg_r, GV_StrCode("mgrexrl"), BODY_FLAG, 0);
    GM_ConfigObjectJoint(&work->leg_r);
    GM_ConfigMotionControl(&work->leg_r, &work->leg_r_m_ctrl, GV_StrCode("mgrexrl"), work->leg_r_m_segs1, work->leg_r_m_segs2, &work->leg_r_control, work->leg_r_rots);
    GM_ConfigMotionAdjust(&work->leg_r, work->leg_r_adjust);
    GM_ConfigObjectLight(&work->leg_r, work->light);
    GM_ConfigObjectRoot(&work->leg_r, &work->objWaist, 0);
    work->leg_r.objs->waist_rot = NULL;

    work->f390 = 1;
    work->f710 = 1;

    work->control.rot.vx = work->control.turn.vx;
    work->control.rot.vy = work->control.turn.vy;
    work->control.rot.vz = work->control.turn.vz;

    work->timers[1] = work->f5F8 / 2;
    work->timers[2] = work->f5F8 / 2;
    work->timers[4] = work->f668 / 2;
    work->f778 = work->f5F0;
    work->f77C = work->f5F0;

    work->f7AC = work->f61C;
    work->f7AC = MIN(work->f7AC, work->f648);
    work->f7AC = MIN(work->f7AC, work->f67C);

    work->f7B0 = work->f61C;
    work->f7B0 = MAX(work->f7B0, work->f648);
    work->f7B0 = MAX(work->f7B0, work->f67C);

    work->f7B4 = (work->f7AC + work->f7B0) / 2;

    work->f7B8 = work->f61C - work->f5D8;
    work->f7B8 = MIN(work->f7B8, work->f648 - work->f5DC);
    work->f7B8 = MIN(work->f7B8, work->f67C - work->f5E0);

    work->f7BC = work->f61C - work->f5D8;
    work->f7BC = MAX(work->f7BC, work->f648 - work->f5DC);
    work->f7BC = MAX(work->f7BC, work->f67C - work->f5E0);

    work->f7C0 = (work->f7B8 + work->f7BC) / 2;

    work->target_size = (work->leg_l.objs->objs[8].model->uz - work->leg_l.objs->objs[8].model->lz) / 2;

    size.vx = work->target_size;
    size.vy = work->target_size + 500;
    size.vz = work->target_size;

    GM_SetTarget(&work->target1, TARGET_AVAIL, NO_SIDE, &size);
    GM_SetTarget(&work->target2, TARGET_AVAIL, NO_SIDE, &size);
    GM_SetPowerTarget(&work->target1, POWER_DECREASE, -1, work->f5E4, 0, &DG_ZeroVector);
    GM_SetPowerTarget(&work->target2, POWER_DECREASE, -1, work->f5E4, 0, &DG_ZeroVector);
    work->target1.weapon = 10;
    work->target2.weapon = 10;

    size.vy = work->target_size * 2;

    work->target3 = GM_AllocTarget();
    work->target4 = GM_AllocTarget();
    GM_SetTarget(work->target3, TARGET_AVAIL | TARGET_PUSH, NO_SIDE, &size);
    GM_SetPowerTarget(work->target3, POWER_CONST, -1, 0, 0, &DG_ZeroVector);
    GM_SetTarget(work->target4, TARGET_AVAIL | TARGET_PUSH, NO_SIDE, &size);
    GM_SetPowerTarget(work->target4, POWER_CONST, -1, 0, 0, &DG_ZeroVector);

    work->f6B8.vx = ((work->objWaist.objs->objs[2].model->ux - work->objWaist.objs->objs[2].model->lx) * 5) / 16;
    work->f6B8.vy = (work->objWaist.objs->objs[2].model->uy - work->objWaist.objs->objs[2].model->ly) / 5;
    work->f6C0.vx = -(((work->objWaist.objs->objs[2].model->ux - work->objWaist.objs->objs[2].model->lx) * 5) / 16);
    work->f6C0.vy = (work->objWaist.objs->objs[2].model->uy - work->objWaist.objs->objs[2].model->ly) / 5;
    work->f6C8 = work->f5FC + work->f60C;
    work->f6CC = work->f600 + work->f60C;
    work->f6D0 = work->f604;
    work->f6D4 = work->f608 + work->f610;

    work->f6DA = (work->objWaist.objs->objs[9].model->ly - work->objWaist.objs->objs[9].model->uy) / 2;
    work->f6DC = ((work->objWaist.objs->objs[9].model->uz - work->objWaist.objs->objs[9].model->lz) * 3) / 4;

    work->f6E0 = work->f62C + work->f638;
    work->f6E4 = work->f630 + work->f638;
    work->f6E8 = work->f634 + work->f63C;

    work->f6EE = -((work->leg_l.objs->objs[1].model->uy - work->leg_l.objs->objs[1].model->ly) / 5);
    work->f6F0 = ((work->leg_l.objs->objs[1].model->uz - work->leg_l.objs->objs[1].model->lz) * 6) / 7;
    work->f6F6 = -((work->leg_r.objs->objs[1].model->uy - work->leg_r.objs->objs[1].model->ly) / 5);
    work->f6F8 = ((work->leg_r.objs->objs[1].model->uz - work->leg_r.objs->objs[1].model->lz) * 6) / 7;

    for (i = 0; i < 10; i++)
    {
        work->objWaist.objs->objs[i].world = DG_ZeroMatrix;
    }

    for (i = 0; i < 13; i++)
    {
        work->leg_l.objs->objs[i].world = DG_ZeroMatrix;
    }

    for (i = 0; i < 13; i++)
    {
        work->leg_r.objs->objs[i].world = DG_ZeroMatrix;
    }

    work->f1A9C = work->objWaist.objs->objs[3].model->ty;

    if (work->mode == 0)
    {
        work->f1960 = 1;
        work->f1954 = -1;
        s17a_800DEBB4(work, 12, 0);
        GM_ConfigObjectAction(&work->objWaist, 47, 0, 0);
        GM_ConfigObjectAction(&work->leg_l, 47, 0, 0);
        GM_ConfigObjectAction(&work->leg_r, 47, 0, 0);
        work->f1ABC = work->f1AC0 = work->f1AC4 = work->f5BC;
    }
    else if (work->mode == 3)
    {
        s17a_800DEBB4(work, 0, 0);
        GM_ConfigObjectAction(&work->objWaist, 0, 0, 0);
        GM_ConfigObjectAction(&work->leg_l, 0, 0, 0);
        GM_ConfigObjectAction(&work->leg_r, 0, 0, 0);
        work->f1ABC = work->f1AC0 = work->f1AC4 = work->f5C4;
        work->objWaist.objs->objs[3].model->ty -= 500;
    }
    else
    {
        work->f1960 = 1;
        work->f1954 = -1;
        s17a_800DEBB4(work, 13, 0);
        GM_ConfigObjectAction(&work->objWaist, 49, 0, 0);
        GM_ConfigObjectAction(&work->leg_l, 49, 0, 0);
        GM_ConfigObjectAction(&work->leg_r, 49, 0, 0);
        work->objWaist.objs->objs[3].model->ty -= 500;
    }

    life_bar = &work->life_bar;
    life_bar->name = mgrex_name;
    life_bar->left[0] = 0x10;
    life_bar->left[1] = 0x6F;
    life_bar->left[2] = 0x9F;
    life_bar->right[0] = 0x1A;
    life_bar->right[1] = 0xBB;
    life_bar->right[2] = 0x8A;

    GM_InitObjectNoRots(&work->objCockpit, GV_StrCode("pit_t"), PART_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)&work->objCockpit, work->light);
    GM_ConfigObjectRoot((OBJECT *)&work->objCockpit, &work->objWaist, 2);

    GM_InitObjectNoRots(&work->pit_u, GV_StrCode("pit_u"), PART_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)&work->pit_u, work->light);
    GM_ConfigObjectRoot((OBJECT *)&work->pit_u, &work->objWaist, 3);

    GM_InitObject(&work->objCockpit2, GV_StrCode("pit_liq"), LIQUID_FLAG, 0);
    GM_ConfigObjectRoot(&work->objCockpit2, &work->objWaist, 3);
    GM_ConfigObjectLight(&work->objCockpit2, work->pit_light);
    GM_ConfigObjectJoint(&work->objCockpit2);

    if (work->mode == 0)
    {
        GM_InitObjectNoRots(&work->radar, GV_StrCode("radar_f1"), PART_FLAG, 0);
        DG_InvisibleObjs(work->objCockpit.objs);
        DG_InvisibleObjs(work->objCockpit2.objs);
        DG_InvisibleObjs(work->pit_u.objs);
        work->radar_parent = &work->objWaist.objs->objs[6];
    }
    else if (work->mode == 3 || work->mode == 5)
    {
        GM_InitObjectNoRots(&work->radar, GV_StrCode("radar_f3"), PART_FLAG, 0);
        work->radar_parent = &work->objCockpit2.objs->objs[1];
    }

    GM_ConfigObjectLight((OBJECT *)&work->radar, work->light);
    GM_ConfigObjectRoot((OBJECT *)&work->radar, &work->objWaist, 6);

    GM_InitControl(&work->control2, name, where);
    GM_ConfigControlAttribute(&work->control2, 0);
    work->control2.r_sphere = -2;
    GM_ConfigControlRadarparam(&work->control2, 0, 20000, 200, 0);

    if (work->mode == 0)
    {
        work->hatch_l_model = 0;
        work->hatch_r_model = 0;
        work->f1978 = 0;
        work->f197C = 0;
    }
    else
    {
        work->hatch_l_model = mgrex_saved.hatch_l_model;
        work->hatch_r_model = mgrex_saved.hatch_r_model;
        work->f1978 = mgrex_saved.f1978;
        work->f197C = mgrex_saved.f197C;
    }

    GM_InitObjectNoRots(&work->hatch_l, GV_StrCode("l_hatch1") + work->hatch_l_model, PART_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)&work->hatch_l, work->light);
    GM_ConfigObjectRoot((OBJECT *)&work->hatch_l, &work->leg_l, 1);

    GM_InitObjectNoRots(&work->hatch_r, GV_StrCode("r_hatch1") + work->hatch_r_model, PART_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)&work->hatch_r, work->light);
    GM_ConfigObjectRoot((OBJECT *)&work->hatch_r, &work->leg_r, 1);

    mgrex_saved = *work;

    work->segs = GV_Malloc(45 * sizeof(HZD_SEG));
    s17a_800E37D4(work, work->segs);

    for (i = 0; i < 37; i++)
    {
        HZD_QueueDynamicSegment2(work->control.map->hzd, &work->segs[i], 0x7F);
    }

    work->segs2 = &work->segs[37];
    s17a_800E3B00(work, work->segs2);

    for (i = 0; i < 8; i++)
    {
        HZD_QueueDynamicSegment2(work->control.map->hzd, &work->segs2[i], 0x51);
    }

    work->f1980 = 1;
    work->f1984 = 255;
    work->player_pos = GM_PlayerPosition;
    work->f6FC = 2;
    work->f1ACC = 3;
    s17a_dword_800E5E30 = 0;
    work->frame = 0;
    s17a_dword_800E5E34 = 0;
    work->f176C = work->body_rots[0].vy;
    GM_GameStatus &= ~STATE_DEMO;

    return (void *)work;
}
