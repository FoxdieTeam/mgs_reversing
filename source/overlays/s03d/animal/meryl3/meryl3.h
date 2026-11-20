#ifndef __MGS_ANIMAL_MERYL3_H__
#define __MGS_ANIMAL_MERYL3_H__

#include "mgstype.h"
#include "game/game.h"
#include "libdg/libdg.h"

/*---------------------------------------------------------------------------*/

typedef struct _PAD {
    int press;
    int dir;
} PAD;

struct _Work;

typedef void ( *ACTION )( struct _Work *, int ) ;

typedef struct _Work {
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[17];
    MOTION_SEGMENT m_segs2[17];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    char           pad_7D8[0x4];
    OBJECT         weapon;
    int            lod;
    DG_DEF        *models[2];
    TARGET        *target;
    char           pad_8D0[0x50];
    int            height;
    char           pad_924[0x30];
    ACTION         action;
    ACTION         action2;
    int            time;
    int            time2;
    int            n_action;
    int            trg_yaw;
    int            trg_pitch;
    short          field_970;
    PAD            pad;
    int            think1;
    int            think2;
    int            think3;
    int            count3;
    int            count1;
    int            field_990;
    char           pad_994[0x10];
    int            player_dir;
    int            player_dis;
    char           pad_9AC[0x4];
    void          *shadow;
    void          *glight;
} Work;

/*---------------------------------------------------------------------------*/

/* meryl3.c */
void *NewMeryl3(int name, int where);

/* ml3act.c */
void Meryl3Act(Work *work);

/* think.c */
void Meryl3Think(Work *work);

#endif // __MGS_ANIMAL_MERYL3_H__
