#define __LIBGV_PAD_C__
#include "libgv.h"

#include "mts/mts.h"
#include "mts/mts_pad.h"
#include "linkvar.h"
#include "game/game.h"

/***bss****************************************************************/
static int BSS dword_800B05A8[ 6 ];
GV_PAD BSS     GV_PadData[ 4 ];
/*********************************************************************/

#define ANALOG_MARGIN 64

int GV_PadMask = 0;
STATIC int PadOrg = 0;
STATIC int GV_800AB37C = 0;

STATIC int SECTION(".sbss") dword_800AB950;
STATIC int SECTION(".sbss") dword_800AB954;
u_long SECTION(".sbss") GV_DemoPadStatus;
u_long SECTION(".sbss") GV_DemoPadAnalog;

#ifdef VR_EXE
static void sub_800165B0( MTS_PAD *pad )
{
    u_short status;

    status = GV_DemoPadStatus;
    if ( status & PAD_R3 )
    {
        pad->flag = MTS_PAD_ANALOG;
        pad->lx = GV_DemoPadAnalog;
        pad->ly = ( GV_DemoPadAnalog & 0xFF00 ) >> 8;
    }
    else
    {
        pad->flag = MTS_PAD_DIGITAL;
    }
}
#endif

static int SwapButtons( int stat, int a, int b )
{
    int swap, i;

    swap = stat;
    for ( i = 1; i >= 0; i-- )
    {
        swap &= ~( a | b );
        if ( stat & a ) swap |= b;
        if ( stat & b ) swap |= a;
        a <<= 16;
        b <<= 16;
    }
    return swap;
}

static int ApplyConfig( int stat )
{
    switch ( GM_Configuration & GM_CONFIG_BUTTON_MASK )
    {
    case GM_CONFIG_BUTTON_TYPE_B:
        return SwapButtons( stat, PAD_CIRCLE, PAD_CROSS );
    case GM_CONFIG_BUTTON_TYPE_C:
        return SwapButtons( stat, PAD_CIRCLE, PAD_SQUARE );
    default: /* GM_CONFIG_BUTTON_TYPE_A */
        return stat;
    }
}

static void AnalogStat( int *stat, MTS_PAD *pad )
{
    u_char dx, dy;
    int dir;

    *stat &= ~PAD_UDLR;

    dx = pad->lx;
    dy = pad->ly;

    dir = 0;
    if ( dx < 128 - ANALOG_MARGIN ) dir = PAD_LEFT;
    else if ( dx > 128 + ANALOG_MARGIN ) dir = PAD_RIGHT;
    if ( dy < 128 - ANALOG_MARGIN ) dir |= PAD_UP;
    else if ( dy > 128 + ANALOG_MARGIN ) dir |= PAD_DOWN;
    *stat |= dir;
}

void GV_InitPadSystem( void )
{
    GV_PAD *pad;
    int i;

    pad = GV_PadData;
    for ( i = 2; i > 0; i-- )
    {
        pad->release = 0;
        pad->press = 0;
        pad->status = 0;
        pad->dir = -1;
        pad++;
    }

    dword_800AB950 = 0;
    PadOrg = 0;

    for ( i = 0; i < 6; i++ )
    {
        dword_800B05A8[ i ] = 0;
    }
}

static inline int GetPadDir( int pad )
{
    static short Dirs[] = {
        0x000, 0x800, 0x400, 0x600,
        0x000, 0x000, 0x200, 0x000,
        0xC00, 0xA00, 0x000, 0x000,
        0xE00, 0x000, 0x000, 0x000 
    };
    pad &= PAD_UDLR;
    if ( pad == 0 ) return -1;
    return 4095 & ( Dirs[ pad >> 12 ] + PadOrg );
}

