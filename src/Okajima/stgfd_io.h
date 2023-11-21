#ifndef _STGFD_IO_
#define _STGFD_IO_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"

typedef struct StgfdIoWork_0x30
{
    DR_TPAGE field_0_dr_tpage[2];
    TILE     field_10_tile[2];
} StgfdIoWork_0x30;

typedef struct StgfdIoWork
{
    GV_ACT                field_0_actor;
    StgfdIoWork_0x30 *field_20_pAlloc0x30;
    int                  field_24;
    int                  field_28;
    SVECTOR              field_2C;
    SVECTOR              field_34;
    int                  field_3C_state;
} StgfdIoWork;

void stgfd_io_act_80074F5C(StgfdIoWork *work);
void stgfd_io_kill_80075164(StgfdIoWork *work);
int  stgfd_io_loader_80075194(StgfdIoWork *work);

StgfdIoWork * NewStnFade_800752A0(void);

#endif // _STGFD_IO_
