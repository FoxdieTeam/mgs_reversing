#include <stddef.h> // for NULL

#ifdef VR_EXE
#include "chara/snake_vr/sna_init.h"
#else
#include "chara/snake/sna_init.h"
#endif

#include "Game/linkvarbuf.h"
#include "Game/object.h"

extern int     GM_GameOverTimer;
extern int     GM_PlayerStatus_800ABA50;
extern short   word_8009EFC0[];

extern SVECTOR           svector_800AB7CC;
SVECTOR SECTION(".sbss") svector_800AB7CC;

extern void           *GM_BombSeg_800ABBD8;
void *SECTION(".sbss") GM_BombSeg_800ABBD8;

extern int           dword_800ABBA8;
int SECTION(".sbss") dword_800ABBA8;

extern int           gSnaMoveDir_800ABBA4;
int SECTION(".sbss") gSnaMoveDir_800ABBA4;

extern char           *dword_800ABBB4;
char *SECTION(".sbss") dword_800ABBB4;

extern SVECTOR           *svector_800ABBB8;
SVECTOR *SECTION(".sbss") svector_800ABBB8;

#define GetAction( work ) (work->field_9C_obj.action_flag)

void sna_start_anim_8004E1F4(SnaInitWork *work, void *pFn)
{
    short vec_x = 0;
    work->field_9B8_fn_anim = pFn;
    work->field_9BC_anim_frame = 0;
    work->field_A3A = 0;
    work->field_A38_local_data = 0;

    if ((GM_PlayerStatus_800ABA50 & PLAYER_GROUND) != 0)
    {
        vec_x = work->field_A2A;
    }

    work->control.turn.vx = vec_x;
    work->control.turn.vz = 0;
}

void SetAction_8004E22C(SnaInitWork *work, int action_flag, int interp)
{
    if (GetAction(work) != action_flag)
    {
        GM_ConfigObjectAction(&work->field_9C_obj, action_flag, 0, interp);
    }
}

void sna_8004E260(SnaInitWork *work, int a2, int interp, int a4)
{
    if (work->field_9C_obj.field_10 != a2)
    {
        GM_ConfigObjectOverride(&work->field_9C_obj, a2, 0, interp, a4);
    }
}

int GM_CheckPlayerStatusFlag_8004E29C(PlayerStatusFlag arg0)
{
    return (GM_PlayerStatus_800ABA50 & arg0) != 0;
}

int GM_SetPlayerStatusFlag_8004E2B4(PlayerStatusFlag arg0)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus_800ABA50 | arg0;
    GM_PlayerStatus_800ABA50 = temp_v0;
    return temp_v0;
}

void GM_ClearPlayerStatusFlag_8004E2D4(PlayerStatusFlag flag)
{
    GM_PlayerStatus_800ABA50 &= ~flag;
}

