#include <LIBPAD.H>
#include <LIBAPI.H>
#include <MEMORY.H>

#include "pad.h"
#include "receive_buffer.h"

#include "mts/mts_new.h"
#include "libdg/libdg.h"

// BSS
extern char gMtsPadActBuffers_800C1470[2][6];

extern PadReceiveBuffer       gMtsPadRecvBuffers_800C1480[2];
extern PadParsedReceiveBuffer gMtsPadParsedRecvBuffers_800C14E0[2];

extern unsigned char gMtsPadSendBuffers_800C14D0[2][8];
extern int           gMtsPadInitStates_800C14F0[2];

int gMtsSioUnlocked_800A3DB0 = 1;
int dword_800A3DB4 = 0;
int dword_800A3DB8 = 0;
int gMtsPadInited_800A3DBC = 0;
int dword_800A3DC0[] = {0, 0};
int dword_800A3DC8 = 1;

#define GET_ACTIVE_PAD_INDEX() (gMtsPadRecvBuffers_800C1480[0].success == 0 ? 1 : 2) // 0 = successful

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

        if (subfunc == 1 && size == 1)
        {
            gMtsPadActBuffers_800C1470[pad][1] = i;
            continue;
        }

        if (subfunc == 2 && size == 0)
        {
            gMtsPadActBuffers_800C1470[pad][0] = i;
        }
    }

    PadSetActAlign(port, gMtsPadActBuffers_800C1470[pad]);
}

void mts_callback_controller_8008BDEC(void)
{
    int i;
    int state;
    int capability;

    for (i = 0; i < 2; i++)
    {
        state = PadGetState(i * 16);
        capability = PAD_CAPABILITY_INACTIVE;

        switch (state)
        {
        case 6:
            if (gMtsPadInitStates_800C14F0[i] == 1)
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 0;
                gMtsPadSendBuffers_800C14D0[i][1] = 0;

                mts_init_controller_actuators_8008BC8C(i);

                gMtsPadInitStates_800C14F0[i] = 3;
                gMtsPadParsedRecvBuffers_800C14E0[i].capability = capability;
                continue;
            }

            break;

        case 2:
            gMtsPadInitStates_800C14F0[i] = 2;
            break;

        case 1:
            gMtsPadInitStates_800C14F0[i] = 1;

        default:
            gMtsPadParsedRecvBuffers_800C14E0[i].capability = capability;
            continue;
        }

        if (gMtsPadRecvBuffers_800C1480[i].success == 0) // 0 = successful
        {
            switch (PAD_RECEIVE_BUFFER_GET_TERMINAL_TYPE(&gMtsPadRecvBuffers_800C1480[i]))
            {
            case TERMINAL_TYPE_ANALOG_CONTROLLER:
                capability++; // PAD_CAPABILITY_ANALOG_CONTROLLER

            // You can add support for a mouse by adding this here:
            // case TERMINAL_TYPE_MOUSE:

            case TERMINAL_TYPE_ANALOG_JOYSTICK:
                capability++; // PAD_CAPABILITY_JOYSTICK

                LCOPY(&gMtsPadRecvBuffers_800C1480[i].terminal_data.analog_joystick.right_stick_x,
                      &gMtsPadParsedRecvBuffers_800C14E0[i].right_stick_x);

            case TERMINAL_TYPE_16_BUTTON:
                capability++; // PAD_CAPABILITY_16_BUTTON

                gMtsPadParsedRecvBuffers_800C14E0[i].buttons_state =
                    gMtsPadRecvBuffers_800C1480[i].terminal_data.sixteen_button_analog.button_state_left << 8 |
                    gMtsPadRecvBuffers_800C1480[i].terminal_data.sixteen_button_analog.button_state_right;
                break;
            }
        }

        gMtsPadParsedRecvBuffers_800C14E0[i].capability = capability;

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

void mts_init_controller_8008C098(void)
{
    if (gMtsPadInited_800A3DBC == 0)
    {
        PadInitDirect((unsigned char *)&gMtsPadRecvBuffers_800C1480[0],
                      (unsigned char *)&gMtsPadRecvBuffers_800C1480[1]);
        PadSetAct(0, gMtsPadSendBuffers_800C14D0[0], 8);
        PadSetAct(0x10, gMtsPadSendBuffers_800C14D0[1], 8);
        PadStartCom();
        gMtsPadInitStates_800C14F0[1] = 1;
        gMtsPadInitStates_800C14F0[0] = 1;
        mts_set_callback_controller_800893D8(mts_callback_controller_8008BDEC);
        gMtsPadInited_800A3DBC = 1;
    }
}

void mts_stop_controller_8008C12C(void)
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
    char capability;

    if (pad == 0)
    {
        pad = 1;

        if (gMtsPadParsedRecvBuffers_800C14E0[0].capability <= PAD_CAPABILITY_INACTIVE)
        {
            pad = 2;
        }
        else if (gMtsPadParsedRecvBuffers_800C14E0[0].capability == PAD_CAPABILITY_16_BUTTON)
        {
            if (gMtsPadParsedRecvBuffers_800C14E0[0].buttons_state == BUTTON_STATE_NOTHING_PRESSED &&
                gMtsPadParsedRecvBuffers_800C14E0[1].capability != PAD_CAPABILITY_INACTIVE &&
                gMtsPadParsedRecvBuffers_800C14E0[1].buttons_state != BUTTON_STATE_NOTHING_PRESSED)
            {
                pad = 2;
            }
        }
    }

    if (gMtsPadParsedRecvBuffers_800C14E0[pad - 1].capability > PAD_CAPABILITY_INACTIVE)
    {
        pData->channel = pad;
        pData->button = ~gMtsPadParsedRecvBuffers_800C14E0[pad - 1].buttons_state;

        capability = gMtsPadParsedRecvBuffers_800C14E0[pad - 1].capability;
        pData->capability = capability;
        if (capability >= PAD_CAPABILITY_JOYSTICK)
        {
            LCOPY(&gMtsPadParsedRecvBuffers_800C14E0[pad - 1].right_stick_x, &pData->rx);
        }

        return 1;
    }

    pData->channel = -1;
    return 0;
}

