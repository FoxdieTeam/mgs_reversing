#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "game/map.h"
#include "linkvar.h"
#include "bullet/rmissile.h"
#include "sd/g_sound.h"

extern int DG_CurrentGroupID;

/*---------------------------------------------------------------------------*/
// RC-Missile (Nikita)

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define NIKITA_MODEL    GV_StrCode("nikita")
#define LIGHT_TEXTURE   GV_StrCode("rcm_l")

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

typedef struct _Work
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
} Work;

STATIC SVECTOR stru_800AB870 = {-100, -800, 80, 0};
STATIC RECT    rect_800AB878 = {100, 100, 200, 200};
STATIC SVECTOR svector_800AB880 = {-50, -300, 100, 0};

/*---------------------------------------------------------------------------*/

static void SetLightTexture(POLY_FT4 *poly, DG_TEX *tex)
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
 * @param   work    Pointer to the Work structure containing missile data.
 * @param   flags   Integer flags indicating the current state or input.
 */
static void UpdateLight(Work *work, int flags)
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
static void Act(Work *work)
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

    GM_CurrentMap = mapBit;

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
    UpdateLight(work, p_flags);

    ammo_count = GM_Weapons[WP_Nikita];
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

            mt2.t[1] = GM_PlayerPosition.vy + 320;

            mt1.t[0] = mt2.t[0];
            mt1.t[1] = mt2.t[1];
            mt1.t[2] = mt2.t[2];

            if (NewRMissile(&mt1, work->which_side))
            {
                GM_Weapons[WP_Nikita] = --ammo_count;
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
static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);
    GM_FreePrim(work->prim);
}

/**
 * @brief Loads resources for the Nikita launcher.
 *
 * @param   work    The Work structure to initialize.
 * @param   parent  The parent OBJECT structure.
 */
static int GetResources(Work *work, OBJECT *parent, int unit)
{
    DG_PRIM        *prim;
    DG_TEX         *tex;
    OBJECT_NO_ROTS *obj;

    obj = &work->object;
    GM_InitObjectNoRots(obj, NIKITA_MODEL, BODY_FLAG, 0);
    if (!obj->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot((OBJECT *)obj, parent, unit);

    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &svector_800AB880, &rect_800AB878);
    work->prim = prim;

    if (prim)
    {
        tex = DG_GetTexture(LIGHT_TEXTURE);
        if (tex)
        {
            SetLightTexture(&prim->packs[0]->poly_ft4, tex);
            SetLightTexture(&prim->packs[1]->poly_ft4, tex);
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
 * @returns The actor's work area.
 */
void *NewRCM(CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "rcm.c");

        if (GetResources(work, parent, num_parent) < 0)
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

    GM_MagazineMax = 0;
    GM_Magazine = 0;

    return (void *)work;
}
