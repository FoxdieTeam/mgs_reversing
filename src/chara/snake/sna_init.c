#include "sna_init.h"
#include "afterse.h"
#include "libdg/libdg.h"
#include "linker.h"
#include "map/map.h"
#include "Game/object.h"
#include "Kojo/demothrd.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "unknown.h"
#include "Okajima/blood.h"
#include "Bullet/bakudan.h"
#include "Game/homing_target.h"
#include "Game/vibrate.h"
#include "psyq.h"
#include "Game/camera.h"
#include "Weapon/grenade.h"
#include "Anime/animeconv/anime.h"

extern short word_8009EFC0[];

extern Target_Data stru_8009EFE4;

extern Sna_E1 e1_800AB7C4;
Sna_E1        SECTION(".sdata") e1_800AB7C4;

extern int dword_800ABBA8;
int        SECTION(".sbss") dword_800ABBA8;

extern int gSnaMoveDir_800ABBA4;
int        SECTION(".sbss") gSnaMoveDir_800ABBA4;

extern int dword_800ABBB4;
int        SECTION(".sbss") dword_800ABBB4;

extern GM_Control *gSnaControl_800AB9F4;
extern OBJECT     *dword_800ABA20;

extern SVECTOR *svector_800ABBB8;
SVECTOR *SECTION(".sbss") svector_800ABBB8;

extern Actor_SnaInit *sna_init_800ABBA0;
Actor_SnaInit *SECTION(".sbss") sna_init_800ABBA0;

extern int dword_800ABBC4;
int        SECTION(".sbss") dword_800ABBC4;

extern SVECTOR *pVec_800ABBC8;
SVECTOR        *SECTION(".sbss") pVec_800ABBC8;

extern SVECTOR *pVec_800ABBCC;
SVECTOR        *SECTION(".sbss") pVec_800ABBCC;

extern int dword_800ABBD0;
int        SECTION(".sbss") dword_800ABBD0;

extern short dword_800ABBDC;
short        SECTION(".sbss") dword_800ABBDC;

extern short dword_800ABBD4;
short        SECTION(".sbss") dword_800ABBD4;

extern int dword_800ABBB0;
int        SECTION(".sbss") dword_800ABBB0;

extern GM_Target *GM_BombSeg_800ABBD8; // probably wrong type?
GM_Target        *SECTION(".sbss") GM_BombSeg_800ABBD8;

extern short              GM_WeaponChanged_800AB9D8;
extern int                GM_AlertMode_800ABA00;
extern int                GM_GameOverTimer_800AB3D4;
extern int                GM_GameStatus_800AB3CC;
extern SVECTOR            DG_ZeroVector_800AB39C;
extern PlayerStatusFlag   GM_PlayerStatus_800ABA50;
extern Target_Data        stru_8009F044;
extern SVECTOR            stru_800AB7FC;
extern GM_Camera GM_Camera_800B77E8;
extern SVECTOR            dword_800AB7D4;
extern SVECTOR            dword_800AB7DC;
extern unsigned short     GM_WeaponTypes_8009D580[];
extern Sna_ActionTable    actions_no_weapon_8009ED70;
extern unsigned short     GM_ItemTypes_8009D598[];
extern void              *dword_8009EEA4[];
extern int                GV_Time_800AB330;
extern int                used_counter_8009F42C;
extern SVECTOR            dword_800AB7EC;
extern SVECTOR            dword_800AB7F4;
extern int                gSnaMoveDir_800ABBA4;
extern int                DG_UnDrawFrameCount_800AB380;
extern int                dword_8009EF24[];
extern int                dword_8009EF2C[];
extern SVECTOR            dword_800AB7CC;
extern int                counter_8009F448;
extern const char         aSnakeEUC[];
extern SVECTOR            stru_8009EFD4[];
extern int                dword_800ABA1C;
extern int                dword_8009F2C0;
extern int                dword_800AB9F0;

extern const char aRunMoveCancel[]; // = "run move cancel\n"
extern const char aForceStanceCan[]; // = "force stance cancel\n"
extern const char aForceActCancel[]; // = "force act cancel\n"

void sna_init_start_anim_8004E1F4(Actor_SnaInit *pActor, void *pFn)
{
    short vec_x = 0;
    pActor->field_9B8_fn_anim = pFn;
    pActor->field_9BC_anim_frame = 0;
    pActor->field_A3A = 0;
    pActor->field_A38 = 0;

    if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_PRONE) != 0)
    {
        vec_x = pActor->field_A2A;
    }

    pActor->field_20_ctrl.field_4C_turn_vec.vx = vec_x;
    pActor->field_20_ctrl.field_4C_turn_vec.vz = 0;
}

void sna_init_8004E22C(Actor_SnaInit *pActor, int action_flag, int interp)
{
    if (pActor->field_9C_obj.action_flag != action_flag)
    {
        GM_ConfigObjectAction_80034CD4(&pActor->field_9C_obj, action_flag, 0, interp);
    }
}

void sna_init_8004E260(Actor_SnaInit *pActor, int a2, int interp, int a4)
{
    if (pActor->field_9C_obj.field_10 != a2)
    {
        GM_ConfigObjectOverride_80034D30(&pActor->field_9C_obj, a2, 0, interp, a4);
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

void sna_init_set_flags1_8004E2F4(Actor_SnaInit *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

void sna_init_clear_flags1_8004E308(Actor_SnaInit *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

int sna_init_check_flags1_8004E31C(Actor_SnaInit *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}

void sna_init_set_flags2_8004E330(Actor_SnaInit *snake, SnaFlag2 flag)
{
    snake->field_898_flags2 |= flag;
}

void sna_init_clear_flags2_8004E344(Actor_SnaInit *snake, SnaFlag2 flags)
{
    snake->field_898_flags2 &= ~flags;
}

unsigned int sna_init_sub_8004E358(Actor_SnaInit *snake, SnaFlag2 param_2)
{
    unsigned int result = 0;

    if (GM_UnkFlagBE != 0)
    {
        result = (((unsigned int)snake->field_898_flags2 & param_2) != result);
    }

    return result;
}

void sna_init_check_dead_8004E384(Actor_SnaInit *snake)
{
    if ((GM_SnakeCurrentHealth == 0) || (GM_GameOverTimer_800AB3D4 != 0))
    {
        snake->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_flags1_8004E2F4(snake, SNA_FLAG1_UNK23);
        GM_GameStatus_800AB3CC |= 0x10080000;

        if (GM_GameOverTimer_800AB3D4 != -2)
        {
            sna_init_set_flags1_8004E2F4(snake, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        }
    }
}

void sna_init_sub_8004E41C(Actor_SnaInit *snake, unsigned short flags)
{
    GM_Target *target = snake->field_8E8_pTarget;

    if (target != NULL)
    {
        target->field_6_flags &= ~flags;
        snake->field_8E8_pTarget = 0;
        snake->field_A54.choke_count = 0;
        snake->field_89C_pTarget->field_10_size.vx = 300;
    }
}

// ... categorize move/turn direction by angle?
// param_1: snake->field_20_ctrl.field_4C_turn_vec.vy
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

int sub_8004E4C0(Actor_SnaInit *pActor, int param_2)
{
    int iVar1;

    if (-1 < dword_800ABBA8)
    {
        if ((*(char *)dword_800ABBB4 & 0x40) != 0)
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
    GV_SubVec3_80016D40(&param_1[1], param_1, param_1);
    return GV_VecLen3_80016D80(param_1);
}

void sub_8004E588(HZD_MAP *param_1, SVECTOR *param_2, int *param_3)
{
    unsigned int uVar1;

    uVar1 = sub_800296C4(param_1, param_2, 3);
    sub_800298DC(param_3);
    if ((uVar1 & 1) == 0)
    {
        *param_3 = 0xffff8001;
    }
    if ((uVar1 & 2) == 0)
    {
        param_3[1] = 0x7fff;
    }
}

int sub_8004E5E8(Actor_SnaInit *pActor, int flag)
{
    int     i;
    SVECTOR vec;
    int     unk1[2];
    int     unk2[2];

    vec.vx = pActor->field_9C_obj.objs->objs[4].world.t[0];
    vec.vy = pActor->field_9C_obj.objs->objs[4].world.t[1];
    vec.vz = pActor->field_9C_obj.objs->objs[4].world.t[2];

    DG_SetPos2_8001BC8C(&vec, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutVector_8001BE48(&dword_800AB7CC, &vec, 1);
    sub_8004E588(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &vec, unk1);

    i = -1;

    if ((sub_80029A2C() & flag) == 0)
    {
        sub_800298C0(unk2);

        if (vec.vy - unk1[0] < 350)
        {
            i = 0;
        }
        else if (unk1[1] - vec.vy < 125)
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
                GM_BombSeg_800ABBD8 = (GM_Target *)(unk2[i] & ~0x80000000);
            }

            return 1;
        }
    }

    return 2;
}

int sna_init_8004E71C(int a1, HZD_MAP *pHzd, SVECTOR *pVec, int a4)
{
    int point[2];
    SVECTOR vec, vec_saved;
    MATRIX mtx;

    pVec->vz = a1;
    pVec->vy = 0;
    pVec->vx = 0;

    DG_PutVector_8001BE48(pVec, pVec, 1);
    ReadRotMatrix_80092DD8(&mtx);

    vec.vx = mtx.t[0];
    vec.vy = mtx.t[1];
    vec.vz = mtx.t[2];

    vec_saved = *pVec;

    if ( sub_8004E51C(&vec, pHzd, 12, 1) >= 0 )
    {
        *pVec = vec_saved;
    }

    sub_8004E588(pHzd, pVec, point);
    return (point[1] - pVec->vy) < a4;
}

int sna_init_8004E808(Actor_SnaInit *pActor, int a2, int a3, int a4, int a5)
{
    GM_Control *pCtrl = &pActor->field_20_ctrl;
    int bVar1 = 0;
    SVECTOR SStack48;
    SVECTOR auStack40;
    
    if (sna_init_8004E71C(a3, pCtrl->field_2C_map->field_8_hzd, &SStack48, a5))
    {
        return 1;
    }
    
    if (a2 == 0)
    {
        return 0;
    }

    if (sna_init_8004E71C(a4, pCtrl->field_2C_map->field_8_hzd, &auStack40, a5))
    {
        if (!svector_800ABBB8 || (svector_800ABBB8->pad == 2))
        {
            return 1;
        }

        if (sub_8004E51C(&SStack48, pActor->field_20_ctrl.field_2C_map->field_8_hzd, 3, 1) < 0)
        {
            return 1;
        }

        bVar1 = 1;
    }

    if ((!bVar1) && sna_init_8004E71C((a3 + a4) / 2, pCtrl->field_2C_map->field_8_hzd, &SStack48, a5))
    {
        return 1;
    }

    return 0;
}

int sub_8004E930(Actor_SnaInit *snake, int arg1)
{
    int     int0;
    int     int1;
    SVECTOR vec0;
    SVECTOR vec1;

    vec0.vy = 0;
    vec0.vx = 0;
    vec0.vz = (short)arg1;
    DG_PutVector_8001BE48(&vec0, &vec0, 1);

    int1 = HZD_SlopeFloorLevel_800298F8(&vec0, svector_800ABBB8);
    int1 -= snake->field_20_ctrl.field_78;

    vec1.vx = int1;
    vec1.vz = SquareRoot0_80092708(arg1 * arg1 - int1 * int1);
    int0 = -GV_VecDir2_80016EF8(&vec1);

    if (int0 < -0x800)
    {
        int0 += 0x1000;
    }

    return int0;
}

void sub_8004E9D0(Actor_SnaInit *pActor)
{
    int iVar1;

    if (svector_800ABBB8)
    {
        iVar1 = sub_8004E930(pActor, 500);
        iVar1 = iVar1 / 2;
    }
    else
    {
        iVar1 = 0;
    }

    pActor->field_718[1].vx = GV_NearExp2_80026384(pActor->field_718[1].vx, iVar1);
    pActor->field_718[4].vx = GV_NearExp2_80026384(pActor->field_718[4].vx, -iVar1);
    pActor->field_718[9].vx = GV_NearExp2_80026384(pActor->field_718[9].vx, -iVar1);
}

void sub_8004EA50(Actor_SnaInit *pActor, int param_2)
{
    int iVar1 = GV_DiffDirS_8001704C(param_2, pActor->field_20_ctrl.field_8_rotator.vy);

    if (iVar1 > 128)
    {
        iVar1 = 128;
    }
    else if (iVar1 < -128)
    {
        iVar1 = -128;
    }

    pActor->field_20_ctrl.field_4C_turn_vec.vz = iVar1;
}

int sna_init_8004EAA8(Actor_SnaInit *pActor, int a2)
{
    if (a2 == 0)
    {
        return pActor->field_9B4_action_table->field_0->field_0;
    }

    if (a2 == 1)
    {
        return pActor->field_9B4_action_table->field_0->field_2;
    }

    if (a2 == 2)
    {
        return pActor->field_9B4_action_table->field_0->field_3;
    }

    return -1;
}

void sna_init_8004EB14(Actor_SnaInit *pActor)
{
    memcpy(&pActor->field_9D0, &word_8009EFC0, sizeof(pActor->field_9D0));
}

void sub_8004EB74(Actor_SnaInit *pActor)
{
    if (GM_Camera_800B77E8.field_22 == 0)
    {
        if (pActor->field_9B0_pad_ptr->dir == (short)-1)
        {
            pActor->field_A20 = -6;
        }
        else
        {
            pActor->field_A20 = -3;
        }
    }

    GM_Camera_800B77E8.field_22 = 1;
    pActor->field_A56 = 0;
    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON);

    if (GM_UnkFlagBE == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
    }

    sd_set_cli_800887EC(0x1ffff20, 0);
}

void sna_init_8004EC00(Actor_SnaInit *pActor)
{
    if (GM_Camera_800B77E8.field_22 == 1)
    {
        pActor->field_A20 = 6;
    }

    GM_Camera_800B77E8.field_22 = 0;
    pActor->field_A56 = 0;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
    sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK16);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        sd_set_cli_800887EC(0x1ffff21, 0);
    }

    sna_init_clear_flags2_8004E344(pActor, (SNA_FLAG2_UNK5 | SNA_FLAG2_UNK6));
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK400);
}

void sna_init_8004EC8C(Actor_SnaInit *pActor)
{
    ushort v2; // $v1

    sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK12);
    pActor->field_A28 = 460;
    GM_Camera_800B77E8.field_22 = 1;
    v2 = *(ushort *)&e1_800AB7C4.field_4;
    pActor->field_A20 = -6;
    pActor->field_9D0[2] = 320;
    pActor->field_9D0[4] = v2;
    pActor->field_9D0[6] = v2;
    sd_set_cli_800887EC(0x1FFFF20, 0);
    sna_init_set_flags2_8004E330(pActor, SNA_FLAG2_UNK5);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON);
}

void sub_8004ED08(Actor_SnaInit *pActor)
{
    sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK12);
    pActor->field_A28 = 0x1c2;
    GM_Camera_800B77E8.field_22 = 0; // weapon related?
    pActor->field_A20 = 6;
    sna_init_8004EB14(pActor);
    sd_set_cli_800887EC(0x1ffff21, 0);
    sna_init_clear_flags2_8004E344(pActor, (SNA_FLAG2_UNK5 | SNA_FLAG2_UNK6));
}

void sna_init_act_helper2_helper3_8004ED6C(Actor_SnaInit *pActor)
{
    if (pActor->field_A20 != 0)
    {
        if (pActor->field_A20 >= 1)
        {

            if ((GM_Camera_800B77E8.field_22 == 0) && (--pActor->field_A20 == 0))
            {
                DG_VisibleObjs(pActor->field_9C_obj.objs);

                if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK4))
                {
                    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
                }
            }
        }
        else if ((GM_Camera_800B77E8.field_22 != 0) && (++pActor->field_A20 == 0))
        {
            DG_InvisibleObjs(pActor->field_9C_obj.objs);
        }
    }
}

extern UnkCameraStruct gUnkCameraStruct_800B77B8;
void                 sna_init_8004EE28(Actor_SnaInit *snake)
{
    MATRIX  mat1;
    MATRIX  mat2;
    SVECTOR vec;
    int     vx;
    MATRIX *world = &snake->field_9C_obj.objs->objs[6].world;

    ReadRotMatrix_80092DD8(&mat1);
    DG_TransposeMatrix_8001EAD8(&mat1, &mat2);
    MulMatrix0_80092A48(&mat2, world, &mat2);
    DG_MatrixRotZYX_8001E92C(&mat2, &vec);
    SetRotMatrix_80093218(&mat1);
    vx = vec.vx;
    if (vx < 0)
    {
        vx += 0xf;
    }
    vx &= 0xfff0;
    gUnkCameraStruct_800B77B8.field_28.vx = vx;
}

void sub_8004EEB0(Actor_SnaInit *pActor)
{
    short sVar1;
    int   iVar2;
    int   arg0;

    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        arg0 = pActor->field_20_ctrl.field_4C_turn_vec.vy;
        if (GV_DiffDirS_8001704C(arg0, gSnaMoveDir_800ABBA4))
        {
            iVar2 = sub_80026418(arg0, gSnaMoveDir_800ABBA4);
            sVar1 = sub_8002646C(iVar2, gSnaMoveDir_800ABBA4, 0x40);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = sVar1;
        }
    }
}

