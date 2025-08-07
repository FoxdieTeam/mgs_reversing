#ifndef __TERMINAL_H__
#define __TERMINAL_H__

// "Table 13-3: Terminal Types"
// from Run-Time Library Overview 4.4, Chapter 13
// +---------------+-------------------+-------------------------+
// | Terminal Type   Controller Name     Model Number            |
// | 1               Mouse               SCPH-1030               |
// | 2               16-button analog    SLPH-00001 (Namco Ltd)  |
// | 3               Gun controller      SLPH-00014 (Konami Ltd) |
// | 4               16-button           SCPH-1080,1150,1200     |
// | 5               Analog joystick     SCPH-1110               |
// | 6               Gun controller      SLPH-00034 (Namco Ltd)  |
// | 7               Analog Controller   SCPH-1150,1200          |
// | 8               Multi Tap           SCPH-1070               |
// +---------------+-------------------+-------------------------+

enum {
    TERMINAL_TYPE_MOUSE         = 1,    // SCPH-1030
    TERMINAL_TYPE_NEGCON        = 2,    // SLPH-00001 (Namco Ltd)
    TERMINAL_TYPE_KONAMI_GUN    = 3,    // SLPH-00014 (Konami Ltd)
    TERMINAL_TYPE_DIGITAL       = 4,    // SCPH-1080,1150,1200
    TERMINAL_TYPE_ANAJOY        = 5,    // SCPH-1110
    TERMINAL_TYPE_NAMCO_GUN     = 6,    // SLPH-00034 (Namco Ltd)
    TERMINAL_TYPE_ANALOG        = 7,    // SCPH-1150,1200
    TERMINAL_TYPE_MULTITAP      = 8,    // SCPH-1070
};

// Terminal Type: Mouse
// +--------+----------------------------------------------------+
// | Offset   Contents                                           |
// | 0        0x00 = successful, other values = failure          |
// | 1        Upper four bits: 0x1                               |
// |          Lower four bits: (Byte count of received data) / 2 |
// | 2,3      Button state 1: released, 0: pressed               |
// | 4        Displacement along the X axis (-128 to 127)        |
// | 5        Displacement along the Y axis (-128 to 127)        |
// +--------+----------------------------------------------------+

typedef struct {
    unsigned char button_hi;
    unsigned char button_lo;
    unsigned char dx;
    unsigned char dy;
} RECV_DATA_MOUSE;

// Terminal Type: 16 Button Analog
// +--------+----------------------------------------------------+
// | Offset   Contents                                           |
// | 0        0x00 = successful, other values = failure          |
// | 1        Upper four bits: 0x2                               |
// |          Lower four bits: (Byte count of received data) / 2 |
// | 2,3      Button state 1: released, 0: pressed               |
// | 4        Rotation, 0 to 128 to 255                          |
// | 5        I button, 0 to 255                                 |
// | 6        II button, 0 to 255                                |
// | 7        L button, 0 to 255                                 |
// +--------+----------------------------------------------------+

typedef struct {
    unsigned char button_hi;
    unsigned char button_lo;
    unsigned char rotation;
    unsigned char i_button;
    unsigned char ii_button;
    unsigned char l_button;
} RECV_DATA_NEGCON;

// Terminal Type: Gun Controller (Konami)
// +--------+----------------------------------------------------+
// | Offset   Contents                                           |
// | 0        0x00 = successful, other values = failure          |
// | 1        Upper four bits: 0x3                               |
// |          Lower four bits: (Byte count of received data) / 2 |
// | 2,3      Button state 1: released, 0: pressed               |
// +--------+----------------------------------------------------+

typedef struct {
    unsigned char button_hi;
    unsigned char button_lo;
} RECV_DATA_KONAMI_GUN;

// Terminal Type: 16 Button
// +--------+----------------------------------------------------+
// | Offset   Contents                                           |
// | 0        0x00 = successful, other values = failure          |
// | 1        Upper four bits: 0x4                               |
// |          Lower four bits: (Byte count of received data) / 2 |
// | 2,3      Button state 1: released, 0: pressed               |
// +--------+----------------------------------------------------+

typedef struct {
    unsigned char button_hi;  // Table 13-11, buttons like LEFT/UP/...
    unsigned char button_lo; // Table 13-12, buttons like X/O/R1/...
} RECV_DATA_DIGITAL;

// Terminal Type: Analog Joystick
// +--------+----------------------------------------------------------+
// | Offset   Contents                                                 |
// | 0        0x00 = successful, other values = failure                |
// | 1        Upper four bits: 0x5                                     |
// |          Lower four bits: (Byte count of received data) / 2       |
// | 2,3      Button state, 1: released, 0: pressed                    |
// | 4        Position along the X axis (right stick), 0 to 128 to 255 |
// | 5        Position along the Y axis (right stick), 0 to 128 to 255 |
// | 6        Position along the X axis (left stick), 0 to 128 to 255  |
// | 7        Position along the Y axis (left stick), 0 to 128 to 255  |
// +--------+----------------------------------------------------------+

typedef struct {
    unsigned char button_hi;  // Table 13-11, buttons like LEFT/UP/...
    unsigned char button_lo; // Table 13-12, buttons like X/O/R1/...
    unsigned char rx;
    unsigned char ry;
    unsigned char lx;
    unsigned char ly;
} RECV_DATA_ANAJOY;

