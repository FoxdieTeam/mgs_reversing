#include <libpad.h>
#include <libapi.h>
#include <memory.h>
#include "common.h"

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

// Amount of frames to vibrate for each pad
int vibration_count_800A3DC0[] = {0, 0};

// 0 = enabled, everything else = disabled
int vibration_enable_800A3DC8 = 1;

#define GET_ACTIVE_PAD_INDEX() (gMtsPadRecvBuffers_800C1480[0].success == 0 ? 1 : 2) // 0 = successful
#define PAD_1 0
#define PAD_2 1
/**
 * @brief Initialize actuator buffers for the controller by querying the
 * controller for function and subfunction information.
 * If the controller supports vibration, the actuator buffers are initialized.
 *
 * @param pad 0 first pad, 1 second pad
 */
void mts_init_controller_actuators_8008BC8C(int pad)
{
    int port;
    int actuators_count;
    int i;
    int func, subfunc, size;

    port = pad * 0x10;
    // Get the total number of actuators present in the controller
    actuators_count = PadInfoAct(port, -1, 0);

    // Clear the actuator buffers
    for (i = 0; i < 6; i++)
    {
        gMtsPadActBuffers_800C1470[pad][i] = 0xFF;
    }

    for (i = actuators_count - 1; i >= 0; i--)
    {
        func = PadInfoAct(port, i, InfoActFunc);
        subfunc = PadInfoAct(port, i, InfoActSub);
        // 0: 1 bit (ON/OFF only), 1 or greater: number of bytes
        size = PadInfoAct(port, i, InfoActSize);

        // if the function is not 1 (continuous-rotation vibration)
        if (func != 1)
        {
            continue;
        }

        // 1: low-speed rotation
        if (subfunc == 1 && size == 1)
        {
            gMtsPadActBuffers_800C1470[pad][1] = i;
            continue;
        }

        // 2: high-speed rotation
        if (subfunc == 2 && size == 0)
        {
            gMtsPadActBuffers_800C1470[pad][0] = i;
        }
    }
    // Set up the sequence to transmit actuator control data
    PadSetActAlign(port, gMtsPadActBuffers_800C1470[pad]);
}