void sub_8004EF14(Actor_SnaInit *param_1)
{
    int actionFlag;
    int diff;
    int y;

    y = param_1->field_20_ctrl.field_4C_turn_vec.vy;

    diff = GV_DiffDirS_8001704C(y, gSnaMoveDir_800ABBA4);
    if (diff == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        y = param_1->field_9B4_action_table->field_0->field_1;
        sna_init_8004E22C(param_1, y, 4);
    }
    else
    {
        short sVar2;
        int   iVar4;

        if (diff < 0)
        {
            actionFlag = param_1->field_9B4_action_table->field_4->field_8;
        }
        else
        {
            actionFlag = param_1->field_9B4_action_table->field_4->field_9;
        }

        sna_init_8004E22C(param_1, actionFlag, 4);
        iVar4 = sub_80026418(y, gSnaMoveDir_800ABBA4);
        sVar2 = sub_8002646C(iVar4, gSnaMoveDir_800ABBA4, 0x40);
        param_1->field_20_ctrl.field_4C_turn_vec.vy = sVar2;
    }
}

int sub_8004EFE4(Actor_SnaInit *pActor, int param_2)
{
    int      ret;
    SVECTOR *vec; // not sure if correct

    if (param_2 == 1)
    {
        vec = (SVECTOR *)&pActor->field_180.field_04;
    }
    else
    {
        vec = (SVECTOR *)&pActor->field_180.field_1C;
    }

    if (param_2 == 1)
    {
        ret = pActor->field_9C_obj.action_flag;
    }
    else
    {
        ret = pActor->field_9C_obj.field_10;
    }

    if (vec->vx + vec->vy == 1)
    {
        return ret;
    }

    return -1;
}

void sna_init_8004F034(Actor_SnaInit *pActor, unsigned int bits)
{
    if ( bits != pActor->field_180.field_04.field_8 )
    {
        pActor->field_180.field_1C.field_8 = ~bits;
        pActor->field_180.field_04.field_8 = bits;
        if ( bits == 0xFFFF && sub_8004EFE4(pActor, 2) >= 0 )
        {
            pActor->field_180.interp = 4;
            pActor->field_180.field_1C.field_14 = 2;
        }
    }
}

void sna_init_act_helper2_helper4_8004F090(Actor_SnaInit *pActor, int param_2)
{
    int    iVar1;
    MATRIX mtx;

    DG_SetPos_8001BC44(&pActor->field_9C_obj.objs->objs[6].world);
    DG_MovePos_8001BD20(&dword_800AB7D4);
    DG_RotatePos_8001BD64(&dword_800AB7DC);
    ReadRotMatrix_80092DD8(&mtx);

    iVar1 = -1;
    switch (param_2)
    {
    case 3:
        iVar1 = 0;
        break;
    case 1:
    case 4:
        iVar1 = 1;
        break;
    case 2:
        iVar1 = 2;
        break;
    }

    if (iVar1 >= 0)
    {
        NewBlood_80072728(&mtx, iVar1);
    }
}

void sub_8004F14C(Actor_SnaInit *param_1)
{
    param_1->field_91C_weapon_idx = WEAPON_NONE;
    GM_CurrentWeaponId = WEAPON_NONE;

    if (param_1->field_908_weapon_actor != 0)
    {
        GV_DestroyActorQuick_80015164(param_1->field_908_weapon_actor);
    }

    param_1->field_908_weapon_actor = 0;
    param_1->field_920_tbl_8009D580 = GM_WeaponTypes_8009D580[0];
    param_1->field_918_pWeaponState = 0;
    param_1->field_9B4_action_table = &actions_no_weapon_8009ED70;
    param_1->field_90C_pWeaponFn = sna_init_anim_chokethrow_begin1_80054210;
    param_1->field_910 = 0;
    param_1->field_926 = 0;
    param_1->field_924 = 0;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        param_1->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
    }
    else
    {
        sna_init_8004EC00(param_1);
    }
}

void sub_8004F204(Actor_SnaInit *param_1)
{
    if (param_1->field_9A4_item_actor != 0)
    {
        GV_DestroyActorQuick_80015164(param_1->field_9A4_item_actor);
    }

    param_1->field_9A4_item_actor = 0;
    param_1->field_9A8_current_item = ITEM_NONE;
    GM_CurrentItemId = ITEM_NONE;
    param_1->field_9AC = GM_ItemTypes_8009D598[0];

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        param_1->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
    }
    else
    {
        sna_init_8004EC00(param_1);
    }

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK1000);
}

void sna_init_set_invuln_8004F2A0(Actor_SnaInit *pActor, char invuln_frames)
{
    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_INVULNERABLE);
    pActor->field_A24_invuln_frames = invuln_frames;
    pActor->field_89C_pTarget->field_0_flags &= ~0x96;
}

void sna_init_clear_invuln_8004F2EC(Actor_SnaInit *snake)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_INVULNERABLE);
    sna_init_clear_flags1_8004E308(snake, SNA_FLAG1_UNK1);
    snake->field_89C_pTarget->field_0_flags |= TARGET_FLAG;
}

void sub_8004F338(Actor_SnaInit *param_1)
{
    int iVar2;

    iVar2 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT);
    if (iVar2 != 0)
    {

        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
        param_1->field_A56 = 0;
    }
    else
    {
        sna_init_8004EC00(param_1);
    }

    sna_init_clear_invuln_8004F2EC(param_1);
    param_1->field_A24_invuln_frames = 0;
    sna_init_sub_8004E41C(param_1, 2);
    GM_ConfigMotionAdjust_80035008(&param_1->field_9C_obj, 0);
    sna_init_clear_flags1_8004E308(param_1, SNA_FLAG1_UNK9);
    param_1->field_9C0 = 0;
    sna_init_8004E260(param_1, 0, 4, 0);
    param_1->field_92C->def = (DG_DEF *)((int)param_1->field_92C->def | 0x100);
    GM_ExitBehindCamera_80030AEC();

    GM_PlayerStatus_800ABA50 &= PLAYER_STATUS_CAN_USE_CONTROLLER_PORT_2 | PLAYER_STATUS_UNK4000000 |
                                PLAYER_STATUS_GAMEOVER | PLAYER_STATUS_UNK1000 | PLAYER_STATUS_FIRST_PERSON_DUCT |
                                PLAYER_STATUS_UNK4 | PLAYER_STATUS_CROUCHING | PLAYER_STATUS_PRONE;

    if ((param_1->field_920_tbl_8009D580 & 0x200) != 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON);
    }

    param_1->field_A28 = 0x1c2;
    param_1->field_894_flags1 &= (SNA_FLAG1_UNK20 | SNA_FLAG1_UNK28 | SNA_FLAG1_UNK29);
    param_1->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK9);
}

void sub_8004F454(Actor_SnaInit *pActor)
{
    int i;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING | PLAYER_STATUS_PREVENT_FIRST_PERSON |
                                      PLAYER_STATUS_KNOCKING);
    GM_ConfigMotionAdjust_80035008(&pActor->field_9C_obj, NULL);

    for (i = 0; i < (int)(sizeof(pActor->field_718) / sizeof(SVECTOR)); i++) // 16
    {
        pActor->field_718[i] = DG_ZeroVector_800AB39C;
    }

    sna_init_8004E260(pActor, 0, 4, 0);
    sna_init_sub_8004E41C(pActor, 2);
    sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK26);
    pActor->field_92C->def = (DG_DEF *)((unsigned int)pActor->field_92C->def | 0x100); // ?

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_ON_WALL) == 0)
    {
        pActor->field_A28 = 450;
        GM_ExitBehindCamera_80030AEC();
    }

    pActor->field_20_ctrl.field_55_flags &= ~8;
    sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK9);
}

int sna_init_8004F544(Actor_SnaInit *pActor, SVECTOR param_2, int a3, int a4, int a5)
{
    MATRIX mtx;
    SVECTOR vec1;
    SVECTOR vec2;
    SVECTOR vec3;

    int bVar1;
    int iVar2;
    
    vec1 = param_2;
    
    vec3.vy = 0;
    vec3.vx = 0;
    vec3.vz = a3;
    
    ReadRotMatrix_80092DD8(&mtx);
    DG_SetPos2_8001BC8C(&param_2, &pActor->field_20_ctrl.field_4C_turn_vec);
    DG_PutVector_8001BE48(&vec3, &vec2, 1);
    DG_SetPos_8001BC44(&mtx);

    iVar2 = sub_8004E51C(&vec1, pActor->field_20_ctrl.field_2C_map->field_8_hzd, a4, a5);

    bVar1 = a3 < iVar2;

    if (a3 < 0)
    {
        a3 = -a3;
        bVar1 = a3 < iVar2;
    }

    if (bVar1)
    {
        iVar2 = -1;
    }

    return iVar2;
}

int sna_init_8004F628(Actor_SnaInit *pActor, SVECTOR *param_2, int param_3, int param_4, int param_5, int param_6)
{
    SVECTOR vec;
  
    DG_SetPos2_8001BC8C(&pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutVector_8001BE48(param_2, &vec, 1);

    if (param_6 >= 1)
    {
        vec.vy = pActor->field_20_ctrl.field_78 + param_6;
    }

    return sna_init_8004F544(pActor, vec, param_3, param_4, param_5) >= 0;
}

static inline int sna_init_helper_8004F6E8(int health, int item)
{
    int temp;

    if ((health == 0) &&
        (GM_GameOverTimer_800AB3D4 == 0) &&
        (item == ITEM_RATION) &&
        (GM_Items[ITEM_RATION] > 0) &&
        !GM_FrozenItemsState)
    {
        temp = (GM_DifficultyFlag > DIFFICULTY_EASY) ? 256 : 384;

        if (GM_DifficultyFlag < DIFFICULTY_EASY)
        {
            temp = GM_SnakeMaxHealth;
        }

        health = temp;

        if (health > GM_SnakeMaxHealth)
        {
            health = GM_SnakeMaxHealth;
        }

        GM_Items[ITEM_RATION] -= 1;
            
        if (GM_Items[ITEM_RATION] == 0)
        {
            GM_CurrentItemId = ITEM_NONE;
        }

        GM_TotalRationsUsed += 1;
        GM_Sound_80032968(0, 63, 12);
    }

    return health;
}

void sna_init_8004F6E8(Actor_SnaInit *pActor)
{
    int health;
    
    if (sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK23))
    {
        return;
    }

    if (sna_init_check_flags1_8004E31C(pActor,SNA_FLAG1_UNK25) &&
        (GM_SnakeCurrentHealth == pActor->field_89C_pTarget->field_26_hp))
    {
        return;
    }
    
    if ((pActor->field_9A8_current_item == ITEM_B_ARMOR) && (pActor->field_89C_pTarget->field_3E == 1))
    {
        pActor->field_89C_pTarget->field_28 /= 2;
        pActor->field_89C_pTarget->field_26_hp += pActor->field_89C_pTarget->field_28;
        pActor->field_89C_pTarget->field_28 = 0;
    }
    
    health = pActor->field_89C_pTarget->field_26_hp + GM_SnakeCurrentHealth - pActor->field_A22_snake_current_health;
    
    if (health > GM_SnakeMaxHealth)
    {
        health = GM_SnakeMaxHealth;
    }

    if (health < 0)
    {
        health = 0;
    }

    if (pActor->field_89C_pTarget->field_44 != 10)
    {
        health = sna_init_helper_8004F6E8(health, pActor->field_9A8_current_item);
    }
    else
    {
        health = 0;
    }
    
    pActor->field_89C_pTarget->field_26_hp = health;
    pActor->field_A22_snake_current_health = health;
    GM_SnakeCurrentHealth = health;
    
    sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK25);
}
    
void sna_init_8004F8E4(Actor_SnaInit *pActor, int a2)
{
    GV_MSG msg;

    if ((GM_GameOverTimer_800AB3D4 == -1) || (GM_GameOverTimer_800AB3D4 == 0))
    {
        msg.address = GV_StrCode_80016CCC(aSnakeEUC);
        msg.message_len = 6;
        msg.message[0] = 48650;
        msg.message[1] = a2;
        msg.message[2] = -1;
        msg.message[3] = -1;
        msg.message[4] = 2;
        msg.message[5] = 2042;
    
        pActor->field_7A4_msgs[pActor->field_7A0_msg_count] = msg;
        pActor->field_7A0_msg_count++;

        GM_GameOverTimer_800AB3D4 = 0;
        GM_GameOver_8002B6C8();

        GM_GameStatus_800AB3CC |= 0x10000000;
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK20);
    
        if (pActor->field_A70 >= 0)
        {
            GCL_ForceExecProc_8001FEFC(pActor->field_A70, NULL);
        }

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000))
        {
            sub_8004F204(pActor);
        }
    }
}

int sna_act_unk_helper4_8004FA3C(void)
{
    if (GM_SnakeCurrentHealth == 0 || GM_GameOverTimer_800AB3D4 != 0)
    {
        return 1;
    }
    return 0;
}

void sna_init_8004FA74(Actor_SnaInit *param_1)
{
    sna_init_clear_flags2_8004E344(param_1, SNA_FLAG2_UNK6);
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                      PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK);
}

void sub_8004FA9C(Actor_SnaInit *snake)
{
    ushort action = snake->field_9B0_pad_ptr->status;
    sna_init_80051FD0(snake);
    if (action & PAD_DOWN)
    {
        sna_init_set_flags2_8004E330(snake, SNA_FLAG2_UNK1);
    }
}

void sub_8004FAE8(Actor_SnaInit *snake)
{
    SVECTOR vec;

    DG_MatrixRotYXZ_8001E734(&snake->field_9C_obj.objs->objs[6].world, &vec);
    gUnkCameraStruct_800B77B8.field_28 = vec;
}

int sna_init_current_item_8004FB38(void)
{
    return sna_init_800ABBA0->field_9A8_current_item;
}

int sna_init_ration_available_8004FB4C(void)
{
    if ((sna_init_800ABBA0->field_9A8_current_item == ITEM_RATION) &&
        (GM_Items[ITEM_RATION] > 0) &&
        (GM_FrozenItemsState == 0))
    {
        return 1;
    }

    return 0;
}

SVECTOR ** sub_8004FB90(void)
{
    return &svector_800ABBB8;
}

extern unsigned char gBulNames_800BDC78[64];

int GM_Next_BulName_8004FBA0()
{
    int i;                   // $a0
    for (i = 1; i < 64; i++) // for some reason skip the first one ??
    {
        if (!gBulNames_800BDC78[i])
        {
            gBulNames_800BDC78[i] = 1;
            return i;
        }
    }
    return 0;
}

void GM_ClearBulName_8004FBE4(int idx)
{
    gBulNames_800BDC78[idx] = 0;
}

void GM_CheckShukanReverse_8004FBF8(unsigned short *pInput)
{
    unsigned short old;
    unsigned int   v2; // $v1
    unsigned int   v3; // $v0

    if ((GM_GameStatusFlag & 0x1000) != 0 && (GM_GameStatus_800AB3CC & 0x40000000) == 0)
    {
        old = *pInput;

        *pInput = old & ~0x5000;

        v2 = old & 0x5000;
        v3 = v2 & 0x1000;

        if (v3)
        {
            *pInput |= 0x4000;
        }

        if (v2 & 0x4000)
        {
            *pInput |= 0x1000;
        }
    }
}

void GM_CheckShukanReverseAnalog_8004FC70(unsigned char *pInput)
{
    if ((GM_GameStatusFlag & 0x1000) != 0 && (GM_GameStatus_800AB3CC & 0x40000000) == 0)
    {
        *pInput = ~*pInput;
    }
}

int sub_8004FCB8(Actor_SnaInit *snake, UnkSnakeStruct *unkSnakeStruct, int param_3)
{
    int        sub_8004E51C_result;
    GM_Target *pTarget;
    SVECTOR    vec;
    SVECTOR    vec_arr[2];

    pTarget = &snake->field_8A0_target;
    GM_SetTarget_8002DC74(pTarget, 4, 1, &unkSnakeStruct->field_0_vectors[1]);
    DG_RotVector_8001BE98(&unkSnakeStruct->field_0_vectors[2], &vec, 1);
    GM_Target_8002DCCC(pTarget, 3, param_3, unkSnakeStruct->field_18_ints[0], unkSnakeStruct->field_18_ints[1], &vec);
    DG_PutVector_8001BE48(unkSnakeStruct->field_0_vectors, &vec, 1);
    vec_arr[0].vx = snake->field_9C_obj.objs->objs[5].world.t[0];
    vec_arr[0].vy = snake->field_9C_obj.objs->objs[5].world.t[1];
    vec_arr[0].vz = snake->field_9C_obj.objs->objs[5].world.t[2];
    vec_arr[1] = vec;
    sub_8004E51C_result = sub_8004E51C(vec_arr, ((snake->field_20_ctrl).field_2C_map)->field_8_hzd, 0xf, 1);
    if (sub_8004E51C_result < 0)
    {
        GM_Target_SetVector_8002D500(pTarget, &vec);
        return sub_8002D7DC(pTarget);
    }
    return 0;
}

int sna_init_8004FDE8(Actor_SnaInit *pActor, Target_Data *pTargetData)
{
    int flags = 0x2;
    GM_Target *pTarget;
    SVECTOR vec;
    SVECTOR vecs[2];

    if (pTargetData->field_18 == 0x40)
    {
        flags = 0x40;
    }

    GM_SetTarget_8002DC74(&pActor->field_8A0_target, flags, 1, &pTargetData->field_8_size);
    GM_Target_8002DCB4(&pActor->field_8A0_target, pTargetData->field_18, pTargetData->field_1C, &pActor->field_8F4, &pActor->field_8FC);
    DG_PutVector_8001BE48(&pTargetData->field_0, &vec, 1);
    GM_Target_SetVector_8002D500(&pActor->field_8A0_target, &vec);

    pActor->field_8E8_pTarget = NULL;

    if (flags == 2)
    {
        pTarget = GM_CaptureTarget_8002D530(&pActor->field_8A0_target);
    }
    else
    {
        pTarget = GM_C4Target_8002D620(&pActor->field_8A0_target);
    }

    if (pTarget)
    {
        if (pTarget->field_0_flags & 0x20)
        {
            pTarget->field_6_flags &= ~flags;
            pTarget->field_2A += pTargetData->field_1C;
            return 0;
        }

        vecs[0] = pActor->field_20_ctrl.field_0_position;
        vecs[1] = pTarget->field_8_vec;

        if (sub_8004E51C(vecs, pActor->field_20_ctrl.field_2C_map->field_8_hzd, 15, 1) < 0)
        {
            pActor->field_8E8_pTarget = pTarget;
            return 1;
        }

        pTarget->field_6_flags &= ~flags;
        pTarget->field_2A += pTargetData->field_1C;
    }

    return 0;
}

