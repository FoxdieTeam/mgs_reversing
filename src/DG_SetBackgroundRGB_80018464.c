#include "dgd.h"

extern struct_dg gOts_800B1800[3];

void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
void DG_Init_800179F4(struct_dg *pDg, DRAWENV *pDrawEnv, int bUnknown);

void DG_SetBackgroundRGB_80018464(unsigned char r, unsigned char g, unsigned char b)
{
    DRAWENV drawEnv;
    struct_dg *pStruct = &gOts_800B1800[0];
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    setRGB0(&drawEnv, r, g, b);
    DG_Init_800179F4(pStruct, &drawEnv, 1);
    pStruct->word_6BC37A_0_1EC_size = 2;
}
