#ifndef _CDBIOS_H_
#define _CDBIOS_H_

struct _CDBIOS_TASK;
typedef int (*cdbios_task_pfn)(struct _CDBIOS_TASK *);

typedef struct _CDBIOS_TASK {
    int field_0_state;
    int field_4_sector;
    void *field_8_buffer;
    int field_C;
    int field_10_ticks;
    int field_14_sectors_delivered;
    int field_18_size;
    int field_1C_remaining;
    cdbios_task_pfn field_20_callback;
} CDBIOS_TASK;

enum CDBIOS_STATE {
    CDBIOS_STATE_INVALID = -1,
    CDBIOS_STATE_IDLE,
    CDBIOS_STATE_START,
    CDBIOS_STATE_READ,
    CDBIOS_STATE_ERROR,
};

#endif // _CDBIOS_H_