int sna_init_act_helper2_helper5_8004FF88(Actor_SnaInit *pActor)
{
    void *pAnim;

    if (!(GM_GameStatus_800AB3CC & 0xd0000000) && (GM_AlertMode_800ABA00 != 3))
    {
        if (!GM_CheckPlayerStatusFlag_8004E29C(0x20001304) &&
            !sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK9) &&
            (GM_SnakeCurrentHealth != 0) &&
            (GM_GameOverTimer_800AB3D4 == 0) &&
            (GM_StreamStatus_80037CD8() == -1) &&
            (pActor->field_9C_obj.field_10 == 0))
        {
            pAnim = pActor->field_9B8_fn_anim;
            
            if ((pAnim == sna_init_anim_idle_8005275C) ||
                (pAnim == sna_init_anim_crouch_800527DC) ||
                (pAnim == sna_init_anim_prone_idle_800528BC) ||
                (pAnim == sna_init_anim_wall_idle_and_c4_80052A5C) ||
                (pAnim == sna_init_anim_wall_crouch_80052CCC) ||
                (pAnim == sna_init_anim_duct_move_80054424))
            {
                return 1;   
            }
        }
    }

    return 0;
}

int sna_init_8005009C(Actor_SnaInit *pActor)
{
    GV_PAD *pPad = pActor->field_9B0_pad_ptr;
    int tbl = pActor->field_920_tbl_8009D580;
    unsigned short press = pPad->press;
    unsigned short input = press;
    void *pAnimFn;

    if (!(tbl & 0x100))
    {
        input = pPad->status;
    }

    if (input & PAD_SQUARE)
    {
        pActor->field_910 = 0;

        if (tbl & 0x10)
        {
            sna_init_start_anim_8004E1F4(pActor, pActor->field_90C_pWeaponFn);
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK3);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            return 1;
        }

        if (tbl & 8)
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING))
            {
                pAnimFn = sna_init_anim_rungun_80056C3C;
            }
            else
            {
                pAnimFn = sna_init_anim_shoot_weapon_80056B88;
            }

            sna_init_start_anim_8004E1F4(pActor, pAnimFn);
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_PREVENT_ITEM_SWITCH);
        }
        else
        {
            if ((input & PAD_CROSS) && (pActor->field_9B0_pad_ptr->dir >= 0))
            {
                pAnimFn = sna_init_anim_rungun_80056C3C;
            }
            else
            {
                pAnimFn = sna_init_anim_shoot_weapon_80056B88;
            }

            sna_init_start_anim_8004E1F4(pActor, pAnimFn);
        }

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
        return 1;
    }

    if ((press & PAD_CIRCLE) && ((pActor->field_9B4_action_table->field_10->field_2 ^ 0x88) != 0))
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_punch_80058C10);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK3);
        return 1;
    }

    return 0;
}

void sna_init_check_knock_800501F8(Actor_SnaInit *pActor, int time)
{
    void *func;

    if (time >= 8)
    {
        if (pActor->field_91C_weapon_idx != WEAPON_C4 || GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING) != 0)
        {
            if ((pActor->field_9B0_pad_ptr->press & PAD_CIRCLE) != 0)
            {
                func = sna_init_knock_80054D68;
                sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK9);
                pActor->field_9C0 = func;
                pActor->field_9C4 = 0;
            }
        }
    }
}

void sna_init_8005027C(Actor_SnaInit *pActor, int time)
{
    SVECTOR *pVec;

    if (pActor->field_91C_weapon_idx != WEAPON_C4)
    {
        return;
    }

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING))
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0;
    }

    if ((time < 8) || !(pActor->field_9B0_pad_ptr->press & PAD_SQUARE) || (pActor->field_9C0 == sna_init_80057378))
    {
        return;
    }

    if ((*pActor->field_918_pWeaponState != 0) && (used_counter_8009F42C < 16))
    {
        pVec = &stru_8009EFD4[0];

        if (pActor->field_A26_fn_stance_idx != SNA_STANCE_STANDING)
        {
            pVec = &stru_8009EFD4[1];
        }

        if (sna_init_8004F628(pActor, pVec, 300, 12, 81, -1) > 0)
        {
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK9);
            pActor->field_9C0 = sna_init_80057378;
            pActor->field_9C4 = 0;
            return;
        }
    }

    GM_Sound_80032968(0, 63, 35);
}

int sna_init_prone_check_standup_80050398(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) != 0 && sna_init_8004E808(pActor, 1, 0, 0xfffffd92, 1500) == 0)
    {

        pActor->field_A28 = 450;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_standup_80053D74);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_2, 4);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
        return 1;
    }

    return 0;
}

void sna_init_80050440(Actor_SnaInit *pActor)
{
    GM_Control *pCtrl;
    unsigned short *pArr;
    int inDuct;
    int i;

    // TODO: There is probably a better way to match this...
    Actor_SnaInit *pActor2;
    int a;
    
    if ((GM_GameOverTimer_800AB3D4 == 0) && (GM_SnakeCurrentHealth != 0))
    {
        pCtrl = &pActor->field_20_ctrl;
        pArr = pCtrl->field_10_pStruct_hzd_unknown.field_8_array;

        inDuct = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON_DUCT);
        
        for (i = pCtrl->field_10_pStruct_hzd_unknown.field_6_count; i > 0; pArr++, i--)
        {
            if (*pArr == 0x73D2)
            {
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON_DUCT);
                break;
            }
        }

        if (!inDuct)
        {
            if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
            {
                return;
            }
                
            sna_init_8004EC8C(pActor);
            // TODO: There is probably a better way to match this...
            pActor2 = pActor;
            a = 4;
            dword_800ABA1C = 0x100;
        }
        else
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
            {
                return;
            }
                
            sub_8004ED08(pActor);
            // TODO: There is probably a better way to match this...
            pActor2 = pActor;
            a = 4;
            dword_800ABA1C = 0;
        }

        sna_init_set_flags1_8004E2F4(pActor2, a);
        sna_init_set_flags2_8004E330(pActor, 0x100);

        pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
    }
}

void sna_init_80050568(Actor_SnaInit *pActor)
{
    short    dir;
    DG_OBJS *pDVar3;
    SVECTOR  local_10;

    sna_init_80050440(pActor);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        pDVar3 = pActor->field_9C_obj.objs;
        pActor->field_20_ctrl.field_4C_turn_vec.vz = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
        pActor->field_20_ctrl.field_44_movementVector.vz = 0;
        pActor->field_20_ctrl.field_44_movementVector.vx = 0;
    
        DG_InvisibleObjs(pDVar3);

        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
        pActor->field_A54.prone_bool_thing = 0;
        sna_init_set_invuln_8004F2A0(pActor, 24);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK1);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200 |
                                          PLAYER_STATUS_UNK100);
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5));
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 0);

        pDVar3 = (pActor->field_9C_obj).objs;
        // TODO: clean this up
        local_10.vx = *(short *)&pDVar3[8].movs - *(short *)pDVar3[1].world.t;
        pDVar3 = (pActor->field_9C_obj).objs;
        local_10.vz = pDVar3[9].world.m[0][2] - *(short *)(pDVar3[1].world.t + 2);

        dir = GV_VecDir2_80016EF8(&local_10);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dir;
        pActor->field_20_ctrl.field_8_rotator.vy = dir;
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    }
}

void sna_init_knockdown_getup_80050668(Actor_SnaInit *pActor)
{
    SVECTOR vec;
    int var_a2;
    int var_a3;
    int dir;
    DG_OBJS *pObjs;

    var_a2 = 500;

    if (pActor->field_A54.knockdown_thing == 1)
    {
        var_a2 = 2;
        var_a3 = -630;
    }
    else
    {
        var_a3 = -18;
    }

    if (!sna_init_8004E808(pActor, 1, var_a2, var_a3, 1500))
    {
        sna_init_set_invuln_8004F2A0(pActor, 0);
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_knockdown_getup_80054A10);
    }
    else
    {
        pActor->field_A54.knockdown_thing = 0;

        sna_init_set_invuln_8004F2A0(pActor, 24);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK1);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200 | PLAYER_STATUS_UNK100);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK5 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK2);

        DG_VisibleObjs(pActor->field_9C_obj.objs);

        if (pActor->field_9C_obj.action_flag == 0x45)
        {
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);

            // TODO: Duplication is probably from an inline
            pObjs = pActor->field_9C_obj.objs;
            vec.vx = pObjs->objs[6].world.t[0] - pObjs->objs[0].world.t[0];
            pObjs = pActor->field_9C_obj.objs;
            vec.vz = pObjs->objs[6].world.t[2] - pObjs->objs[0].world.t[2];

            dir = GV_VecDir2_80016EF8(&vec);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dir;
            pActor->field_20_ctrl.field_8_rotator.vy = dir;

            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_prone_idle_800528BC);
        }
        else
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
            sna_init_set_invuln_8004F2A0(pActor, 0);
            sna_init_set_flags1_8004E2F4(pActor, 4);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_8005425C);
        }
    }
}

int sub_800507D8(Actor_SnaInit *param_1)
{
    int ret;

    if (dword_800ABBC4 == 0 && param_1->field_A38 == 0)
    {
        param_1->field_A28 = 0x1c2;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_KNOCKING | PLAYER_STATUS_ON_WALL | PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(param_1, dword_8009EEA4[param_1->field_A26_fn_stance_idx]);
        sna_init_clear_flags1_8004E308(param_1, SNA_FLAG1_UNK9);
        param_1->field_9C0 = NULL;
        sna_init_8004E260(param_1, 0, 4, 0);
        GM_ExitBehindCamera_80030AEC();
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

void sna_init_act_helper3_80050878(Actor_SnaInit *pActor)
{
    int ret;
    int length;
    GV_MSG *pEntry;
    GV_MSG *pMsg;
    unsigned short id;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK80000) &&
        (GM_SnakeCurrentHealth != 0) &&
        (GM_GameOverTimer_800AB3D4 == 0) &&
        !GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK4))
    {
        sna_init_start_anim_8004E1F4(pActor, &sna_init_act_helper3_helper_80056650);
        sna_init_set_invuln_8004F2A0(pActor, 0);
        sna_act_unk2_80051170(pActor->field_89C_pTarget);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK80000);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK4);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK28);
    }
    
    if (sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK20))
    {
        return;
    }

    ret = GV_ReceiveMessage_80016620(pActor->field_20_ctrl.field_30_scriptData, &pMsg);
        
    if (ret == 0)
    {
        return;
    }

    length = ret;
        
    pEntry = &pActor->field_7A4_msgs[pActor->field_7A0_msg_count];
    pMsg = (pMsg + length) - 1;

    for (; length > 0; pActor->field_7A0_msg_count++, pMsg--, pEntry++, length--)
    {
        if (pActor->field_7A0_msg_count == 8)
        {
            break;
        }

        id = pMsg->message[0];

        if ((id == 0x937A) || (id == 0x70FB) || (id == 0x3238) || (id == 0xBE0A))
        {
            if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK4))
            {
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK4);
            }
        }

        *pEntry = *pMsg;
    }
}

static inline void sna_act_unk_helper_80050A64(Actor_SnaInit *pActor, GV_MSG *pMsg)
{
    UnkSnakeStruct2 *pStr;
    
    if (sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK28))
    {
        return;
    }
                        
    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK4);
        pMsg->message_len = 0;
    }
    else
    {
        pStr = &pActor->field_9E4;

        pActor->field_9FC = pActor->field_9B8_fn_anim;
        pStr->field_9EE = 0;
        pStr->field_9E8 = -1;
        pStr->field_9EA = pMsg->message[1];
        pStr->field_9EC_flags3 = 0;
        
        if (pMsg->message_len > 2)
        {
            pStr->field_9E8 = pMsg->message[2];
        }
                            
        if (pMsg->message_len > 3)
        {
            pStr->field_9EC_flags3 = pMsg->message[3];
        }
                                
        if (sna_act_unk_helper4_8004FA3C() && !(pStr->field_9EC_flags3 & 0x400))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK4);
            pMsg->message_len = 0;
            mts_printf_8008BBA0(aForceStanceCan);    
        }
        else
        {
            if (pStr->field_9EC_flags3 & 4)
            {
                pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
            }
                                    
            sna_init_start_anim_8004E1F4(pActor, &sna_act_unk_helper3_80055DD8);
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK28);
            pMsg->message_len = 0;    
            pStr->field_9F0 = 0;
        }
    }
}

static inline void sna_act_unk_helper2_80050A64(Actor_SnaInit *pActor, GV_MSG *pMsg)
{
    UnkSnakeStruct2 *pStr;
    
    if (sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK28))
    {
        return;
    }

    pStr = &pActor->field_9E4;

    pStr->field_9E8 = -1;
    pStr->field_9F4.vx = pMsg->message[1];
    pStr->field_9F4.vy = pMsg->message[2];
    pStr->field_9F4.vz = pMsg->message[3];
    pStr->field_9F4.pad = pMsg->message[4];
    pStr->field_9EC_flags3 = 0;
    
    if (pMsg->message_len > 5)
    {
        pStr->field_9EC_flags3 = pMsg->message[5];
    }

    if (sna_act_unk_helper4_8004FA3C() && !(pStr->field_9EC_flags3 & 0x400))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK4);
        pMsg->message_len = 0;
        mts_printf_8008BBA0(aRunMoveCancel);
    }
    else
    {
        if (pMsg->message_len > 6)
        {
            pStr->field_9E8 = pMsg->message[6];
        }
                        
        if (pStr->field_9EC_flags3 & 4)
        {
            pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
        }
                            
        pStr->field_9F0 = 0;
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_mini_cutscene_800559D8);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK28);
        pMsg->message_len = 0;
    }
}

static inline void sna_act_unk_helper3_80050A64(Actor_SnaInit *pActor, GV_MSG *pMsg, int var_s4)
{
    int flags;
    int len;
    UnkSnakeStruct2 *pStr;
    
    if (sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK28))
    {
        return;
    }

    flags = 0;
    len = pMsg->message_len;
    pStr = &pActor->field_9E4;

    pMsg->message_len = 0;
    pStr->field_9E4 = pMsg->message[1];
    pStr->field_9E6 = -1;
    pStr->field_9E8 = -1;
    pStr->field_9EA = -1;
    pStr->field_9EC_flags3 = 0;

    if (len > 2)
    {
        pStr->field_9E6 = pMsg->message[2];
    }

    if (len > 3)
    {
        pStr->field_9E8 = pMsg->message[3];
    }

    if (len > 4)
    {
        pStr->field_9EA = pMsg->message[4];
    }

    if (len > 5)
    {
        flags = pStr->field_9EC_flags3 = pMsg->message[5];
    }
                      
    if (sna_act_unk_helper4_8004FA3C() && (var_s4 == 0))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK4);
        pMsg->message_len = 0;
        mts_printf_8008BBA0(aForceActCancel);
    }
    else
    {
        pStr->field_9F2 = 0;

        if (var_s4 != 0)
        {
            pStr->field_9F2 = 1;
        }

        if (!(flags & 0x80))
        {
            if (!pActor->field_A5A)
            {
                return;
            }

            GM_ConfigMotionControl_80034F08(&pActor->field_9C_obj, &pActor->field_180, pActor->field_A5A,
                                            &pActor->field_1D0, &pActor->field_1F4[16], &pActor->field_20_ctrl,
                                            (SVECTOR *)&pActor->field_698_joint_rotations);
        }

        if (flags & 4)
        {
            if (len <= 6)
            {
                return;
            }

            pStr->field_9EE = pActor->field_20_ctrl.field_0_position.vy - pMsg->message[6];
        }
        else
        {
            pStr->field_9EE = pActor->field_20_ctrl.field_78;
        }
                     
        if (flags & 1)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(2);
            sub_8004ED08(pActor);
        }
                                            
        if (flags & 0x10)
        {
            pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
        }
                                                
        pStr->field_9F0 = 1;

        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_dying_80055524);
        GM_SetPlayerStatusFlag_8004E2B4(4);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK28);
    }
}

