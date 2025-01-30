#include "focus.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct _FocusPrims
{
    DR_STP   stp[2][4];
    DR_TPAGE tpage1[2];
    SPRT     sprt1[2];
    DR_TPAGE tpage2[2];
    SPRT     sprt2[2];
} FocusPrims;

typedef struct _FocusWork
{
    GV_ACT      actor;
    FocusPrims *prims;
    int         xoff;
    int         yoff;
    int         near;
    int         far;
    int         f_len;
    int         f_target;
    int         f_range;
} FocusWork;

extern int GV_Clock;
extern int GV_PauseLevel;

void FocusAct_800CEA70(FocusWork *work)
{
    GV_MSG       *msg;
    int           f_len;
    int           near;
    int           far;
    unsigned int *ot;
    SPRT         *sprt;
    DR_STP       *stp;

    if (GV_PauseLevel == 0)
    {
        if (GV_ReceiveMessage(GV_StrCode("FocusView"), &msg))
        {
            work->f_target = msg->message[0];
        }

        work->f_len = GV_NearExp4(work->f_len, work->f_target);
    }

    f_len = work->f_len;

    work->near = (f_len - work->f_range) / 256;
    work->far = (f_len * 2 + work->f_range) / 256;

    near = work->near;
    if (near < 0)
    {
        near = 0;
    }

    far = work->far;
    if (far > 255)
    {
        far = 255;
    }

    ot = (unsigned int *)DG_ChanlOTag(0);

    sprt = &work->prims->sprt2[GV_Clock];
    sprt->x0 = -work->xoff;
    sprt->y0 = -112 - work->yoff;
    addPrim(ot, sprt);
    addPrim(ot, &work->prims->tpage2[GV_Clock]);

    sprt = &work->prims->sprt1[GV_Clock];
    sprt->x0 = -160 - work->xoff;
    sprt->y0 = -112 - work->yoff;
    addPrim(ot, sprt);
    addPrim(ot, &work->prims->tpage1[GV_Clock]);

    stp = work->prims->stp[GV_Clock];

    addPrim(&ot[0], &stp[3]);
    addPrim(&ot[near], &stp[2]);
    addPrim(&ot[far], &stp[1]);
    addPrim(&ot[0xFF], &stp[0]);
}

void FocusDie_800CED74(FocusWork *work)
{
    if (work->prims != NULL)
    {
        GV_DelayedFree(work->prims);
    }
}

int FocusGetResources_800CEDA4(FocusWork *work, int arg1, int arg2)
{
    FocusPrims *prims;
    SPRT       *sprt;

    prims = GV_Malloc(sizeof(FocusPrims));
    work->prims = prims;

    SetDrawStp(&prims->stp[0][0], 1);
    SetDrawStp(&prims->stp[1][0], 1);
    SetDrawStp(&prims->stp[0][1], 0);
    SetDrawStp(&prims->stp[1][1], 0);
    SetDrawStp(&prims->stp[0][2], 1);
    SetDrawStp(&prims->stp[1][2], 1);
    SetDrawStp(&prims->stp[0][3], 0);
    SetDrawStp(&prims->stp[1][3], 0);

    SetDrawTPage(&prims->tpage1[0], 0, 1, GetTPage(2, 0, 0, 0));
    SetDrawTPage(&prims->tpage1[1], 0, 1, GetTPage(2, 0, 320, 0));

    SetDrawTPage(&prims->tpage2[0], 0, 1, GetTPage(2, 0, 128, 0));
    SetDrawTPage(&prims->tpage2[1], 0, 1, GetTPage(2, 0, 448, 0));

    sprt = &prims->sprt1[0];
    setSprt(sprt);
    setSemiTrans(sprt, 1);
    setXY0(sprt, -160, -112);
    setWH(sprt, 160, 224);
    setUV0(sprt, 0, 0);
    setRGB0(sprt, 128, 128, 128);

    prims->sprt1[1] = prims->sprt1[0];
    prims->sprt2[0] = prims->sprt1[0];

    sprt = &prims->sprt2[0];
    sprt->x0 = 0;
    sprt->u0 = 32;

    prims->sprt2[1] = prims->sprt2[0];

    work->xoff = 2;
    work->yoff = 0;
    work->near = 0;
    work->far = 0;
    work->f_len = arg1;
    work->f_target = arg1;
    work->f_range = arg2;

    return 0;
}

#define EXEC_LEVEL GV_ACTOR_AFTER2

GV_ACT *NewFocus_800CEFF8(int name, int where, int argc, char **argv)
{
    FocusWork *work;

    work = (FocusWork *)GV_NewActor(EXEC_LEVEL, sizeof(FocusWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)FocusAct_800CEA70, (GV_ACTFUNC)FocusDie_800CED74, "focus.c");

        if (FocusGetResources_800CEDA4(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
