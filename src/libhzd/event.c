#include "common.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Game/delay.h"
#include "Game/linkvarbuf.h"
#include "strcode.h"

int dword_8009D548[] = {0, 0x20, 0x40, 8, 0x800, 0x10000, 0x20000, 0x1000, 4, 1};
int dword_8009D570[] = {0x20, 0x80, 0x40, 0x10};

unsigned short GM_WeaponTypes_8009D580[] = {0x0110, 0x9042, 0x9043, 0x414C, 0x20C0, 0x2220, 0x4110, 0x4110, 0x414C, 0x414C, 0x9220};
unsigned short GM_ItemTypes_8009D598[] = {
    0x0000, 0x8000, 0x8003, 0x8001, 0x8001, 0x8001, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8003, 0x2000, 0x2000,
    0x2000, 0, 0, 0, 0, 0, 0, 0, 0, 0};

extern int    GM_PlayerStatus_800ABA50;
extern GV_PAD GV_PadData_800B05C0[4];

extern int         gLastBindNum_800AB9B8; //N_BindsLV
extern BindStruct *gpBinds_800AB9BC;

int         SECTION(".sbss") gLastBindNum_800AB9B8;
BindStruct *SECTION(".sbss") gpBinds_800AB9BC;

#define SCRPAD_ADDR 0x1F800000

/*
possible function names
 HZD_ReExecEventSubXQ
 HZD_ExecEventRCM
 Binds
 HZD_BindMapChangep
 HZD_SetEvent
 HZD_ExecBindX
 HZD_ExecEventRCM
 HZD_ExecEventL
 HZD_ReExecEventSub
 HZD_FlashEvent
 ExecLeaveEvent
 HZD_EnterTrap
*/

void HZD_SetBind_80029A5C( int param_1, BindStruct *param_2, int param_3 )
{
    gLastBindNum_800AB9B8 = param_3;
    gpBinds_800AB9BC = param_2;
    return;
}

void HZD_BindMapChange_80029A6C( int mask )
{
    int         counter; // $a1
    BindStruct *pIter;   // $v1

    pIter = gpBinds_800AB9BC;

    for ( counter = gLastBindNum_800AB9B8; counter > 0; counter-- )
    {
        if ( ( pIter->field_6 & mask ) == 0 )
        {
            pIter->field_8_param_i_c_flags &= ~0x80u;
        }
        pIter++;
    }
}

void HZD_SetEvent_80029AB4( HZD_EVT *event, int name )
{
    unsigned short *tmp;
    int             i;

    event->field_0_scriptData_orHashedName = name;
    event->field_6_count = 0;
    event->field_4_trigger_Hash_Name_or_camera_w = 0;
    event->field_2_name_hash = 0;

    tmp = event->field_8_array;

    for ( i = 6 ; i > 0 ; i-- )
    {
        *tmp++ = 0;
    }

    event->field_14_vec.vz = 0;
    event->field_14_vec.vy = 0;
    event->field_14_vec.vx = 0;
}

void HZD_ExecBindX_80029AEC( BindStruct *pBind, HZD_EVT *pSubCtrl, int a3, int a4 )
{
    int f_4; // $v1
    int msg_type; // $a0
    int x; // $t0
    int y; // $t1
    int z; // $a1
    int f_10; // $v0
    GCL_ARGS gclArgs; // [sp+10h] [-28h] BYREF
    long args[8]; // [sp+18h] [-20h] BYREF

    f_4 = pSubCtrl->field_4_trigger_Hash_Name_or_camera_w;
    msg_type = pSubCtrl->field_0_scriptData_orHashedName;
    x = pSubCtrl->field_14_vec.vx;
    y = pSubCtrl->field_14_vec.vy;
    z= pSubCtrl->field_14_vec.vz;
    gclArgs.argc = 7;
    gclArgs.argv = args;
    f_10 = pBind->field_10_every;
    args[2] = a3;
    args[6] = a4;
    args[0] = f_4;
    args[1] = msg_type;
    args[3] = x;
    args[4] = y;
    args[5] = z;

    if ( f_10 )
    {
        GM_DelayedExecCommand_80033230( pBind->field_14_proc_and_block, &gclArgs, f_10 );
    }
    else if ( ( pBind->field_B_param_e & 0x80 ) != 0 )
    {
        GCL_ExecProc( pBind->field_14_proc_and_block, &gclArgs );
    }
    else
    {
        GCL_ExecBlock( ( unsigned char * )pBind->field_14_proc_and_block, &gclArgs );
    }
}

