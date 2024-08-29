#include "libgv.h"
#include "Game/linkvarbuf.h"
#include "psyq.h"
#include "Game/game.h"
#include "mts/pad/pad.h"

/***bss****************************************************************/
extern int     dword_800B05A8[6];
extern GV_PAD GV_PadData_800B05C0[4];
/*********************************************************************/

/***$gp****************************************************************/
int GV_PadMask_800AB374 = 0;
int GV_PadOrigin_800AB378 = 0;
int GV_800AB37C = 0;

extern int dword_800AB950;
int        SECTION(".sbss") dword_800AB950;

extern int dword_800AB954;
int        SECTION(".sbss") dword_800AB954;

extern int GV_DemoPadStatus_800AB958;
int        SECTION(".sbss") GV_DemoPadStatus_800AB958;

extern int GV_DemoPadAnalog_800AB95C;
int        SECTION(".sbss") GV_DemoPadAnalog_800AB95C;
/*********************************************************************/

short key_table_8009D32C[] = {0x0000, 0x0800, 0x0400, 0x0600, 0x0000, 0x0000, 0x0200, 0x0000,
                              0x0C00, 0x0A00, 0x0000, 0x0000, 0x0E00, 0x0000, 0x0000, 0x0000};

extern int   DG_UnDrawFrameCount_800AB380;
extern int   GM_GameStatus_800AB3CC;
extern int   GV_Time_800AB330;

#ifdef VR_EXE
void sub_800165B0(MTS_PAD_DATA *data)
{
    unsigned short status = GV_DemoPadStatus_800AB958;
    if (status & 0x400)
    {
        data->capability = PAD_CAPABILITY_ANALOG_CONTROLLER;
        data->lx = GV_DemoPadAnalog_800AB95C;
        data->ly = (GV_DemoPadAnalog_800AB95C & 0xFF00) >> 8;
    }
    else
    {
        data->capability = PAD_CAPABILITY_16_BUTTON;
    }
}
#endif

int GV_UpdatePadSystem_helper_helper_800166AC(int a0, int a1, int a2)
{
    int v1, i;

    v1 = a0;

    for (i = 1; i >= 0; --i)
    {
        v1 &= ~(a1 | a2);

        if (a0 & a1)
        {
            v1 |= a2;
        }

        if (a0 & a2)
        {
            v1 |= a1;
        }

        a1 <<= 16;
        a2 <<= 16;
    }

    return v1;
}

int GV_UpdatePadSystem_helper_800166F0(int a0)
{
    switch (GM_GameStatusFlag & 0x7)
    {
    case GV_PAD_ANAJOY:
        return GV_UpdatePadSystem_helper_helper_800166AC(a0, 0x20, 0x40);
        break;
    case GV_PAD_ANALOG:
        return GV_UpdatePadSystem_helper_helper_800166AC(a0, 0x20, 0x80);
        break;
    default:
        return a0;
    }
}

void GV_UpdatePadSystem_helper2_80016750(int *button, MTS_PAD_DATA *data)
{
    int           v1;
    unsigned int  a2;
    unsigned char a1;

    *button &= 0xFFFF0FFF;

    a2 = data->lx;
    a1 = data->ly;
    v1 = 0;

    if (a2 < 0x40)
    {
        v1 = 0x8000;
    }
    else if (a2 >= 0xC1)
    {
        v1 = 0x2000;
    }

    if (a1 < 0x40)
    {
        v1 |= 0x1000;
    }
    else if (a1 >= 0xC1)
    {
        v1 |= 0x4000;
    }

    *button |= v1;
}

void GV_InitPadSystem_800167C8(void)
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
    GV_PadOrigin_800AB378 = 0;

    for (i = 5; i > -1; --i)
    {
        dword_800B05A8[i] = 0;
    }
}

