#ifndef _CHARADEF_H_
#define _CHARADEF_H_

#include "strcode.h"
#include "libgv/libgv.h"

typedef GV_ACT *(*NEWCHARA)(int name, int where, int argc, char **argv);

typedef struct CHARA
{
    unsigned short  class_id;   // strcode of chara's GCL name
    NEWCHARA        func;       // pointer to actor creation function
} CHARA;

#endif // _CHARADEF_H_