static inline int sub_helper_80029B9C(unsigned short value, unsigned int hash)
{
    return (value == 0) || (value == hash);
}

//HZD_ExecEventRCM ?
void sub_80029B9C( HZD_HDL *pMap, HZD_EVT *arg1, int arg2 )
{
    BindStruct  *pBind;
    unsigned int hash;
    unsigned int name;
    unsigned int trigger;
    int          count;
    unsigned int one;
    unsigned int name2;

    pBind = gpBinds_800AB9BC;
    hash = arg1->field_0_scriptData_orHashedName;
    name = arg1->field_2_name_hash;
    trigger = arg1->field_4_trigger_Hash_Name_or_camera_w;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        one = 1;

        if (!sub_helper_80029B9C(pBind->field_4, trigger))
        {
            continue;
        }

        if (!(pBind->field_6 & pMap->f08_areaIndex))
        {
            continue;
        }

        if (!sub_helper_80029B9C(pBind->field_0, hash))
        {
            if (!(pBind->field_8_param_i_c_flags & 0x2))
            {
                continue;
            }

            if (!sub_helper_80029B9C(pBind->field_0, CHARA_SNAKE))
            {
                continue;
            }
        }

        name2 = name;

        if (pBind->field_B_param_e & 0xF)
        {
            continue;
        }

        if ((arg2 != 0) && (one != 0))
        {
            if ((arg2 != one) && !(pBind->field_B_param_e & 0x40))
            {
                continue;
            }
        }
        else
        {
            name2 = HASH_LEAVE;
            pBind->field_8_param_i_c_flags &= ~0x80;
        }

        if (sub_helper_80029B9C(pBind->field_2_param_m, name2))
        {
            HZD_ExecBindX_80029AEC(pBind, arg1, name2, 2);
        }
    }
}

static inline int sub_helper2_80029D50(BindStruct *pBind, HZD_EVT *arg1)
{
    int diff;
    int mask;

    if (!(pBind->field_B_param_e & 0xF))
    {
        return 1;
    }

    if (pBind->field_B_param_e & 0x1)
    {
        diff = (-pBind->field_C_param_d + arg1->field_14_vec.pad) & 0xFFF;

        if (diff > 2048)
        {
            diff = 4096 - diff;
        }

        if (pBind->field_E_param_d_or_512 < diff)
        {
            return 0;
        }
    }

    if (pBind->field_B_param_e & 0x2)
    {
        if (dword_8009D548[pBind->field_9_param_s])
        {
            if (!(GM_PlayerStatus_800ABA50 & dword_8009D548[pBind->field_9_param_s]))
            {
                return 0;
            }
        }
        else if (GM_PlayerStatus_800ABA50 != 0)
        {
            if ((GM_UnkFlagBE != 0) && !(GM_PlayerStatus_800ABA50 & 0x2))
            {
                mask = 0xFFF4C011;
            }
            else
            {
                mask = 0xFFF44010;
            }

            if (GM_PlayerStatus_800ABA50 & ~mask)
            {
                return 0;
            }
        }
    }

    if (pBind->field_B_param_e & 0x4)
    {
        if (GM_PlayerStatus_800ABA50 & 0x80)
        {
            return 0;
        }

        if (!(GV_PadData_800B05C0[0].press & dword_8009D570[pBind->field_A_param_b]))
        {
            return 0;
        }
    }

    return 1;
}

// HZD_ExecEventL ?
void sub_80029D50(HZD_HDL *pMap, HZD_EVT *arg1, int arg2)
{
    BindStruct   *pBind;
    unsigned int  hash, hash2;
    unsigned int  name;
    unsigned int  trigger;
    int           count;
    unsigned char flag;

    if (arg1->field_0_scriptData_orHashedName == 0x50AE)
    {
        sub_80029B9C(pMap, arg1, arg2);
        return;
    }

    pBind = gpBinds_800AB9BC;

    hash = arg1->field_0_scriptData_orHashedName;
    name = arg1->field_2_name_hash;
    trigger = arg1->field_4_trigger_Hash_Name_or_camera_w;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        if (!sub_helper_80029B9C(pBind->field_4, trigger) || !(pBind->field_6 & pMap->f08_areaIndex))
        {
            continue;
        }

        if (!sub_helper_80029B9C(pBind->field_0, hash))
        {
            continue;
        }

        hash2 = name;

        if ((arg2 != 0) && sub_helper2_80029D50(pBind, arg1))
        {
            if (!(pBind->field_B_param_e & 0xF))
            {
                if ((arg2 != 1) && !(pBind->field_B_param_e & 0x40))
                {
                    continue;
                }
            }
            else if (pBind->field_8_param_i_c_flags & 0x80)
            {
                continue;
            }
            else if (!(pBind->field_B_param_e & 0x40))
            {
                pBind->field_8_param_i_c_flags |= 0x80;
            }
        }
        else
        {
            flag = pBind->field_B_param_e;
            if ((flag & 0xF) && !(flag & 0x40) && !(pBind->field_8_param_i_c_flags & 0x80))
            {
                continue;
            }

            hash2 = HASH_LEAVE;
            pBind->field_8_param_i_c_flags &= ~0x80;
        }

        if (sub_helper_80029B9C(pBind->field_2_param_m, hash2))
        {
            HZD_ExecBindX_80029AEC(pBind, arg1, hash2, 0);
        }
    }
}

