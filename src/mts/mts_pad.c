#include <memory.h>
#include <sys/types.h>
#include <libapi.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpad.h>
#include "common.h"

#include "mts_pad.h"
#include "receive_buffer.h"
#include "mts_new.h"

/*---------------------------------------------------------------------------*/
// extern BSS

extern PadReceiveBuffer         padbuf_800C1480[2];
extern unsigned char            sendbuf_800C14D0[2][8];
extern PadParsedReceiveBuffer   pad_800C14E0[2];
extern int                      pad_state_800C14F0[2];

/*---------------------------------------------------------------------------*/

STATIC int pad_init_flag = 0;

// Amount of frames to vibrate for each pad
STATIC int vibration_count[] = {0, 0};

// 0 = disabled
STATIC int vibration_enable = 1;

#define GET_ACTIVE_PAD_INDEX() \
    (padbuf_800C1480[0].success == 0 ? 1 : 2) // 0 = successful

#define PAD_1 0
#define PAD_2 1

/**
 * @brief   Initialize actuator buffers for the controller by querying the
 *          controller for function and subfunction information.
 *
 * If the controller supports vibration, the actuator buffers are initialized.
 *
 * @param   channel     0: first pad, 1: second pad
 */
STATIC void init_expand_pad( int channel )
{
    int port;
    int actuators_count;
    int i;
    int func, subfunc, size;

    extern char param_800C1470[2][6]; // "param.2" (in 5thMix)

    port = channel * 0x10;
    // Get the total number of actuators present in the controller
    actuators_count = PadInfoAct(port, -1, 0);

    // Clear the actuator buffers
    for (i = 0; i < 6; i++)
    {
        param_800C1470[channel][i] = 0xFF;
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
            param_800C1470[channel][1] = i;
            continue;
        }

        // 2: high-speed rotation
        if (subfunc == 2 && size == 0)
        {
            param_800C1470[channel][0] = i;
        }
    }
    // Set up the sequence to transmit actuator control data
    PadSetActAlign(port, param_800C1470[channel]);
}

