#include "bakudan.h"
#include "blast.h"
#include "linker.h"
#include "chara/snake/sna_init.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"

// c4 (armed)

extern int     GM_GameStatus_800AB3CC;
extern GV_PAD  GV_PadData_800B05C0[4];
extern int     GM_PlayerStatus_800ABA50;

extern HITTABLE c4_actors_800BDD78[C4_COUNT];
extern int GM_CurrentMap_800AB9B0;

extern int GV_Time_800AB330;
extern int GM_PlayerMap_800ABA0C;

extern unsigned short GM_ItemTypes_8009D598[];

extern SVECTOR GM_PlayerPosition_800ABA10;
extern Blast_Data blast_data_8009F4B8[8];

int bakudan_count_8009F42C = 0;
int time_last_press_8009F430 = 0;
int dword_8009F434 = 0; // unused variable

// default orientation for c4 object when placed on a moving target
// (probably to keep it upright because the 3d model is not oriented correctly)
SVECTOR model_orientation_8009F438 = {3072, 0, 0, 0};

/**
 * @brief Main function for the C4 actor. Handles the logic for the C4's behavior.
 *
 * @param work Pointer to the BakudanWork structure.
 */
void bakudan_act_8006A218(BakudanWork *work)
{
    MATRIX rotation;
    CONTROL *pCtrl;
    GV_PAD *pPad;
    MATRIX *pMtx;
    TARGET *pTarget;
#ifdef VR_EXE
    int cond;
#endif
    // if invalid game status, destroy the actor
    if (GM_GameStatus_800AB3CC < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    pCtrl = &work->control;
    pPad = &GV_PadData_800B05C0[0];

    if (GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2)
    {
        pPad = &GV_PadData_800B05C0[1];
    }

    work->active_pad = pPad;
    GM_ActControl_80025A7C(pCtrl);

    pMtx = work->transform;

    // if the c4 is placed on a moving target
    if (pMtx)
    {
        DG_RotatePos_8001BD64(&model_orientation_8009F438);
        // get the target where the c4 is placed
        pTarget = c4_actors_800BDD78[work->c4_index].data;
        work->map_index = pTarget->map;

        // if the target is not alive, destroy the actor
        if (!pTarget->field_20)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return;
        }
    }

    GM_CurrentMap_800AB9B0 = work->map_index;

    GM_ActObject2_80034B88((OBJECT *)&work->kmd);
    DG_GetLightMatrix_8001A3C4(&pCtrl->mov, work->light_mtx);

#ifdef VR_EXE
    // VR executable for some reason assigns the result
    // of the condition below to a temporary variable!?
    cond = 0;
#endif
    // check if the circle button was pressed
    // the frame counter is different from the last time the circle button was
    // pressed to prevent counting multiple presses in the same frame
    // the player is in the same map as the c4
    // the player has not released the pad
    // the player is not holding an item that can't be used with the c4
    if (((work->active_pad->press & PAD_CIRCLE) &&
         (time_last_press_8009F430 != GV_Time_800AB330) &&
         (GM_CurrentMap_800AB9B0 & GM_PlayerMap_800ABA0C) &&
         !(GM_GameStatus_800AB3CC & STATE_PADRELEASE) &&
         !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) &&
         !(GM_ItemTypes_8009D598[GM_CurrentItemId + 1] & 2)) ||
        dword_8009F434)
#ifdef VR_EXE
    {
        cond = 1;
    }
    if (cond)
#endif
    {
        work->detonator_btn_pressed = 1;

        if (work->active_pad->press & PAD_CIRCLE)
        {
            GM_SeSetMode_800329C4(&GM_PlayerPosition_800ABA10, 0x32, GM_SEMODE_BOMB);
        }

        time_last_press_8009F430 = GV_Time_800AB330;
    }
    // keep track of the consecutive frames the circle button is pressed
    if (work->detonator_btn_pressed)
    {
        work->detonator_frames_count++;
    }

    // detonate the c4 after 3 frames
    if (work->detonator_frames_count >= 3)
    {
        ReadRotMatrix(&rotation);
        NewBlast_8006DFDC(&rotation, &blast_data_8009F4B8[1]);
        sub_8002A258(work->control.map->hzd, &work->control.field_10_events);
        GV_DestroyActor_800151C8(&work->actor);
    }
    else if (pMtx)
    {
        // update the c4 position and rotation to follow the target
        DG_SetPos_8001BC44(pMtx);
        DG_PutVector_8001BE48(work->position, &pCtrl->mov, 1);
        DG_MatrixRotYXZ_8001E734(pMtx, &pCtrl->rot);
    }
}

