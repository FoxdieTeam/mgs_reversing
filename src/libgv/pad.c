#include "libgv.h"
#include "Game/linkvarbuf.h"
#include "Game/game.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"

/***bss****************************************************************/
extern int     dword_800B05A8[6];
extern GV_PAD GV_PadData_800B05C0[4];
/*********************************************************************/

/***$gp****************************************************************/
int GV_PadMask = 0;
int GV_PadOrigin = 0;
int GV_800AB37C = 0;

int SECTION(".sbss") dword_800AB950;
int SECTION(".sbss") dword_800AB954;
int SECTION(".sbss") GV_DemoPadStatus_800AB958;
int SECTION(".sbss") GV_DemoPadAnalog_800AB95C;
/*********************************************************************/

short key_table_8009D32C[] = {
    0x0000, 0x0800, 0x0400, 0x0600, 0x0000, 0x0000, 0x0200, 0x0000,
    0x0C00, 0x0A00, 0x0000, 0x0000, 0x0E00, 0x0000, 0x0000, 0x0000
};

extern int   DG_UnDrawFrameCount;
extern int   GM_GameStatus;
extern int   GV_Time;

#ifdef VR_EXE
void sub_800165B0(MTS_PAD *data)
{
    unsigned short status = GV_DemoPadStatus_800AB958;
    if (status & 0x400)
    {
        data->capability = MTS_PAD_ANALOG;
        data->lx = GV_DemoPadAnalog_800AB95C;
        data->ly = (GV_DemoPadAnalog_800AB95C & 0xFF00) >> 8;
    }
    else
    {
        data->capability = MTS_PAD_DIGITAL;
    }
}
#endif

int GV_SwapButtons(int button, int a, int b)
{
    int swapped;
    int i;

    swapped = button;

    for (i = 1; i >= 0; --i)
    {
        swapped &= ~(a | b);

        if (button & a)
        {
            swapped |= b;
        }

        if (button & b)
        {
            swapped |= a;
        }

        a <<= 16;
        b <<= 16;
    }

    return swapped;
}

int GV_ConvertButtonMode(int button)
{
    switch (GM_GameStatusFlag & 0x7)
    {
    case 1: // Button Mode B
        return GV_SwapButtons(button, PAD_CIRCLE, PAD_CROSS);

    case 2: // Button Mode C
        return GV_SwapButtons(button, PAD_CIRCLE, PAD_SQUARE);

    default: // Button Mode A
        return button;
    }
}

void GV_AnalogToDirection(int *button, MTS_PAD *data)
{
    char lx, rx;
    int  dir;

    *button &= ~PAD_DIR;

    lx = data->lx;
    rx = data->ly;
    dir = 0;

    if (lx < 64)
    {
        dir = PAD_LEFT;
    }
    else if (lx > 192)
    {
        dir = PAD_RIGHT;
    }

    if (rx < 64)
    {
        dir |= PAD_UP;
    }
    else if (rx > 192)
    {
        dir |= PAD_DOWN;
    }

    *button |= dir;
}

void GV_InitPadSystem(void)
{
    int     i;
    GV_PAD *pad;

    pad = GV_PadData_800B05C0;

    for (i = 2; i > 0; --i)
    {
        pad->release = 0;
        pad->press = 0;
        pad->status = 0;
        pad->dir = -1;
        pad++;
    }

    dword_800AB950 = 0;
    GV_PadOrigin = 0;

    for (i = 5; i > -1; --i)
    {
        dword_800B05A8[i] = 0;
    }
}

void GV_UpdatePadSystem(void)
{
    int           chan, prev;
    unsigned int  t0, t1, t2, t3, t4, t5;
    unsigned long button, ret; // button = var_20, ret = s2
    GV_PAD       *pad;
    MTS_PAD       data;
    SVECTOR       svector;
    int           s3, var;

    // loc_8001682C
    ret = mts_PadRead(0);
    button = GV_ConvertButtonMode(ret);

    if (DG_UnDrawFrameCount > 0)
    {
        button = 0;
        ret = 0;
    }
    else
    {
        // loc_80016870
        if (GM_GameStatus >= 0)
        {
            if (GM_GameStatus & STATE_PADDEMO)
            {
                ret = GV_DemoPadStatus_800AB958 & ~0x06000600;
                button = ret;
            }
            else if (GM_GameStatus & STATE_PADRELEASE)
            {
                button = 0;
                ret = 0;
            }
            else if (GM_GameStatus & STATE_PADMASK)
            {
                ret &= GV_PadMask;
                button &= GV_PadMask;
            }
        }
    }

    // loc_800168E0
    pad = GV_PadData_800B05C0;
    s3 = 0;
    chan = 2;

    // loc_800168FC
    for (; chan > 0; --chan)
    {
        if (mts_get_pad((chan % 2) + 1, &data) || (GM_GameStatus & STATE_PADDEMO && chan == 2))
        {
            // loc_80016944
            // int local_gamestatus = GM_GameStatus & 0x40000000;
            if (GM_GameStatus & STATE_PADDEMO)
            {
                #ifndef VR_EXE
                    data.capability = MTS_PAD_DIGITAL;
                #else
                    if (chan == 2)
                    {
                        sub_800165B0(&data);
                    }
                    else
                    {
                        data.capability = MTS_PAD_DIGITAL;
                    }
                #endif
            }

            // loc_80016960
            pad->analog = data.capability - 1;

            // if ( pad->analog > 0 && ( GM_GameStatus & 0x90000000 && local_gamestatus ) )
            if (pad->analog > 0 && (!(GM_GameStatus & (STATE_PADRELEASE | STATE_DEMO)) || GM_GameStatus & STATE_PADDEMO))
            {
                // loc_8001698C
                if (button & PAD_DIR)
                {
                    // loc_800169A0
                    int v0 = key_table_8009D32C[(button & PAD_DIR) >> 12];
                    v0 += GV_PadOrigin;
                    pad->dir = v0 & 0x0FFF;
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
                        dir = (GV_VecDir2(&svector) + GV_PadOrigin);
                    }
                    // loc_80016A40:
                    pad->dir = dir;
                    GV_AnalogToDirection((int *)&button, &data);
                }
                // loc_80016A50:
                *((unsigned long *)&pad->right_dx) = *((unsigned long *)(&data.rx));
                if (GM_GameStatus & STATE_PADMASK)
                {
                    if (!(GV_PadMask & PAD_DIR))
                    {
                        pad->analog = 0;
                        pad->dir = -1;
                    }
                }
            }
            else
            {
                // loc_80016A94
                int val, check;
                pad->analog = 0;
                check = button & PAD_DIR;
                if (!(check))
                {
                    val = -1;
                }
                else
                {
                    check >>= 12;
                    val = (key_table_8009D32C[check] + GV_PadOrigin) & 0x0FFF;
                }
                pad->dir = val;
            }
            // loc_80016AD8
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
    GV_CopyMemory(GV_PadData_800B05C0, &GV_PadData_800B05C0[2], 0x20);

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

    pad = GV_PadData_800B05C0;

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

void GV_OriginPadSystem(int org)
{
    GV_PadOrigin = org;
}

int GV_GetPadOrigin(void)
{
    return GV_PadOrigin;
}

int GV_GetPadDirNoPadOrg(unsigned int button)
{
    int value;

    value = -1;
    if (button & PAD_DIR)
    {
        value = (key_table_8009D32C[(button & PAD_DIR) >> 12] + GV_PadOrigin) & ~PAD_DIR & 0xFFFF;
    }

    return value - GV_PadOrigin;
}