void GV_UpdatePadSystem_8001682C(void)
{
    int           chan, prev;
    unsigned int  t0, t1, t2, t3, t4, t5;
    unsigned long button, ret; // button = var_20, ret = s2
    GV_PAD       *pad;
    MTS_PAD_DATA  data;
    SVECTOR       svector;
    int           s3, var;

    // loc_8001682C
    ret = mts_PadRead_8008C324(0);
    button = GV_UpdatePadSystem_helper_800166F0(ret);

    if (DG_UnDrawFrameCount_800AB380 > 0)
    {
        button = 0;
        ret = 0;
    }
    else
    {
        // loc_80016870
        if (GM_GameStatus_800AB3CC >= 0)
        {
            if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31)
            {
                ret = GV_DemoPadStatus_800AB958 & 0xF9FFF9FF;
                button = ret;
            }
            else if (GM_GameStatus_800AB3CC & STATE_PADRELEASE)
            {
                button = 0;
                ret = 0;
            }
            else if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_28)
            {
                ret &= GV_PadMask_800AB374;
                button &= GV_PadMask_800AB374;
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
        if (mts_get_pad_8008C170((chan % 2) + 1, &data) || (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31 && chan == 2))
        {
            // loc_80016944
            // int local_gamestatus = GM_GameStatus_800AB3CC & 0x40000000;
            if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31)
            {
                #ifndef VR_EXE
                    data.capability = PAD_CAPABILITY_16_BUTTON;
                #else
                    if (chan == 2)
                    {
                        sub_800165B0(&data);
                    }
                    else
                    {
                        data.capability = PAD_CAPABILITY_16_BUTTON;
                    }
                #endif
            }

            // loc_80016960
            pad->analog = data.capability - 1;

            // if ( pad->analog > 0 && ( GM_GameStatus_800AB3CC & 0x90000000 && local_gamestatus ) )
            if (pad->analog > 0 && (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_IN_DEMO)) || GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31))
            {
                // loc_8001698C
                if (button & 0xF000)
                {
                    // loc_800169A0
                    int v0 = key_table_8009D32C[(button & 0xF000) / 4096];
                    v0 += GV_PadOrigin_800AB378;
                    pad->dir = v0 & 0x0FFF;
                    pad->analog = 0;
                }
                else
                {
                    // loc_800169C0
                    MTS_PAD_DATA *local_data = &data;
                    int           lx, ly, dir, temp;

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
                        dir = (GV_VecDir2_80016EF8(&svector) + GV_PadOrigin_800AB378);
                    }
                    // loc_80016A40:
                    pad->dir = dir;
                    GV_UpdatePadSystem_helper2_80016750((int *)&button, &data);
                }
                // loc_80016A50:
                *((unsigned long *)&pad->right_dx) = *((unsigned long *)(&data.rx));
                if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_28)
                {
                    if (!(GV_PadMask_800AB374 & 0xF000))
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
                check = button & 0xF000;
                if (!(check))
                {
                    val = -1;
                }
                else
                {
                    check >>= 12;
                    val = (key_table_8009D32C[check] + GV_PadOrigin_800AB378) & 0x0FFF;
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
    GV_CopyMemory_800160D8(GV_PadData_800B05C0, &GV_PadData_800B05C0[2], 0x20);

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
    dword_800B05A8[(GV_Time_800AB330 % 6)] = t0;

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

void GV_OriginPadSystem_80016C78(int org)
{
    GV_PadOrigin_800AB378 = org;
}

int GV_GetPadOrigin_80016C84(void)
{
    return GV_PadOrigin_800AB378;
}

int GV_GetPadDirNoPadOrg_80016C90(unsigned int button)
{
    int    value;
    short *table;

    value = -1;

    if (button & 0xF000)
    {
        table = key_table_8009D32C;
        value = (button & 0xF000) / 4096;
        value = (table[value] + GV_PadOrigin_800AB378) & 0x0FFF;
    }
    return value - GV_PadOrigin_800AB378;
}