//HZD_ExecEventSub ?
void sub_8002A090(HZD_HDL *pHzdMap, HZD_EVT *pCtrlSub, int flags, int hash)
{
    BindStruct     *pBinds;
    int             bindCount;
    int             msgType;
    unsigned short *pArray;
    int             count;

    pBinds = gpBinds_800AB9BC;
    bindCount = gLastBindNum_800AB9B8;

    msgType = pCtrlSub->field_0_scriptData_orHashedName;

    for (bindCount--; bindCount >= 0; pBinds++, bindCount--)
    {
        if (!(pBinds->field_6 & pHzdMap->f08_areaIndex))
        {
            continue;
        }

        if (flags != 0 && !(pBinds->field_8_param_i_c_flags & flags))
        {
            continue;
        }

        if (!sub_helper_80029B9C(pBinds->field_0, msgType))
        {
            continue;
        }

        pArray = pCtrlSub->field_8_array;

        for (count = pCtrlSub->field_6_count; count > 0; count--, pArray++)
        {
            if (sub_helper_80029B9C(pBinds->field_4, *pArray) && sub_helper_80029B9C(pBinds->field_2_param_m, hash))
            {
                HZD_ExecBindX_80029AEC(pBinds, pCtrlSub, hash, 1);
            }
        }
    }
}

void HZD_ReExecEvent_8002A1F4(HZD_HDL *param_1, HZD_EVT *param_2, unsigned int flags)
{
    if (flags & 0x200)
    {
        sub_8002A090(param_1, param_2, flags, HASH_LEAVE);
    }
    if (flags & 0x100)
    {
        sub_8002A090(param_1, param_2, flags, HASH_ENTER);
    }
}

//ExecLeaveEvent ?
void sub_8002A258(HZD_HDL *hzd, HZD_EVT *event)
{
    sub_8002A090(hzd, event, 0, HASH_LEAVE);
}

static inline int GM_ActControl_helper6_helper_helper_8002A27C(void)
{
    if (*(short *)0x1F800000 < *(short *)0x1F800008 || *(short *)0x1F800000 >= *(short *)0x1F800010)
    {
        return 0;
    }

    if (*(short *)0x1F800002 < *(short *)0x1F80000A || *(short *)0x1F800002 >= *(short *)0x1F800012)
    {
        return 0;
    }

    if (*(short *)0x1F800004 < *(short *)0x1F80000C || *(short *)0x1F800004 >= *(short *)0x1F800014)
    {
        return 0;
    }

    return 1;
}

static inline int GM_ActControl_helper6_helper_helper2_8002A27C(unsigned short *ptrIn, unsigned int target)
{
    int             count = *(unsigned int *)0x1F800018;
    unsigned short *ptr = (unsigned short *)0x1F80001C;

    for (; count > 0; count--)
    {
        if (*ptr++ == target)
        {
            *(int *)0x1F800018 -= 1;
            ptr[-1] = (ptrIn + 0x0E)[*(int *)0x1F800018];
            return 1;
        }
    }
    return 0;
}

