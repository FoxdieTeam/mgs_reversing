#ifndef __MGS_CHARA_PSYCO_H__
#define __MGS_CHARA_PSYCO_H__

#include "game/game.h"

typedef struct _PSYOBJ {
    int      name;
    int      flag;
    SVECTOR  pos;
    SVECTOR  rot;
    CONTROL *control;
} PSYOBJ;

extern SVECTOR s07b_dword_800E5BE0;

PSYOBJ *PSYOBJ_FindObject( int name );
void PSYOBJ_Init( void );

void *NewPsychoObject( int name, int where );

#endif // __MGS_CHARA_PSYCO_H__
