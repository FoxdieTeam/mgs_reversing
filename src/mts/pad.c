#include "linker.h"
#include "mts_new.h"
#include "psyq.h"

// BSS
extern char          gMtsPadActBuffers_800C1470[2][6];
extern unsigned char gMtsPadRecvBuffers_800C1480[2][36];
extern unsigned char gMtsPadSendBuffers_800C14D0[2][8];
extern short         gMtsPadUnknBuffers_800C14E0[2][4];
extern int           gMtsPadInitStates_800C14F0[2];

int dword_800A3DB0 = 1;
int dword_800A3DB4 = 0;
int dword_800A3DB8 = 0;
int gMtsPadInited_800A3DBC = 0;
int dword_800A3DC0[] = {0, 0};
int dword_800A3DC8 = 1;

void mts_init_controller_actuators_8008BC8C(int pad)
{
    int port;
    int act;
    int i;
    int func, subfunc, size;

    port = pad * 16;
    act = PadInfoAct(port, -1, 0);

    for (i = 0; i < 6; i++)
    {
        gMtsPadActBuffers_800C1470[pad][i] = 0xFF;
    }

    for (i = act - 1; i >= 0; i--)
    {
        func = PadInfoAct(port, i, InfoActFunc);
        subfunc = PadInfoAct(port, i, InfoActSub);
        size = PadInfoAct(port, i, InfoActSize);

        if (func != 1)
        {
            continue;
        }

        if ((subfunc == 1) && (size == 1))
        {
            gMtsPadActBuffers_800C1470[pad][1] = i;
            continue;
        }

        if ((subfunc == 2) && (size == 0))
        {
            gMtsPadActBuffers_800C1470[pad][0] = i;
        }
    }

    PadSetActAlign(port, gMtsPadActBuffers_800C1470[pad]);
}

void mts_callback_controller_8008BDEC()
{
    int i;
    int state;
    int type;

    for (i = 0; i < 2; i++)
    {
        state = PadGetState(i * 16);
        type = 0;

        switch (state)
        {
        case 6:
            if (gMtsPadInitStates_800C14F0[i] == 1)
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 0;
                gMtsPadSendBuffers_800C14D0[i][1] = 0;

                mts_init_controller_actuators_8008BC8C(i);

                gMtsPadInitStates_800C14F0[i] = 3;
                gMtsPadUnknBuffers_800C14E0[i][0] = type;
                continue;
            }

            break;

        case 2:
            gMtsPadInitStates_800C14F0[i] = 2;
            break;

        case 1:
            gMtsPadInitStates_800C14F0[i] = 1;

        default:
            gMtsPadUnknBuffers_800C14E0[i][0] = type;
            continue;
        }


        if (gMtsPadRecvBuffers_800C1480[i][0] == 0)
        {
            switch (gMtsPadRecvBuffers_800C1480[i][1] >> 4)
            {
            case 7:
                type++;

            case 5:
                type++;
                *(unsigned int *)&gMtsPadUnknBuffers_800C14E0[i][2] = *(unsigned int *)&gMtsPadRecvBuffers_800C1480[i][4];

            case 4:
                type++;
                gMtsPadUnknBuffers_800C14E0[i][1] = gMtsPadRecvBuffers_800C1480[i][3] | (gMtsPadRecvBuffers_800C1480[i][2] << 8);
                break;
            }
        }

        gMtsPadUnknBuffers_800C14E0[i][0] = type;

        if (dword_800A3DC0[i] != 0)
        {
            if (gMtsPadInitStates_800C14F0[i] == 2)
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 64;
                gMtsPadSendBuffers_800C14D0[i][1] = 1;
            }
            else
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 1;
            }

            if (dword_800A3DC0[i] > 0)
            {
                dword_800A3DC0[i]--;
            }
        }
        else if (gMtsPadInitStates_800C14F0[i] == 2)
        {
            gMtsPadSendBuffers_800C14D0[i][0] = 0;
            gMtsPadSendBuffers_800C14D0[i][1] = 0;
        }
        else
        {
            gMtsPadSendBuffers_800C14D0[i][0] = 0;
        }
    }
}

void mts_init_controller_8008C098()
{
    if (gMtsPadInited_800A3DBC == 0)
    {
        PadInitDirect(gMtsPadRecvBuffers_800C1480[0], gMtsPadRecvBuffers_800C1480[1]);
        PadSetAct(0, gMtsPadSendBuffers_800C14D0[0], 8);
        PadSetAct(0x10, gMtsPadSendBuffers_800C14D0[1], 8);
        PadStartCom();
        gMtsPadInitStates_800C14F0[1] = 1;
        gMtsPadInitStates_800C14F0[0] = 1;
        mts_set_callback_controller_800893D8(mts_callback_controller_8008BDEC);
        gMtsPadInited_800A3DBC = 1;
    }
}

void mts_stop_controller_8008C12C()
{
    if (gMtsPadInited_800A3DBC != 0)
    {
        StopPAD();
        ChangeClearPAD(0);
        mts_set_callback_controller_800893D8(0);
        gMtsPadInited_800A3DBC = 0;
    }
}