void GM_ActControl_helper6_helper_8002A27C(HZD_HDL *pMap, HZD_EVT *arg1)
{
    HZD_AREA       *pArea;
    HZD_TRG        *pTrigger;
    int             count;
    int             i, j;
    unsigned int    name_id;
    unsigned short *pSlots;
    unsigned short *ptr;
    int             a1;

    pArea = pMap->f04_area;
    pTrigger = pArea->triggers;

    arg1->field_2_name_hash = HASH_ENTER;
    count = 0;

    for (i = pArea->n_triggers - pMap->f0E_n_cameras; i > 0; i--, pTrigger++)
    {
        ptr = (unsigned short *)0x1F800000;

        *(HZD_SEG *)0x1F800008 = *(HZD_SEG *)pTrigger;
        do {} while (0);

        if (!GM_ActControl_helper6_helper_helper_8002A27C())
        {
            continue;
        }

        name_id = pTrigger->trap.name_id;
        arg1->field_4_trigger_Hash_Name_or_camera_w = name_id;

        if (!GM_ActControl_helper6_helper_helper2_8002A27C(ptr, name_id))
        {
            sub_80029D50(pMap, arg1, 1);
        }
        else
        {
            sub_80029D50(pMap, arg1, 2);
        }

        a1 = count;

        pSlots = arg1->field_8_array;
        for (j = count; j > 0; j--)
        {
            if (*pSlots++ == name_id)
            {
                count = a1;
                goto loop;
            }
        }

        *pSlots = name_id;
        count = a1 + 1;

loop:
    }

    arg1->field_6_count = count;
}


void GM_ActControl_helper6_helper2_8002A4B8(HZD_HDL *pMap, HZD_EVT *arg1)
{
    int    count;
    short *pData;

    pData = (short *)getScratchAddr(7);

    arg1->field_2_name_hash = HASH_LEAVE;

    for (count = *getScratchAddr(6); count > 0; count--)
    {
        arg1->field_4_trigger_Hash_Name_or_camera_w = *pData++;
        sub_80029D50(pMap, arg1, 0);
    }
}

// HZD_EnterTrap ?
void GM_ActControl_helper6_8002A538(HZD_HDL *pMap, HZD_EVT *arg1)
{
    SVECTOR *pSrcVec;
    short   *pArr;
    short   *pScr;
    short    tmp;
    int      i;

    pSrcVec = &arg1->field_14_vec;

    *(short *)0x1F800000 = pSrcVec->vx;
    do {} while (0);

    *(short *)0x1F800004 = pSrcVec->vy;
    pArr = arg1->field_8_array;
    do {} while (0);

    tmp = pSrcVec->vz;
    pScr = (short *)getScratchAddr(7);

    do {} while (0);

    *(short *)0x1F800002 = tmp;
    *getScratchAddr(6) = arg1->field_6_count;

    for (i = arg1->field_6_count; i > 0; i--)
    {
        *pScr++ = *pArr++;
    }

    GM_ActControl_helper6_helper_8002A27C(pMap, arg1);
    GM_ActControl_helper6_helper2_8002A4B8(pMap, arg1);
}

static inline int HZD_CheckBehindTrap_8002A5E0_helper()
{
    if (*(short *)(SCRPAD_ADDR + 0x0) < *(short *)(SCRPAD_ADDR + 0x8) ||
        *(short *)(SCRPAD_ADDR + 0x0) >= *(short *)(SCRPAD_ADDR + 0x10) ||
        *(short *)(SCRPAD_ADDR + 0x2) < *(short *)(SCRPAD_ADDR + 0xA) ||
        *(short *)(SCRPAD_ADDR + 0x2) >= *(short *)(SCRPAD_ADDR + 0x12) ||
        *(short *)(SCRPAD_ADDR + 0x4) < *(short *)(SCRPAD_ADDR + 0xC) ||
        *(short *)(SCRPAD_ADDR + 0x4) >= *(short *)(SCRPAD_ADDR + 0x14))
    {
        return 0;
    }

    return 1;
}

HZD_TRP *HZD_CheckBehindTrap_8002A5E0(HZD_HDL *pHzdMap, CONTROL *pControl)
{
    HZD_TRP *iterTrap;
    HZD_SEG *scratchSeg;
    int      i;
    short    copied;

    copied = pControl->mov.vx;
    *(short *)(SCRPAD_ADDR + 0x0) = copied;
    copied = pControl->mov.vy;
    *(short *)(SCRPAD_ADDR + 0x4) = copied;
    copied = pControl->mov.vz;
    *(short *)(SCRPAD_ADDR + 0x2) = copied;
    do {} while (0);

    for (i = pHzdMap->f0E_n_cameras, iterTrap = pHzdMap->f18_traps; i > 0; i--, iterTrap++)
    {
        scratchSeg = (HZD_SEG *)(SCRPAD_ADDR + 0x8);
        do {} while (0);

        *scratchSeg = *(HZD_SEG *)iterTrap; // TODO: Change b1, b2 in HZD_TRP to a single HZD_SEG?
        do {} while (0);

        if (HZD_CheckBehindTrap_8002A5E0_helper())
        {
            return iterTrap;
        }
    }

    return NULL;
}