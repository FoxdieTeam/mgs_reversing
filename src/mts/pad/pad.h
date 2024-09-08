#ifndef _MTS_PAD_H
#define _MTS_PAD_H

typedef struct MTS_PAD_DATA
{
    signed char    channel;
    char           capability; // See PAD_CAPABILITY_* enum
    unsigned short button;
    unsigned char  rx;
    unsigned char  ry;
    unsigned char  lx;
    unsigned char  ly;
} MTS_PAD_DATA;

enum
{
    PAD_CAPABILITY_INACTIVE = 0,
    PAD_CAPABILITY_16_BUTTON = 1,
    PAD_CAPABILITY_JOYSTICK = 2,
    PAD_CAPABILITY_ANALOG_CONTROLLER = 3,
};

// states for MTS init pad state machine
enum {
    PAD_STATE_UNDETECTED = 0,
    PAD_STATE_DETECTED = 1,
    PAD_STATE_IDENTIFIED = 2,
    PAD_STATE_ACTUATORS_READY = 3,
};

/* pad.c */
void mts_init_controller_actuators(int pad);
void mts_callback_controller(void);
void mts_init_controller(void);
void mts_stop_controller(void);
int  mts_get_pad(int pad, MTS_PAD_DATA *pData);
int  mts_read_pad(int pad);
long mts_PadRead(int unused);

int  mts_control_vibration(int enable);
void mts_set_pad_vibration(int pad, int enable);
void mts_set_pad_vibration2(int pad, int enable);
int  mts_get_pad_vibration_type(int pad);

#endif // _MTS_PAD_H