int mts_read_pad_8008C25C(int pad)
{
    if (pad == 0)
    {
        if (gMtsPadParsedRecvBuffers_800C14E0[0].capability != PAD_CAPABILITY_INACTIVE)
        {
            if (gMtsPadParsedRecvBuffers_800C14E0[0].buttons_state != BUTTON_STATE_NOTHING_PRESSED ||
                gMtsPadParsedRecvBuffers_800C14E0[1].capability == PAD_CAPABILITY_INACTIVE ||
                gMtsPadParsedRecvBuffers_800C14E0[1].buttons_state == BUTTON_STATE_NOTHING_PRESSED)
            {
                return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[0].buttons_state;
            }
            else
            {
                return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[1].buttons_state;
            }
        }
        else if (gMtsPadParsedRecvBuffers_800C14E0[1].capability != PAD_CAPABILITY_INACTIVE)
        {
            return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[1].buttons_state;
        }

        return 0;
    }

    if (gMtsPadParsedRecvBuffers_800C14E0[pad - 1].capability != PAD_CAPABILITY_INACTIVE)
    {
        return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[pad - 1].buttons_state;
    }

    return 0;
}

long mts_PadRead_8008C324(int unused)
{
    int ret;

    ret = 0;

    if (gMtsPadParsedRecvBuffers_800C14E0[0].capability != PAD_CAPABILITY_INACTIVE)
    {
        ret = ~gMtsPadParsedRecvBuffers_800C14E0[0].buttons_state & 0xFFFF;
    }

    if (gMtsPadParsedRecvBuffers_800C14E0[1].capability != PAD_CAPABILITY_INACTIVE)
    {
        ret |= ~gMtsPadParsedRecvBuffers_800C14E0[1].buttons_state << 16;
    }

    return ret;
}

PadReceiveBuffer *mts_get_pad_receive_buffer_8008C380(int pad)
{
    if (pad == 0)
    {
        pad = GET_ACTIVE_PAD_INDEX();
    }

    return &gMtsPadRecvBuffers_800C1480[pad - 1];
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
        pad = GET_ACTIVE_PAD_INDEX();
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
        pad = GET_ACTIVE_PAD_INDEX();
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
        pad = GET_ACTIVE_PAD_INDEX();
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == 2)
    {
        return gMtsPadParsedRecvBuffers_800C14E0[pad - 1].capability == PAD_CAPABILITY_ANALOG_CONTROLLER ? 2 : 0;
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == 3)
    {
        return 1;
    }

    return -1;
}
