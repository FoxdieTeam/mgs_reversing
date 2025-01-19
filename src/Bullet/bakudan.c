#include "bakudan.h"
#include "blast.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "chara/snake/sna_init.h"
#include "Game/game.h"
#include "Game/hittable.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "SD/g_sound.h"

extern GV_PAD  GV_PadData_800B05C0[4];
extern int     GM_PlayerStatus;

extern HITTABLE GM_C4Datas_800BDD78[C4_COUNT];
extern int GM_CurrentMap;

extern int GM_PlayerMap_800ABA0C;

extern unsigned short GM_ItemTypes[];

extern SVECTOR GM_PlayerPosition_800ABA10;
extern BLAST_DATA blast_data_8009F4B8[8];

/*---------------------------------------------------------------------------*/
// C4 bomb (armed)

#define EXEC_LEVEL 6

int bakudan_count_8009F42C = 0;
int time_last_press_8009F430 = 0;
int dword_8009F434 = 0; // unused variable

// default orientation for C4 object when placed on a moving target
// (probably to keep it upright because the 3d model is not oriented correctly)
SVECTOR model_orientation_8009F438 = {3072, 0, 0, 0};

/**
 * @brief Main function for the C4 actor. Handles the logic for the C4's behavior.
 *
 * @param work Pointer to the BakudanWork structure.
 */
STATIC void BakudanAct(BakudanWork *work)
{
    MATRIX rotation;
    CONTROL *control;
    GV_PAD *pad;
    MATRIX *world;
    TARGET *target;
#ifdef VR_EXE
    int cond;
#endif
    // if invalid game status, destroy the actor
    if (GM_GameStatus < 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    control = &work->control;
    pad = &GV_PadData_800B05C0[0];

    if (GM_PlayerStatus & PLAYER_SECOND_CONTROLLER)
    {
        pad = &GV_PadData_800B05C0[1];
    }

    work->active_pad = pad;
    GM_ActControl(control);

    world = work->transform;

    // if the C4 is placed on a moving target
    if (world)
    {
        DG_RotatePos(&model_orientation_8009F438);
        // get the target where the C4 is placed
        target = GM_C4Datas_800BDD78[work->c4_index].data;
        work->map_index = target->map;

        // if the target is not alive, destroy the actor
        if (!target->field_20)
        {
            GV_DestroyActor(&work->actor);
            return;
        }
    }

    GM_CurrentMap = work->map_index;

    GM_ActObject2((OBJECT *)&work->kmd);
    DG_GetLightMatrix(&control->mov, work->light_mtx);

#ifdef VR_EXE
    // VR executable for some reason assigns the result
    // of the condition below to a temporary variable!?
    cond = 0;
#endif
    // check if the circle button was pressed
    // the frame counter is different from the last time the circle button was
    // pressed to prevent counting multiple presses in the same frame
    // the player is in the same map as the C4
    // the player has not released the pad
    // the player is not holding an item that can't be used with the C4
    if (((work->active_pad->press & PAD_CIRCLE) &&
         (time_last_press_8009F430 != GV_Time) &&
         (GM_CurrentMap & GM_PlayerMap_800ABA0C) &&
         !(GM_GameStatus & STATE_PADRELEASE) &&
         !(GM_PlayerStatus & PLAYER_PAD_OFF) &&
         !(GM_ItemTypes[GM_CurrentItemId + 1] & 2)) ||
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
            GM_SeSetMode(&GM_PlayerPosition_800ABA10, SE_C4_SWITCH, GM_SEMODE_BOMB);
        }

        time_last_press_8009F430 = GV_Time;
    }
    // keep track of the consecutive frames the circle button is pressed
    if (work->detonator_btn_pressed)
    {
        work->detonator_frames_count++;
    }

    // detonate the C4 after 3 frames
    if (work->detonator_frames_count >= 3)
    {
        ReadRotMatrix(&rotation);
        NewBlast(&rotation, &blast_data_8009F4B8[1]);
        HZD_8002A258(work->control.map->hzd, &work->control.event);
        GV_DestroyActor(&work->actor);
    }
    else if (world)
    {
        // update the C4 position and rotation to follow the target
        DG_SetPos(world);
        DG_PutVector(work->position, &control->mov, 1);
        DG_MatrixRotYXZ(world, &control->rot);
    }
}

