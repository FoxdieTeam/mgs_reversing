#ifndef __MGS_CHARADEF_H__
#define __MGS_CHARADEF_H__

// XXX NOTE: The empty parameter list is widely regarded as one of old C's
// XXX anti-features. C++ and C23 have changed its meaning to (void).

typedef void *NEWCHARA();
// typedef void *NEWCHARA(int name, int map); <-- MGS2 version.

// NOTE: Seems like earlier in development, GCL args were passed via main-style
// (int argc, char *argv[]) arguments. This was apparently replaced with libgcl's
// GCL_GetOption/GCL_Next* APIs. Some NewActor funcs are still declared with
// argc, argv parameters, but they go unused.
//
// XXX The "chara" command handler in game/script.c still calls NewActor funcs
// XXX with this outdated signature, so registers $a2 and $a3 are trashed and
// XXX passed garbage values every time a chara is instantiated.
// XXX
// XXX typedef void *NEWCHARA(int name, int map, int argc, char **argv);

typedef struct {
    unsigned short class_id;    // strcode of the chara's GCL name
    NEWCHARA *func;             // NewActor callback
} CHARA;

#endif // __MGS_CHARADEF_H__
