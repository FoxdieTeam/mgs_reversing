#ifndef _RFSIGHT_H_
#define _RFSIGHT_H_

#include "libgv/libgv.h"
#include "Thing/sight.h"

// PSG1 first person HUD

typedef Actor_Sight * (*rfsight_pfn_t)(int, int, short *, short, short *);

typedef struct _RfSightWork
{
    GV_ACT        actor;
    DVECTOR      *field_20;
    int           field_24;
    int           field_28;
    rfsight_pfn_t field_2c_pfn;
} RfSightWork;

GV_ACT *NewRifleSight_8006989C(void);
GV_ACT *NewRifleSightFast_80069920(void);

#endif // _RFSIGHT_H_
