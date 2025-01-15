#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Bullet/rmissile.h"
#include "SD/g_sound.h"

extern int   GM_CurrentMap_800AB9B0;
extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;

extern SVECTOR GM_PlayerPosition_800ABA10;

extern int DG_CurrentGroupID;

extern PlayerStatusFlag GM_PlayerStatus;
extern int              GV_Clock;

/*---------------------------------------------------------------------------*/
// RC-Missile (Nikita)

typedef struct RcmWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            num_parent;
    unsigned int  *flags;
    int            which_side;
    int            counter;
    DG_PRIM       *prim;
    int            lightval; // state of the blinking light
} RcmWork;

#define EXEC_LEVEL 6

STATIC SVECTOR stru_800AB870 = {-100, -800, 80, 0};
STATIC RECT    rect_800AB878 = {100, 100, 200, 200};
STATIC SVECTOR svector_800AB880 = {-50, -300, 100, 0};

/*---------------------------------------------------------------------------*/

STATIC void RcmSetLightTexture(POLY_FT4 *poly, DG_TEX *tex)
{
    u_char offx;
    u_char offy;
    u_char offx_width;
    u_char offy_height;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    offx = tex->off_x;
    offx_width = offx + tex->w;

    offy = tex->off_y;
    offy_height = offy + tex->h;

    setUV4(poly, offx, offy, offx_width, offy, offx, offy_height, offx_width, offy_height);
    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

/**
 * @brief Adjusts the RGB values for the Nikita launcher's activation light.
 *
 * This function controls the blinking effect of the Nikita launcher's light
 * based on the provided flags. It modifies the brightness of the light
 * to create a fading effect when the action button is pressed.
 *
 * @param   work    Pointer to the RcmWork structure containing missile data.
 * @param   flags   Integer flags indicating the current state or input.
 */
STATIC void RcmUpdateLight(RcmWork *work, int flags)
{
    int lightval;
    union Prim_Union *prim;

    lightval = work->lightval;
    if ((flags & 1) != 0)
    {
        if (lightval <= 0)
        {
            lightval = 256;
        }
        // fade the light out
        lightval -= 8;
    }
    else
    {
        // light off if the button is not pressed
        lightval = 0;
    }
    work->lightval = lightval;

    lightval -= 64;

    if (lightval < 0)
    {
        lightval = 0;
    }
    prim = work->prim->packs[GV_Clock];
    prim->line_g2.r0 = lightval;
    prim->line_g2.g0 = lightval;
    prim->line_g2.b0 = lightval;
}

/**
 * @brief Handles the behavior of the Nikita launcher.
 *
 * @param work The Nikita actor data.
 */
STATIC void RcmAct(RcmWork *work)
{
    int     mapBit;
    int     p_flags;
    int     ammo_count;
    MATRIX  mt1;
    MATRIX  mt2;
    SVECTOR vec1;

    mapBit = work->control->map->index;

    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);
    DG_GroupPrim(work->prim, DG_CurrentGroupID);

    GM_CurrentMap_800AB9B0 = mapBit;

    if ((work->parent->objs->flag & DG_FLAG_INVISIBLE) || (GM_PlayerStatus & PLAYER_CB_BOX))
    {
        DG_InvisibleObjs( work->object.objs );
        DG_InvisiblePrim( work->prim );
    }
    else
    {
        DG_VisibleObjs( work->object.objs );
        DG_VisiblePrim( work->prim );
    }

    // p_flags store the state of the action button
    // to check if the player pressed and released the button
    p_flags = *work->flags;

    // update the blinking light
    RcmUpdateLight(work, p_flags);

    ammo_count = GM_Weapons[WEAPON_NIKITA];
    // if no ammo and the button is released, play a sound effect
    if (!ammo_count && (p_flags & 2))
    {
        GM_SeSet(&work->control->mov, SE_KARASHT);
        GM_SetNoise(5, 2, &work->control->mov);
        return;
    }

    if (ammo_count > 0 && (p_flags & 2))
    {
        // add a delay before firing the missile
        // to avoid hitting the player
        work->counter = 6;
        return;
    }
    if (work->counter)
    {
        work->counter--;
        if (work->counter < 2)
        {
            work->counter = 0;

            vec1.vx = -1024;
            vec1.vz = 0;
            vec1.vy = work->control->rot.vy;

            RotMatrixYXZ(&vec1, &mt1);
            DG_SetPos(&work->parent->objs->objs[work->num_parent].world);
            DG_MovePos(&stru_800AB870);
            ReadRotMatrix(&mt2);

            mt2.t[1] = GM_PlayerPosition_800ABA10.vy + 320;

            mt1.t[0] = mt2.t[0];
            mt1.t[1] = mt2.t[1];
            mt1.t[2] = mt2.t[2];

            if (NewRMissile(&mt1, work->which_side))
            {
                GM_Weapons[WEAPON_NIKITA] = --ammo_count;
                GM_SeSet(&work->control->mov, SE_MISSILE_FIRED);
                GM_SetNoise(100, 2, &work->control->mov);
            }
        }
    }
}

/**
 * @brief Frees resources associated with the Nikita launcher.
 *
 * @param   work    The Nikita actor data.
 */
STATIC void RcmDie(RcmWork *work)
{
    DG_PRIM *prim;

    GM_FreeObject((OBJECT *)&work->object);
    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

/**
 * @brief Loads resources for the Nikita launcher.
 *
 * @param   work    The RcmWork structure to initialize.
 * @param   parent  The parent OBJECT structure.
 */
STATIC int RcmGetResources(RcmWork *work, OBJECT *parent, int unit)
{
    DG_PRIM        *prim;
    DG_TEX         *tex;
    OBJECT_NO_ROTS *obj;

    obj = &work->object;
    GM_InitObjectNoRots(obj, GV_StrCode("nikita"), 109, 0);
    if (!obj->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot((OBJECT *)obj, parent, unit);

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &svector_800AB880, &rect_800AB878);
    work->prim = prim;

    if (prim)
    {
        tex = DG_GetTexture(GV_StrCode("rcm_l"));
        if (tex)
        {
            RcmSetLightTexture(&prim->packs[0]->poly_ft4, tex);
            RcmSetLightTexture(&prim->packs[1]->poly_ft4, tex);
            prim->root = &parent->objs->objs[unit].world;
            return 0;
        }
    }

    return -1;
}

/*---------------------------------------------------------------------------*/

/**
 * @brief   Creates a new RC missile actor.
 *
 * @param   control     The control structure for the Nikita launcher.
 * @param   parent      The parent OBJECT structure.
 * @param   num_parent  The parent object index.
 * @param   flags       Pointer to flags indicating Nikita state.
 * @param   which_side  Indicates which side the Nikita is on.
 *
 * @return  GV_ACT*     Returns a pointer to the new actor.
 */
GV_ACT *NewRCM(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    RcmWork *work;
    int      loadResult;

    work = (RcmWork *)GV_NewActor(EXEC_LEVEL, sizeof(RcmWork));
    if (work != 0)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)RcmAct,
                         (GV_ACTFUNC)RcmDie,
                         "rcm.c");

        loadResult = RcmGetResources(work, parent, num_parent);

        if (loadResult < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
        work->num_parent = num_parent;
        work->flags = flags;
        work->which_side = which_side;
        work->lightval = 0;
        work->counter = 0;
    }

    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;

    return &work->actor;
}
