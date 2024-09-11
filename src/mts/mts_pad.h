#ifndef _MTS_PAD_H
#define _MTS_PAD_H

#include "mts.h"

#define MTS_PAD_INACTIVE    0
//#define MTS_PAD_DIGITAL   1
//#define MTS_PAD_ANAJOY    2
//#define MTS_PAD_ANALOG    3

// states for MTS init pad state machine
enum {
    PAD_STATE_UNDETECTED = 0,
    PAD_STATE_DETECTED = 1,
    PAD_STATE_IDENTIFIED = 2,
    PAD_STATE_ACTUATORS_READY = 3,
};

/* mts_pad.c (private) */
void mts_stop_controller(void);
long mts_PadRead(int unused);
int mts_control_vibration(int enable);

#endif // _MTS_PAD_H