void sna_act_unk_80050A64(Actor_SnaInit *pActor)
{
    int unk[2];
    GV_MSG *pMsg;
    GV_MSG *pMsgIter;
    int msgCount;
    int count;
    int state;
    
    if ((pActor->field_7A0_msg_count == 0) || sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK18))
    {
        return;
    }

    msgCount = 0;
    pMsgIter = pActor->field_7A4_msgs;
    pMsg = pActor->field_7A4_msgs;
    
    for (count = pActor->field_7A0_msg_count; count > 0; count--, pMsg++)
    {        
        switch (pMsg->message[0])
        {
        case 0xc000:
            pMsg->message_len = 0;
            break;
            
        case 0x937a:
            state = 0;
            goto helper3;

        case 0xbe0a:
            state = 1;
helper3:
            sna_act_unk_helper3_80050A64(pActor, pMsg, state);
            break;

        case 0x70fb:
            sna_act_unk_helper2_80050A64(pActor, pMsg);
            break;

        case 0x3238:
            sna_act_unk_helper_80050A64(pActor, pMsg);
            break;

        case 0x5e8b:
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK19);
            pMsg->message_len = 0;
            break;

        case 0x9a1f:
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK19);
            pMsg->message_len = 0;
            break;
            
        case 0x3223:
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            pMsg->message_len = 0;
            break;

        case 0x2580:
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000);
            pMsg->message_len = 0;
            break;
            
        case 0xaf6a:
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000);
            pMsg->message_len = 0;
            break;

        case 0x8012:
            dword_8009F2C0 = pMsg->message[1];
            pMsg->message_len = 0;
            break;

        case 0x62b6:
            pActor->field_20_ctrl.field_0_position.vx = pMsg->message[1];
            pActor->field_20_ctrl.field_0_position.vy = pMsg->message[2];
            pActor->field_20_ctrl.field_0_position.vz = pMsg->message[3];
            pActor->field_20_ctrl.field_44_movementVector = DG_ZeroVector_800AB39C;
            sub_8004E588(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl.field_0_position, unk);
            pActor->field_20_ctrl.field_78 = unk[0];
            pActor->field_20_ctrl.field_7A = unk[1];
            pMsg->message_len = 0;
            break;

        case 0x3e92:
            if (pMsg->message[1] == 0xe4e)
            {
                sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG2_UNK27);
                pMsg->message_len = 0;
            }
            else
            {
                sna_init_clear_flags1_8004E308(pActor, SNA_FLAG2_UNK27);
                pMsg->message_len = 0;
            }

            break;

        default:
            pMsg->message_len = 0;
            break;
        } 

    
        if (pMsg->message_len != 0)
        {
            *pMsgIter = *pMsg;
            pMsgIter++;
            msgCount++;
        }
    }

    pActor->field_7A0_msg_count = msgCount;
}

void sna_act_unk2_80051170(GM_Target *param_1)
{
    param_1->field_28 = 0;
    param_1->field_2A = 0;
    param_1->field_6_flags &= ~(0x80 | 0x04);
    param_1->field_2C_vec = DG_ZeroVector_800AB39C;
    param_1->field_44 = -1;
    param_1->field_3E = 0;
}

#pragma INCLUDE_ASM("asm/sna_init_weapon_switching_800511BC.s")        // 1024 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_800515BC.s")             // 1108 bytes

void sna_init_80051A10(Actor_SnaInit *pActor, SVECTOR *pPos, SVECTOR *pOut, SVECTOR *pVec)
{
    MATRIX rot;
    SVECTOR vec;
    SVECTOR vec2;
    SVECTOR vec3;
    SVECTOR vec4;

    int len;

    ReadRotMatrix_80092DD8(&rot);
    DG_SetPos2_8001BC8C(pPos, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutVector_8001BE48(pVec, pVec, 1);
    SetRotMatrix_80093218(&rot);

    vec = *pPos;
    vec2 = *pVec;

    if (sub_8004E51C(&vec, pActor->field_20_ctrl.field_2C_map->field_8_hzd, 15, 1) < 0)
    {
        vec2 = *pVec;
    }

    GV_SubVec3_80016D40(&vec2, pPos, &vec3);
    len = GV_VecLen3_80016D80(&vec3);

    if ((len - pActor->field_A28) <= 0)
    {
        vec3 = *pPos;
    }
    else
    {
        GV_LenVec3_80016DDC(&vec3, &vec4, len, len - pActor->field_A28);
        GV_AddVec3_80016D00(pPos, &vec4, &vec3);
    }

    *pOut = vec3;
}

int sna_init_80051BA4(Actor_SnaInit *pActor)
{
    SVECTOR vec;
    SVECTOR vec2;
    SVECTOR vec3;
    
    GV_PAD *pPad = pActor->field_9B0_pad_ptr;
    unsigned short press = pPad->press;
    unsigned short release = pPad->release;

    if (pPad->status & (PAD_R1 | PAD_L1))
    {
        if (press & PAD_R1)
        {
            pActor->field_A56 = 8;
        }

        if (press & PAD_L1)
        {
            pActor->field_A56 = 4;
        }

        if (release & PAD_R1)
        {
            pActor->field_A56 = 4;
        }

        if (release & PAD_L1)
        {
            pActor->field_A56 = 8;
        }

        vec2 = vec = DG_ZeroVector_800AB39C;
        vec2.vx = 1280;
        vec.vx = -1280;
        vec3 = pActor->field_A60;

        sna_init_80051A10(pActor, &vec3, &pActor->field_A3C, &vec2);
        sna_init_80051A10(pActor, &vec3, &pActor->field_A44, &vec);

        if (!sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK16))
        {
            pActor->field_A58 = 8;
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK16);
        }
        else if (pActor->field_A56 & 4)
        {
            pActor->field_A60 = pActor->field_A3C;

        }
        else if (pActor->field_A56 & 8)
        {
            pActor->field_A60 = pActor->field_A44;
        }

        return 1;
    }

    if (pActor->field_A58 > 0)
    {
        if (--pActor->field_A58 == 0)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK16);
            return 0;
        }

        return 1;
    }

    return 0;
}

void sna_init_80051DA0(Actor_SnaInit *pActor)
{
    unsigned int status = pActor->field_9B0_pad_ptr->status;
    unsigned char ldy = pActor->field_9B0_pad_ptr->left_dy;
    short *temp_s4;
    int var_s1;
    int var_s2;
    int var_s0;
    int temp_v0;
    int temp_a1;
    short var_a0;
    short var_a2;

    // status is passed using the wrong type here
    GM_CheckShukanReverse_8004FBF8((unsigned short *)&status);
    GM_CheckShukanReverseAnalog_8004FC70(&ldy);

    temp_s4 = pActor->field_9D0;
    var_s2 = temp_s4[4];
    var_s1 = -temp_s4[3];

    if (pActor->field_9D0[0] == 0)
    {
        if (pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND)
        {
            var_s0 = pActor->field_A2A;
        }
        else
        {
            var_s0 = 0;
        }
    }
    else
    {
        var_s0 = pActor->field_20_ctrl.field_4C_turn_vec.vx;
    }

    if (pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND)
    {
        if (pActor->field_91C_weapon_idx == WEAPON_PSG1)
        {
            temp_v0 = pActor->field_A2A;
            var_s1 += temp_v0;
            var_s2 += temp_v0;
        }
        else
        {
            var_s1 += var_s0;
            var_s2 += var_s0;
        }
    }

    if (var_s1 < dword_800ABBDC)
    {
        var_s1 = dword_800ABBDC;
    }

    if (var_s2 > dword_800ABBD4)
    {
        var_s2 = dword_800ABBD4;
    }

    temp_a1 = sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK15);
    var_a2 = 1;
    var_a0 = 1;

    if (status & PAD_UP)
    {
        if (temp_a1 & 0xff)
        {
            var_a0 = 64 - ldy;
            var_a2 = 64;
        }

        var_s0 -= (temp_s4[5] * (var_a0 & 0xff)) / var_a2;
    }
    else if (status & PAD_DOWN)
    {
        if (temp_a1 & 0xff)
        {
            var_a0 = ldy + 64;
            var_a2 = 63;
        }

        var_s0 += (temp_s4[6] * (var_a0 & 0xff)) / var_a2;
    }


    if (var_s0 < var_s1)
    {
        var_s0 = var_s1;
    }

    if (var_s2 < var_s0)
    {
        var_s0 = var_s2;
    }

    pActor->field_20_ctrl.field_4C_turn_vec.vx = var_s0;
}

void sna_init_80051FD0(Actor_SnaInit *pActor)
{
    int          iVar1;
    ushort       uVar2;
    unsigned int uVar3;
    short        sVar4;
    short        sVar5;
    int          iVar6;
    short     *short_arr;

    short_arr = pActor->field_9D0;
    uVar2 = pActor->field_9B0_pad_ptr->status;
    if ((uVar2 & (PAD_LEFT | PAD_RIGHT)) != 0)
    {
        iVar1 = pActor->field_20_ctrl.field_4C_turn_vec.vy;
        uVar3 = sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK15);
        sVar4 = 1;
        sVar5 = 1;
        if (uVar2 & PAD_LEFT)
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x40;
                sVar5 = 0x40 - (*((unsigned char *)((short *)pActor->field_9B0_pad_ptr + 7)));
            }
            iVar6 = ((int)short_arr[8]) * (sVar5 & 0xff);
            iVar1 += iVar6 / sVar4;
        }
        else
        {
            if ((uVar3 & 0xff) != 0)
            {
                sVar4 = 0x3f;
                sVar5 = (*((unsigned char *)((short *)pActor->field_9B0_pad_ptr + 7))) + 0x40;
            }
            iVar6 = ((int)short_arr[7]) * (sVar5 & 0xff);
            iVar1 -= iVar6 / sVar4;
        }
        pActor->field_20_ctrl.field_4C_turn_vec.vy = iVar1;
    }
}

void sna_init_fn_80052120(Actor_SnaInit *pActor, int time)
{
    unsigned short press;
    int            sound;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
    {
        if (GM_UnkFlagBE == 0)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }

        sna_init_set_invuln_8004F2A0(pActor, 0);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_enter_duct_80053E9C);
    }
    else
    {
        press = pActor->field_9B0_pad_ptr->press;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, sna_init_8004EAA8(pActor, (int)pActor->field_A26_fn_stance_idx), 4);

        if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
        {
            if (GM_UnkFlagBE == 0)
            {
                sna_init_8004EC00(pActor);
            }
            else
            {
                sna_init_8004FA74(pActor);
            }

            sna_init_start_anim_8004E1F4(pActor, dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
        }
        else
        {
            if (sna_init_80051BA4(pActor))
            {
                return;
            }

            sna_init_80051DA0(pActor);
            sna_init_80051FD0(pActor);

            if ((press & PAD_CROSS) != 0)
            {
                switch (pActor->field_A26_fn_stance_idx)
                {
                case 0:
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_crouch_800527DC);
                    break;
                case 2:
                    if (sna_init_8004E808(pActor, 1, 0, -0x26e, 0x5dc) != 0)
                    {
                        return;
                    }
                default:
                    if (sna_init_8004E808(pActor, 0, 0, 0, 0x5dc) != 0)
                    {
                        return;
                    }

                    pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
                    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_PRONE);

                    sound = 8;
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
                    {
                        sound = 0xb7;
                    }

                    GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
                    break;
                }
            }
        }
    }
}

void sub_8005230C(Actor_SnaInit *pActor)
{
    int            action;
    unsigned short status;
    unsigned short press;

    status = pActor->field_9B0_pad_ptr->status;
    press = pActor->field_9B0_pad_ptr->press;

    if ((status & PAD_TRIANGLE) == 0)
    {
        sna_init_8004EC00(pActor);
        pActor->field_A38 = 2;
    }
    else
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING) != 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);

            if (pActor->field_A26_fn_stance_idx == SNA_STANCE_STANDING)
            {
                action = pActor->field_9B4_action_table->field_0->field_4;
            }
            else
            {
                action = pActor->field_9B4_action_table->field_0->field_5;
            }

            sna_init_8004E22C(pActor, action, 4);
        }
        if (((press & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) != 0) ||
            ((status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) == 0))
        {

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_ON_WALL);
            pActor->field_A28 = 0x1c2;
            sna_init_start_anim_8004E1F4(pActor, dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
            GM_ExitBehindCamera_80030AEC();
        }

        if (!sna_init_80051BA4(pActor) && (press & PAD_CROSS) != 0)
        {
            if (pActor->field_A26_fn_stance_idx == SNA_STANCE_STANDING)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_crouch_80052CCC);
            }
            else
            {
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_idle_and_c4_80052A5C);
            }
        }
    }
}

void sub_80052468(Actor_SnaInit *pActor)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        pActor->field_A56 = 0;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                          PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        sna_init_set_invuln_8004F2A0(pActor, 0);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_enter_duct_80053E9C);
    }
    else
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);

        if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
        {
            pActor->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK400 |
                                              PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
            sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK6);
        }

        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
    }
}

void sna_init_fn_80052540(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        if (GM_UnkFlagBE == 0)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }
    }

    if (pActor->field_9B8_fn_anim == sna_init_anim_knockdown_idle_80054930 &&
        ((pActor->field_9B0_pad_ptr->press & ~PAD_TRIANGLE) != 0))
    {
        sna_init_knockdown_getup_80050668(pActor);
    }

    gUnkCameraStruct_800B77B8.field_0.vy += 320;
    sna_init_8004EE28(pActor);
}

void sna_init_fn_800525F8(Actor_SnaInit *pActor)
{
    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    if (pActor->field_9B8_fn_anim != sna_init_anim_box_idle_800553EC)
    {
        if (pActor->field_9C_obj.field_1A)
        {
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_2, 4);
        }
    }

    if (!(pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE))
    {
        if (!GM_UnkFlagBE)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }
    else
    {
        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
    }
}

void sna_init_act_helper2_helper_helper_800526BC(Actor_SnaInit *pActor)
{
    if ((pActor->field_9B0_pad_ptr->status & PAD_TRIANGLE) == 0)
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
        {
            pActor->field_A56 = 0;
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH |
                                              PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK | PLAYER_STATUS_FIRST_PERSON);
        }
        else if (!GM_UnkFlagBE)
        {
            sna_init_8004EC00(pActor);
        }
        else
        {
            sna_init_8004FA74(pActor);
        }
    }

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
    {
        sna_init_8004EE28(pActor);
    }
}

void sna_init_anim_idle_8005275C(Actor_SnaInit *pActor, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_80052E58;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;

        if (GM_AlertMode_800ABA00 >= 3)
        {
            action_flag = pActor->field_9B4_action_table->field_0->field_1;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_0->field_0;
        }

        sna_init_8004E22C(pActor, action_flag, 4);
    }
}

void sna_init_anim_crouch_800527DC(Actor_SnaInit *param_1, int time)
{
    int sound;

    if (time == 0)
    {
        if (param_1->field_A26_fn_stance_idx != SNA_STANCE_CROUCH)
        {
            sound = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }
            GM_SeSet_80032858(&param_1->field_20_ctrl.field_0_position, sound);
        }

        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_crouch_helper_80053014;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_0->field_2, 4);
        param_1->field_A2C.vy = -128;
    }

    if ((time == 0 && param_1->field_A26_fn_stance_idx != SNA_STANCE_STANDING) ||
        (time == 4 && param_1->field_A26_fn_stance_idx == SNA_STANCE_STANDING))
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING);
        param_1->field_A26_fn_stance_idx = SNA_STANCE_CROUCH;
    }
}

void sna_init_anim_prone_idle_800528BC(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        pActor->field_A28 = 450;
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800531F4;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
    }
}

void sna_init_anim_run_8005292C(Actor_SnaInit *pActor, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_80053360;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        if (GM_AlertMode_800ABA00 >= 3)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_7;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_0;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
    }
}

void sna_init_anim_prone_move_800529C0(Actor_SnaInit *pActor, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        pActor->field_A28 = 450;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800535B8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        if (pActor->field_A54.prone_bool_thing)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_4;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_3;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_A54.prone_bool_thing = 0;
    }
    sna_init_80050440(pActor);
}

void sna_init_anim_wall_idle_and_c4_80052A5C(Actor_SnaInit *pActor, int time)
{
    int sVar3;
    int sound;

    if (time == 0)
    {
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_ON_WALL) == 0)
        {
            sound = 7;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_ON_WALL);
        }

        sVar3 = pActor->field_91C_weapon_idx != WEAPON_C4 ? 300 : 472;

        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_wall_idle_and_c4_helper_800537D4;
        pActor->field_A28 = sVar3;
        pActor->field_A26_fn_stance_idx = 0;
        pActor->field_9CC_anim_update_fn_1p = sub_8005230C;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_4, 4);
    }

    GM_CheckBehindCamera_80030B3C(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl);

    if (pActor->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        (pActor->field_20_ctrl).field_44_movementVector.vx += pVec_800ABBCC->vx / 8;
        (pActor->field_20_ctrl).field_44_movementVector.vz += pVec_800ABBCC->vz / 8;
        pActor->field_A3A++;
    }

    return;
}

void sna_init_anim_wall_move_80052BA8(Actor_SnaInit *pActor, int time)
{
    int action;

    if (time == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING | PLAYER_STATUS_ON_WALL);
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_wall_move_helper_800538CC;
        pActor->field_9CC_anim_update_fn_1p = sub_8005230C;

        if (pActor->field_A54.wall_thing == 2)
        {
            action = pActor->field_9B4_action_table->field_4->field_5;
        }
        else
        {
            action = pActor->field_9B4_action_table->field_4->field_6;
        }

        pActor->field_A28 = 300;
        pActor->field_A54.wall_thing = 0;
        sna_init_8004E22C(pActor, action, 4);
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
    }

    if (pActor->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        pActor->field_20_ctrl.field_44_movementVector.vx += pVec_800ABBCC->vx / 8;
        pActor->field_20_ctrl.field_44_movementVector.vz += pVec_800ABBCC->vz / 8;
        pActor->field_A3A++;
    }
}

void sna_init_anim_wall_crouch_80052CCC(Actor_SnaInit *pActor, int time)
{
    int sound;
    int sound2;

    if (time == 0)
    {
        if (pActor->field_A26_fn_stance_idx != SNA_STANCE_CROUCH)
        {
            sound = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
        }

        pActor->field_A26_fn_stance_idx = SNA_STANCE_CROUCH;
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_wall_crouch_helper_80053A54;
        pActor->field_9CC_anim_update_fn_1p = sub_8005230C;

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_ON_WALL) == 0)
        {
            sound2 = 7;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound2 = 0xb7;
            }
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound2);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
        }

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_ON_WALL);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_5, 4);

        pActor->field_A28 = pActor->field_91C_weapon_idx != WEAPON_C4 ? 300 : 472;
    }

    GM_CheckBehindCamera_80030B3C(((pActor->field_20_ctrl).field_2C_map)->field_8_hzd, &pActor->field_20_ctrl);

    if (pActor->field_A3A < 8 && pVec_800ABBCC != NULL)
    {
        pActor->field_20_ctrl.field_44_movementVector.vx += pVec_800ABBCC->vx / 8;
        pActor->field_20_ctrl.field_44_movementVector.vz += pVec_800ABBCC->vz / 8;
        pActor->field_A3A++;
    }
}

