#define __HZD_EVENT_SBSS__
#include "libhzd.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/delay.h"
#include "linkvar.h"
#include "strcode.h"

STATIC int dword_8009D548[] = {0, 0x20, 0x40, 8, 0x800, 0x10000, 0x20000, 0x1000, 4, 1};
STATIC int dword_8009D570[] = {0x20, 0x80, 0x40, 0x10};

// TODO: These two shouldn't belong in libhzd...
unsigned short GM_WeaponTypes[] = {
    0x0110,     //  0: NONE
    0x9042,     //  1: SOCOM
    0x9043,     //  2: FAMAS
    0x414C,     //  3: GRENADE
    0x20C0,     //  4: NIKITA
    0x2220,     //  5: STINGER
    0x4110,     //  6: CLAYMORE
    0x4110,     //  7: C4
    0x414C,     //  8: STUN G.
    0x414C,     //  9: CHAFF G.
    0x9220      // 10: PSG1
};
unsigned short GM_ItemTypes[] = {
    0x0000,     //  0: NONE
    0x8000,     //  1: CIGS
    0x8003,     //  2: SCOPE
    0x8001,     //  3: C.BOX A
    0x8001,     //  4: C.BOX B
    0x8001,     //  5: C.BOX C
    0x8000,     //  6: N.V.G.
    0x8000,     //  7: THERM G.
    0x8000,     //  8: GASMASK
    0x8000,     //  9: B.ARMOR
    0x8000,     // 10: KETCHUP
    0x8000,     // 11: STEALTH
    0x8000,     // 12: BANDANA
    0x8003,     // 13: CAMERA
    0x2000,     // 14: RATION
    0x2000,     // 15: MEDICINE
    0x2000,     // 16: DIAZEPAM
    0,          // 17: PAL KEY
    0,          // 18: CARD
    0,          // 19: TIMER B.
    0,          // 20: MINE D.
    0,          // 21: DISC
    0,          // 22: ROPE
    0,          // 23: SCARF
    0,          // 24: SUPPR
    0           // 25: ???
};

extern int         gLastBindNum_800AB9B8; //N_BindsLV
extern HZD_BIND *gpBinds_800AB9BC;

int         SECTION(".sbss") gLastBindNum_800AB9B8;
HZD_BIND *SECTION(".sbss") gpBinds_800AB9BC;

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

void HZD_SetBind( int param_1, HZD_BIND *bind, int n_bind )
{
    gLastBindNum_800AB9B8 = n_bind;
    gpBinds_800AB9BC = bind;
    return;
}

void HZD_BindMapChange( int map )
{
    HZD_BIND *bind;
    int       i;

    bind = gpBinds_800AB9BC;
    for ( i = gLastBindNum_800AB9B8; i > 0; i-- )
    {
        if ( !( bind->map & map ) )
        {
            bind->field_8_param_i_c_flags &= ~0x80;
        }

        bind++;
    }
}

void HZD_SetEvent( HZD_EVT *event, int name )
{
    unsigned short *tmp;
    int             i;

    event->name = name;
    event->n_triggers = 0;
    event->last = 0;
    event->type = 0;

    tmp = event->triggers;

    for ( i = 6 ; i > 0 ; i-- )
    {
        *tmp++ = 0;
    }

    event->pos.vz = 0;
    event->pos.vy = 0;
    event->pos.vx = 0;
}

