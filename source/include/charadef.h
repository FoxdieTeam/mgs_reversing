#ifndef _CHARADEF_H_
#define _CHARADEF_H_

#include "strcode.h"

// XXX NEWCHARA was defined with an empty parameter list in MGS4's dwarf info.
// XXX Seems like they originally did it here in MGS1 as well, considering
// XXX NewActor funcs have various different signatures.
// XXX
// XXX NOTE: The empty parameter list is widely regarded as one of old C's
// XXX anti-features. C++ and C23 have changed its meaning to (void).

//typedef void *(*NEWCHARA)();
typedef void *(*NEWCHARA)(int name, int where, int argc, char **argv);

typedef struct CHARA
{
    unsigned short  class_id;   // strcode of chara's GCL name
    NEWCHARA        func;       // pointer to actor creation function
} CHARA;

#endif // _CHARADEF_H_