void sna_init_fn_80052E58(Actor_SnaInit *pActor)
{
    int action;
    int diff;

    if (sna_init_8005009C(pActor))
    {
        return;
    }

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) != 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_crouch_800527DC);
        return;
    }

    if (GM_AlertMode_800ABA00 >= 3)
    {
        action = pActor->field_9B4_action_table->field_0->field_1;
    }
    else
    {
        action = pActor->field_9B4_action_table->field_0->field_0;
    }

    sna_init_8004E22C(pActor, action, 4);

    if (pActor->field_A38 > 0)
    {
        pActor->field_A38--;
    }

    if (pActor->field_A38 == 0 && gSnaMoveDir_800ABBA4 >= 0)
    {
        if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && pActor->field_79C == 2))
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_idle_and_c4_80052A5C);
        }
        else
        {
            if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
            {
                diff = GV_DiffDirAbs_8001706C(pActor->field_20_ctrl.field_4C_turn_vec.vy, gSnaMoveDir_800ABBA4);
                if (diff > 256)
                {
                    pActor->field_A38 = diff / 1024 + 1;
                }
                else
                {
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_begin_80053B88);
                }

                pActor->field_20_ctrl.field_4C_turn_vec.vy = gSnaMoveDir_800ABBA4;
            }
            else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_begin_80053B88);
            }
            else
            {
                sna_init_80051FD0(pActor);
            }
        }
    }
}

void sna_init_anim_crouch_helper_80053014(Actor_SnaInit *pActor)
{
    int diff;
    int sound;

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) != 0)
    {
        if (sna_init_8004E808(pActor, 0, 0, 0, 1100) == 0)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;

            sound = 8;
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
            {
                sound = 0xb7;
            }

            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
    }
    else
    {
        if (pActor->field_A38 > 0)
        {
            pActor->field_A38--;
        }

        if (pActor->field_A38 == 0 && gSnaMoveDir_800ABBA4 >= 0)
        {
            if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && pActor->field_79C == 2))
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_crouch_80052CCC);
            }
            else
            {
                if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
                {
                    diff = GV_DiffDirAbs_8001706C(pActor->field_20_ctrl.field_4C_turn_vec.vy, gSnaMoveDir_800ABBA4);
                    if (diff > 256)
                    {
                        pActor->field_A38 = diff / 1024 + 1;
                    }
                    else
                    {
                        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_begin_80053BE8);
                    }

                    pActor->field_20_ctrl.field_4C_turn_vec.vy = gSnaMoveDir_800ABBA4;
                }
                else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
                {
                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_begin_80053BE8);

                    if ((pActor->field_9B0_pad_ptr->status & PAD_DOWN) != 0)
                    {
                        pActor->field_20_ctrl.field_4C_turn_vec.vy += 2048;
                    }
                }
                else
                {
                    sna_init_80051FD0(pActor);
                }
            }
        }
    }
}

void sna_init_fn_800531F4(Actor_SnaInit *pActor)
{
    if (pActor->field_A38 > 0)
    {
        pActor->field_A38 -= 1;
    }

    if (!sna_init_prone_check_standup_80050398(pActor) && pActor->field_A38 == 0 && gSnaMoveDir_800ABBA4 >= 0)
    {
        if (dword_800ABBC4 == 1 || (dword_800ABBC4 != 0 && pActor->field_79C == 2))
        {
            if (sna_init_8004E808(pActor, 0, 0, 0, 1500) == 0)
            {
                pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_ON_WALL);
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_wall_crouch_80052CCC);
            }
        }
        else
        {
            if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
            {
                if (sub_8004E458(pActor->field_20_ctrl.field_4C_turn_vec.vy, gSnaMoveDir_800ABBA4) == 3)
                {
                    pActor->field_A54.prone_bool_thing = 1;
                }
                else
                {
                    pActor->field_A54.prone_bool_thing = 0;
                }

                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_move_800529C0);
            }
            else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_move_800529C0);
            }
            else
            {
                sna_init_80051FD0(pActor);
                pActor->field_20_ctrl.field_4C_turn_vec.vx = pActor->field_A2A;
            }
        }
    }
}

void sna_init_80053360(Actor_SnaInit *pActor)
{
    int angle;

    if (sna_init_8005009C(pActor))
    {
        return;
    }

    if (pActor->field_9B0_pad_ptr->press & PAD_CROSS)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_crouch_800527DC);
        return;
    }

    if (gSnaMoveDir_800ABBA4 < 0)
    {        
        if (++pActor->field_A3A >= 5)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_idle_8005275C);
            return;
        }
    }
    else
    {
        pActor->field_A3A = 0;   
    }


    if ((dword_800ABBC4 == 1) || ((dword_800ABBC4 != 0) && (pActor->field_79C == 2)))
    {
        if (++pActor->field_A38 >= 3)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_idle_and_c4_80052A5C);
            return;
        }
    }
    else
    {
        pActor->field_A38 = 0;   
    }

    if (sna_init_sub_8004E358(pActor, 16) == 0)
    {
        if (pActor->field_A38 == 0)
        {
            if (gSnaMoveDir_800ABBA4 >= 0)
            {
                angle = sub_8004E4C0(pActor, gSnaMoveDir_800ABBA4);
            }
            else
            {
                angle = pActor->field_20_ctrl.field_4C_turn_vec.vy;
            }
        }
        else
        {
            angle = gSnaMoveDir_800ABBA4;

            if (angle < 0)
            {
                angle = pActor->field_20_ctrl.field_4C_turn_vec.vy;
            }
        }

        if (GV_DiffDirAbs_8001706C(pActor->field_20_ctrl.field_4C_turn_vec.vy, angle) > 1048)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_idle_8005275C);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = angle;
            return;
        }

        pActor->field_20_ctrl.field_4C_turn_vec.vy = angle;
        sub_8004EA50(pActor, angle);
    }
    else
    {
        if (!(pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_idle_8005275C);
            return;
        }

        sub_8004FA9C(pActor);
    }

    if (GM_AlertMode_800ABA00 >= 3)
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_4->field_7, 4);
    }
    else
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_4->field_0, 4);
    }
}

void sna_init_fn_800535B8(Actor_SnaInit *pActor)
{
    int var_s0;
    int temp_s2;
    int temp_s3;
    unsigned char var_a1;
    unsigned char var_a1_2;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
    {
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_enter_duct_80053E9C);
        sna_init_set_invuln_8004F2A0(pActor, 0);
        return;
    }

    if (!sna_init_prone_check_standup_80050398(pActor))
    {
        if (gSnaMoveDir_800ABBA4 < 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_prone_idle_800528BC);
            return;
        }
        

        if ((dword_800ABBC4 == 1) || ((dword_800ABBC4 != 0) && (pActor->field_79C == 2)))
        {
            if (!sna_init_8004E808(pActor, 0, 0, 0, 1500))
            {
                pActor->field_20_ctrl.field_4C_turn_vec.vy = pActor->field_20_ctrl.field_8_rotator.vy;
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE | PLAYER_STATUS_MOVING);
                GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_ON_WALL | PLAYER_STATUS_CROUCHING);
                sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_crouch_80052CCC);
            }
        }
        else
        {
            temp_s3 = pActor->field_9B4_action_table->field_4->field_3;
            temp_s2 = pActor->field_9B4_action_table->field_4->field_4;

            if (!sna_init_sub_8004E358(pActor, 16))
            {
                if (pActor->field_9C_obj.action_flag == temp_s2)
                {
                    var_s0 = gSnaMoveDir_800ABBA4 + 2048;
                }
                else
                {
                    var_s0 = gSnaMoveDir_800ABBA4;
                }

                if (sub_8004E458(pActor->field_20_ctrl.field_4C_turn_vec.vy, var_s0) == 3)
                {
                    var_s0 += 2048;
                    var_a1 = temp_s3;

                    if (pActor->field_9C_obj.action_flag == var_a1)
                    {
                        var_a1 = temp_s2;
                    }

                    sna_init_8004E22C(pActor, (var_a1), 4);
                }

                pActor->field_20_ctrl.field_4C_turn_vec.vy = sub_8004E4C0(pActor, var_s0);
                return;
            }

            if (!(pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)))
            {
                GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
                sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
                sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_prone_idle_800528BC);
                return;
            }

            var_a1_2 = temp_s2;

            if (pActor->field_9B0_pad_ptr->status & PAD_UP)
            {
                var_a1_2 = temp_s3;
            }

            sna_init_8004E22C(pActor, var_a1_2, 4);
            sna_init_80051FD0(pActor);

            pActor->field_20_ctrl.field_4C_turn_vec.vx = pActor->field_A2A;
        }
    }
}

void sna_init_anim_wall_idle_and_c4_helper_800537D4(Actor_SnaInit *pActor, int time)
{
    if (pActor->field_A38 != 0)
    {
        pActor->field_A38--;
    }

    if (sub_800507D8(pActor))
    {
        return;
    }

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) && !sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK9))
    {
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_crouch_80052CCC);
        return;
    }

    if ((dword_800ABBC4 == 2) || (dword_800ABBC4 == 4))
    {
        pActor->field_A54.wall_thing = dword_800ABBC4;
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_move_80052BA8);
    }

    if ((dword_800ABBD0 - 2048) != pActor->field_20_ctrl.field_8_rotator.vy)
    {
        pActor->field_A3A = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
    }

    sna_init_check_knock_800501F8(pActor, time);
    sna_init_8005027C(pActor, time);
}

void sna_init_anim_wall_move_helper_800538CC(Actor_SnaInit *pActor, int time)
{
    int var_s1;

    if (pActor->field_A38 != 0)
    {
        pActor->field_A38--;
    }

    if (sub_800507D8(pActor))
    {
        return;
    }

    GM_CheckBehindCamera_80030B3C(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl);

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) && !sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK9))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_crouch_80052CCC);
        return;
    }

    if (dword_800ABBC4 == 1)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_idle_and_c4_80052A5C);
        return;
    }

    if (((dword_800ABBD0 - 2048) != pActor->field_20_ctrl.field_8_rotator.vy) || (pVec_800ABBC8 != pVec_800ABBCC))
    {
        pActor->field_A3A = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
    }

    sna_init_check_knock_800501F8(pActor, time);
    sna_init_8005027C(pActor, time);

    if (dword_800ABBC4 == 2)
    {
        var_s1 = pActor->field_9B4_action_table->field_4->field_5;
    }
    else
    {
        var_s1 = pActor->field_9B4_action_table->field_4->field_6;
    }

    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
    sna_init_8004E22C(pActor, var_s1, 4);
}

void sna_init_anim_wall_crouch_helper_80053A54(Actor_SnaInit *pActor, int time)
{
    int var_s0;

    if (pActor->field_A38 != 0)
    {
        pActor->field_A38--;
    }

    if (sub_800507D8(pActor))
    {
        return;
    }

    if ((pActor->field_9B0_pad_ptr->press & PAD_CROSS) && !sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK9))
    {
        if (!sna_init_8004E808(pActor, 0, 0, 0, 1100))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
            var_s0 = 8;
            
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000))
            {
                var_s0 = 183;
            }

            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, var_s0);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_wall_idle_and_c4_80052A5C);
        }
    }
    else
    {
        if (!(GM_GameStatus_800AB3CC & 0x10) && ((dword_800ABBD0 - 2048) != pActor->field_20_ctrl.field_8_rotator.vy))
        {
            pActor->field_A3A = 0;
            pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBD0 - 2048;
        }

        sna_init_check_knock_800501F8(pActor, time);
        sna_init_8005027C(pActor, time);
    }
}

void sna_init_fn_nothing_80053B80(void)
{
}

void sna_init_anim_run_begin_80053B88(Actor_SnaInit *param_1, int time)
{
    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_80054318;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_80052120;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_1, 4);
    }
}

void sna_init_anim_prone_begin_80053BE8(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_0, 4);
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        pActor->field_20_ctrl.field_55_flags |= (CONTROL_FLAG_UNK8 | CONTROL_FLAG_UNK2);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
    }

    if (time == 7)
    {
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK2;
    }

    switch (pActor->field_A38)
    {
    case 0:
        if (pActor->field_798 < 0xfa)
        {
            pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
        }

        if (pActor->field_9C_obj.field_1A != 0)
        {
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
            pActor->field_A38 = 1;
        }
        break;
    case 1:
        sna_init_80050440(pActor);

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_enter_duct_80053E9C);
            sna_init_set_invuln_8004F2A0(pActor, 0);
            sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_4->field_3, 4);
        }
        else
        {
            sna_init_clear_flags1_8004E308(pActor, 0x30);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        }
    }
}

void sna_init_anim_prone_standup_80053D74(Actor_SnaInit *pActor, int time)
{
    int sound;

    if (time == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_8->field_2, 4);

        sound = 8;
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000000) != 0)
        {
            sound = 0xb7;
        }
        GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, sound);
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }

    if (pActor->field_20_ctrl.field_32_height >= 250)
    {
        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK8;
    }

    if (pActor->field_20_ctrl.field_32_height > 500)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
    }

    if (time == 2)
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if (time == 7)
    {
        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK2;
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        pActor->field_20_ctrl.field_55_flags &= ~(CONTROL_FLAG_UNK8 | CONTROL_FLAG_UNK2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }
}

void sna_init_anim_enter_duct_80053E9C(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_800543A8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));

        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0 &&
            pActor->field_9C_obj.action_flag == pActor->field_9B4_action_table->field_4->field_4)
        {
            pActor->field_A38 = 48;
        }
        else
        {
            pActor->field_A38 = 24;
        }
    }

    if (time == pActor->field_A38)
    {
        sna_init_clear_invuln_8004F2EC(pActor);
        sna_init_80050440(pActor);
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
        sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK9);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
        }
        else
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        }
    }
}

void sub_80053FAC(Actor_SnaInit *pActor, int time)
{
    short          vec_y;      // $v1
    unsigned short pad_status; // $s1

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_3, 2);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK3);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
        vec_y = pActor->field_A54.prone_bool_thing;
        pActor->field_A54.prone_bool_thing = 0;
        pActor->field_90C_pWeaponFn = sna_init_gun_800540D0;
        pActor->field_910 = 0;
        pActor->field_926 = 0;
        pActor->field_924 = 0;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = vec_y;
        sna_init_8004E260(pActor, 0, 4, 0);
    }

    pad_status = pActor->field_9B0_pad_ptr->status;
    if (pActor->field_9C_obj.field_1A || (pad_status & PAD_SQUARE) == 0)
    {
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        pActor->field_910 = 0;
        if ((pad_status & PAD_SQUARE) != 0)
        {
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 9);
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_shoot_weapon_80056B88);
            pActor->field_90C_pWeaponFn = sub_80057BF0;
            pActor->field_910 = 0;
            pActor->field_926 = 0;
            pActor->field_924 = 0;
        }
        else
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
    }
}

void sna_init_gun_800540D0(Actor_SnaInit *pActor, int time)
{
    int iVar1;
    int a4;

    if (time == 0)
    {
        iVar1 = GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING);
        a4 = 0xffff;
        if (iVar1 != 0)
        {
            a4 = 0x3fe;
        }
        sna_init_8004E260(pActor, pActor->field_9B4_action_table->field_10->field_0, 4, a4);
        pActor->field_A38 = 0;
    }

    if ((pActor->field_9B0_pad_ptr->release & PAD_SQUARE) != 0)
    {
        pActor->field_A38 = 1;
    }

    if ((pActor->field_9B0_pad_ptr->status & PAD_SQUARE) != 0)
    {
        pActor->field_926++;
    }
    else
    {
        pActor->field_926 = 0;
    }

    if (time == 8)
    {
        pActor->field_90C_pWeaponFn = sub_80057BF0;
        pActor->field_910 = 0;
        pActor->field_926 = 0;
        pActor->field_924 = 0;
    }
}

void sna_init_bomb_800541A8(Actor_SnaInit *pActor)
{
    void *pFn; // $a1

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
    pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
    if (sna_init_8004FDE8(pActor, &stru_8009EFE4))
    {
        pFn = sna_init_800571B8;
    }
    else
    {
        pFn = sna_init_80057118;
    }
    sna_init_start_anim_8004E1F4(pActor, pFn);
}

// or sna_init_no_weapon_80054210 ?
void sna_init_anim_chokethrow_begin1_80054210(Actor_SnaInit *pActor)
{
    void *pFn;
    pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
    pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
    if (gSnaMoveDir_800ABBA4 >= 0)
    {
        pFn = sna_init_anim_throw_800589C8;
    }
    else
    {
        pFn = sna_init_anim_chokethrow_begin2_80058C80;
    }
    sna_init_start_anim_8004E1F4(pActor, pFn);
}

void sna_init_8005425C(Actor_SnaInit *pActor, int time)
{
    short new_y; // $v0

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, 134, 4);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK26);
    }

    if (pActor->field_9C_obj.field_1A)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_prone_idle_800528BC);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 0);
        new_y = pActor->field_20_ctrl.field_4C_turn_vec.vy + 2048;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = new_y;
        pActor->field_20_ctrl.field_8_rotator.vy = new_y;
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK26));
        sna_init_clear_invuln_8004F2EC(pActor);
    }
}

