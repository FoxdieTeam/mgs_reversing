#ifndef __MGS_CHARA_PSYCO_H__
#define __MGS_CHARA_PSYCO_H__

#include "game/game.h"

typedef struct _PSYOBJ {
    int      id;
    int      flag;
    SVECTOR  pos;
    SVECTOR  rot;
    CONTROL *control;
} PSYOBJ;

PSYOBJ *s07b_800D2CFC( int id );

extern SVECTOR s07b_dword_800E5BE0;

#endif // __MGS_CHARA_PSYCO_H__