STATIC void do_control( void )
{
    int i;
    int state;
    int capability;

    for (i = 0; i < 2; i++)
    {
        // Get the state for 0x00 (Port 1) and 0x10 (Port 2)
        // directly connected controllers. (LIBREF46.PDF, page 789)
        state = PadGetState(i * 0x10);
        capability = MTS_PAD_INACTIVE;

        // State machine to perform the discovery and initialization of the pads
        switch (state)
        {
        // if the pad is a DualShock controller
        case PadStateStable:
            // If the pad was previously detected, initialize the actuators
            // and set it to ready
            if (pad_state_800C14F0[i] == PAD_STATE_DETECTED)
            {
                sendbuf_800C14D0[i][0] = 0;
                sendbuf_800C14D0[i][1] = 0;

                init_expand_pad(i);

                pad_state_800C14F0[i] = PAD_STATE_ACTUATORS_READY;
                pad_800C14E0[i].capability = capability;
                continue;
            }

            break;

        // If the pad is a normal controller (not DualShock)
        case PadStateFindCTP1:
            pad_state_800C14F0[i] = PAD_STATE_IDENTIFIED;
            break;

        case PadStateFindPad:
            pad_state_800C14F0[i] = PAD_STATE_DETECTED;

        // otherwise continue
        default:
            pad_800C14E0[i].capability = capability;
            continue;
        }

        if (padbuf_800C1480[i].success == 0) // 0 = successful
        {
            switch (PAD_RECEIVE_BUFFER_GET_TERMINAL_TYPE(&padbuf_800C1480[i]))
            {
            case TERMINAL_TYPE_ANALOG_CONTROLLER:
                capability++; // MTS_PAD_ANALOG

            // You can add support for a mouse by adding this here:
            // case TERMINAL_TYPE_MOUSE:

            case TERMINAL_TYPE_ANALOG_JOYSTICK:
                capability++; // MTS_PAD_ANAJOY

                LCOPY(&padbuf_800C1480[i].terminal_data.analog_joystick.right_stick_x,
                      &pad_800C14E0[i].right_stick_x);

            case TERMINAL_TYPE_16_BUTTON:
                capability++; // MTS_PAD_DIGITAL

                pad_800C14E0[i].buttons_state =
                    padbuf_800C1480[i].terminal_data.sixteen_button_analog.button_state_left << 8 |
                    padbuf_800C1480[i].terminal_data.sixteen_button_analog.button_state_right;
                break;
            }
        }

        pad_800C14E0[i].capability = capability;

        if (vibration_count[i] != 0)
        {
            if (pad_state_800C14F0[i] == PAD_STATE_IDENTIFIED)
            {
                sendbuf_800C14D0[i][0] = 64;
                sendbuf_800C14D0[i][1] = 1;
            }
            else
            {
                sendbuf_800C14D0[i][0] = 1;
            }

            if (vibration_count[i] > 0)
            {
                vibration_count[i]--;
            }
        }
        else if (pad_state_800C14F0[i] == PAD_STATE_IDENTIFIED)
        {
            sendbuf_800C14D0[i][0] = 0;
            sendbuf_800C14D0[i][1] = 0;
        }
        else
        {
            sendbuf_800C14D0[i][0] = 0;
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
void mts_init_controller( void )
{
    if (pad_init_flag == 0)
    {
        //Initialize controller environment
        PadInitDirect((unsigned char *)&padbuf_800C1480[0],
                      (unsigned char *)&padbuf_800C1480[1]);
        // Set the transmit buffers for the actuators
        PadSetAct(0, sendbuf_800C14D0[0], 8);
        PadSetAct(0x10, sendbuf_800C14D0[1], 8);
        // Initate the controller communication
        PadStartCom();
        pad_state_800C14F0[1] = PAD_STATE_DETECTED;
        pad_state_800C14F0[0] = PAD_STATE_DETECTED;
        mts_set_vsync_control_func(do_control);
        pad_init_flag = 1;
    }
}

/**
 * @brief Stops the controller system if it has been initialized.
 */
void mts_stop_controller( void )
{
    if (pad_init_flag != 0)
    {
        StopPAD();
        ChangeClearPAD(0);
        mts_set_vsync_control_func(NULL);
        pad_init_flag = 0;
    }
}

int mts_get_pad( int channel, MTS_PAD *pad )
{
    char capability;

    if (channel == 0)
    {
        channel = 1;

        if (pad_800C14E0[PAD_1].capability <= MTS_PAD_INACTIVE)
        {
            channel = 2;
        }
        else if (pad_800C14E0[PAD_1].capability == MTS_PAD_DIGITAL)
        {
            if (pad_800C14E0[PAD_1].buttons_state == BUTTON_STATE_NOTHING_PRESSED &&
                pad_800C14E0[PAD_2].capability != MTS_PAD_INACTIVE &&
                pad_800C14E0[PAD_2].buttons_state != BUTTON_STATE_NOTHING_PRESSED)
            {
                channel = 2;
            }
        }
    }

    if (pad_800C14E0[channel - 1].capability > MTS_PAD_INACTIVE)
    {
        pad->channel = channel;
        pad->button = ~pad_800C14E0[channel - 1].buttons_state;

        capability = pad_800C14E0[channel - 1].capability;
        pad->capability = capability;
        if (capability >= MTS_PAD_ANAJOY)
        {
            LCOPY(&pad_800C14E0[channel - 1].right_stick_x, &pad->rx);
        }

        return 1;
    }

    pad->channel = -1;
    return 0;
}

/**
 * @brief Return the button state of a controller.
 *
 * @param channel 1 or 2 for a specific gamepad or 0 for the active one.
 * @return int the button state.
 */
int mts_read_pad( int channel )
{
    // If the pad is not specified, get the active pad
    if (channel == 0)
    {
        // The first pad is available
        if (pad_800C14E0[PAD_1].capability != MTS_PAD_INACTIVE)
        {
            if (pad_800C14E0[PAD_1].buttons_state != BUTTON_STATE_NOTHING_PRESSED ||
                pad_800C14E0[PAD_2].capability == MTS_PAD_INACTIVE ||
                pad_800C14E0[PAD_2].buttons_state == BUTTON_STATE_NOTHING_PRESSED)
            {
                return (unsigned short)~pad_800C14E0[PAD_1].buttons_state;
            }
            else
            {
                return (unsigned short)~pad_800C14E0[PAD_2].buttons_state;
            }
        }
        // The second pad is active
        else if (pad_800C14E0[PAD_2].capability != MTS_PAD_INACTIVE)
        {
            return (unsigned short)~pad_800C14E0[PAD_2].buttons_state;
        }

        return 0;
    }
    // Return the button state for the specified pad
    if (pad_800C14E0[channel - 1].capability != MTS_PAD_INACTIVE)
    {
        return (unsigned short)~pad_800C14E0[channel - 1].buttons_state;
    }

    return 0;
}

long mts_PadRead( int unused )
{
    int ret;

    ret = 0;

    if (pad_800C14E0[PAD_1].capability != MTS_PAD_INACTIVE)
    {
        ret = ~pad_800C14E0[PAD_1].buttons_state & 0xFFFF;
    }

    if (pad_800C14E0[PAD_2].capability != MTS_PAD_INACTIVE)
    {
        ret |= ~pad_800C14E0[PAD_2].buttons_state << 0x10;
    }

    return ret;
}

/**
 * @brief Return the receive buffer for a specific controller.
 *
 * @param   channel     0 for the active pad, 1 for the first pad,
 *                      2 for the second.
 *
 * @return  PadReceiveBuffer*   the receive buffer.
 */
PadReceiveBuffer *mts_get_pad_receive_buffer( int channel )
{
    if (channel == 0)
    {
        channel = GET_ACTIVE_PAD_INDEX();
    }

    return &padbuf_800C1480[channel - 1];
}

/**
 * @brief Set the vibration enable flag.
 *
 * @param   enable      0 to disable vibration, >= 1 to enable.
 * @return  int         the previous vibration enable flag.
 */
int mts_control_vibration( int enable )
{
    int old;

    old = vibration_enable;
    if (enable >= 0)
    {
        vibration_enable = enable;
    }
    // Clear the vibration buffers
    memset(sendbuf_800C14D0, 0, sizeof(sendbuf_800C14D0));
    return old;
}

/**
 * @brief Set the number of frames to vibrate for a specific controller.
 *
 * @param   channel     0 for the active pad, 1 for the first pad,
 *                      2 for the second.
 * @param   time        the number of frames to vibrate.
 */
void mts_set_pad_vibration( int channel, int time )
{
    if (vibration_enable == 0)
    {
        return;
    }

    if (channel == 0)
    {
        channel = GET_ACTIVE_PAD_INDEX();
    }

    vibration_count[channel - 1] = time;
}

/**
 * @brief Set the vibration level for a specific controller.
 *
 * @param   channel     0 for the active pad, 1 for the first pad,
 *                      2 for the second.
 * @param   value       the vibration level (0 to 255).
 */
void mts_set_pad_vibration2( int channel, int value )
{
    if (vibration_enable == 0)
    {
        return;
    }

    if (channel == 0)
    {
        channel = GET_ACTIVE_PAD_INDEX();
    }

    if (pad_state_800C14F0[channel - 1] == PAD_STATE_ACTUATORS_READY)
    {
        sendbuf_800C14D0[channel - 1][1] = value;
    }
}

/**
 * @brief Get the vibration type for a specific controller.
 *
 * @param   channel     0 for the active pad, 1 for the first pad,
 *                      2 for the second.
 *
 * @return  int         the vibration type.
 */
int mts_get_pad_vibration_type( int channel )
{
    if (channel == 0)
    {
        channel = GET_ACTIVE_PAD_INDEX();
    }

    if (pad_state_800C14F0[channel - 1] == PAD_STATE_IDENTIFIED)
    {
        return pad_800C14E0[channel - 1].capability == MTS_PAD_ANALOG ? 2 : 0;
    }

    if (pad_state_800C14F0[channel - 1] == PAD_STATE_ACTUATORS_READY)
    {
        return 1;
    }

    return -1;
}

/*---------------------------------------------------------------------------*/

STATIC int graph_reset_flag = 0;

void mts_reset_graph(void)
{
    if (graph_reset_flag == 0)
    {
        ResetGraph(0);
        SetGraphDebug(0);
        InitGeom();
        graph_reset_flag = 1;
    }
    else
    {
        ResetGraph(1);
    }
}