void sna_init_80054318(Actor_SnaInit *pActor, int time)
{
    if (time == 2 && gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_8005292C);
        return;
    }

    if ((pActor->field_9B0_pad_ptr->status & PAD_DOWN) != 0)
    {
        sna_init_set_flags2_8004E330(pActor, SNA_FLAG2_UNK1);
    }

    if (pActor->field_9C_obj.field_1A)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        return;
    }
}

void sna_init_fn_800543A8(Actor_SnaInit *pActor, int time)
{
    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) && time >= 16)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        if (sna_init_prone_check_standup_80050398(pActor))
        {
            sna_init_clear_invuln_8004F2EC(pActor);
            sna_init_clear_flags1_8004E308(
                pActor, (SNA_FLAG1_UNK2 | SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6 | SNA_FLAG1_UNK10));
            sna_init_clear_flags2_8004E344(pActor, SNA_FLAG2_UNK9);
        }
    }
}

void sna_init_anim_duct_move_80054424(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sub_8005688C;
        pActor->field_9CC_anim_update_fn_1p = sub_80052468;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_3, 4);
    }
    pActor->field_A60.vy = pActor->field_20_ctrl.field_78 + 150;
}

void sna_init_anim_duct_idle_80054488(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        pActor->field_9C8_anim_update_fn_3p = sub_80056928;
        pActor->field_9CC_anim_update_fn_1p = sub_80052468;
    }
    pActor->field_A60.vy = pActor->field_20_ctrl.field_78 + 250;
    sna_init_80050440(pActor);
}

void sna_init_anim_shot_flinch_800544E0(Actor_SnaInit *pActor, int time)
{
    int action_flag;

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_invuln_8004F2A0(pActor, 0);

        if (pActor->field_89C_pTarget->field_26_hp < 1)
        {
            GM_Sound_80032968(0, 0x3f, 0x1a);
            sna_init_8004F8E4(pActor, pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND ? 125 : 128);
        }

        if (pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_8;
        }
        else if ((GV_Time_800AB330 & 1) != 0)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_0;
            pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_1;
            pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        }

        sna_init_8004E22C(pActor, action_flag, 4);
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100 | PLAYER_STATUS_PREVENT_WEAPON_SWITCH);
        sna_init_start_anim_8004E1F4(pActor, dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
    }

    if (pActor->field_A26_fn_stance_idx == SNA_STANCE_GROUND)
    {
        sna_init_80050568(pActor);
    }
}

void sna_init_act_helper2_helper7_80054648(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 0);
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;

        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_4, 4);

        if (pActor->field_89C_pTarget->field_26_hp <= 0)
        {
            GM_Sound_80032968(0, 63, 0x1Au);
            sna_init_8004F8E4(pActor, 128);
        }
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK6);
    }
}

// knocked down by grenade etc
void sna_init_anim_knockdown_80054710(Actor_SnaInit *pActor, int time)
{
    int bVar1;

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_invuln_8004F2A0(pActor, 0);

        if ((GV_Time_800AB330 & 1) != 0)
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_2;
            pActor->field_A54.prone_bool_thing = 1;
        }
        else
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_3;
            pActor->field_A54.prone_bool_thing = 2;
        }

        sna_init_8004E22C(pActor, bVar1, 4);

        if (pActor->field_89C_pTarget->field_26_hp < 1 && GM_GameOverTimer_800AB3D4 == 0)
        {
            GM_Sound_80032968(0, 0x3f, 0x1a);
            GM_GameOverTimer_800AB3D4 = -1;
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK20);
        }

        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK8;
    }

    if (pActor->field_20_ctrl.field_32_height < 500)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
    }

    if (pActor->field_798 < 250)
    {
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
    }
    else
    {
        if (time < 12 && pActor->field_A54.prone_bool_thing == 1)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy += 170;
        }

        if (time > 16)
        {
            GV_NearExp8V_80026734(&pActor->field_A2C.vx, &DG_ZeroVector_800AB39C.vx, 3);
        }

        if ((pActor->field_A54.prone_bool_thing == 1 && time == 12) ||
            (pActor->field_A54.prone_bool_thing == 2 && time == 0x14))
        {
            GM_Sound_800329C4(&pActor->field_20_ctrl.field_0_position, 51, 1);
        }

        pActor->field_20_ctrl.field_44_movementVector.vx = pActor->field_A2C.vx;
        pActor->field_20_ctrl.field_44_movementVector.vz = pActor->field_A2C.vz;
        sna_init_80050568(pActor);
    }
}

void sna_init_anim_knockdown_idle_80054930(Actor_SnaInit *pActor, int time)
{
    int   local_field_A54; // $v1
    int   action_flag;     // $a1
    short v5;              // $a1

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_knockdown_check_getup_80056A1C;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK5);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK200 | PLAYER_STATUS_PRONE);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);
        local_field_A54 = pActor->field_A54.prone_bool_thing;
        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
        if (local_field_A54 == 1)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_4;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_5;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        if (pActor->field_89C_pTarget->field_26_hp <= 0)
        {
            v5 = 127;
            if (pActor->field_A54.prone_bool_thing == 1)
            {
                v5 = 126;
            }
            sna_init_8004F8E4(pActor, v5);
        }
        sna_init_80050568(pActor);
    }
}

void sna_init_anim_knockdown_getup_80054A10(Actor_SnaInit *pActor, int time)
{
    int action_flag; // $a1

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        if (pActor->field_A54.prone_bool_thing == 1)
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_6;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_C->field_7;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_A54.prone_bool_thing = 0;
    }

    if (pActor->field_20_ctrl.field_32_height >= 250)
    {
        pActor->field_20_ctrl.field_55_flags |= CONTROL_FLAG_UNK8;
    }

    if (pActor->field_20_ctrl.field_32_height >= 501)
    {
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
    }

    if (time == 2)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5));
        sna_init_set_invuln_8004F2A0(pActor, 24);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_SWITCH | PLAYER_STATUS_UNK200);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK1);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK8;
    }
}

void sna_init_anim_knockdown_shot_80054B50(Actor_SnaInit *pActor)
{
    pActor->field_9C8_anim_update_fn_3p = sna_init_knockdown_check_getup_80056A1C;
    pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;

    GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK100);

    if (pActor->field_89C_pTarget->field_26_hp <= 0 && !GM_GameOverTimer_800AB3D4)
    {
        GM_Sound_80032968(0, 63, 0x1Au);
        sna_init_8004F8E4(pActor, pActor->field_A54.prone_bool_thing == 1 ? 126 : 127);
    }
    else
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
    }

    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
}

// shot by tank while proned
void sna_init_anim_knockdown_shot_tank_80054C08(Actor_SnaInit *pActor, int time)
{
    char bVar1;

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_80052540;
        sna_init_set_invuln_8004F2A0(pActor, 0);

        if (pActor->field_A54.prone_bool_thing == 1)
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_A;
        }
        else
        {
            bVar1 = pActor->field_9B4_action_table->field_C->field_B;
        }

        sna_init_8004E22C(pActor, bVar1, 4);

        if (pActor->field_89C_pTarget->field_26_hp < 1 && GM_GameOverTimer_800AB3D4 == 0)
        {
            GM_Sound_80032968(0, 0x3f, 0x1a);
            GM_GameOverTimer_800AB3D4 = -1;
            sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK20);
        }
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_set_invuln_8004F2A0(pActor, 32);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_knockdown_idle_80054930);
    }
    else
    {
        if (time == 12)
        {
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
        }

        if (time > 16)
        {
            GV_NearExp8V_80026734(&pActor->field_A2C.vx, &DG_ZeroVector_800AB39C.vx, 3);
        }

        pActor->field_20_ctrl.field_44_movementVector.vx = pActor->field_A2C.vx;
        pActor->field_20_ctrl.field_44_movementVector.vz = pActor->field_A2C.vz;
        sna_init_80050568(pActor);
    }
}

void sna_init_knock_80054D68(Actor_SnaInit *pActor, int time)
{
    SVECTOR vec;

    int var_a1;
    int var_t0;
    int temp_v0;
    int noise;
    
    if (time == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_KNOCKING);

        if (dword_800ABBC4 == 4)
        {
            var_a1 = pActor->field_9B4_action_table->field_0->field_7;
        }
        else
        {
            var_a1 = pActor->field_9B4_action_table->field_0->field_6;
        }

        GM_ConfigObjectOverride_80034D30(&pActor->field_9C_obj, var_a1, 0, 4, 1022);

        if (((pActor->field_91C_weapon_idx >= 0) && (pActor->field_91C_weapon_idx < 2)) || (pActor->field_91C_weapon_idx == 3))
        {
            var_t0 = 0x578;

            if (pActor->field_A26_fn_stance_idx != 0)
            {
                var_t0 = 0x302;
            }
        }
        else
        {
            var_t0 = 0x325;

            if (pActor->field_A26_fn_stance_idx != 0)
            {
                var_t0 = 0x15E;
            }
        }

        vec.vz = -150;
        vec.vy = 0;
        vec.vx = (dword_800ABBC4 == 4) ? 300 : -300;

        if (sna_init_8004F628(pActor, &vec, -250, 12, 1, var_t0))
        {
            temp_v0 = sub_80028830();

            if (((temp_v0 >> 8) & 7) < 4)
            {
                noise = GM_GetNoiseSound_8002E614(temp_v0, 0);
                afterse_init_800604C0(noise, 6);
            }
        }
    }

    if ((pActor->field_9C_obj.field_1C != 0) || (pActor->field_9C_obj.field_10 == 0))
    {
        sna_init_8004E260(pActor, 0, 4, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_KNOCKING);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK9);
        pActor->field_9C0 = NULL;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_80054EFC.s") // 1080 bytes

void sna_init_anim_scope_80055334(Actor_SnaInit *param_1, int time)
{
    int action_flag;
    int sVar2;

    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        if (param_1->field_A26_fn_stance_idx == SNA_STANCE_STANDING)
        {
            action_flag = 0x87;
        }
        else
        {
            action_flag = sna_init_8004EAA8(param_1, param_1->field_A26_fn_stance_idx);
        }

        sna_init_8004E22C(param_1, action_flag, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
    }

    sVar2 = param_1->field_A2A;
    if (sVar2 < dword_800ABBDC)
    {
        sVar2 = dword_800ABBDC;
    }
    else if (dword_800ABBD4 < sVar2)
    {
        sVar2 = dword_800ABBD4;
    }

    param_1->field_20_ctrl.field_4C_turn_vec.vx = sVar2;
}

void sna_init_anim_jpegcam_800553CC(Actor_SnaInit *pActor, int time)
{
    sna_init_anim_scope_80055334(pActor, time);
}

void sna_init_anim_box_idle_800553EC(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_80056A54;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE | PLAYER_STATUS_CROUCHING);
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_2, 4);
    }
}

void sna_init_anim_box_move_8005544C(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_80056AD8;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_3, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        GM_ConfigControlInterp_80026244(&pActor->field_20_ctrl, 4);
    }
}

void sna_init_anim_box_stop_800554B4(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_800525F8;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_4, 4);
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
    }
}

void sna_init_anim_dying_80055524(Actor_SnaInit *pActor, int time)
{
    UnkSnakeStruct2 *unk2 = &pActor->field_9E4;

    if (time == 0)
    {
        int f9e6;

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        sub_8004F338(pActor);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_UNK20000000);

        if ((unk2->field_9EC_flags3 & 0x400) == 0) // TODO: make flags enum for flags3
        {
            if ((unk2->field_9EC_flags3 & 0x4000) != 0)
            {
                pActor->field_20_ctrl.field_38 = -2;
                pActor->field_20_ctrl.field_36 = -2;
                pActor->field_A28 = -2;
            }
            else
            {
                pActor->field_20_ctrl.field_38 = -1;
                pActor->field_20_ctrl.field_36 = -1;
                pActor->field_A28 = -1;
            }
        }

        sna_init_set_invuln_8004F2A0(pActor, 0);
        pActor->field_9C_obj.action_flag = -1;
        sna_init_8004E22C(pActor, unk2->field_9E4, 4);

        f9e6 = unk2->field_9E6;
        if (f9e6 >= 0)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = f9e6;
            pActor->field_20_ctrl.field_8_rotator.vy = f9e6;
        }

        pActor->field_A38 = -1;
        pActor->field_A3A = -1;

        if ((unk2->field_9EC_flags3 & 0x1000) == 0)
        {
            if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000) == 0)
            {
                if ((pActor->field_9AC & 2) != 0)
                {
                    if ((GM_GameOverTimer_800AB3D4 == 0 && unk2->field_9F2 == 0) ||
                        sna_init_check_flags1_8004E31C(pActor, SNA_FLAG1_UNK29) != 0)
                    {
                        pActor->field_A38 = pActor->field_9A8_current_item;
                        sub_8004F204(pActor);
                    }
                    else
                    {
                        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK4000000);
                    }
                }
            }
            else
            {
                pActor->field_A38 = pActor->field_9A8_current_item;
                sub_8004F204(pActor);
            }

            if ((pActor->field_920_tbl_8009D580 & 0x200) != 0)
            {
                if (GM_GameOverTimer_800AB3D4 != 0 || unk2->field_9F2 != 0)
                {
                    GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK4000000);
                }
                else
                {
                    pActor->field_A3A = pActor->field_91C_weapon_idx;
                    sub_8004F14C(pActor);
                }
            }
            else if (pActor->field_91C_weapon_idx != -1 && GM_CurrentWeaponId == WEAPON_NONE)
            {
                sub_8004F14C(pActor);
            }
        }

        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING);
    }

    if ((unk2->field_9EC_flags3 & 0x200) != 0 && pActor->field_20_ctrl.field_32_height < 500)
    {
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
    }
    else
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE);
        pActor->field_20_ctrl.field_4C_turn_vec.vx = 0;
    }

    if ((unk2->field_9EC_flags3 & 2) == 0)
    {
        pActor->field_A2C = DG_ZeroVector_800AB39C;
    }

    if ((unk2->field_9EC_flags3 & 0x4000) == 0)
    {
        if ((unk2->field_9EC_flags3 & 2) == 0)
        {
            int   f78;
            int   new_height;
            short y_pos;

            new_height = pActor->field_9C_obj.field_18 - (-unk2->field_9EE + pActor->field_20_ctrl.field_78);
            f78 = pActor->field_20_ctrl.field_78;
            pActor->field_20_ctrl.field_32_height = new_height;
            y_pos = new_height + f78;

            pActor->field_20_ctrl.field_0_position.vy = y_pos;
            pActor->field_9C_obj.objs->world.t[1] = y_pos;

            DG_GetLightMatrix2_8001A5D8(&pActor->field_20_ctrl.field_0_position, &pActor->field_848_lighting_mtx);
        }
    }
    else
    {
        int unk[2];
        sub_8004E588(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_20_ctrl.field_0_position, unk);
        pActor->field_20_ctrl.field_78 = unk[0];
        pActor->field_20_ctrl.field_7A = unk[1];
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK22);

        if ((unk2->field_9EC_flags3 & 0x20) == 0)
        {
            pActor->field_20_ctrl.field_55_flags &= ~2;
        }

        if ((unk2->field_9EC_flags3 & 0x100) != 0)
        {
            pActor->field_180.interp = 15;
            pActor->field_180.field_04.field_14 = 0;
            pActor->field_9B8_fn_anim = sna_init_fn_nothing_80053B80;
            pActor->field_9BC_anim_frame = 0;
            pActor->field_A3A = 0;
            pActor->field_A38 = 0;
        }
        else
        {
            int stance;
            int fa38;
            int fa3a;

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH |
                                              PLAYER_STATUS_UNK20000000);
            sna_init_clear_invuln_8004F2EC(pActor);

            stance = unk2->field_9EA;
            fa38 = pActor->field_A38;
            fa3a = pActor->field_A3A;

            if (stance < SNA_STANCE_STANDING)
            {
                if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
                {
                    stance = pActor->field_A26_fn_stance_idx;
                }
                else
                {
                    stance = SNA_STANCE_UNK;
                }
            }

            if ((unk2->field_9EC_flags3 & 0x1000) != 0)
            {
                sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_idle_800553EC);
                pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
            }
            else
            {
                if (stance < SNA_STANCE_UNK)
                {
                    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
                    {
                        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_FIRST_PERSON_DUCT);
                        sub_8004ED08(pActor);
                    }

                    pActor->field_A26_fn_stance_idx = stance;
                    sna_init_start_anim_8004E1F4(pActor, dword_8009EEA4[stance]);
                }
                else
                {
                    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT))
                    {
                        pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
                        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_FIRST_PERSON_DUCT | PLAYER_STATUS_PRONE);
                        sna_init_8004EC8C(pActor);
                    }

                    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_move_80054424);
                }

                if ((unk2->field_9EC_flags3 & 8) == 0)
                {
                    if (fa38 >= 0)
                    {
                        GM_CurrentItemId = fa38;

                        if ((unsigned int)(fa38 - 2) < 3)
                        {
                            pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
                        }
                    }
                    if (fa3a >= 0)
                    {
                        GM_CurrentWeaponId = fa3a;
                        GM_WeaponChanged_800AB9D8 = 1;

                        if (fa3a == WEAPON_PSG1)
                        {
                            pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
                        }
                    }
                }
            }
        }
    }
}