int mts_get_pad_8008C170(int pad, MTS_PAD_DATA *pData)
{
    unsigned short v1;
    char  flag;

    if (pad == 0)
    {
        pad = 1;

        if (gMtsPadUnknBuffers_800C14E0[0][0] <= 0)
        {
            pad = 2;
        }
        else if (gMtsPadUnknBuffers_800C14E0[0][0] == 1)
        {
            v1 = gMtsPadUnknBuffers_800C14E0[0][1];

            if ((v1 == 0xffff) &&
                (gMtsPadUnknBuffers_800C14E0[1][0] != 0) &&
                (v1 != (unsigned short)gMtsPadUnknBuffers_800C14E0[1][1]))
            {
                pad = 2;
            }
        }
    }

    if (gMtsPadUnknBuffers_800C14E0[pad - 1][0] > 0)
    {
        pData->channel = pad;
        pData->button = ~gMtsPadUnknBuffers_800C14E0[pad - 1][1];
        flag = gMtsPadUnknBuffers_800C14E0[pad - 1][0];
        pData->flag = flag;

        if (flag >= 2)
        {
            *(unsigned int *)&pData->rx = *(unsigned int *)&gMtsPadUnknBuffers_800C14E0[pad - 1][2];
        }

        return 1;
    }

    pData->channel = -1;
    return 0;
}

int mts_read_pad_8008C25C(int pad)
{
    unsigned short buf;

    if (pad == 0)
    {
        if (gMtsPadUnknBuffers_800C14E0[0][0] != 0)
        {
            buf = gMtsPadUnknBuffers_800C14E0[0][1];

            if ((buf != 0xFFFF) ||
                (gMtsPadUnknBuffers_800C14E0[1][0] == 0) ||
                ((unsigned short)gMtsPadUnknBuffers_800C14E0[1][1] == buf))
            {
                return (unsigned short)~gMtsPadUnknBuffers_800C14E0[0][1];
            }
            else
            {
                return (unsigned short)~gMtsPadUnknBuffers_800C14E0[1][1];
            }
        }
        else if (gMtsPadUnknBuffers_800C14E0[1][0] != 0)
        {
            return (unsigned short)~gMtsPadUnknBuffers_800C14E0[1][1];
        }
        else
        {
            return 0;
        }
    }
    else if (gMtsPadUnknBuffers_800C14E0[pad - 1][0] != 0)
    {
        return (unsigned short)~gMtsPadUnknBuffers_800C14E0[pad - 1][1];
    }

    return 0;
}

long mts_PadRead_8008C324(int unused)
{
    int ret;

    ret = 0;

    if (gMtsPadUnknBuffers_800C14E0[0][0] != 0)
    {
        ret = ~(unsigned short)gMtsPadUnknBuffers_800C14E0[0][1] & 0xFFFF;
    }

    if (gMtsPadUnknBuffers_800C14E0[1][0] != 0)
    {
        ret |= ~(unsigned short)gMtsPadUnknBuffers_800C14E0[1][1] << 16;
    }

    return ret;
}

unsigned char * mts_get_controller_data_8008C380(int pad)
{
    int buffer;

    buffer = pad;
    if (pad == 0)
    {
        if (gMtsPadRecvBuffers_800C1480[0][0] == 0)
        {
            buffer = 1;
        }
        else
        {
            buffer = 2;
        }
    }

    return gMtsPadRecvBuffers_800C1480[buffer - 1];
}

int mts_control_vibration_8008C3BC(int arg0)
{
    int ret;

    ret = dword_800A3DC8;
    if (arg0 >= 0)
    {
        dword_800A3DC8 = arg0;
    }
    memset(gMtsPadSendBuffers_800C14D0, 0, sizeof(gMtsPadSendBuffers_800C14D0));
    return ret;
}

void mts_set_pad_vibration_8008C408(int pad, int enable)
{
    if (dword_800A3DC8 == 0)
    {
        return;
    }

    if (pad == 0)
    {
        pad = (gMtsPadRecvBuffers_800C1480[0][0] == 0) ? 1 : 2;
    }

    dword_800A3DC0[pad - 1] = enable;
}

void mts_set_pad_vibration2_8008C454(int pad, int enable)
{
    if (dword_800A3DC8 == 0)
    {
        return;
    }

    if (pad == 0)
    {
        pad = (gMtsPadRecvBuffers_800C1480[0][0] == 0) ? 1 : 2;
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == 3)
    {
        gMtsPadSendBuffers_800C14D0[pad - 1][1] = enable;
    }
}

int mts_get_pad_vibration_type_8008C4BC(int pad)
{
    if (pad == 0)
    {
        pad = (gMtsPadRecvBuffers_800C1480[0][0] == 0) ? 1 : 2;
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == 2)
    {
        return (gMtsPadUnknBuffers_800C14E0[pad - 1][0] == 3) ? 2 : 0;
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == 3)
    {
        return 1;
    }

    return -1;
}
