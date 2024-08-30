#ifndef _JPEGCAM_H
#define _JPEGCAM_H

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Thing/sight.h"
#include "memcard/memcard.h"

typedef signed char TMat8x8B[8][8];     // Matrix with 8 rows by 8 bytes
typedef signed char TMat16x16B[16][16]; // Matrix with 16 rows by 16 bytes
typedef int         TMat8x8I[8][8];

typedef struct JpegCamWork
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *field_24_parent;
    OBJECT_NO_ROTS field_28_goggles;
    short          field_4c_head_saved_packs;
    short          field_4e_head_saved_raise;
    GV_PAD        *field_50_pInput;
    SVECTOR        field_54_vec;
    SVECTOR        field_5C_ang;
    int            field_64_state;
    int            field_68;
    MAP           *field_6C_pMap;
    int            field_70;
    int            field_74;
    int            field_78;
    int            field_7C;
    int            field_80;
    char          *field_84;
    char          *field_88;
    int            field_8C_size;
    SightWork     *field_90_pSight;
    int            field_94_bMakeVisible;
    int            field_98;
} JpegCamWork;
STATIC_ASSERT_SIZE(JpegCamWork, 0x9c);

void jpegcam_act_80064C50(JpegCamWork *work);
void jpegcam_kill_80065008(JpegCamWork *work);
int  jpegcam_loader_80065098(JpegCamWork *work, CONTROL *pCtrl, OBJECT *pParent);

GV_ACT * NewJpegcam_80065118(CONTROL *pCtrl, OBJECT *pParent, int unused);

void jpegcam_unk1_80063704(char *buf, mem_card *pMemcard, int arg2, int arg3);
void jpegcam_unk2_80063888(char *param_1, int param_2);
void jpegcam_unk3_800638B4(int *arg0);

#endif // _JPEGCAM_H