// Terminal Type: Gun Controller (Namco)
// +--------+----------------------------------------------------+
// | Offset   Contents                                           |
// | 0        0x00 = successful, other values = failure          |
// | 1        Upper four bits: 0x6                               |
// |          Lower four bits: (Byte count of received data) / 2 |
// | 2,3      Button state 1: released, 0: pressed               |
// | 4        Position along the X axis: Low-order byte          |
// | 5        Position along the X axis: High-order byte         |
// | 6        Position along the Y axis: Low-order byte          |
// | 7        Position along the Y axis: High-order byte         |
// +--------+----------------------------------------------------+

typedef struct {
    unsigned char button_hi;
    unsigned char button_lo;
    unsigned char x_axis_lo;
    unsigned char x_axis_hi;
    unsigned char y_axis_lo;
    unsigned char y_axis_hi;
} RECV_DATA_NAMCO_GUN;


// Terminal Type: Analog Controller
// +--------+----------------------------------------------------------+
// | Offset   Contents                                                 |
// | 0        0x00 = successful, other values = failure                |
// | 1        Upper four bits: 0x7                                     |
// |          Lower four bits: (Byte count of received data) / 2       |
// | 2,3      Button state, 1: released, 0: pressed                    |
// | 4        Position along the X axis (right stick), 0 to 128 to 255 |
// | 5        Position along the Y axis (right stick), 0 to 128 to 255 |
// | 6        Position along the X axis (left stick), 0 to 128 to 255  |
// | 7        Position along the Y axis (left stick), 0 to 128 to 255  |
// +--------+----------------------------------------------------------+

typedef struct {
    unsigned char button_hi;
    unsigned char button_lo;
    unsigned char rx;
    unsigned char ry;
    unsigned char lx;
    unsigned char ly;
} RECV_DATA_ANALOG;

// Terminal Type: Multitap
// +---------+--------+-------------------------------------------------------+
// | Offset             Contents                                              |
// | 0                  Receive result 0x00: successful, other values: failed |
// | 1                  0x80                                                  |
// | 2         Port A   Receive result 0x00: successful, other values: failed |
// | 3                  Upper four bits: Terminal type                        |
// |                    Lower four bits: (Byte count of received data) / 2    |
// | 4 - 9              Received data                                         |
// | 10        Port B   Receive result 0x00: successful, other values: failed |
// | 11                 Upper four bits: Terminal type                        |
// |                    Lower four bits: (Byte count of received data) / 2    |
// | 12 - 17            Received data                                         |
// | 18        Port C   Receive result 0x00: successful, other values: failed |
// | 19                 Upper four bits: Terminal type                        |
// |                    Lower four bits: (Byte count of received data) / 2    |
// | 20 - 25            Received data                                         |
// | 26        Port D   Receive result 0x00: successful, other values: failed |
// | 27                 Upper four bits: Terminal type                        |
// |                    Lower four bits: (Byte count of received data) / 2    |
// | 28 - 33            Received data                                         |
// +---------+--------+-------------------------------------------------------+

typedef struct {
    struct {
        unsigned char result;
        unsigned char type_size;
        unsigned char data[6];
    } port_a, port_b, port_c, port_d;
} RECV_DATA_MULTITAP;

// Button State Bit Assignments
// +-------------------------+--------------------------------+
// | Bit                       D15 D14 D13 D12 D11 D10 D9 D8  |
// | 16-button                 ←  ↓  →  ↑  ST         SEL |
// | Analog Controller         ←  ↓  →  ↑  ST  R3  L3 SEL |
// | Analog joystick           ←  ↓  →  ↑  ST         SEL |
// | 16-button analog          ←  ↓  →  ↑  ST             |
// | Mouse                                                    |
// | Gun controller (Konami)                   ST             |
// | Gun controller (Namco)                    A              |
// +-------------------------+--------------------------------+
//
// +-------------------------+---------------------------+
// | Bit                       D7  D6 D5  D4 D3 D2 D1 D0 |
// | 16-button                 □  × ○  △ R1 L1 R2 L2 |
// | Analog Controller         □  × ○  △ R1 L1 R2 L2 |
// | Analog joystick           □  × ○  △ R1 L1 R2 L2 |
// | 16-button analog                 A   B  R           |
// | Mouse                                   左 右       |
// | Gun controller (Konami)   TRG ○                    |
// | Gun controller (Namco)        B  TRG                |
// +-------------------------+---------------------------+
//
// (All bits 1: released, 0: pressed)

#define BUTTON_STATE_NOTHING_PRESSED 0xFFFF

typedef struct {
    // 0x00: successful, other values: failed
    unsigned char result;

    // The upper four bits indicate the terminal type (see TERMINAL_TYPE_* enum),
    // The lower four bits represent half the byte count of the data
    // received from the terminal (stored in the receive buffer starting at offset 3).
    unsigned char type_size;

    union {
        unsigned char           raw_data[34];
        RECV_DATA_MOUSE         mouse;      // 1
        RECV_DATA_NEGCON        negcon;     // 2
        RECV_DATA_KONAMI_GUN    konami_gun; // 3
        RECV_DATA_DIGITAL       digital;    // 4
        RECV_DATA_ANAJOY        anajoy;     // 5
        RECV_DATA_NAMCO_GUN     namco_gun;  // 6
        RECV_DATA_ANALOG        analog;     // 7
        RECV_DATA_MULTITAP      multitap;   // 8
    } data;
} PAD_RECV_BUF;

#endif // __TERMINAL_H__
