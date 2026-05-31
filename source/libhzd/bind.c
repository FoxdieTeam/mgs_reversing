#define __LIBHZD_EVENT_C__
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

extern int      N_Binds;
extern HZD_BND *Bind;

int      SECTION(".sbss") N_Binds;
HZD_BND *SECTION(".sbss") Bind;

/*
possible function names
 HZD_ReExecEventSubXQ
 HZD_ExecEventRCM
 Binds
 HZD_BindMapChangep
 HZD_SetEvent
 HZD_ExecBind
 HZD_ExecEventRCM
 HZD_ExecEventL
 HZD_ReExecEventSub
 HZD_FlashEvent
 ExecLeaveEvent
 HZD_EnterTrap
*/

void HZD_SetBind( int param_1, HZD_BND *bind, int n_bind )
{
    N_Binds = n_bind;
    Bind = bind;
    return;
}

void HZD_BindMapChange( int map )
{
    HZD_BND *bind;
    int       i;

    bind = Bind;
    for ( i = N_Binds; i > 0; i-- )
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
    event->n_inside = 0;
    event->object = 0;
    event->type = 0;

    tmp = event->inside;

    for ( i = 6 ; i > 0 ; i-- )
    {
        *tmp++ = 0;
    }

    event->mov.vz = 0;
    event->mov.vy = 0;
    event->mov.vx = 0;
}

void HZD_ExecBind( HZD_BND *bnd, HZD_EVT *ev, int event, int type )
{
    GCL_ARGS args;
    long     buf[8], *p;

    p = buf;
    *p++ = ev->object;
    *p++ = ev->name;
    *p++ = event;
    *p++ = ev->mov.vx;
    *p++ = ev->mov.vy;
    *p++ = ev->mov.vz;
    *p++ = type;

    args.argc = 7;
    args.argv = buf;

    if ( bnd->time != 0 )
    {
        GM_DelayedExecCommand( bnd->command, &args, bnd->time );
    }
    else if ( bnd->field_B_param_e & 0x80 )
    {
        GCL_ExecProc( (int)bnd->command, &args );
    }
    else
    {
        GCL_ExecBlock( (u_char *)bnd->command, &args );
    }
}

static inline int HashMatch(unsigned short value, unsigned int hash)
{
    return (value == 0) || (value == hash);
}

static void HZD_ExecEventRCM( HZD_HDL *hzd, HZD_EVT *event, int mode )
{
    HZD_BND  *pBind;
    unsigned int hash;
    unsigned int name;
    unsigned int trigger;
    int          count;
    unsigned int one;
    unsigned int name2;

    pBind = Bind;
    hash = event->name;
    name = event->type;
    trigger = event->object;

    count = N_Binds;
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

            if (!HashMatch(pBind->field_0, SNAKE_NAME))
            {
                continue;
            }
        }

        name2 = name;

        if (pBind->field_B_param_e & 0xF)
        {
            continue;
        }

        if ((mode != 0) && (one != 0))
        {
            if ((mode != one) && !(pBind->field_B_param_e & 0x40))
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
            HZD_ExecBind(pBind, event, name2, 2);
        }
    }
}

static inline int HZD_helper2_80029D50(HZD_BND *pBind, HZD_EVT *event)
{
    int diff;
    int mask;

    if (!(pBind->field_B_param_e & 0xF))
    {
        return 1;
    }

    if (pBind->field_B_param_e & 0x1)
    {
        diff = (-pBind->field_C_param_d + event->mov.pad) & 0xFFF;

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

void HZD_ExecEvent(HZD_HDL *hzd, HZD_EVT *event, int mode)
{
    HZD_BND   *pBind;
    unsigned int  hash, hash2;
    unsigned int  name;
    unsigned int  trigger;
    int           count;
    unsigned char flag;

    if (event->name == RCM_NAME)
    {
        HZD_ExecEventRCM(hzd, event, mode);
        return;
    }

    pBind = Bind;

    hash = event->name;
    name = event->type;
    trigger = event->object;

    count = N_Binds;
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

        if ((mode != 0) && HZD_helper2_80029D50(pBind, event))
        {
            if (!(pBind->field_B_param_e & 0xF))
            {
                if ((mode != 1) && !(pBind->field_B_param_e & 0x40))
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
            HZD_ExecBind(pBind, event, hash2, 0);
        }
    }
}

//HZD_ExecEventSub ?
STATIC void HZD_8002A090(HZD_HDL *hzd, HZD_EVT *event, int flags, int hash)
{
    HZD_BND     *pBinds;
    int             bindCount;
    int             msgType;
    unsigned short *pArray;
    int             count;

    pBinds = Bind;
    bindCount = N_Binds;

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

        pArray = event->inside;

        for (count = event->n_inside; count > 0; count--, pArray++)
        {
            if (HashMatch(pBinds->field_4, *pArray) && HashMatch(pBinds->field_2_param_m, hash))
            {
                HZD_ExecBind(pBinds, event, hash, 1);
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