// things like "a surveillance camera??" where player control is halted    
void sna_init_anim_mini_cutscene_800559D8(Actor_SnaInit *pActor, int time)
{
    SVECTOR vec;

    UnkSnakeStruct2 *pStr = &pActor->field_9E4;
    int weapon;
    int item;
    int stance;
    unsigned char action;
    
    short temp_v0;
    short temp_v1_2;
    short temp_v0_2;

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = &sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = &sna_init_fn_nothing_80053B80;

        sub_8004F338(pActor);

        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);
        sna_init_set_invuln_8004F2A0(pActor, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PRONE | PLAYER_STATUS_CROUCHING);

        pActor->field_A00.field_0_ivec.vz = -1;
        pActor->field_A00.field_0_ivec.vx = dword_800AB9F0;
        pActor->field_A00.field_0_ivec.pad = dword_800AB9F0;

        sna_act_unk_helper2_helper2_800605DC(&pActor->field_A00, pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_9E4.field_9F4);
        temp_v0 = sub_8005C6C4(pActor->field_20_ctrl.field_2C_map->field_8_hzd, &pActor->field_9E4.field_9F4,  pActor->field_A00.field_0_ivec.vy);

        temp_v1_2 = (temp_v0 >> 8) & 0xff;
        temp_v0_2 = temp_v0 & 0xff;

        if ((temp_v1_2 == 0xff) || (temp_v0_2 == 0xff) || (temp_v1_2 != temp_v0_2))
        {
            pStr->field_9EC_flags3 |= 0x200;
        }

        if (pStr->field_9EC_flags3 & 0x200)
        {
            GV_SubVec3_80016D40(&pStr->field_9F4, &pActor->field_20_ctrl.field_0_position, &vec);
            pActor->field_20_ctrl.field_4C_turn_vec.vy = GV_VecDir2_80016EF8(&vec);
            pActor->field_20_ctrl.field_38 = -1;
            pActor->field_20_ctrl.field_36 = -1;
            pActor->field_A28 = -1;
        }

        pActor->field_A38 = -1;

        if (!(pStr->field_9EC_flags3 & 0x100) && ((GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK1000)) || (pActor->field_9AC & 2)))
        {
            pActor->field_A38 = pActor->field_9A8_current_item;
            sub_8004F204(pActor);
        }

        pActor->field_A3A = -1;

        if (pActor->field_920_tbl_8009D580 & 0x200)
        {
            pActor->field_A3A = pActor->field_91C_weapon_idx;
            sub_8004F14C(pActor);
        }
        
        if (pStr->field_9EC_flags3 & 0x100)
        {
            stance = SNA_STANCE_STANDING;
            action = pActor->field_9B4_action_table->field_18->field_3;
        }
        else if (pStr->field_9EC_flags3 & 1)
        {
            stance = SNA_STANCE_GROUND;
            action = pActor->field_9B4_action_table->field_4->field_3;
            GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_PRONE);
        }
        else
        {
            stance = SNA_STANCE_STANDING;
            action = pActor->field_9B4_action_table->field_4->field_0;
        }
        
        pActor->field_A26_fn_stance_idx = stance;
        
        sna_init_8004E22C(pActor, action, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
    }

    if (!(pStr->field_9EC_flags3 & 0x200))
    {
        pActor->field_A00.field_0_ivec.vx = dword_800AB9F0;
        sna_unk_helper2_helper_8006070C(&pActor->field_A00.field_0_ivec, &pActor->field_20_ctrl.field_0_position);
    }

    GV_NearExp4PV_800269A0(&pActor->field_20_ctrl.field_8_rotator.vx, &pActor->field_20_ctrl.field_4C_turn_vec.vx, 3);
    GV_NearExp4PV_800269A0(&pActor->field_20_ctrl.field_8_rotator.vx, &pActor->field_20_ctrl.field_4C_turn_vec.vx, 3);

    if (sna_act_unk_helper2_helper3_80060684(&pActor->field_A00.field_0_ivec, &pActor->field_20_ctrl.field_0_position) < pStr->field_9F4.pad)
    {
        sna_init_clear_invuln_8004F2EC(pActor);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK22);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH);

        if (pStr->field_9EC_flags3 & 0x200)
        {
            pActor->field_20_ctrl.field_38 = 450;
            pActor->field_20_ctrl.field_36 = 450;
            pActor->field_A28 = 450;
        }

        if (!(pStr->field_9EC_flags3 & 2))
        {
            item = pActor->field_A38;
            weapon = pActor->field_A3A;

            if (item >= 0)
            {
                GM_CurrentItemId = item;

                if ((item == ITEM_C_BOX_A) || (item == ITEM_C_BOX_B) || (item == ITEM_C_BOX_C))
                {
                    pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
                }
            }

            if (weapon >= 0)
            {
                GM_CurrentWeaponId = weapon;
                GM_WeaponChanged_800AB9D8 = 1;
    
                if (weapon == WEAPON_PSG1)
                {
                    pActor->field_A26_fn_stance_idx = SNA_STANCE_GROUND;
                }
                else if (weapon == WEAPON_STINGER)
                {
                    pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
                }
            }
        }

        if (!(pStr->field_9EC_flags3 & 8))
        {
            pActor->field_20_ctrl.field_55_flags &= ~CONTROL_FLAG_UNK2;
        }

        if (pStr->field_9EC_flags3 & 1)
        {
            sna_init_80050440(pActor);
            sna_init_clear_flags1_8004E308(pActor, 4);
        }

        if (pStr->field_9EC_flags3 & 0x100)
        {
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_box_stop_800554B4);
        }
        else
        {
            sna_init_start_anim_8004E1F4(pActor, dword_8009EEA4[pActor->field_A26_fn_stance_idx]);
        }

        if (pStr->field_9E8 >= 0)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = pStr->field_9E8;
        }
    }
}

// similar to above, seems freeze snake and make him look at a certain direction or track something
// triggers on first elevator ride at dock and right before mantis fight to look at meryl
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper3_80055DD8.s") // 2168 bytes

void sna_init_act_helper3_helper_80056650(Actor_SnaInit *pActor, int time)
{
    int            result;
    int            footstepsFrame; // guessed

    if (time == 0)
    {
        int *status = &GM_GameStatus_800AB3CC;

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        *status |= 0x10000000;

        sub_8004F338(pActor);
        pActor->field_20_ctrl.field_55_flags &= ~2;
        sna_init_set_invuln_8004F2A0(pActor, 0);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_CROUCHING | PLAYER_STATUS_PRONE);
        sub_8004F14C(pActor);
        sub_8004F204(pActor);
        pActor->field_A26_fn_stance_idx = 0;
        sna_init_8004E22C(pActor, 3, 1);
    }

    if (!pActor->field_908_weapon_actor)
    {
        Actor_Grenade *timerBomb;
        timerBomb = NewTimerBomb_80066ACC(&pActor->field_20_ctrl, &pActor->field_9C_obj, 4,
                                           &pActor->field_914, 1);
        pActor->field_908_weapon_actor = &timerBomb->field_0_actor;
        pActor->field_924 = 0;
        sna_init_8004E22C(pActor, 0x3c, 4);

        if (!pActor->field_908_weapon_actor)
        {
            return;
        }
    }

    result = 1;
    footstepsFrame = pActor->field_180.field_04.field_2_footstepsFrame;
    switch (pActor->field_924)
    {
    case 0:
        if (pActor->field_9C_obj.field_1A != 0)
        {
            sna_init_8004E22C(pActor, 3, 1);
            pActor->field_924 = 1;
        }
        break;
    case 1:
        sna_init_8004E22C(pActor, 0x32, 1);
        pActor->field_924 = 2;
        break;
    case 2:
        if (footstepsFrame == 6)
        {
            result = 3;
            pActor->field_924 = 3;
        }
        break;
    case 3:
        result = 0;

        if (pActor->field_9C_obj.field_1A != 0)
        {
            sna_init_clear_invuln_8004F2EC(pActor);
            GM_GameStatus_800AB3CC &= ~0x10000000;
            GV_DestroyActorQuick_80015164(pActor->field_908_weapon_actor);
            pActor->field_908_weapon_actor = NULL;
            pActor->field_924 = 0;
            pActor->field_9E4.field_9F0 = 0;
            sna_init_set_flags1_8004E2F4(pActor, 0x200000);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
        break;
    }

    pActor->field_914 = result;
}

void sub_8005684C(Actor_SnaInit *pActor)
{
    int y;

    if ((pActor->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_RIGHT)) == 0)
    {
        return;
    }

    y = pActor->field_20_ctrl.field_4C_turn_vec.vy;
    if ((pActor->field_9B0_pad_ptr->status & PAD_LEFT) != 0)
    {
        y += 32;
    }
    else
    {
        y -= 32;
    }
    pActor->field_20_ctrl.field_4C_turn_vec.vy = y;
}

void sub_8005688C(Actor_SnaInit *pActor)
{
    int action_flag; // $a1

    if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
    {
        if ((pActor->field_9B0_pad_ptr->status & PAD_UP) != 0)
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_3;
        }
        else
        {
            action_flag = pActor->field_9B4_action_table->field_4->field_4;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_duct_idle_80054488);
    }
    else
    {
        sub_8005684C(pActor);
    }
}

void sub_80056928(Actor_SnaInit *param_1)
{
    char bVar1;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_FIRST_PERSON_DUCT) == 0)
    {
        sna_init_start_anim_8004E1F4(param_1, sna_init_anim_enter_duct_80053E9C);
        sna_init_set_invuln_8004F2A0(param_1, 0);
    }
    else
    {
        if ((param_1->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) == 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(param_1, sna_init_anim_duct_move_80054424);
            sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_0->field_3, 4);
        }
        else
        {
            if ((param_1->field_9B0_pad_ptr->status & PAD_UP) != 0)
            {
                bVar1 = param_1->field_9B4_action_table->field_4->field_3;
            }
            else
            {
                bVar1 = param_1->field_9B4_action_table->field_4->field_4;
            }

            sna_init_8004E22C(param_1, bVar1, 4);
            sub_8005684C(param_1);
        }
    }
}

void sna_init_knockdown_check_getup_80056A1C(Actor_SnaInit *pActor)
{
    if (pActor->field_9B0_pad_ptr->press)
    {
        sna_init_knockdown_getup_80050668(pActor);
    }
}

void sna_init_80056A54(Actor_SnaInit *pActor)
{
    if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
    {
        if (gSnaMoveDir_800ABBA4 >= 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_move_8005544C);
        }
    }
    else
    {
        if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) != 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_move_8005544C);
        }

        sub_8004FA9C(pActor);
    }
}

void sna_init_fn_80056AD8(Actor_SnaInit *pActor)
{
    if (gSnaMoveDir_800ABBA4 < 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_stop_800554B4);
    }
    else
    {
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_3, 4);
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);

        if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5) == 0)
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = (short)gSnaMoveDir_800ABBA4;
        }
        else if ((pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)) == 0)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_box_stop_800554B4);
        }
        else
        {
            sub_8004FA9C(pActor);
        }
    }
}

void sna_init_anim_shoot_weapon_80056B88(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_shoot_weapon_helper_80057590;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_0->field_1, 4);
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
    }
}

void sna_init_anim_rungun_begin_80056BDC(Actor_SnaInit *param_1, int time)
{
    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_rungun_begin_helper_800577B4;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_1, 4);
    }
}

void sna_init_anim_rungun_80056C3C(Actor_SnaInit *param_1, int time)
{
    if (time == 0)
    {
        param_1->field_9C8_anim_update_fn_3p = sna_init_anim_rungun_helper_80057844;
        param_1->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(param_1, param_1->field_9B4_action_table->field_4->field_0, 4);
    }
}

// https://decomp.me/scratch/XqwyZ
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_nikita_80056C9C.s") // 320 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_80056DDC.s")   // 740 bytes

void sna_init_anim_stinger_800570C0(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_stinger_helper_80058378;
        pActor->field_9CC_anim_update_fn_1p = sna_init_anim_stinger_helper_80058378;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_0, 4);
        pActor->field_A26_fn_stance_idx = SNA_STANCE_STANDING;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH | PLAYER_STATUS_PRONE |
                                          PLAYER_STATUS_CROUCHING);
    }
}

void sna_init_80057118(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        if (used_counter_8009F42C >= 16)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
            GM_Sound_80032968(0, 0x3f, 0x23);
            return;
        }

        pActor->field_9C8_anim_update_fn_3p = sub_80058644;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_5, 4);
    }

    sub_8004E9D0(pActor);
}

void sna_init_800571B8(Actor_SnaInit *pActor, int time)
{
    SVECTOR   *vec1;
    GM_Target *pGVar3;
    SVECTOR   *vec2;

    vec2 = &pActor->field_8EC_vec;

    if (time == 0)
    {
        if (used_counter_8009F42C >= 16)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
            pActor->field_8E8_pTarget->field_6_flags &= ~(0x40);
            pActor->field_8E8_pTarget = NULL;
            return;
        }

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_6, 4);
        pGVar3 = pActor->field_8E8_pTarget;
        DG_PutVector_8001BE48(&dword_800AB7EC, vec2, 1);
        GV_SubVec3_80016D40(&pGVar3->field_8_vec, vec2, vec2);

        vec2->vx /= 4;
        vec2->vy /= 4;
        vec2->vz /= 4;
    }

    vec1 = &pActor->field_20_ctrl.field_44_movementVector;

    if (time < 4)
    {
        GV_AddVec3_80016D00(vec1, vec2, vec1);
    }

    if (time == 6)
    {
        GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 49);
        NewBakudan_8006A6CC(pActor->field_8E8_pTarget->field_20, &dword_800AB7F4, 1, 1, pActor->field_8E8_pTarget);
        pActor->field_914 = 5;
        pActor->field_8E8_pTarget->field_6_flags &= ~(0x40);
        pActor->field_8E8_pTarget = 0;
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
    }
}

void sna_init_80057378(Actor_SnaInit *pActor, int time)
{
    int action;
    int stance;

    stance = pActor->field_A26_fn_stance_idx;
    pActor->field_20_ctrl.field_4C_turn_vec.vy = dword_800ABBA8;

    if (time == 0)
    {
        if (stance == 0)
        {
            action = pActor->field_9B4_action_table->field_10->field_6;
        }
        else
        {
            action = pActor->field_9B4_action_table->field_10->field_7;
        }

        sna_init_8004E260(pActor, action, 4, 0xffff);
    }

    if ((stance == SNA_STANCE_STANDING && time == 6) || (stance == SNA_STANCE_CROUCH && time == 14))
    {
        pActor->field_914 = 3;
        GM_BombSeg_800ABBD8 = (GM_Target *)dword_800ABBB0;
    }

    if (pActor->field_9C_obj.field_1C != 0 || pActor->field_9C_obj.field_10 == 0)
    {
        sna_init_8004E260(pActor, 0, 4, 0);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK9);
        pActor->field_9C0 = NULL;
    }
}

void sna_init_anim_claymore_80057474(Actor_SnaInit *pActor, int time)
{
    int              i;
    int              down_count;
    GM_Target       *targets;

    if (time == 0)
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        GM_Target_8002E374(&down_count, &targets);

        if (counter_8009F448 == 8 || down_count == 64)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
            GM_Sound_80032968(0, 63, 35);
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            return;
        }

        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_claymore_helper_80058780;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_0, 4);

        for (i = 0; i < (int)(sizeof(pActor->field_718) / sizeof(SVECTOR)); i++) // 16
        {
            pActor->field_718[i] = DG_ZeroVector_800AB39C;
        }

        GM_ConfigMotionAdjust_80035008(&pActor->field_9C_obj, pActor->field_718);
        sna_init_set_flags1_8004E2F4(pActor, SNA_FLAG1_UNK26);
    }

    sub_8004E9D0(pActor);
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shoot_weapon_helper_80057590.s") // 548 bytes

void sna_init_anim_rungun_begin_helper_800577B4(Actor_SnaInit *pActor, int time)
{
    if (time == 2 && gSnaMoveDir_800ABBA4 >= 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_rungun_80056C3C);
    }
    else
    {
        if ((pActor->field_9B0_pad_ptr->status & PAD_DOWN) != 0)
        {
            sna_init_set_flags2_8004E330(pActor, SNA_FLAG2_UNK1);
        }

        if (pActor->field_9C_obj.field_1A)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_shoot_weapon_80056B88);
        }
    }
}

void sna_init_anim_rungun_helper_80057844(Actor_SnaInit *pActor)
{
    int angle;

    if (!GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_PREVENT_FIRST_PERSON))
    {
        sna_init_8004E260(pActor, 0, 4, 0);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_run_8005292C);
        return;
    }
    
    if (gSnaMoveDir_800ABBA4 < 0 || (!(pActor->field_920_tbl_8009D580 & 8) && !(pActor->field_9B0_pad_ptr->status & 0x40)))
    {
        if (++pActor->field_A3A >= 5)
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_shoot_weapon_80056B88);
            return;
        }
    }
    else
    {
        pActor->field_A3A = 0;
    }
    
    if (!sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5))
    {
        if (gSnaMoveDir_800ABBA4 < 0)
        {
            angle = pActor->field_20_ctrl.field_4C_turn_vec.vy;
        }
        else
        {
            angle = sub_8004E4C0(pActor, gSnaMoveDir_800ABBA4);
        }

        pActor->field_20_ctrl.field_4C_turn_vec.vy = angle;
        sub_8004EA50(pActor, angle);
    }
    else if (!(pActor->field_9B0_pad_ptr->status & (PAD_DOWN | PAD_UP)))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_shoot_weapon_80056B88);
    }
    else
    {
        sub_8004FA9C(pActor);
    }
}