void HZD_ExecBindX( HZD_BIND *pBind, HZD_EVT *event, int a3, int a4 )
{
    int f_4; // $v1
    int msg_type; // $a0
    int x; // $t0
    int y; // $t1
    int z; // $a1
    int f_10; // $v0
    GCL_ARGS gclArgs; // [sp+10h] [-28h] BYREF
    long args[8]; // [sp+18h] [-20h] BYREF

    f_4 = event->last;
    msg_type = event->name;
    x = event->pos.vx;
    y = event->pos.vy;
    z= event->pos.vz;
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
        GM_DelayedExecCommand( pBind->field_14_proc_and_block, &gclArgs, f_10 );
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

static inline int HashMatch(unsigned short value, unsigned int hash)
{
    return (value == 0) || (value == hash);
}

void HZD_ExecEventRCM( HZD_HDL *hzd, HZD_EVT *event, int arg2 )
{
    HZD_BIND  *pBind;
    unsigned int hash;
    unsigned int name;
    unsigned int trigger;
    int          count;
    unsigned int one;
    unsigned int name2;

    pBind = gpBinds_800AB9BC;
    hash = event->name;
    name = event->type;
    trigger = event->last;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        one = 1;

        if (!HashMatch(pBind->field_4, trigger))
        {
            continue;
        }

        if (!(pBind->map & hzd->map))
        {
            continue;
        }

        if (!HashMatch(pBind->field_0, hash))
        {
            if (!(pBind->field_8_param_i_c_flags & 0x2))
            {
                continue;
            }

            if (!HashMatch(pBind->field_0, CHARA_SNAKE))
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

        if (HashMatch(pBind->field_2_param_m, name2))
        {
            HZD_ExecBindX(pBind, event, name2, 2);
        }
    }
}

static inline int HZD_helper2_80029D50(HZD_BIND *pBind, HZD_EVT *event)
{
    int diff;
    int mask;

    if (!(pBind->field_B_param_e & 0xF))
    {
        return 1;
    }

    if (pBind->field_B_param_e & 0x1)
    {
        diff = (-pBind->field_C_param_d + event->pos.pad) & 0xFFF;

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
            if (!(GM_PlayerStatus & dword_8009D548[pBind->field_9_param_s]))
            {
                return 0;
            }
        }
        else if (GM_PlayerStatus != 0)
        {
            if ((GM_UnkFlagBE != 0) && !(GM_PlayerStatus & 0x2))
            {
                mask = 0xFFF4C011;
            }
            else
            {
                mask = 0xFFF44010;
            }

            if (GM_PlayerStatus & ~mask)
            {
                return 0;
            }
        }
    }

    if (pBind->field_B_param_e & 0x4)
    {
        if (GM_PlayerStatus & PLAYER_NOT_PLAYABLE)
        {
            return 0;
        }

        if (!(GV_PadData[0].press & dword_8009D570[pBind->field_A_param_b]))
        {
            return 0;
        }
    }

    return 1;
}

// HZD_ExecEventL ?
STATIC void HZD_80029D50(HZD_HDL *hzd, HZD_EVT *event, int arg2)
{
    HZD_BIND   *pBind;
    unsigned int  hash, hash2;
    unsigned int  name;
    unsigned int  trigger;
    int           count;
    unsigned char flag;

    if (event->name == CHARA_RCM)
    {
        HZD_ExecEventRCM(hzd, event, arg2);
        return;
    }

    pBind = gpBinds_800AB9BC;

    hash = event->name;
    name = event->type;
    trigger = event->last;

    count = gLastBindNum_800AB9B8;
    for (count--; count >= 0; pBind++, count--)
    {
        if (!HashMatch(pBind->field_4, trigger) || !(pBind->map & hzd->map))
        {
            continue;
        }

        if (!HashMatch(pBind->field_0, hash))
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

        if (HashMatch(pBind->field_2_param_m, hash2))
        {
            HZD_ExecBindX(pBind, event, hash2, 0);
        }
    }
}

//HZD_ExecEventSub ?
STATIC void HZD_8002A090(HZD_HDL *hzd, HZD_EVT *event, int flags, int hash)
{
    HZD_BIND     *pBinds;
    int             bindCount;
    int             msgType;
    unsigned short *pArray;
    int             count;

    pBinds = gpBinds_800AB9BC;
    bindCount = gLastBindNum_800AB9B8;

    msgType = event->name;

    for (bindCount--; bindCount >= 0; pBinds++, bindCount--)
    {
        if (!(pBinds->map & hzd->map))
        {
            continue;
        }

        if (flags != 0 && !(pBinds->field_8_param_i_c_flags & flags))
        {
            continue;
        }

        if (!HashMatch(pBinds->field_0, msgType))
        {
            continue;
        }

        pArray = event->triggers;

        for (count = event->n_triggers; count > 0; count--, pArray++)
        {
            if (HashMatch(pBinds->field_4, *pArray) && HashMatch(pBinds->field_2_param_m, hash))
            {
                HZD_ExecBindX(pBinds, event, hash, 1);
            }
        }
    }
}

void HZD_ReExecEvent(HZD_HDL *hzd, HZD_EVT *event, unsigned int flags)
{
    if (flags & 0x200)
    {
        HZD_8002A090(hzd, event, flags, HASH_LEAVE);
    }
    if (flags & 0x100)
    {
        HZD_8002A090(hzd, event, flags, HASH_ENTER);
    }
}

