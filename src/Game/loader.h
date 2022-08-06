#ifndef _LOADER_H_
#define _LOADER_H_

#include "libgv/actor.h"

struct Loader_Rec_2
{
    char field_0;
    char field_1;
};

struct Loader_Record
{
    int                  field_0;
    int                  field_4; // cnf count?
    struct Loader_Rec_2 *field_8_p2Alloc;
    int                  field_C; // str ptr?
    int                  field_10;
    int                  field_14; // last size?
    int                  field_18; // state ?
    int                  field_1C; // cnf ptr?
    int                  field_20;
    int                  field_24;
    int                  field_28;
    int                  field_2C;
    int                  field_30;
    int                  field_34;
};

struct Loader
{
    struct Actor          base;
    struct Loader_Record *field_20_pFileName;
    int                   field_24_proc_cancel_flags;
    int                   field_28_bRunning;
    int                   field_2C_counter;
};

struct Loader            *Loader_Init_8002E460(const char *pStageName);

#endif // _LOADER_H_
