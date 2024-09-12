#include "bakudan.h"

#include "common.h"
#include "blast.h"
#include "chara/snake/sna_init.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "SD/g_sound.h"

// c4 (armed)

extern int     GM_GameStatus;
extern GV_PAD  GV_PadData_800B05C0[4];
extern int     GM_PlayerStatus_800ABA50;

extern HITTABLE c4_actors_800BDD78[C4_COUNT];
extern int GM_CurrentMap_800AB9B0;

extern int GV_Time;
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
void BakudanAct_8006A218(BakudanWork *work)
{
    MATRIX rotation;
    CONTROL *pCtrl;
    GV_PAD *pPad;
    MATRIX *world;
    TARGET *pTarget;
#ifdef VR_EXE
    int cond;
#endif
    // if invalid game status, destroy the actor
    if (GM_GameStatus < 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    pCtrl = &work->control;
    pPad = &GV_PadData_800B05C0[0];

    if (GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2)
    {
        pPad = &GV_PadData_800B05C0[1];
    }

    work->active_pad = pPad;
    GM_ActControl(pCtrl);

    world = work->transform;

    // if the c4 is placed on a moving target
    if (world)
    {
        DG_RotatePos(&model_orientation_8009F438);
        // get the target where the c4 is placed
        pTarget = c4_actors_800BDD78[work->c4_index].data;
        work->map_index = pTarget->map;

        // if the target is not alive, destroy the actor
        if (!pTarget->field_20)
        {
            GV_DestroyActor(&work->actor);
            return;
        }
    }

    GM_CurrentMap_800AB9B0 = work->map_index;

    GM_ActObject2((OBJECT *)&work->kmd);
    DG_GetLightMatrix(&pCtrl->mov, work->light_mtx);

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
         (time_last_press_8009F430 != GV_Time) &&
         (GM_CurrentMap_800AB9B0 & GM_PlayerMap_800ABA0C) &&
         !(GM_GameStatus & STATE_PADRELEASE) &&
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
            GM_SeSetMode_800329C4(&GM_PlayerPosition_800ABA10, SE_C4_SWITCH, GM_SEMODE_BOMB);
        }

        time_last_press_8009F430 = GV_Time;
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
        sub_8002A258(work->control.map->hzd, &work->control.event);
        GV_DestroyActor(&work->actor);
    }
    else if (world)
    {
        // update the c4 position and rotation to follow the target
        DG_SetPos(world);
        DG_PutVector(work->position, &pCtrl->mov, 1);
        DG_MatrixRotYXZ(world, &pCtrl->rot);
    }
}

/**
 * @brief Cleanup function for the C4 actor.
 * Frees resources and updates the actor list.
 *
 * @param work Pointer to the BakudanWork structure.
 */
void BakudanKill_8006A4A4(BakudanWork *work)
{
    GM_FreeControl(&work->control);
    GM_ClearBulName_8004FBE4(work->control.name);
    GM_FreeObject((OBJECT *)&work->kmd);

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
int BakudanNextIndex_8006A510( void )
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
 * @param world Transform matrix.
 * @param pos Position vector.
 * @param attached 1 if the C4 is placed on a moving target, 0 otherwise.
 * @param data Pointer to the target (wall/floor or moving target).
               Used to update the c4 position and rotation and to delete the
               c4 when the target is dead)
* @return int 0 on success, -1 on failure.
 */
int BakudanGetResources_8006A54C(BakudanWork *work, MATRIX *world, SVECTOR *pos, int attached, void *data)
{
    CONTROL *pCtrl = &work->control;
    OBJECT_NO_ROTS *pKmd;
    int nextItem;
    HITTABLE *pItem;


    work->map_index = GM_CurrentMap_800AB9B0 = GM_PlayerMap_800ABA0C;

    if (GM_InitControl(pCtrl, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(pCtrl, 0, 0, 0);
    GM_ConfigControlMatrix(pCtrl, world);

    if (attached == 1)
    {
        // initial position and rotation
        work->transform = world;
        work->position = pos;
    }
    else
    {
        work->transform = NULL;
    }

    pKmd = &work->kmd;
    GM_InitObjectNoRots(pKmd, 0xf83d, 0x6d, 0);

    if (!pKmd->objs)
    {
        return -1;
    }

    pKmd->objs->world = *world;
    GM_ConfigObjectLight((OBJECT *)pKmd, work->light_mtx);
    pKmd->objs->objs[0].raise = 200;

    work->c4_index = nextItem = BakudanNextIndex_8006A510();

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
 * @param world Transform matrix.
 * @param pos Position vector.
 * @param attached 1 if the c4 is placed on a moving target, 0 otherwise.
 * @param unused
 * @param data Pointer to the target (used to update the c4 position,
 *             rotation and to delete the c4 when the target is dead).
 * @return * GV_ACT* pointer to the new c4 actor.
 */
GV_ACT *NewBakudan_8006A6CC(MATRIX *world, SVECTOR *pos, int attached, int unused, void *data)
{
    BakudanWork *work;

    // if there are already 16 c4s, don't create a new one
    if (bakudan_count_8009F42C == 16)
    {
        return 0;
    }

    work = (BakudanWork *)GV_NewActor(6, sizeof(BakudanWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BakudanAct_8006A218,
                         (TActorFunction)BakudanKill_8006A4A4, "bakudan.c");
        if (BakudanGetResources_8006A54C(work, world, pos, attached, data) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
        work->detonator_frames_count = 0;
        work->detonator_btn_pressed = 0;
    }
#ifdef VR_EXE
    if (time_last_press_8009F430 > GV_Time)
    {
        time_last_press_8009F430 = 0;
    }
#endif
    return &work->actor;
}