void HZD_ExecLeaveEvent(HZD_HDL *hzd, HZD_EVT *event)
{
    HZD_8002A090(hzd, event, 0, HASH_LEAVE);
}

static inline int CheckTrapBounds(void)
{
    HZD_VEC *pos;
    HZD_SEG *box;

    pos = (HZD_VEC *)(SCRPAD_ADDR + 0);
    box = (HZD_SEG *)(SCRPAD_ADDR + 8);

    if (pos->x < box->p1.x || pos->x >= box->p2.x ||
        pos->z < box->p1.z || pos->z >= box->p2.z ||
        pos->y < box->p1.y || pos->y >= box->p2.y)
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

STATIC void HZD_8002A27C(HZD_HDL *hzd, HZD_EVT *event)
{
    HZD_GRP *group;
    HZD_TRG *trigger;
    int      count;

    int             i, j;
    unsigned int    name_id;
    unsigned short *pSlots;
    unsigned short *ptr;
    int             a1;

    group = hzd->group;
    trigger = group->triggers;

    event->type = HASH_ENTER;

    count = 0;
    for (i = group->n_triggers - hzd->n_cameras; i > 0; i--, trigger++)
    {
        ptr = (unsigned short *)SCRPAD_ADDR;
        *(HZD_SEG *)(SCRPAD_ADDR + 8) = *(HZD_SEG *)trigger;

        if (!CheckTrapBounds())
        {
            continue;
        }

        name_id = trigger->trap.name_id;
        event->last = name_id;

        if (!HZD_8002A27C_helper2(ptr, name_id))
        {
            HZD_80029D50(hzd, event, 1);
        }
        else
        {
            HZD_80029D50(hzd, event, 2);
        }

        a1 = count;

        pSlots = event->triggers;
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

    event->n_triggers = count;
}

STATIC void HZD_8002A4B8(HZD_HDL *hzd, HZD_EVT *event)
{
    int    count;
    short *pData;

    pData = (short *)getScratchAddr(7);

    event->type = HASH_LEAVE;

    for (count = *getScratchAddr(6); count > 0; count--)
    {
        event->last = *pData++;
        HZD_80029D50(hzd, event, 0);
    }
}

void HZD_EnterTrap(HZD_HDL *hzd, HZD_EVT *event)
{
    SVECTOR *pSrcVec;
    short   *pArr;
    short   *pScr;
    short    tmp;
    int      i;

    pSrcVec = &event->pos;

    *(short *)0x1F800000 = pSrcVec->vx;
    do {} while (0);

    *(short *)0x1F800004 = pSrcVec->vy;
    pArr = event->triggers;
    do {} while (0);

    tmp = pSrcVec->vz;
    pScr = (short *)getScratchAddr(7);

    do {} while (0);

    *(short *)0x1F800002 = tmp;
    *getScratchAddr(6) = event->n_triggers;

    for (i = event->n_triggers; i > 0; i--)
    {
        *pScr++ = *pArr++;
    }

    HZD_8002A27C(hzd, event);
    HZD_8002A4B8(hzd, event);
}

// TODO: move

#define HZD_COPY_ELEM(dst, src) \
do {                            \
    *(dst) = (src);             \
} while (0)

#define HZD_COPY_VEC(dst, src)                        \
do {                                                  \
    HZD_COPY_ELEM(&((HZD_VEC *)(dst))->x, (src)->vx); \
    HZD_COPY_ELEM(&((HZD_VEC *)(dst))->y, (src)->vy); \
    HZD_COPY_ELEM(&((HZD_VEC *)(dst))->z, (src)->vz); \
} while (0)

HZD_TRP *HZD_CheckBehindTrap(HZD_HDL *hzd, SVECTOR *pos)
{
    int      i;
    HZD_TRP *trap;

    HZD_COPY_VEC(SCRPAD_ADDR + 0, pos);

    for (i = hzd->n_cameras, trap = hzd->traps; i > 0; i--, trap++)
    {
        *(HZD_SEG *)(SCRPAD_ADDR + 8) = *(HZD_SEG *)trap;

        if (CheckTrapBounds())
        {
            return trap;
        }
    }

    return NULL;
}