void sna_init_auto_aim_800579A0(Actor_SnaInit *pActor)
{
    int unk;
    int out_x_copy;
    int snake_not_moving;
    int out_x;
    int out_y;
    int diff;

    // loops enemies and finds candidate to aim at, returns angle to auto turn/aim to
    // melee also uses this in a different func
    HomingTarget_2_80032EAC(&pActor->field_9C_obj.objs->objs[6].world,
                            pActor->field_20_ctrl.field_8_rotator.vy, // input snake horizontal facing angle
                            &out_y, &out_x, pActor->field_20_ctrl.field_2C_map->field_0_map_index_bit,
                            pActor->field_890_autoaim_max_dist,
                            pActor->field_892_autoaim_min_angle); // min angle to activate auto aim

    // ?
    unk = pActor->field_718[2].vx;
    diff = unk - out_x;
    if (diff >= 65)
    {
        out_x = unk - 64;
    }
    else if (diff < -64)
    {
        out_x = unk + 64;
    }

    // ?
    out_x_copy = out_x;
    pActor->field_718[2].vx = out_x;
    pActor->field_718[6].vx = out_x;
    snake_not_moving = gSnaMoveDir_800ABBA4 < 0;
    pActor->field_718[7].vx = 3 * out_x_copy / 2; // maybe aim gun/head up/down??

    if (snake_not_moving && out_y >= 0) // if not moving, set snake turn angle
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy = out_y;
    }

    if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5))
    {
        gUnkCameraStruct_800B77B8.field_28.vx = out_x;
    }
}

extern short d_800AB9EC_mag_size;
extern short d_800ABA2C_ammo;
#include "Game/linkvarbuf.h"
void sna_init_80057A90(Actor_SnaInit *pActor, int time)
{
    int bits;
    int ammo, magSize;

    if (GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING))
    {
        bits = 0x3fe;
    }
    else
    {
        bits = 0xffff;
    }
    
    if (time == 0)
    {
        GM_ConfigMotionAdjust_80035008(&pActor->field_9C_obj, NULL);
        anime_create_8005DDE0(&pActor->field_9C_obj.objs->objs[4].world);
        sna_init_8004E260(pActor, pActor->field_9B4_action_table->field_10->field_1, 4, bits);

        ammo = d_800ABA2C_ammo;
        magSize = GM_Weapons[pActor->field_91C_weapon_idx];
        
        if (ammo > 0 && ammo < magSize)
        {
            magSize = ammo;
        }

        d_800ABA2C_ammo = ammo;
        d_800AB9EC_mag_size = magSize;
    }

    sna_init_8004F034(pActor, bits);

    if (time == 16)
    {
        GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 47);
    }

    if (pActor->field_9C_obj.field_1C != 0)
    {
        if (!(pActor->field_9B0_pad_ptr->status & PAD_SQUARE))
        {
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_FIRST_PERSON);
            sna_init_8004E260(pActor, 0, 4, 0);
            sna_init_start_anim_8004E1F4(pActor, &sna_init_anim_idle_8005275C);
            pActor->field_90C_pWeaponFn = sna_init_gun_800540D0;
        }
        else
        {
            pActor->field_90C_pWeaponFn = sub_80057BF0;
        }

        pActor->field_910 = 0;
        pActor->field_926 = 0;
        pActor->field_924 = 0;
    }
}

#pragma INCLUDE_ASM("asm/sub_80057BF0.s")                                   // 996 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_psg1_helper_80057FD4.s") // 932 bytes

void sna_init_anim_stinger_helper_80058378(Actor_SnaInit *pActor)
{
    int    iVar2;
    short *vec;

    iVar2 = 1;
    if (((pActor->field_9B0_pad_ptr->release & PAD_SQUARE) != 0 && (GM_GameStatus_800AB3CC & 0x10000000) == 0) &&
        GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_UNK20000000) == 0)
    {
        if (pActor->field_918_pWeaponState[0] >= 1)
        {
            iVar2 = 3;
        }
        else
        {
            GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_position, 4);
            pActor->field_9A0 = 4;
        }
    }

    pActor->field_914 = iVar2;

    if ((pActor->field_9B0_pad_ptr->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) != 0)
    {
        vec = pActor->field_9D0;
        vec[0] = 1;
        vec[3] = 0x200;
        vec[4] = 0x200;
        vec[5] = 0x20;
        vec[6] = 0x20;
        vec[7] = 0x20;
        vec[8] = 0x20;

        sna_init_80051DA0(pActor);
        sna_init_80051FD0(pActor);
        sna_init_8004EB14(pActor);
    }
}

void sna_init_anim_grenade_80058470(Actor_SnaInit *pActor, int time)
{
    int bits;
    int uVar2;
    int res;
    
    if ( GM_CheckPlayerStatusFlag_8004E29C(PLAYER_STATUS_MOVING) )
    {
        bits = 0x3fe;
    }
    else
    {
        bits = 0xffff;
    }
    
    if (time == 0)
    {
        sna_init_8004E260(pActor, pActor->field_9B4_action_table->field_10->field_0, 4, bits);
        pActor->field_924 = 0;
        GM_SeSet_80032858(&(pActor->field_20_ctrl).field_0_position, 44);
    }

    sna_init_8004F034(pActor, bits);
    res = 1;

    uVar2 = pActor->field_180.field_1C.field_2_footstepsFrame;
    
    switch (pActor->field_924)
    {
    case 0:
        if (pActor->field_9C_obj.field_1C != 0)
        {
            sna_init_8004E260(pActor, pActor->field_9B4_action_table->field_0->field_0, 1, bits);
            pActor->field_924 = 1;
        }

        break;
    case 1:        
        if (!(pActor->field_9B0_pad_ptr->status & PAD_SQUARE) && (DG_UnDrawFrameCount_800AB380 == 0))
        {
            sna_init_8004E260(pActor, pActor->field_9B4_action_table->field_10->field_4, 1, bits);
            pActor->field_924 = 2;
        }

        break;
    case 2:
        if (uVar2 == 7)
        {
            res = 3;
            pActor->field_924 = 3;
        }

        break;
    case 3:
        res = 0;
        
        if ((uVar2 > 11) && (pActor->field_9B0_pad_ptr->status & PAD_SQUARE))
        {
            pActor->field_910 = 0;
            return;
        }
        

        if (pActor->field_9C_obj.field_1C != 0)
        {
            sna_init_8004E260(pActor, 0, 4, 0);
            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_PREVENT_FIRST_PERSON | PLAYER_STATUS_PREVENT_ITEM_SWITCH | PLAYER_STATUS_PREVENT_WEAPON_SWITCH);
        }

        break;
    }

    pActor->field_914 = res;
}

void sub_80058644(Actor_SnaInit *pActor, int time)
{
    int iVar1;

    pActor->field_914 = 1;

    if (time >= 10)
    {
        iVar1 = (int)pActor->field_A38;
        if (iVar1 == 0)
        {
            sub_8004EEB0(pActor);
        }

        if ((pActor->field_9B0_pad_ptr->status & PAD_SQUARE) == 0 && iVar1 == 0 && DG_UnDrawFrameCount_800AB380 == 0)
        {
            iVar1 = sub_8004E5E8(pActor, 0x80);
            if (iVar1 == 1)
            {
                sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_8, 1);
                pActor->field_A38 = 1;
                pActor->field_914 |= 2;
            }
            else if (iVar1 == 2)
            {
                GM_Sound_80032968(0, 0x3f, 0x23);
            }
        }

        if ((iVar1 == 1 && pActor->field_9C_obj.field_1A != 0) || iVar1 == 2)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }

        pActor->field_A2C.vy = -100;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_claymore_helper_80058780.s") // 584 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_throw_800589C8.s")           // 584 bytes

void sna_init_anim_punch_80058C10(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_punch_helper_800591F4;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_10->field_2, 1);
        pActor->field_A38 = 0;
        sna_init_set_flags1_8004E2F4(pActor, (SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
    }
}

void sna_init_anim_chokethrow_begin2_80058C80(Actor_SnaInit *pActor, int time)
{
    int        bClear;            // $s0
    GM_Target *field_8E8_pTarget; // $v1
    int        action_flag;       // $a1
    SVECTOR   *p;

    if (time == 0)
    {
        pActor->field_904_frames_last_choke = 0;
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        bClear = 0;
        pActor->field_A54.choke_count = 0;

        if (!sna_init_8004FDE8(pActor, &stru_8009F044))
        {
            bClear = 1;
            pActor->field_A38 = 1;
        }

        p = &pActor->field_8EC_vec;
        if (!bClear)
        {

            field_8E8_pTarget = pActor->field_8E8_pTarget;

            field_8E8_pTarget->field_2A--;

            DG_SetPos2_8001BC8C(&field_8E8_pTarget->field_8_vec, &pActor->field_20_ctrl.field_8_rotator);

            DG_PutVector_8001BE48(&stru_800AB7FC, p, 1);
            DG_SetPos2_8001BC8C(&pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_8_rotator);
            GV_SubVec3_80016D40(p, &pActor->field_20_ctrl.field_0_position, p);
            p->vx /= 4;
            p->vy /= 4;
            p->vz /= 4;
            action_flag = pActor->field_9B4_action_table->field_18->field_0;
        }
        else
        {
            pActor->field_8EC_vec = DG_ZeroVector_800AB39C;
            action_flag = pActor->field_9B4_action_table->field_0->field_1;
        }
        sna_init_8004E22C(pActor, action_flag, 4);
    }

    if (time < 4)
    {
        ++pActor->field_904_frames_last_choke;
        GV_AddVec3_80016D00(&pActor->field_20_ctrl.field_44_movementVector, &pActor->field_8EC_vec,
                            &pActor->field_20_ctrl.field_44_movementVector);
    }
    else
    {
        if (pActor->field_A38)
        {
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        }
        else
        {
            pActor->field_89C_pTarget->field_10_size.vx = 150;
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
        }
    }
}

void sna_init_anim_choke_80058E88(Actor_SnaInit *pActor, int time)
{
    short action_flag; // $s0

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_choke_helper_8005951C;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        action_flag = pActor->field_9B4_action_table->field_18->field_0;
        sna_init_8004E22C(pActor, action_flag, 4);
        pActor->field_8E8_pTarget->field_3E = action_flag;
    }
}

void sna_init_anim_choke_rechoke_80058EF4(Actor_SnaInit *pActor, int time)
{
    short bVar1;

    if (time == 0 || (pActor->field_9B0_pad_ptr->press & PAD_SQUARE) != 0)
    {
        pActor->field_9C_obj.action_flag = -1;
        pActor->field_9C8_anim_update_fn_3p = sna_init_anim_choke_rechoke_helper_8005961C;
        pActor->field_904_frames_last_choke = 0;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        bVar1 = pActor->field_9B4_action_table->field_10->field_6;
        sna_init_8004E22C(pActor, bVar1, 4);
        pActor->field_8E8_pTarget->field_3E = bVar1;
    }
}

/*
void sna_init_anim_choke_rechoke_80058EF4(Actor_SnaInit *pActor, int time)
{
    Sna_ActionTable *field_9B4_action_table; // $v1
    short action_flag; // $s0

    if (time == 0)
    {
        if (!(pActor->field_9B0_pad_bits[1] & 0x80))
        {
        field_9B4_action_table = pActor->field_9B4_action_table;

        pActor->field_9C_obj.action_flag = -1;
        pActor->field_9C8_anim_update_fn_3p = sub_8005961C;
        pActor->field_904_frames_last_choke = 0;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        action_flag = field_9B4_action_table->field_10->field_6;
        sna_init_8004E22C(pActor, field_9B4_action_table->field_10->field_6, 4);
        pActor->field_8E8_pTarget->field_3E = action_flag;
        }
    }
}
*/

void sna_init_anim_choke_kill_80058F88(Actor_SnaInit *pActor, int time)
{
    GM_Target *field_8E8_pTarget; // $s0
    int        action_flag;       // $s1

    if (time == 0)
    {
        field_8E8_pTarget = pActor->field_8E8_pTarget;
        action_flag = pActor->field_9B4_action_table->field_10->field_7;

        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;

        sna_init_8004E22C(pActor, action_flag, 4);

        field_8E8_pTarget->field_3E = action_flag;
        field_8E8_pTarget->field_28 = 5;
        field_8E8_pTarget->field_2A--;
        pActor->field_A54.choke_count = 0;
    }

    if (pActor->field_9C_obj.field_1A)
    {
        sna_init_sub_8004E41C(pActor, 2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
    }

    if (sna_init_sub_8004E358(pActor, SNA_FLAG2_UNK5))
    {
        sub_8004FAE8(pActor);
    }
}

void sna_init_anim_choke_drag_80059054(Actor_SnaInit *pActor, int time)
{
    int bVar2;
    int iVar3;

    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        bVar2 = pActor->field_9B4_action_table->field_18->field_1;
        GM_SetPlayerStatusFlag_8004E2B4(PLAYER_STATUS_MOVING);
        sna_init_8004E22C(pActor, bVar2, 4);
        pActor->field_8E8_pTarget->field_3E = bVar2;
    }

    iVar3 = pActor->field_904_frames_last_choke + 1;
    pActor->field_904_frames_last_choke = iVar3;

    if ((gSnaMoveDir_800ABBA4 < 0 || ((pActor->field_9B0_pad_ptr->status & PAD_SQUARE) == 0)))
    {
        GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
    }
    else
    {
        if (!((pActor->field_8E8_pTarget->field_26_hp > 0) &&
              ((iVar3 < 0x5a && pActor->field_8E8_pTarget->field_42 != 0))))
        {

            GM_ClearPlayerStatusFlag_8004E2D4(PLAYER_STATUS_MOVING);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
            return;
        }
        else
        {
            pActor->field_20_ctrl.field_4C_turn_vec.vy = gSnaMoveDir_800ABBA4 + 0x800;
        }
    }
}

void sna_init_anim_choke_hold_80059154(Actor_SnaInit *pActor, int time)
{
    if (time == 0)
    {
        pActor->field_9C8_anim_update_fn_3p = sna_init_fn_nothing_80053B80;
        pActor->field_9CC_anim_update_fn_1p = sna_init_fn_nothing_80053B80;
        sna_init_8004E22C(pActor, pActor->field_9B4_action_table->field_18->field_6, 4);
    }

    if (pActor->field_9C_obj.field_1A != 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
    }
}

void sub_800591BC(Actor_SnaInit *pActor)
{
    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_idle_8005275C);
    sna_init_clear_flags1_8004E308(pActor, (SNA_FLAG1_UNK3 | SNA_FLAG1_UNK5 | SNA_FLAG1_UNK6));
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_punch_helper_800591F4.s") // 808 bytes

void sna_init_anim_choke_helper_8005951C(Actor_SnaInit *pActor)
{
    int   sinceLastChoke;
    short press;
    short status;

    sinceLastChoke = ++pActor->field_904_frames_last_choke;

    if (((pActor->field_8E8_pTarget->field_26_hp < 1 || sinceLastChoke >= 90) ||
         pActor->field_8E8_pTarget->field_42 == 0))
    {
        sna_init_sub_8004E41C(pActor, 2);
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_hold_80059154);
        sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        return;
    }

    press = pActor->field_9B0_pad_ptr->press;
    status = pActor->field_9B0_pad_ptr->status;

    if ((press & PAD_SQUARE) != 0)
    {
        sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_rechoke_80058EF4);
    }
    else if ((status & PAD_SQUARE) == 0)
    {
        // A38 is snake stop movement frames, counts down
        if (++pActor->field_A38 >= 9)
        {
            sna_init_sub_8004E41C(pActor, 2);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_hold_80059154);
            sna_init_clear_flags1_8004E308(pActor, SNA_FLAG1_UNK3);
        }
    }
    else
    {
        pActor->field_A38 = 0;
        if (gSnaMoveDir_800ABBA4 >= 0)
        {
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_drag_80059054);
        }
    }
}

void sna_init_anim_choke_rechoke_helper_8005961C(Actor_SnaInit *pActor, int time)
{
    if (time == 0 || (pActor->field_9B0_pad_ptr->press & PAD_SQUARE) != 0)
    {
        pActor->field_8E8_pTarget->field_2A--;

        if (++pActor->field_A54.choke_count >= 10) // feels good
        {
            // TODO: fix data when vibrate is figured out
            vibrate_init2_8005D58C((unsigned char *)dword_8009EF24, 1);
            vibrate_init2_8005D58C((unsigned char *)dword_8009EF2C, 2);
            sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_kill_80058F88);
            return;
        }
    }

    if (pActor->field_9C_obj.field_1A == 0 && pActor->field_8E8_pTarget->field_42 != 0)
    {
        return;
    }

    sna_init_start_anim_8004E1F4(pActor, sna_init_anim_choke_80058E88);
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_main_logic_800596FC.s") // 5652 bytes
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_8005AD10.s")        // 2076 bytes

void sna_init_kill_8005B52C(Actor_SnaInit *pActor)
{
    GM_Control *pCtrl;   // $s2
    DG_OBJS    *pObjs;   // $s0
    Actor      *pShadow; // $a0
    Actor      *pWeapon; // $a0
    Actor      *pItem;   // $a0

    if ((pActor->field_898_flags2 & 0x1000) != 0)
    {
        GM_UnkFlagBE = 1;
    }

    pCtrl = &pActor->field_20_ctrl;
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);
    GM_FreeTarget_8002D4B0(pActor->field_89C_pTarget);

    pObjs = pActor->field_92C;
    if (pObjs)
    {
        DG_DequeuePrim_800182E0(pActor->field_92C);
        DG_FreePrim_8001BC04(pObjs);
    }

    GM_SnakeStance = pActor->field_A26_fn_stance_idx;

    pShadow = pActor->field_888_pShadow;
    if (pShadow)
    {
        GV_DestroyOtherActor_800151D8(pShadow);
    }

    pWeapon = pActor->field_908_weapon_actor;
    if (pWeapon)
    {
        GV_DestroyOtherActor_800151D8(pWeapon);
    }

    pItem = pActor->field_9A4_item_actor;
    if (pItem)
    {
        GV_DestroyOtherActor_800151D8(pItem);
    }

    if (gSnaControl_800AB9F4 == pCtrl)
    {
        gSnaControl_800AB9F4 = 0;
    }

    if (dword_800ABA20 == &pActor->field_9C_obj)
    {
        dword_800ABA20 = 0;
    }
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_init_8005B650.s") // 2356 bytes