/**
 * @brief Cleanup function for the C4 actor.
 * Frees resources and updates the actor list.
 *
 * @param work Pointer to the BakudanWork structure.
 */
STATIC void BakudanDie(BakudanWork *work)
{
    GM_FreeControl(&work->control);
    GM_ClearBulName(work->control.name);
    GM_FreeObject((OBJECT *)&work->kmd);

    if (work->c4_index >= 0)
    {
        GM_C4Datas_800BDD78[work->c4_index].actor = NULL;
        bakudan_count_8009F42C--;
    }
}

/**
 * @brief Find the next free slot in the GM_C4Datas_800BDD78 array.
 *
 * @return int Index of the next free slot, or -1 if no free slot is available.
 */
STATIC int BakudanNextIndex( void )
{
    int i;
    for (i = 0; i < C4_COUNT; i++)
    {
        if (!GM_C4Datas_800BDD78[i].actor)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Helper function to initialize a C4 actor.
 *
 * @param work      Pointer to the BakudanWork structure.
 * @param world     Transform matrix.
 * @param pos       Position vector.
 * @param attached  1 if the C4 is placed on a moving target, 0 otherwise.
 * @param data      Pointer to the target (wall/floor or moving target).
 *                  Used to update the C4 position and rotation and to delete the
 *                  C4 when the target is dead)
 *
 * @return int      0 on success, -1 on failure.
 */
STATIC int BakudanGetResources(BakudanWork *work, MATRIX *world, SVECTOR *pos, int attached, void *data)
{
    CONTROL *control = &work->control;
    OBJECT_NO_ROTS *object;
    int nextItem;
    HITTABLE *item;

    work->map_index = GM_CurrentMap = GM_PlayerMap_800ABA0C;

    if (GM_InitControl(control, GM_Next_BulName_8004FBA0(), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, 0, 0, 0);
    GM_ConfigControlMatrix(control, world);

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

    object = &work->kmd;
    GM_InitObjectNoRots(object, 0xf83d, 0x6d, 0);

    if (!object->objs)
    {
        return -1;
    }

    object->objs->world = *world;
    GM_ConfigObjectLight((OBJECT *)object, work->light_mtx);
    object->objs->objs[0].raise = 200;

    work->c4_index = nextItem = BakudanNextIndex();

    if (nextItem < 0)
    {
        return -1;
    }

    item = &GM_C4Datas_800BDD78[nextItem];
    item->actor = &work->actor;
    item->control = control;
    item->data = data;

    bakudan_count_8009F42C++;
    return 0;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief   Construct a new C4 actor
 *
 * @param   world       Transform matrix.
 * @param   pos         Position vector.
 * @param   attached    1 if the C4 is placed on a moving target, 0 otherwise.
 * @param   unused
 * @param   data        Pointer to the target (used to update the C4 position,
 *                      rotation and to delete the C4 when the target is dead).
 *
 * @return  GV_ACT*     Pointer to the new C4 actor.
 */
GV_ACT *NewBakudan(MATRIX *world, SVECTOR *pos, int attached, int unused, void *data)
{
    BakudanWork *work;

    // if there are already 16 C4s, don't create a new one
    if (bakudan_count_8009F42C == C4_COUNT)
    {
        return NULL;
    }

    work = (BakudanWork *)GV_NewActor(EXEC_LEVEL, sizeof(BakudanWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)BakudanAct,
                         (GV_ACTFUNC)BakudanDie, "bakudan.c");
        if (BakudanGetResources(work, world, pos, attached, data) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
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