void GV_UpdatePadSystem( void )
{
    unsigned long ret, button;

    int           chan, prev;
    unsigned int  t0, t1, t2, t3, t4, t5;
    GV_PAD       *pad;
    MTS_PAD       data;
    SVECTOR       svector;
    int           s3, var;

    ret = mts_PadRead(0);
    button = ApplyConfig(ret);

    if ( DG_UnDrawFrameCount > 0 )
    {
        button = 0;
        ret = 0;
    }
    else if ( !( GM_GameStatus & STATE_DEMO ) )
    {
        if ( GM_GameStatus & STATE_PADDEMO )
        {
            ret = GV_DemoPadStatus & ~0x06000600;
            button = ret;
        }
        else if ( GM_GameStatus & STATE_PADRELEASE )
        {
            button = 0;
            ret = 0;
        }
        else if ( GM_GameStatus & STATE_PADMASK )
        {
            button &= GV_PadMask;
            ret &= GV_PadMask;
        }
    }

    pad = GV_PadData;
    s3 = 0;
    chan = 2;

    for (; chan > 0; --chan)
    {
        if (mts_get_pad((chan % 2) + 1, &data) || (GM_GameStatus & STATE_PADDEMO && chan == 2))
        {
            // loc_80016944
            // int local_gamestatus = GM_GameStatus & 0x40000000;
            if (GM_GameStatus & STATE_PADDEMO)
            {
            #ifndef VR_EXE
                data.flag = MTS_PAD_DIGITAL;
            #else
                if (chan == 2)
                {
                    sub_800165B0(&data);
                }
                else
                {
                    data.flag = MTS_PAD_DIGITAL;
                }
            #endif
            }

            pad->analog = data.flag - 1;

            if (pad->analog > 0 && (!(GM_GameStatus & (STATE_PADRELEASE | STATE_DEMO)) || GM_GameStatus & STATE_PADDEMO))
            {
                if (button & PAD_UDLR)
                {
                    pad->dir = GetPadDir( button );
                    pad->analog = 0;
                }
                else
                {
                    // loc_800169C0
                    MTS_PAD *local_data = &data;
                    int      lx, ly, dir, temp;

                    // analog x dir
                    temp = local_data->lx - 0x80;
                    if (temp < 0)
                    {
                        temp = local_data->lx - 0x79;
                    }
                    temp >>= 3;
                    lx = temp << 8;
                    svector.vx = lx;

                    // analog y dir
                    temp = local_data->ly - 0x80;
                    if (temp < 0)
                    {
                        temp = local_data->ly - 0x79;
                    }
                    // this is all nonsense and clearly not the way it would have been originally programmed
                    ly = temp >> 3;
                    temp = ly << 8;
                    svector.vz = temp;

                    temp = lx + 0x07FF;
                    temp &= 0xFFFF;

                    ly <<= 8;

                    if (((unsigned int)temp < 0x0FFF) && (ly >= -0x07FF) && (ly < 0x800))
                    {
                        dir = -1;
                    }
                    else
                    {
                        // loc_80016A2C:
                        dir = (GV_VecDir2(&svector) + PadOrg);
                    }
                    // loc_80016A40:
                    pad->dir = dir;
                    AnalogStat((int *)&button, &data);
                }
                // loc_80016A50:
                *((unsigned long *)&pad->right_dx) = *((unsigned long *)(&data.rx));
                if (GM_GameStatus & STATE_PADMASK)
                {
                    if (!(GV_PadMask & PAD_UDLR))
                    {
                        pad->analog = 0;
                        pad->dir = -1;
                    }
                }
            }
            else
            {
                pad->analog = 0;
                pad->dir = GetPadDir( button );
            }

            var = 1;
            GV_800AB37C |= var << chan;
        }
        else
        {
            // loc_80016AF0/loc_80016AF4
            pad->analog = 0;
            pad->dir = -1;
        }

        // loc_80016B00:
        pad++;
        s3 |= button << ((2 - chan) << 4);
        button >>= 16;
    }

    // loc_80016B28
    ret |= s3 & 0xF000F000;
    button = s3;
    GV_CopyMemory(GV_PadData, &GV_PadData[2], sizeof(GV_PAD)*2);

    prev = dword_800AB954;
    dword_800AB954 = ret;

    t0 = button & ~dword_800AB950;
    t1 = 0;
    t2 = ~button & dword_800AB950;
    t4 = ret & ~prev;
    t3 = ~ret & prev;

    dword_800AB950 = button;

    if (t0)
    {
        for (chan = t1; chan < 6; chan++)
        {
            t1 |= dword_800B05A8[chan];
        }
        t1 &= t0;
    }

    // loc_80016BB4
    chan = 4;
    t5 = 2;
    dword_800B05A8[(GV_Time % 6)] = t0;

    pad = GV_PadData;

    for (; chan > 0; --chan)
    {
        if (chan == t5)
        {
            // loc_80016C14
            button = ret;
            t0 = t4;
            t2 = t3;
        }
        // loc_80016C20
        pad->status = button;

        pad->press = t0;
        t0 >>= 16; // max value + 1;

        pad->release = t2;
        t2 >>= 16;

        pad->quick = t1;
        t1 >>= 16;

        pad++;
        button = (button >> 16) & 0xFFFF;
    }
}

void GV_OriginPadSystem( int org )
{
    PadOrg = org;
}

int GV_GetPadOrigin( void )
{
    return PadOrg;
}

int GV_GetPadDirNoPadOrg( int pad )
{
    return GetPadDir( pad ) - PadOrg;
}
