#ifndef __MGS_ANIMAL_MERYL3_H__
#define __MGS_ANIMAL_MERYL3_H__

#include "common.h"
#include "game/game.h"
#include "libdg/libdg.h"

typedef struct {
    int   press;
    int   dir;
} Meryl72Pad;

typedef struct _Work {
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          body;           /* 0x09C */
    MOTION_CONTROL  m_ctrl;         /* 0x180 */
    MOTION_SEGMENT  m_segs1[17];    /* 0x1D0 */
    MOTION_SEGMENT  m_segs2[17];    /* 0x434 */
    SVECTOR         rots[16];       /* 0x698 */
    SVECTOR         adjust[16];     /* 0x718 */
    MATRIX          light[2];       /* 0x798 */
    char            pad_7D8[0x7DC - 0x7D8];
    OBJECT          weapon;         /* 0x7DC */
    int             lod;            /* 0x8C0 */
    DG_DEF         *models[2];      /* 0x8C4 */
    TARGET         *target;         /* 0x8CC */
    char            pad_8D0[0x920 - 0x8D0];
    int             height;         /* 0x920 */
    char            pad_924[0x954 - 0x924];
    void          (*action)(struct _Work *, int);  /* 0x954 */
    void          (*action2)(struct _Work *, int); /* 0x958 */
    int             time;           /* 0x95C */
    int             time2;          /* 0x960 */
    int             n_action;       /* 0x964 */
    int             trg_yaw;        /* 0x968 */
    int             trg_pitch;      /* 0x96C */
    short           field_970;      /* 0x970 */
    char            pad_972[0x974 - 0x972];
    Meryl72Pad      pad;            /* 0x974 */
    int             think1;         /* 0x97C */
    int             think2;         /* 0x980 */
    int             think3;         /* 0x984 */
    int             count3;         /* 0x988 */
    int             count1;         /* 0x98C */
    int             field_990;      /* 0x990 */
    char            pad_994[0x9A4 - 0x994];
    int             player_dir;     /* 0x9A4 */
    int             player_dis;     /* 0x9A8 */
    char            pad_9AC[0x9B0 - 0x9AC];
    void           *shadow;         /* 0x9B0 */
    void           *glight;         /* 0x9B4 */
} Work;

static inline void SetMode(Work *work, void (*action)(Work *, int))
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

/* meryl3.c */
void *NewMeryl3(int name, int where);

/* ml3act.c */
void Meryl3Act(Work *work);

/* think.c */
void Meryl3Think(Work *work);

#endif // __MGS_ANIMAL_MERYL3_H__
