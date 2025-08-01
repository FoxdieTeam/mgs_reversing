#include "d_blood.h"
#include "d_bloodr.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "linkvar.h"
#include "sd/g_sound.h"

/*---------------------------------------------------------------------------*/

typedef struct _DBloodWork
{
    GV_ACT actor;
    int    f20;
    int    f24_state;
    int    f28;
    char   padding[0xC];
    int    current_map;
} DBloodWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

STATIC void d_blood_Die(DBloodWork *work)
{
}

STATIC int d_blood_act_helper_800729B4(void)
{
    CONTROL *control;
    unsigned short *pArray;
    int i;

    control = GM_PlayerControl;
    if (!control)
    {
        return 0;
    }

    pArray = control->event.field_8_array;

    for (i = control->event.field_6_count; i > 0; i--, pArray++)
    {
        if (*pArray == 0xC09E)
        {
            return 1;
        }
    }

    return 0;
}

STATIC void d_blood_Act(DBloodWork *work)
{
    switch (work->f24_state)
    {
    case 0:
        if (((GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_MOVE |
                PLAYER_GROUND | PLAYER_PAD_OFF)) == PLAYER_GROUND) &&
            (GV_PadData[0].press & PAD_CIRCLE))
        {
            if (d_blood_act_helper_800729B4())
            {
                GM_SeSet2(0, 63, 183);
                work->f24_state = 1;
                NewKetchap_r(work->current_map);
                GM_GameStatus |= STATE_PADRELEASE;
            }
            else
            {
                GM_SeSet2(0, 63, SE_BUZZER);
            }
        }
        break;

    case 1:
        if (++work->f28 > work->f20)
        {
            work->f24_state = 2;
            GM_GameStatus &= ~STATE_PADRELEASE;
            GM_CurrentItemId = IT_None;
            GM_Items[IT_Ketchup] = IT_None;
        }
        break;

    case 2:
        break;
    }
}

STATIC int d_blood_loader_helper_80072B24(DBloodWork *work)
{
    work->f20 = 100;
    work->f24_state = 0;
    return 0;
}

STATIC int d_blood_GetResources(DBloodWork *work)
{
    work->current_map = GM_CurrentMap;
    d_blood_loader_helper_80072B24(work);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewKetchap(CONTROL *control, OBJECT *parent_obj, int num_parent)
{
    DBloodWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(DBloodWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, &d_blood_Act, &d_blood_Die, "d_blood.c");

        if (d_blood_GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