void mts_callback_controller_8008BDEC(void)
{
    int i;
    int state;
    int capability;

    for (i = 0; i < 2; i++)
    {
        // Get the state for 0x00 (Port 1) and 0x10 (Port 2)
        // directly connected controllers. (LIBREF46.PDF, page 789)
        state = PadGetState(i * 0x10);
        capability = PAD_CAPABILITY_INACTIVE;

        // State machine to perform the discovery and initialization of the pads
        switch (state)
        {
        // if the pad is a dualshock controller
        case PadStateStable:
            // If the pad was previously detected, initialize the actuators
            // and set it to ready
            if (gMtsPadInitStates_800C14F0[i] == PAD_STATE_DETECTED)
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 0;
                gMtsPadSendBuffers_800C14D0[i][1] = 0;

                mts_init_controller_actuators_8008BC8C(i);

                gMtsPadInitStates_800C14F0[i] = PAD_STATE_ACTUATORS_READY;
                gMtsPadParsedRecvBuffers_800C14E0[i].capability = capability;
                continue;
            }

            break;

        // If the pad is a normal controller (not dualshock)
        case PadStateFindCTP1:
            gMtsPadInitStates_800C14F0[i] = PAD_STATE_IDENTIFIED;
            break;

        case PadStateFindPad:
            gMtsPadInitStates_800C14F0[i] = PAD_STATE_DETECTED;

        // otherwise continue
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

        if (vibration_count_800A3DC0[i] != 0)
        {
            if (gMtsPadInitStates_800C14F0[i] == PAD_STATE_IDENTIFIED)
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 64;
                gMtsPadSendBuffers_800C14D0[i][1] = 1;
            }
            else
            {
                gMtsPadSendBuffers_800C14D0[i][0] = 1;
            }

            if (vibration_count_800A3DC0[i] > 0)
            {
                vibration_count_800A3DC0[i]--;
            }
        }
        else if (gMtsPadInitStates_800C14F0[i] == PAD_STATE_IDENTIFIED)
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

/**
 * @brief Initializes the controller system.
 *
 * This function initializes the controllers if it has not been
 * initialized already, start the controller communication, and set up the
 * callback.
 */
void mts_init_controller_8008C098(void)
{
    if (gMtsPadInited_800A3DBC == 0)
    {
        //Initialize controller environment
        PadInitDirect((unsigned char *)&gMtsPadRecvBuffers_800C1480[0],
                      (unsigned char *)&gMtsPadRecvBuffers_800C1480[1]);
        // Set the transmit buffers for the actuators
        PadSetAct(0, gMtsPadSendBuffers_800C14D0[0], 8);
        PadSetAct(0x10, gMtsPadSendBuffers_800C14D0[1], 8);
        // Initate the controller communication
        PadStartCom();
        gMtsPadInitStates_800C14F0[1] = PAD_STATE_DETECTED;
        gMtsPadInitStates_800C14F0[0] = PAD_STATE_DETECTED;
        mts_set_callback_controller_800893D8(mts_callback_controller_8008BDEC);
        gMtsPadInited_800A3DBC = 1;
    }
}

/**
 * @brief Stops the controller system if it has been initialized.
 */
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

        if (gMtsPadParsedRecvBuffers_800C14E0[PAD_1].capability <= PAD_CAPABILITY_INACTIVE)
        {
            pad = 2;
        }
        else if (gMtsPadParsedRecvBuffers_800C14E0[PAD_1].capability == PAD_CAPABILITY_16_BUTTON)
        {
            if (gMtsPadParsedRecvBuffers_800C14E0[PAD_1].buttons_state == BUTTON_STATE_NOTHING_PRESSED &&
                gMtsPadParsedRecvBuffers_800C14E0[PAD_2].capability != PAD_CAPABILITY_INACTIVE &&
                gMtsPadParsedRecvBuffers_800C14E0[PAD_2].buttons_state != BUTTON_STATE_NOTHING_PRESSED)
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

/**
 * @brief Return the button state of a controller.
 *
 * @param pad 1 or 2 for a specific gamepad or 0 for the active one.
 * @return int the button state.
 */
int mts_read_pad_8008C25C(int pad)
{
    // If the pad is not specified, get the active pad
    if (pad == 0)
    {
        // The first pad is available
        if (gMtsPadParsedRecvBuffers_800C14E0[PAD_1].capability != PAD_CAPABILITY_INACTIVE)
        {
            if (gMtsPadParsedRecvBuffers_800C14E0[PAD_1].buttons_state != BUTTON_STATE_NOTHING_PRESSED ||
                gMtsPadParsedRecvBuffers_800C14E0[PAD_2].capability == PAD_CAPABILITY_INACTIVE ||
                gMtsPadParsedRecvBuffers_800C14E0[PAD_2].buttons_state == BUTTON_STATE_NOTHING_PRESSED)
            {
                return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[PAD_1].buttons_state;
            }
            else
            {
                return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[PAD_2].buttons_state;
            }
        }
        // The second pad is active
        else if (gMtsPadParsedRecvBuffers_800C14E0[PAD_2].capability != PAD_CAPABILITY_INACTIVE)
        {
            return (unsigned short)~gMtsPadParsedRecvBuffers_800C14E0[PAD_2].buttons_state;
        }

        return 0;
    }
    // Return the button state for the specified pad
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

    if (gMtsPadParsedRecvBuffers_800C14E0[PAD_1].capability != PAD_CAPABILITY_INACTIVE)
    {
        ret = ~gMtsPadParsedRecvBuffers_800C14E0[PAD_1].buttons_state & 0xFFFF;
    }

    if (gMtsPadParsedRecvBuffers_800C14E0[PAD_2].capability != PAD_CAPABILITY_INACTIVE)
    {
        ret |= ~gMtsPadParsedRecvBuffers_800C14E0[PAD_2].buttons_state << 0x10;
    }

    return ret;
}

/**
 * @brief Return the receive buffer for a specific controller.
 *
 * @param pad 0 for the active pad, 1 for the first pad, 2 for the second.
 * @return PadReceiveBuffer* the receive buffer.
 */
PadReceiveBuffer *mts_get_pad_receive_buffer_8008C380(int pad)
{
    if (pad == 0)
    {
        pad = GET_ACTIVE_PAD_INDEX();
    }

    return &gMtsPadRecvBuffers_800C1480[pad - 1];
}

/**
 * @brief Set the vibration enable flag.
 *
 * @param arg0 0 to disable vibration, else to enable.
 * @return int the previous vibration enable flag.
 */
int mts_control_vibration_8008C3BC(int enable)
{
    int ret;

    ret = vibration_enable_800A3DC8;
    if (enable >= 0)
    {
        vibration_enable_800A3DC8 = enable;
    }
    // Clear the vibration buffers
    memset(gMtsPadSendBuffers_800C14D0, 0, sizeof(gMtsPadSendBuffers_800C14D0));
    return ret;
}

/**
 * @brief Set the number of frames to vibrate for a specific controller.
 *
 * @param pad 0 for the active pad, 1 for the first pad, 2 for the second.
 * @param duration the number of frames to vibrate.
 */
void mts_set_pad_vibration_8008C408(int pad, int duration)
{
    if (vibration_enable_800A3DC8 == 0)
    {
        return;
    }

    if (pad == 0)
    {
        pad = GET_ACTIVE_PAD_INDEX();
    }

    vibration_count_800A3DC0[pad - 1] = duration;
}

/**
 * @brief Set the vibration level for a specific controller.
 *
 * @param pad 0 for the active pad, 1 for the first pad, 2 for the second.
 * @param level the vibration level (0 to 255).
 */
void mts_set_pad_vibration2_8008C454(int pad, int level)
{
    if (vibration_enable_800A3DC8 == 0)
    {
        return;
    }

    if (pad == 0)
    {
        pad = GET_ACTIVE_PAD_INDEX();
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == PAD_STATE_ACTUATORS_READY)
    {
        gMtsPadSendBuffers_800C14D0[pad - 1][1] = level;
    }
}

/**
 * @brief Get the vibration type for a specific controller.
 *
 * @param pad 0 for the active pad, 1 for the first pad, 2 for the second.
 * @return int the vibration type.
 */
int mts_get_pad_vibration_type_8008C4BC(int pad)
{
    if (pad == 0)
    {
        pad = GET_ACTIVE_PAD_INDEX();
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == PAD_STATE_IDENTIFIED)
    {
        return gMtsPadParsedRecvBuffers_800C14E0[pad - 1].capability == PAD_CAPABILITY_ANALOG_CONTROLLER ? 2 : 0;
    }

    if (gMtsPadInitStates_800C14F0[pad - 1] == PAD_STATE_ACTUATORS_READY)
    {
        return 1;
    }

    return -1;
}
