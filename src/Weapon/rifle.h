#ifndef _RIFLE_H_
#define _RIFLE_H_

#include "Game/game.h"
#include "libgv/libgv.h"

// PSG1

typedef struct _RifleWork
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20_obj;
    CONTROL       *control;
    OBJECT        *field_48_pParentObj;
    int            field_4c_numParent;
    int           *field_50;
    int            field_54;
    int            field_58;
    void          *field_5c;
} RifleWork;

GV_ACT *NewRifle_80068214(CONTROL *pCtrl, OBJECT *pParentObj, int numParent, unsigned int *a4, int a5);

#endif // _RIFLE_H_
