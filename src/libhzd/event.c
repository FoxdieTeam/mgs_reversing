#include "common.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
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

void HZD_SetBind( int param_1, BindStruct *param_2, int param_3 )
{
    gLastBindNum_800AB9B8 = param_3;
    gpBinds_800AB9BC = param_2;
    return;
}

void HZD_BindMapChange( int mask )
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

void HZD_SetEvent( HZD_EVT *event, int name )
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

void HZD_ExecBindX( BindStruct *pBind, HZD_EVT *event, int a3, int a4 )
{
    int f_4; // $v1
    int msg_type; // $a0
    int x; // $t0
    int y; // $t1
    int z; // $a1
    int f_10; // $v0
    GCL_ARGS gclArgs; // [sp+10h] [-28h] BYREF
    long args[8]; // [sp+18h] [-20h] BYREF

    f_4 = event->field_4_trigger_Hash_Name_or_camera_w;
    msg_type = event->field_0_scriptData_orHashedName;
    x = event->field_14_vec.vx;
    y = event->field_14_vec.vy;
    z= event->field_14_vec.vz;
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

static inline int HZD_helper_80029B9C(unsigned short value, unsigned int hash)
{
    return (value == 0) || (value == hash);
}

//HZD_ExecEventRCM ?
void HZD_80029B9C( HZD_HDL *hdl, HZD_EVT *event, int arg2 )
{
    BindStruct  *pBind;
    unsigned int hash;
    unsigned int name;
    unsigned int trigger;
    int          count;
    unsigned int one;
    unsigned int name2;

    pBind = gpBinds_800AB9BC;
    hash = event->field_0_scriptData_orHashedName;
    name = event->field_2_name_hash;
    trigger = event->field_4_trigger_Hash_Name_or_camera_w;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        one = 1;

        if (!HZD_helper_80029B9C(pBind->field_4, trigger))
        {
            continue;
        }

        if (!(pBind->field_6 & hdl->area_index))
        {
            continue;
        }

        if (!HZD_helper_80029B9C(pBind->field_0, hash))
        {
            if (!(pBind->field_8_param_i_c_flags & 0x2))
            {
                continue;
            }

            if (!HZD_helper_80029B9C(pBind->field_0, CHARA_SNAKE))
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

        if (HZD_helper_80029B9C(pBind->field_2_param_m, name2))
        {
            HZD_ExecBindX(pBind, event, name2, 2);
        }
    }
}

static inline int HZD_helper2_80029D50(BindStruct *pBind, HZD_EVT *event)
{
    int diff;
    int mask;

    if (!(pBind->field_B_param_e & 0xF))
    {
        return 1;
    }

    if (pBind->field_B_param_e & 0x1)
    {
        diff = (-pBind->field_C_param_d + event->field_14_vec.pad) & 0xFFF;

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
void HZD_80029D50(HZD_HDL *hdl, HZD_EVT *event, int arg2)
{
    BindStruct   *pBind;
    unsigned int  hash, hash2;
    unsigned int  name;
    unsigned int  trigger;
    int           count;
    unsigned char flag;

    if (event->field_0_scriptData_orHashedName == 0x50AE)
    {
        HZD_80029B9C(hdl, event, arg2);
        return;
    }

    pBind = gpBinds_800AB9BC;

    hash = event->field_0_scriptData_orHashedName;
    name = event->field_2_name_hash;
    trigger = event->field_4_trigger_Hash_Name_or_camera_w;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        if (!HZD_helper_80029B9C(pBind->field_4, trigger) || !(pBind->field_6 & hdl->area_index))
        {
            continue;
        }

        if (!HZD_helper_80029B9C(pBind->field_0, hash))
        {
            continue;
        }

        hash2 = name;

        if ((arg2 != 0) && HZD_helper2_80029D50(pBind, event))
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

        if (HZD_helper_80029B9C(pBind->field_2_param_m, hash2))
        {
            HZD_ExecBindX(pBind, event, hash2, 0);
        }
    }
}

//HZD_ExecEventSub ?
void HZD_8002A090(HZD_HDL *hdl, HZD_EVT *event, int flags, int hash)
{
    BindStruct     *pBinds;
    int             bindCount;
    int             msgType;
    unsigned short *pArray;
    int             count;

    pBinds = gpBinds_800AB9BC;
    bindCount = gLastBindNum_800AB9B8;

    msgType = event->field_0_scriptData_orHashedName;

    for (bindCount--; bindCount >= 0; pBinds++, bindCount--)
    {
        if (!(pBinds->field_6 & hdl->area_index))
        {
            continue;
        }

        if (flags != 0 && !(pBinds->field_8_param_i_c_flags & flags))
        {
            continue;
        }

        if (!HZD_helper_80029B9C(pBinds->field_0, msgType))
        {
            continue;
        }

        pArray = event->field_8_array;

        for (count = event->field_6_count; count > 0; count--, pArray++)
        {
            if (HZD_helper_80029B9C(pBinds->field_4, *pArray) && HZD_helper_80029B9C(pBinds->field_2_param_m, hash))
            {
                HZD_ExecBindX(pBinds, event, hash, 1);
            }
        }
    }
}

void HZD_ReExecEvent(HZD_HDL *hdl, HZD_EVT *event, unsigned int flags)
{
    if (flags & 0x200)
    {
        HZD_8002A090(hdl, event, flags, HASH_LEAVE);
    }
    if (flags & 0x100)
    {
        HZD_8002A090(hdl, event, flags, HASH_ENTER);
    }
}

//ExecLeaveEvent ?
void HZD_8002A258(HZD_HDL *hzd, HZD_EVT *event)
{
    HZD_8002A090(hzd, event, 0, HASH_LEAVE);
}

static inline int HZD_8002A27C_helper(void)
{
    if (*(short *)0x1F800000 <  *(short *)0x1F800008 ||
        *(short *)0x1F800000 >= *(short *)0x1F800010)
    {
        return 0;
    }

    if (*(short *)0x1F800002 <  *(short *)0x1F80000A ||
        *(short *)0x1F800002 >= *(short *)0x1F800012)
    {
        return 0;
    }

    if (*(short *)0x1F800004 <  *(short *)0x1F80000C ||
        *(short *)0x1F800004 >= *(short *)0x1F800014)
    {
        return 0;
    }

    return 1;
}

static inline int HZD_8002A27C_helper2(unsigned short *ptrIn, unsigned int target)
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

void HZD_8002A27C(HZD_HDL *hdl, HZD_EVT *event)
{
    HZD_AREA       *pArea;
    HZD_TRG        *pTrigger;
    int             count;
    int             i, j;
    unsigned int    name_id;
    unsigned short *pSlots;
    unsigned short *ptr;
    int             a1;

    pArea = hdl->area;
    pTrigger = pArea->triggers;

    event->field_2_name_hash = HASH_ENTER;
    count = 0;

    for (i = pArea->n_triggers - hdl->n_cameras; i > 0; i--, pTrigger++)
    {
        ptr = (unsigned short *)0x1F800000;

        *(HZD_SEG *)0x1F800008 = *(HZD_SEG *)pTrigger;
        do {} while (0);

        if (!HZD_8002A27C_helper())
        {
            continue;
        }

        name_id = pTrigger->trap.name_id;
        event->field_4_trigger_Hash_Name_or_camera_w = name_id;

        if (!HZD_8002A27C_helper2(ptr, name_id))
        {
            HZD_80029D50(hdl, event, 1);
        }
        else
        {
            HZD_80029D50(hdl, event, 2);
        }

        a1 = count;

        pSlots = event->field_8_array;
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

    event->field_6_count = count;
}

void HZD_8002A4B8(HZD_HDL *hdl, HZD_EVT *event)
{
    int    count;
    short *pData;

    pData = (short *)getScratchAddr(7);

    event->field_2_name_hash = HASH_LEAVE;

    for (count = *getScratchAddr(6); count > 0; count--)
    {
        event->field_4_trigger_Hash_Name_or_camera_w = *pData++;
        HZD_80029D50(hdl, event, 0);
    }
}

// HZD_EnterTrap ?
void HZD_8002A538(HZD_HDL *hdl, HZD_EVT *event)
{
    SVECTOR *pSrcVec;
    short   *pArr;
    short   *pScr;
    short    tmp;
    int      i;

    pSrcVec = &event->field_14_vec;

    *(short *)0x1F800000 = pSrcVec->vx;
    do {} while (0);

    *(short *)0x1F800004 = pSrcVec->vy;
    pArr = event->field_8_array;
    do {} while (0);

    tmp = pSrcVec->vz;
    pScr = (short *)getScratchAddr(7);

    do {} while (0);

    *(short *)0x1F800002 = tmp;
    *getScratchAddr(6) = event->field_6_count;

    for (i = event->field_6_count; i > 0; i--)
    {
        *pScr++ = *pArr++;
    }

    HZD_8002A27C(hdl, event);
    HZD_8002A4B8(hdl, event);
}

static inline int HZD_CheckBehindTrap_helper(void)
{
    if (*(short *)(SCRPAD_ADDR + 0x00) <  *(short *)(SCRPAD_ADDR + 0x08) ||
        *(short *)(SCRPAD_ADDR + 0x00) >= *(short *)(SCRPAD_ADDR + 0x10) ||
        *(short *)(SCRPAD_ADDR + 0x02) <  *(short *)(SCRPAD_ADDR + 0x0A) ||
        *(short *)(SCRPAD_ADDR + 0x02) >= *(short *)(SCRPAD_ADDR + 0x12) ||
        *(short *)(SCRPAD_ADDR + 0x04) <  *(short *)(SCRPAD_ADDR + 0x0C) ||
        *(short *)(SCRPAD_ADDR + 0x04) >= *(short *)(SCRPAD_ADDR + 0x14))
    {
        return 0;
    }

    return 1;
}

HZD_TRP *HZD_CheckBehindTrap(HZD_HDL *hdl, SVECTOR *svec)
{
    HZD_TRP *iterTrap;
    HZD_SEG *scratchSeg;
    int      i;
    short    copied;

    copied = svec->vx;
    *(short *)(SCRPAD_ADDR + 0x0) = copied;
    copied = svec->vy;
    *(short *)(SCRPAD_ADDR + 0x4) = copied;
    copied = svec->vz;
    *(short *)(SCRPAD_ADDR + 0x2) = copied;
    do {} while (0);

    for (i = hdl->n_cameras, iterTrap = hdl->traps; i > 0; i--, iterTrap++)
    {
        scratchSeg = (HZD_SEG *)(SCRPAD_ADDR + 0x8);
        do {} while (0);

        *scratchSeg = *(HZD_SEG *)iterTrap; // TODO: Change b1, b2 in HZD_TRP to a single HZD_SEG?
        do {} while (0);

        if (HZD_CheckBehindTrap_helper())
        {
            return iterTrap;
        }
    }

    return NULL;
}
