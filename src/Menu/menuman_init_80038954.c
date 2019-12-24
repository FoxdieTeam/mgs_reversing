#include "linker.h"
#include "menuMan.h"
#include <LIBGTE.h>
#include <LIBGPU.h>

MenuMan SECTION(".gMenuMan_800BD360") gMenuMan_800BD360;

extern const char aMenumanC[];

void menuman_act_800386A4(MenuMan *);
void menuman_kill_800387E8(MenuMan *);

void menu_viewer_init_80044A70(MenuMan *);

void MENU_InitRadioTable_80049644(void);

extern MenuGlue gMenuPrimBuffer_8009E2D0;
extern TInitKillFn gMenuInitFns_8009E290[];

unsigned char SECTION(".gPrimBackingBuffers_800B9360") gPrimBackingBuffers_800B9360[2][8192];

extern const char aItem[]; // sdata

void sub_8003DD1C(const char *);

void SetDrawEnv_800906B0(DR_ENV *dr_env, DRAWENV *env);
void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);

void menu_init_subsystems_8003884C(MenuMan *pMenuMan)
{
    TInitKillFn *pIter;
    DRAWENV drawEnv;

    pMenuMan->field_2A_state = 0;
    pMenuMan->field_29 = 0;
    pMenuMan->field_28_flags = 0;

    pMenuMan->field_20_prim_buffer = &gMenuPrimBuffer_8009E2D0.mPrimBuf;

    gMenuPrimBuffer_8009E2D0.mPrimPtrs[0] = &gPrimBackingBuffers_800B9360[0][0];
    gMenuPrimBuffer_8009E2D0.mPrimPtrs[1] = &gPrimBackingBuffers_800B9360[1][0];

    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv_800906B0(&pMenuMan->mDR_ENV_field_4C[0], &drawEnv);

    DG_Init_DrawEnv_80018384(&drawEnv, 320, 0, 320, 224);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv_800906B0(&pMenuMan->mDR_ENV_field_4C[1], &drawEnv);

    sub_8003DD1C(aItem);

    pIter = &gMenuInitFns_8009E290[0];
    while (*pIter)
    {
        (*pIter)(pMenuMan);
        pIter++;
    }

    menu_viewer_init_80044A70(pMenuMan);
}

void menuman_init_80038954(void)
{
    GV_ActorInit_8001514c(&gMenuMan_800BD360.mBase, (TActorFunction)menuman_act_800386A4, (TActorFunction)menuman_kill_800387E8, aMenumanC);
    menu_init_subsystems_8003884C(&gMenuMan_800BD360);
    MENU_InitRadioTable_80049644();
}
