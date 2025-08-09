#ifndef __MGS_CDBIOS_H__
#define __MGS_CDBIOS_H__

struct _CDBIOS_TASK;
typedef int (*cdbios_task_pfn)(struct _CDBIOS_TASK *);

typedef struct _CDBIOS_TASK {
    int state;
    int sector;
    void *buffer;
    int buffer_size;
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

/* cdbios.c */
int  CDBIOS_Reset(void);
void CDBIOS_TaskStart(void);
void CDBIOS_ReadRequest(void *buffer, unsigned int sector, unsigned int size, void *callback);
int  CDBIOS_ReadSync(void);
void CDBIOS_ForceStop(void);
int  CDBIOS_TaskState(void);

#endif // __MGS_CDBIOS_H__
