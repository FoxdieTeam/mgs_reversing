#ifndef _POCKET_H_
#define _POCKET_H_

#include "libgv/libgv.h"
#include "libdg/libdg.h"

/*
 * A drawing job of the pocket screens. pkt_back.c and entry.c each keep a
 * doubly linked list of them; the actor runs job->func( work, job ) every
 * frame for each job whose state is 1.
 */
typedef struct PKT_JOB PKT_JOB;

typedef void ( *PKT_JOB_FUNC )( void *work, PKT_JOB *job );

struct PKT_JOB
{
    /* 0x00 */ PKT_JOB     *prev;
    /* 0x04 */ PKT_JOB     *next;
    /* 0x08 */ PKT_JOB_FUNC func;
    /* 0x0C */ short        time;     /* counters, clamped by the actors */
    /* 0x0E */ short        time2;
    /* 0x10 */ u_short      n_prims;
    /* 0x12 */ char         gouraud;  /* prims are POLY_GT4 instead of POLY_FT4 */
    /* 0x13 */ char         field_13;
    /* 0x14 */ int          field_14;
    /* 0x18 */ int          field_18;
    /* 0x1C */ char         field_1C;
    /* 0x1E */ u_short      flags;
    /* 0x20 */ void        *prims;    /* POLY_FT4[n_prims] or POLY_GT4[n_prims] */
    /* 0x24 */ u_short      id;       /* ids >= 0x80 own no prims */
    /* 0x26 */ short        state;
    /* 0x28 */ int          field_28;
};

/* A queued change of a job's state, applied once per frame */
typedef struct PKT_REQUEST
{
    u_short id;
    u_short state;
} PKT_REQUEST;

#define PKT_MAX_REQUESTS 8

#endif /* _POCKET_H_ */
