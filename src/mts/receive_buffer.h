#ifndef _PAD_RECEIVE_BUFFER_H
#define _PAD_RECEIVE_BUFFER_H

// Based on "Table 13-3: Terminal Types" from
// Run-Time Library Overview 4.4, chapter 13
enum
{
    TERMINAL_TYPE_MOUSE = 1,             // Mouse, SCPH-1030
    TERMINAL_TYPE_16_BUTTON_ANALOG = 2,  // 16-button analog, SLPH-00001 (Namco Ltd)
    TERMINAL_TYPE_GUN_CONTROLLER = 3,    // Gun controller, SLPH-00014 (Konami Ltd)
    TERMINAL_TYPE_16_BUTTON = 4,         // 16-button, SCPH-1080,1150,1200
    TERMINAL_TYPE_ANALOG_JOYSTICK = 5,   // Analog joystick, SCPH-1110
    TERMINAL_TYPE_GUN_CONTROLLER2 = 6,   // Gun controller, SLPH-00034 (Namco Ltd)
    TERMINAL_TYPE_ANALOG_CONTROLLER = 7, // Analog Controller, SCPH-1150,1200
    TERMINAL_TYPE_MULTI_TAP = 8,         // Multi Tap, SCPH-1070
};

// Based on "Table 13-7: Analog Joystick" from
// Run-Time Library Overview 4.4, chapter 13
//
// Offset Contents
// 2,3    Button state, 1: released, 0: pressed
// 4      Position along the X axis (right stick), 0 to 128 to 255
// 5      Position along the Y axis (right stick), 0 to 128 to 255
// 6      Position along the X axis (left stick), 0 to 128 to 255
// 7      Position along the Y axis (left stick), 0 to 128 to 255
typedef struct TerminalDataAnalogJoystick
{
    unsigned char button_state_left;  // Table 13-11, buttons like LEFT/UP/...
    unsigned char button_state_right; // Table 13-12, buttons like X/O/R1/...

    unsigned char right_stick_x; // Position along the X axis (right stick), 0 to 128 to 255
    unsigned char right_stick_y; // Position along the Y axis (right stick), 0 to 128 to 255
    unsigned char left_stick_x;  // Position along the X axis (left stick), 0 to 128 to 255
    unsigned char left_stick_y;  // Position along the Y axis (left stick), 0 to 128 to 255
} TerminalDataAnalogJoystick;

// Based on "Table 13-5: 16-button Analog" from
// Run-Time Library Overview 4.4, chapter 13
//
// Offset Contents
// 2,3    Button state, 1: released, 0: pressed
// 4      Rotation, 0 to 128 to 255
// 5      I button, 0 to 255
// 6      II button, 0 to 255
// 7      L button, 0 to 255
typedef struct TerminalData16ButtonAnalog
{
    unsigned char button_state_left;  // Table 13-11, buttons like LEFT/UP/...
    unsigned char button_state_right; // Table 13-12, buttons like X/O/R1/...

    unsigned char rotation;  // Rotation, 0 to 128 to 255
    unsigned char i_button;  // I button, 0 to 255
    unsigned char ii_button; // II button, 0 to 255
    unsigned char l_button;  // L button, 0 to 255
} TerminalData16ButtonAnalog;

#define BUTTON_STATE_NOTHING_PRESSED 0xFFFF

// Based on "Receive Buffer Data Format" from
// Run-Time Library Overview 4.4, chapter 13.
typedef struct PadReceiveBuffer
{
    // 0 = successful, other values = failure
    unsigned char success;

    // The upper four bits indicate the terminal type (see TERMINAL_TYPE_* enum),
    // The lower four bits represent half the byte count of the data
    // received from the terminal (stored in the receive buffer starting at offset 3).
    unsigned char terminal_type_and_size;

    union {
        TerminalDataAnalogJoystick analog_joystick;
        TerminalData16ButtonAnalog sixteen_button_analog;
        unsigned char              raw_data[34];
    } terminal_data;
} PadReceiveBuffer;

#endif // _PAD_RECEIVE_BUFFER_H