/**
 * @brief Cleanup function for the C4 actor.
 * Frees resources and updates the actor list.
 *
 * @param work Pointer to the BakudanWork structure.
 */
void bakudan_kill_8006A4A4(BakudanWork *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_ClearBulName_8004FBE4(work->control.name);
    GM_FreeObject_80034BF8((OBJECT *)&work->kmd);

    if (work->c4_index >= 0)
    {
        c4_actors_800BDD78[work->c4_index].actor = NULL;
        bakudan_count_8009F42C--;
    }
}

/**
 * @brief Find the next free slot in the c4_actors_800BDD78 array.
 *
 * @return int Index of the next free slot, or -1 if no free slot is available.
 */
int bakudan_next_free_item_8006A510()
{
    int i;
    for (i = 0; i < C4_COUNT; i++)
    {
        if (!c4_actors_800BDD78[i].actor)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Helper function to initialize a C4 actor.
 *
 * @param work Pointer to the BakudanWork structure.
 * @param pMtx Transform matrix.
 * @param pVec Position vector.
 * @param followTarget 1 if the C4 is placed on a moving target, 0 otherwise.
 * @param data Pointer to the target (wall/floor or moving target).
               Used to update the c4 position and rotation and to delete the
               c4 when the target is dead)
* @return int 0 on success, -1 on failure.
 */
int bakudan_8006A54C(BakudanWork *work, MATRIX *pMtx, SVECTOR *pVec, int followTarget, void *data)
{
    CONTROL *pCtrl = &work->control;
    OBJECT_NO_ROTS *pKmd;
    int nextItem;
    HITTABLE *pItem;


    work->map_index = GM_CurrentMap_800AB9B0 = GM_PlayerMap_800ABA0C;

    if (GM_InitControl_8002599C(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 0, 0, 0);
    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);

    if (followTarget == 1)
    {
        // initial position and rotation
        work->transform = pMtx;
        work->position = pVec;
    }
    else
    {
        work->transform = NULL;
    }

    pKmd = &work->kmd;
    GM_InitObjectNoRots_800349B0(pKmd, 0xf83d, 0x6d, 0);

    if (!pKmd->objs)
    {
        return -1;
    }

    pKmd->objs->world = *pMtx;
    GM_ConfigObjectLight_80034C44((OBJECT *)pKmd, work->light_mtx);
    pKmd->objs->objs[0].raise = 200;

    work->c4_index = nextItem = bakudan_next_free_item_8006A510();

    if (nextItem < 0)
    {
        return -1;
    }

    pItem = &c4_actors_800BDD78[nextItem];
    pItem->actor = &work->actor;
    pItem->control = pCtrl;
    pItem->data = data;

    bakudan_count_8009F42C++;
    return 0;
}

/**
 * @brief Construct a new c4 actor
 *
 * @param pMtx Transform matrix.
 * @param pVec Position vector.
 * @param followTarget 1 if the c4 is placed on a moving target, 0 otherwise.
 * @param not_used
 * @param data Pointer to the target (used to update the c4 position,
 *             rotation and to delete the c4 when the target is dead).
 * @return * GV_ACT* pointer to the new c4 actor.
 */
GV_ACT *NewBakudan_8006A6CC(MATRIX *pMtx, SVECTOR *pVec, int followTarget, int not_used, void *data)
{
    BakudanWork *work;

    // if there are already 16 c4s, don't create a new one
    if (bakudan_count_8009F42C == 16)
    {
        return 0;
    }

    work = (BakudanWork *)GV_NewActor_800150E4(6, sizeof(BakudanWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)bakudan_act_8006A218,
                                  (TActorFunction)bakudan_kill_8006A4A4, "bakudan.c");
        if (bakudan_8006A54C(work, pMtx, pVec, followTarget, data) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return 0;
        }
        work->detonator_frames_count = 0;
        work->detonator_btn_pressed = 0;
    }
#ifdef VR_EXE
    if (time_last_press_8009F430 > GV_Time_800AB330)
    {
        time_last_press_8009F430 = 0;
    }
#endif
    return &work->actor;
}
