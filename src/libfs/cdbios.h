#ifndef _CDBIOS_H_
#define _CDBIOS_H_

struct _CDBIOS_TASK;
typedef int (*cdbios_task_pfn)(struct _CDBIOS_TASK *);

typedef struct _CDBIOS_TASK {
    int state;
    int sector;
    void *buffer;
    int field_C;
    int ticks;
    int sectors_delivered;
    int size;
    int remaining;
    cdbios_task_pfn callback;
} CDBIOS_TASK;

enum CDBIOS_STATE {
    CDBIOS_STATE_INVALID = -1,
    CDBIOS_STATE_IDLE,
    CDBIOS_STATE_START,
    CDBIOS_STATE_READ,
    CDBIOS_STATE_ERROR,
};

#endif // _CDBIOS_H_
