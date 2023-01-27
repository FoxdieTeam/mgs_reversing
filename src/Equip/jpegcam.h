#ifndef _JPEGCAM_H
#define _JPEGCAM_H

#include "libgv/libgv.h"
#include "Game/Game.h"
#include "Game/GM_Control.h"

typedef char TMat8x8B[8][8];     // Matrix with 8 rows by 8 bytes
typedef char TMat16x16B[16][16]; // Matrix with 16 rows by 16 bytes

typedef struct Actor_jpegcam
{
    Actor       field_0_actor;
    GM_Control *field_20_pCtrl;
    int         field_24;
    int         field_28;
    int         field_2c;
    int         field_30;
    int         field_34;
    int         field_38;
    int         field_3c;
    int         field_40;
    int         field_44;
    int         field_48;
    int         field_4c;
    int         field_50;
    int         field_54;
    int         field_58;
    int         field_5c;
    int         field_60;
    int         field_64;
    int         field_68;
    int         field_6c;
    int         field_70;
    int         field_74;
    int         field_78;
    int         field_7c;
    int         field_80;
    int         field_84;
    int         field_88;
    int         field_8c;
    int         field_90;
    int         field_94;
    int         field_98;
} Actor_jpegcam;

void jpegcam_act_80064C50(Actor_jpegcam *pActor);
void jpegcam_kill_80065008(Actor_jpegcam *pActor);
int  jpegcam_loader_80065098(Actor_jpegcam *pActor, GM_Control *pCtrl, OBJECT *pParent);

Actor_jpegcam *NewJpegcam_80065118(GM_Control *pCtrl, OBJECT *pParent);

#endif // _JPEGCAM_H
