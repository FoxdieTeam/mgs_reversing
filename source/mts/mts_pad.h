#ifndef _MTS_PAD_H_
#define _MTS_PAD_H_

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

// Slightly altered MTS_PAD for internal use
typedef struct {
    short          flag;        // See MTS_PAD_* flags
    unsigned short button;      // Stores the button state (pressed or not pressed).
    unsigned char  rx;          // X axis position (right stick), 0 to 128 to 255
    unsigned char  ry;          // Y axis position (right stick), 0 to 128 to 255
    unsigned char  lx;          // X axis position (left stick), 0 to 128 to 255
    unsigned char  ly;          // Y axis position (left stick), 0 to 128 to 255
} MTS_PAD_IN;

/* mts_pad.c (private) */
void mts_stop_controller( void );
long mts_PadRead( int unused );
int mts_control_vibration( int enable );

#endif // _MTS_PAD_H_
