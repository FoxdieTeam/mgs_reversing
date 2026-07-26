#include "d_blood.h"
#include "d_bloodr.h"

#include "common.h"
#include "linkvar.h"
#include "strcode.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "sound/g_sound.h"

/*---------------------------------------------------------------------------*/

#define KETCHUP_FLAG ( PLAYER_INTRUDE | PLAYER_MOVE | PLAYER_GROUND | PLAYER_PAD_OFF )

typedef struct _Work
{
    GV_ACT actor;
    int    delay;
    int    state;
    int    time;
    char   unused[12];
    int    map;
} Work;

/*---------------------------------------------------------------------------*/

static void Die(Work *work)
{
    /* do nothing */
}

static int CheckTrap(void)
{
    CONTROL *control;
    u_short *inside;
    int      i;

    control = GM_PlayerControl;
    if (control == NULL) return 0;

    inside = control->evt.inside;
    for (i = control->evt.n_inside; i > 0; i--)
    {
        if (*inside == HASH_TRAP_KETCHUP) return 1;
        inside++;
    }
    return 0;
}

static void Act(Work *work)
{
    switch (work->state)
    {
    case 0:
        if ((GM_PlayerStatus & KETCHUP_FLAG) == PLAYER_GROUND)
        {
            if (GV_PadData[0].press & PAD_CIRCLE)
            {
                if (CheckTrap())
                {
                    GM_SeSet2(0, 63, 183);
                    work->state = 1;
                    NewKetchap_r(work->map);
                    GM_GameStatus |= STATE_PADRELEASE;
                }
                else
                {
                    GM_SeSet2(0, 63, SE_BUZZER);
                }
            }
        }
        break;
    case 1:
        if (++work->time > work->delay)
        {
            work->state = 2;
            GM_GameStatus &= ~STATE_PADRELEASE;
            GM_CurrentItemId = IT_None;
            GM_Items[IT_Ketchup] = IT_None;
        }
        break;
    case 2:
        break;
    }
}

static int InitState(Work *work)
{
    work->delay = 100;
    work->state = 0;
    return 0;
}

static int GetResources(Work *work)
{
    work->map = GM_CurrentMap;
    InitState(work);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewKetchap(CONTROL *root_ctrl, OBJECT *root_obj, int unit)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "d_blood.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
