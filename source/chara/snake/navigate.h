#ifndef __MGS_CHARA_NAVIGATE_H__
#define __MGS_CHARA_NAVIGATE_H__

#include "game/game.h"

typedef struct _NAVIGATE
{
    int     addr;
    int     target;
    int     target_next;
    int     next;
    SVECTOR next_pos;
    SVECTOR target_pos;
} NAVIGATE;

void NagivateInit(NAVIGATE *nav, HZD_HDL *hzd, SVECTOR *pos);
void NavigateSetTarget(NAVIGATE *nav, HZD_HDL *hzd, SVECTOR *pos);
void NavigateSetTargetPlayer(NAVIGATE *nav);
int NavigateGetTargetDist(NAVIGATE *nav, SVECTOR *pos);
int NavigateTargetNear(NAVIGATE *nav, SVECTOR *pos, int dist);
int NavigateUpdate(NAVIGATE *nav, CONTROL *control);

#endif // __MGS_CHARA_NAVIGATE_H__