void sna_set_flags1_8004E2F4(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

void sna_clear_flags1_8004E308(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

int sna_check_flags1_8004E31C(SnaInitWork *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}

#ifndef VR_EXE
void sna_set_flags2_8004E330(SnaInitWork *snake, SnaFlag2 flag)
{
    snake->field_898_flags2 |= flag;
}

void sna_clear_flags2_8004E344(SnaInitWork *snake, SnaFlag2 flags)
{
    snake->field_898_flags2 &= ~flags;
}

unsigned int sna_sub_8004E358(SnaInitWork *snake, SnaFlag2 param_2)
{
    unsigned int result = 0;

    if (GM_UnkFlagBE != 0)
    {
        result = (((unsigned int)snake->field_898_flags2 & param_2) != result);
    }

    return result;
}
#endif

void CheckSnakeDead_8004E384(SnaInitWork *snake)
{
    if ((GM_SnakeCurrentHealth == 0) || (GM_GameOverTimer != 0))
    {
        snake->control.skip_flag |= CTRL_SKIP_TRAP;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_PAD_OFF | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
        sna_set_flags1_8004E2F4(snake, SNA_FLAG1_UNK23);
        GM_GameStatus |= (STATE_MENU_OFF | STATE_PADRELEASE);

        if (GM_GameOverTimer != -2)
        {
            sna_set_flags1_8004E2F4(snake, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        }
    }
}

void sna_sub_8004E41C(SnaInitWork *snake, unsigned short flags)
{
    TARGET *target = snake->field_8E8_pTarget;

    if (target != NULL)
    {
        target->damaged &= ~flags;
        snake->field_8E8_pTarget = 0;
        snake->field_A54.choke_count = 0;
        snake->field_89C_pTarget->size.vx = 300;
    }
}

// ... categorize move/turn direction by angle?
// param_1: snake->control.turn.vy
// param_2: gSnaMoveDir_800ABBA4
int sub_8004E458(short param_1, int param_2)
{
    short uVar2;

    if (param_2 < 0)
    {
        return 0;
    }

    uVar2 = (param_2 - param_1) & 0xFFF;

    if (uVar2 < 0x800)
    {
        if (uVar2 < 0x100)
        {
            return 1;
        }
        else if (uVar2 > 0x500)
        {
            return 3;
        }

        return 4;
    }
    else
    {
        if (uVar2 > 0xF00)
        {
            return 1;
        }
        else if (uVar2 < 0xB00)
        {
            return 3;
        }

        return 2;
    }
}

int sub_8004E4C0(SnaInitWork *work, int param_2)
{
    int iVar1;

    if (-1 < dword_800ABBA8)
    {
        if ((*dword_800ABBB4 & 0x40) != 0)
        {
            return param_2;
        }
        iVar1 = (param_2 - dword_800ABBA8) & 0xfff;
        if (iVar1 < 0x400)
        {
            param_2 = dword_800ABBA8 + 0x400;
        }
        if (iVar1 > 0xc00)
        {
            param_2 = dword_800ABBA8 - 0x400;
        }
    }
    return param_2;
}

int sub_8004E51C(SVECTOR *param_1, void *param_2, int param_3, int param_4)
{
    if (sub_80028454(param_2, param_1, &param_1[1], param_3, param_4) == 0)
    {
        return -1;
    }
    sub_80028890(&param_1[1]);
    GV_SubVec3(&param_1[1], param_1, param_1);
    return GV_VecLen3(param_1);
}

void sub_8004E588(HZD_HDL *param_1, SVECTOR *param_2, HZD_VEC *vec)
{
    unsigned int uVar1;

    uVar1 = sub_800296C4(param_1, param_2, 3);
    sub_800298DC(vec);
    if ((uVar1 & 1) == 0)
    {
        vec->long_access[0] = 0xffff8001;
    }
    if ((uVar1 & 2) == 0)
    {
        vec->long_access[1] = 0x00007fff;
    }
}

int sub_8004E5E8(SnaInitWork *work, int flag)
{
    int     i;
    SVECTOR vec;
    HZD_VEC vec2;
    int     unk2[2];

    vec.vx = work->field_9C_obj.objs->objs[4].world.t[0];
    vec.vy = work->field_9C_obj.objs->objs[4].world.t[1];
    vec.vz = work->field_9C_obj.objs->objs[4].world.t[2];

    DG_SetPos2(&vec, &work->control.rot);
    DG_PutVector(&svector_800AB7CC, &vec, 1);
    sub_8004E588(work->control.map->hzd, &vec, &vec2);

    i = -1;

    if ((sub_80029A2C() & flag) == 0)
    {
        sub_800298C0(unk2);

        if (vec.vy - vec2.long_access[0] < 350)
        {
            i = 0;
        }
        else if (vec2.long_access[1] - vec.vy < 125)
        {
            i = 1;
        }

        if (i >= 0)
        {
            if (!unk2[i])
            {
                GM_BombSeg_800ABBD8 = 0;
            }
            else
            {
                GM_BombSeg_800ABBD8 = (void *)(unk2[i] & ~0x80000000);
            }

            return 1;
        }
    }

    return 2;
}

int sna_8004E71C(int a1, HZD_HDL *pHzd, SVECTOR *pVec, int a4)
{
    HZD_VEC point;
    SVECTOR vec, vec_saved;
    MATRIX mtx;

    pVec->vz = a1;
    pVec->vy = 0;
    pVec->vx = 0;

    DG_PutVector(pVec, pVec, 1);
    ReadRotMatrix(&mtx);

    vec.vx = mtx.t[0];
    vec.vy = mtx.t[1];
    vec.vz = mtx.t[2];

    vec_saved = *pVec;

    if ( sub_8004E51C(&vec, pHzd, 12, 1) >= 0 )
    {
        *pVec = vec_saved;
    }

    sub_8004E588(pHzd, pVec, &point);
    return (point.long_access[1] - pVec->vy) < a4;
}

int sna_8004E808(SnaInitWork *work, int a2, int a3, int a4, int a5)
{
    CONTROL *pCtrl = &work->control;
    int bVar1 = 0;
    SVECTOR SStack48;
    SVECTOR auStack40;

    if (sna_8004E71C(a3, pCtrl->map->hzd, &SStack48, a5))
    {
        return 1;
    }

    if (a2 == 0)
    {
        return 0;
    }

    if (sna_8004E71C(a4, pCtrl->map->hzd, &auStack40, a5))
    {
        if (!svector_800ABBB8 || (svector_800ABBB8->pad == 2))
        {
            return 1;
        }

        if (sub_8004E51C(&SStack48, work->control.map->hzd, 3, 1) < 0)
        {
            return 1;
        }

        bVar1 = 1;
    }

    if ((!bVar1) && sna_8004E71C((a3 + a4) / 2, pCtrl->map->hzd, &SStack48, a5))
    {
        return 1;
    }

    return 0;
}

int sub_8004E930(SnaInitWork *snake, int arg1)
{
    int     int0;
    int     int1;
    SVECTOR vec0;
    SVECTOR vec1;

    vec0.vy = 0;
    vec0.vx = 0;
    vec0.vz = (short)arg1;
    DG_PutVector(&vec0, &vec0, 1);

    int1 = HZD_SlopeFloorLevel_800298F8(&vec0, svector_800ABBB8);
    int1 -= snake->control.levels[0];

    vec1.vx = int1;
    vec1.vz = SquareRoot0(arg1 * arg1 - int1 * int1);
    int0 = -GV_VecDir2(&vec1);

    if (int0 < -0x800)
    {
        int0 += 0x1000;
    }

    return int0;
}

void sub_8004E9D0(SnaInitWork *work)
{
    int iVar1;

    if (svector_800ABBB8)
    {
        iVar1 = sub_8004E930(work, 500);
        iVar1 = iVar1 / 2;
    }
    else
    {
        iVar1 = 0;
    }

    work->field_718[1].vx = GV_NearExp2(work->field_718[1].vx, iVar1);
    work->field_718[4].vx = GV_NearExp2(work->field_718[4].vx, -iVar1);
    work->field_718[9].vx = GV_NearExp2(work->field_718[9].vx, -iVar1);
}

void sub_8004EA50(SnaInitWork *work, int param_2)
{
    int iVar1 = GV_DiffDirS(param_2, work->control.rot.vy);

    if (iVar1 > 128)
    {
        iVar1 = 128;
    }
    else if (iVar1 < -128)
    {
        iVar1 = -128;
    }

    work->control.turn.vz = iVar1;
}

int sna_8004EAA8(SnaInitWork *work, int a2)
{
    if (a2 == 0)
    {
        return work->field_9B4_action_table->field_0->field_0;
    }

    if (a2 == 1)
    {
        return work->field_9B4_action_table->field_0->field_2;
    }

    if (a2 == 2)
    {
        return work->field_9B4_action_table->field_0->field_3;
    }

    return -1;
}

void sna_8004EB14(SnaInitWork *work)
{
    memcpy(&work->field_9D0, &word_8009EFC0, sizeof(work->field_9D0));
}
