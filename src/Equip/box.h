#ifndef _BOX_H_
#define _BOX_H_

#include "actor.h"
#include "game.h"
#include "GM_Control.h"

typedef struct Actor_Box
{
  Actor field_0_actor;
  OBJECT field_20;
  GM_Control *field_44_pCtrl;
  OBJECT *field_48_pParent;
  int field_4C_bFound;
  int field_50_pName;
  int field_54;
 } Actor_Box;

Actor* NewBox_80061C7C(GM_Control *pCtrl, OBJECT *pObj);

#endif // _BOX_H_
