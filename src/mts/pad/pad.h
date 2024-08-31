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

void mts_set_pad_vibration_8008C408(int pad, int enable);
void mts_set_pad_vibration2_8008C454(int pad, int enable);
int  mts_get_pad_8008C170(int pad, MTS_PAD_DATA *pData);
long mts_PadRead_8008C324(int unused);
int  mts_read_pad_8008C25C(int pad);
int  mts_get_pad_vibration_type_8008C4BC(int pad);

#endif // _MTS_PAD_H
